#ifndef NFWWINMONS
#define NFWWINMONS

#include "NFWDebug.h"

struct NFWMonitors
{
private:
	GLFWmonitor** m_monitors;
	unsigned int monitorCount;
	bool active;
public:
	NFWMonitors();
	int GetMonitors(int* count);
	GLFWmonitor* GetMonitor(int index);
	~NFWMonitors();
};

int SetMonitorCallback(GLFWmonitorfun cb);

#endif
