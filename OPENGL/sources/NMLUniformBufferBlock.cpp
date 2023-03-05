#include "NMLUniformBufferBlock.h"

NMLUniformBufferBlock::NMLUniformBufferBlock()
{
	CurrentData = false;
	DefaultGood = false;
	index = 0;
}
int NMLUniformBufferBlock::CreateUniformBufferBlock(GLuint u_index, GLsizeiptr size, const GLvoid* data, GLenum usage)
{
	if (!DefaultGood)
	{
		int GenerationStatus = GenerateBuffer();
		DefaultGood = GenerationStatus;
		if (!GenerationStatus) { return 0; }
	}
	index = u_index;
	UniformBufferData(size, data, usage);
}
int NMLUniformBufferBlock::BindToUnit(GLuint u_index)
{
	if (!DefaultGood)
	{
		DefaultGood = GenerateBuffer();
		if (!DefaultGood) { return 0; }
	}
	index = u_index;
	return 1;
}
int NMLUniformBufferBlock::SetUnit(GLuint u_index)
{
	index = u_index;
	return 1;
}
int NMLUniformBufferBlock::UniformBufferData(GLsizeiptr size, const GLvoid* data, GLenum usage)
{
	if (!CurrentData && DefaultGood)
	{
		if (Bound())
		{
			return BufferData(size, data, usage);
		}
		int BindStatus = BindBufferBase(GL_UNIFORM_BUFFER, index);
		if (BindStatus)
		{
			return BufferData(size, data, usage);
		}
		return 0;
	}
	return 0;
}
int NMLUniformBufferBlock::UniformBufferSubData(GLintptr offset, GLsizei size, const void* data)
{
	if (CurrentData && DefaultGood)
	{
		if (Bound())
		{
			return BufferSubData(offset, size, data);
		}
		int BindStatus = BindBufferBase(GL_UNIFORM_BUFFER, index);
		
		if (BindStatus)
		{
			return BufferSubData(offset, size, data);
		}
		return 0;
	}
	return 0;
}
NMLUniformBufferBlock::~NMLUniformBufferBlock()
{

}