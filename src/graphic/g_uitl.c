#include <stdio.h>
#include <stdlib.h>
#include <png.h>

#include "../../include/graphic.h"

void release_img(img *_img) {
  int i, j, k;
  int img_pos;

  for(i = 0; i < _img->height; i++) {
    for(j = 0; j < _img->width; j++) {
      img_pos = i * _img->width + j;
      for(k = 0; k < _img->colors; k++) {
        _img->data[i][j * 3 + k]     = '\0';
        _img->ldata[img_pos * 3 + k] = '\0';
      }
    }
    free(_img->data[i]);
    _img->data[i] = NULL;
  }

  free(_img->data);
  _img->data = NULL;

  free(_img->ldata);
  _img->ldata = NULL;
}
