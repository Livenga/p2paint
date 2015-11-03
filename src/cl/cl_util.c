#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CL/cl.h>

#include "../../include/opencl.h"

void release_kernel_code(kcode *code) {
  int i;

  for(i = 0; i < code->count; i++) {
    free(code->paths[i]); code->paths[i] = NULL;
    free(code->codes[i]); code->codes[i] = NULL;
  }
  free(code->paths); code->paths = NULL;
  free(code->codes); code->codes = NULL;
}

void release_cl_properties(cl_prop *prop) {
  clReleaseKernel(prop->kernel);
  clReleaseProgram(prop->program);
  clReleaseCommandQueue(prop->queue);
  clReleaseContext(prop->context);

  free(prop->platforms); prop->platforms = NULL;
  free(prop->devices);   prop->devices   = NULL;

  release_kernel_code(&prop->code);
}
