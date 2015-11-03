#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

#include "../../include/opencl.h"

int get_kernel_paths(const char *path,
    kcode *code) {
  int count;
  char *p;
  DIR *kernel_dir;
  struct dirent *kernel_stat;

  /* Cファイル数カウント */
  kernel_dir = opendir(path);
  if(kernel_dir == NULL) {
    perror(path);
    return EOF;
  }
  count = 0;
  while((kernel_stat = readdir(kernel_dir)) != NULL) {
    p = strstr(kernel_stat->d_name, ".c"); // 拡張子が ".c " のみを認識
    if(p != NULL)
      ++count;
  }
  closedir(kernel_dir);
  kernel_dir = NULL;
  if(count == 0) return EOF;

  /* パスの取得 */
  long kernel_len, full_len;
  code->count = count;

  kernel_dir = opendir(path);
  if(kernel_dir == NULL) {
    perror(path);
    return EOF;
  }

  count = 0;
  code->paths = (unsigned char **)calloc(
      count, sizeof(unsigned char *));

  kernel_len = strlen(path);
  while((kernel_stat = readdir(kernel_dir)) != NULL) {
    p = strstr(kernel_stat->d_name, ".c");
    if(p != NULL) {
      full_len = kernel_len + 1 +
        strlen(kernel_stat->d_name);
      code->paths[count] = (unsigned char *)calloc(
          full_len, sizeof(unsigned char));
      sprintf((char *)code->paths[count], "%s/%s",
          path, kernel_stat->d_name);
      ++count;
    }
  }
  closedir(kernel_dir);
  kernel_dir = NULL;

  return 0;
}

int read_kernel_code(kcode *code) {
  int i;
  FILE *kernel_fp;
  long kernel_len;

  code->codes = (unsigned char **)calloc(
      code->count, sizeof(unsigned char *));
  for(i = 0; i < code->count; i++) {
    kernel_fp = fopen((char *)code->paths[i], "r");
    if(kernel_fp == NULL) {
      perror((char *)code->paths[i]);
      return EOF;
    }
    fseek(kernel_fp, 0L, SEEK_END);
    kernel_len = ftell(kernel_fp);
    fseek(kernel_fp, 0L, SEEK_SET);

    code->codes[i] = (unsigned char *)calloc(
        kernel_len, sizeof(unsigned char));
    fread((void *)code->codes[i], sizeof(unsigned char),
        kernel_len, kernel_fp);

    fclose(kernel_fp);
  }

  return 0;
}
