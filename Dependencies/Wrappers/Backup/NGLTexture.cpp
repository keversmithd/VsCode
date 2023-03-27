#include "NGLTexture.h"

NGLTexture::NGLTexture()
{
	m_texture = 0;
	created = false;
	m_textype = 0;
	m_textureUnit = 0;
	allocated = false;
}
int NGLTexture::GenerateTexture()
{
	if (created)
	{
		NGLStateError("Texture has already been generated, delete this object to regenerate.\n");
		return 0;
	}
	glGenTextures(1, &m_texture);
	GetError
		if (Code) { return 0; }
	created = true;
	return 1;

}
int NGLTexture::BindTexture(GLenum target)
{
	if (created)
	{
		glBindTexture(target, m_texture);
		GetError
			if (Code) { return 0; }
		
		m_textype = target;
		return 1;
	}
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}
int NGLTexture::BindTextureUnit(GLuint unit)
{
	if (created)
	{
		glBindTextureUnit(unit, m_texture);
		
		GetError
			if (Code) { return 0; }

		m_textureUnit = unit;
		
		return 1;
	}
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}
int NGLTexture::DeleteTexture()
{
	if (created)
	{
		glDeleteTextures(1, &m_texture);
		GetError
			if (Code) { return 0; }
		created = false;
		return 1;
	}
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}

int NGLTexture::ClearTexImage(GLint level, GLenum format, GLenum type, const void* data)
{
	if (created)
	{
		glClearTexImage(m_texture, level,
			format,
			type,
			data
		);
		GetError
			if (Code) { return 0; }
		
		return 1;
	}
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}
int NGLTexture::ClearTexSubImage(GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* data)
{
	if (created)
	{
		glClearTexSubImage(m_texture, level,
			xoffset,
			yoffset,
			zoffset,
			width,
			height,
			depth,
			format,
			type,
			data
		);
		GetError
			if (Code) { return 0; }
		
		return 1;
	}
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}

int NGLTexture::CompressedTexImage1D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const GLvoid* data)
{
	if (created)
	{
		glCompressedTexImage1D(target,
			level,
			internalformat,
			width,
			border,
			imageSize,
			data
		);
		GetError
			if (Code) { return 0; }
		allocated = true;
		return 1;
	}
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}
int NGLTexture::CompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid* data)
{
	if (created)
	{
		glCompressedTexImage2D(target,
			level,
			internalformat,
			width,
			height,
			border,
			imageSize,
			data
		);
		GetError
			if (Code) { return 0; }
		allocated = true;
		return 1;
	}
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}
int NGLTexture::CompressedTexImage3D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid* data)
{
	if (created)
	{
		glCompressedTexImage3D(target,
			level,
			internalformat,
			width,
			height,
			depth,
			border,
			imageSize,
			data
		);
		allocated = true;
		GetError
			if (Code) { return 0; }
		
		return 1;
	}
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}

int NGLTexture::CompressedTexSubImage1D(GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void* data)
{
	if (created)
	{
		glCompressedTextureSubImage1D(m_texture, level, xoffset,
			width,
			format,
			imageSize,
			data
		);
		GetError
			if (Code) { return 0; }
		allocated = true;
		return 1;
	}
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}
int NGLTexture::CompressedTexSubImage2D(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void* data)
{
	if (created)
	{
		glCompressedTexSubImage2D(m_texture, level,
			xoffset,
			yoffset,
			width,
			height,
			format,
			imageSize,
			data
		);
		GetError
			if (Code) { return 0; }
		allocated = true;
		return 1;
	}
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}
int NGLTexture::CompressedTexSubImage3D(GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void* data)
{
	if (created)
	{
		glCompressedTextureSubImage3D(m_texture, level,
			xoffset,
			yoffset,
			zoffset,
			width,
			height,
			depth,
			format,
			imageSize,
			data
		);
		GetError
			if (Code) { return 0; }
		allocated = true;
		return 1;
	}
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}

