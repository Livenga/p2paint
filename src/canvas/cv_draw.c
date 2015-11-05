#include <stdio.h>
#include <stdlib.h>

#include "../../include/graphic.h"
#include "../../include/canvas.h"

void
draw_circuit(int x0,
             int y0,
             int r,
             canvas *cv,
             img target) {
  int i, j, x, y;
  int dx, dy, out_x, out_y;
  int value, cv_pos, target_pos;

  dx = rand() % target.width;
  dy = rand() % target.height;

  for(i = -r; i < r; i++) {
        y = y0 + i;
    out_y = dy + i;

    for(j = -r; j < r; j++) {
          x = x0 + j;
      out_x = dx + j;

      value  = i * i + j * j;
      cv_pos = y * target.width + x;
      target_pos = out_y * target.width + out_x;

      if(value <= (r * r) &&
          x > -1 && y > -1 &&
          x < target.width && y < target.height &&
          (out_x) > -1 && (out_y) > -1 &&
          (out_x) < target.width && (out_y) < target.height
          ) {
        cv->data[cv_pos * 3 + 0] = target.ldata[target_pos * 3 + 0];
        cv->data[cv_pos * 3 + 1] = target.ldata[target_pos * 3 + 1];
        cv->data[cv_pos * 3 + 2] = target.ldata[target_pos * 3 + 2];
      }
#if 0
      else {
        cv->data[cv_pos * 3 + 0] = 0xFF;
        cv->data[cv_pos * 3 + 1] = 0xFF;
        cv->data[cv_pos * 3 + 2] = 0xFF;
      }
#endif

    }
  }
}
