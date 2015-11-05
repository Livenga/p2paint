#ifndef CANVAS_H
#define CANVAS_H

typedef unsigned char uchar;
typedef struct _canvas {
  size_t width, height, colors;
  uchar *data;
} canvas;

/* src/canvas/cv_init.c */
extern canvas
cvalloc(int width,  /* 横幅 */
        int height, /* 縦幅 */
        int colors  /* 色サイズ */);

/* src/canvas/cv_util.c */
extern void
release_canvas(int population,
               canvas *cv);
#endif