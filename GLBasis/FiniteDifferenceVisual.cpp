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

#include <GeometricHelper.h>

#include <thread>
#include "SDFArchive.h"



struct wav4
{
    float l;
    float a;
    float s;
    float dx;
    float dy;
    float z0;
};

void AddQuadFrontFourCorners(const SDFVec3 c0, const SDFVec3 c1, const SDFVec3 c2, const SDFVec3 c3,  SceneObject& object){

    object.AddVertex(c0);
    object.AddVertex(c1);
    object.AddVertex(c2);
    
    object.AddVertex(c0);
    object.AddVertex(c2);
    object.AddVertex(c3);

    const SDFVec3 norm = Cross(Subtract(c1, c0), Subtract(c3, c0));

    object.AddNormal(norm);
    object.AddNormal(norm);
    object.AddNormal(norm);

    object.AddNormal(norm);
    object.AddNormal(norm);
    object.AddNormal(norm);


    object.AddTexcoord({0.0, 0.0});
    object.AddTexcoord({1.0, 0.0});
    object.AddTexcoord({1.0, 1.0});

    object.AddTexcoord({0.0, 0.0});
    object.AddTexcoord({1.0, 1.0});
    object.AddTexcoord({0.0, 1.0});

    object.AddColor({0.0, 1.0, 0.0});
    object.AddColor({0.0, 1.0, 0.0});
    object.AddColor({0.0, 1.0, 0.0});

    object.AddColor({0.0, 1.0, 0.0});
    object.AddColor({0.0, 1.0, 0.0});
    object.AddColor({0.0, 1.0, 0.0});
}

void AddRectangularLineSegment(const SDFVec3 inital, const SDFVec3 destination, float lineRadius, SceneObject& addedObject)
{
    
    //calculate planar basis vectors : not entirely sure this works..
    const SDFVec3 LineVector = Subtract(destination, inital);
    const SDFVec3 SampleVector = Subtract(inital, {0.0,0.0,0.0});
    
    const SDFVec3 ARightAngle = Cross(LineVector,SampleVector);
    const SDFVec3 XAxis = Normalize(Cross(ARightAngle, LineVector));
    const SDFVec3 YAxis = Normalize(Cross(XAxis, LineVector));

    const SDFVec3 TopLeftAdjustment = Add( Multiply(XAxis, -lineRadius), Multiply(YAxis, lineRadius) );
    const SDFVec3 TopRightAdjustment = Add( Multiply(XAxis, lineRadius), Multiply(YAxis, lineRadius) );
    const SDFVec3 BottomLeftAdjustment = Add(Multiply(XAxis, -lineRadius), Multiply(YAxis, -lineRadius));
    const SDFVec3 BottomRightAdjustment = Add(Multiply(XAxis, lineRadius), Multiply(YAxis, -lineRadius));

    const SDFVec3 InitalTopLeftCorner = Add(inital, TopLeftAdjustment);
    const SDFVec3 InitalTopRightCorner = Add(inital, TopRightAdjustment);
    const SDFVec3 InitalBottomLeftCorner = Add(inital, BottomLeftAdjustment);
    const SDFVec3 InitalBottomRightCorner = Add(inital, BottomRightAdjustment);

    
    AddQuadFrontFourCorners(InitalBottomLeftCorner, InitalBottomRightCorner, InitalTopRightCorner, InitalTopLeftCorner, addedObject);

    const SDFVec3 DestinationTopLeftCorner = Add(destination, TopLeftAdjustment);
    const SDFVec3 DestinationTopRightCorner = Add(destination, TopRightAdjustment);
    const SDFVec3 DestinationBottomLeftCorner = Add(destination, BottomLeftAdjustment);
    const SDFVec3 DestinationBottomRightCorner = Add(destination, BottomRightAdjustment);

    AddQuadFrontFourCorners(DestinationBottomLeftCorner, DestinationBottomRightCorner, DestinationTopRightCorner, DestinationTopLeftCorner, addedObject);

    AddQuadFrontFourCorners(InitalBottomRightCorner, DestinationBottomRightCorner,  DestinationTopRightCorner, InitalTopRightCorner, addedObject);
    AddQuadFrontFourCorners(InitalBottomLeftCorner, InitalBottomRightCorner, DestinationBottomRightCorner, DestinationBottomLeftCorner, addedObject);
    AddQuadFrontFourCorners(InitalTopLeftCorner, InitalTopRightCorner, DestinationTopRightCorner, DestinationTopLeftCorner, addedObject);
    AddQuadFrontFourCorners(DestinationBottomLeftCorner, InitalBottomLeftCorner, InitalTopLeftCorner, DestinationTopLeftCorner, addedObject);


}


