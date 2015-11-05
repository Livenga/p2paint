#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/graphic.h"
#include "../../include/canvas.h"

void
img2canvas(img _img,
           canvas *cv) {
  int i;
  int img_size = _img.width * _img.height * _img.colors;

  cv->width  = _img.width;
  cv->height = _img.height;
  cv->colors = _img.colors;

  cv->data = (uchar *)calloc(
      img_size,
      sizeof(uchar));
  memmove((void *)cv->data, (const void *)_img.ldata,
      img_size);
}

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

void free_canvas(canvas *cv) {
  int i, j;

  for(i = 0; i < cv->height; i++)
    for(j = 0; j < cv->width; j++) {
      cv->data[(i * cv->width + j) * 3 + 0] = '\0';
      cv->data[(i * cv->width + j) * 3 + 1] = '\0';
      cv->data[(i * cv->width + j) * 3 + 2] = '\0';
    }
  free(cv->data);
  cv->data = NULL;
}
