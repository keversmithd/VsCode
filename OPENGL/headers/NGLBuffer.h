#ifndef NGLBUFF
#define NGLBUFF

#include "NGLDebug.h"

struct NGLBuffer
{
private:
	unsigned int m_buffer;
	GLenum       m_buffertype;

	bool         bound;
	bool		 mapped;
	bool         invalidated;
	bool		 deleted;
public:
	             NGLBuffer();
	int          GenerateBuffer();
	int          BindBuffer(GLenum m_type);
	int          BindBufferRange(GLenum target, GLuint index, GLintptr offset, GLsizeiptr size);
	int          BindBufferBase(GLenum target, GLuint index);
	int			 Unbind(GLenum target);
	int          BufferData(GLsizeiptr size, const GLvoid* data, GLenum usage);
	int          BufferDataType(GLenum type, GLsizeiptr size, const GLvoid* data, GLenum usage);
	int          BufferStorage(GLsizeiptr size, const GLvoid* data, GLbitfield flags);
	int          BufferSubData(GLintptr offset, GLsizei size, const void* data);
	void*        MapBuffer(GLenum access);
	void*        MapBufferRange(GLintptr offset, GLsizei length, GLbitfield access);
	int          FlushMappedBufferRange(GLintptr offset, GLsizei length);
	int          UnmapBuffer();
	int          CopyBufferSubDataIn(GLuint readBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizei size);
	int          CopyBufferSubDataOut(GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizei size);
	int          ClearBufferData(GLenum internalformat, GLenum format, GLenum type, const void* data);
	int          ClearBufferSubData(GLenum internalformat, GLintptr offset, GLsizei size, GLenum format, GLenum type, const void* data);
	int          InvalidateBufferData();
	int          InvalidateSubBufferData(GLintptr offset, GLsizeiptr length);
	int          GetBufferSubData(GLintptr offset, GLsizei size, void* data);
	int          DeleteBuffer();
	int          GetBufferParameteriv(GLenum pname, GLint* params);
	int          GetBufferParameteri64v(GLenum pname, GLint64* params);
	int          GetBufferPointerv(GLenum pname, void** params);
	bool         IsBuffer();
	bool		 Bound();
	bool		 Mapped();
	bool		 Invalidated();
	void  SetDeleted(bool status);
	bool		 Deleted();
	unsigned int ReturnBuffer();
	unsigned int& ReferenceBuffer();
	unsigned int* PointToBuffer();
	             ~NGLBuffer();


};


#endif
