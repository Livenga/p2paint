#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/opencl.h"
#include "../../include/graphic.h"
#include "../../include/genetic.h"
#include "../../include/canvas.h"

/* Canvas領域の割当 */
canvas cvalloc(int width,
    int height,
    int colors) {
  int i;
  canvas cv;

  cv.width  = width;
  cv.height = height;
  cv.colors = colors;

  cv.data = (uchar *)calloc(
      width * height * colors,
      sizeof(uchar));
  memset((void *)cv.data, 0xFF,
      width * height * colors * sizeof(uchar));
  return cv;
}
