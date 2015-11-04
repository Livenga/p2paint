#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/graphic.h"
#include "../include/opencl.h"

extern void
run_k_means(cl_prop prop,
            img read_img);

int main(int argc, char *argv[])
{
  const int pid = 1, did = 0;
  cl_prop prop;
  img read_img;

  srand((unsigned)time(NULL));
  /* 画像ファイル(PNG)の読み込み */
  pnread("imgs/img02.png", &read_img);
  //save_csv("img00.csv", read_img);

  /* Kernelコードの読み込み */
  get_kernel_paths("src/kernel", &prop.code);
  read_kernel_code(&prop.code);

  /* OpenCLプロパティ設定 */
  numof_platforms(&prop);
  get_platforms(&prop);
  numof_devices(pid, &prop);
  get_devices(pid, &prop);
  set_kernels(did, &prop);

  run_k_means(prop, read_img);

  /* OpenCLプロパティの解放 */
  release_cl_properties(&prop);
  release_img(&read_img);
  return 0;
}
