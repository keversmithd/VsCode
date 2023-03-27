#include <iostream>
#include <LearnOpenglHelper.h>
#include "CL/cl.h"
#include <math.h>
#include <algorithm>

#include <imgui/imgui.h>
#include "imgui/imgui_impl_glfw_gl3.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

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
    std::cout << "resized" << std::endl;
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
    // glfwSetWindowRefreshCallback(window, refreshCallback);
    // glfwSetWindowFocusCallback(window, focusCallback);
    // glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    // glfwSetWindowSizeCallback(window, windowSizeCallback);
    // glfwSetWindowPosCallback(window, windowSizeCallback);


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

    glEnable(GL_DEPTH_TEST);


#pragma endregion

#pragma region LoadingTexture
stbi_set_flip_vertically_on_load(true);

int width, height, nrChannels;
unsigned char *data = stbi_load(WS "frog.jpg", &width, &height, &nrChannels, 0); 

if(!data){return -1;}

NGLTexture texture;
texture.GenerateTexture();
texture.BindTexture(GL_TEXTURE_2D);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

texture.TexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
glGenerateMipmap(GL_TEXTURE_2D);

stbi_image_free(data);

#pragma endregion

#pragma region Shaders

    int error = 0;
    NGLProgram nglProgram = CreateShader(WS "shaders/phong.vs", WS "haders/phong.fs");
    NGLProgram lightSourceProgram = CreateShader(WS "shaders/lightSource.vs", WS "shaders/lightSource.fs");


    
#pragma endregion

#pragma region vertexes

//Unit Plane
float TexplaneData[16]
{
    -1.0f, -1.0f, 0.0f, 0.0f,
     1.0f, -1.0f, 1.0f, 0.0f,
     1.0f, 1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 0.0f, 1.0f
};

unsigned int at[] = { 0,1,2,3,2,0 };


const GLfloat CubicTexcoords[] = 
{
    0.000059f, 1.0f-0.000004f,
    0.000103f, 1.0f-0.336048f,
    0.335973f, 1.0f-0.335903f,
    1.000023f, 1.0f-0.000013f,
    0.667979f, 1.0f-0.335851f,
    0.999958f, 1.0f-0.336064f,
    0.667979f, 1.0f-0.335851f,
    0.336024f, 1.0f-0.671877f,
    0.667969f, 1.0f-0.671889f,
    1.000023f, 1.0f-0.000013f,
    0.668104f, 1.0f-0.000013f,
    0.667979f, 1.0f-0.335851f,
    0.000059f, 1.0f-0.000004f,
    0.335973f, 1.0f-0.335903f,
    0.336098f, 1.0f-0.000071f,
    0.667979f, 1.0f-0.335851f,
    0.335973f, 1.0f-0.335903f,
    0.336024f, 1.0f-0.671877f,
    1.000004f, 1.0f-0.671847f,
    0.999958f, 1.0f-0.336064f,
    0.667979f, 1.0f-0.335851f,
    0.668104f, 1.0f-0.000013f,
    0.335973f, 1.0f-0.335903f,
    0.667979f, 1.0f-0.335851f,
    0.335973f, 1.0f-0.335903f,
    0.668104f, 1.0f-0.000013f,
    0.336098f, 1.0f-0.000071f,
    0.000103f, 1.0f-0.336048f,
    0.000004f, 1.0f-0.671870f,
    0.336024f, 1.0f-0.671877f,
    0.000103f, 1.0f-0.336048f,
    0.336024f, 1.0f-0.671877f,
    0.335973f, 1.0f-0.335903f,
    0.667969f, 1.0f-0.671889f,
    1.000004f, 1.0f-0.671847f,
    0.667979f, 1.0f-0.335851f

};


const GLfloat CubicVerticies[] =
{
    -1.0f,-1.0f,-1.0f, // triangle 1 : begin
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, // triangle 1 : end
    1.0f, 1.0f,-1.0f, // triangle 2 : begin
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f, // triangle 2 : end
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f

};

const GLfloat CubicNormals[] = 
{
   -1.0f ,0.0f ,0.0f,
-1.0f ,0.0f ,0.0f,
-1.0f ,0.0f ,0.0f,
-0.0f ,0.0f ,-1.0f,
-0.0f ,0.0f ,-1.0f,
-0.0f ,0.0f ,-1.0f,
0.0f ,-1.0f ,-0.0f,
0.0f ,-1.0f ,-0.0f,
0.0f ,-1.0f ,-0.0f,
0.0f ,-0.0f ,-1.0f,
0.0f ,-0.0f ,-1.0f,
0.0f ,-0.0f ,-1.0f,
-1.0f ,0.0f ,0.0f,
-1.0f ,0.0f ,0.0f,
-1.0f ,0.0f ,0.0f,
-0.0f ,-1.0f ,0.0f,
-0.0f ,-1.0f ,0.0f,
-0.0f ,-1.0f ,0.0f,
0.0f ,0.0f ,1.0f,
0.0f ,0.0f ,1.0f,
0.0f ,0.0f ,1.0f,
1.0f ,0.0f ,0.0f,
1.0f ,0.0f ,0.0f,
1.0f ,0.0f ,0.0f,
1.0f ,0.0f ,0.0f,
1.0f ,0.0f ,0.0f,
1.0f ,0.0f ,0.0f,
0.0f ,1.0f ,0.0f,
0.0f ,1.0f ,0.0f,
0.0f ,1.0f ,0.0f,
0.0f ,1.0f ,0.0f,
0.0f ,1.0f ,0.0f,
0.0f ,1.0f ,0.0f,
0.0f ,0.0f ,1.0f,
0.0f ,0.0f ,1.0f,
0.0f ,0.0f ,1.0f,
};

