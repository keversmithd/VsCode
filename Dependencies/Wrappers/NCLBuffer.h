#ifndef __FUNCTION__ 
 #define __FUNCTION__ 
 #endif
#ifndef __FUNCTION__
#define __FUNCTION__
#endif
#ifndef __LINE__
#define __LINE__
#endif

#ifndef NCLBUF
#define NCLBUF

#include <CL/cl.h>
#include <memory>
#include "NCLDebug.h"

struct NCLBuffer
{
private:
	cl_mem m_buffer;
	bool incomplete;
	bool active = false;
public:
	NCLBuffer();
	int CreateBuffer(cl_context context, cl_mem_flags flags, size_t size, void* host_ptr);
	int CreateBufferFromGLBuffer(cl_context context, cl_mem_flags flags, cl_GLuint buffer);
	cl_mem CreateSubBuffer(cl_mem_flags flags, cl_buffer_create_type buffer_create_type, const void* buffer_create_info);
	int ReleaseBuffer();
	int RetainBuffer();
	//Enqueue Sub Object : Doesn't have to be here.
	int EnqueueReadBuffer(cl_command_queue command_queue, cl_bool blocking_read, size_t offset, size_t size, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* p_event);
	int EnqueueWriteBuffer(cl_command_queue command_queue, cl_bool blocking_write, size_t offset, size_t size, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* p_event);
	int EnqueueReadBufferRect(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, const size_t* buffer_offset, const size_t* host_offset, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	int EnqueueWriteBufferRect(cl_command_queue command_queue, cl_bool blocking_write, const size_t* buffer_offset, const size_t* host_offset, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	int EnqueueCopyBuffer(cl_command_queue command_queue, cl_mem dst_buffer, size_t src_offset, size_t dst_offset, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	int EnqueueCopyBufferRect(cl_command_queue command_queue, cl_mem dst_buffer, const size_t* src_origin, const size_t* dst_origin, const size_t* region, size_t src_row_pitch, size_t src_slice_pitch, size_t dst_row_pitch, size_t dst_slice_pitch, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	int EnqueueFillBuffer(cl_command_queue command_queue, const void* pattern, size_t pattern_size, size_t offset, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	void* EnqueueMapBuffer(cl_command_queue command_queue, cl_bool blocking_map, cl_map_flags map_flags, size_t offset, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	int EnqueueUnmapBuffer(cl_command_queue command_queue, void* mapped_ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	bool Completeness();
	cl_mem ReturnBuffer();
	~NCLBuffer();

};

#endif
