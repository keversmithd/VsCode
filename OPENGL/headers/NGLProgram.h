#ifndef NGLPROGRAM
#define NGLPROGRAM

#include "NGLDebug.h"

struct NGLProgram 
{
private:
	unsigned int m_program;
	bool created;
public:
	NGLProgram();
	int CreateProgram();
	int DeleteProgram();
	int GetProgramBinary(GLsizei bufSize, GLsizei* length, GLenum* binaryFormat, void* binary);
	int GetProgramInfoLog(GLsizei maxLength, GLsizei* length, GLchar* infoLog);
	int GetProgramInterfaceiv(GLenum programInterface, GLenum pname, GLint* params);
	int GetProgramiv(GLenum pname, GLint* params);
	int GetProgramResourceIndex(GLenum programInterface, const char* name);
	int GetProgramResourceiv(GLenum programInterface, GLuint index, GLsizei propCount, const GLenum* props, GLsizei bufSize, GLsizei* length, GLint* params);
	int GetProgramResourceLocation(GLenum programInterface, const char* name);
	int GetProgramResourceLocationIndex(GLenum programInterface, const char* name);
	int GetProgramResourceName(GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei* length, char* name);
	int GetProgramStageiv(GLenum pname, GLint* params);
	int GetActiveAttrib(GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name);
	int GetActiveAtomicCounterBufferiv(GLuint bufferIndex, GLenum pname, GLint* params);
	int GetActiveSubroutineName(GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei* length, GLchar* name);
	int GetActiveSubroutineUniformName(GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei* length, GLchar* name);
	int GetActiveUniform(GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name);
	int GetActiveUniformBlockiv(GLuint uniformBlockIndex, GLenum pname, GLint* params);
	int GetActiveUniformBlockName(GLuint uniformBlockIndex, GLsizei bufSize, GLsizei* length, GLchar* uniformBlockName);
	int GetActiveUniformName(GLuint uniformIndex, GLsizei bufSize, GLsizei* length, GLchar* uniformName);
	int GetActiveUniformsiv(GLsizei uniformCount, const GLuint* uniformIndices, GLenum pname, GLint* params);
	int GetAttachedShaders(GLsizei maxCount, GLsizei* count, GLuint* shaders);
	int GetAttribLocation(const GLchar* name);
	int GetFragDataIndex(const char* name);
	int GetFragDataLocation(const char* name);
	int GetSubroutineIndex(GLenum shadertype, const GLchar* name);
	int GetSubroutineUniformLocation(GLenum shadertype, const GLchar* name);
	int GetUniformfv(GLint location, GLfloat* params);
	int GetUniformiv(GLint location, GLint* params);
	int GetUniformuiv(GLint location, GLuint* params);
	int GetUniformdv(GLint location, GLdouble* params);
	int GetnUniformfv(GLint location, GLsizei bufSize, GLfloat* params);
	int GetnUniformiv(GLint location, GLsizei bufSize, GLint* params);
	int GetnUniformuiv(GLint location, GLsizei bufSize, GLuint* params);
	int GetnUniformdv(GLint location, GLsizei bufSize, GLdouble* params);
	int GetUniformBlockIndex(const GLchar* uniformBlockName, GLuint* index);
	int GetUniformIndices(GLsizei uniformCount, const GLchar** uniformNames, GLuint* uniformIndices);
	int GetUniformLocation(const GLchar* name, GLint* param);
	int UniformBlockBinding(GLuint uniformBlockIndex, GLuint uniformBlockBinding);
	int GetUniformSubroutine();
	int BindAttribLocation(GLuint index, const GLchar* name);
	int BindFragDataLocation(GLuint colorNumber, const char* name);
	int BindFragDataLocationIndexed(GLuint colorNumber, GLuint index, const char* name);
	bool IsProgram();
	int AttachShader(GLuint shader);
	int DetachShader(GLuint shader);
	int LinkProgram();
	int ProgramBinary(GLenum binaryFormat, const void* binary, GLsizei length);
	int ProgramParamateri(GLenum pname, GLint value);
	int ProgramUniform1d(GLint location, GLdouble x);
	int ProgramUniform1dv(GLint location, GLsizei count, GLdouble* x);
	int ProgramUniform1f(GLint location, GLfloat v0);
	int ProgramUniform1fv(GLint location, GLsizei count, GLfloat* v0);
	int ProgramUniform1i(GLint location, GLint v0);
	int ProgramUniform1iv(GLint location, GLsizei count, GLint* v0);
	int ProgramUniform1ui(GLint location, GLuint x);
	int ProgramUniform1uiv(GLint location, GLsizei count, GLuint* v0);
	int ProgramUniform2d(GLint location, GLdouble x, GLdouble y);
	int ProgramUniform2dv(GLint location, GLsizei count, GLdouble* value);
	int ProgramUniform2f(GLint location, GLfloat x, GLfloat y);
	int ProgramUniform2fv(GLint location, GLsizei count, GLfloat* value);
	int ProgramUniform2i(GLint location, GLint x, GLint y);
	int ProgramUniform2iv(GLint location, GLsizei count, GLint* value);
	int ProgramUniform2ui(GLint location, GLuint x, GLuint y);
	int ProgramUniform2uiv(GLint location, GLsizei count, GLuint* value);
	int ProgramUniform3d(GLint location, GLdouble x, GLdouble y, GLdouble z);
	int ProgramUniform3dv(GLint location, GLsizei count, GLdouble* value);
	int ProgramUniform3f(GLint location, GLfloat x, GLfloat y, GLfloat z);
	int ProgramUniform3fv(GLint location, GLsizei count, GLfloat* value);
	int ProgramUniform3i(GLint location, GLint x, GLint y, GLint z);
	int ProgramUniform3iv(GLint location, GLsizei count, GLint* value);
	int ProgramUniform3ui(GLint location, GLuint x, GLuint y, GLuint z);
	int ProgramUniform3uiv(GLint location, GLsizei count, GLuint* value);
	int ProgramUniform4d(GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
	int ProgramUniform4dv(GLint location, GLsizei count, GLdouble* value);
	int ProgramUniform4f(GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	int ProgramUniform4fv(GLint location, GLsizei count, GLfloat* value);
	int ProgramUniform4i(GLint location, GLint x, GLint y, GLint z, GLint w);
	int ProgramUniform4iv(GLint location, GLsizei count, GLint* value);
	int ProgramUniform4ui(GLint location, GLuint x, GLuint y, GLuint z, GLuint w);
	int ProgramUniform4uiv(GLint location, GLsizei count, GLuint* value);
	int ProgramUniformMatrix2dv(GLint location, GLsizei count, GLboolean transpose, GLdouble* value);
	int ProgramUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, GLfloat* value);
	int ProgramUniformMatrix2x3dv(GLint location, GLsizei count, GLboolean transpose, GLdouble* value);
	int ProgramUniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, GLfloat* value);
	int ProgramUniformMatrix2x4dv(GLint location, GLsizei count, GLboolean transpose, GLdouble* value);
	int ProgramUniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, GLfloat* value);
	int ProgramUniformMatrix3dv(GLint location, GLsizei count, GLboolean transpose, GLdouble* value);
	int ProgramUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, GLfloat* value);
	int ProgramUniformMatrix3x2dv(GLint location, GLsizei count, GLboolean transpose, GLdouble* value);
	int ProgramUniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, GLfloat* value);
	int ProgramUniformMatrix3x4dv(GLint location, GLsizei count, GLboolean transpose, GLdouble* value);
	int ProgramUniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, GLfloat* value);
	int ProgramUniformMatrix4dv(GLint location, GLsizei count, GLboolean transpose, GLdouble* value);
	int ProgramUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, GLfloat* value);
	int ProgramUniformMatrix4x2dv(GLint location, GLsizei count, GLboolean transpose, GLdouble* value);
	int ProgramUniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, GLfloat* value);
	int ProgramUniformMatrix4x3dv(GLint location, GLsizei count, GLboolean transpose, GLdouble* value);
	int ProgramUniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, GLfloat* value);
	int UseProgram();
	int ValidateProgram();
	int ActiveShaderProgram(GLuint pipeline);
	int GetTransformFeedbackVarying(GLuint index, GLsizei bufSize, GLsizei* length, GLsizei* size, GLenum* type, char* name);
	int TransformFeedbackVaryings(GLsizei count, const char** varyings, GLenum bufferMode);
	unsigned int ReturnProgram();
	~NGLProgram();

};

#endif