void AddCuboidFromVolume(const SDFBoundingVolume volume, const int currentScene, int objectID)
{
    SceneObject CuboidVolume(objectID);

    const SDFVec3 FrontNormal = Cross(Subtract({volume.BottomRightBack.x, volume.BottomRightBack.y, volume.TopLeftFront.z}, {volume.TopLeftFront.x, volume.BottomRightBack.y, volume.TopLeftFront.z}), Subtract({volume.BottomRightBack.x, volume.TopLeftFront.y, volume.TopLeftFront.z},{volume.TopLeftFront.x, volume.BottomRightBack.y, volume.TopLeftFront.z}));
    
    CuboidVolume.AddVertex({volume.TopLeftFront.x, volume.BottomRightBack.y, volume.TopLeftFront.z});
    CuboidVolume.AddVertex({volume.BottomRightBack.x, volume.BottomRightBack.y, volume.TopLeftFront.z});
    
    CuboidVolume.AddVertex({volume.BottomRightBack.x, volume.TopLeftFront.y, volume.TopLeftFront.z});
    

    CuboidVolume.AddVertex({volume.TopLeftFront.x, volume.BottomRightBack.y, volume.TopLeftFront.z});
    
    CuboidVolume.AddVertex({volume.BottomRightBack.x, volume.TopLeftFront.y, volume.TopLeftFront.z});
    
    CuboidVolume.AddVertex({volume.TopLeftFront.x, volume.TopLeftFront.y, volume.TopLeftFront.z});
    
    CuboidVolume.AddTexcoord({0.0, 0.0});
    CuboidVolume.AddTexcoord({1.0, 0.0});
    CuboidVolume.AddTexcoord({1.0, 1.0});
    CuboidVolume.AddTexcoord({0.0, 0.0});
    CuboidVolume.AddTexcoord({1.0, 0.0});
    CuboidVolume.AddTexcoord({0.0, 1.0});

    CuboidVolume.AddNormal(FrontNormal);
    CuboidVolume.AddNormal(FrontNormal);
    CuboidVolume.AddNormal(FrontNormal);

    CuboidVolume.AddNormal(FrontNormal);
    CuboidVolume.AddNormal(FrontNormal);
    CuboidVolume.AddNormal(FrontNormal);

    CuboidVolume.AddColor({0.5, 0.5, 0.0});
    CuboidVolume.AddColor({0.5, 0.5, 0.0});
    CuboidVolume.AddColor({0.5, 0.5, 0.0});

    CuboidVolume.AddColor({0.5, 0.5, 0.0}); 
    CuboidVolume.AddColor({0.5, 0.5, 0.0});
    CuboidVolume.AddColor({0.5, 0.5, 0.0});

    const SDFVec3 LeftBottomBack = {volume.TopLeftFront.x, volume.BottomRightBack.y, volume.BottomRightBack.z}, LeftBottomFront = {volume.TopLeftFront.x, volume.BottomRightBack.y, volume.TopLeftFront.z}, LeftTopFront = {volume.TopLeftFront.x, volume.TopLeftFront.y, volume.TopLeftFront.z}, LeftTopBack = {volume.TopLeftFront.x, volume.TopLeftFront.y, volume.BottomRightBack.z};
    const SDFVec3 RightBottomBack = {volume.BottomRightBack.x, volume.BottomRightBack.y, volume.BottomRightBack.z}, RightBottomFront = {volume.BottomRightBack.x, volume.BottomRightBack.y, volume.TopLeftFront.z}, RightTopFront = {volume.BottomRightBack.x, volume.TopLeftFront.y, volume.TopLeftFront.z}, RightTopBack = {volume.BottomRightBack.x, volume.TopLeftFront.y, volume.BottomRightBack.z}; 


    const SDFVec3 LeftNormal = Cross(Subtract(LeftBottomFront,LeftBottomBack), Subtract(LeftTopBack, LeftBottomBack));

    CuboidVolume.AddVertex(LeftBottomBack);
    CuboidVolume.AddVertex(LeftBottomFront);
    CuboidVolume.AddVertex(LeftTopFront);

    CuboidVolume.AddVertex(LeftBottomBack);
    CuboidVolume.AddVertex(LeftTopFront);
    CuboidVolume.AddVertex(LeftTopBack);

    CuboidVolume.AddTexcoord({0.0, 0.0});
    CuboidVolume.AddTexcoord({1.0, 0.0});
    CuboidVolume.AddTexcoord({1.0, 1.0});
    CuboidVolume.AddTexcoord({0.0, 0.0});
    CuboidVolume.AddTexcoord({1.0, 0.0});
    CuboidVolume.AddTexcoord({0.0, 1.0});

    CuboidVolume.AddColor({0.5, 0.8, 0.0});
    CuboidVolume.AddColor({0.5, 0.8, 0.0});
    CuboidVolume.AddColor({0.5, 0.8, 0.0});

    CuboidVolume.AddColor({0.5, 0.8, 0.0}); 
    CuboidVolume.AddColor({0.5, 0.8, 0.0});
    CuboidVolume.AddColor({0.5, 0.8, 0.0});

    CuboidVolume.AddNormal(LeftNormal);
    CuboidVolume.AddNormal(LeftNormal);
    CuboidVolume.AddNormal(LeftNormal);

    CuboidVolume.AddNormal(LeftNormal);
    CuboidVolume.AddNormal(LeftNormal);
    CuboidVolume.AddNormal(LeftNormal);

    const SDFVec3 RightNormal = Cross(Subtract(RightBottomFront,RightBottomBack), Subtract(RightTopBack, RightBottomBack));

    CuboidVolume.AddVertex(RightBottomFront);
    CuboidVolume.AddVertex(RightBottomBack);
    CuboidVolume.AddVertex(RightTopBack);

    CuboidVolume.AddVertex(RightBottomFront);
    CuboidVolume.AddVertex(RightTopBack);
    CuboidVolume.AddVertex(RightTopFront);

    CuboidVolume.AddTexcoord({0.0, 0.0});
    CuboidVolume.AddTexcoord({1.0, 0.0});
    CuboidVolume.AddTexcoord({1.0, 1.0});
    CuboidVolume.AddTexcoord({0.0, 0.0});
    CuboidVolume.AddTexcoord({1.0, 0.0});
    CuboidVolume.AddTexcoord({0.0, 1.0});

    CuboidVolume.AddColor({0.5, 0.8, 0.0});
    CuboidVolume.AddColor({0.5, 0.8, 0.0});
    CuboidVolume.AddColor({0.5, 0.8, 0.0});

    CuboidVolume.AddColor({0.5, 0.8, 0.0}); 
    CuboidVolume.AddColor({0.5, 0.8, 0.0});
    CuboidVolume.AddColor({0.5, 0.8, 0.0});

    CuboidVolume.AddNormal(RightNormal);
    CuboidVolume.AddNormal(RightNormal);
    CuboidVolume.AddNormal(RightNormal);

    CuboidVolume.AddNormal(RightNormal);
    CuboidVolume.AddNormal(RightNormal);
    CuboidVolume.AddNormal(RightNormal);

    


    const SDFVec3 BackNormal = Cross(Subtract(RightBottomBack, LeftBottomBack), Subtract(LeftTopBack, LeftBottomBack));


    CuboidVolume.AddVertex(LeftBottomBack);
    CuboidVolume.AddVertex(RightBottomBack);
    CuboidVolume.AddVertex(RightTopBack);

    CuboidVolume.AddVertex(LeftBottomBack);
    CuboidVolume.AddVertex(RightTopBack);
    CuboidVolume.AddVertex(LeftTopBack);

    CuboidVolume.AddTexcoord({0.0, 0.0});
    CuboidVolume.AddTexcoord({1.0, 0.0});
    CuboidVolume.AddTexcoord({1.0, 1.0});
    CuboidVolume.AddTexcoord({0.0, 0.0});
    CuboidVolume.AddTexcoord({1.0, 0.0});
    CuboidVolume.AddTexcoord({0.0, 1.0});

    CuboidVolume.AddColor({0, 0.8, 0.0});
    CuboidVolume.AddColor({0, 0.8, 0.0});
    CuboidVolume.AddColor({0, 0.8, 0.0});

    CuboidVolume.AddColor({0, 0.8, 0.0}); 
    CuboidVolume.AddColor({0, 0.8, 0.0});
    CuboidVolume.AddColor({0, 0.8, 0.0});

    CuboidVolume.AddNormal(BackNormal);
    CuboidVolume.AddNormal(BackNormal);
    CuboidVolume.AddNormal(BackNormal);

    CuboidVolume.AddNormal(BackNormal);
    CuboidVolume.AddNormal(BackNormal);
    CuboidVolume.AddNormal(BackNormal);

    //const SDFVec3 LeftTopFront = {volume.TopLeftFront.x, volume.TopLeftFront.y, volume.TopLeftFront.z};
    const SDFVec3 TopNormal = Cross(Subtract(RightTopFront, LeftTopFront), Subtract(LeftTopBack, LeftTopFront) );

    CuboidVolume.AddVertex(LeftTopFront);
    CuboidVolume.AddVertex(RightTopFront);
    CuboidVolume.AddVertex(RightTopBack);

    CuboidVolume.AddVertex(LeftTopFront);
    CuboidVolume.AddVertex(RightTopBack);
    CuboidVolume.AddVertex(LeftTopBack);

    CuboidVolume.AddTexcoord({0.0, 0.0});
    CuboidVolume.AddTexcoord({1.0, 0.0});
    CuboidVolume.AddTexcoord({1.0, 1.0});
    CuboidVolume.AddTexcoord({0.0, 0.0});
    CuboidVolume.AddTexcoord({1.0, 0.0});
    CuboidVolume.AddTexcoord({0.0, 1.0});

    CuboidVolume.AddNormal(TopNormal);
    CuboidVolume.AddNormal(TopNormal);
    CuboidVolume.AddNormal(TopNormal);
    CuboidVolume.AddNormal(TopNormal);
    CuboidVolume.AddNormal(TopNormal);
    CuboidVolume.AddNormal(TopNormal);

    CuboidVolume.AddColor({1, 0.0, 1.0});
    CuboidVolume.AddColor({1, 0.8, 1.0});
    CuboidVolume.AddColor({1, 0.8, 1.0});

    CuboidVolume.AddColor({1, 0.8, 0.0}); 
    CuboidVolume.AddColor({1, 0.8, 1.0});
    CuboidVolume.AddColor({0, 0.8, 0.0});

    const SDFVec3 BottomNormal = Cross(Subtract(RightBottomFront, LeftBottomFront), Subtract(LeftBottomBack, LeftBottomFront));

    CuboidVolume.AddVertex(LeftBottomFront);
    CuboidVolume.AddVertex(RightBottomFront);
    CuboidVolume.AddVertex(RightBottomBack);

    CuboidVolume.AddVertex(LeftBottomFront);
    CuboidVolume.AddVertex(RightBottomBack);
    CuboidVolume.AddVertex(LeftBottomBack);

    CuboidVolume.AddTexcoord({0.0, 0.0});
    CuboidVolume.AddTexcoord({1.0, 0.0});
    CuboidVolume.AddTexcoord({1.0, 1.0});
    CuboidVolume.AddTexcoord({0.0, 0.0});
    CuboidVolume.AddTexcoord({1.0, 0.0});
    CuboidVolume.AddTexcoord({0.0, 1.0});

    CuboidVolume.AddNormal(BottomNormal);
    CuboidVolume.AddNormal(BottomNormal);
    CuboidVolume.AddNormal(BottomNormal);
    CuboidVolume.AddNormal(BottomNormal);
    CuboidVolume.AddNormal(BottomNormal);
    CuboidVolume.AddNormal(BottomNormal);

    SceneCenter[currentScene].Objects.push_back(CuboidVolume);
}

