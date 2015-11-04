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

  uchar *ldata;
  uchar **data;
} img;

/* src/graphic/g_png.c */
extern int // PNG読み込み
pnread(const char *path,
       img *_img);

/* src/graphic/g_util.c */
extern void // 構造体img の解放
release_img(img *_img);
#endif
