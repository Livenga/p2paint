#include <cluster.h>

__kernel void cluster(
    __global img_info *info
    ) {
  const int x = get_global_id(0), y = get_global_id(1);
  
  printf("%3dx%3d(%d)\t%dx%d\n",
      (int)info->width, (int)info->height, (int)info->colors, x, y);
}
