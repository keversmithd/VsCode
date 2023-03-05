#include "NMLShaderLog.h"
NMLShaderLog::NMLShaderLog() : NKStateLog("NMLShaderLog.txt")
{

}
NMLShaderLog::~NMLShaderLog()
{
	ClearLog();
}


NMLStateErrorLogInstance::NMLStateErrorLogInstance() 
{
	
}
int NMLStateErrorLogInstance::LogStateError(const char* errmessage)
{
	return instance.AppendMessage(errmessage);
}
NMLStateErrorLogInstance::~NMLStateErrorLogInstance()
{
	
}


NMLStateErrorLogInstance NMLInstance;

int NMLLogShader(const char* errmessage)
{
	return NMLInstance.LogStateError(errmessage);
}