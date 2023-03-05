#include "NGLFramebuffer.h"

NGLFramebuffer::NGLFramebuffer()
{
	m_framebuffer = 0;
	created = false;
}
int NGLFramebuffer::GenerateFramebuffer()
{
	if (created)
	{
		NGLStateError("Framebuffer previously created, delete in order to recreate\n");
		return 0;
	}
	glGenFramebuffers(1, &m_framebuffer);
	GetError
		if (Code) { return 0; }
	created = true;
	return 1;

}
int NGLFramebuffer::BindFramebuffer(GLenum target)
{
	if (target != GL_FRAMEBUFFER && target != GL_READ_FRAMEBUFFER && target != GL_DRAW_FRAMEBUFFER)
	{
		return 0;
	}
	if (created)
	{
		glBindFramebuffer(target, m_framebuffer);
		GetError
			if (Code) { return 0; }
		return 1;

	}
	NGLStateError("Framebuffer is not currently active, generate in order to edit.\n");
	return 0;
}
int NGLFramebuffer::UnbindFramebuffer(GLenum target)
{
	if (target != GL_FRAMEBUFFER && target != GL_READ_FRAMEBUFFER && target != GL_DRAW_FRAMEBUFFER)
	{
		return 0;
	}
	if (created)
	{
		glBindFramebuffer(target, 0);
		GetError
			if (Code) { return 0; }
		return 1;

	}
	NGLStateError("Framebuffer is not currently active, generate in order to edit.\n");
	return 0;
}
int NGLFramebuffer::BlitNamedFramebuffer(GLuint readFramebuffer, GLuint drawFramebuffer, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter)
{
	if (created)
	{
		glBlitNamedFramebuffer(readFramebuffer, drawFramebuffer, srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter );
		GetError
			if (Code) { return 0; }
		return 1;

	}
	NGLStateError("Framebuffer is not currently active, generate in order to edit.\n");
	return 0;
}
GLenum NGLFramebuffer::CheckFramebufferStatus(GLenum target)
{
	if (target != GL_FRAMEBUFFER && target != GL_READ_FRAMEBUFFER && target != GL_DRAW_FRAMEBUFFER)
	{
		return 0;
	}
	if (created)
	{
		GLenum frameBufferStatus = glCheckNamedFramebufferStatus(m_framebuffer, target);
		GetError
			if (Code) { return 0; }
		if (frameBufferStatus != GL_FRAMEBUFFER_COMPLETE) { return 0; }
		return frameBufferStatus;

	}
	NGLStateError("Framebuffer is not currently active, generate in order to edit.\n");
	return 0;
}
int NGLFramebuffer::DeleteFramebuffer()
{
	if (created)
	{
		glDeleteFramebuffers(1, &m_framebuffer);
		GetError
			if (Code) { return 0; }
		created = false;
		return 1;
	}
	NGLStateError("Frame buffer is not currently active, generate in order to edit\n");
	return 0;
}
int NGLFramebuffer::NamedFramebufferDrawBuffers(int n, const GLenum* buffers)
{
	if (created)
	{
		glNamedFramebufferDrawBuffers(m_framebuffer, n, buffers);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	NGLStateError("Framebuffer is not currently active, generate in order to edit.\n");
	return 0;
}
int NGLFramebuffer::NamedFramebufferDrawBuffer(GLenum buf)
{
	if (created)
	{
		glNamedFramebufferDrawBuffer(m_framebuffer, buf);
		GetError
			if (Code) { return 0; }
		return 0;

	}
	NGLStateError("Framebuffer is not currently active, generate in order to edit.\n");
	return 0;
}
int NGLFramebuffer::FramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint level)
{
	if (created)
	{
		glFramebufferTexture( target,
			 attachment,
			 texture,
			level);
		GetError
			if (Code) { return 0; }
		return 0;

	}
	NGLStateError("Framebuffer is not currently active, generate in order to edit.\n");
	return 0;
}
int NGLFramebuffer::FramebufferTexture1D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
{
	if (created)
	{
		glFramebufferTexture1D(target,
			attachment,
			textarget,
			texture,
			level);
		GetError
			if (Code) { return 0; }
		return 0;

	}
	NGLStateError("Framebuffer is not currently active, generate in order to edit.\n");
	return 0;
}
int NGLFramebuffer::FramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
{
	if (created)
	{
		glFramebufferTexture2D(target,
			attachment,
			textarget,
			texture,
			level);
		GetError
			if (Code) { return 0; }
		return 0;

	}
	NGLStateError("Framebuffer is not currently active, generate in order to edit.\n");
	return 0;
}
int NGLFramebuffer::FramebufferTexture3D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint layer)
{
	if (created)
	{
		glFramebufferTexture3D(target,
			attachment,
			textarget,
			texture,
			level, layer);
		GetError
			if (Code) { return 0; }
		return 0;

	}
	NGLStateError("Framebuffer is not currently active, generate in order to edit.\n");
	return 0;
}
int NGLFramebuffer::NamedFramebufferTexture(GLenum attachment, GLuint texture, GLint level)
{
	if (created)
	{
		glNamedFramebufferTexture(m_framebuffer, attachment, texture, level);
		GetError
			if (Code) { return 0; }
		return 1;

	}
	NGLStateError("Framebuffer is not currently active, generate in order to edit.\n");
	return 0;
}
int NGLFramebuffer::NamedFramebufferTextureLayer(GLenum attachment, GLuint texture, GLint level, GLint layer)
{
	if (created)
	{
		glNamedFramebufferTextureLayer(m_framebuffer, attachment, texture, level, layer);
		GetError
			if (Code) { return 0; }
		return 0;

	}
	NGLStateError("Framebuffer is not currently active, generate in order to edit.\n");
	return 0;
}
int NGLFramebuffer::GetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint* params)
{
	if (created)
	{
		glGetFramebufferAttachmentParameteriv(target, attachment, pname, params);
		GetError
			if (Code) { return 0; }
		return 0;

	}
	NGLStateError("Framebuffer is not currently active, generate in order to edit.\n");
	return 0;
}
int NGLFramebuffer::GetNamedFramebufferAttachmentParameteriv(GLuint framebuffer, GLenum attachment, GLenum pname, GLint* params)
{
	if (created)
	{
		glGetNamedFramebufferAttachmentParameteriv(framebuffer, attachment, pname, params);
		GetError
			if (Code) { return 0; }
		return 0;

	}
	NGLStateError("Framebuffer is not currently active, generate in order to edit.\n");
	return 0;
}
int NGLFramebuffer::GetFramebufferParameteriv(GLenum target, GLenum pname, GLint* params)
{
	if (created)
	{
		glGetFramebufferParameteriv(target, pname, params);
		GetError
			if (Code) { return 0; }
		return 0;

	}
	NGLStateError("Framebuffer is not currently active, generate in order to edit.\n");
	return 0;
}
int NGLFramebuffer::GetNamedFramebufferParameteriv(GLenum pname, GLint* param)
{
	if (created)
	{
		glGetNamedFramebufferParameteriv(m_framebuffer, pname, param);
		GetError
			if (Code) { return 0; }
		return 0;

	}
	NGLStateError("Framebuffer is not currently active, generate in order to edit.\n");
	return 0;
}
int NGLFramebuffer::InvalidateFramebuffer(GLenum target, GLsizei numAttachments, const GLenum* attachments)
{
	if (created)
	{
		glInvalidateFramebuffer(target, numAttachments, attachments);
		GetError
			if (Code) { return 0; }
		return 0;

	}
	NGLStateError("Framebuffer is not currently active, generate in order to edit.\n");
	return 0;
}
int NGLFramebuffer::InvalidateNamedFramebufferData(GLsizei numAttachments, const GLenum* attachments)
{
	if (created)
	{
		glInvalidateNamedFramebufferData(m_framebuffer, numAttachments, attachments);
		GetError
			if (Code) { return 0; }
		return 0;

	}
	NGLStateError("Framebuffer is not currently active, generate in order to edit.\n");
	return 0;
}
int NGLFramebuffer::InvalidateSubFramebuffer(GLenum target, GLsizei numAttachments, const GLenum* attachments, GLint x, GLint y, GLint width, GLint height)
{
	if (created)
	{
		glInvalidateSubFramebuffer(target, numAttachments, attachments, x, y, width, height);
		GetError
			if (Code) { return 0; }
		return 0;

	}
	NGLStateError("Framebuffer is not currently active, generate in order to edit.\n");
	return 0;
}
int NGLFramebuffer::InvalidateNamedFramebufferSubData(GLsizei numAttachments, const GLenum* attachments, GLint x, GLint y, GLsizei width, GLsizei height)
{
	if (created)
	{
		glInvalidateNamedFramebufferSubData(m_framebuffer, numAttachments, attachments, x, y, width, height);
		GetError
			if (Code) { return 0; }
		return 0;

	}
	NGLStateError("Framebuffer is not currently active, generate in order to edit.\n");
	return 0;
}
GLboolean NGLFramebuffer::IsFramebuffer()
{
	GLboolean isfb = glIsFramebuffer(m_framebuffer);
	return isfb;
}
int NGLFramebuffer::SampleMaski(GLuint maskNumber, GLbitfield mask)
{
	
	if (created)
	{
		glSampleMaski(maskNumber, mask);
		GetError
			if (Code) { return 0; }
		return 0;

	}
	NGLStateError("Framebuffer is not currently active, generate in order to edit.\n");
	return 0;
}
int NGLFramebuffer::FramebufferRenderbuffer(GLenum attachment, GLuint rbo)
{

	if (created)
	{
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, rbo);
		GetError
			if (Code) { return 0; }
		return 0;

	}
	NGLStateError("Framebuffer is not currently active, generate in order to edit.\n");
	return 0;
}
unsigned int NGLFramebuffer::ReturnFramebuffer()
{
	return m_framebuffer;
}

NGLFramebuffer::~NGLFramebuffer()
{
	DeleteFramebuffer();
}