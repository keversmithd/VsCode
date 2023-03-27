#ifndef __FUNCTION__ 
 #define __FUNCTION__ 
 #endif
#ifndef NGLSAMPLER
#define NGLSAMPLER

#include "NGLDebug.h"

struct NGLSampler
{
private:
	unsigned int m_sampler;
	bool generated;
public:

	NGLSampler();
	int GenerateSampler();
	int BindSampler(GLuint textureunit);
	int GetSamplerParameterfv(GLenum pname, GLfloat* params);
	int GetSamplerParameteriv(GLenum pname, GLint* params);
	int GetSamplerParameterIiv(GLenum pname, GLint* params);
	int GetSamplerParameterIuiv(GLenum pname, GLuint* params);
	int SamplerParameteri(GLenum pname, GLint param);
	int SamplerParameterf(GLenum pname, GLfloat param);
	int SamplerParameterfv(GLenum pname, const GLfloat* params);
	int SamplerParameteriv(GLenum pname, const GLint* params);
	int SamplerParameterIiv(GLenum pname, const GLint* params);
	int SamplerParameterIuiv(GLenum pname, const GLuint* params);
	bool IsSampler();
	int DeleteSampler();
	unsigned int ReturnSampler();
	~NGLSampler();

};

#endif
