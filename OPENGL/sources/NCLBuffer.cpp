#include "NCLBuffer.h"


NCLBuffer::NCLBuffer()
{
	m_buffer = 0;
	incomplete = true;
}
int NCLBuffer::CreateBuffer(cl_context context, cl_mem_flags flags, size_t size, void* host_ptr)
{
	cl_int Error = 0;
	if (active == true)
	{
		printf("Buffer active, releasing previous buffer.: \n: " __FUNCTION__ " %d\n", __LINE__);
		int ReleaseSuccess = ReleaseBuffer();
		if (!ReleaseSuccess) { return 0; }
	}
	m_buffer = clCreateBuffer(context, flags, size, host_ptr, &Error);
	if (CLerr(Error) == 0) {
		//printf("Unable to create buffer: \n: " __FUNCTION__ " %d\n", __LINE__); incomplete = true; if (CLerr(Error) == false) { return 0; }
		return 0;
	}
	active = true;
	return 1;
}
int NCLBuffer::CreateBufferFromGLBuffer(cl_context context, cl_mem_flags flags, cl_GLuint buffer)
{
	cl_int Error = 0;
	if (active == true)
	{
		printf("Buffer active, releasing previous buffer.: \n: " __FUNCTION__ " %d\n", __LINE__);
		int ReleaseSuccess = ReleaseBuffer();
		if (!ReleaseSuccess) { return 0; }
	}
	m_buffer = clCreateFromGLBuffer(context, flags, buffer, &Error);
	if (!CLerr(Error)) { ReleaseBuffer(); return 0; }
	active = true;
	return 1;


}
cl_mem NCLBuffer::CreateSubBuffer(cl_mem_flags flags, cl_buffer_create_type buffer_create_type, const void *buffer_create_info)
{
	cl_int Error = 0;
	if (active)
	{
		cl_mem memory = clCreateSubBuffer(m_buffer, flags, buffer_create_type, buffer_create_info, &Error);
		if (Error == -1) {
			printf("Unable to subjucate buffer : \n: " __FUNCTION__ " %d\n", __LINE__); incomplete = true; if (CLerr(Error) == false) { return 0; }
		}

		return memory;
	}
	printf("Buffer is not active : \n: " __FUNCTION__ " %d\n", __LINE__); incomplete = true; return 0;
}
int NCLBuffer::ReleaseBuffer()
{
	cl_int Error = 0;
	if (active == true)
	{
		Error = clReleaseMemObject(m_buffer);
		if (Error == -1) {
			printf("Unable to release buffer devices: \n: " __FUNCTION__ " %d\n", __LINE__); incomplete = true; if (CLerr(Error) == false) { return 0; }
		}
		active = false;
		return 1;
	}
	active = false;
	return 1;
	
}
int NCLBuffer::RetainBuffer()
{
	cl_int Error = 0;
	if (active)
	{
		Error = clRetainMemObject(m_buffer);
		if (Error == -1) {
			printf("Unable to retain mem object: \n: " __FUNCTION__ " %d\n", __LINE__); incomplete = true; if (CLerr(Error) == false) { return 0; }
		}
	}
	return 0;
}
//enqueue sections

