#include <stdio.h>
#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <imgui/imgui.h>
#include "imgui/imgui_impl_glfw_gl3.h"
#include "WindowStats.h"

#include <algorithm>

void APIENTRY glDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity,
    GLsizei length, const char* message, const void* userParam) {
    // ignore non-significant error/warning codes
    if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

    std::cout << "---------------" << std::endl;
    std::cout << "Debug message (" << id << "): " << message << std::endl;

    switch (source)
    {
    case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
    case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
    case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
    } std::cout << std::endl;

    switch (type)
    {
    case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
    case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
    case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
    case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
    case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
    case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
    case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
    } std::cout << std::endl;

    switch (severity)
    {
    case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
    case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
    case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
    case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
    } std::cout << std::endl;
    std::cout << std::endl;
    throw("bad");
}
void FrameBufferResize(GLFWwindow *window, int width, int height)
{
    WindowContext* windowContext = (WindowContext*)glfwGetWindowUserPointer(window);

    glViewport(0, 0, width, height);
    windowContext->windowDimensions.vx = width;
    windowContext->windowDimensions.vy = height;
}
void WindowResize(GLFWwindow *window, int width, int height)
{
    WindowContext* windowContext = (WindowContext*)glfwGetWindowUserPointer(window);

    windowContext->windowDimensions.wx = width;
    windowContext->windowDimensions.wy = height;
}
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {

    WindowContext* windowContext = (WindowContext*)glfwGetWindowUserPointer(window);
    if(!windowContext)
    {
        return;
    }
    cameraBaseClass* activeCamera = windowContext->activeCamera;
    double xpos,ypos;
    glfwGetCursorPos(window,  &xpos, &ypos);

    
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        //GlobalInputContainer.SendClick(window, activeCamera, xpos, ypos);
    }
}

GLFWwindow* CreateContext()
{
    bool debugO = true;
    if(!glfwInit()){return 0;}
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE,GL_TRUE);
    //glfwWindowHint(GLFW_SAMPLES, 4);
    if(debugO)
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    
    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(1024, 768, "Hello World", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        //throw std::range_error("Did not load context of window.");
    }

    WindowContext* windowContext = new WindowContext;
    windowContext->activeCamera = 0;
    windowContext->windowDimensions.wx = 1024;
    windowContext->windowDimensions.wy = 768;
    windowContext->windowDimensions.vx = 1024;
    windowContext->windowDimensions.vy = 768;

    glfwSetWindowUserPointer(window, windowContext);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    
    if(glewInit() != GLEW_OK)
    {
        printf("%s\n", "GLEW not initialized correctly.");
    }

    if(debugO)
    {
        int flags;
        glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
        if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
        {
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

            glDebugMessageCallback(glDebugOutput, nullptr);
            glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
        }
     }

    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(window, true);
    ImGui::StyleColorsDark();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwSetFramebufferSizeCallback(window, FrameBufferResize);
    glfwSetWindowSizeCallback(window, WindowResize);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);

    return window;
}

int main()
{
    GLFWwindow* window = CreateContext();


    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.0,0.0,0.0,1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



        ImGui_ImplGlfwGL3_NewFrame();
        {
            ImGui::Begin("Salad Menu");
        

            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    glfwDestroyWindow(window);

    return 1;
}