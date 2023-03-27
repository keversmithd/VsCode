#include  "NFWWindow.h"

NFWWindow::NFWWindow()
{
	m_window = nullptr;
	active = false;
}
int NFWWindow::MakeWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
{
	if (active)
	{
		NFWStateError("Window already created and cannot be regeneated, delete in order to continue.\n");
		return 0;
	}
	m_window = glfwCreateWindow(width, height, title, monitor, share);
	int Error = NFWGetError();
	if (Error != GLFW_NO_ERROR)
	{
		return 0;
	}

	active = true;
	return 1;
}
int NFWWindow::DestroyWindow()
{
	if (active)
	{
		glfwDestroyWindow(m_window);
		int Error = NFWGetError();
		if (Error != GLFW_NO_ERROR)
		{
			return 0;
		}
		active = false;
		return 1;
	}
	NFWStateError("Window doesn't exit, create window to continue.\n");
	return 0;

}
int NFWWindow::ShouldClose()
{

	if (active)
	{
		int ShouldCloseStatus = glfwWindowShouldClose(m_window);
		int Error = NFWGetError();
		if (Error != GLFW_NO_ERROR)
		{
			return 0;
		}
		return ShouldCloseStatus;
	}
	NFWStateError("Window doesn't exit, create window to continue.\n");
	return 0;

}
int NFWWindow::SetWindowCloseCallback(GLFWwindowclosefun cb)
{
	if (active)
	{
		glfwSetWindowCloseCallback(m_window, cb);
		int Error = NFWGetError();
		if (Error != GLFW_NO_ERROR)
		{
			return 0;
		}
		return 1;
	}
	NFWStateError("Window doesn't exit, create window to continue.\n");
	return 0;
}
int NFWWindow::SetWindowSizeCallback(GLFWwindowsizefun cb)
{
	if (active)
	{
		glfwSetWindowSizeCallback(m_window,cb);
		int Error = NFWGetError();
		if (Error != GLFW_NO_ERROR)
		{
			return 0;
		}
		return 1;
	}
	NFWStateError("Window doesn't exit, create window to continue.\n");
	return 0;
}
int NFWWindow::SetFramebufferSizeCallback(GLFWframebuffersizefun cb)
{
	if (active)
	{
		glfwSetFramebufferSizeCallback(m_window, cb);
		int Error = NFWGetError();
		if (Error != GLFW_NO_ERROR)
		{
			return 0;
		}
		return 1;
	}
	NFWStateError("Window doesn't exit, create window to continue.\n");
	return 0;
}
int NFWWindow::SetWindowContentScaleCallback(GLFWwindowcontentscalefun cb)
{
	if (active)
	{
		glfwSetWindowContentScaleCallback(m_window, cb);
		int Error = NFWGetError();
		if (Error != GLFW_NO_ERROR)
		{
			return 0;
		}
		return 1;
	}
	NFWStateError("Window doesn't exit, create window to continue.\n");
	return 0;
}
int NFWWindow::SetWindowPosCallback(GLFWwindowposfun cb)
{
	if (active)
	{
		glfwSetWindowPosCallback(m_window, cb);
		int Error = NFWGetError();
		if (Error != GLFW_NO_ERROR)
		{
			return 0;
		}
		return 1;
	}
	NFWStateError("Window doesn't exit, create window to continue.\n");
	return 0;
}
int NFWWindow::SetWindowIconifyCallback(GLFWwindowiconifyfun cb)
{
	if (active)
	{
		glfwSetWindowIconifyCallback(m_window, cb);
		int Error = NFWGetError();
		if (Error != GLFW_NO_ERROR)
		{
			return 0;
		}
		return 1;
	}
	NFWStateError("Window doesn't exit, create window to continue.\n");
	return 0;
}
int NFWWindow::SetWindowMaximizeCallback(GLFWwindowmaximizefun cb)
{
	if (active)
	{
		glfwSetWindowMaximizeCallback(m_window, cb);
		int Error = NFWGetError();
		if (Error != GLFW_NO_ERROR)
		{
			return 0;
		}
		return 1;
	}
	NFWStateError("Window doesn't exit, create window to continue.\n");
	return 0;
}
int NFWWindow::SetWindowRefreshCallback(GLFWwindowrefreshfun cb)
{
	if (active)
	{
		glfwSetWindowRefreshCallback(m_window, cb);
		int Error = NFWGetError();
		if (Error != GLFW_NO_ERROR)
		{
			return 0;
		}
		return 1;
	}
	NFWStateError("Window doesn't exit, create window to continue.\n");
	return 0;
}
int NFWWindow::SetWindowFocusCallback(GLFWwindowfocusfun cb)
{
	if (active)
	{
		glfwSetWindowFocusCallback(m_window, cb);
		int Error = NFWGetError();
		if (Error != GLFW_NO_ERROR)
		{
			return 0;
		}
		return 1;
	}
	NFWStateError("Window doesn't exit, create window to continue.\n");
	return 0;
}
int NFWWindow::SetWindowMonitor(GLFWmonitor* monitor, int 	xpos, int  ypos, int width, int height, int refreshRate)
{
	if (active)
	{
		glfwSetWindowMonitor(m_window, monitor, xpos, ypos, width, height, refreshRate);
		int Error = NFWGetError();
		if (Error != GLFW_NO_ERROR)
		{
			return 0;
		}
		return 1;
	}
	NFWStateError("Window doesn't exit, create window to continue.\n");
	return 0;
}
int NFWWindow::SetWindowSize(int width, int height)
{
	if (active)
	{
		glfwSetWindowSize(m_window, width, height);
		int Error = NFWGetError();
		if (Error != GLFW_NO_ERROR)
		{
			return 0;
		}
		return 1;
	}
	NFWStateError("Window doesn't exit, create window to continue.\n");
	return 0;
}
int NFWWindow::SetWindowSizeLimits(int minwidth, int minheight, int maxwidth, int maxheight)
{
	if (active)
	{
		glfwSetWindowSizeLimits(m_window, minwidth, minheight, maxwidth, maxheight);
		int Error = NFWGetError();
		if (Error != GLFW_NO_ERROR)
		{
			return 0;
		}
		return 1;
	}
	NFWStateError("Window doesn't exit, create window to continue.\n");
	return 0;
}
int NFWWindow::SetWindowAspectRatio(int numer, int denom)
{
	if (active)
	{
		glfwSetWindowAspectRatio(m_window, numer, denom);
		int Error = NFWGetError();
		if (Error != GLFW_NO_ERROR)
		{
			return 0;
		}
		return 1;
	}
	NFWStateError("Window doesn't exit, create window to continue.\n");
	return 0;
}
int NFWWindow::SetWindowPos(int xpos, int ypos)
{
	if (active)
	{
		glfwSetWindowPos(m_window, xpos, ypos);
		int Error = NFWGetError();
		if (Error != GLFW_NO_ERROR)
		{
			return 0;
		}
		return 1;
	}
	NFWStateError("Window doesn't exit, create window to continue.\n");
	return 0;
}
int NFWWindow::SetWindowTitle(const char* title)
{
	if (active)
	{
		glfwSetWindowTitle(m_window, title);
		int Error = NFWGetError();
		if (Error != GLFW_NO_ERROR)
		{
			return 0;
		}
		return 1;
	}
	NFWStateError("Window doesn't exit, create window to continue.\n");
	return 0;
}
int NFWWindow::SetWindowIcon(int count, const GLFWimage* images)
{
	if (active)
	{
		glfwSetWindowIcon(m_window, count, images);
		int Error = NFWGetError();
		if (Error != GLFW_NO_ERROR)
		{
			return 0;
		}
		return 1;
	}
	NFWStateError("Window doesn't exit, create window to continue.\n");
	return 0;
}
int NFWWindow::SetWindowAttrib(int attrib, int value)
{
	if (active)
	{
		glfwSetWindowAttrib(m_window, attrib, value);
		int Error = NFWGetError();
		if (Error != GLFW_NO_ERROR)
		{
			return 0;
		}
		return 1;
	}
	NFWStateError("Window doesn't exit, create window to continue.\n");
	return 0;
}
int NFWWindow::SetWindowUserPointer(void* ptr)
{
	if (active)
	{
		glfwSetWindowUserPointer(m_window, ptr);
		int Error = NFWGetError();
		if (Error != GLFW_NO_ERROR)
		{
			return 0;
		}
		return 1;
	}
	NFWStateError("Window doesn't exit, create window to continue.\n");
	return 0;
}
int NFWWindow::SetWindowOpacity(float t)
{
	if (active)
	{
		glfwSetWindowOpacity(m_window, t);
		int Error = NFWGetError();
		if (Error != GLFW_NO_ERROR)
		{
			return 0;
		}
		return 1;
	}
	NFWStateError("Window doesn't exit, create window to continue.\n");
	return 0;
}
int NFWWindow::GetWindowSize(int* width, int* height)
{
	if (active)
	{
		glfwGetWindowSize(m_window, width, height);
		int Error = NFWGetError();
		if (Error != GLFW_NO_ERROR)
		{
			return 0;
		}
		return 1;
	}
	NFWStateError("Window doesn't exit, create window to continue.\n");
	return 0;
}
int NFWWindow::GetWindowFrameSize(int* left, int* top, int* right, int* bottom)
{
	if (active)
	{
		glfwGetWindowFrameSize(m_window, left, top, right, bottom);
		int Error = NFWGetError();
		if (Error != GLFW_NO_ERROR)
		{
			return 0;
		}
		return 1;
	}
	NFWStateError("Window doesn't exit, create window to continue.\n");
	return 0;
}
int NFWWindow::GetFramebufferSize(int* width, int* height)
{
	if (active)
	{
		glfwGetFramebufferSize(m_window, width, height);
		int Error = NFWGetError();
		if (Error != GLFW_NO_ERROR)
		{
			return 0;
		}
		return 1;
	}
	NFWStateError("Window doesn't exit, create window to continue.\n");
	return 0;
}
int NFWWindow::GetWindowContentScale(float* xscale, float* yscale)
{
	if (active)
	{
		glfwGetWindowContentScale(m_window, xscale, yscale);
		int Error = NFWGetError();
		if (Error != GLFW_NO_ERROR)
		{
			return 0;
		}
		return 1;
	}
	NFWStateError("Window doesn't exit, create window to continue.\n");
	return 0;
}
int NFWWindow::GetWindowPos(int* xpos, int* ypos)
{
	if (active)
	{
		glfwGetWindowPos(m_window, xpos, ypos);
		int Error = NFWGetError();
		if (Error != GLFW_NO_ERROR)
		{
			return 0;
		}
		return 1;
	}
	NFWStateError("Window doesn't exit, create window to continue.\n");
	return 0;
}
int NFWWindow::GetWindowAttrib(int attrib, int* ret)
{
	if (active)
	{
		int attribret = glfwGetWindowAttrib(m_window, attrib);
		*ret = attribret;
		int Error = NFWGetError();
		if (Error != GLFW_NO_ERROR)
		{
			return 0;
		}
		return 1;
	}
	NFWStateError("Window doesn't exit, create window to continue.\n");
	return 0;
}
int NFWWindow::GetWindowUserPointer(void* &ret)
{
	if (active)
	{
		void* usr_ret = glfwGetWindowUserPointer(m_window);
		ret = usr_ret;
		int Error = NFWGetError();
		if (Error != GLFW_NO_ERROR)
		{
			return 0;
		}
		return 1;
	}
	NFWStateError("Window doesn't exit, create window to continue.\n");
	return 0;
}
int NFWWindow::GetWindowOpacity(float* ret)
{
	if (active)
	{
		*ret = glfwGetWindowOpacity(m_window);
		int Error = NFWGetError();
		if (Error != GLFW_NO_ERROR)
		{
			return 0;
		}
		return 1;
	}
	NFWStateError("Window doesn't exit, create window to continue.\n");
	return 0;
}
int NFWWindow::GetWindowMonitor(GLFWmonitor* &monitor)
{
	if (active)
	{
		monitor = glfwGetWindowMonitor(m_window);
		int Error = NFWGetError();
		if (Error != GLFW_NO_ERROR)
		{
			return 0;
		}
		return 1;
	}
	NFWStateError("Window doesn't exit, create window to continue.\n");
	return 0;
}
int NFWWindow::IconifyWindow()
{
	if (active)
	{
		glfwIconifyWindow(m_window);
		int Error = NFWGetError();
		if (Error != GLFW_NO_ERROR)
		{
			return 0;
		}
		return 1;
	}
	NFWStateError("Window doesn't exit, create window to continue.\n");
	return 0;
}
int NFWWindow::RestoreWindow()
{
	if (active)
	{
		glfwRestoreWindow(m_window);
		int Error = NFWGetError();
		if (Error != GLFW_NO_ERROR)
		{
			return 0;
		}
		return 1;
	}
	NFWStateError("Window doesn't exit, create window to continue.\n");
	return 0;
}
int NFWWindow::MaximizeWindow()
{
	if (active)
	{
		glfwMaximizeWindow(m_window);
		int Error = NFWGetError();
		if (Error != GLFW_NO_ERROR)
		{
			return 0;
		}
		return 1;
	}
	NFWStateError("Window doesn't exit, create window to continue.\n");
	return 0;
}
int NFWWindow::HideWindow()
{
	if (active)
	{
		glfwMaximizeWindow(m_window);
		int Error = NFWGetError();
		if (Error != GLFW_NO_ERROR)
		{
			return 0;
		}
		return 1;
	}
	NFWStateError("Window doesn't exit, create window to continue.\n");
	return 0;
}
int NFWWindow::ShowWindow()
{
	if (active)
	{
		glfwShowWindow(m_window);
		int Error = NFWGetError();
		if (Error != GLFW_NO_ERROR)
		{
			return 0;
		}
		return 1;
	}
	NFWStateError("Window doesn't exit, create window to continue.\n");
	return 0;
}
int NFWWindow::FocusWindow()
{
	if (active)
	{
		glfwFocusWindow(m_window);
		int Error = NFWGetError();
		if (Error != GLFW_NO_ERROR)
		{
			return 0;
		}
		return 1;
	}
	NFWStateError("Window doesn't exit, create window to continue.\n");
	return 0;
}
int NFWWindow::RequestWindowAttention()
{
	if (active)
	{
		glfwRequestWindowAttention(m_window);
		int Error = NFWGetError();
		if (Error != GLFW_NO_ERROR)
		{
			return 0;
		}
		return 1;
	}
	NFWStateError("Window doesn't exit, create window to continue.\n");
	return 0;
}
GLFWwindow* NFWWindow::GetWindow()
{
	return m_window;
}
NFWWindow::~NFWWindow() 
{
	DestroyWindow();
}