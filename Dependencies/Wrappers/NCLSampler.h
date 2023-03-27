#ifndef __FUNCTION__ 
 #define __FUNCTION__ 
 #endif
#ifndef NCLSAMPLR
#define NCLSAMPLR

#include "NCLDebug.h"

struct NCLSampler
{
private:
	cl_sampler m_sampler;
	bool incomplete;
	bool active;
public:
	NCLSampler();
	int CreateSampler(cl_context context, cl_bool normalized_coords, cl_addressing_mode addressing_mode, cl_filter_mode filter_mode);
	int ReleaseSampler();
	int RetainSampler();
	int GetSamplerInfo(cl_sampler_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
	bool Completeness();
	cl_sampler ReturnSampler();
	~NCLSampler();

};


#endif