void AddCuboidFrame(const SDFBoundingVolume volume, const int currentScene, int objectID)
{
    SceneObject cuboidFrame(objectID);
    
    const SDFVec3 RightBottomFront = {volume.BottomRightBack.x, volume.BottomRightBack.y, volume.TopLeftFront.z};
    const SDFVec3 LeftBottomFront = {volume.TopLeftFront.x, volume.BottomRightBack.y, volume.TopLeftFront.z};
    const SDFVec3 RightTopFront = {volume.BottomRightBack.x, volume.TopLeftFront.y, volume.TopLeftFront.z};
    const SDFVec3 LeftTopFront = {volume.TopLeftFront.x, volume.TopLeftFront.y, volume.TopLeftFront.z};
    

    const SDFVec3 LeftBottomBack = {volume.TopLeftFront.x, volume.BottomRightBack.y, volume.BottomRightBack.z};
    const SDFVec3 RightBottomBack =  {volume.BottomRightBack.x, volume.BottomRightBack.y, volume.BottomRightBack.z};
    const SDFVec3 LeftTopBack = {volume.TopLeftFront.x, volume.TopLeftFront.y, volume.BottomRightBack.z};
    const SDFVec3 RightTopBack = {volume.BottomRightBack.x, volume.TopLeftFront.y, volume.BottomRightBack.z};

    //front
    AddRectangularLineSegment(LeftTopFront, RightTopFront, 0.05, cuboidFrame);
    AddRectangularLineSegment(LeftTopFront, LeftBottomFront, 0.05, cuboidFrame);
    AddRectangularLineSegment(LeftBottomFront, RightBottomFront, 0.05, cuboidFrame);
    AddRectangularLineSegment(RightBottomFront, RightTopFront, 0.05, cuboidFrame);

    //right
    AddRectangularLineSegment(RightBottomFront, RightBottomBack,0.05, cuboidFrame);
    AddRectangularLineSegment(RightBottomFront, RightTopFront,0.05, cuboidFrame);
    AddRectangularLineSegment(RightTopFront, RightTopBack,0.05, cuboidFrame);
    AddRectangularLineSegment(RightBottomBack, RightTopBack,0.05, cuboidFrame);

    //left
    AddRectangularLineSegment(LeftBottomBack, LeftBottomFront,0.05, cuboidFrame);
    AddRectangularLineSegment(LeftBottomBack, LeftTopBack,0.05, cuboidFrame);
    AddRectangularLineSegment(LeftTopBack, RightTopFront,0.05, cuboidFrame);
    AddRectangularLineSegment(LeftBottomFront, LeftTopFront,0.05, cuboidFrame);

    //back
    AddRectangularLineSegment(LeftBottomBack, RightBottomBack,0.05, cuboidFrame);
    AddRectangularLineSegment(LeftBottomBack, LeftTopBack,0.05, cuboidFrame);
    AddRectangularLineSegment(LeftTopBack, RightTopBack,0.05, cuboidFrame);
    AddRectangularLineSegment(RightBottomBack, RightTopBack,0.05, cuboidFrame);

    //top
    AddRectangularLineSegment(LeftTopFront, RightTopFront,0.05, cuboidFrame);
    AddRectangularLineSegment(LeftTopFront, LeftTopBack,0.05, cuboidFrame);
    AddRectangularLineSegment(LeftTopBack, RightTopBack,0.05, cuboidFrame);
    AddRectangularLineSegment(RightTopBack, RightTopFront,0.05, cuboidFrame);

    //bottom
    AddRectangularLineSegment(LeftBottomFront, RightBottomFront,0.05, cuboidFrame);
    AddRectangularLineSegment(LeftBottomFront, LeftBottomBack,0.05, cuboidFrame);
    AddRectangularLineSegment(LeftBottomBack, RightBottomBack,0.05, cuboidFrame);
    AddRectangularLineSegment(RightBottomBack, RightBottomFront,0.05, cuboidFrame);

    SceneCenter[currentScene].Objects.push_back(cuboidFrame);

}


