#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/canvas.h"

double cv_finish_init(canvas cv) {
  int i, j, k, position;
  int sum, count = 0;

  for(i = 0; i < cv.height; i++) {
    for(j = 0; j < cv.width; j++) {
      position = i * cv.width + j;

      sum = 0;
      for(k = 0; k < cv.colors; k++)
        sum += cv.data[position * 3 + k];
      if(sum != (0xFF * 3)) ++count;
    }
  }

  return (double)count / (cv.width * cv.height);
}

/* Canvas領域の解放 */
void release_canvas(int population,
    canvas *cv) {
  int cnt_p;
  int i, j, k;

  //printf("%p\n", cv);
  for(cnt_p = 0; cnt_p < population; cnt_p++) {
    for(i = 0; i < cv[cnt_p].height; i++)
      for(j = 0; j < cv[cnt_p].width; j++)
        for(k = 0; k < cv[cnt_p].colors; k++)
          cv[cnt_p].data[(i * cv->width + j) * 3 + k] = '\0';
    free(cv[cnt_p].data);
    cv[cnt_p].data = NULL;
  }
  free(cv);
  cv = NULL;
}
