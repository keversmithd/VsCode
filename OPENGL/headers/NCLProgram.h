#ifndef NCLPROG
#define NCLPROG

#include "NCLDebug.h"

struct NCLProgram
{
private:
	cl_program m_program;
	bool incomplete;
	bool active;
public:
	NCLProgram();
	int CreateProgramWithSource(cl_context context, cl_uint count, const char** strings, const size_t* lengths);
	int CreateProgramWithBinary(cl_context context, cl_uint num_devices, const cl_device_id* device_list, const size_t* lengths, const unsigned char** binaries, cl_int* binary_status);
	int CompileProgram(cl_uint num_devices, const cl_device_id* device_list, const char* options, cl_uint num_input_headers, const cl_program* input_headers, const char** header_include_names, void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data), void* user_data);
	int LinkProgram(cl_context context, cl_uint num_devices, const cl_device_id* device_list, const char* options, cl_uint num_input_programs, const cl_program* input_programs, void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data), void* user_data);
	int BuildProgram(cl_uint num_devices, const cl_device_id* device_list, const char* options, void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data), void* user_data);
	int GetProgramBuildInfo(cl_device_id device, cl_program_build_info param_name, size_t param_value_size,void* param_value,size_t* param_value_size_ret);
	int GetProgramInfo(cl_program_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
	int ReleaseProgram();
	int RetainProgram();
	cl_program ReturnProgram();
	bool Completeness();
	~NCLProgram();


};



#endif
