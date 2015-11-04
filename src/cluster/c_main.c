#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>

#include "../../include/graphic.h"
#include "../../include/opencl.h"
#include "../../include/cluster.h"

#define K 5
//#define K 10
#define MAX_RANGE 200

void set_image_info(img _img, img_info *info);

void run_k_means(cl_prop prop, img read_img) {
  const size_t img_size = read_img.width * read_img.height;
  int num_k, k;

  cl_int status;
  img_info info;           // 画像情報
  cluster_args cl_cls_arg; // Kernel引数
  size_t global_size[2];

  ushort *k2;          // 分類
  p_cluster cls_k2[K]; // クラスタ

  set_image_info(read_img, &info);
  k2 = dist_alloc(read_img.width, read_img.height);

  do {
    init_dist(K, read_img.width, read_img.height, k2);
    for(k = 0; k < K; k++)
      calc_cluster_center(k, read_img, (const ushort *)k2, &cls_k2[k]);
  } while(conf_cluster_center(K, cls_k2) == 0);

  num_k = K;
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

  global_size[0] = read_img.width;
  global_size[1] = read_img.height;
  clSetKernelArg(prop.kernel, 0, sizeof(cl_mem), &cl_cls_arg.k);
  clSetKernelArg(prop.kernel, 1, sizeof(cl_mem), &cl_cls_arg.img_info);
  clSetKernelArg(prop.kernel, 2, sizeof(cl_mem), &cl_cls_arg.cls_center);
  clSetKernelArg(prop.kernel, 3, sizeof(cl_mem), &cl_cls_arg.dist);
  clSetKernelArg(prop.kernel, 4, sizeof(cl_mem), &cl_cls_arg.data);

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
    
    for(k = 0; k < K; k++)
      calc_cluster_center(k, read_img, (const ushort *)k2, &cls_k2[k]);
    //cluster_print(K, cls_k2);
  } while(++count != MAX_RANGE);
  cluster_print(K, cls_k2);
  //class_print(read_img.width, read_img.height, k2);

  char image_path[1024];
  for(k = 0; k < K; k++) {
    sprintf(image_path, "k_output/k%03d.png", k);
    pnwrite_from_dist(image_path, read_img.width, read_img.height, k,
        k2, read_img.data);
  }

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
