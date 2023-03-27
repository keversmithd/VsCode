#ifndef __FUNCTION__ 
 #define __FUNCTION__ 
 #endif
#ifndef NCLCON
#define NCLCON
#include <CL/cl.h>
#include <stdio.h>
#include "NCLDebug.h"
#include <memory>
struct NCLContext
{
private:
	cl_context context;
	bool incomplete;
	bool active;
public:
	NCLContext();
	int CreateContext(const cl_context_properties* properties, cl_uint num_devices, const cl_device_id* devices, void(__stdcall pfn_notify)(const char* errinfo, const void* private_info, size_t cb, void* user_data), void* user_data);
	int RetainContext();
	cl_context ReturnContext();
	bool ReleaseContext();
	bool Completeness();
	~NCLContext();
};


#endif