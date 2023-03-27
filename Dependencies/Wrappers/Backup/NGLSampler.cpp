#include "NGLSampler.h"

NGLSampler::NGLSampler()
{
	m_sampler = 0;
	generated = false;
}
int NGLSampler::GenerateSampler()
{
	if (generated)
	{
		printf("Object already generated delete before generated.\n");
	}
	glGenSamplers(1, &m_sampler);
	GetError
		if (Code) { return 0; }
	generated = true;
	return 1;
}
int NGLSampler::BindSampler(GLuint textureunit)
{
	if (generated)
	{
		glBindSampler(textureunit, m_sampler);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Object not generated yet and cannot be used.\n");
}
int NGLSampler::GetSamplerParameterfv(GLenum pname, GLfloat* params)
{
	if (generated)
	{
		glGetSamplerParameterfv(m_sampler, pname, params);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Object not generated yet and cannot be used.\n");
}
int NGLSampler::GetSamplerParameteriv(GLenum pname, GLint* params)
{
	if (generated)
	{
		glGetSamplerParameteriv(m_sampler, pname, params);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Object not generated yet and cannot be used.\n");
}
int NGLSampler::GetSamplerParameterIiv(GLenum pname, GLint* params)
{
	if (generated)
	{
		glGetSamplerParameterIiv(m_sampler, pname, params);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Object not generated yet and cannot be used.\n");
}
int NGLSampler::GetSamplerParameterIuiv(GLenum pname, GLuint* params)
{
	if (generated)
	{
		glGetSamplerParameterIuiv(m_sampler, pname, params);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Object not generated yet and cannot be used.\n");
}
int NGLSampler::SamplerParameterf(GLenum pname, GLfloat param)
{
	if (generated)
	{
		glSamplerParameterf(m_sampler, pname, param);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Object not generated yet and cannot be used.\n");
}
int NGLSampler::SamplerParameteri(GLenum pname, GLint param)
{
	if (generated)
	{
		glSamplerParameterf(m_sampler, pname, param);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Object not generated yet and cannot be used.\n");
}
int NGLSampler::SamplerParameterfv(GLenum pname, const GLfloat* params)
{
	if (generated)
	{
		glSamplerParameterfv(m_sampler, pname, params);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Object not generated yet and cannot be used.\n");
}
int NGLSampler::SamplerParameteriv(GLenum pname, const GLint* params)
{
	if (generated)
	{
		glSamplerParameteriv(m_sampler, pname, params);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Object not generated yet and cannot be used.\n");
}
int NGLSampler::SamplerParameterIiv(GLenum pname, const GLint* params)
{
	if (generated)
	{
		glSamplerParameterIiv(m_sampler, pname, params);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Object not generated yet and cannot be used.\n");
	
}
int NGLSampler::SamplerParameterIuiv(GLenum pname, const GLuint* params)
{
	if (generated)
	{
		glSamplerParameterIuiv(m_sampler, pname, params);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Object not generated yet and cannot be used.\n");
}
bool NGLSampler::IsSampler()
{
	GLboolean issmplr = glIsSampler(m_sampler);
	return issmplr;
}
int NGLSampler::DeleteSampler()
{
	if (generated)
	{
		glDeleteSamplers(1, &m_sampler);
		GetError
			if (Code) { return 0; }
		generated = false;
		return 1;
	}
	printf("Object not generated yet and cannot be used.\n");
}
unsigned int NGLSampler::ReturnSampler() { return m_sampler; }
NGLSampler::~NGLSampler()
{
	DeleteSampler();
}