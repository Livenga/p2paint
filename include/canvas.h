#ifndef CANVAS_H
#define CANVAS_H

#ifndef GRAPHIC_H
typedef unsigned char uchar;
#endif

typedef struct _canvas {
  size_t width, height, colors;
  uchar *data;
} canvas;

/* src/canvas/cv_init.c */
extern canvas
cvalloc(int width,  /* 横幅 */
        int height, /* 縦幅 */
        int colors  /* 色サイズ */);

/* src/canvas/cv_draw.c */
// *cv_paintにcv_targetより円を描画
extern void
draw_circuit(int r,            /* 円半径 */
             canvas *cv_paint, /* Paint  Canvas */
             canvas cv_target  /* Target Canvas */);

/* src/canvas/cv_util.c */
extern double
cv_finish_init(canvas cv);
extern void
release_canvas(int population,
               canvas *cv);
extern void
free_canvas(canvas *cv);

extern int
pnwrite_from_canvas(const char *path,
                    canvas cv);
#endif
