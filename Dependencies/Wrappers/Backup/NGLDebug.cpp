#include "NGLDebug.h"

const char* GLErrorString(GLenum Code)
{

    const char* ErrorString;
    switch (Code)
    {
    case GL_INVALID_ENUM:                  ErrorString = "INVALID_ENUM"; break;
    case GL_INVALID_VALUE:                 ErrorString = "INVALID_VALUE"; break;
    case GL_INVALID_OPERATION:             ErrorString = "INVALID_OPERATION"; break;
    case GL_STACK_OVERFLOW:                ErrorString = "STACK_OVERFLOW"; break;
    case GL_STACK_UNDERFLOW:               ErrorString = "STACK_UNDERFLOW"; break;
    case GL_OUT_OF_MEMORY:                 ErrorString = "OUT_OF_MEMORY"; break;
    case GL_INVALID_FRAMEBUFFER_OPERATION: ErrorString = "INVALID_FRAMEBUFFER_OPERATION"; break;
    default: ErrorString = "No Error";
    }

    return ErrorString;
}

int GLError()
{
	GLenum code = glGetError();
	if (code != GL_NO_ERROR)
	{
		const char* codeString = GLErrorString(code);
		//fprintf(stderr, "OpenGL error: %s\n", codeString);
		return 1;
		
	}
	
	return 0;
}


