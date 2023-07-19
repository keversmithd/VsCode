#include <iostream>
#include <LearnOpenglHelper.h>
#include "CL/cl.h"
#include <math.h>
#include <algorithm>

#include <imgui/imgui.h>
#include "imgui/imgui_impl_glfw_gl3.h"

#include "FGeom.h"
#include "Camera.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

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
    GLFWwindow* window = CreateContext();

#pragma region Shaders
    NGLProgram program = CreateShader("shaders/wavewaterWithNormalMap.vs","shaders/wavewaterWithNormalMap.fs");
    NGLProgram FrameBufferProgram  = CreateShader("shaders/WaveToTexture.vs", "shaders/WaveToTexture.fs");

#pragma endregion

#pragma region


#pragma region UnpackInitalScene

    SubPlane UVPlane = EqualSubdividedPlane(1);
    NGLVertexArray FramebufferRenderVertexArray;
    FramebufferRenderVertexArray.GenerateVertexArray();
    FramebufferRenderVertexArray.BindVertexArray();
    NGLBuffer FrameBufferVertexBuffer;
    FrameBufferVertexBuffer.GenerateBuffer();
    FrameBufferVertexBuffer.BindBuffer(GL_ARRAY_BUFFER);
    FrameBufferVertexBuffer.BufferData(UVPlane.byteSize, UVPlane.data, GL_STATIC_DRAW);
    FramebufferRenderVertexArray.EnableVertexAttribArray(0);
    FramebufferRenderVertexArray.VertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (GLvoid*)0);
    FramebufferRenderVertexArray.EnableVertexAttribArray(1);
    FramebufferRenderVertexArray.VertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float)*8, (GLvoid*)(sizeof(float) * 3));
    FramebufferRenderVertexArray.EnableVertexAttribArray(2);
    FramebufferRenderVertexArray.VertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float)*8, (GLvoid*)(sizeof(float) * 5));

#pragma endregion

    #pragma region lookuptable

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
    NGLProgram CosinFrameBufferProgram = CreateShader("shaders/WaveToTextureLookupTable.vs","shaders/WaveToTextureLookupTable.fs");

    glViewport(0,0,256,1);
    CosinFrameBufferProgram.UseProgram();
    FramebufferRenderVertexArray.BindVertexArray();
    glBindFramebuffer(GL_FRAMEBUFFER, CosineFrameBuffer);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    #pragma endregion

    #pragma region normalmap
    NGLTexture WaveNormalMap;
    WaveNormalMap.GenerateTexture();
    WaveNormalMap.BindTexture(GL_TEXTURE_2D);
    WaveNormalMap.TexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256,256, 0, GL_RGB, GL_FLOAT, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  

    unsigned int NormalFrameBuffer;
    glGenFramebuffers(1, &NormalFrameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, NormalFrameBuffer);
    
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, WaveNormalMap.ReferenceTexture(), 0);
    glDrawBuffers(1, DrawBuffers);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        printf("\nWent Wrong\n");
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0,0,1024,768);


