#include "NMLBufferTexture.h"

NMLBufferTexture::NMLBufferTexture()
{
	m_unit = 0;
	m_format = GL_NONE;
	validTexture = GenerateTexture();
}
int NMLBufferTexture::AttachBuffer(unsigned int unit, GLenum format, unsigned int buffer)
{
	if (!IsSupportedFormat(format)) { NMLStateError("The format specificed while attaching the buffer texture was invalid.\n"); return 0; }
	if (!validTexture) { NMLStateError("The texture for buffer attachment was invalid.\n"); return 0; }
	if (!glIsBuffer(buffer)) { NMLStateError("The buffer is not valid.\n"); return 0; }

	glActiveTexture(GL_TEXTURE0 + unit);
	m_unit = unit;
	m_format = format;
	int BindStatus = BindTexture(GL_TEXTURE_BUFFER);
	if (!BindStatus) { return 0; }
	int TexBufferStatus = TexBuffer(format, buffer);
}
int NMLBufferTexture::AttachBufferRange(GLuint bindingunit, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size)
{
	if (!IsSupportedFormat(internalformat)) { NMLStateError("The format specificed while attaching the buffer texture was invalid.\n"); return 0; }
	if (!validTexture) { NMLStateError("The texture for buffer attachment was invalid.\n"); return 0; }
	if (!glIsBuffer(buffer)) { NMLStateError("The buffer is not valid.\n"); return 0; }

	glBindBuffer(GL_DRAW_INDIRECT_BUFFER, buffer);
	GLint bufferSize;
	glGetBufferParameteriv(GL_DRAW_INDIRECT_BUFFER, GL_BUFFER_SIZE, &bufferSize);
	glBindBuffer(GL_DRAW_INDIRECT_BUFFER, 0);
	GLint alignment;
	glGetTexParameteriv(GL_TEXTURE_BUFFER, GL_TEXTURE_BUFFER_OFFSET_ALIGNMENT, &alignment);

	GetError
		if (Code) { return 0; }

	if (offset % alignment != 0)
	{
		NMLStateError("Offset into texture buffer was not an integer multiple of texture offset alignment.\n");
		return 0;
	}
	
	if (offset < 0 || size <= 0 || offset + size > bufferSize)
	{
		TexBufferRange(internalformat, buffer, offset, size);
	}
	else
	{
		return 0;
	}
	
}

bool NMLBufferTexture::IsSupportedFormat(GLenum format)
{
	return (1 * (format == GL_R8)) + (1 * (format == GL_R16)) + (1 * (format == GL_R16F)) + (1 * (format == GL_R32F)) + (1 * (format == GL_R8I)) + (1 * (format == GL_R16I)) + (1 * (format == GL_R32I)) + (1 * (format == GL_R8UI)) + (1 * (format == GL_R16UI)) + (1 * (format == GL_R32UI)) + (1 * (format == GL_RG8)) + (1 * (format == GL_RG16)) + (1 * (format == GL_RG16F)) + (1 * (format == GL_RG32F)) + (1 * (format == GL_RG8I)) + (1 * (format == GL_RG16I)) + (1 * (format == GL_RG32I)) + (1 * (format == GL_RG8UI)) + (1 * (format == GL_RG16UI)) + (1 * (format == GL_RG32UI)) + (1 * (format == GL_RGB32F)) + (1 * (format == GL_RGB32I)) + (1 * (format == GL_RGB32UI)) + (1 * (format == GL_RGBA8)) + (1 * (format == GL_RGBA16)) + (1 * (format == GL_RGBA16F)) + (1 * (format == GL_RGBA32F)) + (1 * (format == GL_RGBA8I)) + (1 * (format == GL_RGBA16I)) + (1 * (format == GL_RGBA32I)) + (1 * (format == GL_RGBA8UI)) + (1 * (format == GL_RGBA16UI));
}
NMLBufferTexture::~NMLBufferTexture()
{
	
}