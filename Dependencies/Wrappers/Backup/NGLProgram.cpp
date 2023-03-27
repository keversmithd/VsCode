#include "NGLProgram.h"


NGLProgram::NGLProgram()
{
	m_program = 0;
	created = false;
}
int NGLProgram::CreateProgram()
{
	if (created)
	{
		printf("Program already created, delete program and continue.\n");
		return 0;
	}
	m_program = glCreateProgram();
	GetError
		if (Code) { return 0; }
	created = true;
	return 1;
}
int NGLProgram::DeleteProgram()
{
	if (created)
	{
		glDeleteProgram(m_program);
		GetError
			if (Code) { return 0; }
		created = false;
		return 1;
	}
	printf("Program object doesn't exist, generate in order to delete.\n");
	return 0;
}
int NGLProgram::GetProgramBinary(GLsizei bufSize, GLsizei* length, GLenum* binaryFormat, void* binary)
{
	if (created)
	{
		glGetProgramBinary(m_program, bufSize, length, binaryFormat, binary);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::GetProgramInfoLog(GLsizei maxLength, GLsizei* length, GLchar* infoLog)
{
	if (created)
	{
		glGetProgramInfoLog(m_program, maxLength,length,infoLog);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::GetProgramInterfaceiv(GLenum programInterface, GLenum pname, GLint* params)
{
	if (created)
	{
		glGetProgramInterfaceiv(m_program, programInterface, pname, params);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::GetProgramiv(GLenum pname, GLint* params)
{
	if (created)
	{
		glGetProgramiv(m_program, pname, params);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::GetProgramResourceIndex(GLenum programInterface, const char* name)
{
	if (created)
	{
		glGetProgramResourceIndex(m_program, programInterface, name);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::GetProgramResourceiv(GLenum programInterface, GLuint index, GLsizei propCount, const GLenum* props, GLsizei bufSize, GLsizei* length, GLint* params)
{
	if (created)
	{
		glGetProgramResourceiv(m_program, programInterface, index, propCount, props, bufSize,  length, params);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::GetProgramResourceLocation(GLenum programInterface, const char* name)
{
	if (created)
	{
		glGetProgramResourceLocation(m_program, programInterface, name);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::GetProgramResourceLocationIndex(GLenum programInterface, const char* name)
{
	if (created)
	{
		glGetProgramResourceLocationIndex(m_program, programInterface, name);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::GetProgramResourceName(GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei* length, char* name)
{
	if (created)
	{
		glGetProgramResourceName(m_program, programInterface, index, bufSize, length, name );
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::GetProgramStageiv(GLenum pname, GLint* params)
{
	if (created)
	{
		glGetProgramiv(m_program, pname, params );
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::GetActiveAttrib(GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name)
{
	if (created)
	{
		glGetActiveAttrib(m_program, index, bufSize, length, size, type, name);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program has not been created and cannot be queried.\n");
	return 0;
}
int NGLProgram::GetActiveAtomicCounterBufferiv(GLuint bufferIndex, GLenum pname, GLint* params)
{
	if (created)
	{
		glGetActiveAtomicCounterBufferiv(m_program, bufferIndex, pname, params);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program has not been created and cannot be queried.\n");
	return 0;
}
int NGLProgram::GetActiveSubroutineName(GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei* length, GLchar* name)
{
	if (created)
	{
		glGetActiveSubroutineName(m_program, shadertype, index, bufsize, length, name);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program has not been created and cannot be queried.\n");
	return 0;
}
int NGLProgram::GetActiveSubroutineUniformName(GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei* length, GLchar* name)
{
	if (created)
	{
		glGetActiveSubroutineUniformName(m_program, shadertype,
			index,
			bufsize,
			length,
			name
		);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program has not been created and cannot be queried.\n");
	return 0;
}
int NGLProgram::GetActiveUniform(GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name)
{
	if (created)
	{
		glGetActiveUniform(m_program, index,
			bufSize,
			length,
			size,
			type,
			name
		);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program has not been created and cannot be queried.\n");
	return 0;
}
int NGLProgram::GetActiveUniformBlockiv(GLuint uniformBlockIndex, GLenum pname, GLint* params)
{
	if (created)
	{
		glGetActiveUniformBlockiv(m_program, uniformBlockIndex,
			pname,
			params

		);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program has not been created and cannot be queried.\n");
	return 0;
}
int NGLProgram::GetActiveUniformBlockName(GLuint uniformBlockIndex, GLsizei bufSize, GLsizei* length, GLchar* uniformBlockName)
{
	if (created)
	{
		glGetActiveUniformBlockName(m_program, uniformBlockIndex,
			bufSize,
			length,
			uniformBlockName
		);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program has not been created and cannot be queried.\n");
	return 0;
}
int NGLProgram::GetActiveUniformName(GLuint uniformIndex, GLsizei bufSize, GLsizei* length, GLchar* uniformName)
{
	if (created)
	{
		glGetActiveUniformName(m_program, uniformIndex,
			bufSize,
			length,
			uniformName
		);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program has not been created and cannot be queried.\n");
	return 0;
}
int NGLProgram::GetActiveUniformsiv(GLsizei uniformCount, const GLuint* uniformIndices, GLenum pname, GLint* params)
{
	if (created)
	{
		glGetActiveUniformsiv(m_program, uniformCount,
			uniformIndices,
			pname,
			params

		);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program has not been created and cannot be queried.\n");
	return 0;
}
int NGLProgram::GetAttachedShaders(GLsizei maxCount, GLsizei* count, GLuint* shaders)
{
	if (created)
	{
		glGetAttachedShaders(m_program, maxCount,
			count,
			shaders
		);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program has not been created and cannot be queried.\n");
	return 0;
}
int NGLProgram::GetAttribLocation(const GLchar* name)
{
	if (created)
	{
		glGetAttribLocation(m_program, name
		);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program has not been created and cannot be queried.\n");
	return 0;
}
int NGLProgram::GetFragDataIndex(const char* name)
{
	if (created)
	{
		glGetFragDataIndex(m_program, name
		);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program has not been created and cannot be queried.\n");
	return 0;
}
int NGLProgram::GetFragDataLocation(const char* name)
{
	if (created)
	{
		glGetFragDataLocation(m_program, name
		);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program has not been created and cannot be queried.\n");
	return 0;
}
int NGLProgram::GetSubroutineIndex(GLenum shadertype, const GLchar* name)
{
	if (created)
	{
		glGetSubroutineIndex(m_program, shadertype,
			name
		);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program has not been created and cannot be queried.\n");
	return 0;
}
int NGLProgram::GetSubroutineUniformLocation(GLenum shadertype, const GLchar* name)
{
	if (created)
	{
		glGetSubroutineUniformLocation(m_program, shadertype,
			name
		);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program has not been created and cannot be queried.\n");
	return 0;
}
int NGLProgram::GetUniformfv(GLint location, GLfloat* params)
{
	if (created)
	{
		glGetUniformfv(m_program, location,
			params
		);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program has not been created and cannot be queried.\n");
	return 0;
}
int NGLProgram::GetUniformiv(GLint location, GLint* params)
{
	if (created)
	{
		glGetUniformiv(m_program, location,
			params
		);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program has not been created and cannot be queried.\n");
	return 0;
}
int NGLProgram::GetUniformuiv(GLint location, GLuint* params)
{
	if (created)
	{
		glGetUniformuiv(m_program, location,
			params
		);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program has not been created and cannot be queried.\n");
	return 0;
}
int NGLProgram::GetUniformdv(GLint location, GLdouble* params)
{
	if (created)
	{
		glGetUniformdv(m_program, location,
			params
		);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program has not been created and cannot be queried.\n");
	return 0;
}
int NGLProgram::GetnUniformfv(GLint location, GLsizei bufSize, GLfloat* params)
{
	if (created)
	{
		glGetnUniformfv(m_program, location, bufSize,
			params
		);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program has not been created and cannot be queried.\n");
	return 0;
}
int NGLProgram::GetnUniformiv(GLint location, GLsizei bufSize, GLint* params)
{
	if (created)
	{
		glGetnUniformiv(m_program, location, bufSize,
			params
		);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program has not been created and cannot be queried.\n");
	return 0;
}
int NGLProgram::GetnUniformuiv(GLint location, GLsizei bufSize, GLuint* params)
{
	if (created)
	{
		glGetnUniformuiv(m_program, location, bufSize,
			params
		);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program has not been created and cannot be queried.\n");
	return 0;
}
int NGLProgram::GetnUniformdv(GLint location, GLsizei bufSize, GLdouble* params)
{
	if (created)
	{
		glGetnUniformdv(m_program, location, bufSize,
			params
		);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program has not been created and cannot be queried.\n");
	return 0;
}
int NGLProgram::GetUniformBlockIndex(const GLchar* uniformBlockName, GLuint* index)
{
	if (created)
	{
		GLuint indexi = glGetUniformBlockIndex(m_program, uniformBlockName);
		if (indexi == GL_INVALID_INDEX) { return 0; }
		*index = indexi;
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program has not been created and cannot be queried.\n");
	return 0;
}
int NGLProgram::UniformBlockBinding(GLuint uniformBlockIndex, GLuint uniformBlockBinding)
{
	if (created)
	{
		
		glUniformBlockBinding(m_program, uniformBlockIndex, uniformBlockBinding);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program has not been created and cannot be queried.\n");
	return 0;
}
int NGLProgram::GetUniformIndices(GLsizei uniformCount, const GLchar** uniformNames, GLuint* uniformIndices)
{
	if (created)
	{
		glGetUniformIndices(m_program, uniformCount,
			uniformNames,
			uniformIndices
		);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program has not been created and cannot be queried.\n");
	return 0;
}
int NGLProgram::GetUniformLocation(const GLchar* name, GLint* param)
{
	if (created)
	{
		GLint loc = glGetUniformLocation(m_program, name);
		if (loc == -1) {return 0;}
		*param = loc;
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program has not been created and cannot be queried.\n");
	return 0;
}
int NGLProgram::GetUniformSubroutine()
{
	//fill out later
	return 0;
}
int NGLProgram::BindAttribLocation(GLuint index, const GLchar* name)
{
	if (created)
	{
		glBindAttribLocation(m_program, index,name
		);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program has not been created and cannot be queried.\n");
	return 0;
}
int NGLProgram::BindFragDataLocation(GLuint colorNumber, const char* name)
{
	if (created)
	{
		glBindAttribLocation(m_program, colorNumber,
			name
		);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program has not been created and cannot be queried.\n");
	return 0;
}
int NGLProgram::BindFragDataLocationIndexed(GLuint colorNumber, GLuint index, const char* name)
{
	if (created)
	{
		glBindFragDataLocationIndexed(m_program, colorNumber,
			index,
			name
		);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program has not been created and cannot be queried.\n");
	return 0;
}
bool NGLProgram::IsProgram()
{
	GLboolean isprgm = glIsProgram(m_program);
	return isprgm;
}
int NGLProgram::AttachShader(GLuint shader) 
{
	if (created)
	{
		glAttachShader(m_program, shader);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::DetachShader(GLuint shader)
{
	if (created)
	{
		glDetachShader(m_program, shader);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::LinkProgram()
{
	if (created)
	{

		glLinkProgram(m_program);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::ProgramBinary(GLenum binaryFormat, const void* binary, GLsizei length)
{
	if (created)
	{
		glProgramBinary(m_program, binaryFormat, binary, length);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::ProgramParamateri(GLenum pname, GLint value)
{
		glProgramParameteri(m_program, pname, value);
		GetError
			if (Code) { return 0; }
		return 1;
}
int NGLProgram::ProgramUniform1d(GLint location, GLdouble x)
{
	if (created)
	{
		glProgramUniform1d(m_program, location, x);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;

}
int NGLProgram::ProgramUniform1dv(GLint location, GLsizei count, GLdouble* x)
{
	if (created)
	{
		glProgramUniform1dv(m_program, location, count, x);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::ProgramUniform1f(GLint location, GLfloat v0)
{
	if (created)
	{
		glProgramUniform1f(m_program, location, v0);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::ProgramUniform1fv(GLint location, GLsizei count, GLfloat* v0)
{
	if (created)
	{
		glProgramUniform1fv(m_program, location, count, v0);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::ProgramUniform1i(GLint location, GLint v0)
{
	if (created)
	{
		glProgramUniform1i(m_program, location, v0);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::ProgramUniform1iv(GLint location, GLsizei count, GLint* v0)
{
	if (created)
	{
		glProgramUniform1iv(m_program, location, count, v0);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::ProgramUniform1ui(GLint location, GLuint x)
{
	if (created)
	{
		glProgramUniform1ui(m_program, location, x);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::ProgramUniform1uiv(GLint location, GLsizei count, GLuint* v0)
{
	if (created)
	{
		glProgramUniform1uiv(m_program, location, count, v0);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::ProgramUniform2d(GLint location, GLdouble x, GLdouble y)
{
	if (created)
	{
		glProgramUniform2d(m_program, location, x,y);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::ProgramUniform2dv(GLint location, GLsizei count, GLdouble* value)
{
	if (created)
	{
		glProgramUniform2dv(m_program, location, count, value);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::ProgramUniform2f(GLint location, GLfloat x, GLfloat y)
{
	if (created)
	{
		glProgramUniform2f(m_program, location, x,y);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::ProgramUniform2fv(GLint location, GLsizei count, GLfloat* value)
{
	if (created)
	{
		glProgramUniform2fv(m_program, location, count, value);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::ProgramUniform2i(GLint location, GLint x, GLint y)
{
	if (created)
	{
		glProgramUniform2i(m_program, location, x, y);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::ProgramUniform2iv(GLint location, GLsizei count, GLint* value)
{
	if (created)
	{
		glProgramUniform2iv(m_program, location, count, value);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::ProgramUniform2ui(GLint location, GLuint x, GLuint y)
{
	if (created)
	{
		glProgramUniform2ui(m_program, location, x, y);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::ProgramUniform2uiv(GLint location, GLsizei count, GLuint* value)
{
	if (created)
	{
		glProgramUniform2uiv(m_program, location, count, value);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::ProgramUniform3d(GLint location, GLdouble x, GLdouble y, GLdouble z)
{
	if (created)
	{
		glProgramUniform3d(m_program, location, x, y, z);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::ProgramUniform3dv(GLint location, GLsizei count, GLdouble* value)
{
	if (created)
	{
		glProgramUniform3dv(m_program, location, count, value);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::ProgramUniform3f(GLint location, GLfloat x, GLfloat y, GLfloat z)
{
	if (created)
	{
		glProgramUniform3f(m_program, location, x, y, z);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::ProgramUniform3fv(GLint location, GLsizei count, GLfloat* value)
{
	if (created)
	{
		glProgramUniform3fv(m_program, location, count, value);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::ProgramUniform3i(GLint location, GLint x, GLint y, GLint z)
{
	if (created)
	{
		glProgramUniform3i(m_program, location, x, y, z);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::ProgramUniform3iv(GLint location, GLsizei count, GLint* value)
{
	if (created)
	{
		glProgramUniform3iv(m_program, location, count, value);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::ProgramUniform3ui(GLint location, GLuint x, GLuint y, GLuint z)
{
	if (created)
	{
		glProgramUniform3ui(m_program, location, x, y, z);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::ProgramUniform3uiv(GLint location, GLsizei count, GLuint* value)
{
	if (created)
	{
		glProgramUniform3uiv(m_program, location, count, value);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::ProgramUniform4d(GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
	if (created)
	{
		glProgramUniform4d(m_program, location, x,y,z,w);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::ProgramUniform4dv(GLint location, GLsizei count, GLdouble* value)
{
	if (created)
	{
		glProgramUniform4dv(m_program, location, count, value);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::ProgramUniform4f(GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	if (created)
	{
		glProgramUniform4f(m_program, location, x, y, z, w);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::ProgramUniform4fv(GLint location, GLsizei count, GLfloat* value)
{
	if (created)
	{
		glProgramUniform4fv(m_program, location, count, value);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::ProgramUniform4i(GLint location, GLint x, GLint y, GLint z, GLint w)
{
	if (created)
	{
		glProgramUniform4i(m_program, location, x, y, z, w);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::ProgramUniform4iv(GLint location, GLsizei count, GLint* value)
{
	if (created)
	{
		glProgramUniform4iv(m_program, location, count, value);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::ProgramUniform4ui(GLint location, GLuint x, GLuint y, GLuint z, GLuint w)
{
	if (created)
	{
		glProgramUniform4ui(m_program, location, x, y, z, w);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::ProgramUniform4uiv(GLint location, GLsizei count, GLuint* value)
{
	if (created)
	{
		glProgramUniform4uiv(m_program, location, count, value);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::ProgramUniformMatrix2dv(GLint location, GLsizei count, GLboolean transpose, GLdouble* value)
{
	if (created)
	{
		glProgramUniformMatrix2dv(m_program, location, count, transpose, value);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::ProgramUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, GLfloat* value)
{
	if (created)
	{
		glProgramUniformMatrix2fv(m_program, location, count, transpose, value );
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::ProgramUniformMatrix2x3dv(GLint location, GLsizei count, GLboolean transpose, GLdouble* value)
{
	if (created)
	{
		glProgramUniformMatrix2x3dv(m_program, location, count, transpose, value);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::ProgramUniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, GLfloat* value)
{
	if (created)
	{
		glProgramUniformMatrix2x3fv(m_program, location, count, transpose, value);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::ProgramUniformMatrix2x4dv(GLint location, GLsizei count, GLboolean transpose, GLdouble* value)
{
	if (created)
	{
		glProgramUniformMatrix2x4dv(m_program, location, count, transpose, value);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::ProgramUniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, GLfloat* value)
{
	if (created)
	{
		glProgramUniformMatrix2x4fv(m_program, location, count, transpose, value);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::ProgramUniformMatrix3dv(GLint location, GLsizei count, GLboolean transpose, GLdouble* value)
{
	if (created)
	{
		glProgramUniformMatrix3dv(m_program, location, count, transpose, value);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
	
}
int NGLProgram::ProgramUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, GLfloat* value)
{
	if (created)
	{
		glProgramUniformMatrix3fv(m_program, location, count, transpose, value);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::ProgramUniformMatrix3x2dv(GLint location, GLsizei count, GLboolean transpose, GLdouble* value)
{
	if (created)
	{
		glProgramUniformMatrix3x2dv(m_program, location, count, transpose, value);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::ProgramUniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, GLfloat* value)
{
	if (created)
	{
		glProgramUniformMatrix3x2fv(m_program, location, count, transpose, value);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::ProgramUniformMatrix3x4dv(GLint location, GLsizei count, GLboolean transpose, GLdouble* value)
{
	if (created)
	{
		glProgramUniformMatrix3x4dv(m_program, location, count, transpose, value);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::ProgramUniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, GLfloat* value)
{
	if (created)
	{
		glProgramUniformMatrix3x4fv(m_program, location, count, transpose, value);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::ProgramUniformMatrix4dv(GLint location, GLsizei count, GLboolean transpose, GLdouble* value)
{
	if (created)
	{
		glProgramUniformMatrix4dv(m_program, location, count, transpose, value);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::ProgramUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, GLfloat* value)
{
	if (created)
	{
		glProgramUniformMatrix4fv(m_program, location, count, transpose, value);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::ProgramUniformMatrix4x2dv(GLint location, GLsizei count, GLboolean transpose, GLdouble* value)
{
	if (created)
	{
		glProgramUniformMatrix4x2dv(m_program, location, count, transpose, value);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::ProgramUniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, GLfloat* value)
{
	if (created)
	{
		glProgramUniformMatrix4x2fv(m_program, location, count, transpose, value);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::ProgramUniformMatrix4x3dv(GLint location, GLsizei count, GLboolean transpose, GLdouble* value)
{
	if (created)
	{
		glProgramUniformMatrix4x3dv(m_program, location, count, transpose, value);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::ProgramUniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, GLfloat* value)
{
	if (created)
	{
		glProgramUniformMatrix4x3fv(m_program, location, count, transpose, value);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::UseProgram()
{
	if (created)
	{
		glUseProgram(m_program);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;
}
int NGLProgram::ValidateProgram()
{
	glValidateProgram(m_program);
	GetError
		if (Code) { return 0; }
	return 1;

}
int NGLProgram::ActiveShaderProgram(GLuint pipeline)
{
	if (created)
	{
		glActiveShaderProgram(pipeline, m_program);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Program object doesn't exist, generate in order to edit.\n");
	return 0;


}
int NGLProgram::GetTransformFeedbackVarying(GLuint index, GLsizei bufSize, GLsizei* length, GLsizei* size, GLenum* type, char* name)
{
	if (created)
	{
		glGetTransformFeedbackVarying(m_program, index, bufSize, length, size, type, name);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	NGLStateError("Program not valid, generate to edit.\n");
	return 0;
}
int NGLProgram::TransformFeedbackVaryings(GLsizei count, const char** varyings, GLenum bufferMode)
{
	if (created)
	{
		glTransformFeedbackVaryings(m_program, count, varyings, bufferMode);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	NGLStateError("Program not valid, generate to edit.\n");
	return 0;
}
unsigned int  NGLProgram::ReturnProgram() { return m_program; }
NGLProgram::~NGLProgram()
{
	DeleteProgram();
}