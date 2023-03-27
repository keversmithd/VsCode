#ifndef NGLFRAMEBUFFER
#define NGLFRAMEBUFFER


#include "NGLDebug.h"


struct NGLFramebuffer
{
private:
	unsigned int m_framebuffer;
	bool created;
public:
	NGLFramebuffer();
	int GenerateFramebuffer();
	int BindFramebuffer(GLenum target);
	int UnbindFramebuffer(GLenum target);
	int BlitNamedFramebuffer(GLuint readFramebuffer, GLuint drawFramebuffer, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
	GLenum CheckFramebufferStatus(GLenum target);
	int DeleteFramebuffer();
	int NamedFramebufferDrawBuffers(int n, const GLenum* buffers);
	int NamedFramebufferDrawBuffer(GLenum buffer);

	int FramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint level);
	int FramebufferTexture1D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
	int FramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
	int FramebufferTexture3D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint layer);
	int NamedFramebufferTexture(GLenum attachment, GLuint texture, GLint level);
	int NamedFramebufferTextureLayer(GLenum attachment, GLuint texture, GLint level, GLint layer);

	int GetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint* params);
	int GetNamedFramebufferAttachmentParameteriv(GLuint framebuffer, GLenum attachment, GLenum pname, GLint* params);

	int GetFramebufferParameteriv(GLenum target, GLenum pname, GLint* params);
	int GetNamedFramebufferParameteriv(GLenum pname, GLint* param);

	int InvalidateFramebuffer(GLenum target, GLsizei numAttachments, const GLenum* attachments);
	int InvalidateNamedFramebufferData(GLsizei numAttachments, const GLenum* attachments);
	int InvalidateSubFramebuffer(GLenum target, GLsizei numAttachments, const GLenum* attachments, GLint x, GLint y, GLint width, GLint height);
	int InvalidateNamedFramebufferSubData(GLsizei numAttachments, const GLenum* attachments, GLint x, GLint y, GLsizei width, GLsizei height);

	GLboolean IsFramebuffer();

	int SampleMaski(GLuint maskNumber, GLbitfield mask);
	int FramebufferRenderbuffer(GLenum attachment, GLuint rbo);
	unsigned int ReturnFramebuffer();
	~NGLFramebuffer();
};

#endif
