#include "NFWMonitors.h"


NFWMonitors::NFWMonitors()
{
	m_monitors = nullptr;
	monitorCount = 0;
	active = false;
}
int NFWMonitors::GetMonitors(int* count)
{
	m_monitors = glfwGetMonitors(count);
	int Error = NFWGetError();
	if (Error != GLFW_NO_ERROR)
	{
		return 0;

	}
	monitorCount = *count;
	active = true;
	return 1;
}
GLFWmonitor* NFWMonitors::GetMonitor(int index)
{
	if (active && index < monitorCount)
	{
		return m_monitors[index];
	}
	NFWStateError("Monitors are not active.\n");
	return nullptr;
}

NFWMonitors::~NFWMonitors(){}


int SetMonitorCallback(GLFWmonitorfun cb)
{
	glfwSetMonitorCallback(cb);
	int Error = NFWGetError();
	if (Error != GLFW_NO_ERROR)
	{
		return 0;

	}
	return 1;

}