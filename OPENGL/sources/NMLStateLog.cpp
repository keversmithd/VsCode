#include "NMLStateLog.h"

NMLStateLog::NMLStateLog()
{
	Log = NULL;
	LogCreated = false;
	LogOpen = false;
	FileName = "NMLStateLog.txt";
}
int NMLStateLog::CreateStateErrorLog()
{
	if (LogCreated)
	{
		return 1;
	}

	FILE* tempLog = NULL;
	errno_t err = fopen_s(&tempLog, FileName, "w");
	if (err != 0) { return 0; }
	if (tempLog == NULL) { return 0; }
	fclose(tempLog);

	int OpenStatus = OpenLogInAppendedState();
	if (OpenStatus == 0) { return 0; }


	Log = tempLog;
	LogCreated = true;
	LogOpen = true;
	return 1;
}
int NMLStateLog::OpenLogInAppendedState()
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
	if (err != 0) { return 0; }
	if (tempLog == NULL)
	{
		return 0;
	}
	Log = tempLog;
}
int NMLStateLog::ClearErrors()
{
	errno_t err = fopen_s(&Log, "NMLStateLog.txt", "w");
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
int NMLStateLog::LogStateError(const char* errmessage)
{
	if (LogCreated && LogOpen)
	{
		size_t elemSize = strlen(errmessage);
		
		size_t fwriteStatus = fwrite(errmessage, elemSize, 1, Log);
		if (fwriteStatus != elemSize)
		{
			return InconsistenWrite;
		}
		return 1;
	}
	return NoFile;
}
NMLStateLog::~NMLStateLog() {
	ClearErrors();
}


NMLStateLogInstance::NMLStateLogInstance()
{
	valid = false;
	int state = instance.CreateStateErrorLog();
	if (state != 0) { valid = true; }
}
int NMLStateLogInstance::LogStateError(const char* errmessage)
{
	if (valid)
	{
		instance.LogStateError(errmessage);
	}
	return 0;
}
bool NMLStateLogInstance::Active()
{
	return valid;
}
NMLStateLogInstance::~NMLStateLogInstance()
{

}
NMLStateLogInstance NMLStateLog;
void NMLStateError(const char* errmessage)
{
	if (NMLStateLog.Active())
	{
		NMLStateLog.LogStateError(errmessage);
	}
}