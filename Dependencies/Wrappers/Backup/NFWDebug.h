#ifndef NFWDEB
#define NFWDEB

#include <GLFW/glfw3.h>
#include "NFWErrorLog.h"



extern int NFWErrorCode;

int NFWGetError();

void NFWErrorCallback(int code, const char* err_str);

struct NFWErrorCallbackInstance {
	NFWErrorCallbackInstance();
	~NFWErrorCallbackInstance();
};



#endif