int NGLTexture::CopyFromImageSubData(GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth)
{
	if (created)
	{
		glCopyImageSubData(m_texture, srcTarget,
			srcLevel,
			srcX,
			srcY,
			srcZ,
			dstName,
			dstTarget,
			dstLevel,
			dstX,
			dstY,
			dstZ,
			srcWidth,
			srcHeight,
			srcDepth
		);
		allocated = true;
		GetError
			if (Code) { return 0; }
		
		return 1;
	}
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}
int NGLTexture::CopyToImageSubData(GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth)
{
	if (created)
	{
		glCopyImageSubData(srcName, srcTarget,
			srcLevel,
			srcX,
			srcY,
			srcZ,
			m_texture,
			dstTarget,
			dstLevel,
			dstX,
			dstY,
			dstZ,
			srcWidth,
			srcHeight,
			srcDepth
		);
		allocated = true;
		GetError
			if (Code) { return 0; }
		
		return 1;
	}
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}
int NGLTexture::CopyTexImage1D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border)
{
	if (created)
	{
		glCopyTexImage1D(target,
			level,
			internalformat,
			x,
			y,
			width,
			border
		);
		
		GetError
			if (Code) { return 0; }
		allocated = true;
		return 1;
	}
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}
int NGLTexture::CopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border)
{
	if (created)
	{
		glCopyTexImage2D(target,
			level,
			internalformat,
			x,
			y,
			width,
			height,
			border
		);
		
		GetError
			if (Code) { return 0; }
		allocated = true;
		return 1;
	}
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;


}

int NGLTexture::CopyTexSubImage1D(GLint level, GLint xoffset, GLint x, GLint y, GLsizei width)
{
	if (created)
	{
		glCopyTexSubImage1D(m_texture, level,
			xoffset,
			x,
			y,
			width);
		GetError
			if (Code) { return 0; }
		allocated = true;
		return 1;
	}
	
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}
int NGLTexture::CopyTexSubImage2D(GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
	if (created)
	{
		glCopyTexSubImage2D(m_texture, level,
			xoffset,
			yoffset,
			x,
			y,
			width,
			height
		);
		GetError
			if (Code) { return 0; }
		allocated = true;
		return 1;
	}
	
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}
int NGLTexture::CopyTexSubImage3D(GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
	if (created)
	{
		glCopyTexSubImage3D(m_texture, level,
			xoffset,
			yoffset,
			zoffset,
			x,
			y,
			width,
			height
		);
		GetError
			if (Code) { return 0; }
		allocated = true;
		return 1;
	}
	
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}

int NGLTexture::GetCompressedTexImage(GLenum target, GLint level, GLvoid* pixels)
{
	if (created)
	{
		glGetCompressedTexImage(target,
			level,
			pixels

		);
		GetError
			if (Code) { return 0; }
		
		return 1;
	}
	
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}
int NGLTexture::GetnCompressedTexImage(GLenum target, GLint level, GLsizei bufSize, GLvoid* pixels)
{
	if (created)
	{
		glGetnCompressedTexImage(target,
			level,
			bufSize,
			pixels
		);
		GetError
			if (Code) { return 0; }
		
		return 1;
	}
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}
int NGLTexture::GetCompressedTextureImage(GLint level, GLsizei bufSize, void* pixels)
{
	if (created)
	{
		glGetnCompressedTexImage(m_texture, level,
			bufSize,
			pixels
		);
		GetError
			if (Code) { return 0; }
		
		return 1;
	}
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}

int NGLTexture::GetCompressedTextureSubImage(GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei bufSize, void* pixels)
{
	if (created)
	{
		glGetCompressedTextureSubImage(m_texture, level,
			xoffset,
			yoffset,
			zoffset,
			width,
			height,
			depth,
			bufSize,
			pixels
		);
		GetError
			if (Code) { return 0; }
		
		return 1;
	}
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}
int NGLTexture::GetTexImage(GLenum target, GLint level, GLenum format, GLenum type, GLvoid* pixels)
{
	if (created)
	{
		glGetTexImage(target,
			level,
			format,
			type,
			pixels
		);
		GetError
			if (Code) { return 0; }
		
		return 1;
	}
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}
int NGLTexture::GetnTexImage(GLenum target, GLint level, GLenum format, GLenum type, GLsizei bufSize, void* pixels)
{
	if (created)
	{
		glGetnTexImage(target,
			level,
			format,
			type,
			bufSize,
			pixels
		);
		GetError
			if (Code) { return 0; }
		
		return 1;
	}
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}
int NGLTexture::GetTextureImage(GLint level, GLenum format, GLenum type, GLsizei bufSize, void* pixels)
{
	if (created)
	{
		if (IsTexture())
		{
			glGetTextureImage(m_texture, level, format, type, bufSize, pixels);
			GetError
				if (Code) { return 0; }
			
			return 1;
		}
	}
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}

