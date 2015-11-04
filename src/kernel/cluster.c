#define F_KERNEL

#include <cluster.h>

//typedef unsigned char uchar;

__kernel void cluster(
    __global int           *k,
    __global img_info      *info,
    __global ushort        *dist,
    __global unsigned char *data
    ) {
  const int num_k = *k;
  const int x = get_global_id(0), y = get_global_id(1);
  
  printf("%3dx%3d(%d)\t%dx%d\t%d(0x%02X%02X%02X) %d\n",
      (int)info->width, (int)info->height, (int)info->colors, x, y, num_k,
      data[y * (info->width) + x * 3 + 0],
      data[y * (info->width) + x * 3 + 1],
      data[y * (info->width) + x * 3 + 2],
      dist[y * (info->width) + x]);

}
