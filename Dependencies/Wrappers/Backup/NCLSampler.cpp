#include "NCLSampler.h"


NCLSampler::NCLSampler() 
{
	m_sampler = 0;
	incomplete = false;
	active = false;
}
int NCLSampler::CreateSampler(cl_context context, cl_bool normalized_coords, cl_addressing_mode addressing_mode, cl_filter_mode filter_mode)
{
	if (active)
	{
		ReleaseSampler();
		printf("Sampler was active and was released and recreated \n");
	}
	cl_int Error = 0;
	m_sampler = clCreateSampler(context, normalized_coords, addressing_mode, filter_mode, &Error);
	if (Error == -1)
	{
		printf("Unable to create sampler object: \n: " __FUNCTION__ " %d\n", __LINE__); incomplete = true; if (CLerr(Error) == false) { return 0; }
	}
	active = true;
	return 1;
}
int NCLSampler::ReleaseSampler()
{
	if (active)
	{
		cl_int Error = 0;
		Error = clReleaseSampler(m_sampler);
		if (Error == -1)
		{
			printf("Unable to release sampler object: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; }
		}
		active = false;
		return 1;
	}
	return 0;
}
int NCLSampler::RetainSampler()
{
	if (active)
	{
		cl_int Error = 0;
		Error = clRetainSampler(m_sampler);
		if (Error == -1)
		{
			printf("Unable to retain sampler object: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; }
		}
		return 1;
	}
	return 0;
}
int NCLSampler::GetSamplerInfo(cl_sampler_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret)
{
	if (active)
	{
		cl_int Error = 0;
		Error = clGetSamplerInfo(m_sampler, param_name, param_value_size, param_value, param_value_size_ret);
		if (Error == -1)
		{
			printf("Unable to get sampler info: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; }
		}
		return 1;
	}
	return 0;
}
bool NCLSampler::Completeness()
{
	bool Flip = !incomplete;
	return Flip;
}
cl_sampler NCLSampler::ReturnSampler()
{
	return m_sampler;
}
NCLSampler::~NCLSampler()
{
	if (active)
	{
		ReleaseSampler();
	}
}