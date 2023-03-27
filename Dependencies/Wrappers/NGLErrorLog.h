#ifndef __FUNCTION__ 
 #define __FUNCTION__ 
 #endif
#ifndef NGLERRORLOG
#define NGLERRORLOG

#include <stdio.h>
#include <string.h>

#define NGLInconsistenWrite 0x99
#define NGLNoFile 0x98

struct NGLStateErrorLog
{
private:
	bool LogCreated;
	bool LogOpen;
	const char* FileName;
	FILE* Log;
public:
	NGLStateErrorLog();
	int CreateStateErrorLog();
	int OpenLogInAppendedState();
	int ClearErrors();
	int LogStateError(const char* errmessage);
	~NGLStateErrorLog();
};

struct NGLStateErrorLogInstance
{
private:
	NGLStateErrorLog instance;
	bool valid;
public:
	NGLStateErrorLogInstance();
	int LogStateError(const char* errmessage);
	~NGLStateErrorLogInstance();
	bool Active();
};


void NGLStateError(const char* errmessage);


#endif