#pragma endregion

    

    std::vector<vec2> PlanarUVs;
    std::vector<vec4> PlanarMesh = SubdividedPlane(0.05, 1.0, 1.0, PlanarUVs);

    int vertices = PlanarMesh.size();

    NGLVertexArray vertexarray;
    vertexarray.GenerateVertexArray();

    NGLBuffer vertex, uv;
    vertex.GenerateBuffer();
    uv.GenerateBuffer();

    vertexarray.BindVertexArray();
    vertex.BindBuffer(GL_ARRAY_BUFFER);
    vertex.BufferData(PlanarMesh.size()  * sizeof(vec4), PlanarMesh.data(), GL_STATIC_DRAW);
    vertexarray.VertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    vertexarray.EnableVertexAttribArray(0);
    vertex.Unbind(GL_ARRAY_BUFFER);

    uv.BindBuffer(GL_ARRAY_BUFFER);
    uv.BufferData(PlanarUVs.size()*sizeof(vec2), PlanarUVs.data(), GL_STATIC_DRAW);
    vertexarray.VertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    vertexarray.EnableVertexAttribArray(1);
    uv.Unbind(GL_ARRAY_BUFFER);
    vertexarray.UnbindVertexArray();

    double ai = 0.0; //height from the water plane to the wave crest
    double L = 0.0; //the crest-to-crest distance between waves in world space. Wavelength L relates to frequency w as w = 2pi/L.
    double w =  (2*3.14)/L;
    double S = 0.0; //the distance the crest moves forward per second. It is convenient to express speed as phase-constant. phi swirl
    double phiswirl = S * w;
    double D = 0.0; //the horizontal vector perpendicular to the wave front along which the crest travels
    
    
    
    std::vector<wav4> waveData;
    waveData.push_back({1.0, 0.0, 0.1, 0.0, 1.0, 0.0, 0.0, 0.0});
    waveData.push_back({0.4, 0.4, 0.7, 0.0, 1.0, 0.0, 0.0, 0.0});
    waveData.push_back({0.1, 0.1, 0.1, 0.0, 1.0, 0.0, 0.0, 0.0});

    wav4 wavedata[] =
    {
        {32.0, 0.2, -0.3, 0.3, -0.6, 0.0, 0.0, 0.0},
        {5.0, 0.2, 0.4, 0.4, -0.4, 0.0, 0.0, 0.0},
        {4.0, 0.3, 0.2, 0.2, -1.0, 0.0, 0.0, 0.0},
        {10.0, 0.8, 0.1, -0.3, -1.0, 0.0, 0.0, 0.0},
        {3.0, 0.4, 0.4, -0.4, -1.0, -2.0, 0.0, 0.0},
        {22.0, 0.7, 0.5, 0.2, 1.0, 0.0, 0.0, 0.0},
        {14.0, 0.7, 0.6, 0.1, 1.0, 0.0, 0.0, 0.0},
        {12.0, 0.4, 0.1, 0.3, 1.0, 0.0, 0.0, 0.0},
        {22.0, 0.8, 0.6, 0.4, 1.0, 0.0, 0.0, 0.0},
        {32.0, 0.3, 0.6, 0.5, 1.0, 0.0, 0.0, 0.0},
        {32.0, 0.4, 0.1, -0.7, 1.0, 0.0, 0.0, 0.0},
        {33.0, 0.5, 0.1, 0.3, 1.0, 0.0, 0.0, 0.0},
        {14.0, 0.3, 0.1, 0.3, 1.0, 0.0, 0.0, 0.0}
    };

    int NumberOfWaves = 5;

    unsigned int m_program;
    const char* m = "michael";

    // NGLBuffer waveInformation;
    // waveInformation.GenerateBuffer();
    // waveInformation.BindBuffer(GL_UNIFORM_BUFFER);
    // waveInformation.BufferData(sizeof(wav4)*NumberOfWaves, wavedata, GL_STATIC_DRAW);
    // waveInformation.Unbind(GL_UNIFORM_BUFFER);

    NGLBuffer waveInformation = CreateUniformBuffer(sizeof(wav4)*NumberOfWaves, wavedata, 0);

    setUniformBlock(program, "WaveBuffer", 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_1D, CosineLookupTable.ReturnTexture());
    setInt(FrameBufferProgram, "LookUp", 0);
    setUniformBlock(FrameBufferProgram, "WaveBuffer", 0);
    //waveInformation.BindBufferBase(GL_UNIFORM_BUFFER, 0);



#pragma endregion

    Camera MainCamera;
    MainCamera.MakeActiveCamera(window);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    glm::vec3 lightLocation = glm::vec3(0,0,0);
    glm::vec3 viewPos = MainCamera.cameraPos;

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();

        MainCamera.proccessInput(window);

        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        setVec3(program, "lightPos", lightLocation);
        setVec3(program, "viewPos", MainCamera.cameraPos);
        setFloat(program, "time", currentFrame);
        setInt(program, "numberofwaves", NumberOfWaves);
        setUniformBlock(program, "WaveBuffer", 0);
        setMat4(program, "view", MainCamera.view);
        setMat4(program, "projection", MainCamera.projection);
        setMat4(program, "model", model);


        glActiveTexture(GL_TEXTURE0 + 1);
        setInt(program, "NormalMap", 0);
        program.UseProgram();
        vertexarray.BindVertexArray();
        glDrawArrays(GL_TRIANGLES, 0, vertices);

        

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_1D, CosineLookupTable.ReturnTexture());
        setInt(FrameBufferProgram, "LookUp", 0);
        setUniformBlock(FrameBufferProgram, "WaveBuffer", 0);
        setFloat(FrameBufferProgram, "time", currentFrame);
        FrameBufferProgram.UseProgram();
        FramebufferRenderVertexArray.BindVertexArray();
        glViewport(0,0,256,256);
        glBindFramebuffer(GL_FRAMEBUFFER, NormalFrameBuffer);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0,0,1024,768);






        ImGui_ImplGlfwGL3_NewFrame();
        {
                
                float e[4][4];
                ImGui::Begin("Salad");

                ImGui::SliderFloat3("LightPos", glm::value_ptr(lightLocation), -1.0, 1.0);
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