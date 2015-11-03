#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>

#include "../../include/common.h"
#include "../../include/opencl.h"

cl_int set_kernels(const int did,
    cl_prop *prop) {
  cl_int status;

  prop->context = clCreateContext(0,
      prop->num_devices,
      (const cl_device_id *)prop->devices,
      NULL, NULL, &status);

  prop->queue = clCreateCommandQueueWithProperties(
      prop->context, prop->devices[did], 0, &status);

  prop->program = clCreateProgramWithSource(
      prop->context, prop->code.count,
      (const char **)prop->code.codes,
      NULL, &status);

  const char *options = NULL;
  status = clBuildProgram(prop->program, prop->num_devices,
      (const cl_device_id *)prop->devices,
      options, NULL, NULL);

  if(status != CL_SUCCESS)
    printf("%s[Build Error Log]%s\n",
        ERR_STR, CLR_STR);
  else
    printf("%s[Build Log]%s\n",
        WHT_STR, CLR_STR);

  size_t value_size;
  char *value;
  clGetProgramBuildInfo(prop->program, prop->devices[did],
      CL_PROGRAM_BUILD_LOG, 0, NULL, &value_size);
  value = (char *)calloc(value_size, sizeof(char));
  clGetProgramBuildInfo(prop->program, prop->devices[did],
      CL_PROGRAM_BUILD_LOG, value_size, (void *)value, NULL);
  printf("%s\n", value);
  free(value);
  if(status != CL_SUCCESS) getchar();

  prop->kernel = clCreateKernel(prop->program,
      (const char *)"cluster", &status);

  return status;
}
