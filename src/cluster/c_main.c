#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>

#include "../../include/graphic.h"
#include "../../include/opencl.h"
#include "../../include/cluster.h"

void do_cl(cl_prop prop, img read_img) {
  img_info info;
  cluster_args cl_cls_arg;

  info.width  = read_img.width;
  info.height = read_img.height;
  info.colors = read_img.colors;

  cl_cls_arg.img_info = clCreateBuffer(prop.context,
      CL_READ_COPY, sizeof(img_info), (void *)&info, NULL);
  clSetKernelArg(prop.kernel, 0, sizeof(cl_mem), &cl_cls_arg.img_info);

  size_t global_size[2];
  global_size[0] = read_img.width;
  global_size[1] = read_img.height;

  clEnqueueNDRangeKernel(prop.queue, prop.kernel, 2,
      NULL, global_size, NULL, 0, NULL, NULL);

  printf("%dx%d\n", read_img.width, read_img.height);

  clReleaseMemObject(cl_cls_arg.img_info);
}
