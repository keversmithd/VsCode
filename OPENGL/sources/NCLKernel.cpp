#include "NCLKernel.h"

NCLKernel::NCLKernel() 
{
	m_kernel = 0;
	incomplete = false;
	active = false;
}
int NCLKernel::CreateKernel(cl_program program, const char* kernel_name)
{
	if (active)
	{
		int ReleaseStatus = ReleaseKernel();
		if (!ReleaseStatus)
		{
			printf("Releasing kernel upon recreation failed and will have memory leak.\n");
			
		}
		else
		{
			printf("Released kernel up recreation.\n");
		}
		
	}

	cl_int Error = 0;

	m_kernel = clCreateKernel(program, kernel_name, &Error);

	if (Error == -1)
	{
		printf("Creating the kernel failed.: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; }
	}

	active = true;
	return 1;

}
int NCLKernel::GetKernelInfo(cl_kernel_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret)
{
	if (active)
	{
		cl_int Error = 0;
		Error = clGetKernelInfo(m_kernel, param_name, param_value_size, param_value, param_value_size_ret);

		if (Error == -1)
		{
			printf("Getting kernel info failed.: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; }
		}
		return 1;
	}

	return 0;
}
int NCLKernel::GetKernelArgInfo(cl_uint arg_indx, cl_kernel_arg_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret)
{

	if (active)
	{
		cl_int Error = 0;
		Error = clGetKernelArgInfo(m_kernel, arg_indx, param_name, param_value_size, param_value, param_value_size_ret);

		if (Error == -1)
		{
			printf("Getting kernel info failed.: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; }
		}
		return 1;
	}

	return 0;
}
int NCLKernel::GetKernelWorkGroupInfo(cl_device_id device, cl_kernel_work_group_info param_name, size_t param_value_size, void* param_value,size_t* param_value_size_ret)
{
	if (active)
	{
		cl_int Error = 0;
		Error = clGetKernelWorkGroupInfo(m_kernel, device, param_name, param_value_size, param_value, param_value_size_ret);

		if (Error == -1)
		{
			printf("Getting kernel info failed.: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; }
		}
		return 1;
	}

	return 0;
}
int NCLKernel::EnqueueNDRangeKernel(cl_command_queue command_queue,cl_uint work_dim, const size_t* global_work_offset, const size_t* global_work_size, const size_t* local_work_size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event)
{
	if (active)
	{
		cl_int Error = 0;
		Error = clEnqueueNDRangeKernel(command_queue, m_kernel, work_dim, global_work_offset, global_work_size, local_work_size, num_events_in_wait_list, event_wait_list, event);
		if (CLerr(Error) == false)
		{
			printf("Enqueuing kernel failed.: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; }
		}
		return 1;
	}

	return 0;
}
int NCLKernel::EnqueueNativeKernel(cl_command_queue command_queue, void (CL_CALLBACK* user_func)(void*), void* args, size_t cb_args, cl_uint num_mem_objects, const cl_mem* mem_list, const void** args_mem_loc, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event)
{
	if (active)
	{
		cl_int Error = 0;
		Error = clEnqueueNativeKernel(command_queue, user_func , args, cb_args, num_mem_objects, mem_list, args_mem_loc, num_events_in_wait_list, event_wait_list, event);
		if (Error == -1)
		{
			printf("Enqueuing kernel failed.: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; }
		}
		return 1;
	}

	return 0;
}
int NCLKernel::ReleaseKernel()
{
	if (active)
	{
		cl_int Error = 0;
		Error = clReleaseKernel(m_kernel);
		if (Error == -1)
		{
			printf("Releasing kernel info failed.: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; }
		}
		return 1;
	}
	return 1;
}
int NCLKernel::RetainKernel()
{
	if (active)
	{
		cl_int Error = 0;
		Error = clRetainKernel(m_kernel);
		if (Error == -1)
		{
			printf("Retaining kernel info failed.: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; }
		}
		return 1;
	}
	return 0;
}
int NCLKernel::SetKernelArg(cl_uint arg_index, size_t arg_size, const void* arg_value)
{
	if (active)
	{
		cl_int Error = 0;
		Error = clSetKernelArg(m_kernel, arg_index, arg_size, arg_value);
		if (Error == -1)
		{
			printf("Setting kernel arg failed.: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; }
		}
		return 1;
	}
	return 0;
}
bool NCLKernel::Completeness()
{
	bool Flip = !incomplete;
	return Flip;
}
NCLKernel::~NCLKernel()
{
	ReleaseKernel();
}