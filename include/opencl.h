#ifndef CL_PROPERTIES
#define CL_PROPERTIES

#ifndef __OPENCL_CL_H
#include <CL/cl.h>
#endif

typedef struct _kerenl_code {
  size_t count;
  unsigned char **paths;
  unsigned char **codes;
} kcode;

typedef struct _cl_prop {
  /* Kernel Code */
  kcode code;

  /* Platform */
  cl_uint num_platforms;
  cl_platform_id *platforms;

  /* Device */
  cl_uint num_devices;
  cl_device_id *devices;

  cl_context context;
  cl_command_queue queue;
  cl_program program;

  cl_kernel kernel;

} cl_prop;

/* src/cl/cl_plat_dev.c */
extern cl_int numof_platforms(cl_prop *prop);
extern cl_int get_platforms(cl_prop *prop);
extern cl_int numof_devices(const int pid,
    cl_prop *prop);
extern cl_int get_devices(const int pid,
    cl_prop *prop);

/* src/cl/cl_kernel.c */
extern cl_int set_kernels(const int did,
    cl_prop *prop);

/* src/cl/cl_code.c */
extern int get_kernel_paths(const char *path,
    kcode *code);
extern int read_kernel_code(kcode *code);

/* src/cl/cl_util.c */
extern void release_cl_properties(cl_prop *prop);
#endif
