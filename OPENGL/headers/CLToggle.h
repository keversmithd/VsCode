#pragma once
#include "NCLDebug.h"
struct NCLEventToggle
{
protected:
	bool toggle;
	cl_event m_event;
	bool active;
public:
	NCLEventToggle();
	int CreateUserEvent(cl_context context);
	int GetEventInfo(cl_event_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
	int ReleaseEvent();
	int RetainEvent();
	int SetEventCallback(cl_int command_exec_callback_type, void (CL_CALLBACK* pfn_notify)(cl_event event, cl_int event_command_status, void* user_data), void* user_data);
	int SetUserEventStatus(cl_int execution_status);
	int WaitForEvents();
	~NCLEventToggle();
};

struct NCLImageToggle
{
protected:
	bool toggle;
	cl_mem m_image;
	bool incomplete;
	bool active;
public:
	NCLImageToggle();
	int CreateImage(cl_context context, cl_mem_flags flags, const cl_image_format* image_format, const cl_image_desc* image_desc, void* host_ptr);
	int ReleaseImage();
	int RetainImage();
	int EnqueueReadImage(cl_command_queue command_queue, cl_bool blocking_read, const size_t* origin, const size_t* region, size_t row_pitch, size_t slice_pitch, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	int EnqueueWriteImage(cl_command_queue command_queue, cl_bool blocking_write, const size_t* origin, const size_t* region, size_t input_row_pitch, size_t input_slice_pitch, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	int EnqueueCopyImage(cl_command_queue command_queue, cl_mem dst_image, const size_t* src_origin, const size_t* dst_origin, const size_t* region, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	int EnqueueCopyImageToBuffer(cl_command_queue command_queue, cl_mem dst_buffer, const size_t* src_origin, const size_t* region, size_t dst_offset, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	int EnqueueCopyBufferToImage(cl_command_queue command_queue, cl_mem src_buffer, cl_mem dst_image, size_t src_offset, const size_t* dst_origin, const size_t* region, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	int EnqueueFillImage(cl_command_queue command_queue, const void* fill_color, const size_t* origin, const size_t* region, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	void* EnqueueMapImage(cl_command_queue command_queue, cl_bool blocking_map, cl_map_flags map_flags, const size_t* origin, const size_t* region, size_t* image_row_pitch, size_t* image_slice_pitch, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	int EnqueueUnmapBuffer(cl_command_queue command_queue, void* mapped_ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	int GetImageInfo(cl_image_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
	bool Completeness();
	cl_mem ReturnImage();
	~NCLImageToggle();
};

struct NCLKernelToggle
{
protected:
	bool toggle;
	cl_kernel m_kernel;
	bool incomplete;
	bool active;
public:
	NCLKernelToggle();
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
	~NCLKernelToggle();
};

struct NCLProgramToggle
{
protected:
	bool toggle;
	cl_program m_program;
	bool incomplete;
	bool active;
public:
	NCLProgramToggle();
	int CreateProgramWithSource(cl_context context, cl_uint count, const char** strings, const size_t* lengths);
	int CreateProgramWithBinary(cl_context context, cl_uint num_devices, const cl_device_id* device_list, const size_t* lengths, const unsigned char** binaries, cl_int* binary_status);
	int CompileProgram(cl_uint num_devices, const cl_device_id* device_list, const char* options, cl_uint num_input_headers, const cl_program* input_headers, const char** header_include_names, void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data), void* user_data);
	int LinkProgram(cl_context context, cl_uint num_devices, const cl_device_id* device_list, const char* options, cl_uint num_input_programs, const cl_program* input_programs, void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data), void* user_data);
	int BuildProgram(cl_uint num_devices, const cl_device_id* device_list, const char* options, void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data), void* user_data);
	int GetProgramBuildInfo(cl_device_id device, cl_program_build_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
	int GetProgramInfo(cl_program_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
	int ReleaseProgram();
	int RetainProgram();
	cl_program ReturnProgram();
	bool Completeness();
	~NCLProgramToggle();
};

struct NCLSamplerToggle
{
protected:
	bool toggle;
	cl_sampler m_sampler;
	bool incomplete;
	bool active;
public:
	NCLSamplerToggle();
	int CreateSampler(cl_context context, cl_bool normalized_coords, cl_addressing_mode addressing_mode, cl_filter_mode filter_mode);
	int ReleaseSampler();
	int RetainSampler();
	int GetSamplerInfo(cl_sampler_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
	bool Completeness();
	cl_sampler ReturnSampler();
	~NCLSamplerToggle();
};

struct NCLBufferToggle
{
protected:
	bool toggle;
	cl_mem m_buffer;
	bool incomplete;
	bool active = false;
public:
	NCLBufferToggle();
	int CreateBuffer(cl_context context, cl_mem_flags flags, size_t size, void* host_ptr);
	int CreateBufferFromGLBuffer(cl_context context, cl_mem_flags flags, cl_GLuint buffer);
	cl_mem CreateSubBuffer(cl_mem_flags flags, cl_buffer_create_type buffer_create_type, const void* buffer_create_info);
	int ReleaseBuffer();
	int RetainBuffer();
	int EnqueueReadBuffer(cl_command_queue command_queue, cl_bool blocking_read, size_t offset, size_t size, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* p_event);
	//Enqueue Sub Object  : Doesn't have to be here.int EnqueueReadBuffer(cl_command_queue command_queue, cl_bool blocking_read, size_t offset, size_t size, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* p_event);
	int EnqueueWriteBuffer(cl_command_queue command_queue, cl_bool blocking_write, size_t offset, size_t size, const void* ptr, cl_uint num_events_in_wait_list, const cl_event * event_wait_list, cl_event * p_event);
	int EnqueueReadBufferRect(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, const size_t* buffer_offset, const size_t* host_offset, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	int EnqueueWriteBufferRect(cl_command_queue command_queue, cl_bool blocking_write, const size_t* buffer_offset, const size_t* host_offset, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	int EnqueueCopyBuffer(cl_command_queue command_queue, cl_mem dst_buffer, size_t src_offset, size_t dst_offset, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	int EnqueueCopyBufferRect(cl_command_queue command_queue, cl_mem dst_buffer, const size_t* src_origin, const size_t* dst_origin, const size_t* region, size_t src_row_pitch, size_t src_slice_pitch, size_t dst_row_pitch, size_t dst_slice_pitch, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	int EnqueueFillBuffer(cl_command_queue command_queue, const void* pattern, size_t pattern_size, size_t offset, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	void* EnqueueMapBuffer(cl_command_queue command_queue, cl_bool blocking_map, cl_map_flags map_flags, size_t offset, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	int EnqueueUnmapBuffer(cl_command_queue command_queue, void* mapped_ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	bool Completeness();
	cl_mem ReturnBuffer();
	~NCLBufferToggle();
};

struct NCLCommandQueueToggle
{
protected:
	bool toggle;
	cl_command_queue commandqueue;
	bool active;
	bool incomplete;
	bool released;
public:
	NCLCommandQueueToggle();
	int CreateCommandQueue(cl_context context, cl_device_id device, cl_command_queue_properties properties);
	int RetainCommandQueue();
	int ReleaseCommandQueue();
	int EnqueueBarrier();
	int EnqueueBarrierWithWaitList(cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	int EnqueueMarkerWithWaitList(cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	int Flush();
	int Finish();
	cl_command_queue ReturnCommandQueue();
	bool Completeness();
	~NCLCommandQueueToggle();
};

struct NCLContextToggle
{
protected:
	bool toggle;
	cl_context context;
	bool incomplete;
	bool active;
public:
	NCLContextToggle();
	int CreateContext(const cl_context_properties* properties, cl_uint num_devices, const cl_device_id* devices, void(__stdcall pfn_notify)(const char* errinfo, const void* protected_info, size_t cb, void* user_data), void* user_data);
	int RetainContext();
	cl_context ReturnContext();
	bool Completeness();
	~NCLContextToggle();
};

struct NCLDeviceToggle
{
protected:
	bool toggle;
	cl_device_id device;
	cl_device_id* devices;
	cl_uint num_devices;
	bool incomplete;
public:
	NCLDeviceToggle();
	int GetDevices(cl_platform_id platform, cl_device_type devicetype);
	int GetDeviceInfo(unsigned int index, cl_device_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
	int SelectDefaultDevice(cl_uint deviceindex);
	int FreeDevices();
	cl_device_id ArrayReturnDevice(cl_uint deviceindex);
	cl_device_id ReturnDevice();
	int RetainDevice();
	bool CheckCompleteness();
	~NCLDeviceToggle();
};

struct NCLPlatformToggle
{
protected:
	bool toggle;
	cl_platform_id platform;
	cl_platform_id* platforms;
	cl_uint num_platforms;
	bool incomplete;
public:
	NCLPlatformToggle();
	int GetPlatforms();
	int SelectDefaultPlatform(cl_uint platformindex);
	int FreePlatforms();
	cl_platform_id ReturnPlatform();
	cl_platform_id& ReferencePlatform();
	cl_platform_id ArrayReturnPlatform(cl_uint platformindex);
	bool Completeness();
	~NCLPlatformToggle();
};