#include <stdio.h>
#include "../../include/graphic.h"

int save_csv(const char *path,
    img _img) {
  int i, j;
  FILE *csv_fp;

  if((csv_fp = fopen(path, "w")) == NULL) {
    perror(path);
    return EOF;
  }

  for(i = 0; i < _img.height; i++) {
    for(j = 0; j < _img.width; j++) {
      fprintf(csv_fp, "%d\t%d\t%d\n",
          _img.data[i][j * 3 + 0],
          _img.data[i][j * 3 + 1],
          _img.data[i][j * 3 + 2]);
    }
  }
  fclose(csv_fp);
  return 0;
}
