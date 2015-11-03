#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>

#include "../../include/opencl.h"

cl_int numof_platforms(cl_prop *prop) {
  return clGetPlatformIDs(0, NULL, &prop->num_platforms);
}

cl_int get_platforms(cl_prop *prop) {
  prop->platforms = (cl_platform_id *)calloc(
      prop->num_platforms, sizeof(cl_platform_id));

  return clGetPlatformIDs(prop->num_platforms, prop->platforms, NULL);
}

cl_int numof_devices(const int pid,
    cl_prop *prop) {
  return clGetDeviceIDs(prop->platforms[pid],
      CL_DEVICE_TYPE_ALL,
      0,
      NULL,
      &prop->num_devices);
}

cl_int get_devices(const int pid,
    cl_prop *prop) {
  prop->devices = (cl_device_id *)calloc(
      prop->num_devices, sizeof(cl_device_id));

  return clGetDeviceIDs(prop->platforms[pid],
      CL_DEVICE_TYPE_ALL,
      prop->num_devices,
      prop->devices,
      NULL);
}
