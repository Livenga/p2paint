#include <stdio.h>
#include <math.h>

#include "../../include/canvas.h"

double
calc_fitness(canvas input, /* 個体仮想Canvas */
             canvas teach  /* 目標画像Canvas */) {
  int i, j, k;
  int position;
  double diff, sum_diff, sumof;

  sumof = 0.0;
  for(i = 0; i < input.height; i++) {
    for(j = 0; j < input.width; j++) {
      position = i * input.width + j;
      sum_diff = 0.0;

      for(k = 0; k < input.colors; k++) {
        diff = (double)input.data[position * 3 + k] - teach.data[position * 3 + k];
        sum_diff += diff * diff;
      }

      sumof += sqrt(sum_diff);
    }
  }
  return sumof;
}

int
minof_fitness(int population,
              double *fitness) {
  int i, arg = 0;
  double minof = fitness[0];

  for(i = 1; i < population; i++) {
    if(minof > fitness[i]) {
      minof = fitness[i];
      arg = i;
    }
  }
  return arg;
}
