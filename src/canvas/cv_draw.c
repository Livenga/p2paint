#include <stdlib.h>
#include "../../include/canvas.h"

void
draw_circuit(int r,
             canvas *cv_paint,
             canvas cv_target) {
  int i, j;
  int circ_area, paint_pos, target_pos;

  int pt_x0, pt_y0;
  int tr_x0, tr_y0;
  int paint_x0, paint_y0;
  int target_x0, target_y0;

  /* Paint Canvas の描画中心点 */
  pt_x0 = rand() % cv_paint->width;
  pt_y0 = rand() % cv_paint->height;

  /* Target Canvas の描画中心点 */
  tr_x0 = rand() % cv_target.width;
  tr_y0 = rand() % cv_target.height;

  for(i = -r; i < r; i++) {
    target_y0 = tr_y0 + i;
    paint_y0  = pt_y0 + i;

    for(j = -r; j < r; j++) {
    target_x0 = tr_x0 + j;
    paint_x0  = pt_x0 + j;

      circ_area  = i * i + j * j; // 円領域
      paint_pos  = paint_y0  * cv_paint->width + paint_x0;
      target_pos = target_y0 * cv_target.width + target_x0;

      /* Paint, Target Canvas
       * 画像内のみ描画 */
      if(circ_area <= (r * r) &&
          target_x0 > -1 && target_y0 > -1 &&
          target_x0 < cv_target.width && target_y0 < cv_target.height &&
          paint_x0 > -1 && paint_y0 > -1 &&
          paint_x0 < cv_paint->width && paint_y0 < cv_paint->height
          ) {
        cv_paint->data[paint_pos * 3 + 0] =
          cv_target.data[target_pos * 3 + 0];
        cv_paint->data[paint_pos* 3 + 1] =
          cv_target.data[target_pos * 3 + 1];
        cv_paint->data[paint_pos * 3 + 2] =
          cv_target.data[target_pos * 3 + 2];
      }
    }
  }
}