inline SDFVec3 CenterOfVolumeStaticVisualizer(const SDFBoundingVolume volume)
{
    int currentScene = SceneCenter.CreateNewScene();
    
    //problem, this system only supports one primitive type, has memory transfer based inefficencnies and is just the beginning prototype.

    float ZDepth = volume.BottomRightBack.z - volume.TopLeftFront.z;
    float XDepth = volume.BottomRightBack.x - volume.TopLeftFront.x;
    float YDepth = volume.TopLeftFront.y - volume.BottomRightBack.y;
    return {XDepth/2, YDepth/2, ZDepth/2};
}


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
#define WS "X:\\1.4 C++\\Vscode\\GLBasis\\"


void inverse2x2(double* A, double* invA) {
    double detA = A[0] * A[3] - A[1] * A[2];

    // Check if the matrix is invertible
    if (detA != 0) {
        double invDetA = 1.0 / detA;

        // Calculate the inverse matrix
        invA[0] = A[3] * invDetA;
        invA[1] = -A[1] * invDetA;
        invA[2] = -A[2] * invDetA;
        invA[3] = A[0] * invDetA;
    } else {
       invA[0] = A[0];
       invA[1] = A[1];
       invA[2] = A[2];
       invA[3] = A[3];
    }
}

void vecmul2(double* A, double* x, double* result)
{

    result[0] = (A[0] * x[0]) + (A[1] * x[1]);
    result[1] = (A[2] * x[0]) + (A[3] * x[1]);

}

