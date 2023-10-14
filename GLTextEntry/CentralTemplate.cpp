#include <iostream>
#include <LearnOpenglHelper.h>
#include "CL/cl.h"
#include <math.h>
#include <algorithm>

#include <imgui/imgui.h>
#include "imgui/imgui_impl_glfw_gl3.h"
#include <SDFArchive.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#include "fon.h"

#include <thread>
#include "SDFArchive.h"

#include "FullScreenQuad.h"
#include "AtlasTester.h"
#include "Camera.h"
#include "GraphicVector.h"
#include "UVSphere.h"
#include "InputBox.h"
#include "UVSphereFactory.h"
#include "MappedPlane.h"


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
    glViewport(0, 0, width, height);
    GlobalWindowStats.vx = width;
    GlobalWindowStats.vy = height;
}
void WindowResize(GLFWwindow *window, int width, int height)
{
    GlobalWindowStats.wx = width;
    GlobalWindowStats.wy = height;
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {

    Camera* activeCamera = (Camera*)glfwGetWindowUserPointer(window);
    double xpos,ypos;
    glfwGetCursorPos(window,  &xpos, &ypos);
    if(!activeCamera)
    {
        return;
    }
    
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        GlobalInputContainer.SendClick(window, activeCamera, xpos, ypos);
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
        throw std::range_error("Did not load context of window.");
    }

    
    

    GlobalWindowStats.wx = 1024;
    GlobalWindowStats.wy = 768;
    GlobalWindowStats.vx = 1024;
    GlobalWindowStats.vy = 768;

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
    
    //glEnable(GL_MULTISAMPLE);

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
#pragma region Init

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = CreateContext();

    LoadCharacterAtlas("X:\\Videos\\MonsoonLife\\Euler-Math.otf");

    //Previous Quad Controller
    FullQuadController Texture_Viewer;
    Texture_Viewer.texture = CharacterAtlas;

    AtlasText TextRenderer;
    TextRenderer.AddText(0, 0, -0.01, 0.01, "hello mike");
    TextRenderer.SetupBuffers();

    Camera MainCamera;
    MainCamera.MakeActiveCamera(window);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));


    AtlasAlignedText alignedText;
    alignedText.AddAlignedText({-1.0, -1.0, 0.0}, {1.0, 1.0, 0.0}, "hello mike", 0.2, 0.2);
    GraphicVector AlignmentAxis({-1.0, -1.0, 0.0}, {1.0, 1.0, 0.0});

    InputBoxUpdate b({{-1,-1,0},{-1.3,-1.5,0.7}});
    UVSphereFactory SphereFactory(3);
    
    MappedViewFrustrum frustrum;
    MappedPlane plane(&SphereFactory);
    plane.AttachToViewFrustrum(&frustrum);
    plane.CreateNormalPlane({-0.5,0,-0.5},{0,0,-1}, 1.0f, 1.0f);



    std::vector<SDFVec3> PlaneLines = 
    {
        {0,0,0},{1,1,0},
        {0,0,0},{1,2,0},
    };
    PlaneProjection projectionTest({-0.5,0,-0.5},{0,0,-1},1.0f, 1.0f, PlaneLines);
    projectionTest.AttachToMappedPlane(plane);

    double lastTime = glfwGetTime();
    int nbFrames = 0;
    float fcx = 0.0f, fcz = 0.0f;
    while (!glfwWindowShouldClose(window))
    {
        double currentTime = glfwGetTime();
        nbFrames++;
        if ( currentTime - lastTime >= 1.0 ){ // If last prinf() was more than 1 sec ago
            // printf and reset timer

            glfwSetWindowTitle(window, std::to_string(double(nbFrames)).c_str());
            nbFrames = 0;
            lastTime += 1.0;
        }
            
        MainCamera.proccessInput(window);

        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        frustrum.Draw(MainCamera);
        plane.Draw(MainCamera);
        projectionTest.Draw(MainCamera);
        
        ImGui_ImplGlfwGL3_NewFrame();
        {
            ImGui::Begin("Salad Menu");
            float ffar = 0.5f;
           
            float dx = 0.0f;
            float dz = 0.0f;
            bool Slid = ImGui::SliderAngle("Near", &ffar, 0.2f, 100.0f);
            bool U = ImGui::SliderAngle("dx", &dx, -1.0f, 1.0f);
            bool Z = ImGui::SliderAngle("dz", &dz, -1.0f, 1.0f);
            float R = 0.0;
            bool T = ImGui::SliderAngle("theta", &R, -360.f, 360.0f);

            bool Click = ImGui::Button("ButtonNOw");
            
            if(Slid || U || Z || T)
            {
                fcx  += dx*0.1f;
                dx = 0;
                fcz += dz*0.1f;
                dz = 0;
                frustrum.UpdateFrustrum({fcx ,fcz,0},{cosf(R),sinf(R),-1},{0,1,0}, 0.1f, ffar, 90.0f);
                
            }

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