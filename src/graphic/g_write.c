#include <stdio.h>
#include <stdlib.h>
#include <png.h>

#include "../../include/graphic.h"
#include "../../include/cluster.h"
#include "../../include/canvas.h"

int pnwrite_from_dist(const char *path,
    int width,
    int height,
    int k,
    unsigned short *dist,
    uchar **data) {
  int i, j;
  int position; // distance position
  FILE *png_fp;
  png_structp png_ptr;
  png_infop info_ptr;
  uchar **img_data;

  if((png_fp = fopen(path, "wb")) == NULL) {
    perror(path);
    return EOF;
  }
  png_ptr = png_create_write_struct(
      PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  info_ptr = png_create_info_struct(png_ptr);

  png_init_io(png_ptr, png_fp);

  png_set_IHDR(png_ptr, info_ptr,
      width, height,  8, PNG_COLOR_TYPE_RGB,
      PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE,
      PNG_FILTER_TYPE_BASE);

  img_data = (uchar **)calloc(height, sizeof(uchar *));
  for(i = 0; i < height; i++) {
    img_data[i] = (uchar *)calloc(width * 3, sizeof(uchar));
    
    for(j = 0; j < width; j++) {
    position = i * width + j;

      if(dist[position] == k) {
        img_data[i][j * 3 + 0] = data[i][j * 3 + 0];
        img_data[i][j * 3 + 1] = data[i][j * 3 + 1];
        img_data[i][j * 3 + 2] = data[i][j * 3 + 2];
      }
      else {
        img_data[i][j * 3 + 0] = 0x0;
        img_data[i][j * 3 + 1] = 0x0;
        img_data[i][j * 3 + 2] = 0x0;
      }

    }
  }

  png_write_info(png_ptr, info_ptr);
  png_write_image(png_ptr, (png_bytepp)img_data);
  png_write_end(png_ptr, info_ptr);

  png_destroy_info_struct(png_ptr, &info_ptr);
  png_destroy_write_struct(&png_ptr, &info_ptr);
  fclose(png_fp);

  for(i = 0; i < height; i++) {
    for(j = 0; j < width; j++) {
      img_data[i][j * 3 + 0] = '\0';
      img_data[i][j * 3 + 1] = '\0';
      img_data[i][j * 3 + 2] = '\0';
    }
    free(img_data[i]);
    img_data[i] = NULL;
  }
  free(img_data);
  img_data = NULL;
  return 0;
}

int pnwrite_from_cluster(const char *path,
    int width,
    int height,
    p_cluster *_cluster,
    unsigned short *dist) {
  int i, j;
  int position; // distance position
  FILE *png_fp;
  png_structp png_ptr;
  png_infop info_ptr;
  uchar **img_data;

  if((png_fp = fopen(path, "wb")) == NULL) {
    perror(path);
    return EOF;
  }
  png_ptr = png_create_write_struct(
      PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  info_ptr = png_create_info_struct(png_ptr);

  png_init_io(png_ptr, png_fp);

  png_set_IHDR(png_ptr, info_ptr,
      width, height,  8, PNG_COLOR_TYPE_RGB,
      PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE,
      PNG_FILTER_TYPE_BASE);

  img_data = (uchar **)calloc(height, sizeof(uchar *));
  for(i = 0; i < height; i++) {
    img_data[i] = (uchar *)calloc(width * 3, sizeof(uchar));
    
    for(j = 0; j < width; j++) {
    position = i * width + j;

    img_data[i][j * 3 + 0] = _cluster[dist[position]].r;
    img_data[i][j * 3 + 1] = _cluster[dist[position]].g;
    img_data[i][j * 3 + 2] = _cluster[dist[position]].b;
    }
  }

  png_write_info(png_ptr, info_ptr);
  png_write_image(png_ptr, (png_bytepp)img_data);
  png_write_end(png_ptr, info_ptr);

  png_destroy_info_struct(png_ptr, &info_ptr);
  png_destroy_write_struct(&png_ptr, &info_ptr);
  fclose(png_fp);

  for(i = 0; i < height; i++) {
    for(j = 0; j < width; j++) {
      img_data[i][j * 3 + 0] = '\0';
      img_data[i][j * 3 + 1] = '\0';
      img_data[i][j * 3 + 2] = '\0';
    }
    free(img_data[i]);
    img_data[i] = NULL;
  }
  free(img_data);
  img_data = NULL;
  return 0;
}

int pnwrite_from_canvas(const char *path,
    canvas cv) {
  int i, j;
  int position; // distance position
  FILE *png_fp;
  png_structp png_ptr;
  png_infop info_ptr;
  uchar **img_data;

  if((png_fp = fopen(path, "wb")) == NULL) {
    perror(path);
    return EOF;
  }
  png_ptr = png_create_write_struct(
      PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  info_ptr = png_create_info_struct(png_ptr);

  png_init_io(png_ptr, png_fp);

  png_set_IHDR(png_ptr, info_ptr,
      cv.width, cv.height,  8, PNG_COLOR_TYPE_RGB,
      PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE,
      PNG_FILTER_TYPE_BASE);

  img_data = (uchar **)calloc(cv.height, sizeof(uchar *));
  for(i = 0; i < cv.height; i++) {
    img_data[i] = (uchar *)calloc(cv.width * 3, sizeof(uchar));
    
    for(j = 0; j < cv.width; j++) {
    position = i * cv.width + j;

    img_data[i][j * 3 + 0] = cv.data[position * 3 + 0];
    img_data[i][j * 3 + 1] = cv.data[position * 3 + 1];
    img_data[i][j * 3 + 2] = cv.data[position * 3 + 2];
    }
  }

  png_write_info(png_ptr, info_ptr);
  png_write_image(png_ptr, (png_bytepp)img_data);
  png_write_end(png_ptr, info_ptr);

  png_destroy_info_struct(png_ptr, &info_ptr);
  png_destroy_write_struct(&png_ptr, &info_ptr);
  fclose(png_fp);

  for(i = 0; i < cv.height; i++) {
    for(j = 0; j < cv.width; j++) {
      img_data[i][j * 3 + 0] = '\0';
      img_data[i][j * 3 + 1] = '\0';
      img_data[i][j * 3 + 2] = '\0';
    }
    free(img_data[i]);
    img_data[i] = NULL;
  }
  free(img_data);
  img_data = NULL;
  return 0;
}
