#include <stdio.h>
#include <stdlib.h>

#include "../../include/graphic.h"
#include "../../include/opencl.h"
#include "../../include/cluster.h"

/* 所属クラスタの中心地計算 */
void calc_cluster_center(const int k,
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
#if 1
        sum_r += read_img.data[i][j * 3 + 0];
        sum_g += read_img.data[i][j * 3 + 1];
        sum_b += read_img.data[i][j * 3 + 2];
#else
        sum_r += read_img.ldata[position * 3 + 0];
        sum_g += read_img.ldata[position * 3 + 1];
        sum_b += read_img.ldata[position * 3 + 2];
#endif
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
#if 0
    _cluster->r = _cluster->r;
    _cluster->g = _cluster->g;
    _cluster->b = _cluster->b;
#else
    _cluster->r = 0;
    _cluster->g = 0;
    _cluster->b = 0;
#endif
  }
}

int conf_cluster_center(const int k,
    p_cluster *_cluster) {
  int i, conf = 0;

  for(i = 0; i < k - 1; i++) {
    conf += _cluster[i].r == _cluster[i + 1].r;
    conf += _cluster[i].g == _cluster[i + 1].g;
    conf += _cluster[i].b == _cluster[i + 1].b;
  }

  return ((conf == 0) ? 0 : 1);
}