void mul4(double*  A, double K, double* result)
{
    result[0] = A[0] * K;
    result[1] = A[1] * K;
    result[2] = A[2] * K;
    result[3] = A[3] * K;
}


void LoadQuadTriangulation(SDFVec3 a, SDFVec3 b, SDFVec3 c, SDFVec3 d, std::vector<vec3>& VertexVector, std::vector<vec3>& NormalVector, std::vector<vec2>& Texcoords)
{
    SDFVec3 Normal = Cross(Subtract(b,a),Subtract(d,a));

    vec3 vNormal = {Normal.x, Normal.y, Normal.z};

    Texcoords.push_back({0.0, 0.0});
    Texcoords.push_back({1.0, 0.0});
    Texcoords.push_back({1.0, 1.0});

    Texcoords.push_back({0.0, 0.0});
    Texcoords.push_back({1.0, 1.0});
    Texcoords.push_back({0.0, 1.0});

    VertexVector.push_back({a.x, a.y, a.z});
    VertexVector.push_back({b.x, b.y, b.z});
    VertexVector.push_back({c.x, c.y, c.z});

    VertexVector.push_back({a.x, a.y, a.z});
    VertexVector.push_back({c.x, c.y, c.z});
    VertexVector.push_back({d.x, d.y, d.z});

    NormalVector.push_back(vNormal);
    NormalVector.push_back(vNormal);
    NormalVector.push_back(vNormal);
    NormalVector.push_back(vNormal);
    NormalVector.push_back(vNormal);
    NormalVector.push_back(vNormal);

}

