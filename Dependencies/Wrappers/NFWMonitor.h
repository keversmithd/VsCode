#ifndef __FUNCTION__ 
 #define __FUNCTION__ 
 #endif
#ifndef NFWWINMON
#define NFWWINMON

#include "NFWDebug.h"

struct NFWMonitor
{
private:
	GLFWmonitor* m_monitor;
	bool active;
public:
	NFWMonitor();
	int BecomePrimaryMonitor();
	int BecomeWindowMonitor(GLFWwindow* window);
	int BecomeMonitor(GLFWmonitor* monitor);
	int GetMonitorPos(int* xpos, int* ypos);
	int GetMonitorWorkarea(int* xpos, int* ypos, int* width, int* height);
	int GetMonitorPhysicalSize(int* widthMM, int* heightMM);
	int GetMonitorContentScale(float* xscale, float* yscale);
	int GetMonitorName(char* &retName);
	int GetMonitorUserPointer(void* &retPointer);
	int GetVideoModes(int* count, GLFWvidmode* &retModes);
	int GetGammaRamp(GLFWgammaramp* &retGammaRamp);
	int SetMonitorUserPointer(void* pointer);
	int SetGamma(float gamma);
	int SetGammaRamp(const GLFWgammaramp* ramp);
	int GetVideoMode(GLFWvidmode* &ret);
	GLFWmonitor* GetMonitor();
	~NFWMonitor();
};
	

#endif
