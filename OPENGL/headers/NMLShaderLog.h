#ifndef NMLSHADERLOG
#define NMLSHADERLOG

#include "NKStateLog.h"
#include <string.h>
struct NMLShaderLog : NKStateLog
{
public:
	NMLShaderLog();
	~NMLShaderLog();
};


struct NMLStateErrorLogInstance
{
private:
	NMLShaderLog instance;
public:
	NMLStateErrorLogInstance();
	int LogStateError(const char* errmessage);
	~NMLStateErrorLogInstance();
};

int NMLLogShader(const char* errmessage);

#endif
