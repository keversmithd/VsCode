#include "NFWMonitor.h"

NFWMonitor::NFWMonitor()
{
	m_monitor = nullptr;
	active = false;
}
int NFWMonitor::BecomePrimaryMonitor()
{
	m_monitor = glfwGetPrimaryMonitor();
	int Error = NFWGetError();
	if (Error != GLFW_NO_ERROR)
	{
		return 0;
	}
	active = true;
	return 1;
}
int NFWMonitor::BecomeWindowMonitor(GLFWwindow* window)
{
	m_monitor = glfwGetWindowMonitor(window);
	int Error = NFWGetError();
	if (Error != GLFW_NO_ERROR)
	{
		return 0;
	}
	active = true;
	return 1;
}
int NFWMonitor::BecomeMonitor(GLFWmonitor* monitor)
{
	if (monitor == nullptr)
	{
		NFWStateError("Not a monitor.\n");
		return 0;
	}
	m_monitor = monitor;
	return 1;
}
int NFWMonitor::GetMonitorPos(int* xpos, int* ypos)
{
	if (active)
	{
		glfwGetMonitorPos(m_monitor, xpos, ypos);
		int Error = NFWGetError();
		if (Error != GLFW_NO_ERROR)
		{
			return 0;
		}
		return 1;
	}
	NFWStateError("Monitor is not a monitor object, become a monitor to edit.\n");
	return 0;
}
int NFWMonitor::GetMonitorWorkarea(int* xpos, int* ypos, int* width, int* height)
{
	if (active)
	{
		glfwGetMonitorWorkarea(m_monitor, xpos, ypos, width, height);
		int Error = NFWGetError();
		if (Error != GLFW_NO_ERROR)
		{
			return 0;
		}
		return 1;
	}
	NFWStateError("Monitor is not a monitor object, become a monitor to edit.\n");
	return 0;
}
int NFWMonitor::GetMonitorPhysicalSize(int* widthMM, int* heightMM)
{
	if (active)
	{
		glfwGetMonitorPhysicalSize(m_monitor, widthMM, heightMM);
		int Error = NFWGetError();
		if (Error != GLFW_NO_ERROR)
		{
			return 0;
		}
		return 1;
	}
	NFWStateError("Monitor is not a monitor object, become a monitor to edit.\n");
	return 0;
}
int NFWMonitor::GetMonitorContentScale(float* xscale, float* yscale)
{
	if (active)
	{
		glfwGetMonitorContentScale(m_monitor, xscale, yscale);
		int Error = NFWGetError();
		if (Error != GLFW_NO_ERROR)
		{
			return 0;
		}
		return 1;
	}
	NFWStateError("Monitor is not a monitor object, become a monitor to edit.\n");
	return 0;
}
int NFWMonitor::GetMonitorName(char* &retName) 
{
	if (active)
	{
		retName = (char*)glfwGetMonitorName(m_monitor);
		int Error = NFWGetError();
		if (Error != GLFW_NO_ERROR)
		{
			return 0;
		}
		return 1;
	}
	NFWStateError("Monitor is not a monitor object, become a monitor to edit.\n");
	return 0;
}
int NFWMonitor::GetMonitorUserPointer(void* &retPointer)
{
	if (active)
	{
		retPointer = glfwGetMonitorUserPointer(m_monitor);
		int Error = NFWGetError();
		if (Error != GLFW_NO_ERROR)
		{
			return 0;
		}
		return 1;
	}
	NFWStateError("Monitor is not a monitor object, become a monitor to edit.\n");
	return 0;
}
int NFWMonitor::GetVideoModes(int* count, GLFWvidmode* &retModes)
{
	if (active)
	{
		retModes = (GLFWvidmode*)glfwGetVideoModes(m_monitor, count);
		int Error = NFWGetError();
		if (Error != GLFW_NO_ERROR)
		{
			return 0;
		}
		return 1;
	}
	NFWStateError("Monitor is not a monitor object, become a monitor to edit.\n");
	return 0;
}
int NFWMonitor::GetGammaRamp(GLFWgammaramp* &retGammaRamp)
{
	if (active)
	{
		retGammaRamp = (GLFWgammaramp*)glfwGetGammaRamp(m_monitor);
		int Error = NFWGetError();
		if (Error != GLFW_NO_ERROR)
		{
			return 0;
		}
		return 1;
	}
	NFWStateError("Monitor is not a monitor object, become a monitor to edit.\n");
	return 0;
}
int NFWMonitor::SetMonitorUserPointer(void* pointer)
{
	if (active)
	{
		glfwSetMonitorUserPointer(m_monitor, pointer);
		int Error = NFWGetError();
		if (Error != GLFW_NO_ERROR)
		{
			return 0;
		}
		return 1;
	}
	NFWStateError("Monitor is not a monitor object, become a monitor to edit.\n");
	return 0;
}
int NFWMonitor::SetGamma(float gamma)
{
	if (active)
	{
		glfwSetGamma(m_monitor, gamma);
		int Error = NFWGetError();
		if (Error != GLFW_NO_ERROR)
		{
			return 0;
		}
		return 1;
	}
	NFWStateError("Monitor is not a monitor object, become a monitor to edit.\n");
	return 0;
}
int NFWMonitor::SetGammaRamp(const GLFWgammaramp* ramp)
{
	if (active)
	{
		glfwSetGammaRamp(m_monitor, ramp);
		int Error = NFWGetError();
		if (Error != GLFW_NO_ERROR)
		{
			return 0;
		}
		return 1;
	}
	NFWStateError("Monitor is not a monitor object, become a monitor to edit.\n");
	return 0;
}
int NFWMonitor::GetVideoMode(GLFWvidmode* &ret)
{
	if (active)
	{
		ret = (GLFWvidmode*)glfwGetVideoMode(m_monitor);
		int Error = NFWGetError();
		if (Error != GLFW_NO_ERROR)
		{
			return 0;
		}
		return 1;
	}
	NFWStateError("Monitor is not a monitor object, become a monitor to edit.\n");
	return 0;
}
GLFWmonitor* NFWMonitor::GetMonitor()
{
	return m_monitor;
}
NFWMonitor::~NFWMonitor()
{
	
}