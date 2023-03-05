#include "NGLErrorLog.h"

NGLStateErrorLog::NGLStateErrorLog()
{
	Log = NULL;
	LogCreated = false;
	LogOpen = false;
	FileName = "NGLStateErrorLog.txt";
}
int NGLStateErrorLog::CreateStateErrorLog()
{
	if (LogCreated)
	{
		return 1;
	}

	FILE* tempLog = NULL;
	errno_t err = fopen_s(&tempLog, FileName, "w");
	if (err != 0){ return 0; }
	if (tempLog == NULL) { return 0; }
	fclose(tempLog);

	int OpenStatus = OpenLogInAppendedState();
	if (OpenStatus == 0) { return 0; }


	Log = tempLog;
	LogCreated = true;
	LogOpen = true;
	return 1;
}
int NGLStateErrorLog::OpenLogInAppendedState()
{
	if (LogOpen)
	{
		if (Log == NULL)
		{
			return 0;
		}
		fclose(Log);
	}
	FILE* tempLog = NULL;
	errno_t err = fopen_s(&tempLog, FileName, "a");
	if (err != 0){	return 0; }
	if (tempLog == NULL)
	{ return 0; }
	Log = tempLog;
}
int NGLStateErrorLog::ClearErrors()
{
	errno_t err = fopen_s(&Log, "NGLStateErrorLog.txt", "w");
	if (err != 0)
	{
		//error
		return 0;
	}
	if (Log == NULL)
	{
		return 0;
	}
	fclose(Log);
	return 1;
}
int NGLStateErrorLog::LogStateError(const char* errmessage)
{
	if (LogCreated && LogOpen)
	{
		size_t elemSize = strlen(errmessage);
		size_t fwriteStatus = fwrite(errmessage, elemSize, 1, Log);
		if (fwriteStatus != elemSize)
		{
			return NGLInconsistenWrite;
		}
		return 1;
	}
	return NGLNoFile;
}
NGLStateErrorLog::~NGLStateErrorLog(){
	ClearErrors();
}


NGLStateErrorLogInstance::NGLStateErrorLogInstance()
{
	valid = false;
	int state = instance.CreateStateErrorLog();
	if (state != 0) { valid = true; }
}
int NGLStateErrorLogInstance::LogStateError(const char* errmessage)
{
	if (valid)
	{
		instance.LogStateError(errmessage);
	}
	return 0;
}
bool NGLStateErrorLogInstance::Active()
{
	return valid;
}
NGLStateErrorLogInstance::~NGLStateErrorLogInstance()
{

}
NGLStateErrorLogInstance NGLStateLog;
void NGLStateError(const char* errmessage)
{
	if (NGLStateLog.Active())
	{
		NGLStateLog.LogStateError(errmessage);
	}
}

