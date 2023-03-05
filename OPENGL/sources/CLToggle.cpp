#include "CLToggle.h"
NCLDeviceToggle::NCLDeviceToggle()
{
	if (!(toggle)) {}
	else { device = 0; devices = nullptr; incomplete = false; num_devices = 0; }
}
int NCLDeviceToggle::GetDevices(cl_platform_id platform, cl_device_type devicetype)
{
	if (!(toggle)) { return 0; } cl_int Error = 0; Error = clGetDeviceIDs(platform, devicetype, NULL, NULL, &num_devices); if (Error == -1) { printf("Unable to get device count: \n: " __FUNCTION__ "%d\n", __LINE__); incomplete = true; if (CLerr(Error) == false) { return 0; } }if (devices != nullptr) { free(devices); }devices = (cl_device_id*)malloc(num_devices * sizeof(cl_device_id)); if (devices == nullptr) { return 0; }Error = clGetDeviceIDs(platform, devicetype, num_devices, devices, NULL); if (Error == -1) { printf("Unable to get devices: \n: " __FUNCTION__ "%d\n", __LINE__); incomplete = true; if (CLerr(Error) == false) { return 0; } }return 1;
}
int NCLDeviceToggle::GetDeviceInfo(unsigned int index, cl_device_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret)
{
	if (!(toggle)) { return 0; } if (devices != nullptr) { if (devices[index] != NULL) { cl_int Error = 0; Error = clGetDeviceInfo(devices[index], param_name, param_value_size, param_value, param_value_size_ret); if (Error == -1) { printf("Unable to get device info: \n: " __FUNCTION__ "%d\n", __LINE__); incomplete = true; if (CLerr(Error) == false) { return 0; } }return 1; } }return 0;
}
int NCLDeviceToggle::SelectDefaultDevice(cl_uint deviceindex)
{
	if (!(toggle)) { return 0; } if (deviceindex > (num_devices - 1)) { printf("Device index out of bounds, incomplete: \n: " __FUNCTION__ "%d\n", __LINE__); incomplete = true; return 0; }if (devices == nullptr) { printf("Devices are null: \n: " __FUNCTION__ "%d\n", __LINE__); incomplete = true; return 0; }if (devices[deviceindex] == nullptr) { printf("Device at index is null: \n: " __FUNCTION__ "%d\n", __LINE__); incomplete = true; return 0; }device = devices[deviceindex]; return 1;
}
int NCLDeviceToggle::FreeDevices()
{
	if (!(toggle)) { return 0; } if (devices != nullptr) { free(devices); }return 1;
}
cl_device_id NCLDeviceToggle::ReturnDevice()
{
	if (!(toggle)) { return 0; } return device;
}
int NCLDeviceToggle::RetainDevice()
{
	if (!(toggle)) { return 0; } cl_int Error = 0;//Error = clRetainDevice(device);if (Error == -1) {printf("Unable to retain devices: \n: " __FUNCTION__ "%d\n", __LINE__); incomplete = true; if (CLerr(Error) == false) { return 0; }}return 1;}
}
	cl_device_id NCLDeviceToggle::ArrayReturnDevice(cl_uint deviceindex)
	{
		if (!(toggle)) { return 0; } if (deviceindex > (num_devices - 1)) { printf("Device index out of bounds, incomplete: \n: " __FUNCTION__ "%d\n", __LINE__); incomplete = true; return 0; }if (devices == nullptr) { printf("Devices are null: \n: " __FUNCTION__ "%d\n", __LINE__); incomplete = true; return 0; }if (devices[deviceindex] == nullptr) { printf("Device at index is null: \n: " __FUNCTION__ "%d\n", __LINE__); incomplete = true; return 0; }return devices[deviceindex];
	}
	bool NCLDeviceToggle::CheckCompleteness()
	{
		if (!(toggle)) { return 0; } return !incomplete;
	}
	NCLDeviceToggle::~NCLDeviceToggle() { if (!(toggle)) {} else { if (devices != nullptr) { free(devices); } } }

		NCLEventToggle::NCLEventToggle()
		{
			if (!(toggle)) {}
			else { m_event = 0; active = false; }
		}
		int NCLEventToggle::CreateUserEvent(cl_context context)
		{
			if (!(toggle)) { return 0; } cl_int Error = 0; if (active) { int ReleaseStatus = ReleaseEvent(); if (!ReleaseStatus) { printf("Unable to release previous event object: Memory leak\n"); } else { printf("Released previous event object: Memory leak\n"); } }m_event = clCreateUserEvent(context, &Error); if (Error == -1) { printf("Creating the user event failed.: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; } }active = true; return 1;
		}
		int NCLEventToggle::GetEventInfo(cl_event_info param_name, size_t param_value_size, void* param_value, size_t * param_value_size_ret)
		{
			if (!(toggle)) { return 0; } if (active) { cl_int Error = 0; Error = clGetEventInfo(m_event, param_name, param_value_size, param_value, param_value_size_ret); if (Error == -1) { printf("Creating the event info failed.: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; } }return 1; }return 0;
		}
		int NCLEventToggle::ReleaseEvent()
		{
			if (!(toggle)) { return 0; } if (active) { cl_int Error = 0; Error = clReleaseEvent(m_event); if (Error == -1) { printf("Unalbe to release event.: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; } }active = false; return 1; }return 1;
		}
		int NCLEventToggle::RetainEvent()
		{
			if (!(toggle)) { return 0; } if (active) { cl_int Error = 0; Error = clRetainEvent(m_event); if (Error == -1) { printf("Retaining the event info failed.: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; } }return 1; }return 0;
		}
		int NCLEventToggle::SetEventCallback(cl_int command_exec_callback_type, void (CL_CALLBACK * pfn_notify)(cl_event event, cl_int event_command_status, void* user_data), void* user_data)
		{
			if (!(toggle)) { return 0; } if (active) { cl_int Error = 0; Error = clSetEventCallback(m_event, command_exec_callback_type, pfn_notify, user_data); if (Error == -1) { printf("Unable to set callback on event.: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; } }active = false; return 1; }return 1;
		}
		int NCLEventToggle::SetUserEventStatus(cl_int execution_status)
		{
			if (!(toggle)) { return 0; } if (active) { cl_int Error = 0; Error = clSetUserEventStatus(m_event, execution_status); if (Error == -1) { printf("Setting user event stauts failed.: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; } }active = false; return 1; }return 1;
		}
		NCLEventToggle::~NCLEventToggle()
		{
			if (!(toggle)) {}
			else { ReleaseEvent(); }
		}

		NCLImageToggle::NCLImageToggle()
		{
			if (!(toggle)) {}
			else { m_image = 0; incomplete = true; active = false; }
		}
		int NCLImageToggle::CreateImage(cl_context context, cl_mem_flags flags, const cl_image_format * image_format, const cl_image_desc * image_desc, void* host_ptr)
		{
			if (!(toggle)) { return 0; } cl_int Error = 0; if (active) { ReleaseImage(); printf("Image object released, be aware \n"); }m_image = clCreateImage(context, flags, image_format, image_desc, host_ptr, &Error); if (Error == -1) { printf("Unable to create image: \n: " __FUNCTION__ " %d\n", __LINE__); incomplete = true; if (CLerr(Error) == false) { return 0; } }incomplete = false; return 1;
		}
		int NCLImageToggle::ReleaseImage()
		{
			if (!(toggle)) { return 0; } cl_int Error = 0; if (active == true) { Error = clReleaseMemObject(m_image); if (Error == -1) { printf("Unable to release buffer devices: \n: " __FUNCTION__ " %d\n", __LINE__); incomplete = true; if (CLerr(Error) == false) { return 0; } } }active = false; return 1;
		}
		int NCLImageToggle::RetainImage()
		{
			if (!(toggle)) { return 0; } cl_int Error = 0; if (active) { Error = clRetainMemObject(m_image); if (Error == -1) { printf("Unable to retain image object: \n: " __FUNCTION__ " %d\n", __LINE__); incomplete = true; if (CLerr(Error) == false) { return 0; } } }return 0;
		}
		int NCLImageToggle::EnqueueReadImage(cl_command_queue command_queue, cl_bool blocking_read, const size_t * origin, const size_t * region, size_t row_pitch, size_t slice_pitch, void* ptr, cl_uint num_events_in_wait_list, const cl_event * event_wait_list, cl_event * event)
		{
			if (!(toggle)) { return 0; } cl_int Error = 0; if (active) { Error = clEnqueueReadImage(command_queue, m_image, blocking_read, origin, region, row_pitch, slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event); if (Error == -1) { printf("Unable to enqueue the read command: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; } }return 1; }return 0;
		}
		int NCLImageToggle::EnqueueWriteImage(cl_command_queue command_queue, cl_bool blocking_write, const size_t * origin, const size_t * region, size_t input_row_pitch, size_t input_slice_pitch, const void* ptr, cl_uint num_events_in_wait_list, const cl_event * event_wait_list, cl_event * event)
		{
			if (!(toggle)) { return 0; } cl_int Error = 0; if (active) { Error = clEnqueueWriteImage(command_queue, m_image, blocking_write, origin, region, input_row_pitch, input_slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event); if (Error == -1) { printf("Unable to enqueue the write command: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; } }return 1; }return 0;
		}
		int NCLImageToggle::EnqueueCopyImage(cl_command_queue command_queue, cl_mem dst_image, const size_t * src_origin, const size_t * dst_origin, const size_t * region, cl_uint num_events_in_wait_list, const cl_event * event_wait_list, cl_event * event)
		{
			if (!(toggle)) { return 0; } cl_int Error = 0; if (active) { Error = clEnqueueCopyImage(command_queue, m_image, dst_image, src_origin, dst_origin, region, num_events_in_wait_list, event_wait_list, event); if (Error == -1) { printf("Unable to enqueue the image: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; } }return 1; }return 0;
		}
		int NCLImageToggle::EnqueueCopyImageToBuffer(cl_command_queue command_queue, cl_mem dst_buffer, const size_t * src_origin, const size_t * region, size_t dst_offset, cl_uint num_events_in_wait_list, const cl_event * event_wait_list, cl_event * event)
		{
			if (!(toggle)) { return 0; } cl_int Error = 0; if (active) { Error = clEnqueueCopyImageToBuffer(command_queue, m_image, dst_buffer, src_origin, region, dst_offset, num_events_in_wait_list, event_wait_list, event); if (Error == -1) { printf("Unable to enqueue the image: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; } }return 1; }return 0;
		}
		int NCLImageToggle::EnqueueCopyBufferToImage(cl_command_queue command_queue, cl_mem src_buffer, cl_mem dst_image, size_t src_offset, const size_t * dst_origin, const size_t * region, cl_uint num_events_in_wait_list, const cl_event * event_wait_list, cl_event * event)
		{
			if (!(toggle)) { return 0; } cl_int Error = 0; if (active) { Error = clEnqueueCopyBufferToImage(command_queue, src_buffer, m_image, src_offset, dst_origin, region, num_events_in_wait_list, event_wait_list, event); if (Error == -1) { printf("Unable to enqueue the image: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; } }return 1; }return 0;
		}
		int NCLImageToggle::EnqueueFillImage(cl_command_queue command_queue, const void* fill_color, const size_t * origin, const size_t * region, cl_uint num_events_in_wait_list, const cl_event * event_wait_list, cl_event * event)
		{
			if (!(toggle)) { return 0; } cl_int Error = 0; if (active) { Error = clEnqueueFillImage(command_queue, m_image, fill_color, origin, region, num_events_in_wait_list, event_wait_list, event); if (Error == -1) { printf("Unable to enqueue the image: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; } }return 1; }return 0;
		}
		void* NCLImageToggle::EnqueueMapImage(cl_command_queue command_queue, cl_bool blocking_map, cl_map_flags map_flags, const size_t * origin, const size_t * region, size_t * image_row_pitch, size_t * image_slice_pitch, cl_uint num_events_in_wait_list, const cl_event * event_wait_list, cl_event * event)
		{
			if (!(toggle)) { return 0; } cl_int Error = 0; if (active) { void* map = clEnqueueMapImage(command_queue, m_image, blocking_map, map_flags, origin, region, image_row_pitch, image_slice_pitch, num_events_in_wait_list, event_wait_list, event, &Error); if (Error == -1) { printf("Unable to enqueue the image: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; } }return map; }return 0;
		}
		int NCLImageToggle::EnqueueUnmapBuffer(cl_command_queue command_queue, void* mapped_ptr, cl_uint num_events_in_wait_list, const cl_event * event_wait_list, cl_event * event)
		{
			if (!(toggle)) { return 0; } cl_int Error = 0; if (active) { Error = clEnqueueUnmapMemObject(command_queue, m_image, mapped_ptr, num_events_in_wait_list, event_wait_list, event); if (Error == -1) { printf("Enqueueing the buffer failed: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; } }return 1; }printf("Buffer is not active and should not be enqueued.: \n: " __FUNCTION__ " %d\n", __LINE__); return 0;
		}
		int NCLImageToggle::GetImageInfo(cl_image_info param_name, size_t param_value_size, void* param_value, size_t * param_value_size_ret)
		{
			if (!(toggle)) { return 0; } cl_int Error = 0; Error = clGetImageInfo(m_image, param_name, param_value_size, param_value, param_value_size_ret); if (Error == -1) { printf("Unable to get the image info: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; } }return 1;
		}
		bool NCLImageToggle::Completeness()
		{
			if (!(toggle)) { return 0; } bool Flip = !incomplete; return Flip;
		}
		cl_mem NCLImageToggle::ReturnImage()
		{
			if (!(toggle)) { return 0; } return m_image;
		}
		NCLImageToggle::~NCLImageToggle()
		{
			if (!(toggle)) {}
			else { ReleaseImage(); }
		}

		NCLKernelToggle::NCLKernelToggle()
		{
			if (!(toggle)) {}
			else { m_kernel = 0; incomplete = false; active = false; }
		}
		int NCLKernelToggle::CreateKernel(cl_program program, const char* kernel_name)
		{
			if (!(toggle)) { return 0; } if (active) { int ReleaseStatus = ReleaseKernel(); if (!ReleaseStatus) { printf("Releasing kernel upon recreation failed and will have memory leak.\n"); } else { printf("Released kernel up recreation.\n"); } }cl_int Error = 0; m_kernel = clCreateKernel(program, kernel_name, &Error); if (Error == -1) { printf("Creating the kernel failed.: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; } }active = true; return 1;
		}
		int NCLKernelToggle::GetKernelInfo(cl_kernel_info param_name, size_t param_value_size, void* param_value, size_t * param_value_size_ret)
		{
			if (!(toggle)) { return 0; } if (active) { cl_int Error = 0; Error = clGetKernelInfo(m_kernel, param_name, param_value_size, param_value, param_value_size_ret); if (Error == -1) { printf("Getting kernel info failed.: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; } }return 1; }return 0;
		}
		int NCLKernelToggle::GetKernelArgInfo(cl_uint arg_indx, cl_kernel_arg_info param_name, size_t param_value_size, void* param_value, size_t * param_value_size_ret)
		{
			if (!(toggle)) { return 0; } if (active) { cl_int Error = 0; Error = clGetKernelArgInfo(m_kernel, arg_indx, param_name, param_value_size, param_value, param_value_size_ret); if (Error == -1) { printf("Getting kernel info failed.: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; } }return 1; }return 0;
		}
		int NCLKernelToggle::GetKernelWorkGroupInfo(cl_device_id device, cl_kernel_work_group_info param_name, size_t param_value_size, void* param_value, size_t * param_value_size_ret)
		{
			if (!(toggle)) { return 0; } if (active) { cl_int Error = 0; Error = clGetKernelWorkGroupInfo(m_kernel, device, param_name, param_value_size, param_value, param_value_size_ret); if (Error == -1) { printf("Getting kernel info failed.: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; } }return 1; }return 0;
		}
		int NCLKernelToggle::EnqueueNDRangeKernel(cl_command_queue command_queue, cl_uint work_dim, const size_t * global_work_offset, const size_t * global_work_size, const size_t * local_work_size, cl_uint num_events_in_wait_list, const cl_event * event_wait_list, cl_event * event)
		{
			if (!(toggle)) { return 0; } if (active) { cl_int Error = 0; Error = clEnqueueNDRangeKernel(command_queue, m_kernel, work_dim, global_work_offset, global_work_size, local_work_size, num_events_in_wait_list, event_wait_list, event); if (CLerr(Error) == false) { printf("Enqueuing kernel failed.: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; } }return 1; }return 0;
		}
		int NCLKernelToggle::EnqueueNativeKernel(cl_command_queue command_queue, void (CL_CALLBACK * user_func)(void*), void* args, size_t cb_args, cl_uint num_mem_objects, const cl_mem * mem_list, const void** args_mem_loc, cl_uint num_events_in_wait_list, const cl_event * event_wait_list, cl_event * event)
		{
			if (!(toggle)) { return 0; } if (active) { cl_int Error = 0; Error = clEnqueueNativeKernel(command_queue, user_func, args, cb_args, num_mem_objects, mem_list, args_mem_loc, num_events_in_wait_list, event_wait_list, event); if (Error == -1) { printf("Enqueuing kernel failed.: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; } }return 1; }return 0;
		}
		int NCLKernelToggle::ReleaseKernel()
		{
			if (!(toggle)) { return 0; } if (active) { cl_int Error = 0; Error = clReleaseKernel(m_kernel); if (Error == -1) { printf("Releasing kernel info failed.: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; } }return 1; }return 1;
		}
		int NCLKernelToggle::RetainKernel()
		{
			if (!(toggle)) { return 0; } if (active) { cl_int Error = 0; Error = clRetainKernel(m_kernel); if (Error == -1) { printf("Retaining kernel info failed.: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; } }return 1; }return 0;
		}
		int NCLKernelToggle::SetKernelArg(cl_uint arg_index, size_t arg_size, const void* arg_value)
		{
			if (!(toggle)) { return 0; } if (active) { cl_int Error = 0; Error = clSetKernelArg(m_kernel, arg_index, arg_size, arg_value); if (Error == -1) { printf("Setting kernel arg failed.: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; } }return 1; }return 0;
		}
		bool NCLKernelToggle::Completeness()
		{
			if (!(toggle)) { return 0; } bool Flip = !incomplete; return Flip;
		}
		NCLKernelToggle::~NCLKernelToggle()
		{
			if (!(toggle)) {}
			else { ReleaseKernel(); }
		}

		NCLPlatformToggle::NCLPlatformToggle()
		{
			if (!(toggle)) {}
			else { platform = 0; platforms = nullptr; num_platforms = 0; incomplete = false; }
		}
		int NCLPlatformToggle::GetPlatforms()
		{
			if (!(toggle)) { return 0; } cl_int Error; Error = clGetPlatformIDs(NULL, NULL, &num_platforms); if (Error == -1) { printf("Unable to get platform count. : \n: " __FUNCTION__ "%d\n", __LINE__); incomplete = true; if (CLerr(Error) == false) { return 0; } }if (platforms != nullptr) { free(platforms); }platforms = (cl_platform_id*)malloc(num_platforms * sizeof(cl_platform_id)); if (platforms == nullptr) { printf("Platforms allocation failue. : \n: " __FUNCTION__ "%d\n", __LINE__); incomplete = true; return 0; }Error = clGetPlatformIDs(num_platforms, platforms, NULL); if (Error == -1) { printf("Unable to get platform ids. : \n: " __FUNCTION__ "%d\n", __LINE__); incomplete = true; if (CLerr(Error) == false) { return 0; } }return 1;
		}
		int NCLPlatformToggle::SelectDefaultPlatform(cl_uint platformindex)
		{
			if (!(toggle)) { return 0; } if (platformindex > (num_platforms - 1)) { printf("Platform index out of bounds, incomplete: \n: " __FUNCTION__ "%d\n", __LINE__); incomplete = true; return 0; }if (platforms == nullptr) { printf("platforms are null: \n: " __FUNCTION__ "%d\n", __LINE__); incomplete = true; return 0; }if (platforms[platformindex] == nullptr) { printf("Platform at index is null: \n: " __FUNCTION__ "%d\n", __LINE__); incomplete = true; return 0; }platform = platforms[platformindex]; return 1;
		}
		int NCLPlatformToggle::FreePlatforms()
		{
			if (!(toggle)) { return 0; } if (platforms != nullptr) { free(platforms); }return 1;
		}
		cl_platform_id NCLPlatformToggle::ReturnPlatform()
		{
			if (!(toggle)) { return 0; } return platform;
		}
		cl_platform_id& NCLPlatformToggle::ReferencePlatform()
		{
			return platform;
		}
		cl_platform_id NCLPlatformToggle::ArrayReturnPlatform(cl_uint platformindex)
		{
			if (!(toggle)) { return 0; } if (platformindex > (num_platforms - 1)) { printf("Platform index out of bounds, incomplete: \n: " __FUNCTION__ "%d\n", __LINE__); incomplete = true; return 0; }if (platforms == nullptr) { printf("Platforms are null: \n: " __FUNCTION__ "%d\n", __LINE__); incomplete = true; return 0; }if (platforms[platformindex] == nullptr) { printf("Platform at index is null: \n: " __FUNCTION__ "%d\n", __LINE__); incomplete = true; return 0; }return platforms[platformindex];
		}
		bool NCLPlatformToggle::Completeness()
		{
			if (!(toggle)) { return 0; } bool Flip = !incomplete; return Flip;
		}
		NCLPlatformToggle::~NCLPlatformToggle()
		{
			if (!(toggle)) {}
			else { if (platforms != nullptr) { free(platforms); } }
		}

		NCLProgramToggle::NCLProgramToggle()
		{
			if (!(toggle)) {}
			else { m_program = 0; incomplete = false; active = false; }
		}
		int NCLProgramToggle::CreateProgramWithSource(cl_context context, cl_uint count, const char** strings, const size_t * lengths)
		{
			if (!(toggle)) { return 0; } if (active) { int ReleaseStatus = ReleaseProgram(); if (ReleaseStatus) { printf("Program released because it was already active\n"); } }cl_int Error = 0; m_program = clCreateProgramWithSource(context, count, strings, lengths, &Error); if (Error == -1) { printf("Creating the program failed.: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; } }active = true; return 1;
		}
		int NCLProgramToggle::CreateProgramWithBinary(cl_context context, cl_uint num_devices, const cl_device_id * device_list, const size_t * lengths, const unsigned char** binaries, cl_int * binary_status)
		{
			if (!(toggle)) { return 0; } if (active) { int ReleaseStatus = ReleaseProgram(); if (ReleaseStatus) { printf("Program released because it was already active\n"); } }cl_int Error = 0; m_program = clCreateProgramWithBinary(context, num_devices, device_list, lengths, binaries, binary_status, &Error); if (Error == -1) { printf("Enqueueing the buffer failed: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; } }active = true; return 1;
		}
		int NCLProgramToggle::CompileProgram(cl_uint num_devices, const cl_device_id * device_list, const char* options, cl_uint num_input_headers, const cl_program * input_headers, const char** header_include_names, void (CL_CALLBACK * pfn_notify)(cl_program program, void* user_data), void* user_data)
		{
			if (!(toggle)) { return 0; } cl_int Error = 0; if (active) { Error = clCompileProgram(m_program, num_devices, device_list, options, num_input_headers, input_headers, header_include_names, pfn_notify, user_data); if (Error == -1) { printf("Compiling the program failed: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; } }return 1; }printf("Program is not an active program object\n"); return 0;
		}
		int NCLProgramToggle::LinkProgram(cl_context context, cl_uint num_devices, const cl_device_id * device_list, const char* options, cl_uint num_input_programs, const cl_program * input_programs, void (CL_CALLBACK * pfn_notify)(cl_program program, void* user_data), void* user_data)
		{
			if (!(toggle)) { return 0; } cl_int Error = 0; if (active) { m_program = clLinkProgram(context, num_devices, device_list, options, num_input_programs, input_programs, pfn_notify, user_data, &Error); if (Error == -1) { printf("Compiling the program failed: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; } }return 1; }printf("Program is not an active program object\n"); return 0;
		}
		int NCLProgramToggle::BuildProgram(cl_uint num_devices, const cl_device_id * device_list, const char* options, void (CL_CALLBACK * pfn_notify)(cl_program program, void* user_data), void* user_data)
		{
			if (!(toggle)) { return 0; } cl_int Error = 0; if (active) { Error = clBuildProgram(m_program, num_devices, device_list, options, pfn_notify, user_data); if (Error == -1) { printf("Enqueueing the buffer failed: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; } }return 1; }printf("Program is not an active program object\n"); return 0;
		}
		int NCLProgramToggle::GetProgramBuildInfo(cl_device_id device, cl_program_build_info param_name, size_t param_value_size, void* param_value, size_t * param_value_size_ret)
		{
			if (!(toggle)) { return 0; } cl_int Error = 0; if (active) { Error = clGetProgramBuildInfo(m_program, device, param_name, param_value_size, param_value, param_value_size_ret); if (Error == -1) { printf("Getting build info failed: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; } }return 1; }printf("Program is not an active program object\n"); return 0;
		}
		int NCLProgramToggle::GetProgramInfo(cl_program_info param_name, size_t param_value_size, void* param_value, size_t * param_value_size_ret)
		{
			if (!(toggle)) { return 0; } cl_int Error = 0; if (active) { Error = clGetProgramInfo(m_program, param_name, param_value_size, param_value, param_value_size_ret); if (Error == -1) { printf("Compiling the program failed: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; } }return 1; }printf("Program is not an active program object\n"); return 0;
		}
		int NCLProgramToggle::ReleaseProgram()
		{
			if (!(toggle)) { return 0; } cl_int Error = 0; if (active) { Error = clReleaseProgram(m_program); if (Error == -1) { printf("Releasing the program failed: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; } }active = false; return 1; }return 1;
		}
		int NCLProgramToggle::RetainProgram()
		{
			if (!(toggle)) { return 0; } cl_int Error = 0; if (active) { Error = clRetainProgram(m_program); if (Error == -1) { printf("Retaining the program failed: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; } }return 1; }return 0;
		}
		cl_program NCLProgramToggle::ReturnProgram()
		{
			if (!(toggle)) { return 0; } return m_program;
		}
		bool NCLProgramToggle::Completeness()
		{
			if (!(toggle)) { return 0; } bool Flip = !incomplete; return Flip;
		}
		NCLProgramToggle::~NCLProgramToggle()
		{
			if (!(toggle)) {}
			else { if (active) { ReleaseProgram(); } }
		}

		NCLSamplerToggle::NCLSamplerToggle()
		{
			if (!(toggle)) {}
			else { m_sampler = 0; incomplete = false; active = false; }
		}
		int NCLSamplerToggle::CreateSampler(cl_context context, cl_bool normalized_coords, cl_addressing_mode addressing_mode, cl_filter_mode filter_mode)
		{
			if (!(toggle)) { return 0; } if (active) { ReleaseSampler(); printf("Sampler was active and was released and recreated \n"); }cl_int Error = 0; m_sampler = clCreateSampler(context, normalized_coords, addressing_mode, filter_mode, &Error); if (Error == -1) { printf("Unable to create sampler object: \n: " __FUNCTION__ " %d\n", __LINE__); incomplete = true; if (CLerr(Error) == false) { return 0; } }active = true; return 1;
		}
		int NCLSamplerToggle::ReleaseSampler()
		{
			if (!(toggle)) { return 0; } if (active) { cl_int Error = 0; Error = clReleaseSampler(m_sampler); if (Error == -1) { printf("Unable to release sampler object: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; } }active = false; return 1; }return 0;
		}
		int NCLSamplerToggle::RetainSampler()
		{
			if (!(toggle)) { return 0; } if (active) { cl_int Error = 0; Error = clRetainSampler(m_sampler); if (Error == -1) { printf("Unable to retain sampler object: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; } }return 1; }return 0;
		}
		int NCLSamplerToggle::GetSamplerInfo(cl_sampler_info param_name, size_t param_value_size, void* param_value, size_t * param_value_size_ret)
		{
			if (!(toggle)) { return 0; } if (active) { cl_int Error = 0; Error = clGetSamplerInfo(m_sampler, param_name, param_value_size, param_value, param_value_size_ret); if (Error == -1) { printf("Unable to get sampler info: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; } }return 1; }return 0;
		}
		bool NCLSamplerToggle::Completeness()
		{
			if (!(toggle)) { return 0; } bool Flip = !incomplete; return Flip;
		}
		cl_sampler NCLSamplerToggle::ReturnSampler()
		{
			if (!(toggle)) { return 0; } return m_sampler;
		}
		NCLSamplerToggle::~NCLSamplerToggle()
		{
			if (!(toggle)) {}
			else { if (active) { ReleaseSampler(); } }
		}

		NCLBufferToggle::NCLBufferToggle()
		{
			if (!(toggle)) {}
			else { m_buffer = 0; incomplete = true; }
		}
		int NCLBufferToggle::CreateBuffer(cl_context context, cl_mem_flags flags, size_t size, void* host_ptr)
		{
			if (!(toggle)) { return 0; } cl_int Error = 0; if (active == true) { printf("Buffer active, releasing previous buffer.: \n: " __FUNCTION__ " %d\n", __LINE__); int ReleaseSuccess = ReleaseBuffer(); if (!ReleaseSuccess) { return 0; } }m_buffer = clCreateBuffer(context, flags, size, host_ptr, &Error); if (CLerr(Error) == 0){}//printf("Unable to create buffer: \n: " __FUNCTION__ " %d\n", __LINE__); incomplete = true; if (CLerr(Error) == false) { return 0; }return 0;}active = true;return 1;}
		}
				int NCLBufferToggle::CreateBufferFromGLBuffer(cl_context context, cl_mem_flags flags, cl_GLuint buffer)
				{
					if (!(toggle)) { return 0; } cl_int Error = 0; if (active == true) { printf("Buffer active, releasing previous buffer.: \n: " __FUNCTION__ " %d\n", __LINE__); int ReleaseSuccess = ReleaseBuffer(); if (!ReleaseSuccess) { return 0; } }m_buffer = clCreateFromGLBuffer(context, flags, buffer, &Error); if (!CLerr(Error)) { ReleaseBuffer(); return 0; }active = true; return 1;
				}
				cl_mem NCLBufferToggle::CreateSubBuffer(cl_mem_flags flags, cl_buffer_create_type buffer_create_type, const void* buffer_create_info)
				{
					if (!(toggle)) { return 0; } cl_int Error = 0; if (active) { cl_mem memory = clCreateSubBuffer(m_buffer, flags, buffer_create_type, buffer_create_info, &Error); if (Error == -1) { printf("Unable to subjucate buffer : \n: " __FUNCTION__ " %d\n", __LINE__); incomplete = true; if (CLerr(Error) == false) { return 0; } }return memory; }printf("Buffer is not active : \n: " __FUNCTION__ " %d\n", __LINE__); incomplete = true; return 0;
				}
				int NCLBufferToggle::ReleaseBuffer()
				{
					if (!(toggle)) { return 0; } cl_int Error = 0; if (active == true) { Error = clReleaseMemObject(m_buffer); if (Error == -1) { printf("Unable to release buffer devices: \n: " __FUNCTION__ " %d\n", __LINE__); incomplete = true; if (CLerr(Error) == false) { return 0; } }active = false; return 1; }active = false; return 1;
				}
				int NCLBufferToggle::RetainBuffer()
				{
					if (!(toggle)) { return 0; } cl_int Error = 0; if (active) { Error = clRetainMemObject(m_buffer); if (Error == -1) { printf("Unable to retain mem object: \n: " __FUNCTION__ " %d\n", __LINE__); incomplete = true; if (CLerr(Error) == false) { return 0; } } }return 0;
				}
				int NCLBufferToggle::EnqueueReadBuffer(cl_command_queue command_queue, cl_bool blocking_read, size_t offset, size_t size, void* ptr, cl_uint num_events_in_wait_list, const cl_event * event_wait_list, cl_event * p_event)
				{
					if (!(toggle)) { return 0; } cl_int Error = 0; if (active) { Error = clEnqueueReadBuffer(command_queue, m_buffer, blocking_read, offset, size, ptr, num_events_in_wait_list, event_wait_list, p_event); if (Error == -1) { printf("Enqueueing the buffer failed: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; } }return 1; }printf("Buffer is not active and should not be enqueued.: \n: " __FUNCTION__ " %d\n", __LINE__); return 0;
				}
				int NCLBufferToggle::EnqueueWriteBuffer(cl_command_queue command_queue, cl_bool blocking_write, size_t offset, size_t size, const void* ptr, cl_uint num_events_in_wait_list, const cl_event * event_wait_list, cl_event * p_event)
				{
					if (!(toggle)) { return 0; } cl_int Error = 0; if (active) { Error = clEnqueueWriteBuffer(command_queue, m_buffer, blocking_write, offset, size, ptr, num_events_in_wait_list, event_wait_list, p_event); if (Error == -1) { printf("Enqueueing the buffer failed: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; } }return 1; }printf("Buffer is not active and should not be enqueued.: \n: " __FUNCTION__ " %d\n", __LINE__); return 0;
				}
				int NCLBufferToggle::EnqueueReadBufferRect(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, const size_t * buffer_offset, const size_t * host_offset, const size_t * region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, void* ptr, cl_uint num_events_in_wait_list, const cl_event * event_wait_list, cl_event * event)
				{
					if (!(toggle)) { return 0; } cl_int Error = 0; if (active) { Error = clEnqueueReadBufferRect(command_queue, m_buffer, blocking_read, buffer_offset, host_offset, region, buffer_row_pitch, buffer_slice_pitch, host_row_pitch, host_slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event); if (Error == -1) { printf("Enqueueing the buffer failed: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; } }return 1; }printf("Buffer is not active and should not be enqueued.: \n: " __FUNCTION__ " %d\n", __LINE__); return 0;
				}
				int NCLBufferToggle::EnqueueWriteBufferRect(cl_command_queue command_queue, cl_bool blocking_write, const size_t * buffer_offset, const size_t * host_offset, const size_t * region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, const void* ptr, cl_uint num_events_in_wait_list, const cl_event * event_wait_list, cl_event * event)
				{
					if (!(toggle)) { return 0; } cl_int Error = 0; if (active) { Error = clEnqueueWriteBufferRect(command_queue, m_buffer, blocking_write, buffer_offset, host_offset, region, buffer_row_pitch, buffer_slice_pitch, host_row_pitch, host_slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event); if (Error == -1) { printf("Enqueueing the buffer failed: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; } }return 1; }printf("Buffer is not active and should not be enqueued.: \n: " __FUNCTION__ " %d\n", __LINE__); return 0;
				}
				int NCLBufferToggle::EnqueueCopyBuffer(cl_command_queue command_queue, cl_mem dst_buffer, size_t src_offset, size_t dst_offset, size_t size, cl_uint num_events_in_wait_list, const cl_event * event_wait_list, cl_event * event)
				{
					if (!(toggle)) { return 0; } cl_int Error = 0; if (active) { Error = clEnqueueCopyBuffer(command_queue, m_buffer, dst_buffer, src_offset, dst_offset, size, num_events_in_wait_list, event_wait_list, event); if (Error == -1) { printf("Enqueueing the buffer failed: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; } }return 1; }printf("Buffer is not active and should not be enqueued.: \n: " __FUNCTION__ " %d\n", __LINE__); return 0;
				}
				int NCLBufferToggle::EnqueueCopyBufferRect(cl_command_queue command_queue, cl_mem dst_buffer, const size_t * src_origin, const size_t * dst_origin, const size_t * region, size_t src_row_pitch, size_t src_slice_pitch, size_t dst_row_pitch, size_t dst_slice_pitch, cl_uint num_events_in_wait_list, const cl_event * event_wait_list, cl_event * event)
				{
					if (!(toggle)) { return 0; } cl_int Error = 0; if (active) { Error = clEnqueueCopyBufferRect(command_queue, m_buffer, dst_buffer, src_origin, dst_origin, region, src_row_pitch, src_slice_pitch, dst_row_pitch, dst_slice_pitch, num_events_in_wait_list, event_wait_list, event); if (Error == -1) { printf("Enqueueing the buffer failed: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; } }return 1; }printf("Buffer is not active and should not be enqueued.: \n: " __FUNCTION__ " %d\n", __LINE__); return 0;
				}
				int NCLBufferToggle::EnqueueFillBuffer(cl_command_queue command_queue, const void* pattern, size_t pattern_size, size_t offset, size_t size, cl_uint num_events_in_wait_list, const cl_event * event_wait_list, cl_event * event)
				{
					if (!(toggle)) { return 0; } cl_int Error = 0; if (active) { Error = clEnqueueFillBuffer(command_queue, m_buffer, pattern, pattern_size, offset, size, num_events_in_wait_list, event_wait_list, event); if (Error == -1) { printf("Enqueueing the buffer failed: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; } }return 1; }printf("Buffer is not active and should not be enqueued.: \n: " __FUNCTION__ " %d\n", __LINE__); return 0;
				}
				void* NCLBufferToggle::EnqueueMapBuffer(cl_command_queue command_queue, cl_bool blocking_map, cl_map_flags map_flags, size_t offset, size_t size, cl_uint num_events_in_wait_list, const cl_event * event_wait_list, cl_event * event)
				{
					if (!(toggle)) { return 0; } cl_int Error = 0; if (active) { void* map = clEnqueueMapBuffer(command_queue, m_buffer, blocking_map, map_flags, offset, size, num_events_in_wait_list, event_wait_list, event, &Error); if (Error == -1) { printf("Enqueueing the buffer failed: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; } }if (map == nullptr) { printf("Mapping was null: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; } }return map; }printf("Buffer is not active and should not be enqueued.: \n: " __FUNCTION__ " %d\n", __LINE__); return 0;
				}
				int NCLBufferToggle::EnqueueUnmapBuffer(cl_command_queue command_queue, void* mapped_ptr, cl_uint num_events_in_wait_list, const cl_event * event_wait_list, cl_event * event)
				{
					if (!(toggle)) { return 0; } cl_int Error = 0; if (active) { Error = clEnqueueUnmapMemObject(command_queue, m_buffer, mapped_ptr, num_events_in_wait_list, event_wait_list, event); if (Error == -1) { printf("Enqueueing the buffer failed: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; } }return 1; }printf("Buffer is not active and should not be enqueued.: \n: " __FUNCTION__ " %d\n", __LINE__); return 0;
				}
				bool NCLBufferToggle::Completeness()
				{
					if (!(toggle)) { return 0; } bool Flip = !incomplete; return Flip;
				}
				cl_mem NCLBufferToggle::ReturnBuffer()
				{
					if (!(toggle)) { return 0; } return m_buffer;
				}
				NCLBufferToggle::~NCLBufferToggle()
				{
					if (!(toggle)) {}
					else { ReleaseBuffer(); }
				}

				NCLCommandQueueToggle::NCLCommandQueueToggle()
				{
					if (!(toggle)) {}
					else { commandqueue = 0; incomplete = false; active = false; released = true; }
				}
				int NCLCommandQueueToggle::CreateCommandQueue(cl_context context, cl_device_id device, cl_command_queue_properties properties)
				{
					if (!(toggle)) { return 0; } cl_int Error = 0; if (active == true && released == false) { printf("Command queue already active: Releasing object. \n"); Error = clReleaseCommandQueue(commandqueue); if (CLerr(Error) == false) { printf("Failure to release command queue. \n: " __FUNCTION__ "%d\n", __LINE__); incomplete = true; return 0; } }commandqueue = clCreateCommandQueue(context, device, properties, &Error); if (Error == -1) { printf("Unable to create command queue: \n: " __FUNCTION__ "%d\n", __LINE__); incomplete = true; if (CLerr(Error) == false) { return 0; } }active = true; released = false; return 1;
				}
				int NCLCommandQueueToggle::RetainCommandQueue()
				{
					if (!(toggle)) { return 0; } cl_int Error = 0; if (active == true && released == false) { Error = clRetainCommandQueue(commandqueue); if (CLerr(Error) == false) { printf("Failure to retain command queue. \n: " __FUNCTION__ "%d\n", __LINE__); incomplete = true; return 0; }return 1; }
					else { printf("Not active and possibly released.. \n: " __FUNCTION__ "%d\n", __LINE__); return 0; }return 0;
				}
				int NCLCommandQueueToggle::ReleaseCommandQueue()
				{
					if (!(toggle)) { return 0; } cl_int Error = 0; if (active == true && released == false) { printf("Command queue already active: Releasing object. \n"); Error = clReleaseCommandQueue(commandqueue); if (CLerr(Error) == false) { printf("Failure to release command queue. \n: " __FUNCTION__ "%d\n", __LINE__); incomplete = true; return 0; } }active = false; released = true; return 1;
				}
				int NCLCommandQueueToggle::EnqueueBarrier()
				{
					if (!(toggle)) { return 0; } if (active) {
						cl_int Error = 0;
					}
					//Error = clEnqueueBarrier(commandqueue);if (Error == -1){printf("Unable to enqueue command queue with barrier.: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; }}return 1;}return 0;}
				}
						int NCLCommandQueueToggle::EnqueueBarrierWithWaitList(cl_uint num_events_in_wait_list, const cl_event * event_wait_list, cl_event * event)
						{
							if (!(toggle)) { return 0; } if (active) { cl_int Error = 0; Error = clEnqueueBarrierWithWaitList(commandqueue, num_events_in_wait_list, event_wait_list, event); if (Error == -1) { printf("Unable to enqueue barrier with wait list.: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; } }return 1; }return 0;
						}
						int NCLCommandQueueToggle::EnqueueMarkerWithWaitList(cl_uint num_events_in_wait_list, const cl_event * event_wait_list, cl_event * event)
						{
							if (!(toggle)) { return 0; } if (active) { cl_int Error = 0; Error = clEnqueueMarkerWithWaitList(commandqueue, num_events_in_wait_list, event_wait_list, event); if (Error == -1) { printf("Unable to enqueue barrier with wait list.: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; } }return 1; }return 0;
						}
						int NCLCommandQueueToggle::Flush()
						{
							if (!(toggle)) { return 0; } if (active) { clFlush(commandqueue); return 1; }return 0;
						}
						int NCLCommandQueueToggle::Finish()
						{
							if (!(toggle)) { return 0; } if (active) { clFinish(commandqueue); return 1; }return 0;
						}
						cl_command_queue NCLCommandQueueToggle::ReturnCommandQueue()
						{
							if (!(toggle)) { return 0; } return commandqueue;
						}
						bool NCLCommandQueueToggle::Completeness()
						{
							if (!(toggle)) { return 0; } bool Flip = !incomplete; return Flip;
						}
						NCLCommandQueueToggle::~NCLCommandQueueToggle()
						{
							if (!(toggle)) {}
							else { ReleaseCommandQueue(); }
						}

						NCLContextToggle::NCLContextToggle()
						{
							if (!(toggle)) {}
							else { context = 0; incomplete = false; active = false; }
						}
						int NCLContextToggle::CreateContext(const cl_context_properties * properties, cl_uint num_devices, const cl_device_id * devices, void(__stdcall pfn_notify)(const char* errinfo, const void* private_info, size_t cb, void* user_data), void* user_data)
						{
							if (!(toggle)) { return 0; } cl_int Error = 0; if (active == true) { Error = clReleaseContext(context); if (CLerr(Error) == false) { printf("Failure to release context. \n: "  "%d\n", __LINE__); incomplete = true; return 0; }printf("Released context prematurely. Need to reallocat other objects connected to context.\n"); active = false; }context = clCreateContext(properties, num_devices, devices, pfn_notify, user_data, &Error); if (CLerr(Error) == false) { printf("Failure to create context. \n "  " %d\n", __LINE__); incomplete = true; active = false; return 0; }active = true; return 1;
						}
						bool NCLContextToggle::Completeness()
						{
							if (!(toggle)) { return 0; } bool Flip = !incomplete; return Flip;
						}
						int NCLContextToggle::RetainContext()
						{
							if (!(toggle)) { return 0; } cl_int Error = 0; Error = clRetainContext(context); if (Error == -1) { printf("Unable to retain devices: \n: "  " %d\n", __LINE__); incomplete = true; if (CLerr(Error) == false) { return 0; } }
						}
						cl_context NCLContextToggle::ReturnContext()
						{
							if (!(toggle)) { return 0; } return context;
						}
						NCLContextToggle::~NCLContextToggle()
						{
							if (!(toggle)) {}
							else { clReleaseContext(context); }
						}