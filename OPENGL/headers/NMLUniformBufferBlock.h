#ifndef NMLUNIFORMBUFFER
#define NMLUNIFORMBUFFER

#include "NGLBuffer.h"

struct NMLUniformBufferBlock : NGLBuffer
{
private:
	bool CurrentData;
	bool DefaultGood;
	GLuint index;
public:
	NMLUniformBufferBlock();
	int CreateUniformBufferBlock(GLuint index, GLsizeiptr size, const GLvoid* data, GLenum usage);
	int BindToUnit(GLuint index);
	int SetUnit(GLuint index);
	int UniformBufferData(GLsizeiptr size, const GLvoid* data, GLenum usage);
	int UniformBufferSubData(GLintptr offset, GLsizei size, const void* data);
	~NMLUniformBufferBlock();
};


#endif
