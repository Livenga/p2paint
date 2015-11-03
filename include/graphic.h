#ifndef GRAPHIC_H
#define GRAPHIC_H

#define GDEBUG

typedef unsigned char uchar;

typedef struct _img {
  size_t color_type;
  size_t colors;
  size_t bit_depth;
  size_t bit_size;

  size_t width, height;

  uchar **data;
} img;

/* src/graphic/g_png.c */
extern int pnread(const char *path,
    img *_img);
#endif