const GLuint CubicIndexes[] =
{
    //front
    0, 1, 2,
    0, 2, 3,

    //back
    4, 5, 6,
    4, 6, 7,

    //right
    1, 5, 6,
    1, 6, 2,

    //left
    0, 4, 7,
    0, 7, 3,

    //top
    3, 2, 6,
    3, 6, 7,

    //bottom
    0, 1, 5,
    0, 5, 4,
};

#pragma endregion

#pragma region NonLightSourceCube
    NGLVertexArray vertexarray;
    vertexarray.GenerateVertexArray();
    
    NGLBuffer vertex,index,texcoord, normals;

    vertex.GenerateBuffer();
    index.GenerateBuffer();
    texcoord.GenerateBuffer();
    normals.GenerateBuffer();

    vertexarray.BindVertexArray();
    vertex.BindBuffer(GL_ARRAY_BUFFER);
    vertex.BufferData(sizeof(CubicVerticies), CubicVerticies, GL_STATIC_DRAW);
    vertexarray.VertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    vertexarray.EnableVertexAttribArray(0);

    texcoord.BindBuffer(GL_ARRAY_BUFFER);
    texcoord.BufferData(sizeof(CubicTexcoords), CubicTexcoords, GL_STATIC_DRAW);
    vertexarray.VertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0,  (GLvoid*)0);
    vertexarray.EnableVertexAttribArray(1);

    normals.BindBuffer(GL_ARRAY_BUFFER);
    normals.BufferData(sizeof(CubicNormals), CubicNormals, GL_STATIC_DRAW);
    vertexarray.VertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0,  (GLvoid*)0);
    vertexarray.EnableVertexAttribArray(2);


    vertex.Unbind(GL_ARRAY_BUFFER);
    vertexarray.UnbindVertexArray();

#pragma endregion

#pragma region LightSourceCube
NGLVertexArray LSVertexArra;
    LSVertexArra.GenerateVertexArray();
    
    LSVertexArra.BindVertexArray();

    vertex.BindBuffer(GL_ARRAY_BUFFER);

    LSVertexArra.VertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    LSVertexArra.EnableVertexAttribArray(0);

    LSVertexArra.UnbindVertexArray();

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

#pragma region LightSourceMVP

glm::mat4 model2 = glm::mat4(1.0f);

model2 = glm::rotate(model2, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

#pragma endregion

#pragma region lighUniforms

#pragma endregion

    float cameraSpeed = 0.5f; // adjust accordingly
    double curPosx = 0.0f;
    double curPosy = 0.0f;
    float deltaTime = 0.0f;	// Time between current frame and last frame
    float lastFrame = 0.0f; // Time of last frame
    float currentFrame = 0.0f;

    glm::vec3 lightPos(3.0f, 0.0f, 0.0f);

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

        glClearColor(1.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        lightPos = glm::vec3(3*cos(glfwGetTime()), 3*cos(glfwGetTime()), 0.0f);

        lightSourceProgram.UseProgram();

        

        model2 = glm::mat4(1.0f);
        model2 = glm::translate(model2, lightPos);
        model2 = glm::scale(model2, glm::vec3(0.2f));

        setMat4(lightSourceProgram, "view", view);
        setMat4(lightSourceProgram, "projection", projection);
        setMat4(lightSourceProgram, "model", model2);

        LSVertexArra.BindVertexArray();
        glDrawArrays(GL_TRIANGLES, 0, sizeof(CubicVerticies)/sizeof(GLfloat));


        nglProgram.UseProgram();

        projection = glm::perspective(glm::radians(fov), 640.0f / 480.0f, 0.1f, 100.0f);
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        setVec3(nglProgram, "lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        setVec3(nglProgram, "viewPos", cameraPos);
        setVec3(nglProgram, "lightPos", lightPos);
        setMat4(nglProgram, "model", model);
        setMat4(nglProgram, "view", view);
        setMat4(nglProgram, "projection", projection);

        texture.BindTexture(GL_TEXTURE_2D);
        vertexarray.BindVertexArray();
        //glDrawElements(GL_TRIANGLES, sizeof(CubicIndexes)/sizeof(GLuint), GL_UNSIGNED_INT, (void*)0);
        glDrawArrays(GL_TRIANGLES, 0, sizeof(CubicVerticies)/sizeof(GLfloat));
        glBindTexture(GL_TEXTURE_2D, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 1;
}