
#include "NFWDebug.h"
#include <string.h>
int NFWErrorCode = 0;

int NFWGetError()
{
	int PrevCode = NFWErrorCode;
	NFWErrorCode = 0;
	return PrevCode;
}

void NFWErrorCallback(int code, const char* err_str)
{
	char* cat_err_str = (char*)err_str;
	strcat(cat_err_str, "\n");
	NFWStateError(cat_err_str);
	NFWErrorCode = code;
}

NFWErrorCallbackInstance::NFWErrorCallbackInstance()
{
	glfwSetErrorCallback(NFWErrorCallback);
}
NFWErrorCallbackInstance::~NFWErrorCallbackInstance()
{

}

NFWErrorCallbackInstance NFWCBINSTANCE;