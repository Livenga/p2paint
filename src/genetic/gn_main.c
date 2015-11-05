#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/opencl.h"
#include "../../include/graphic.h"
#include "../../include/genetic.h"
#include "../../include/canvas.h"

#if 0
/* src/canvas/cv_draw.c */
extern void
draw_circuit(int x0,
             int y0,
             int r,
             canvas *cv,
             img target);
#else
extern void
draw_circuit(int x0,
             int y0,
             int r,
             canvas *cv,
             canvas cv_target);
#endif

extern void
img2canvas(img _img,
           canvas *cv);

void
run_genetic(cl_prop prop,
            img target,
            img paint) {
  size_t cnt_generation;
  int i, R;
  int x0, y0; // 円描画位置
  canvas cv_target, cv_paint;
  canvas pr_canvas[POPULATION_SIZE], ch_canvas[CHILDREN_SIZE];

  /* img -> canvas */
  img2canvas(target, &cv_target);
  img2canvas(paint,  &cv_paint);

  /* 個体集合の初期化 */
  for(i = 0; i < POPULATION_SIZE; i++) 
    pr_canvas[i] = cvalloc(target.width, target.height, target.colors);

  /* 子個体集合領域の確保 */
  for(i = 0; i < CHILDREN_SIZE; i++) 
    ch_canvas[i] = cvalloc(target.width, target.height, target.colors);

  char output[1024];
  for(i = 0; i < POPULATION_SIZE; i++) {
    while(cv_finish_init(pr_canvas[i]) < 0.8) {
      R = (rand() % 40) + 40 + 1;
      x0 = rand() % cv_target.width;
      y0 = rand() % cv_target.height;

      /* 2015/11/05 12:55
       * 円描画に関して, cv_target のサイズを考慮していない */
      draw_circuit(x0, y0, R, &pr_canvas[i], cv_target);
    }
    sprintf(output, "imgs/canvas/canvas%03d.png", i);
    pnwrite_from_canvas(output, pr_canvas[i]);
  }

  cnt_generation = 0;
  do {
  } while(++cnt_generation != NUMBER_OF_GENERATION);

  printf("[終了世代] %d\n", cnt_generation);

  /* Canvas領域の解放(後処理) */
  free_canvas(&cv_target);
  free_canvas(&cv_paint);
  //release_canvas(POPULATION_SIZE, pr_canvas);
  //release_canvas(CHILDREN_SIZE, ch_canvas);
}
