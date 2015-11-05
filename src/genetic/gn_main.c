#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/opencl.h"
#include "../../include/graphic.h"
#include "../../include/genetic.h"
#include "../../include/canvas.h"


extern void
img2canvas(img _img,
           canvas *cv);
/* src/genetic/gn_calc.c */
/* 適応度計算 */
extern double
calc_fitness(canvas input, /* 個体仮想Canvas */
             canvas teach  /* 目標画像Canvas */);

void
run_genetic(cl_prop prop,
            img target,
            img paint) {
  size_t cnt_generation;
  int i, R;
  double pr_fitness[POPULATION_SIZE], ch_fitness[CHILDREN_SIZE];

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

      /* 2015/11/05 12:55
       * 円描画に関して, cv_target のサイズを考慮していない */
      draw_circuit(R, &pr_canvas[i], cv_paint);
    }
    sprintf(output, "imgs/canvas/canvas%03d.png", i);
    pnwrite_from_canvas(output, pr_canvas[i]);

    pr_fitness[i] = calc_fitness(cv_target, pr_canvas[i]);
    printf("\033[1m[個体適応度 No.%3d] %f\033[0m\n", i, pr_fitness[i]);
  }

  int slt_rand[2];
  int slt_best;
  cnt_generation = 0;
  do {
    // 個体から2つ選択
    slt_rand[0] = rand() % POPULATION_SIZE;
    slt_rand[1] = rand() % POPULATION_SIZE;
    while(slt_rand[0] == slt_rand[1])
      slt_rand[1] = rand() % POPULATION_SIZE;

    // 交叉

    // 子個体集合評価
    for(i = 0; i < CHILDREN_SIZE; i++)
      ch_fitness[i] = calc_fitness(cv_target, ch_canvas[i]);
    slt_best = minof_fitness(CHILDREN_SIZE, ch_fitness);

  } while(++cnt_generation != NUMBER_OF_GENERATION);

  printf("[終了世代] %d\n", cnt_generation);

  /* Canvas領域の解放(後処理) */
  free_canvas(&cv_target);
  free_canvas(&cv_paint);
  //release_canvas(POPULATION_SIZE, pr_canvas);
  //release_canvas(CHILDREN_SIZE, ch_canvas);
}
