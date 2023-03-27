#include "NFWErrorLog.h"

NFWStateErrorLog::NFWStateErrorLog() : NKStateLog("NFWStateErrorLog.txt")
{

}


NFWStateErrorLog::~NFWStateErrorLog() {
	ClearLog();
}
NFWStateErrorLogInstance::NFWStateErrorLogInstance()
{
}
int NFWStateErrorLogInstance::LogStateError(const char* errmessage)
{
	return instance.AppendMessage(errmessage);
}

int NFWStateErrorLogInstance::DumpLog()
{
	return instance.DumpLog();
}
NFWStateErrorLogInstance::~NFWStateErrorLogInstance()
{

}
NFWStateErrorLogInstance NFWStateLog;
void NFWStateError(const char* errmessage)
{
	NFWStateLog.LogStateError(errmessage);
}

void NFWDumpLog()
{
	NFWStateLog.DumpLog();
}