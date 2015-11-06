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
/* src/genetic/gn_crossover.c */
extern void
gn_crossover(const ushort **segment_data,
             int population,
             canvas cv_target,
             canvas cv_paint,
             canvas cv_in01,
             canvas cv_in02,
             canvas *cv_child);


void
run_genetic(cl_prop prop,
            const ushort **segment_data,
            img target,
            img paint) {
  const size_t img_size = target.width * target.height * target.colors;
  size_t cnt_generation;
  int i, R;
  double pr_fitness[POPULATION_SIZE],
         ch_fitness[CHILDREN_SIZE];

  canvas cv_target, cv_paint;
  canvas pr_canvas[POPULATION_SIZE],
         ch_canvas[CHILDREN_SIZE];

  /* img -> canvas */
  img2canvas(target, &cv_target);
  img2canvas(paint,  &cv_paint);

  /* 個体集合の初期化 */
  for(i = 0; i < POPULATION_SIZE; i++) 
    pr_canvas[i] = cvalloc(
        target.width,
        target.height,
        target.colors);

  /* 子個体集合領域の確保 */
  for(i = 0; i < CHILDREN_SIZE; i++) 
    ch_canvas[i] = cvalloc(
        target.width,
        target.height,
        target.colors);

  char output[1024];
  for(i = 0; i < POPULATION_SIZE; i++) {
    while(cv_finish_init(pr_canvas[i]) < 0.8) {
      R = (rand() % 41) + 40;
      //R = (rand() % 21) + 10;

      /* 2015/11/05 12:55
       * cv_target のサイズを考慮していない 
       * !!! 修正完了 !!! */
      draw_circuit(R / 2, &pr_canvas[i], cv_paint);
    }
    sprintf(output, "imgs/canvas/canvas%03d.png", i);
    pnwrite_from_canvas(output, pr_canvas[i]);

    pr_fitness[i] = calc_fitness(
        cv_target, pr_canvas[i]);
    printf("\033[1m[個体適応度 No.%3d] %f\033[0m\n",
        i, pr_fitness[i]);
  }

  int slt_rand[2];
  int slt_best, slt_roul;

  char gen_path[1024];
  cnt_generation = 0;
  do {
    // 個体から2つ選択
    slt_rand[0] = rand() % POPULATION_SIZE;
    slt_rand[1] = rand() % POPULATION_SIZE;
    while(slt_rand[0] == slt_rand[1])
      slt_rand[1] = rand() % POPULATION_SIZE;

    // 交叉
    gn_crossover(segment_data, CHILDREN_SIZE,
        cv_target, cv_paint,
        pr_canvas[slt_rand[0]], pr_canvas[slt_rand[1]], ch_canvas);

    // 子個体集合評価
    for(i = 0; i < CHILDREN_SIZE; i++) {
      ch_fitness[i] =
        calc_fitness(cv_target, ch_canvas[i]);
      //printf("%f\n", ch_fitness[i]);
    }

    slt_best =
      minof_fitness(CHILDREN_SIZE, ch_fitness);
    //slt_roul = rand() % CHILDREN_SIZE;
    slt_roul = slt_best;

    memmove((void *)pr_canvas[slt_rand[0]].data,
        (const void *)ch_canvas[slt_best].data, sizeof(uchar) * img_size);
    memmove((void *)pr_canvas[slt_rand[1]].data,
        (const void *)ch_canvas[slt_roul].data, sizeof(uchar) * img_size);

    if((cnt_generation % 100) == 0) {
      printf("No.%5d: %f\n", cnt_generation, ch_fitness[slt_best]);
      sprintf(gen_path,"gen/gen%05d.png", cnt_generation);
      pnwrite_from_canvas(gen_path, pr_canvas[slt_rand[0]]);
    }

  } while(++cnt_generation != NUMBER_OF_GENERATION);

  printf("[終了世代] %d\n", cnt_generation);

  /* Canvas領域の解放(後処理) */
  free_canvas(&cv_target);
  free_canvas(&cv_paint);
}
