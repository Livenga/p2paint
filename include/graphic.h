#ifndef GRAPHIC_H
#define GRAPHIC_H

#define GDEBUG

#ifndef CANVAS_H
typedef unsigned char uchar;
#endif

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
/* src/graphic/g_write.c */
extern int
pnwrite_from_dist(const char *path,
                  int width,
                  int height,
                  int k,
                  unsigned short *dist,
                  uchar **data);

/* src/graphic/g_util.c */
extern void // 構造体img の解放
release_img(img *_img);


/* src/graphic/g_c2csv.c */
extern int // 画像データをcsvに変換
save_csv(const char *path,
         img _img);
#endif