int NCLBuffer::EnqueueReadBuffer(cl_command_queue command_queue, cl_bool blocking_read, size_t offset, size_t size, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list,  cl_event* p_event)
{
	cl_int Error = 0;
	if (active)
	{
		Error = clEnqueueReadBuffer(command_queue, m_buffer, blocking_read, offset, size, ptr, num_events_in_wait_list, event_wait_list, p_event);
		if (Error == -1) {
			printf("Enqueueing the buffer failed: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; }
		}
		return 1;
	}
	printf("Buffer is not active and should not be enqueued.: \n: " __FUNCTION__ " %d\n", __LINE__);
	return 0;

}
int NCLBuffer::EnqueueWriteBuffer(cl_command_queue command_queue, cl_bool blocking_write, size_t offset, size_t size, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* p_event)
{
	cl_int Error = 0;
	if (active)
	{
		Error = clEnqueueWriteBuffer(command_queue, m_buffer, blocking_write, offset, size, ptr, num_events_in_wait_list, event_wait_list, p_event);
		if (Error == -1) {
			printf("Enqueueing the buffer failed: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; }
		}
		return 1;
	}
	printf("Buffer is not active and should not be enqueued.: \n: " __FUNCTION__ " %d\n", __LINE__);
	return 0;
}
int NCLBuffer::EnqueueReadBufferRect(cl_command_queue command_queue,cl_mem buffer,cl_bool blocking_read,const size_t* buffer_offset,const size_t* host_offset,const size_t* region,size_t buffer_row_pitch,size_t buffer_slice_pitch,size_t host_row_pitch,size_t host_slice_pitch,void* ptr,cl_uint num_events_in_wait_list,const cl_event* event_wait_list,cl_event* event)
{
	cl_int Error = 0;
	if (active)
	{
		Error = clEnqueueReadBufferRect(command_queue, m_buffer, blocking_read, buffer_offset, host_offset, region, buffer_row_pitch, buffer_slice_pitch, host_row_pitch, host_slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event);
		if (Error == -1) {
			printf("Enqueueing the buffer failed: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; }
		}
		return 1;
	}
	printf("Buffer is not active and should not be enqueued.: \n: " __FUNCTION__ " %d\n", __LINE__);
	return 0;
}
int NCLBuffer::EnqueueWriteBufferRect(cl_command_queue command_queue, cl_bool blocking_write, const size_t* buffer_offset, const size_t* host_offset, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event)
{
	cl_int Error = 0;
	if (active)
	{
		Error = clEnqueueWriteBufferRect(command_queue, m_buffer, blocking_write, buffer_offset, host_offset, region, buffer_row_pitch, buffer_slice_pitch, host_row_pitch, host_slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event);
		if (Error == -1) {
			printf("Enqueueing the buffer failed: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; }
		}
		return 1;
	}
	printf("Buffer is not active and should not be enqueued.: \n: " __FUNCTION__ " %d\n", __LINE__);
	return 0;
}

int NCLBuffer::EnqueueCopyBuffer(cl_command_queue command_queue, cl_mem dst_buffer, size_t src_offset, size_t dst_offset, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event)
{
	cl_int Error = 0;
	if (active)
	{
		Error = clEnqueueCopyBuffer(command_queue, m_buffer, dst_buffer, src_offset, dst_offset, size, num_events_in_wait_list, event_wait_list, event);
		if (Error == -1) {
			printf("Enqueueing the buffer failed: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; }
		}
		return 1;
	}
	printf("Buffer is not active and should not be enqueued.: \n: " __FUNCTION__ " %d\n", __LINE__);
	return 0;
}
int NCLBuffer::EnqueueCopyBufferRect(cl_command_queue command_queue, cl_mem dst_buffer, const size_t* src_origin, const size_t* dst_origin, const size_t* region, size_t src_row_pitch, size_t src_slice_pitch, size_t dst_row_pitch, size_t dst_slice_pitch, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event)
{
	cl_int Error = 0;
	if (active)
	{
		Error = clEnqueueCopyBufferRect(command_queue, m_buffer, dst_buffer, src_origin, dst_origin, region, src_row_pitch, src_slice_pitch, dst_row_pitch, dst_slice_pitch, num_events_in_wait_list, event_wait_list, event);
		if (Error == -1) {
			printf("Enqueueing the buffer failed: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; }
		}
		return 1;
	}
	printf("Buffer is not active and should not be enqueued.: \n: " __FUNCTION__ " %d\n", __LINE__);
	return 0;



}
int NCLBuffer::EnqueueFillBuffer(cl_command_queue command_queue, const void* pattern, size_t pattern_size, size_t offset, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event)
{
	cl_int Error = 0;
	if (active)
	{
		Error = clEnqueueFillBuffer(command_queue, m_buffer, pattern, pattern_size, offset, size, num_events_in_wait_list, event_wait_list, event);
		if (Error == -1) {
			printf("Enqueueing the buffer failed: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; }
		}
		return 1;
	}
	printf("Buffer is not active and should not be enqueued.: \n: " __FUNCTION__ " %d\n", __LINE__);
	return 0;

}
void* NCLBuffer::EnqueueMapBuffer(cl_command_queue command_queue, cl_bool blocking_map, cl_map_flags map_flags, size_t offset, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event)
{

	cl_int Error = 0;
	if (active)
	{
		void* map = clEnqueueMapBuffer(command_queue, m_buffer, blocking_map, map_flags, offset, size, num_events_in_wait_list, event_wait_list, event, &Error);
		if (Error == -1) {
			printf("Enqueueing the buffer failed: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; }
		}
		
		if (map == nullptr)
		{
			printf("Mapping was null: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; }
		}
		return map;
	}
	printf("Buffer is not active and should not be enqueued.: \n: " __FUNCTION__ " %d\n", __LINE__);
	return 0;

}
int NCLBuffer::EnqueueUnmapBuffer(cl_command_queue command_queue, void* mapped_ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event)
{
	cl_int Error = 0;
	if (active)
	{
		Error = clEnqueueUnmapMemObject(command_queue, m_buffer, mapped_ptr, num_events_in_wait_list, event_wait_list, event);
		if (Error == -1) {
			printf("Enqueueing the buffer failed: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; }
		}
		return 1;
	}
	printf("Buffer is not active and should not be enqueued.: \n: " __FUNCTION__ " %d\n", __LINE__);
	return 0;
}

bool NCLBuffer::Completeness()
{
	bool Flip = !incomplete;
	return Flip;

}
cl_mem NCLBuffer::ReturnBuffer()
{
	return m_buffer;
}
NCLBuffer::~NCLBuffer()
{
	ReleaseBuffer();
}