int NGLTexture::GetTextureLevelParameterfv(GLint level, GLenum pname, GLfloat* params)
{
	if (created)
	{
		glGetTextureLevelParameterfv(m_texture, level,
			pname,
			params
		);
		GetError
			if (Code) { return 0; }
		
		return 1;
	}
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}
int NGLTexture::GetTextureLevelParameteriv(GLint level, GLenum pname, GLint* params)
{
	if (created)
	{
		glGetTextureLevelParameteriv(m_texture, level,
			pname,
			params
		);
		GetError
			if (Code) { return 0; }
		
		return 1;
	}
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}

int NGLTexture::GetTextureParameterfv(GLenum pname, GLfloat* params)
{
	if (created)
	{
		glGetTextureParameterfv(m_texture,
			pname,
			params
		);
		GetError
			if (Code) { return 0; }
		
		return 1;
	}
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}
int NGLTexture::GetTextureParameteriv(GLenum pname, GLint* params)
{
	if (created)
	{
		glGetTextureParameteriv(m_texture,
			pname,
			params
		);
		GetError
			if (Code) { return 0; }
		
		return 1;
	}
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}
int NGLTexture::GetTextureParameterIiv(GLenum pname, GLint* params)
{
	if (created)
	{
		glGetTextureParameterIiv(m_texture,
			pname,
			params
		);
		GetError
			if (Code) { return 0; }
		
		return 1;
	}
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}
int NGLTexture::GetTextureParameterIuiv(GLenum pname, GLuint* params)
{
	if (created)
	{
		glGetTextureParameterIuiv(m_texture,
			pname,
			params
		);
		GetError
			if (Code) { return 0; }
		
		return 1;
	}
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}

int NGLTexture::GetTextureSubImage(GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLsizei bufSize, void* pixels)
{
	if (created)
	{
		glGetTextureSubImage(m_texture,
			level,
			xoffset,
			yoffset,
			zoffset,
			width,
			height,
			depth,
			format,
			type,
			bufSize,
			pixels
		);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}

int NGLTexture::InvalidateTexImage(GLint level)
{
	if (created)
	{
		glInvalidateTexImage(m_texture,level);
		GetError
			if (Code) { return 0; }
		allocated = false;
		return 1;
	}
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}
int NGLTexture::InvalidateTexSubImage(GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth)
{
	if (created)
	{
		glInvalidateTexSubImage(m_texture, level,xoffset, yoffset, zoffset, width, height, depth);
		GetError
			if (Code) { return 0; }
		
		return 1;
	}
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}

bool NGLTexture::IsTexture()
{
	bool isTex = glIsTexture(m_texture);
	return isTex;
}

int NGLTexture::TexBuffer(GLenum internalformat, GLuint buffer)
{
	if (created)
	{
		glTextureBuffer(m_texture,  internalformat, buffer);
		GetError
			if (Code) { return 0; }
		
		return 1;
	}
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}
int NGLTexture::TexBufferRange(GLenum internalformat, GLuint buffer, GLintptr offset, GLsizei size)
{
	if (created)
	{
		glTextureBufferRange(m_texture, internalformat,
			buffer,
			offset,
			size
		);
		GetError
			if (Code) { return 0; }
		
		return 1;
	}
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}

int NGLTexture::TexImage1D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid* data)
{
	if (created)
	{
		glTexImage1D(target,
			level,
			internalFormat,
			width,
			border,
			format,
			type,
			data
		);
		GetError
			if (Code) { return 0; }
		allocated = true;
		return 1;
	}
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}
int NGLTexture::TexImage2D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* data)
{
	if (created)
	{
		glTexImage2D(target,
			level,
			internalFormat,
			width,
			height,
			border,
			format,
			type,
			data
		);
		
		GetError
			if (Code) { return 0; }
		allocated = true;
		return 1;
	}
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}
int NGLTexture::TexImage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
{
	if (created)
	{
		glTexImage2DMultisample(target,
			samples,
			internalformat,
			width,
			height,
			fixedsamplelocations
		);
		
		GetError
			if (Code) { return 0; }
		allocated = true;
		return 1;
	}
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}
int NGLTexture::TexImage3D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid* data)
{
	if (created)
	{
		glTexImage3D(target,
			level,
			internalFormat,
			width,
			height,
			depth,
			border,
			format,
			type,
			data
		);
		GetError
			if (Code) { return 0; }
		allocated = true;
		return 1;
	}
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}
int NGLTexture::TexImage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations)
{
	if (created)
	{
		glTexImage3DMultisample(target,
			samples,
			internalformat,
			width,
			height,
			depth,
			fixedsamplelocations
		);
		GetError
			if (Code) { return 0; }
		allocated = true;
		return 1;
	}
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}

