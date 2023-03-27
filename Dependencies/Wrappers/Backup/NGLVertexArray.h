#ifndef NGLVERTEXARRAY
#define NGLVERTEXARRAY

#include "NGLDebug.h"

struct NGLVertexArray
{
private:
	unsigned int m_va;
	bool deleted;
public:
	NGLVertexArray();
	int GenerateVertexArray();
	int BindVertexArray();
	int UnbindVertexArray();
	int VertexArrayElementBuffer(GLuint buffer);
	int EnableVertexArrayAttrib(GLuint index);
	int EnableVertexAttribArray(GLuint index);
	int VertexAttrib1f(GLuint index, GLfloat v0);
	int VertexAttrib1s(GLuint index, GLshort v0);
	int VertexAttrib1d(GLuint index, GLdouble v0);
	int VertexAttribI1i(GLuint index, GLint v0);
	int VertexAttribI1ui(GLuint index, GLuint v0);
	int VertexAttrib2f(GLuint index, GLfloat v0, GLfloat v1);
	int VertexAttrib2s(GLuint index, GLshort v0, GLshort v1);
	int VertexAttrib2d(GLuint index, GLdouble v0, GLdouble v1);
	int VertexAttribI2i(GLuint index, GLint v0, GLint v1);
	int VertexAttribI2ui(GLuint index, GLuint v0, GLuint v1);
	int VertexAttrib3f(GLuint index, GLfloat v0, GLfloat v1, GLfloat v2);
	int VertexAttrib3s(GLuint index, GLshort v0, GLshort v1, GLshort v2);
	int VertexAttrib3d(GLuint index, GLdouble v0, GLdouble v1, GLdouble v2);
	int VertexAttribI3i(GLuint index, GLint v0, GLint v1, GLint v2);
	int VertexAttribI3ui(GLuint index, GLuint v0, GLuint v1, GLuint v2);
	int VertexAttrib4f(GLuint index, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
	int VertexAttrib4s(GLuint index, GLshort v0, GLshort v1, GLshort v2, GLshort v3);
	int VertexAttrib4d(GLuint index, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3);
	int VertexAttrib4Nub(GLuint index, GLubyte v0, GLubyte v1, GLubyte v2, GLubyte v3);
	int VertexAttribI4i(GLuint index, GLint v0, GLint v1, GLint v2, GLint v3);
	int VertexAttribI4ui(GLuint index, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
	int VertexAttribL1d(GLuint index, GLdouble v0);
	int VertexAttribL2d(GLuint index, GLdouble v0, GLdouble v1);
	int VertexAttribL3d(GLuint index, GLdouble v0, GLdouble v1, GLdouble v2);
	int VertexAttribL4d(GLuint index, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3);
	int VertexAttrib1fv(GLuint index, const GLfloat* v);
	int VertexAttrib1sv(GLuint index, const GLshort* v);
	int VertexAttrib1dv(GLuint index, const GLdouble* v);
	int VertexAttribI1iv(GLuint index, const GLint* v);
	int VertexAttribI1uiv(GLuint index, const GLuint* v);
	int VertexAttrib2fv(GLuint index, const GLfloat* v);
	int VertexAttrib2sv(GLuint index, const GLshort* v);
	int VertexAttrib2dv(GLuint index, const GLdouble* v);
	int VertexAttribI2iv(GLuint index, const GLint* v);
	int VertexAttribI2uiv(GLuint index, const GLuint* v);
	int VertexAttrib3fv(GLuint index, const GLfloat* v);
	int VertexAttrib3sv(GLuint index, const GLshort* v);
	int VertexAttrib3dv(GLuint index, const GLdouble* v);
	int VertexAttribI3iv(GLuint index, const GLint* v);
	int VertexAttribI3uiv(GLuint index, const GLuint* v);
	int VertexAttrib4fv(GLuint index, const GLfloat* v);
	int VertexAttrib4sv(GLuint index, const GLshort* v);
	int VertexAttrib4dv(GLuint index, const GLdouble* v);
	int VertexAttrib4iv(GLuint index, const GLint* v);
	int VertexAttrib4bv(GLuint index, const GLbyte* v);
	int VertexAttrib4ubv(GLuint index, const GLubyte* v);
	int VertexAttrib4usv(GLuint index, const GLushort* v);
	int VertexAttrib4uiv(GLuint index, const GLuint* v);
	int VertexAttrib4Nbv(GLuint index, const GLbyte* v);
	int VertexAttrib4Nsv(GLuint index, const GLshort* v);
	int VertexAttrib4Niv(GLuint index, const GLint* v);
	int VertexAttrib4Nubv(GLuint index, const GLubyte* v);
	int VertexAttrib4Nusv(GLuint index, const GLushort* v);
	int VertexAttrib4Nuiv(GLuint index, const GLuint* v);
	int VertexAttribI4bv(GLuint index, const GLbyte* v);
	int VertexAttribI4ubv(GLuint index, const GLubyte* v);
	int VertexAttribI4sv(GLuint index, const GLshort* v);
	int VertexAttribI4usv(GLuint index, const GLushort* v);
	int VertexAttribI4iv(GLuint index, const GLint* v);
	int VertexAttribI4uiv(GLuint index, const GLuint* v);
	int VertexAttribL1dv(GLuint index, const GLdouble* v);
	int VertexAttribL2dv(GLuint index, const GLdouble* v);
	int VertexAttribL3dv(GLuint index, const GLdouble* v);
	int VertexAttribL4dv(GLuint index, const GLdouble* v);
	int VertexAttribP1ui(GLuint index, GLenum type, GLboolean normalized, GLuint value);
	int VertexAttribP2ui(GLuint index, GLenum type, GLboolean normalized, GLuint value);
	int VertexAttribP3ui(GLuint index, GLenum type, GLboolean normalized, GLuint value);
	int VertexAttribP4ui(GLuint index, GLenum type, GLboolean normalized, GLuint value);
	int DisableVertexArrayAttrib(GLuint index);
	int VertexArrayAttribBinding(GLuint attribindex, GLuint bindingindex);
	int VertexArrayAttribDivisor(GLuint index, GLuint divisor);
	int VertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
	int VertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer);
	int VertexAttribLPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer);
	bool IsVertexArray();
	int GetVertexArrayiv(GLenum pname, GLint* param);
	int GetVertexArrayIndexediv(GLuint vaobj, GLuint index, GLenum pname, GLint* param);
	int GetVertexArrayIndexed64iv(GLuint vaobj, GLuint index, GLenum pname, GLint64* param);
	GLuint ReturnVertexArray();
	int DeleteVertexArray();
	~NGLVertexArray();

};


#endif
