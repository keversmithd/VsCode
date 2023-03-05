#include "NGLVertexArray.h"


NGLVertexArray::NGLVertexArray() 
{
	m_va = 0;
	deleted = true;
}
int NGLVertexArray::GenerateVertexArray()
{
	if (deleted)
	{
		glGenVertexArrays(1, &m_va);
		GetError
			if (Code) { return 0; }
		deleted = false;
		return 1;
	}

	printf("Vertex array is no deleted, delete before regenerating.\n");
	return 0;
}
int NGLVertexArray::BindVertexArray()
{
	if (deleted)
	{
		printf("Vertex array is currently deleted, generate before editing. \n");
		Status
		return 0;
	}
	glBindVertexArray(m_va);
	GetError
		if (Code) { return 0; }

	return 1;

}
int NGLVertexArray::UnbindVertexArray()
{
	
	glBindVertexArray(0);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexArrayElementBuffer(GLuint buffer)
{
	if (deleted)
	{
		printf("Vertex array is currently deleted, generate before editing. \n");
		Status
			return 0;
	}
	glVertexArrayElementBuffer(m_va, buffer);
	GetError
		if (Code) { return 0; }

	return 1;
}
int NGLVertexArray::EnableVertexArrayAttrib(GLuint index)
{
	if (deleted)
	{
		printf("Vertex array is currently deleted, generate before editing. \n");
		Status
			return 0;
	}
	glEnableVertexArrayAttrib(m_va, index);
	GetError
		if (Code) { return 0; }

	return 1;

}
int NGLVertexArray::EnableVertexAttribArray(GLuint index)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glEnableVertexAttribArray(index);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttrib1f(GLuint index, GLfloat v0)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttrib1f(index, v0);
	GetError
		if (Code) { return 0; }
	return 1;

}
int NGLVertexArray::VertexAttrib1s(GLuint index, GLshort v0)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttrib1s(index, v0);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttrib1d(GLuint index, GLdouble v0)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttrib1d(index, v0);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttribI1i(GLuint index, GLint v0)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttribI1i(index, v0);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttribI1ui(GLuint index, GLuint v0)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttribI1ui(index, v0);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttrib2f(GLuint index, GLfloat v0, GLfloat v1)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttrib2f(index, v0, v1);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttrib2s(GLuint index, GLshort v0, GLshort v1)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttrib2s(index, v0, v1);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttrib2d(GLuint index, GLdouble v0, GLdouble v1)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttrib2d(index, v0, v1);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttribI2i(GLuint index, GLint v0, GLint v1)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttribI2i(index, v0, v1);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttribI2ui(GLuint index, GLuint v0, GLuint v1)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttribI2ui(index, v0, v1);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttrib3f(GLuint index, GLfloat v0, GLfloat v1, GLfloat v2)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttrib3f(index, v0, v1, v2);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttrib3s(GLuint index, GLshort v0, GLshort v1, GLshort v2)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttrib3s(index, v0, v1, v2);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttrib3d(GLuint index, GLdouble v0, GLdouble v1, GLdouble v2)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttrib3d(index, v0, v1, v2);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttribI3i(GLuint index, GLint v0, GLint v1, GLint v2)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttribI3i(index, v0, v1, v2);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttribI3ui(GLuint index, GLuint v0, GLuint v1, GLuint v2)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttribI3ui(index, v0, v1, v2);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttrib4f(GLuint index, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttrib4f(index, v0, v1, v2, v3);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttrib4s(GLuint index, GLshort v0, GLshort v1, GLshort v2, GLshort v3)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttrib4s(index, v0, v1, v2, v3);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttrib4d(GLuint index, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttrib4d(index, v0, v1, v2, v3);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttrib4Nub(GLuint index, GLubyte v0, GLubyte v1, GLubyte v2, GLubyte v3)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttrib4Nub(index, v0, v1, v2, v3);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttribI4i(GLuint index, GLint v0, GLint v1, GLint v2, GLint v3)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttribI4i(index, v0, v1, v2, v3);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttribI4ui(GLuint index, GLuint v0, GLuint v1, GLuint v2, GLuint v3)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttribI4ui(index, v0, v1, v2, v3);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttribL1d(GLuint index, GLdouble v0)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttribL1d(index, v0);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttribL2d(GLuint index, GLdouble v0, GLdouble v1)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttribL2d(index, v0, v1);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttribL3d(GLuint index, GLdouble v0, GLdouble v1, GLdouble v2)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttribL3d(index, v0, v1, v2);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttribL4d(GLuint index, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttribL4d(index, v0, v1, v2, v3);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttrib1fv(GLuint index, const GLfloat* v)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttrib1fv(index, v);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttrib1sv(GLuint index, const GLshort* v)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttrib1sv(index, v);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttrib1dv(GLuint index, const GLdouble* v)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttrib1dv(index, v);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttribI1iv(GLuint index, const GLint* v)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttribI1iv(index, v);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttribI1uiv(GLuint index, const GLuint* v)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttribI1uiv(index, v);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttrib2fv(GLuint index, const GLfloat* v)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttrib2fv(index, v);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttrib2sv(GLuint index, const GLshort* v)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttrib2sv(index, v);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttrib2dv(GLuint index, const GLdouble* v)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttrib2dv(index, v);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttribI2iv(GLuint index, const GLint* v)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttribI2iv(index, v);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttribI2uiv(GLuint index, const GLuint* v)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttribI2uiv(index, v);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttrib3fv(GLuint index, const GLfloat* v)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttrib3fv(index, v);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttrib3sv(GLuint index, const GLshort* v)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttrib3sv(index, v);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttrib3dv(GLuint index, const GLdouble* v)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttrib3dv(index, v);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttribI3iv(GLuint index, const GLint* v)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttribI3iv(index, v);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttribI3uiv(GLuint index, const GLuint* v)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttribI3uiv(index, v);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttrib4fv(GLuint index, const GLfloat* v)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttrib4fv(index, v);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttrib4sv(GLuint index, const GLshort* v)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttrib4sv(index, v);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttrib4dv(GLuint index, const GLdouble* v)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttrib4dv(index, v);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttrib4iv(GLuint index, const GLint* v)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttrib4iv(index, v);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttrib4bv(GLuint index, const GLbyte* v)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttrib4bv(index, v);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttrib4ubv(GLuint index, const GLubyte* v)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttrib4ubv(index, v);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttrib4usv(GLuint index, const GLushort* v)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttrib4usv(index, v);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttrib4uiv(GLuint index, const GLuint* v)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttrib4uiv(index, v);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttrib4Nbv(GLuint index, const GLbyte* v)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttrib4Nbv(index, v);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttrib4Nsv(GLuint index, const GLshort* v)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttrib4Nsv(index, v);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttrib4Niv(GLuint index, const GLint* v)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttrib4Niv(index, v);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttrib4Nubv(GLuint index, const GLubyte* v)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttrib4Nubv(index, v);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttrib4Nusv(GLuint index, const GLushort* v)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttrib4Nusv(index, v);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttrib4Nuiv(GLuint index, const GLuint* v)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttrib4Nuiv(index, v);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttribI4bv(GLuint index, const GLbyte* v)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttribI4bv(index, v);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttribI4ubv(GLuint index, const GLubyte* v)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttribI4ubv(index, v);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttribI4sv(GLuint index, const GLshort* v)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttribI4sv(index, v);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttribI4usv(GLuint index, const GLushort* v)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttribI4usv(index, v);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttribI4iv(GLuint index, const GLint* v)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttribI4iv(index, v);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttribI4uiv(GLuint index, const GLuint* v)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttribI4uiv(index, v);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttribL1dv(GLuint index, const GLdouble* v)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttribL1dv(index, v);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttribL2dv(GLuint index, const GLdouble* v)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttribL2dv(index, v);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttribL3dv(GLuint index, const GLdouble* v)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttribL3dv(index, v);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttribL4dv(GLuint index, const GLdouble* v)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttribL4dv(index, v);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttribP1ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttribP1ui(index, type, normalized, value);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttribP2ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttribP2ui(index, type, normalized, value);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttribP3ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttribP3ui(index, type, normalized, value);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::VertexAttribP4ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
{
	if (deleted)
	{
		NGLStateError("Vertex array is deleted and cannot be edited.\n");
		return 0;
	}
	glVertexAttribP4ui(index, type, normalized, value);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::DisableVertexArrayAttrib(GLuint index)
{
	
	if (deleted)
	{
		printf("Vertex array is currently deleted, generate before editing. \n");
		Status
			return 0;
	}
	glDisableVertexArrayAttrib(m_va, index);
	GetError
		if (Code) { return 0; }

	return 1;
}
int NGLVertexArray::VertexArrayAttribBinding(GLuint attribindex, GLuint bindingindex)
{
	if (deleted)
	{
		printf("Vertex array is currently deleted, generate before editing. \n");
		Status
			return 0;
	}
	glVertexArrayAttribBinding(m_va, attribindex, bindingindex);
	GetError
		if (Code) { return 0; }

	return 1;
}
int NGLVertexArray::VertexArrayAttribDivisor(GLuint index, GLuint divisor)
{
	if (deleted)
	{
		printf("Vertex array is currently deleted, generate before editing. \n");
		Status
			return 0;
	}
	glVertexAttribDivisor(index, divisor);
	GetError
		if (Code) { return 0; }

	return 1;
}
int NGLVertexArray::VertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer)
{
	if (deleted)
	{
		printf("Vertex array is currently deleted, generate before editing. \n");
		Status
			return 0;
	}
	glVertexAttribPointer(index, size, type, normalized, stride, pointer);
	GetError
		if (Code) { return 0; }

	return 1;
}
int NGLVertexArray::VertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer)
{
	if (deleted)
	{
		printf("Vertex array is currently deleted, generate before editing. \n");
		Status
			return 0;
	}
	glVertexAttribIPointer(index, size, type, stride, pointer);
	GetError
		if (Code) { return 0; }

	return 1;
}
int NGLVertexArray::VertexAttribLPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer)
{
	if (deleted)
	{
		printf("Vertex array is currently deleted, generate before editing. \n");
		Status
			return 0;
	}
	glVertexAttribLPointer(index, size, type, stride, pointer);
	GetError
		if (Code) { return 0; }

	return 1;
}
bool NGLVertexArray::IsVertexArray()
{
	GLboolean isvertexarray = glIsVertexArray(m_va);
	return isvertexarray;
}
int NGLVertexArray::GetVertexArrayiv(GLenum pname, GLint* param)
{
	if (deleted)
	{
		printf("Vertex array is currently deleted, generate before editing. \n");
		Status
			return 0;
	}
	glGetVertexArrayiv(m_va, pname, param);
	GetError
		if (Code) { return 0; }

	return 1;
}
int NGLVertexArray::GetVertexArrayIndexediv(GLuint vaobj, GLuint index, GLenum pname, GLint* param)
{
	if (deleted)
	{
		printf("Vertex array is currently deleted, generate before editing. \n");
		Status
			return 0;
	}
	glGetVertexArrayIndexediv(m_va, index,pname,param);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLVertexArray::GetVertexArrayIndexed64iv(GLuint vaobj, GLuint index, GLenum pname, GLint64* param)
{
	if (deleted)
	{
		printf("Vertex array is currently deleted, generate before editing. \n");
		Status
			return 0;
	}
	glGetVertexArrayIndexed64iv(m_va, index, pname, param);
	GetError
		if (Code) { return 0; }
	return 1;
}
GLuint NGLVertexArray::ReturnVertexArray() { return m_va; }
int NGLVertexArray::DeleteVertexArray()
{
	if (deleted)
	{
		printf("Vertex array is currently deleted, cannot delete again. \n");
		Status
			return 0;
	}
	glDeleteVertexArrays(1, &m_va);
	GetError
		if (Code) { return 0; }
	deleted = true;
	return 1;

}
NGLVertexArray::~NGLVertexArray()
{
	DeleteVertexArray();
}