int NGLTexture::TextureParameterf(GLenum pname, GLfloat param)
{
	if (created)
	{
		glTextureParameterf(m_texture, pname,
			param
		);
		GetError
			if (Code) { return 0; }
		
		return 1;
	}
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}
int NGLTexture::TextureParameteri(GLenum pname, GLint param)
{
	if (created)
	{
		glTextureParameteri(m_texture, pname,
			param
		);
		GetError
			if (Code) { return 0; }
		
		return 1;
	}
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}
int NGLTexture::TextureParameterfv(GLenum pname, const GLfloat* paramtexture)
{

	if (created)
	{
		glTextureParameterfv(m_texture, pname,
			paramtexture
		);
		GetError
			if (Code) { return 0; }
		
		return 1;
	}
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}
int NGLTexture::TextureParameteriv(GLenum pname, const GLint* param)
{
	if (created)
	{
		glTextureParameteriv(m_texture, pname,
			param
		);
		GetError
			if (Code) { return 0; }
		
		return 1;
	}
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}
int NGLTexture::TextureParameterIiv(GLenum pname, const GLint* params) 
{
	if (created)
	{
		glTextureParameterIiv(m_texture, pname,
			params
		);
		GetError
			if (Code) { return 0; }
		
		return 1;
	}
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}
int NGLTexture::TextureParameterIuiv(GLenum pname, const GLuint* params)
{
	if (created)
	{
		glTextureParameterIuiv(m_texture, pname,
			params
		);
		GetError
			if (Code) { return 0; }
		
		return 1;
	}
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}

int NGLTexture::TexStorage1D(GLsizei levels, GLenum internalformat, GLsizei width)
{
	if (created)
	{
		glTexStorage1D(m_texture, levels,
			internalformat,
			width
		);
		GetError
			if (Code) { return 0; }
		allocated = true;
		return 1;
	}
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}
int NGLTexture::TexStorage2D(GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height)
{
	if (created)
	{
		glTexStorage2D(m_texture, levels,
			internalformat,
			width,
			height
		);
		GetError
			if (Code) { return 0; }
		allocated = true;
		return 1;
	}
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}
int NGLTexture::TexStorage2DMultisample(GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
{
	if (created)
	{
		glTexStorage2DMultisample(m_texture, samples,
			internalformat,
			width,
			height,
			fixedsamplelocations
		);
		GetError
			if (Code) { return 0; }
		allocated = true;
		return 1;
	}
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}
int NGLTexture::TexStorage3D(GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth)
{
	if (created)
	{
		glTexStorage3D(m_texture, levels,
			internalformat,
			width,
			height,
			depth
		);
		GetError
			if (Code) { return 0; }
		allocated = true;
		return 1;
	}
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}
int NGLTexture::TexStorage3DMultisample(GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations)
{
	if (created)
	{
		glTexStorage3DMultisample(m_texture, samples,
			internalformat,
			width,
			height,
			depth,
			fixedsamplelocations
		);
		GetError
			if (Code) { return 0; }
		allocated = true;
		return 1;
	}
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}

int NGLTexture::TexSubImage1D(GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void* pixels)
{
	if (created)
	{
		glTextureSubImage1D(m_texture, level,
			xoffset,
			width,
			format,
			type,
			pixels
		);
		GetError
			if (Code) { return 0; }
		allocated = true;
		return 1;
	}
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}
int NGLTexture::TexSubImage2D(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels)
{
	if (created)
	{
		glTextureSubImage2D(m_texture, level,
			xoffset,
			yoffset,
			width,
			height,
			format,
			type,
			pixels
		);
		GetError
			if (Code) { return 0; }
		allocated = true;
		return 1;
	}
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}
int NGLTexture::TexSubImage3D(GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* pixels)
{
	if (created)
	{
		glTexSubImage3D(m_texture, level,
			xoffset,
			yoffset,
			zoffset,
			width,
			height,
			depth,
			format,
			type,
			pixels
		);
		GetError
			if (Code) { return 0; }
		allocated = true;
		return 1;
	}
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}

int NGLTexture::TextureView(GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers)
{
	if (created)
	{
		glTextureView(m_texture, target,
			origtexture,
			internalformat,
			minlevel,
			numlevels,
			minlayer,
			numlayers
		);
		GetError
			if (Code) { return 0; }
		
		return 1;
	}
	NGLStateError("Texture has not been created, and cannot be edited.\n");
	return 0;
}

unsigned int NGLTexture::ReturnTexture()
{
	return m_texture;
}
unsigned int& NGLTexture::ReferenceTexture()
{
	return m_texture;
}

NGLTexture::~NGLTexture()
{
	DeleteTexture();
}