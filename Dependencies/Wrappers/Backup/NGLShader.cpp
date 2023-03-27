#include "NGLShader.h"

char* NGLParseShader(const char* path)
{
	FILE* ParseFile;
	fopen_s(&ParseFile, path, "rb");
	fpos_t extractionByteTotal;
	if (ParseFile != NULL)
	{
		fseek(ParseFile, 0, SEEK_END);
		fgetpos(ParseFile, &extractionByteTotal);
		fseek(ParseFile, 0, SEEK_SET);
		char* ParseBuffer = (char*)malloc(static_cast<size_t>(extractionByteTotal + 1));
		if (ParseBuffer != nullptr)
		{
			fread(ParseBuffer, extractionByteTotal, 1, ParseFile);
			ParseBuffer[extractionByteTotal] = '\0';
		}
		fclose(ParseFile);
		return ParseBuffer;
	}
	return nullptr;
}
NGLShader::NGLShader()
{
	m_shader = 0;
	created = false;
	m_shadertype = GL_NONE;
	sourceloaded = false;
	sourcecompiled = false;
}
int NGLShader::CreateShader(GLenum type)
{
	if (created)
	{
		printf("Shader object already created, delete to regenerate.\n");
		return 0;
	}
	m_shader = glCreateShader(type);
	
	GetError
		if (Code) { return 0; }
	m_shadertype = type;
	created = true;
	return 1;
}
int NGLShader::ShaderSource(GLsizei count, const GLchar** string, const GLint* length)
{

	if (created)
	{
		glShaderSource(m_shader, count, string, length);
		GetError
			if (Code) { return 0; }
		sourceloaded = true;
		return 1;
	}
	printf("Shader object has not been created and cannot be altered.\n");

	return 0;
}
int NGLShader::ShaderBinary(GLenum binaryFormat, const void* binary, GLsizei length)
{
	if (created)
	{
		glShaderBinary(1, &m_shader, binaryFormat, binary, length);
		GetError
			if (Code) { return 0; }
		sourceloaded = true;
		return 1;
	}
	printf("Shader object has not been created and cannot be altered.\n");

	return 0;
}
int NGLShader::CompileShader()
{
	if (created)
	{
		glCompileShader(m_shader);
		GetError
			if (Code) { return 0; }
		sourcecompiled = true;
		return 1;
	}
	printf("Shader object has not been created and cannot be altered.\n");

	return 0;
}
int NGLShader::GetShaderSource(GLsizei bufSize, GLsizei* length, GLchar* source)
{
	if (created)
	{
		glGetShaderSource(m_shader, bufSize, length, source);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Shader object has not been created and cannot be altered.\n");

	return 0;
}
int NGLShader::GetInfoLog(GLsizei maxLength, GLsizei* length, GLchar* infoLog)
{
	if (created)
	{
		glGetShaderInfoLog(m_shader, maxLength, length, infoLog);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Shader object has not been created and cannot be altered.\n");

	return 0;
}
int NGLShader::GetShaderiv(GLenum pname, GLint* param)
{
	glGetShaderiv(m_shader, pname, param);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLShader::DeleteShader()
{
	if (created)
	{
		glDeleteShader(m_shader);
		GetError
			if (Code) { return 0; }
		created = false;
		return 1;
	}
	printf("Shader object has not been created and cannot be deleted.\n");

	return 0;
}
bool NGLShader::IsShader()
{
	GLboolean isShdr = glIsShader(m_shader);
	return isShdr;
}
bool NGLShader::Created()
{
	return created;
}
bool NGLShader::SourceLoaded()
{
	return sourceloaded;
}
bool NGLShader::SourceCompiled()
{
	return sourcecompiled;
}
unsigned int NGLShader::ReturnShader()
{
	return m_shader;
}

NGLShader::~NGLShader()
{
	DeleteShader();
}