#include <stdio.h>
#include <stdlib.h>

#include "../../include/cluster.h"

void cluster_print(const int k,
    const p_cluster *_cluster) {
  int i;
  for(i = 0; i < k; i++) {
    printf("Cluster No.%2d\n", i);
    printf("[R:G:B]\t[%3lu:%3lu:%3lu]\n",
        _cluster[i].r, _cluster[i].g, _cluster[i].b);
  }
}

void class_print(int width,
    int height,
    ushort *dist) {
  int i, j;

  for(i = 0; i < height; i++)
    for(j = 0; j < width; j++)
      printf("%d ", dist[i * width + j]);
}

