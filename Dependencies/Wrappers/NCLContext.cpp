#include "NCLContext.h"

NCLContext::NCLContext()
{
	context = 0;
	incomplete = false;
	active = false;
}
int NCLContext::CreateContext(const cl_context_properties* properties, cl_uint num_devices, const cl_device_id* devices, void (__stdcall pfn_notify)(const char* errinfo, const void* private_info, size_t cb, void* user_data), void* user_data)
{
	cl_int Error = 0;
	if (active == true)
	{
		Error = clReleaseContext(context);
		if (CLerr(Error) == false)
		{
			printf("Failure to release context. \n: "  "%d\n", __LINE__);
			incomplete = true;
			return 0;
		}
		printf("Released context prematurely. Need to reallocat other objects connected to context.\n");
		active = false;
	}
	context = clCreateContext(properties, num_devices, devices, pfn_notify, user_data, &Error);
	if (CLerr(Error) == false)
	{
		printf("Failure to create context. \n "  " %d\n", __LINE__);
		incomplete = true;
		active = false;
		return 0;
	}
	active = true;
	return 1;

}

bool NCLContext::Completeness()
{
	bool Flip = !incomplete;
	return Flip;
}

bool NCLContext::ReleaseContext()
{
	cl_uint referenceCount = 0;
	cl_int error = clGetContextInfo(context, CL_CONTEXT_REFERENCE_COUNT, sizeof(cl_uint), &referenceCount, NULL);
	if (CLerr(error) == false)
	{
		//something is wrong.
	}
	else if (referenceCount == 0)
	{
		//already released
	}
	else
	{
		error = clReleaseContext(context);
		return CLerr(error);
	}
}

int NCLContext::RetainContext()
{
	
	cl_int Error = 0;
	Error = clRetainContext(context);
	if (Error == -1) {
		printf("Unable to retain devices: \n: "  " %d\n", __LINE__); incomplete = true; if (CLerr(Error) == false) { return 0; }
	}
}
cl_context NCLContext::ReturnContext()
{
	return context;
}

NCLContext::~NCLContext()
{
	clReleaseContext(context);
}

