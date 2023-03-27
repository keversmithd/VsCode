#include "NCLProgram.h"

NCLProgram::NCLProgram()
{
	m_program = 0;
	incomplete = false;
	active = false;
}
int NCLProgram::CreateProgramWithSource(cl_context context, cl_uint count, const char** strings, const size_t* lengths)
{
	if (active)
	{
		int ReleaseStatus = ReleaseProgram();
		if (ReleaseStatus)
		{
			printf("Program released because it was already active\n");
		}
	}
	cl_int Error = 0;
	m_program = clCreateProgramWithSource(context, count, strings, lengths, &Error);
	if (Error == -1) {
		printf("Creating the program failed.: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; }
	}
	active = true;
	return 1;

	

}
int NCLProgram::CreateProgramWithBinary(cl_context context, cl_uint num_devices, const cl_device_id* device_list, const size_t* lengths, const unsigned char** binaries, cl_int* binary_status)
{
	if (active)
	{
		int ReleaseStatus = ReleaseProgram();
		if (ReleaseStatus)
		{
			printf("Program released because it was already active\n");
		}
	}
	cl_int Error = 0;
	m_program = clCreateProgramWithBinary(context, num_devices, device_list, lengths, binaries, binary_status, &Error);
	if (Error == -1) {
		printf("Enqueueing the buffer failed: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; }
	}
	active = true;
	return 1;
}
int NCLProgram::CompileProgram(cl_uint num_devices, const cl_device_id* device_list, const char* options, cl_uint num_input_headers, const cl_program* input_headers, const char** header_include_names, void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data), void* user_data)
{
	cl_int Error = 0;
	if (active)
	{
		Error = clCompileProgram(m_program, num_devices, device_list, options, num_input_headers, input_headers, header_include_names, pfn_notify , user_data);
		if (Error == -1)
		{
			printf("Compiling the program failed: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; }
		}
		return 1;
	}
	printf("Program is not an active program object\n");
	return 0;
}
int NCLProgram::LinkProgram(cl_context context, cl_uint num_devices, const cl_device_id* device_list, const char* options, cl_uint num_input_programs, const cl_program* input_programs, void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data), void* user_data)
{
	cl_int Error = 0;
	if (active)
	{
		m_program = clLinkProgram(context,num_devices,device_list,options,num_input_programs,input_programs,pfn_notify,user_data, &Error);
		if (Error == -1)
		{
			printf("Compiling the program failed: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; }
		}
		return 1;
	}
	printf("Program is not an active program object\n");
	return 0;
}
int NCLProgram::BuildProgram(cl_uint num_devices, const cl_device_id* device_list, const char* options, void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data), void* user_data)
{
	cl_int Error = 0;
	if (active)
	{
		Error = clBuildProgram(m_program, num_devices, device_list, options, pfn_notify , user_data);
		if (Error == -1)
		{
			printf("Enqueueing the buffer failed: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; }
		}
		return 1;
	}
	printf("Program is not an active program object\n");
	return 0;

}

int NCLProgram::GetProgramBuildInfo(cl_device_id device, cl_program_build_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret)
{
	cl_int Error = 0;
	if (active)
	{
		Error = clGetProgramBuildInfo(m_program, device,param_name,param_value_size,param_value,param_value_size_ret);
		if (Error == -1)
		{
			printf("Getting build info failed: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; }
		}
		return 1;
	}
	printf("Program is not an active program object\n");
	return 0;
}
int NCLProgram::GetProgramInfo(cl_program_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret)
{
	cl_int Error = 0;
	if (active)
	{
		Error = clGetProgramInfo(m_program, param_name,param_value_size,param_value,param_value_size_ret);
		if (Error == -1)
		{
			printf("Compiling the program failed: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; }
		}
		return 1;
	}
	printf("Program is not an active program object\n");
	return 0;
}
int NCLProgram::ReleaseProgram()
{
	cl_int Error = 0;
	if (active)
	{
		Error = clReleaseProgram(m_program);
		if (Error == -1)
		{
			printf("Releasing the program failed: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; }
		}
		active = false;
		return 1;
	}
	return 1;
}
int NCLProgram::RetainProgram()
{
	cl_int Error = 0;
	if (active)
	{
		Error = clRetainProgram(m_program);
		if (Error == -1)
		{
			printf("Retaining the program failed: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; }
		}
		return 1;
	}

	return 0;
}
cl_program NCLProgram::ReturnProgram()
{
	return m_program;

}
bool NCLProgram::Completeness()
{
	bool Flip = !incomplete;
	return Flip;

}
NCLProgram::~NCLProgram() 
{
	if (active)
	{
		ReleaseProgram();
	}
}