#include <stdio.h>
#include <stdlib.h>

#include "../../include/cluster.h"

void cluster_print(const int k,
    const p_cluster *_cluster) {
  int i;
  for(i = 0; i < k; i++) {
    printf("Cluster No.%2d\n", i);
    printf("R:G:B\t%u\t%u\t%u\n",
        _cluster[i].r, _cluster[i].g, _cluster[i].b);
  }
}
