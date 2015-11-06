#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/cluster.h"
#include "../../include/canvas.h"
#include "../../include/genetic.h"

void
copy_canvas(int label,
    const ushort *segment,
    canvas cv_in01,
    canvas cv_in02,
    canvas cv_child01,
    canvas cv_child02);
void
gn_crossover(const ushort **segment_data,
             int population,
             canvas cv_target,
             canvas cv_paint,
             canvas cv_in01,
             canvas cv_in02,
             canvas *cv_child) {
  const int img_size = cv_in01.width * cv_in01.height * cv_in01.colors;
  int i;
  int k, label;
  int R;
  double cross_rate;

  for(i = 0; i < population; i += 2) {
    k = rand() % 9;

    // 交叉
    cross_rate = (double)(rand() % 100) / 100.0;
    if(cross_rate < CROSSOVER_RAGE) {
      label = (k == 0) ? 0 : rand() % k;
      
      copy_canvas(label, (const ushort *)segment_data[k],
          cv_in01, cv_in02, cv_child[i], cv_child[i + 1]);
    }
    else {
      memmove((void *)cv_child[i].data,     (const void *)cv_in01.data,
          sizeof(uchar) * img_size);
      memmove((void *)cv_child[i + 1].data, (const void *)cv_in02.data,
          sizeof(uchar) * img_size);
    }

    // 突然変異
    R = (rand() % 21) + 20;
    //R = (rand() % 11) + 5;
    draw_circuit(R / 2, &cv_child[i],     cv_paint);
    draw_circuit(R / 2, &cv_child[i + 1], cv_paint);
  }
}

void
copy_canvas(int label,
    const ushort *segment,
    canvas cv_in01,
    canvas cv_in02,
    canvas cv_child01,
    canvas cv_child02) {
  int i, j;
  int position;

  for(i = 0; i < cv_in01.height; i++) {
    for(j = 0; j < cv_in01.width; j++) {
      position = i * cv_in01.width + j;

      //printf("%dx%d\n", j, i);
      if(segment[position] == label) {
        cv_child01.data[position * 3 + 0] = cv_in02.data[position * 3 + 0];
        cv_child01.data[position * 3 + 1] = cv_in02.data[position * 3 + 1];
        cv_child01.data[position * 3 + 2] = cv_in02.data[position * 3 + 2];

        cv_child02.data[position * 3 + 0] = cv_in01.data[position * 3 + 0];
        cv_child02.data[position * 3 + 1] = cv_in01.data[position * 3 + 1];
        cv_child02.data[position * 3 + 2] = cv_in01.data[position * 3 + 2];
      }
      else {
        cv_child01.data[position * 3 + 0] = cv_in01.data[position * 3 + 0];
        cv_child01.data[position * 3 + 1] = cv_in01.data[position * 3 + 1];
        cv_child01.data[position * 3 + 2] = cv_in01.data[position * 3 + 2];

        cv_child02.data[position * 3 + 0] = cv_in02.data[position * 3 + 0];
        cv_child02.data[position * 3 + 1] = cv_in02.data[position * 3 + 1];
        cv_child02.data[position * 3 + 2] = cv_in02.data[position * 3 + 2];
      }

    }
  }
}
