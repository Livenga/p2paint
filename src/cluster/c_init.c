#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>

#include "../../include/graphic.h"
#include "../../include/cluster.h"

ushort *dist_alloc(const int width,
    const int height) {
  ushort *dist;
  dist = (ushort *)calloc(width * height, sizeof(ushort));
  return dist;
}

/* 分類値の初期化 */
void init_dist(const int k,
    const int width,
    const int height,
    ushort *dist) {
  int i, j, position;

  for(i = 0; i < height; i++) {
    for(j = 0; j < width; j++) {
      position = i * width + j;
      dist[position] = rand() % k;
    }
  }
}

/* 分類値の解放 */
void release_dist(const int width,
    const int height,
    ushort *dist) {
  int i, j;

  for(i = 0; i < height; i++)
    for(j = 0; j < width; j++)
      dist[i * width + j] = '\0';
  free(dist);
  dist = NULL;
}
