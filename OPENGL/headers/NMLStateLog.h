#ifndef NMLSTATELOG
#define NMLSTATELOG

#include <stdio.h>
#include <string>

#define InconsistenWrite 0x99
#define NoFile 0x98

struct NMLStateLog
{
private:
	bool LogCreated;
	bool LogOpen;
	const char* FileName;
	FILE* Log;
public:
	NMLStateLog();
	int CreateStateErrorLog();
	int OpenLogInAppendedState();
	int ClearErrors();
	int LogStateError(const char* errmessage);
	~NMLStateLog();
};

struct NMLStateLogInstance
{
private:
	NMLStateLog instance;
	bool valid;
public:
	NMLStateLogInstance();
	int LogStateError(const char* errmessage);
	~NMLStateLogInstance();
	bool Active();
};


void NMLStateError(const char* errmessage);


#endif
