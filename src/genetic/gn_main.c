#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/opencl.h"
#include "../../include/graphic.h"
#include "../../include/genetic.h"
#include "../../include/canvas.h"

void run_genetic(cl_prop prop,
    img target) {
  int i;
  canvas *pr_canvas, *ch_canvas;

  pr_canvas = (canvas *)calloc(POPULATION_SIZE, sizeof(canvas));
  for(i = 0; i < POPULATION_SIZE; i++) { /* 個体集合の初期化 */
    pr_canvas[i] = cvalloc(target.width, target.height, target.colors);
  }

  ch_canvas = (canvas *)calloc(CHILDREN_SIZE, sizeof(canvas));
  for(i = 0; i < CHILDREN_SIZE; i++) /* 子個体集合領域の確保 */
    ch_canvas[i] = cvalloc(target.width, target.height, target.colors);

  /* Canvas領域の解放(後処理) */
  //printf("%p\n", pr_canvas);
  release_canvas(POPULATION_SIZE, pr_canvas);
  //printf("%p\n", ch_canvas);
  release_canvas(CHILDREN_SIZE, ch_canvas);
}
