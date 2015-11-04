#define F_KERNEL
#include <cluster.h>

double
calc_euclid_distance(int position,
                     p_cluster cls_center,
                     unchar *data) {
  int i;
  double diff[3] = {0.0}, euclid = 0.0;

  diff[0] = (double)data[position * 3 + 0] - cls_center.r;
  diff[1] = (double)data[position * 3 + 1] - cls_center.g;
  diff[2] = (double)data[position * 3 + 2] - cls_center.b;

  for(i = 0; i < 3; i++)
    euclid += (diff[i] * diff[i]);
  return euclid;
}

double
minof_arg(int count,
          double *euclid_distance) {
    int i, arg = 0;
    double minof = euclid_distance[0];

    for(i = 1; i < count; i++) {
      if(minof > euclid_distance[i]) {
        minof = euclid_distance[i];
        arg = i;
      }
    }
    return arg;
}
