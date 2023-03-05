#ifndef NGLRENDERER
#define NGLRENDERER
#include "NGLDebug.h"

struct NGLRenderer
{
	NGLRenderer();
	int Clear(GLbitfield mask);
	int ClearBufferiv(GLenum buffer, GLint drawbuffer, const GLint* value);
	int ClearBufferuiv(GLenum buffer, GLint drawbuffer, const GLuint* value);
	int ClearBufferfv(GLenum buffer, GLint drawbuffer, const GLfloat* value);
	int ClearBufferfi(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
	int ClearNamedFramebufferiv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLint* value);
	int ClearNamedFramebufferuiv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLuint* value);
	int ClearNamedFramebufferfv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, GLfloat* value);
	int ClearNamedFramebufferfi(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLfloat depth, GLint stencil);
	int ClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
	int ClearDepth(GLdouble depth);
	int ClearDepthf(GLfloat depth);
	int ClearStencil(GLint s);
	int DrawBuffer(GLenum buf);
	int NamedFramebufferDrawBuffer(GLuint framebuffer, GLenum buf);
	int Finish();
	int Flush();
	int ReadBuffer(GLenum mode);
	int NamedFramebufferReadBuffer(GLuint framebuffer, GLenum mode);
	int ReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* data);
	int ReadnPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void* data);
	~NGLRenderer();
};

#endif
