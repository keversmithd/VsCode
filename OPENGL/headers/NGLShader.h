#ifndef NGLSHADER
#define NGLSHADER
#include "NGLDebug.h"

char* NGLParseShader(const char* path);

struct NGLShader
{
private:
	unsigned int m_shader;
	GLenum m_shadertype;
	bool created;
	bool sourceloaded;
	bool sourcecompiled;
public:
	NGLShader();
	int CreateShader(GLenum type);
	int ShaderSource(GLsizei count, const GLchar** string, const GLint* length);
	int ShaderBinary(GLenum binaryFormat, const void* binary, GLsizei length);
	int CompileShader();
	int GetShaderSource(GLsizei bufSize, GLsizei* length, GLchar* source);
	int GetInfoLog(GLsizei maxLength, GLsizei* length, GLchar* infoLog);
	int GetShaderiv(GLenum pname, GLint* param);
	int DeleteShader();
	bool IsShader();
	bool Created();
	bool SourceLoaded();
	bool SourceCompiled();
	unsigned int ReturnShader();
	~NGLShader();
};

#endif
