#ifndef NMLBUFFTEX
#define NMLBUFFTEX

#include "NGLTexture.h"

#include "NMLDebug.h"


struct NMLBufferTexture : NGLTexture
{
private:
	unsigned int m_unit;
	bool validTexture;
	GLenum m_format;
public:
	NMLBufferTexture();
	int AttachBuffer(unsigned int unit, GLenum format, unsigned int buffer);
	int AttachBufferRange(GLuint bindingunit, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size);

	bool IsSupportedFormat(GLenum format);
	~NMLBufferTexture();


};


#endif
