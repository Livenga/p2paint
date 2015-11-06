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

// クラスタリング後の画像保存
//#define SAVE_CLUSTER_IMAGE

typedef unsigned short ushort;

/* src/cluster/c_init.c */
extern ushort // 分類領域の確保
*dist_alloc(const int width,
            const int height);
extern void // 分類の初期化
init_dist(const int k,
          const int width,
          const int height,
          ushort *dist);

extern void   // 分類の解放
release_dist(const int width,
             const int height,
             ushort *dist);

/* src/cluster/c_calc.c */
extern void   // 中心値の計算
calc_cluster_center(const int k,
                    const img read_img,
                    const ushort *dist,
                    p_cluster *_cluster);
extern int // 中心位置の確認
conf_cluster_center(const int k,
                    p_cluster *_cluster);

/* src/cluster/c_print.c */
extern void   // クラスタ値の表示
cluster_print(const int k,
              const p_cluster *_cluster);
extern void
class_print(int width,
            int height,
            ushort *dist);

#else // Kernel Function
/* ..OpenCL用.. */
typedef unsigned char unchar;
double
minof_arg(int count,
          double *euclid_distance);
double
calc_euclid_distance(int position,
                     p_cluster cls_center,
                     unchar *data);
#endif // F_KERNEL

#endif
