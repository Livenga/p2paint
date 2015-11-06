#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/graphic.h"
#include "../include/opencl.h"
#include "../include/cluster.h"

/* src/cluster/c_main.c */
extern ushort *
run_k_means(const int K,
            cl_prop prop,
            img read_img);
/* src/genetic/gn_main.c */
extern void
run_genetic(cl_prop prop,
            const ushort **segment_data,
            img target,
            img paint);

int main(int argc, char *argv[])
{
  const int pid = 0, did = 0;
  cl_prop prop;
  img read_img, paint_img;

  /* 画像分割データ */
  ushort **segment_data;

  srand((unsigned)time(NULL));
  /* 画像ファイル(PNG)の読み込み */
  //pnread("imgs/img00.png", &read_img);
  pnread("imgs/img06.png", &read_img);
  //pnread("imgs/shout.png", &paint_img);
  pnread("imgs/img00.png", &paint_img);
  save_csv("img00.csv", read_img);

  /* Kernelコードの読み込み */
  get_kernel_paths("src/kernel", &prop.code);
  read_kernel_code(&prop.code);
  /* OpenCLプロパティ設定 */
  numof_platforms(&prop);
  get_platforms(&prop);
  numof_devices(pid, &prop);
  get_devices(pid, &prop);
  set_kernels(did, &prop);

  /* 画像分割データの取得 */
  int i;
  segment_data =
    (ushort **)calloc(10, sizeof(ushort *));
  for(i = 2; i < 11; i++)
    segment_data[i - 2] =
      run_k_means(i, prop, read_img);

  run_genetic(prop, (const ushort **)segment_data,
      read_img, paint_img);

  /* OpenCLプロパティの解放 */
  release_cl_properties(&prop);
  release_img(&read_img);
  release_img(&paint_img);

  /* 分割データ解放 */
  for(i = 2; i < 11; i++)
    release_dist(
        read_img.width,
        read_img.height,
        segment_data[i - 2]);

  return 0;
}
