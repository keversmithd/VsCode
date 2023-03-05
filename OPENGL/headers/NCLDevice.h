#ifndef NCDEV
#define NCDEV

#include <CL/cl.h>
#include <memory>
#include "NCLDebug.h"

//made to be wrapped around by more advanced selector.

struct NCLDevice
{
protected:
	cl_device_id device;

	cl_device_id* devices;
	cl_uint num_devices;

	bool incomplete;
public:
	NCLDevice();
	int GetDevices(cl_platform_id platform, cl_device_type devicetype);
	int GetDeviceInfo(unsigned int index, cl_device_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
	int SelectDefaultDevice(cl_uint deviceindex);
	int FreeDevices();
	cl_device_id ArrayReturnDevice(cl_uint deviceindex);
	cl_device_id ReturnDevice();

	int RetainDevice();
	bool CheckCompleteness();
	~NCLDevice();
};


#endif
