#include <stdio.h>
#include <stdlib.h>
#include <png.h>

#include "../../include/graphic.h"

#if defined(GDEBUG)
const char *color_type_str(const size_t type);
#endif

int pnread(const char *path,
    img *_img) {
  FILE *png_fp;
  png_structp png_ptr;
  png_infop info_ptr;

  if((png_fp = fopen(path, "rb")) == NULL) {
    perror(path);
    return EOF;
  }

  png_ptr = png_create_read_struct(
      PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  info_ptr = png_create_info_struct(png_ptr);

  png_init_io(png_ptr, png_fp);
  png_read_info(png_ptr, info_ptr);

  // 画像情報取得
  png_uint_32 width, height;
  png_byte color_type, bit_depth;

  width  = png_get_image_width(png_ptr, info_ptr);
  height = png_get_image_height(png_ptr, info_ptr);
  bit_depth  = png_get_bit_depth(png_ptr, info_ptr);
  color_type = png_get_color_type(png_ptr, info_ptr);

  switch(color_type) {
    case PNG_COLOR_TYPE_GRAY: _img->colors = 1; break;
    case PNG_COLOR_TYPE_GA:   _img->colors = 2; break;
    case PNG_COLOR_TYPE_RGB:  _img->colors = 3; break;
    case PNG_COLOR_TYPE_RGBA: _img->colors = 4; break;
  }
  _img->bit_size = _img->colors * (bit_depth / 8);

  _img->width  = width;
  _img->height = height;
  _img->color_type = color_type;
  _img->bit_depth  = bit_depth;

#if defined(GDEBUG)
  printf("PNG Size\t%lux%lu\n", width, height);
  printf("PNG Color Type\t%s\n", color_type_str(color_type));
  printf("PNG Bit depth\t%d\n", bit_depth);
#endif

  int i, j, k;
  _img->ldata = (uchar *)calloc(
      height * width * _img->bit_size, sizeof(uchar));

  _img->data = (uchar **)calloc(
      height, sizeof(uchar *));
  for(i = 0; i < height; i++)
    _img->data[i] = (uchar *)calloc(
        width * _img->bit_size, sizeof(uchar));

  png_read_image(png_ptr, (png_bytepp)_img->data);
  png_read_end(png_ptr, info_ptr);

  png_destroy_info_struct(png_ptr, &info_ptr);
  png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

  int img_pos;
  for(i = 0; i < height; i++) {
    for(j = 0; j < width; j++) {
      img_pos = i * width + j;

      for(k = 0; k < _img->colors; k++)
        _img->ldata[img_pos * 3 + k] = _img->data[i][j * 3 + k];
    }
  }
  fclose(png_fp);

  return 0;
}
