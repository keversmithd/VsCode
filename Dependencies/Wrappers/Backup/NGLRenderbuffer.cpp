#include "NGLRenderbuffer.h"


NGLRenderbuffer::NGLRenderbuffer()
{
	m_renderbuffer = 0;
	created = false;
}
int NGLRenderbuffer::GenerateRenderbuffer()
{
	if(created)
	{
		NGLStateError("Render buffer object already generated, delete in order to regenerate.\n");
		return 0;
	}
	glGenRenderbuffers(1, &m_renderbuffer);
	GetError
		if (Code) { return 0; }
	created = true;
	return 1;

}
int NGLRenderbuffer::BindRenderbuffer()
{
	if (created)
	{
		glBindRenderbuffer(GL_RENDERBUFFER, m_renderbuffer);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	NGLStateError("Render buffer not created and cannot be edited.\n");
	return 0;

}
int NGLRenderbuffer::DeleteRenderbuffer()
{
	if (created)
	{
		glDeleteRenderbuffers(1, &m_renderbuffer);
		GetError
			if (Code) { return 0; }
		created = false;
		return 1;
	}
	NGLStateError("Render buffer not created and cannot be edited.\n");
	return 0;
}
int NGLRenderbuffer::FramebufferRenderbuffer(GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget)
{
	if (created)
	{
		glNamedFramebufferRenderbuffer(framebuffer, attachment, renderbuffertarget, m_renderbuffer);
		GetError
			if (Code) { return 0; }
		created = false;
		return 1;
	}
	NGLStateError("Render buffer not created and cannot be edited.\n");
	return 0;
}
int NGLRenderbuffer::GetRenderbufferParameteriv(GLenum pname, GLint* params)
{
	glGetNamedRenderbufferParameteriv(m_renderbuffer, pname, params);
	GetError
		if (Code) { return 0; }
	return 1;
}
bool NGLRenderbuffer::IsRenderBuffer()
{
	GLboolean isRenderbBuffer = glIsRenderbuffer(m_renderbuffer);
	return isRenderbBuffer;
}
int NGLRenderbuffer::RenderbufferStorage(GLenum internalformat, GLsizei width, GLsizei height)
{
	if (created)
	{
		glNamedRenderbufferStorage(m_renderbuffer, internalformat, width, height);
		GetError
			if (Code) { return 0; }
		created = false;
		return 1;
	}
	NGLStateError("Render buffer not created and cannot be edited.\n");
	return 0;
}
int NGLRenderbuffer::RenderbufferStorageMultisample(GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height)
{
	if (created)
	{
		glNamedRenderbufferStorageMultisample(m_renderbuffer, samples, internalformat, width, height);
		GetError
			if (Code) { return 0; }
		created = false;
		return 1;
	}
	NGLStateError("Render buffer not created and cannot be edited.\n");
	return 0;
}
int NGLRenderbuffer::Unbind()
{
	if (created)
	{
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	NGLStateError("Render buffer not created and cannot be edited.\n");
	return 0;
}
unsigned int NGLRenderbuffer::ReturnRenderBuffer()
{
	return m_renderbuffer;
}

NGLRenderbuffer::~NGLRenderbuffer()
{
	DeleteRenderbuffer();
}