#include <iostream>
#include <LearnOpenglHelper.h>
#include "CL/cl.h"
#include <math.h>
#include <algorithm>

#include <imgui/imgui.h>
#include "imgui/imgui_impl_glfw_gl3.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

#include <GeometricHelper.h>

#include <thread>


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
}

void refreshCallback(GLFWwindow* window)
{
    std::cout << "refreshed" << std::endl;

}

void focusCallback(GLFWwindow* window, int focused)
{
    std::cout << "focused" << std::endl;
}

void framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0,0, width, height);
    //passing scene context to update the perspective matrix
}

void windowPosCallback(GLFWwindow *window, int xpos, int ypos)
{
    std::cout << "window pos" << std::endl;
}

void windowSizeCallback(GLFWwindow *window, int width, int height)
{
    std::cout << "windowSized" << std::endl;

}

float lastX = 320, lastY = 240;
float yaw = -90, pitch = 0;
float fov = 45;
bool firstMouse = true;
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
  
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; 
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    //fov += 2;
    // if (fov < 1.0f)
    //     fov = 1.0f;
    // if (fov > 45.0f)
    //     fov = 45.0f; 
}
#define WS "X:\\1.4 C++\\Vscode\\Class CMAKE Template - Copy\\"

int main()
{

#pragma region Init
    if(!glfwInit()){return 0;}
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE,GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    
    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glfwSetScrollCallback(window, scroll_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetWindowSizeCallback(window, windowSizeCallback);

    if(glewInit() != GLEW_OK)
    {
        printf("%s\n", "GLEW not initialized correctly.");
    }

    int flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
    {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

        glDebugMessageCallback(glDebugOutput, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);

    }


    ImGui::CreateContext();
        ImGui_ImplGlfwGL3_Init(window, true);
        ImGui::StyleColorsDark();
    glEnable(GL_DEPTH_TEST);


#pragma endregion


#pragma region Shaders

    int error = 0;
    NGLProgram StaticSceneRenderer = CreateShader(WS "vertex.glsl", WS "fragment.glsl");

#pragma endregion

#pragma region UnpackInitalScene

 

NGLBuffer SceneBuffer;
SceneBuffer.GenerateBuffer();

int maximumSceneSize = MaximumSceneBufferSize(SceneCenter);
LoadCurrentScene(SceneCenter, SceneBuffer, maximumSceneSize);

#pragma endregion


#pragma region NonLightSourceMVP

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    glm::mat4 view = glm::mat4(1.0f);

    glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
    
    glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
    // note that we're translating the scene in the reverse direction of where we want to move
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); 

    bool ortho = false;
    glm::mat4 projection;
    projection = (ortho) ? glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f) : glm::perspective(glm::radians(fov), 640.0f / 480.0f, 0.1f, 100.0f);

#pragma endregion

    float cameraSpeed = 0.5f; // adjust accordingly
    double curPosx = 0.0f;
    double curPosy = 0.0f;
    float deltaTime = 0.0f;	// Time between current frame and last frame
    float lastFrame = 0.0f; // Time of last frame
    float currentFrame = 0.0f;

    glm::vec3 lightPos(3.0f, 0.0f, 0.0f);
    glm::vec3 lightambient = glm::vec3(0.2f, 0.2f, 0.2f), lightdiffuse = glm::vec3(0.5f, 0.5f, 0.5f), lightspecular = glm::vec3(1.0f, 1.0f, 1.0f);
    float shininess = 32.0f;;

    while (!glfwWindowShouldClose(window))
    {
        //set camera
        
#pragma region proccessInput

        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame; 
        cameraSpeed = 2.0f * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

        glfwGetCursorPos(window, &curPosx, &curPosy);
       
#pragma endregion

        glClearColor(1.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 1;
}