void DisplacableRod(float L, int subDivisions, int horizontalSubdivison, float radius, std::vector<vec3>& VertexVector, std::vector<vec3>& NormalVector, std::vector<vec2>& Texcoords)
{

    // SDFVec3 d1 = {-1,0,0};
    // SDFVec3 d2 = {1,0,0};
    // SDFVec3 d3 = {1,1,0};
    // SDFVec3 d4 = {-1,1,0};
    // LoadQuadTriangulation(d1,d2,d3,d4, VertexVector, NormalVector, Texcoords);
    // return;


    float subStep = (2*3.14159)/subDivisions;
    float horzSubStep = 1.0f/horizontalSubdivison;

    SDFVec3 leftCenterCircle = {-1.0, 0.2, 0.1};
    SDFVec3 rightCenterCircle = {1.0, 0.3, 0.0};

    

    SDFVec3 axis = Subtract(rightCenterCircle,leftCenterCircle);

    SDFVec3 crossAxis = Cross(axis, rightCenterCircle);
    SDFVec3 axis1 = Cross(crossAxis, rightCenterCircle);
    SDFVec3 initalCenterCircle = leftCenterCircle;

    
    
    SDFVec3 c1, c2, c3, c4;
    for(float i = 0.0; i < (2*3.14159); i += subStep)
    {   
        leftCenterCircle = {-1.0, 0.3, 0.2};
        // SDFVec3 propulsion = Multiply(axis, 1);
        // rightCenterCircle = Add(initalCenterCircle, propulsion);
        // SDFVec3 c1 = {(leftCenterCircle.x) + (radius*cos(i)*crossAxis.x) + (radius*sin(i)*axis1.x), (leftCenterCircle.y) + (radius*cos(i)*crossAxis.y) + (radius*sin(i)*axis1.y), (leftCenterCircle.z) + (radius*cos(i)*crossAxis.z) + (radius*sin(i)*axis1.z)};
        // SDFVec3 c2 = {(rightCenterCircle.x) + (radius*cos(i)*crossAxis.x) + (radius*sin(i)*axis1.x), (rightCenterCircle.y) + (radius*cos(i)*crossAxis.y) + (radius*sin(i)*axis1.y), (rightCenterCircle.z) + (radius*cos(i)*crossAxis.z) + (radius*sin(i)*axis1.z)};
        // SDFVec3 c4 = {(leftCenterCircle.x) + (radius*cos(i+subStep)*crossAxis.x) + (radius*sin(i+subStep)*axis1.x), (leftCenterCircle.y) + (radius*cos(i+subStep)*crossAxis.y) + (radius*sin(i+subStep)*axis1.y), (leftCenterCircle.z) + (radius*cos(i+subStep)*crossAxis.z) + (radius*sin(i+subStep)*axis1.z)};
        // SDFVec3 c3 = {(rightCenterCircle.x) + (radius*cos(i+subStep)*crossAxis.x) + (radius*sin(i+subStep)*axis1.x), (rightCenterCircle.y) + (radius*cos(i+subStep)*crossAxis.y) + (radius*sin(i+subStep)*axis1.y), (rightCenterCircle.z) + (radius*cos(i+subStep)*crossAxis.z) + (radius*sin(i+subStep)*axis1.z)};

        // LoadQuadTriangulation(c1,c2,c3,c4, VertexVector, NormalVector, Texcoords);

        for(int j = 1; j <= horizontalSubdivison; j++)
        {
            
            SDFVec3 propulsion = Multiply(axis, (j*horzSubStep));
            rightCenterCircle = Add(initalCenterCircle, propulsion);
            SDFVec3 c1 = {(leftCenterCircle.x) + (radius*cos(i)*crossAxis.x) + (radius*sin(i)*axis1.x), (leftCenterCircle.y) + (radius*cos(i)*crossAxis.y) + (radius*sin(i)*axis1.y), (leftCenterCircle.z) + (radius*cos(i)*crossAxis.z) + (radius*sin(i)*axis1.z)};
            SDFVec3 c2 = {(rightCenterCircle.x) + (radius*cos(i)*crossAxis.x) + (radius*sin(i)*axis1.x), (rightCenterCircle.y) + (radius*cos(i)*crossAxis.y) + (radius*sin(i)*axis1.y), (rightCenterCircle.z) + (radius*cos(i)*crossAxis.z) + (radius*sin(i)*axis1.z)};
            SDFVec3 c4 = {(leftCenterCircle.x) + (radius*cos(i+subStep)*crossAxis.x) + (radius*sin(i+subStep)*axis1.x), (leftCenterCircle.y) + (radius*cos(i+subStep)*crossAxis.y) + (radius*sin(i+subStep)*axis1.y), (leftCenterCircle.z) + (radius*cos(i+subStep)*crossAxis.z) + (radius*sin(i+subStep)*axis1.z)};
            SDFVec3 c3 = {(rightCenterCircle.x) + (radius*cos(i+subStep)*crossAxis.x) + (radius*sin(i+subStep)*axis1.x), (rightCenterCircle.y) + (radius*cos(i+subStep)*crossAxis.y) + (radius*sin(i+subStep)*axis1.y), (rightCenterCircle.z) + (radius*cos(i+subStep)*crossAxis.z) + (radius*sin(i+subStep)*axis1.z)};
            leftCenterCircle = rightCenterCircle;
            LoadQuadTriangulation(c1,c2,c3,c4, VertexVector, NormalVector, Texcoords);

        }

        // leftCenterCircle = rightCenterCircle;

        // rightCenterCircle = {1.0, 0.3, 0.0};

        // c1 = {(leftCenterCircle.x) + (radius*cos(i)*crossAxis.x) + (radius*sin(i)*axis1.x), (leftCenterCircle.y) + (radius*cos(i)*crossAxis.y) + (radius*sin(i)*axis1.y), (leftCenterCircle.z) + (radius*cos(i)*crossAxis.z) + (radius*sin(i)*axis1.z)};
        // c2 = {(rightCenterCircle.x) + (radius*cos(i)*crossAxis.x) + (radius*sin(i)*axis1.x), (rightCenterCircle.y) + (radius*cos(i)*crossAxis.y) + (radius*sin(i)*axis1.y), (rightCenterCircle.z) + (radius*cos(i)*crossAxis.z) + (radius*sin(i)*axis1.z)};
        // c4 = {(leftCenterCircle.x) + (radius*cos(i+subStep)*crossAxis.x) + (radius*sin(i+subStep)*axis1.x), (leftCenterCircle.y) + (radius*cos(i+subStep)*crossAxis.y) + (radius*sin(i+subStep)*axis1.y), (leftCenterCircle.z) + (radius*cos(i+subStep)*crossAxis.z) + (radius*sin(i+subStep)*axis1.z)};
        // c3 = {(rightCenterCircle.x) + (radius*cos(i+subStep)*crossAxis.x) + (radius*sin(i+subStep)*axis1.x), (rightCenterCircle.y) + (radius*cos(i+subStep)*crossAxis.y) + (radius*sin(i+subStep)*axis1.y), (rightCenterCircle.z) + (radius*cos(i+subStep)*crossAxis.z) + (radius*sin(i+subStep)*axis1.z)};
        // LoadQuadTriangulation(c1,c2,c3,c4, VertexVector, NormalVector, Texcoords);

       
        
    }
}

