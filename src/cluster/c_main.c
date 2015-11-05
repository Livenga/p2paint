#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>

#include "../../include/graphic.h"
#include "../../include/opencl.h"
#include "../../include/cluster.h"

#define K 11
//#define K 10
#define MAX_RANGE 200

/* src/graphic/g_write.c */
extern int
pnwrite_from_cluster(const char *path,
                     int width,
                     int height,
                     p_cluster *_cluster,
                     unsigned short *dist);

void set_image_info(img _img, img_info *info);

void run_k_means(cl_prop prop, img read_img) {
  const size_t img_size = read_img.width * read_img.height;
  int num_k = K, k;

  cl_int status;           // エラー状態
  size_t global_size[2];   // 並列次元数
  img_info info;           // 画像情報
  cluster_args cl_cls_arg; // Kernel引数

  ushort *k2;          // 分類
  p_cluster cls_k2[K]; // クラスタ

  set_image_info(read_img, &info);
  k2 = dist_alloc(read_img.width, read_img.height);

  do {
    init_dist(K, read_img.width, read_img.height, k2);
    for(k = 0; k < K; k++)
      calc_cluster_center(k, read_img, (const ushort *)k2, &cls_k2[k]);
  } while(conf_cluster_center(K, cls_k2) == 0);

  /* ++++ OpenCL Kernel関数の引数設定 ++++ */
  cl_cls_arg.k = clCreateBuffer(prop.context,
      CL_READ_COPY, sizeof(int), (void *)&num_k, &status);
  cl_cls_arg.img_info = clCreateBuffer(prop.context,
      CL_READ_COPY, sizeof(img_info), (void *)&info, NULL);
  cl_cls_arg.cls_center = clCreateBuffer(prop.context,
      CL_MEM_READ_ONLY, sizeof(p_cluster) * K, (void *)NULL, NULL);
  cl_cls_arg.dist = clCreateBuffer(prop.context,
      CL_MEM_READ_WRITE, sizeof(ushort) * img_size, (void *)NULL, &status);
  cl_cls_arg.data = clCreateBuffer(prop.context,
      CL_READ_COPY, sizeof(uchar) * img_size * 3, (void *)read_img.ldata, NULL);
  clSetKernelArg(prop.kernel, 0, sizeof(cl_mem), &cl_cls_arg.k);
  clSetKernelArg(prop.kernel, 1, sizeof(cl_mem), &cl_cls_arg.img_info);
  clSetKernelArg(prop.kernel, 2, sizeof(cl_mem), &cl_cls_arg.cls_center);
  clSetKernelArg(prop.kernel, 3, sizeof(cl_mem), &cl_cls_arg.dist);
  clSetKernelArg(prop.kernel, 4, sizeof(cl_mem), &cl_cls_arg.data);

  /* 次元数指定 */
  global_size[0] = read_img.width;
  global_size[1] = read_img.height;
  /* ++++ OpenCL ++++ */

  /* 終了条件を回数でなく, クラスタの更新停止も追加(ゆくゆくは) */
  int count = 0;
  do {
    status = clEnqueueWriteBuffer(prop.queue, cl_cls_arg.cls_center,
        CL_TRUE, 0, sizeof(p_cluster) * K, (const void *)cls_k2, 0, NULL, NULL);

    status = clEnqueueWriteBuffer(prop.queue, cl_cls_arg.dist, CL_TRUE,
        0, sizeof(ushort) * img_size, (const void *)k2, 0, NULL, NULL);
    
    clEnqueueNDRangeKernel(prop.queue, prop.kernel, 2,
        NULL, global_size, NULL, 0, NULL, NULL);

    status = clEnqueueReadBuffer(prop.queue,
        cl_cls_arg.dist, CL_TRUE, 0, sizeof(ushort) * img_size,
        (void *)k2, 0, NULL, NULL);
    
    for(k = 0; k < K; k++) // 中心値の再計算
      calc_cluster_center(k, read_img, (const ushort *)k2, &cls_k2[k]);

  } while(++count != MAX_RANGE);
  cluster_print(K, cls_k2);

  char image_path[1024];
  for(k = 0; k < K; k++) {
    sprintf(image_path, "k_output/k%03d.png", k);
    pnwrite_from_dist(image_path, read_img.width, read_img.height, k,
        k2, read_img.data);

  }
#if 1
  sprintf(image_path, "cluster_k_%02d.png", K);
  pnwrite_from_cluster(image_path, read_img.width, read_img.height,
      cls_k2, k2);
#endif

  clReleaseMemObject(cl_cls_arg.k);
  clReleaseMemObject(cl_cls_arg.img_info);
  clReleaseMemObject(cl_cls_arg.cls_center);
  clReleaseMemObject(cl_cls_arg.dist);
  clReleaseMemObject(cl_cls_arg.data);
  release_dist(read_img.width, read_img.height, k2);
}

void set_image_info(img _img, img_info *info) {
  info->width  = _img.width;
  info->height = _img.height;
  info->colors = _img.colors;
}
