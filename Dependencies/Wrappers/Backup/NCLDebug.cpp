#include "NCLDebug.h"
#define CLDEBOUTPUT
char* CLParser(const char* path)
{
	FILE* ParseFile;
	fopen_s(&ParseFile, path, "rb");
	fpos_t extractionByteTotal;
	if (ParseFile != NULL)
	{
		fseek(ParseFile, 0, SEEK_END);
		fgetpos(ParseFile, &extractionByteTotal);
		fseek(ParseFile, 0, SEEK_SET);
		char* ParseBuffer = (char*)malloc(static_cast<size_t>(extractionByteTotal + 1));
		if (ParseBuffer != nullptr)
		{
			fread(ParseBuffer, extractionByteTotal, 1, ParseFile);
			ParseBuffer[extractionByteTotal] = '\0';
		}
		fclose(ParseFile);
		return ParseBuffer;
	}
	return nullptr;
}

bool CLerr(cl_int err)
{
#ifdef CLDEBOUTPUT
	switch (err)
	{

	case -1:   printf("CL_DEVICE_NOT_FOUND	clGetDeviceIDs	if no OpenCL devices that matched device_type were found.\n");
		return false;
		break;
	case -2:   printf("CL_DEVICE_NOT_AVAILABLE	clCreateContext	if a device in devices is currently not available even though the device was returned by clGetDeviceIDs.\n");
		break;
	case -3:   printf("CL_COMPILER_NOT _AVAILABLE	clBuildProgram	if program is created with clCreateProgramWithSourceand a compiler is not available i.e.CL_DEVICE_COMPILER_AVAILABLE specified in the table of OpenCL Device Queries for clGetDeviceInfo is set to CL_FALSE.\n");
		break;
	case -4:   printf("CL_MEM_OBJECT _ALLOCATION_FAILUREif there is a failure to allocate memory for buffer object.\n");
		break;
	case -5:   printf("CL_OUT_OF_RESOURCES if there is a failure to allocate resources required by the OpenCL implementation on the device.\n");
		break;
	case -6:   printf("CL_OUT_OF_HOST_MEMORY		if there is a failure to allocate resources required by the OpenCL implementation on the host.\n");
		break;
	case -7:   printf("CL_PROFILING_INFO_NOT _AVAILABLE	clGetEventProfilingInfo	if the CL_QUEUE_PROFILING_ENABLE flag is not set for the command - queue, if the execution status of the command identified by event is not CL_COMPLETE or if event is a user event object.\n");
		break;
	case -8:   printf("CL_MEM_COPY_OVERLAP	clEnqueueCopyBuffer, clEnqueueCopyBufferRect, clEnqueueCopyImage	if src_bufferand dst_buffer are the same buffer or subbuffer object and the source and destination regions overlap or if src_bufferand dst_buffer are different sub - buffers of the same associated buffer object and they overlap.The regions overlap if src_offset ? to dst_offset ? to src_offset + size – 1, or if dst_offset ? to src_offset ? to dst_offset + size – 1.\n");
		break;
	case -9:   printf("CL_IMAGE_FORMAT _MISMATCH	clEnqueueCopyImage	if src_imageand dst_image do not use the same image format.\n");
		break;
	case -10:	printf("CL_IMAGE_FORMAT_NOT _SUPPORTED	clCreateImage	if the image_format is not supported.\n");
		break;
	case -11:	printf("CL_BUILD_PROGRAM _FAILURE	clBuildProgram	if there is a failure to build the program executable.This error will be returned if clBuildProgram does not return until the build has completed.\n");
		break;
	case -12:	printf("CL_MAP_FAILURE	clEnqueueMapBuffer, clEnqueueMapImage	if there is a failure to map the requested region into the host address space.This error cannot occur for image objects created with CL_MEM_USE_HOST_PTR or CL_MEM_ALLOC_HOST_PTR.\n");
		break;
	case -13:	printf("CL_MISALIGNED_SUB _BUFFER_OFFSET		if a sub - buffer object is specified as the value for an argument that is a buffer objectand the offset specified when the sub - buffer object is created is not aligned to CL_DEVICE_MEM_BASE_ADDR_ALIGN value for device associated with queue.\n");
		break;
	case -14:	printf("CL_EXEC_STATUS_ERROR_ FOR_EVENTS_IN_WAIT_LIST		if the execution status of any of the events in event_list is a negative integer value.\n");
		break;
	case -15:	printf("CL_COMPILE_PROGRAM _FAILURE	clCompileProgram	if there is a failure to compile the program source.This error will be returned if clCompileProgram does not return until the compile has completed.\n");
		break;
	case -16:	printf("CL_LINKER_NOT_AVAILABLE	clLinkProgram	if a linker is not available i.e.CL_DEVICE_LINKER_AVAILABLE specified in the table of allowed values for param_name for clGetDeviceInfo is set to CL_FALSE.\n");
		break;
	case -17:	printf("CL_LINK_PROGRAM_FAILURE	clLinkProgram	if there is a failure to link the compiled binariesand  or libraries.\n");
		break;
	case -18:	printf("CL_DEVICE_PARTITION _FAILED	clCreateSubDevices	if the partition name is supported by the implementation but in_device could not be further partitioned.\n");
		break;
	case -19:	printf("CL_KERNEL_ARG_INFO _NOT_AVAILABLE	clGetKernelArgInfo	if the argument information is not available for kernel.\n");
		break;
	case -30:	printf("CL_INVALID_VALUE	clGetDeviceIDs, clCreateContext	This depends on the function : two or more coupled parameters had errors.\n");
		break;
	case -31:	printf("CL_INVALID_DEVICE_TYPE	clGetDeviceIDs	if an invalid device_type is given\n");
		break;
	case -32:	printf("CL_INVALID_PLATFORM	clGetDeviceIDs	if an invalid platform was given\n");
		break;
	case -33:	printf("CL_INVALID_DEVICE	clCreateContext, clBuildProgram	if devices contains an invalid device or are not associated with the specified platform.\n");
		break;
	case -34:	printf("CL_INVALID_CONTEXT		if context is not a valid context.\n");
		break;
	case -35:	printf("CL_INVALID_QUEUE_PROPERTIES	clCreateCommandQueue	if specified command - queue - properties are valid but are not supported by the device.\n");
		break;
	case -36:	printf("CL_INVALID_COMMAND_QUEUE		if command_queue is not a valid command - queue.\n");
		break;
	case -37:	printf("CL_INVALID_HOST_PTR	clCreateImage, clCreateBuffer	This flag is valid only if host_ptr is not NULL.If specified, it indicates that the application wants the OpenCL implementation to allocate memory for the memory objectand copy the data from memory referenced by host_ptr.CL_MEM_COPY_HOST_PTRand CL_MEM_USE_HOST_PTR are mutually exclusive.CL_MEM_COPY_HOST_PTR can be used with CL_MEM_ALLOC_HOST_PTR to initialize the contents of the cl_mem object allocated using host - accessible(e.g.PCIe) memory.\n");
		break;
	case -38:	printf("CL_INVALID_MEM_OBJECT		if memobj is not a valid OpenCL memory object.\n");
		break;
	case -39:	printf("CL_INVALID_IMAGE_FORMAT_DESCRIPTOR		if the OpenGL  DirectX texture internal format does not map to a supported OpenCL image format.\n");
		break;
	case -40:	printf("CL_INVALID_IMAGE_SIZE		if an image object is specified as an argument valueand the image dimensions(image width, height, specified or compute row and  or slice pitch) are not supported by device associated with queue.\n");
		break;
	case -41:	printf("CL_INVALID_SAMPLER	clGetSamplerInfo, clReleaseSampler, clRetainSampler, clSetKernelArg	if sampler is not a valid sampler object.\n");
		break;
	case -42:	printf("CL_INVALID_BINARY	clCreateProgramWithBinary, clBuildProgram\n");
		break;
	case -43:	printf("CL_INVALID_BUILD_OPTIONS	clBuildProgram	if the build options specified by options are invalid.\n");
		break;
	case -44:	printf("CL_INVALID_PROGRAM		if program is a not a valid program object.\n");
		break;
	case -45:	printf("CL_INVALID_PROGRAM_EXECUTABLE		if there is no successfully built program executable available for device associated with command_queue.\n");
		break;
	case -46:	printf("CL_INVALID_KERNEL_NAME	clCreateKernel	if kernel_name is not found in program.\n");
		break;
	case -47:	printf("CL_INVALID_KERNEL_DEFINITION	clCreateKernel	if the function definition for __kernel function given by kernel_name such as the number of arguments, the argument types are not the same for all devices for which the program executable has been built.\n");
		break;
	case -48:	printf("CL_INVALID_KERNEL		if kernel is not a valid kernel object.\n");
		break;
	case -49:	printf("CL_INVALID_ARG_INDEX	clSetKernelArg, clGetKernelArgInfo	if arg_index is not a valid argument index.\n");
		break;
	case -50:	printf("CL_INVALID_ARG_VALUE	clSetKernelArg, clGetKernelArgInfo	if arg_value specified is not a valid value.\n");
		break;
	case -51:	printf("CL_INVALID_ARG_SIZE	clSetKernelArg	if arg_size does not match the size of the data type for an argument that is not a memory object or if the argument is a memory objectand arg_size != sizeof(cl_mem) or if arg_size is zeroand the argument is declared with the __local qualifier or if the argument is a samplerand arg_size != sizeof(cl_sampler).\n");
		break;
	case -52:	printf("CL_INVALID_KERNEL_ARGS		if the kernel argument values have not been specified.\n");
		break;
	case -53:	printf("CL_INVALID_WORK_DIMENSION		if work_dim is not a valid value(i.e.a value between 1 and 3).\n");
		break;
	case -54:	printf("CL_INVALID_WORK_GROUP_SIZE		if local_work_size is specifiedand number of work - items specified by global_work_size is not evenly divisable by size of work - group given by local_work_size or does not match the work - group size specified for kernel using the __attribute__((reqd_work_group_size(X, Y, Z))) qualifier in program source.if local_work_size is specifiedand the total number of work - items in the work - group computed as local_work_size[0] * … local_work_size[work_dim – 1] is greater than the value specified by CL_DEVICE_MAX_WORK_GROUP_SIZE in the table of OpenCL Device Queries for clGetDeviceInfo.if local_work_size is NULLand the __attribute__((reqd_work_group_size(X, Y, Z))) qualifier is used to declare the work - group size for kernel in the program source.\n");
		break;
	case -55:	printf("CL_INVALID_WORK_ITEM_SIZE		if the number of work - items specified in any of local_work_size[0], … local_work_size[work_dim – 1] is greater than the corresponding values specified by CL_DEVICE_MAX_WORK_ITEM_SIZES[0], ….CL_DEVICE_MAX_WORK_ITEM_SIZES[work_dim – 1].\n");
		break;
	case -56:	printf("CL_INVALID_GLOBAL_OFFSET		if the value specified in global_work_size + the corresponding values in global_work_offset for any dimensions is greater than the sizeof(size_t) for the device on which the kernel execution will be enqueued.\n");
		break;
	case -57:	printf("CL_INVALID_EVENT_WAIT_LIST		if event_wait_list is NULLand num_events_in_wait_list > 0, or event_wait_list is not NULL and num_events_in_wait_list is 0, or if event objects in event_wait_list are not valid events.\n");
		break;
	case -58:	printf("CL_INVALID_EVENT		if event objects specified in event_list are not valid event objects.\n");
		break;
	case -59:	printf("CL_INVALID_OPERATION		if interoperability is specified by setting CL_CONTEXT_ADAPTER_D3D9_KHR, CL_CONTEXT_ADAPTER_D3D9EX_KHR or CL_CONTEXT_ADAPTER_DXVA_KHR to a non - NULL value, and interoperability with another graphics API is also specified. (only if the cl_khr_dx9_media_sharing extension is supported).\n");
		break;
	case -60:	printf("CL_INVALID_GL_OBJECT		if texture is not a GL texture object whose type matches texture_target, if the specified miplevel of texture is not defined, or if the width or height of the specified miplevel is zero.\n");
		break;
	case -61:	printf("CL_INVALID_BUFFER_SIZE	clCreateBuffer, clCreateSubBuffer	if size is 0.Implementations may return CL_INVALID_BUFFER_SIZE if size is greater than the CL_DEVICE_MAX_MEM_ALLOC_SIZE value specified in the table of allowed values for param_name for clGetDeviceInfo for all devices in context.\n");
		break;
	case -62:	printf("CL_INVALID_MIP_LEVEL	OpenGL - functions	if miplevel is greater than zeroand the OpenGL implementation does not support creating from non - zero mipmap levels.\n");
		break;
	case -63:	printf("CL_INVALID_GLOBAL_WORK_SIZE		if global_work_size is NULL, or if any of the values specified in global_work_size[0], …global_work_size[work_dim – 1] are 0 or exceed the range given by the sizeof(size_t) for the device on which the kernel execution will be enqueued.\n");
		break;
	case -64:	printf("CL_INVALID_PROPERTY	clCreateContext	Vague error, depends on the function\n");
		break;
	case -65:	printf("CL_INVALID_IMAGE_DESCRIPTOR	clCreateImage	if values specified in image_desc are not valid or if image_desc is NULL.\n");
		break;
	case -66:	printf("CL_INVALID_COMPILER_OPTIONS	clCompileProgram	if the compiler options specified by options are invalid.\n");
		break;
	case -67:	printf("CL_INVALID_LINKER_OPTIONS	clLinkProgram	if the linker options specified by options are invalid.\n");
		break;
	case -68:	printf("CL_INVALID_DEVICE_PARTITION_COUNT	clCreateSubDevices	if the partition name specified in properties is CL_DEVICE_PARTITION_BY_COUNTSand the number of sub - devices requested exceeds CL_DEVICE_PARTITION_MAX_SUB_DEVICES or the total number of compute units requested exceeds CL_DEVICE_PARTITION_MAX_COMPUTE_UNITS for in_device, or the number of compute units requested for one or more sub - devices is less than zero or the number of sub - devices requested exceeds CL_DEVICE_PARTITION_MAX_COMPUTE_UNITS for in_device.\n");
		break;
	case -69:	printf("CL_INVALID_PIPE_SIZE	clCreatePipe	if pipe_packet_size is 0 or the pipe_packet_size exceeds CL_DEVICE_PIPE_MAX_PACKET_SIZE value for all devices in context or if pipe_max_packets is 0.\n");
		break;
	case -70:	printf("CL_INVALID_DEVICE_QUEUE	clSetKernelArg	when an argument is of type queue_t when it’s not a valid device queue object.\n");
		break;
	case -1000:
		break;
	default:
		break;

	}
#endif
	if (err != CL_SUCCESS)
	{
		return false;
	}
	return true;
}
bool IsCLExtensionSupported(const char* extension, cl_device_id Device)
{
	// see if the extension is bogus:
	if (extension == NULL || extension[0] == '\0')
		return false;
	char* where = (char*)strchr(extension, ' ');
	if (where != NULL)
		return false;
	// get the full list of extensions:
	size_t extensionSize;
	cl_int error;
	error = clGetDeviceInfo(Device, CL_DEVICE_EXTENSIONS, 0, NULL, &extensionSize);
	if (CLerr(error) == false) { return 0; }
	char* extensions = new char[extensionSize];
	error = clGetDeviceInfo(Device, CL_DEVICE_EXTENSIONS, extensionSize, extensions, NULL);
	if (CLerr(error) == false) { delete[] extensions; return 0; }
	for (char* start = extensions; ; )
	{
		where = (char*)strstr((const char*)start, extension);
		if (where == 0)
		{
			delete[] extensions;
			return false;
		}
		char* terminator = where + strlen(extension); // points to what should be the separator
		if (*terminator == ' ' || *terminator == '\0' || *terminator == '\r' || *terminator == '\n')
		{
			delete[] extensions;
			return true;
		}
		start = terminator;
	}
}