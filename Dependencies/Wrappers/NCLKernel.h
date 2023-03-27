#ifndef __FUNCTION__ 
 #define __FUNCTION__ 
 #endif
#ifndef NCLKERNEL
#define NCLKENREL

#include "NCLDebug.h"

struct NCLKernel
{
private:
	cl_kernel m_kernel;
	bool incomplete;
	bool active;
public:
	NCLKernel();
	int CreateKernel(cl_program program, const char* kernel_name);
	int GetKernelInfo(cl_kernel_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
	int GetKernelArgInfo(cl_uint arg_indx, cl_kernel_arg_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
	int GetKernelWorkGroupInfo(cl_device_id device, cl_kernel_work_group_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
	int EnqueueNDRangeKernel(cl_command_queue command_queue, cl_uint work_dim, const size_t* global_work_offset, const size_t* global_work_size, const size_t* local_work_size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	int EnqueueNativeKernel(cl_command_queue command_queue, void (CL_CALLBACK* user_func)(void*), void* args, size_t cb_args, cl_uint num_mem_objects, const cl_mem* mem_list, const void** args_mem_loc, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	int ReleaseKernel();
	int RetainKernel();
	int SetKernelArg(cl_uint arg_index, size_t arg_size, const void* arg_value);
	bool Completeness();
	~NCLKernel();

};

#endif
