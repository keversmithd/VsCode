#ifndef __FUNCTION__ 
 #define __FUNCTION__ 
 #endif
#ifndef NGLRENDERBUFFER
#define NGLRENDERBUFFER

#include "NGLDebug.h"

struct NGLRenderbuffer
{
private:
	unsigned int m_renderbuffer;
	bool created;
public:
	NGLRenderbuffer();
	int GenerateRenderbuffer();
	int BindRenderbuffer();
	int DeleteRenderbuffer();
	int FramebufferRenderbuffer(GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget);
	int GetRenderbufferParameteriv(GLenum pname, GLint* params);
	bool IsRenderBuffer();
	int RenderbufferStorage(GLenum internalformat, GLsizei width, GLsizei height);
	int RenderbufferStorageMultisample( GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
	int Unbind();
	unsigned int ReturnRenderBuffer();
	~NGLRenderbuffer();


};

#endif