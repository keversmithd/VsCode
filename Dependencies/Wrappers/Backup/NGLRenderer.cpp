#include "NGLRenderer.h"



NGLRenderer::NGLRenderer(){}
int NGLRenderer::Clear(GLbitfield mask)
{
	glClear(mask);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLRenderer::ClearBufferiv(GLenum buffer, GLint drawbuffer, const GLint* value)
{
	glClearBufferiv(buffer, drawbuffer, value);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLRenderer::ClearBufferuiv(GLenum buffer, GLint drawbuffer, const GLuint* value)
{
	glClearBufferuiv(buffer, drawbuffer, value);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLRenderer::ClearBufferfv(GLenum buffer, GLint drawbuffer, const GLfloat* value)
{
	glClearBufferfv(buffer, drawbuffer, value);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLRenderer::ClearBufferfi(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil)
{
	glClearBufferfi(buffer, drawbuffer, depth, stencil);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLRenderer::ClearNamedFramebufferiv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLint* value)
{
	glClearNamedFramebufferiv(framebuffer,
		buffer,
		drawbuffer,
		value
	);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLRenderer::ClearNamedFramebufferuiv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLuint* value)
{
	glClearNamedFramebufferuiv(framebuffer,
		buffer,
		drawbuffer,
		value
	);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLRenderer::ClearNamedFramebufferfv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, GLfloat* value)
{
	glClearNamedFramebufferfv(framebuffer, buffer, drawbuffer, value);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLRenderer::ClearNamedFramebufferfi(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLfloat depth, GLint stencil)
{
	glClearNamedFramebufferfi(framebuffer, buffer, drawbuffer, depth, stencil);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLRenderer::ClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
	glClearColor(red, green, blue, alpha);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLRenderer::ClearDepth(GLdouble depth)
{
	glClearDepth(depth);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLRenderer::ClearDepthf(GLfloat depth)
{
	glClearDepthf(depth);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLRenderer::ClearStencil(GLint s)
{
	glClearStencil(s);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLRenderer::DrawBuffer(GLenum buf)
{
	glDrawBuffer(buf);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLRenderer::NamedFramebufferDrawBuffer(GLuint framebuffer, GLenum buf)
{
	glNamedFramebufferDrawBuffer(framebuffer, buf);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLRenderer::Finish()
{
	glFinish();
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLRenderer::Flush()
{
	glFlush();
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLRenderer::ReadBuffer(GLenum mode)
{
	glReadBuffer(mode);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLRenderer::NamedFramebufferReadBuffer(GLuint framebuffer, GLenum mode)
{
	glNamedFramebufferReadBuffer(framebuffer, mode);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLRenderer::ReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* data)
{
	glReadPixels(x,
		y,
		width,
		height,
		format,
		type,
		data
	);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLRenderer::ReadnPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void* data)
{
	glReadnPixels(x,
		y,
		width,
		height,
		format,
		type,
		bufSize,
		data
	);
	GetError
		if (Code) { return 0; }
	return 1;
}
NGLRenderer::~NGLRenderer() 
{
	
}