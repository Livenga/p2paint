#include <stdio.h>
#include <stdlib.h>

#include "../../include/graphic.h"
#include "../../include/opencl.h"
#include "../../include/cluster.h"

/* 所属クラスタの中心地計算 */
void calc_cluster(const int k,
    const img read_img,
    const ushort *dist,
    p_cluster *_cluster) {
  int i, j, position;
  size_t sum_r, sum_g, sum_b, cnt;
  sum_r = 0;
  sum_g = 0;
  sum_b = 0;

  cnt = 0;
  for(i = 0; i < read_img.height; i++) {
    for(j = 0; j < read_img.width; j++) {
      position = i * read_img.width + j;

      if(k == dist[position]) {
        sum_r += read_img.data[i][j * 3 + 0];
        sum_g += read_img.data[i][j * 3 + 1];
        sum_b += read_img.data[i][j * 3 + 2];
        ++cnt;
      }

    }
  }

  if(cnt != 0) {
    _cluster->r = sum_r / cnt;
    _cluster->g = sum_g / cnt;
    _cluster->b = sum_b / cnt;
  }
  else {
    _cluster->r = 0;
    _cluster->g = 0;
    _cluster->b = 0;
  }
}
