#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>

#include "../../include/graphic.h"
#include "../../include/opencl.h"
#include "../../include/cluster.h"

void set_image_info(img _img, img_info *info);

void do_cl(cl_prop prop, img read_img) {
  const size_t img_size = read_img.width * read_img.height;
  int num_k, k;

  cl_int status;
  img_info info;           // 画像情報
  cluster_args cl_cls_arg; // Kernel引数
  size_t global_size[2];

  ushort *k2;          // 分類
  p_cluster cls_k2[2]; // クラスタ

  global_size[0] = read_img.width;
  global_size[1] = read_img.height;
  set_image_info(read_img, &info);
  k2 = init_dist(2, read_img.width, read_img.height);

  num_k = 2;
  cl_cls_arg.k = clCreateBuffer(prop.context,
      CL_READ_COPY, sizeof(int), (void *)&num_k, &status);
  cl_cls_arg.img_info = clCreateBuffer(prop.context,
      CL_READ_COPY, sizeof(img_info), (void *)&info, NULL);
  cl_cls_arg.dist = clCreateBuffer(prop.context,
      CL_READ_COPY, sizeof(ushort) * img_size, (void *)k2, &status);
  cl_cls_arg.data = clCreateBuffer(prop.context,
      CL_READ_COPY, sizeof(uchar) * img_size, (void *)read_img.data, NULL);

  clSetKernelArg(prop.kernel, 0, sizeof(cl_mem), &cl_cls_arg.k);
  clSetKernelArg(prop.kernel, 1, sizeof(cl_mem), &cl_cls_arg.img_info);
  clSetKernelArg(prop.kernel, 2, sizeof(cl_mem), &cl_cls_arg.dist);
  clSetKernelArg(prop.kernel, 3, sizeof(cl_mem), &cl_cls_arg.data);


  for(k = 0; k < 2; k++)
    calc_cluster(k, read_img, (const ushort *)k2, &cls_k2[k]);
  cluster_print(2, cls_k2);

  clEnqueueNDRangeKernel(prop.queue, prop.kernel, 2,
      NULL, global_size, NULL, 0, NULL, NULL);

  clReleaseMemObject(cl_cls_arg.k);
  clReleaseMemObject(cl_cls_arg.img_info);
  clReleaseMemObject(cl_cls_arg.dist);
  clReleaseMemObject(cl_cls_arg.data);
  release_dist(read_img.width, read_img.height, k2);
}

void set_image_info(img _img, img_info *info) {
  info->width  = _img.width;
  info->height = _img.height;
  info->colors = _img.colors;
}
