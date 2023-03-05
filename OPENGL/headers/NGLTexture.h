#ifndef NGLTEX_H
#define NGLTEX_H

#include "NGLDebug.h"

struct NGLTexture
{
private:
	unsigned int m_texture;
	bool created;
	bool allocated;
	GLenum m_textype;
	GLuint m_textureUnit;
public:
	NGLTexture();
	int GenerateTexture();
	int BindTarget(GLenum target);
	int BindTexture(GLenum target);
	int BindTextureUnit(GLuint unit);
	int DeleteTexture();

	int ClearTexImage(GLint level, GLenum format, GLenum type, const void* data);
	int ClearTexSubImage(GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* data);

	int CompressedTexImage1D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const GLvoid* data);
	int CompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid* data);
	int CompressedTexImage3D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid* data);

	int CompressedTexSubImage1D(GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void* data);
	int CompressedTexSubImage2D(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void* data);
	int CompressedTexSubImage3D(GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void* data);

	int CopyFromImageSubData(GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth);
	int CopyToImageSubData(GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth);

	int CopyTexImage1D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border);

	int CopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);

	int CopyTexSubImage1D(GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
	int CopyTexSubImage2D(GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
	int CopyTexSubImage3D(GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);

	int GetCompressedTexImage(GLenum target, GLint level, GLvoid* pixels);
	int GetnCompressedTexImage(GLenum target, GLint level, GLsizei bufSize, GLvoid* pixels);
	int GetCompressedTextureImage(GLint level, GLsizei bufSize, void* pixels);
	int GetCompressedTextureSubImage(GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei bufSize, void* pixels);


	int GetTexImage(GLenum target, GLint level, GLenum format, GLenum type, GLvoid* pixels);
	int GetnTexImage(GLenum target, GLint level, GLenum format, GLenum type, GLsizei bufSize, void* pixels);
	int GetTextureImage(GLint level, GLenum format, GLenum type, GLsizei bufSize, void* pixels);

	int GetTextureLevelParameterfv(GLint level, GLenum pname, GLfloat* params);
	int GetTextureLevelParameteriv(GLint level, GLenum pname, GLint* params);

	int GetTextureParameterfv(GLenum pname, GLfloat* params);
	int GetTextureParameteriv(GLenum pname, GLint* params);
	int GetTextureParameterIiv(GLenum pname, GLint* params);
	int GetTextureParameterIuiv(GLenum pname, GLuint* params);

	int GetTextureSubImage(GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLsizei bufSize, void* pixels);

	int InvalidateTexImage(GLint level);
	int InvalidateTexSubImage(GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth);

	bool IsTexture();

	int TexBuffer(GLenum internalformat, GLuint buffer);
	int TexBufferRange(GLenum internalformat, GLuint buffer, GLintptr offset, GLsizei size);
	
	int TexImage1D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid* data);
	int TexImage2D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* data);
	int TexImage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
	int TexImage3D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid* data);
	int TexImage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);


	int TextureParameterf(GLenum pname, GLfloat param);
	int TextureParameteri(GLenum pname, GLint param);
	int TextureParameterfv(GLenum pname, const GLfloat* paramtexture);
	int TextureParameteriv(GLenum pname, const GLint* param);
	int TextureParameterIiv(GLenum pname, const GLint* params);
	int TextureParameterIuiv(GLenum pname, const GLuint* params);

	
	int TexStorage1D(GLsizei levels, GLenum internalformat, GLsizei width);
	int TexStorage2D(GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
	int TexStorage2DMultisample(GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
	int TexStorage3D(GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
	int TexStorage3DMultisample(GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);

	int TexSubImage1D(GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void* pixels);
	int TexSubImage2D(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels);
	int TexSubImage3D(GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* pixels);

	int TextureView(GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);

	unsigned int ReturnTexture();
	unsigned int& ReferenceTexture();

	~NGLTexture();
};

#endif
