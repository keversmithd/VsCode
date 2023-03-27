#ifndef NFWIN
#define NFWIN

#include "NFWDebug.h"

struct NFWWindow
{
private:
	GLFWwindow* m_window;
	bool active;
public:
	NFWWindow();
	int MakeWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
	int DestroyWindow();
	int ShouldClose();
	int SetWindowCloseCallback(GLFWwindowclosefun cb);
	int SetWindowSizeCallback(GLFWwindowsizefun cb);
	int SetFramebufferSizeCallback(GLFWframebuffersizefun cb);
	int SetWindowContentScaleCallback(GLFWwindowcontentscalefun cb);
	int SetWindowPosCallback(GLFWwindowposfun cb);
	int SetWindowIconifyCallback(GLFWwindowiconifyfun cb);
	int SetWindowMaximizeCallback(GLFWwindowmaximizefun cb);
	int SetWindowRefreshCallback(GLFWwindowrefreshfun cb);
	int SetWindowFocusCallback(GLFWwindowfocusfun cb);
	int SetMouseButtonCallback(GLFWmousebuttonfun cb){  } //glfwSetCharCallback // glfwSetCharModsCallback() //glfwSetDropCallback //implement all callbacks and set up default callback system
	int SetWindowMonitor(GLFWmonitor* monitor, int 	xpos, int  ypos, int width, int height, int refreshRate);
	int SetWindowSize(int width, int height);
	int SetWindowSizeLimits(int minwidth, int minheight, int maxwidth, int maxheight);
	int SetWindowAspectRatio(int numer, int denom);
	int SetWindowPos(int xpos, int ypos);
	int SetWindowTitle(const char* title);
	int SetWindowIcon(int count, const GLFWimage* images);
	int SetWindowAttrib(int attrib, int value);
	int SetWindowUserPointer(void* ptr);
	int SetWindowOpacity(float t);
	int GetWindowSize(int* width, int* height);
	int GetWindowFrameSize(int* left, int* top, int* right, int* bottom);
	int GetFramebufferSize(int* width, int* height);
	int GetWindowContentScale(float* xscale, float* yscale);
	int GetWindowPos(int* xpos, int* ypos);
	int GetWindowAttrib(int attrib, int* ret);
	int GetWindowUserPointer(void* &ret);
	int GetWindowOpacity(float* ret);
	int GetWindowMonitor(GLFWmonitor* &ret);
	int IconifyWindow();
	int RestoreWindow();
	int MaximizeWindow();
	int HideWindow();
	int ShowWindow();
	int FocusWindow();
	GLFWwindow* GetWindow();
	int RequestWindowAttention();
	~NFWWindow();
};

#endif
