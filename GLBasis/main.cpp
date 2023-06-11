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
#include "SDFArchive.h"

// struct vec4
// {
//     float x,y,z,w;
// };


struct wav4
{
    float l;
    float a;
    float s;
    float dx;
    float dy;
    float z0;
    float z1;
    float z2;
};



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

std::vector<vec4> SubdividedPlane(float gap, double width, double height)
{
    std::vector<vec4> mesh;

    double wstep = width/gap;
    double hstep = height/gap;

    for(int i = 0; i < wstep; i++)
    {
        
        for(int j = 0; j < hstep; j++)
        {
            vec4 bottomLet = {j*gap, 0.0, i*gap, 1.0};
            vec4 bottomRight = {(j+1)*gap, 0.0, i*gap, 1.0};
            vec4 TopRight = {(j+1)*gap, 0.0, (i+1)*gap, 1.0};
            vec4 TopLeft = {(j)*gap, 0.0, (i+1)*gap, 1.0};
             mesh.push_back(bottomLet);
            mesh.push_back(bottomRight);
            mesh.push_back(TopRight);
            mesh.push_back(bottomLet);
            mesh.push_back(TopRight);
            mesh.push_back(TopLeft);
        }
        

       


    }


    return mesh;

}


void TriangulateQuad(vec3 A, vec3 B, vec3 C, vec3 D, std::vector<vec3>& Verticies, std::vector<vec2>& UVs)
{

    Verticies.push_back(A);
    Verticies.push_back(B);
    Verticies.push_back(C);

    Verticies.push_back(A);
    Verticies.push_back(C);
    Verticies.push_back(D);


    vec2 AUV = {1.0, 1.0};
    UVs.push_back(AUV);
    UVs.push_back(AUV);
    UVs.push_back(AUV);

    UVs.push_back(AUV);
    UVs.push_back(AUV);
    UVs.push_back(AUV);

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
    GLFWwindow* window = glfwCreateWindow(1024, 768, "Hello World", nullptr, nullptr);
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
    NGLProgram program = CreateShader(WS "shaders/wavewater.vs", WS "shaders/wavewater.fs");
#pragma endregion

#pragma region


#pragma region UnpackInitalScene

    float uvpackage[] =
    {
       0.0, 0.0,
       1.0, 0.0,
       1.0, 1.0,
       0.0, 0.0,
       1.0, 1.0,
       0.0, 1.0,
    };

    NGLProgram FrameBufferProgram = CreateShader(WS "shaders/WaveToTexture.vs",WS "shaders/WaveToTexture.fs");
    
    std::vector<vec3> QuadVertex;
    std::vector<vec2> QuadUV;

    TriangulateQuad({-1,-1,0}, {1,-1,0}, {1,1,0}, {-1,1,0}, QuadVertex, QuadUV);

    NGLVertexArray FramebufferRenderVertexArray;
    FramebufferRenderVertexArray.GenerateVertexArray();
    FramebufferRenderVertexArray.BindVertexArray();
    NGLBuffer FrameBufferVertexBuffer;
    FrameBufferVertexBuffer.GenerateBuffer();
    FrameBufferVertexBuffer.BindBuffer(GL_ARRAY_BUFFER);
    FrameBufferVertexBuffer.BufferData(sizeof(vec3) * QuadVertex.size(), QuadVertex.data(), GL_STATIC_DRAW);
    FramebufferRenderVertexArray.EnableVertexAttribArray(0);
    FramebufferRenderVertexArray.VertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    NGLBuffer FrameBuferUVBuffer;
    FrameBuferUVBuffer.GenerateBuffer();
    FrameBuferUVBuffer.BindBuffer(GL_ARRAY_BUFFER);
    FrameBuferUVBuffer.BufferData(sizeof(vec2) * 6, uvpackage, GL_STATIC_DRAW);
    FramebufferRenderVertexArray.EnableVertexAttribArray(1);
    FramebufferRenderVertexArray.VertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

    // NGLTexture WaveNormalMap;
    // WaveNormalMap.GenerateTexture();
    // WaveNormalMap.BindTexture(GL_TEXTURE_2D);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // WaveNormalMap.TexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 256, 0, GL_RGBA, GL_FLOAT, NULL);

    //COSINE LOOK UP TABLE
    NGLTexture CosineLookupTable;
    CosineLookupTable.GenerateTexture();
    CosineLookupTable.BindTexture(GL_TEXTURE_1D);
    
    CosineLookupTable.TexImage1D(GL_TEXTURE_1D, 0, GL_RGB, 256, 0, GL_RGB, GL_FLOAT, 0);

    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    //FRAME BUFFER OBJECT
    unsigned int CosineFrameBuffer;
    glGenFramebuffers(1, &CosineFrameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, CosineFrameBuffer);
    
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, CosineLookupTable.ReferenceTexture(), 0);
    GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, DrawBuffers);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        printf("\nWent Wrong\n");
    }

    //RENDERING LOOKUP TABLE
    NGLProgram CosinFrameBufferProgram = CreateShader(WS "shaders/WaveToTextureLookupTable.vs",WS "shaders/WaveToTextureLookupTable.fs");
    NGLProgram TableLookup = CreateShader(WS "shaders/WaveToWaterTextureLookup.vs",WS "shaders/WaveToWaterTextureLookup.fs");

    glViewport(0,0,256,1);
    CosinFrameBufferProgram.UseProgram();
    FramebufferRenderVertexArray.BindVertexArray();
    glBindFramebuffer(GL_FRAMEBUFFER, CosineFrameBuffer);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0,0,1024,768);


    //RenderingDone

    std::vector<vec4> PlanarMesh = SubdividedPlane(0.05, 1.0, 1.0);
    int vertices = PlanarMesh.size();

    NGLVertexArray vertexarray;
    vertexarray.GenerateVertexArray();

    NGLBuffer vertex;
    vertex.GenerateBuffer();

    vertexarray.BindVertexArray();
    vertex.BindBuffer(GL_ARRAY_BUFFER);
    vertex.BufferData(PlanarMesh.size()  * sizeof(vec4), PlanarMesh.data(), GL_STATIC_DRAW);
    vertexarray.VertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    vertexarray.EnableVertexAttribArray(0);

    vertex.Unbind(GL_ARRAY_BUFFER);
    vertexarray.UnbindVertexArray();



    double ai = 0.0; //height from the water plane to the wave crest
    double L = 0.0; //the crest-to-crest distance between waves in world space. Wavelength L relates to frequency w as w = 2pi/L.
    double w =  (2*3.14)/L;
    double S = 0.0; //the distance the crest moves forward per second. It is convenient to express speed as phase-constant. phi swirl
    double phiswirl = S * w;
    double D = 0.0; //the horizontal vector perpendicular to the wave front along which the crest travels
    
    NGLBuffer waveInformation;
    
    std::vector<wav4> waveData;
    waveData.push_back({1.0, 0.0, 0.1, 0.0, 1.0, 0.0, 0.0, 0.0});
    waveData.push_back({0.4, 0.4, 0.7, 0.0, 1.0, 0.0, 0.0, 0.0});
    waveData.push_back({0.1, 0.1, 0.1, 0.0, 1.0, 0.0, 0.0, 0.0});

    wav4 wavedata[] =
    {
        {1.0, 0, 0.1, 0.0, 1.0, 0.0, 0.0, 0.0},
        {1.0, 0, 0.1, 0.0, 1.0, 0.0, 0.0, 0.0},
        {1.0, 0, 0.1, 0.0, 1.0, 0.0, 0.0, 0.0}
    };

    int NumberOfWaves = 3;


    unsigned int m_program;
    const char* m = "michael";

    waveInformation.GenerateBuffer();
    waveInformation.BindBuffer(GL_UNIFORM_BUFFER);
    waveInformation.BufferData(sizeof(wav4)*NumberOfWaves, wavedata, GL_STATIC_DRAW);
    waveInformation.Unbind(GL_UNIFORM_BUFFER);



    setUniformBlock(program, "WaveBuffer", 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_1D, CosineLookupTable.ReturnTexture());
    setInt(FrameBufferProgram, "table", 0);
    setInt(TableLookup, "WaveTexture", 0);

    setUniformBlock(FrameBufferProgram, "WaveBuffer", 0);
    
    waveInformation.BindBufferBase(GL_UNIFORM_BUFFER, 0);
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

        // projection = glm::perspective(glm::radians(fov), 640.0f / 480.0f, 0.1f, 100.0f);
        // view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        // setFloat(program, "time", currentFrame);
        // setInt(program, "numberofwaves", NumberOfWaves);
        
        // setMat4(program, "model", model);
        // setMat4(program, "view", view);
        // setMat4(program, "projection", projection);

        // program.UseProgram();
        // vertexarray.BindVertexArray();
        // glDrawArrays(GL_TRIANGLES, 0, vertices);

        


        // TableLookup.UseProgram();
        // FramebufferRenderVertexArray.BindVertexArray();
        // glDrawArrays(GL_TRIANGLES, 0, vertices);
        
        FrameBufferProgram.UseProgram();
        setFloat(FrameBufferProgram, "time", currentFrame);
        FramebufferRenderVertexArray.BindVertexArray();
        glDrawArrays(GL_TRIANGLES, 0,6);

        // CosinFrameBufferProgram.UseProgram();
        // FramebufferRenderVertexArray.BindVertexArray();
        // glDrawArrays(GL_TRIANGLES, 0,6);

        ImGui_ImplGlfwGL3_NewFrame();
        {
                
                float e[4][4];
                ImGui::Begin("Salad");

                for(int i = 0; i < NumberOfWaves; i++)
                {
                    std::string Title = "Length, Amplitude, Speed, dx " + i;
                    ImGui::InputFloat4t(Title.c_str(), &wavedata[i].l, &wavedata[i].a, &wavedata[i].s, &wavedata[i].dx);
                    std::string SecondTitle = "dy, z0, z1, z2" + i;
                    ImGui::InputFloat4t(SecondTitle.c_str(), &wavedata[i].dy, &wavedata[i].z0, &wavedata[i].z1, &wavedata[i].z2);
                }
                
                bool Clicked = ImGui::Button("Change");

                if(Clicked)
                {
                   
                    waveInformation.BindBuffer(GL_UNIFORM_BUFFER);
                    waveInformation.BufferSubData(0, sizeof(wav4)*NumberOfWaves, wavedata);
                    
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