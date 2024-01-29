#include <stdio.h>
#include "OpenGLTools/OpenGLToolBox.h"

#include <imgui/imgui.h>
#include "imgui/imgui_impl_glfw_gl3.h"

#include "ADPAsioDevice.h"

#include "CustomCallback.h"



void APIENTRY glDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity,
                            GLsizei length, const char *message, const void *userParam)
{
    // ignore non-significant error/warning codes
    if (id == 131169 || id == 131185 || id == 131218 || id == 131204)
        return;

    std::cout << "---------------" << std::endl;
    std::cout << "Debug message (" << id << "): " << message << std::endl;

    switch (source)
    {
    case GL_DEBUG_SOURCE_API:
        std::cout << "Source: API";
        break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
        std::cout << "Source: Window System";
        break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
        std::cout << "Source: Shader Compiler";
        break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:
        std::cout << "Source: Third Party";
        break;
    case GL_DEBUG_SOURCE_APPLICATION:
        std::cout << "Source: Application";
        break;
    case GL_DEBUG_SOURCE_OTHER:
        std::cout << "Source: Other";
        break;
    }
    std::cout << std::endl;

    switch (type)
    {
    case GL_DEBUG_TYPE_ERROR:
        std::cout << "Type: Error";
        break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        std::cout << "Type: Deprecated Behaviour";
        break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        std::cout << "Type: Undefined Behaviour";
        break;
    case GL_DEBUG_TYPE_PORTABILITY:
        std::cout << "Type: Portability";
        break;
    case GL_DEBUG_TYPE_PERFORMANCE:
        std::cout << "Type: Performance";
        break;
    case GL_DEBUG_TYPE_MARKER:
        std::cout << "Type: Marker";
        break;
    case GL_DEBUG_TYPE_PUSH_GROUP:
        std::cout << "Type: Push Group";
        break;
    case GL_DEBUG_TYPE_POP_GROUP:
        std::cout << "Type: Pop Group";
        break;
    case GL_DEBUG_TYPE_OTHER:
        std::cout << "Type: Other";
        break;
    }
    std::cout << std::endl;

    switch (severity)
    {
    case GL_DEBUG_SEVERITY_HIGH:
        std::cout << "Severity: high";
        break;
    case GL_DEBUG_SEVERITY_MEDIUM:
        std::cout << "Severity: medium";
        break;
    case GL_DEBUG_SEVERITY_LOW:
        std::cout << "Severity: low";
        break;
    case GL_DEBUG_SEVERITY_NOTIFICATION:
        std::cout << "Severity: notification";
        break;
    }
    std::cout << std::endl;
    std::cout << std::endl;
    throw("bad");
}
void FrameBufferResize(GLFWwindow *window, int width, int height)
{
    WindowContext *windowContext = (WindowContext *)glfwGetWindowUserPointer(window);

    glViewport(0, 0, width, height);
    windowContext->windowDimensions.vx = width;
    windowContext->windowDimensions.vy = height;
}
void WindowResize(GLFWwindow *window, int width, int height)
{
    WindowContext *windowContext = (WindowContext *)glfwGetWindowUserPointer(window);

    windowContext->windowDimensions.wx = width;
    windowContext->windowDimensions.wy = height;
}
void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{

    WindowContext *windowContext = (WindowContext *)glfwGetWindowUserPointer(window);
    if (!windowContext)
    {
        return;
    }
    cameraBaseClass *activeCamera = windowContext->activeCamera;
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        // GlobalInputContainer.SendClick(window, activeCamera, xpos, ypos);
    }
}

GLFWwindow *CreateContext()
{
    bool debugO = true;
    if (!glfwInit())
    {
        return 0;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    // glfwWindowHint(GLFW_SAMPLES, 4);
    if (debugO)
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow *window = glfwCreateWindow(1024, 768, "Hello World", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        // throw std::range_error("Did not load context of window.");
    }

    WindowContext *windowContext = new WindowContext;
    windowContext->activeCamera = 0;
    windowContext->windowDimensions.wx = 1024;
    windowContext->windowDimensions.wy = 768;
    windowContext->windowDimensions.vx = 1024;
    windowContext->windowDimensions.vy = 768;

    glfwSetWindowUserPointer(window, windowContext);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
    {
        printf("%s\n", "GLEW not initialized correctly.");
    }

    if (debugO)
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

    GLFWwindow *window = CreateContext();

    char currentDriverName[20] = "";

    AsioDevice device;

    // device.SetBufferSwitchBehaviour(ProcessingStep);
    device.StartAsioDevice("Focusrite USB ASIO");
    device.Start();

    device.callbacks.SetBufferSwitchTimeInfo(BitSnapper);

    bool CreationMenuOpen = false;
    char expressionBuffer[50] = "";
    int start = 0;
    int end = 0;

    // POPExpression function;
    // function.Parse("5*cos(processedSamples/10)");
    // double _multiVal = function.multival({{"processedSamples", 22}, {"sampleRate", 0}});
    //printf("%f\n", );

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplGlfwGL3_NewFrame();
        {
            ImGui::Begin("Salad Menu");

            ImGui::InputText("Driver Name", currentDriverName, 20);

            bool Start = ImGui::Button("Start");
            if(Start)
            {
                device.Start();
            }

            bool Exit = ImGui::Button("Exit");
            if (Exit)
            {
                device.Exit();
            }

            bool StopDriverButton = ImGui::Button("Stop Driver");

            if(StopDriverButton)
            {
                device.Stop();
            }

            bool StartDriverButton = ImGui::Button("Start Driver");

            if(StartDriverButton)
            {
                device.StartAsioDevice(currentDriverName);
                device.Start();
            }

            ImGui::SameLine(); // Move to the same line as the previous content
            ImGui::BeginChild("List Of Bitspaces");


                ImGui::SliderInt("ProbeStart", &BitSpaces[0].start, 0, 4096);
                ImGui::SliderInt("ProbeEnd", &BitSpaces[0].end, 0, 4096);


                ImGui::Text("List Of Bitspaces");
                
                for(int i = 0; i < BitSpaces.size(); i++)
                {   
                    std::string label = "BitSpace"+std::to_string(i);
                    ImGui::InputText(label.c_str(), BitSpaces[i].expression, 50);
                    ImGui::SameLine();
                    bool Update = ImGui::Button((label+"Update").c_str());

                    if(Update)
                    {
                        BitSpaces[i].function.Parse(BitSpaces[i].expression);
                    }
                    bool Delete = ImGui::Button((label + "Delete").c_str());
                    if(Delete)
                    {
                        BitSpaces.erase(BitSpaces.begin() + i);
                    }
                }

                bool CreateNew = ImGui::Button("Create");

                if (CreationMenuOpen)
                {
                    ImGui::Begin("Creation Menu");
                    ImGui::InputText("Expression", expressionBuffer, 50);
                    ImGui::InputInt("Start", &start);
                    ImGui::InputInt("End", &end);
                    bool CloseThis = ImGui::Button("Close Expression Menu");
                    if(CloseThis)
                    {
                        CreationMenuOpen = false;
                    }

                    bool Add = ImGui::Button("Add");

                    if(Add)
                    {

                        BitSpaces.push_back(BitSpace(start, end, expressionBuffer));
                    }

                    ImGui::End();
                }

                if(CreateNew && !CreationMenuOpen)
                {
                    CreationMenuOpen = true;
                }

                ImGui::EndChild(); // End the child window

                ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    glfwDestroyWindow(window);

   
}