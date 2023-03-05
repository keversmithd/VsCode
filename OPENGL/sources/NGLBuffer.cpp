#include "NGLBuffer.h"

NGLBuffer::NGLBuffer()
{
	m_buffer = 0;
	m_buffertype = 0;

	bound = false;
	mapped = false;
	invalidated = true;
	deleted = true;
}
int   NGLBuffer::GenerateBuffer()
{
	glGenBuffers(1, &m_buffer);
	GetError
	if (Code) { return 0; }
	deleted = false;
	return 1;

}
int   NGLBuffer::BindBuffer(GLenum m_type)
{
	if (deleted)
	{
		printf("This buffer is deleted and has be to generated again.\n");
		return 0;
	}

	glBindBuffer(m_type, m_buffer);

	GetError
		if (Code) { return 0; }
	
	bound = true;
	m_buffertype = m_type;
	return 1;
}
int   NGLBuffer::BindBufferRange(GLenum target, GLuint index, GLintptr offset, GLsizeiptr size)
{
	if (deleted)
	{
		printf("This buffer is deleted and has be to generated again.\n");
		return 0;
	}

	glBindBufferRange(target, index, m_buffer, offset, size);

	GetError
		if (Code) { return 0; }

	bound = true;
	m_buffertype = target;
	return 1;
}
int   NGLBuffer::BindBufferBase(GLenum target, GLuint index)
{
	if (deleted)
	{
		printf("This buffer is deleted and has be to generated again.\n");
		return 0;
	}

	glBindBufferBase(target, index, m_buffer);
	GetError
		if (Code) { return 0; }

	bound = true;
	m_buffertype = target;
	return 1;

}
int   NGLBuffer::Unbind(GLenum target)
{
	if (deleted)
	{
		printf("This buffer is deleted and has be to generated again.\n");
		return 0;
	}

	glBindBuffer(target, 0);
	GetError
		if (Code) { return 0; }
	bound = false;
	return 1;

}
int   NGLBuffer::BufferData(GLsizeiptr size, const GLvoid* data, GLenum usage)
{
	if (deleted)
	{
		printf("This buffer is deleted and has be to generated again.\n");
		return 0;
	}
	glNamedBufferData(m_buffer, size, data, usage);
	GetError
		if (Code) { return 0; }
	invalidated = false;
	return 1;

}
int   NGLBuffer::BufferDataType(GLenum type, GLsizeiptr size, const GLvoid* data, GLenum usage)
{
	if (deleted)
	{
		printf("This buffer is deleted and has be to generated again.\n");
		return 0;
	}

	if (invalidated == false)
	{
		printf("Buffer is not empty. Invalidating now. \n");
		InvalidateBufferData();
	}

	glBufferData(type, size, data, usage);
	GetError
		if (Code) { return 0; }
	invalidated = false;
	return 1;
}
int   NGLBuffer::BufferStorage(GLsizeiptr size, const GLvoid* data, GLbitfield flags)
{
	if (deleted)
	{
		printf("This buffer is deleted and has be to generated again.\n");
		return 0;
	}

	if (invalidated == false)
	{
		printf("Buffer is not empty. Invalidating now. \n");
		InvalidateBufferData();
		//Should also probably delete.
	}

	glNamedBufferStorage(m_buffer, size, data, flags);

	GetError
		if (Code) { return 0; }
	invalidated = false;
	return 1;

}
int   NGLBuffer::BufferSubData(GLintptr offset, GLsizei size, const void* data)
{

	if (deleted)
	{
		printf("This buffer is deleted and has be to generated again.\n");
		return 0;
	}

	glNamedBufferSubData(m_buffer, offset, size, data);
	GetError
		if (Code) { return 0; }
	invalidated = false;
	return 1;

}
void* NGLBuffer::MapBuffer(GLenum access)
{

	if (deleted)
	{
		printf("This buffer is deleted and has be to generated again.\n");
		return 0;
	}

	if (invalidated)
	{
		printf("Buffer object is not valid, or is invalidated.\n");
		return 0;
	}

	if (mapped)
	{
		//UnmapBuffer(); possibly needs to be unmapped
		printf("Current buffer is still mapped and may be altered from other locations.\n");
	}

	void* map = glMapNamedBuffer(m_buffer, access);

	if (map == nullptr)
	{
		printf("Map pointer was null.\n");
		return 0;
	}

	GetError
		if (Code) { return 0; }
	mapped = true;
	return map;


}
void* NGLBuffer::MapBufferRange(GLintptr offset, GLsizei length, GLbitfield access)
{

	if (deleted)
	{
		printf("This buffer is deleted and has be to generated again.\n");
		return 0;
	}

	if (invalidated)
	{
		printf("Buffer object is not valid, or is invalidated.\n");
		return 0;
	}

	if (mapped)
	{
		void* map = glMapNamedBufferRange(m_buffer, offset, length, access);

		if (map == nullptr)
		{
			printf("Map pointer was null.\n");
			return 0;
		}

		GetError
			if (Code) { return 0; }
		mapped = true;
		return map;
	}

	printf("Buffer is not mapped, and or, is invalidated\n");
	return 0;

}
int   NGLBuffer::FlushMappedBufferRange(GLintptr offset, GLsizei length)
{

	if (deleted)
	{
		printf("This buffer is deleted and has be to generated again.\n");
		return 0;
	}

	if (mapped)
	{
		glFlushMappedNamedBufferRange(m_buffer, offset, length);
		GetError
			if (Code) { return 0; }

		return 1;
	}


	printf("Buffer is not current mapped and cannot be flushed\n");
	return 0;
}
int   NGLBuffer::UnmapBuffer()
{

	if (deleted)
	{
		printf("This buffer is deleted and has be to generated again.\n");
		return 0;
	}

	if (mapped)
	{
		GLboolean mappe = glUnmapNamedBuffer(m_buffer);
		GetError
			if (Code) { return 0; }
		mapped = false;
		return 1;
	}
	


	return 0;
	
}
int   NGLBuffer::CopyBufferSubDataIn(GLuint readBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizei size)
{
	if (deleted)
	{
		printf("This buffer is deleted and has be to generated again.\n");
		return 0;
	}

	if (invalidated)
	{
		printf("Buffer data is invalidated and cannot be copied from or coppied to.\n");
		return 0;
	}

	if (bound)
	{
		glCopyNamedBufferSubData(readBuffer, m_buffer, readOffset, writeOffset, size);
		GetError
			if (Code) { return 0; }
		return 1;
	}

	printf("Buffer has not been bound or has been unbound and should not be interacted with.\n");
	return 0;

}
int   NGLBuffer::CopyBufferSubDataOut(GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizei size)
{

	if (deleted)
	{
		printf("This buffer is deleted and has be to generated again.\n");
		return 0;
	}

	if (invalidated)
	{
		printf("Buffer data is invalidated and cannot be copied from or coppied to.\n");
		return 0;
	}

	if (bound)
	{
		glCopyNamedBufferSubData(m_buffer, writeBuffer, readOffset, writeOffset, size);
		GetError
			if (Code) { return 0; }
		return 1;
	}

	printf("Buffer has not been bound or has been unbound and should not be interacted with.\n");
	return 0;

}
int   NGLBuffer::ClearBufferData(GLenum internalformat, GLenum format, GLenum type, const void* data)
{
	if (deleted)
	{
		printf("This buffer is deleted and has be to generated again.\n");
		return 0;
	}

	if (invalidated)
	{
		printf("Buffer data is invalidated and cannot be copied from or coppied to.\n");
		return 0;
	}
	if (bound)
	{
		glClearNamedBufferData(m_buffer, internalformat, format, type, data);
		GetError
			if (Code) { return 0; }
		return 1;
	}

	printf("Buffer has not been bound or has been unbound and should not be interacted with.\n");
	return 0;

}
int   NGLBuffer::ClearBufferSubData(GLenum internalformat, GLintptr offset, GLsizei size, GLenum format, GLenum type, const void* data)
{

	if (deleted)
	{
		printf("This buffer is deleted and has be to generated again.\n");
		return 0;
	}

	if (invalidated)
	{
		printf("Buffer data is invalidated and cannot be copied from or coppied to.\n");
		return 0;
	}
	if (bound)
	{
		glClearNamedBufferSubData(m_buffer, internalformat, offset, size, format, type, data );
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Buffer has not been bound or has been unbound and should not be interacted with.\n");
	return 0;

}
int   NGLBuffer::InvalidateBufferData()
{

	if (deleted)
	{
		printf("This buffer is deleted and has be to generated again.\n");
		return 0;
	}

	if (invalidated)
	{
		printf("Buffer data is invalidated and cannot be invalidated again.\n");
		return 0;
	}

	if (bound)
	{
		glInvalidateBufferData(m_buffer);
		GetError
			if (Code) { return 0; }
		invalidated = true;
		return 1;
	}

	printf("Buffer has not been bound and cannot be invalidated.\n");

}
int   NGLBuffer::InvalidateSubBufferData(GLintptr offset, GLsizeiptr length)
{

	if (deleted)
	{
		printf("This buffer is deleted and has be to generated again.\n");
		return 0;
	}

	if (invalidated)
	{
		printf("Buffer data is invalidated and cannot be invalidated again.\n");
		return 0;
	}

	if (bound)
	{
		glInvalidateBufferSubData(m_buffer, offset, length);
		GetError
			if (Code) { return 0; }
		return 1;
	}

	printf("Buffer has not been bound and cannot be invalidated.\n");

}
int   NGLBuffer::GetBufferSubData(GLintptr offset, GLsizei size, void* data)
{

	if (deleted)
	{
		printf("This buffer is deleted and has be to generated again.\n");
		return 0;
	}

	if (invalidated)
	{
		printf("Buffer data is invalidated and cannot be invalidated again.\n");
		return 0;
	}

	if (bound)
	{
		glGetNamedBufferSubData(m_buffer, offset, size, data);
		
		GetError
			if (Code) { return 0; }
		return 1;
	}

	printf("Buffer has not been bound and cannot be invalidated.\n");

}
int   NGLBuffer::DeleteBuffer()
{
	if (deleted)
	{
		printf("This buffer is deleted and has be to generated again.\n");
		return 0;
	}

	glDeleteBuffers(1, &m_buffer);
	GetError
		if (Code) { return 0; }
	deleted = true;
	return 1;
	
}
int   NGLBuffer::GetBufferParameteriv(GLenum pname, GLint* params)
{

	if (deleted)
	{
		printf("This buffer is deleted and has be to generated again.\n");
		return 0;
	}

	glGetNamedBufferParameteriv(m_buffer, pname, params);
	GetError
		if (Code) { return 0; }
	return 1;
}
int   NGLBuffer::GetBufferParameteri64v(GLenum pname, GLint64* params) 
{
	if (deleted)
	{
		printf("This buffer is deleted and has be to generated again.\n");
		return 0;
	}

	glGetNamedBufferParameteri64v(m_buffer, pname, params);
	GetError
		if (Code) { return 0; }
	return 1;
}
int   NGLBuffer::GetBufferPointerv(GLenum pname, void** params)
{
	if (deleted)
	{
		printf("This buffer is deleted and has be to generated again.\n");
		return 0;
	}

	glGetNamedBufferPointerv(m_buffer, pname, params);
	GetError
		if (Code) { return 0; }
	return 1;



}
bool  NGLBuffer::IsBuffer()
{
	GLboolean isBuffer = glIsBuffer(m_buffer);
	return isBuffer;
}
bool  NGLBuffer::Bound()
{
	return bound;
}
void  NGLBuffer::SetDeleted(bool status)
{
	deleted = status;
}
bool  NGLBuffer::Mapped()
{
	return mapped;
}
bool  NGLBuffer::Invalidated()
{
	return invalidated;
}
bool  NGLBuffer::Deleted()
{
	return deleted;
}
unsigned int NGLBuffer::ReturnBuffer()
{
	return m_buffer;
}
unsigned int& NGLBuffer::ReferenceBuffer()
{
	return m_buffer;
}
unsigned int* NGLBuffer::PointToBuffer()
{
	return &m_buffer;
}
NGLBuffer::~NGLBuffer()
{
	InvalidateBufferData();
	UnmapBuffer();
	DeleteBuffer();
}
