#ifndef NFWERRLOG
#define NFWERRLOG

#include <string>
#include "NKStateLog.h"

#define NFWInconsistenWrite 0x99
#define NFWNoFile 0x98



struct NFWStateErrorLog : NKStateLog
{
	NFWStateErrorLog();
	~NFWStateErrorLog();
};


struct NFWStateErrorLogInstance
{
private:
	NFWStateErrorLog instance;
public:
	NFWStateErrorLogInstance();
	int LogStateError(const char* errmessage);
	int DumpLog();
	~NFWStateErrorLogInstance();
};

void NFWStateError(const char* errmessage);
void NFWDumpLog();

#endif
