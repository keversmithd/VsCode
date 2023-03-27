#ifndef NCLDEB
#define NCLDEB

#include <CL/cl.h>
#include "CL/cl_gl.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>
char* CLParser(const char* src);
bool CLerr(cl_int err);
bool IsCLExtensionSupported(const char* extension, cl_device_id Device);



#endif
