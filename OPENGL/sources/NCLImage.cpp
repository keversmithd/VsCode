#include "NCLImage.h"

NCLImage::NCLImage()
{
	m_image = 0;
	incomplete = true;
	active = false;
}
int NCLImage::CreateImage(cl_context context, cl_mem_flags flags, const cl_image_format* image_format, const cl_image_desc* image_desc, void* host_ptr)
{
	cl_int Error = 0;
	if (active)
	{
		ReleaseImage();
		printf("Image object released, be aware \n");
	}

	m_image = clCreateImage(context, flags, image_format, image_desc, host_ptr, &Error);

	if (Error == -1) {
		printf("Unable to create image: \n: " __FUNCTION__ " %d\n", __LINE__); incomplete = true; if (CLerr(Error) == false) { return 0; }
	}

	incomplete = false;
	return 1;
}
int NCLImage::ReleaseImage()
{
	cl_int Error = 0;
	if (active == true)
	{
		Error = clReleaseMemObject(m_image);
		if (Error == -1) {
			printf("Unable to release buffer devices: \n: " __FUNCTION__ " %d\n", __LINE__); incomplete = true; if (CLerr(Error) == false) { return 0; }
		}
	}
	active = false;
	return 1;
}
int NCLImage::RetainImage()
{
	cl_int Error = 0;
	if (active)
	{
		Error = clRetainMemObject(m_image);
		if (Error == -1) {
			printf("Unable to retain image object: \n: " __FUNCTION__ " %d\n", __LINE__); incomplete = true; if (CLerr(Error) == false) { return 0; }
		}
	}
	return 0;
}
int NCLImage::EnqueueReadImage(cl_command_queue command_queue, cl_bool blocking_read, const size_t* origin, const size_t* region, size_t row_pitch, size_t slice_pitch, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event)
{
	cl_int Error = 0;
	if (active)
	{
		Error = clEnqueueReadImage(command_queue, m_image, blocking_read, origin, region, row_pitch, slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event);
		if (Error == -1) {
			printf("Unable to enqueue the read command: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; }
		}
		return 1;
	}

	return 0;
}
int NCLImage::EnqueueWriteImage(cl_command_queue command_queue, cl_bool blocking_write, const size_t* origin, const size_t* region, size_t input_row_pitch, size_t input_slice_pitch, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event)
{

	cl_int Error = 0;
	if (active)
	{
		Error = clEnqueueWriteImage(command_queue, m_image, blocking_write, origin, region, input_row_pitch, input_slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event);
		if (Error == -1) {
			printf("Unable to enqueue the write command: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; }
		}
		return 1;
	}

	return 0;

}
int NCLImage::EnqueueCopyImage(cl_command_queue command_queue, cl_mem dst_image, const size_t* src_origin, const size_t* dst_origin, const size_t* region, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event)
{
	cl_int Error = 0;
	if (active)
	{
		Error = clEnqueueCopyImage(command_queue, m_image, dst_image, src_origin, dst_origin, region, num_events_in_wait_list, event_wait_list, event);
		if (Error == -1) {
			printf("Unable to enqueue the image: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; }
		}
		return 1;
	}
	return 0;
}
int NCLImage::EnqueueCopyImageToBuffer(cl_command_queue command_queue, cl_mem dst_buffer, const size_t* src_origin, const size_t* region, size_t dst_offset, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event)
{
	cl_int Error = 0;
	if (active)
	{
		Error = clEnqueueCopyImageToBuffer(command_queue, m_image, dst_buffer,src_origin,region,dst_offset,num_events_in_wait_list,event_wait_list,event);
		if (Error == -1) {
			printf("Unable to enqueue the image: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; }
		}
		return 1;
	}
	return 0;
}
int NCLImage::EnqueueCopyBufferToImage(cl_command_queue command_queue, cl_mem src_buffer, cl_mem dst_image, size_t src_offset, const size_t* dst_origin, const size_t* region, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event)
{
	cl_int Error = 0;
	if (active)
	{
		Error = clEnqueueCopyBufferToImage(command_queue, src_buffer, m_image, src_offset, dst_origin, region, num_events_in_wait_list, event_wait_list, event);
		if (Error == -1) {
			printf("Unable to enqueue the image: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; }
		}
		return 1;
	}
	return 0;
}
int NCLImage::EnqueueFillImage(cl_command_queue command_queue, const void* fill_color, const size_t* origin, const size_t* region, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event)
{
	cl_int Error = 0;
	if (active)
	{
		Error = clEnqueueFillImage(command_queue, m_image, fill_color, origin, region, num_events_in_wait_list, event_wait_list, event);
		if (Error == -1) {
			printf("Unable to enqueue the image: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; }
		}
		return 1;
	}
	return 0;
}
void* NCLImage::EnqueueMapImage(cl_command_queue command_queue, cl_bool blocking_map, cl_map_flags map_flags, const size_t* origin, const size_t* region, size_t* image_row_pitch, size_t* image_slice_pitch, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event)
{
	cl_int Error = 0;
	if (active)
	{
		
		void* map = clEnqueueMapImage(command_queue, m_image, blocking_map, map_flags, origin, region, image_row_pitch, image_slice_pitch, num_events_in_wait_list, event_wait_list, event ,&Error);
		if (Error == -1) {
			printf("Unable to enqueue the image: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; }
		}
		return map;
	}
	return 0;
}
int NCLImage::EnqueueUnmapBuffer(cl_command_queue command_queue, void* mapped_ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event)
{
	cl_int Error = 0;
	if (active)
	{
		Error = clEnqueueUnmapMemObject(command_queue, m_image, mapped_ptr, num_events_in_wait_list, event_wait_list, event);
		if (Error == -1) {
			printf("Enqueueing the buffer failed: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; }
		}
		return 1;
	}
	printf("Buffer is not active and should not be enqueued.: \n: " __FUNCTION__ " %d\n", __LINE__);
	return 0;
}

int NCLImage::GetImageInfo(cl_image_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret)
{
	cl_int Error = 0;
	Error = clGetImageInfo(m_image, param_name, param_value_size, param_value, param_value_size_ret);
	if (Error == -1) {
		printf("Unable to get the image info: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; }
	}
	return 1;

}
bool NCLImage::Completeness()
{
	bool Flip = !incomplete;
	return Flip;
}
cl_mem NCLImage::ReturnImage()
{
	return m_image;
}
NCLImage::~NCLImage()
{
	ReleaseImage();
}