#include "DynamicQuantityVertexDrawing.h"

DynamicQuantityVertexBuffer::DynamicQuantityVertexBuffer(size_t size) : dynabuffer(0)
{
	Size = size;
}

void DynamicQuantityVertexBuffer::InitialGeneration()
{
	glGenBuffers(1, &dynabuffer);
}

void DynamicQuantityVertexBuffer::InitialBinding()
{
	glBindBuffer(GL_ARRAY_BUFFER, dynabuffer);
}

void DynamicQuantityVertexBuffer::InitialDataAllocation()
{
	glBufferData(GL_ARRAY_BUFFER, Size, nullptr, GL_DYNAMIC_DRAW);
}

void DynamicQuantityVertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void DynamicQuantityVertexBuffer::InvalidateDynabuffer()
{
	glInvalidateBufferData(dynabuffer);
}
void DynamicQuantityVertexBuffer::DeleteBuffer()
{
	glDeleteBuffers(1, &dynabuffer);
}
void DynamicQuantityVertexBuffer::RegenerateBuffer()
{
	glGenBuffers(1, &dynabuffer);
}
void DynamicQuantityVertexBuffer::AllocateData(const void* data)
{
	glBufferData(GL_ARRAY_BUFFER, Size, data, GL_DYNAMIC_DRAW);
}
void DynamicQuantityVertexBuffer::AllocateSubData(const void* data, size_t size)
{
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
}
void DynamicQuantityVertexBuffer::UpdateData(void* data, size_t size)
{
	if (size > Size)
	{
		Size = size;
		InvalidateDynabuffer();
		DeleteBuffer();
		RegenerateBuffer();
		InitialBinding();
		AllocateData(data);
		Unbind();
	}
	else
	{
		InvalidateDynabuffer();
		InitialBinding();
		AllocateSubData(data, size);
		Unbind();
	}
}