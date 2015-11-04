#define F_KERNEL

#include <cluster.h>

__kernel void cluster(
    __global int           *k,
    __global img_info      *info,
    __global p_cluster     *cls_center,
    __global ushort        *dist,
    __global unsigned char *data
    ) {
  const int num_k = *k;
  const int x = get_global_id(0), y = get_global_id(1);
  const int img_position = y * info->width + x;
  const unsigned char *img_data = (unsigned char *)data;

  int i, min_arg;
  double euclid_distance[256];

  for(i = 0; i < num_k; i++) {
    euclid_distance[i] = calc_euclid_distance(
        img_position, cls_center[i], (unsigned char *)data 
        );
  }

  min_arg = minof_arg(num_k, euclid_distance);
  dist[img_position] = min_arg;
}
