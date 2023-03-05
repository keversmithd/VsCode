#ifndef NKSTATELOG
#define NKSTATELOG

#include <stdio.h>


struct NKStateLog
{
protected:
	FILE* WriteLog;
	FILE* ReadLog;
	const char* FileName;
public:
	NKStateLog(const char* fileName)
	{
		WriteLog = NULL;
		ReadLog = NULL;
		FileName = fileName;
	}
	int AppendMessage(const char* message)
	{
		errno_t err = fopen_s(&WriteLog, FileName, "a");
		if (WriteLog == NULL) { return 0; }
		if (err != 0) { fclose(WriteLog); return 0; }
		fprintf(WriteLog, "%s", message);
		fclose(WriteLog);
	}
	int ClearLog()
	{
		errno_t err = fopen_s(&WriteLog, FileName, "w");
		if (WriteLog == NULL) { return 0; }
		fclose(WriteLog);
		return err;
	}
	int DumpLog()
	{

		errno_t err = fopen_s(&ReadLog, FileName, "r");
		if (ReadLog == NULL) { return 0; }
		if (err != 0) { return 0; }
		char buffer[255];
		while (fgets(buffer, 255, ReadLog))
		{
			printf("%s", buffer);
		}
		fclose(ReadLog);
	}
	~NKStateLog()
	{
		ClearLog();
	}
};


#endif