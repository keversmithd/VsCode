#include "NCLDevice.h"

NCLDevice::NCLDevice()
{
	device = 0;
	devices = nullptr;
	incomplete = false;
	num_devices = 0;
}
int NCLDevice::GetDevices(cl_platform_id platform, cl_device_type devicetype)
{
	
	cl_int Error = 0;
	Error = clGetDeviceIDs(platform, devicetype, NULL, NULL, &num_devices);
	if (Error == -1) {
		printf("Unable to get device count: \n: " __FUNCTION__ "%d\n", __LINE__); incomplete = true; if (CLerr(Error) == false) { return 0; }
	}
	if (devices != nullptr)
	{
		free(devices);
		devices = nullptr;
	}
	devices = (cl_device_id*)malloc(num_devices * sizeof(cl_device_id));
	if (devices == nullptr)
	{
		return 0;
	}
	Error = clGetDeviceIDs(platform, devicetype, num_devices, devices, NULL);
	if (Error == -1) {
		printf("Unable to get devices: \n: " __FUNCTION__ "%d\n", __LINE__); incomplete = true; if (CLerr(Error) == false) { return 0; }
	}

	return 1;
}
cl_device_id* NCLDevice::get_devices()
{
	return devices;
}

int NCLDevice::get_num_devices()
{
	return num_devices;
}

int NCLDevice::GetDeviceInfo(unsigned int index, cl_device_info param_name, size_t param_value_size, void* param_value, size_t *param_value_size_ret)
{
	if (devices != nullptr)
	{
		if (devices[index] != NULL)
		{
			cl_int Error = 0;
			Error = clGetDeviceInfo(devices[index], param_name, param_value_size, param_value, param_value_size_ret);
			if (Error == -1) {
				printf("Unable to get device info: \n: " __FUNCTION__ "%d\n", __LINE__); incomplete = true; if (CLerr(Error) == false) { return 0; }
			}

			return 1;
		}
	}
	return 0;
}
int NCLDevice::SelectDefaultDevice(cl_uint deviceindex)
{
	if (deviceindex > (num_devices - 1))
	{
		printf("Device index out of bounds, incomplete: \n: " __FUNCTION__ "%d\n", __LINE__);
		incomplete = true;
		return 0;
	}

	if (devices == nullptr)
	{
		printf("Devices are null: \n: " __FUNCTION__ "%d\n", __LINE__);
		incomplete = true;
		return 0;
	}

	if (devices[deviceindex] == nullptr)
	{
		printf("Device at index is null: \n: " __FUNCTION__ "%d\n", __LINE__);
		incomplete = true;
		return 0;
	}

	device = devices[deviceindex];
	return 1;
}


int NCLDevice::FreeDevices()
{
	if (devices != nullptr)
	{
		free(devices);
		devices = nullptr;
	}
	
	return 1;
}
cl_device_id NCLDevice::ReturnDevice()
{
	
	return device;
}
int NCLDevice::RetainDevice()
{
	cl_int Error = 0;
	//Error = clRetainDevice(device);
	if (Error == -1) {
		printf("Unable to retain devices: \n: " __FUNCTION__ "%d\n", __LINE__); incomplete = true; if (CLerr(Error) == false) { return 0; }
	}
	return 1;
}
cl_device_id NCLDevice::ArrayReturnDevice(cl_uint deviceindex)
{
	if (deviceindex > (num_devices - 1))
	{
		printf("Device index out of bounds, incomplete: \n: " __FUNCTION__ "%d\n", __LINE__);
		incomplete = true;
		return 0;
	}

	if (devices == nullptr)
	{
		printf("Devices are null: \n: " __FUNCTION__ "%d\n", __LINE__);
		incomplete = true;
		return 0;
	}

	if (devices[deviceindex] == nullptr)
	{
		printf("Device at index is null: \n: " __FUNCTION__ "%d\n", __LINE__);
		incomplete = true;
		return 0;
	}

	return devices[deviceindex];
}
bool NCLDevice::CheckCompleteness()
{
	return !incomplete;
}

NCLDevice::~NCLDevice(){
	if (devices != nullptr)
	{
		free(devices);
	}

}