int main()
{


#pragma region Init

    bool debugO = true;

    if(!glfwInit()){return 0;}
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE,GL_TRUE);
    if(debugO)
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


#pragma endregion


#pragma region Shaders
    NGLProgram program = CreateShader(WS "shaders/StiffnessRod.vs", WS "shaders/StiffnessRod.fs");
    program.UseProgram();
#pragma endregion

#pragma region UnpackInitalScene

    float L = 1.0;
    double A = 0.5;

    float uniaxialStress = 0.2;
    float strain = 0.3;
    double E = uniaxialStress/strain;

    float F = 5;

    float rodData[] = {-1.0, 0.2, 0.1, 1.0, 0.3, 0.0};

    double Stiffness[4] = {1/L, -1/L, -1/L, 1/L};
    double ConstantStiffness[4];
    double Force[2] = {-(F * (L/2)), -(F * (L/2))};
    double NodalDisplacements[2];
    double IL[4];

    inverse2x2(Stiffness, IL);
    mul4(IL, ((-E*A)/L), ConstantStiffness);
    vecmul2(ConstantStiffness, Force, NodalDisplacements);


    std::vector<vec3> VertexVector;
    std::vector<vec3> NormalVector;
    std::vector<vec2> Texcoords;

    DisplacableRod(L, 20, 20, A, VertexVector,  NormalVector, Texcoords);

    int vertices = VertexVector.size();

    NGLVertexArray vertexarray;
    vertexarray.GenerateVertexArray();

    NGLBuffer vertex, normal, texcoords;
    vertex.GenerateBuffer();
    normal.GenerateBuffer();
    texcoords.GenerateBuffer();

    vertexarray.BindVertexArray();

    vertex.BindBuffer(GL_ARRAY_BUFFER);
    vertex.BufferData((vertices*3)  * sizeof(float), VertexVector.data(), GL_STATIC_DRAW);
    vertexarray.VertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    vertexarray.EnableVertexAttribArray(0);

    normal.BindBuffer(GL_ARRAY_BUFFER);
    normal.BufferData((vertices*3)  * sizeof(float), NormalVector.data(), GL_STATIC_DRAW);
    vertexarray.VertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    vertexarray.EnableVertexAttribArray(1);

    texcoords.BindBuffer(GL_ARRAY_BUFFER);
    texcoords.BufferData((vertices*2)  * sizeof(float), Texcoords.data(), GL_STATIC_DRAW);
    vertexarray.VertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    vertexarray.EnableVertexAttribArray(2);


    vertex.Unbind(GL_ARRAY_BUFFER);
    vertexarray.UnbindVertexArray();

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

    float forceDirection[] = {0.0, 1.0, 0.0};
    setVec3(program,"forceDirection", forceDirection);

    while (!glfwWindowShouldClose(window))
    {
        
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

        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        projection = glm::perspective(glm::radians(fov), 640.0f / 480.0f, 0.1f, 100.0f);
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        //setFloat(program, "time", currentFrame);

        set2Vec3Array(program, "nodalLocation", rodData);
        setMat4(program, "model", model);
        setMat4(program, "view", view);
        setMat4(program, "projection", projection);

        vertexarray.BindVertexArray();
        glDrawArrays(GL_TRIANGLES, 0, vertices);


        ImGui_ImplGlfwGL3_NewFrame();
        {
                
            

                ImGui::Begin("Salad");

                bool OnF = ImGui::SliderFloat("F", &F, 0.0, 1.0);
                bool OnE = ImGui::SliderFloat("uniaxialStress", &uniaxialStress, 0.0, 10.0);
                bool OnA = ImGui::SliderFloat("strain", &strain, 0.0, 10.0);
                
                bool OnD = ImGui::SliderFloat3("Direction", forceDirection, -1.0, 1.0);


                if(OnD)
                {
                    setVec3(program,"forceDirection", forceDirection);
                }

                if(OnF || OnE || OnA)
                {
                    E = uniaxialStress/strain;
                    inverse2x2(Stiffness, IL);
                    mul4(IL, ((-E*A)/L), ConstantStiffness);
                    vecmul2(ConstantStiffness, Force, NodalDisplacements);
                    
                    
                    setVec2(program, "nodalDisplacement", glm::vec2(NodalDisplacements[0], NodalDisplacements[1]));
                }   

                ImGui::End();
                
                
                
                

        }
        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 1;
}