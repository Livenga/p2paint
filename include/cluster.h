#ifndef CLUSTER_H
#define CLUSTER_H

typedef struct _image_info {
  size_t width, height, colors;
} img_info;

typedef struct _cluster {
  size_t  r, g, b;
} p_cluster;

#ifndef F_KERNEL
/* ..Common Function.. */
#ifndef GRAPHIC_H
#include "graphic.h"
#endif

typedef unsigned short ushort;

/* src/cluster/c_init.c */
extern ushort // 分類の初期化
*init_dist(const int k,
           const int width,
           const int height);

extern void   // 分類の解放
release_dist(const int width,
             const int height,
             ushort *dist);

/* src/cluster/c_calc.c */
extern void   // 中心値の計算
calc_cluster(const int k,
             const img read_img,
             const ushort *dist,
             p_cluster *_cluster);


/* src/cluster/c_print.c */
extern void   // クラスタ値の表示
cluster_print(const int k,
              const p_cluster *_cluster);

#else // Kernel Function
/* ..OpenCL用.. */
#endif // F_KERNEL

#endif
