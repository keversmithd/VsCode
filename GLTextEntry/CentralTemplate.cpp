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




vec3* GenerateTwoDimensionalAxis(const vec2 XDimensionality, const vec2 YDimensionality, double dx, double dy, int& size)
{
    int xsteps = (XDimensionality.y - XDimensionality.x)/dx;
    int ysteps = (YDimensionality.y - XDimensionality.x)/dx;

    int e = 4 + xsteps + ysteps;
    vec3* data = new vec3[(e*2)];
    size = (e*2);

    int datapointer = 0;

    for(int i = 0; i < xsteps; i++)
    {
        float currentx = (XDimensionality.x + i * dx);

        data[datapointer] = {currentx, YDimensionality.x, 0};
        data[datapointer+1] = {currentx, YDimensionality.y, 0};
        
        datapointer+=2;
        
    }

    for(int j = 0; j <= ysteps; j++)
    {
        float currenty = (YDimensionality.x + (j * dy));

        data[datapointer] = {XDimensionality.x, currenty, 0};
        data[datapointer+1] = {XDimensionality.y, currenty, 0};
        
        datapointer+=2;
    }

    return data;

}

GLFWwindow* CreateContext()
{
    bool debugO = true;
    if(!glfwInit()){return 0;}
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE,GL_TRUE);
    if(debugO)
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    
    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(1024, 768, "Hello World", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        throw std::range_error("Did not load context of window.");
    }
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
    return window;
}


int main()
{


#pragma region Init

    
    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = CreateContext();

    LoadCharacterAtlas("C:\\Users\\Dust\\Desktop\\Joan-Regular.ttf");

    //Previous Quad Controller
    FullQuadController Texture_Viewer;
    Texture_Viewer.texture = CharacterAtlas;

    //Atlas Tester
    AtlasText TextRenderer;
    TextRenderer.AddText(0, 0, -0.1, 0.01, "!CG!");
    TextRenderer.AddText(0, 0.6, -0.001, 0.001, "!!!");
    TextRenderer.SetupBuffers();

    char e = '!';
    AtlasCharacter ch = AtlasCharacters[e];

    float scale = 0.01;

    //QuickTesting
    float sq[] =
    {
        0.0, 0.0, -0.1,
        ch.Size.x * scale, 0.0, -0.1,
        ch.Size.x * scale, ch.Size.y*scale, -0.1,

        0.0, 0.0, -0.1,
        ch.Size.x * scale, ch.Size.y*scale, -0.1,
        0.0, ch.Size.y*scale, -0.1,
    };

    float squv[] =
    {
        ch.BottomLeft.x, ch.BottomLeft.y,
        ch.TopRight.x, ch.BottomLeft.y,
        ch.TopRight.x, ch.TopRight.y,

        ch.BottomLeft.x, ch.BottomLeft.y,
        ch.TopRight.x, ch.TopRight.y,
        ch.BottomLeft.x, ch.TopRight.y,
    };

    QuickRender AtlasSub;
    AtlasSub.SetUpBuffers(sq, squv, sizeof(sq), sizeof(squv));


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    Camera MainCamera;
    MainCamera.MakeActiveCamera(window);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    GraphicVector v({-1.0, -1.0, 0.0}, {1.0, 1.0, 0.0});

    while (!glfwWindowShouldClose(window))
    {
        
        MainCamera.proccessInput(window);

        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        setMat4(TextRenderer.program, "projection", MainCamera.projection);
        setMat4(TextRenderer.program, "view", MainCamera.view);

        TextRenderer.Draw();
        v.DrawElements(MainCamera);

        ImGui_ImplGlfwGL3_NewFrame();
        {
            
        }

        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 1;
}