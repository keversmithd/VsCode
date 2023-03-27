#ifndef __FUNCTION__ 
 #define __FUNCTION__ 
 #endif
#ifndef NCLIMAGE
#define NCLIMAGE



#include <memory>
#include "NCLDebug.h"

struct NCLImage
{
private:
	cl_mem m_image;
	bool incomplete;
	bool active;
public:
	NCLImage();
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
	~NCLImage();


};


#endif
