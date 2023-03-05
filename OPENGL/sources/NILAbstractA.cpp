#include "NILAbstractA.h"



void APIENTRY glDebugxOutput(GLenum source, GLenum type, unsigned int id, GLenum severity,
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

#define WS "X:\\1.4 C++\\Visual Studio Projects\\OpenGL\\OpenGL32\\OpenGL\\"

int EnableDebugCallback() 
{
    int flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
    {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

        glDebugMessageCallback(glDebugxOutput, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
        return 1;
    }
    return 0;
}
int DisableDebugCallback()
{
    int flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
    {
        glDebugMessageCallback(NULL, NULL);
        return 1;
    }
    return 0;
}


struct NCILBase : NCLPlatform, NCLDevice, NCLContext
{
    NCLPlatform Platform;
    NCLDevice Device;
    NCLContext Context;
    bool* Toggles[5];

    int MakeContext(int PlatformIndex, cl_device_type DeviceType, int DeviceIndex, bool GLInterop)
    {
        if (PlatformIndex < 0) { return 0; }
        if (DeviceIndex < 0) { return 0; }
        if (!ValidDeviceType(DeviceType)) { return 0; }
        int Error;
        Error = Platform.GetPlatforms();
        if (Error == 0) { Platform.FreePlatforms(); return 0; }
        Error = Platform.SelectDefaultPlatform(PlatformIndex);
        if (Error == 0) { Platform.FreePlatforms(); return 0; }
        Error = Platform.FreePlatforms();
        if (Error == 0) { return 0; }
        Error = Device.GetDevices(Platform.ReturnPlatform(), DeviceType);
        if (Error == 0) { Device.FreeDevices(); return 0; }
        Error = Device.SelectDefaultDevice(DeviceIndex);
        if (Error == 0) { Device.FreeDevices(); return 0; }
        Error = Device.FreeDevices();
        if (Error == 0) { return 0; }
        cl_device_id device_id = Device.ReturnDevice();
        if (GLInterop)
        {
            if (!IsCLExtensionSupported("cl_khr_gl_sharing", device_id)) { return 0; }

#ifdef _WIN32
            const cl_context_properties properties[] = {
            CL_GL_CONTEXT_KHR, (cl_context_properties)wglGetCurrentContext(),
            CL_WGL_HDC_KHR, (cl_context_properties)wglGetCurrentDC(),
            CL_CONTEXT_PLATFORM, (cl_context_properties)Platform.ReturnPlatform(),
            0 };
#endif
#ifdef __linux__
            cl_context_properties properties[] = {
            CL_GL_CONTEXT_KHR, (cl_context_properties)glXGetCurrentContext(),
            CL_WGL_HDC_KHR, (cl_context_properties)glXGetCurrentDisplay(),
            CL_CONTEXT_PLATFORM, (cl_context_properties)Platform.ReturnPlatform(),
            0
            };
#endif
#ifdef __APPLE__
            cl_context_properties props[] =
            {
            CL_CONTEXT_PROPERTY_USE_CGL_SHAREGROUP_APPLE,
            (cl_context_properties)kCGLShareGroup,
            0
            };
#endif

            Error = Context.CreateContext(properties, 1, &device_id, NULL, NULL);
            if (Error == 0) { return 0; }
            return 1;
        }


        Error = Context.CreateContext(NULL, 1, &device_id, NULL, NULL);
        if (Error == 0) { return 0; }
        return 1;



    }
    int MakeContextDemo(int PlatformIndex, cl_device_type DeviceType, int DeviceIndex, bool GLInterop)
    {
        if (PlatformIndex < 0 || DeviceIndex < 0 || !ValidDeviceType(DeviceType)) { return 0; }
        int Error;
        
        Error = GetPlatforms();
        if (PlatformIndex > num_platforms - 1) { return 0; }
        if (Error == 0) { FreePlatforms(); return 0; }
        Error = SelectDefaultPlatform(PlatformIndex);
        if (Error == 0) { FreePlatforms(); return 0; }
        Error = FreePlatforms();
        if (Error == 0) { return 0; }
        Error = GetDevices(ReferencePlatform(), DeviceType);
        if (Error == 0) { FreeDevices(); return 0; }
        Error = SelectDefaultDevice(DeviceIndex);
        if (Error == 0) { FreeDevices(); return 0; }
        Error = FreeDevices();
        if (Error == 0) { return 0; }
        cl_device_id device_id = ReturnDevice();
        if (GLInterop)
        {
            if (!IsCLExtensionSupported("cl_khr_gl_sharing", device_id)) { return 0; }

#ifdef _WIN32
            const cl_context_properties properties[] = {
            CL_GL_CONTEXT_KHR, (cl_context_properties)wglGetCurrentContext(),
            CL_WGL_HDC_KHR, (cl_context_properties)wglGetCurrentDC(),
            CL_CONTEXT_PLATFORM, (cl_context_properties)ReturnPlatform(),
            0 };
#endif
#ifdef __linux__
            cl_context_properties properties[] = {
            CL_GL_CONTEXT_KHR, (cl_context_properties)glXGetCurrentContext(),
            CL_WGL_HDC_KHR, (cl_context_properties)glXGetCurrentDisplay(),
            CL_CONTEXT_PLATFORM, (cl_context_properties)Platform.ReturnPlatform(),
            0
            };
#endif
#ifdef __APPLE__
            cl_context_properties props[] =
            {
            CL_CONTEXT_PROPERTY_USE_CGL_SHAREGROUP_APPLE,
            (cl_context_properties)kCGLShareGroup,
            0
            };
#endif

            Error = CreateContext(properties, 1, &device_id, NULL, NULL);
            if (Error == 0) { return 2; }
            return 1;
        }


        Error = CreateContext(NULL, 1, &device_id, NULL, NULL);
        if (Error == 0) { return 0; }
        return 1;
    }
    bool ValidDeviceType(cl_device_type dtype)
    {
        return ((dtype == CL_DEVICE_TYPE_CPU) || (dtype == CL_DEVICE_TYPE_GPU) || (dtype == CL_DEVICE_TYPE_ACCELERATOR) || (dtype == CL_DEVICE_TYPE_CUSTOM) || (dtype == CL_DEVICE_TYPE_DEFAULT) || (dtype == CL_DEVICE_TYPE_ALL));
    }
    int BruteForceInterop(cl_device_type DeviceType)
    {
        
        int Error = 0;
        int ErrorA = 0;
        Error =  GetPlatforms();
        if (!Error) { return 0; }
        for (int i = 0; i < num_platforms; i++)
        {
            #ifdef _WIN32
                        const cl_context_properties properties[] = {
                        CL_GL_CONTEXT_KHR, (cl_context_properties)wglGetCurrentContext(),
                        CL_WGL_HDC_KHR, (cl_context_properties)wglGetCurrentDC(),
                        CL_CONTEXT_PLATFORM, (cl_context_properties)ArrayReturnPlatform(i),
                        0 };
            #endif
            #ifdef __linux__
                        cl_context_properties properties[] = {
                        CL_GL_CONTEXT_KHR, (cl_context_properties)glXGetCurrentContext(),
                        CL_WGL_HDC_KHR, (cl_context_properties)glXGetCurrentDisplay(),
                        CL_CONTEXT_PLATFORM, (cl_context_properties)Platform.ReturnPlatform(),
                        0
                        };
            #endif
            #ifdef __APPLE__
                        cl_context_properties props[] =
                        {
                        CL_CONTEXT_PROPERTY_USE_CGL_SHAREGROUP_APPLE,
                        (cl_context_properties)kCGLShareGroup,
                        0
                        };
            #endif
            Error = FreeDevices();
            ErrorA = GetDevices(platforms[i], DeviceType);
            if (Error && ErrorA)
            {
                for (int j = 0; j < num_devices; j++)
                {
                    Error = CreateContext(properties, 1, &devices[i], NULL, NULL);
                    if (Error) 
                    {
                        Error = SelectDefaultDevice(j);
                        if (!Error) { FreePlatforms(); FreeDevices(); return 3; }
                        Error = FreeDevices(); 
                        if (!Error) { FreePlatforms(); return 3; }
                        Error = SelectDefaultPlatform(i); 
                        if (!Error ) { FreePlatforms(); return 2; }
                        Error = FreePlatforms(); 
                        if (!Error) { return 2; }
                        return 1; 
                    }
                }

            }
        }




    }
    int BruteForceContext(cl_device_type DeviceType)
    {
        int Error1 = 0;
        int Error2 = 0;
        Error1 = GetPlatforms();
    }
};

struct NILBuffer : NGLBuffer
{
    GLenum m_type;
    bool HasData;
    GLsizeiptr m_size;
    NILBuffer(GLenum type) { GenerateBuffer(); m_type = type; HasData = false; m_size = 0; }
    NILBuffer(GLenum type, GLsizeiptr size, const GLvoid* data, GLenum usage)
    {
        GenerateBuffer();
        m_type = type;
        HasData = false;
        m_size = 0;
        HasData = Data(size, data, usage);
    }
    int Data(GLsizeiptr size, const GLvoid* data, GLenum usage) 
    {
        if (HasData && size < m_size) 
        {
            if (!SubData(size, data)) {  return 0; }
            m_size = size;
            HasData = true;
            return 1;
        }
        else
        {
            if (!BindBuffer(m_type)) { return 0; }
            if (!BufferData(size, data, usage)) { return 0; }
            m_size = size;
            HasData = true;
            return 1;
        }
        return 0; 
    }
    int SubData(GLsizeiptr size, const GLvoid* data)
    {
        return BufferSubData(0, size, data);
    }

};
float Ranf(float min, float max)
{
 
    return (float)rand() / RAND_MAX * (max - min) + min;
  
}

struct NCILProgram : NCLProgramToggle
{
    NCILProgram() { }
    int MakeProgram(NCILBase& Base, const char* src) 
    {
        

        cl_context Context = Base.ReturnContext();
        cl_device_id Device = Base.ReturnDevice();
        int Error = 0;
        char* ProgramSource = CLParser(src);
        if (ProgramSource == nullptr) { return 0; }
        Error = CreateProgramWithSource(Context, 1, (const char**)&ProgramSource, NULL);
        if (Error == 0) { free(ProgramSource); return 0; }
        Error = BuildProgram(1, &Device, NULL, NULL, NULL);
        if (Error == 0) { ReleaseProgram(); free(ProgramSource); return 0; }
        free(ProgramSource);
        int st = 0;
        GetProgramBuildInfo(Device, CL_PROGRAM_BUILD_STATUS, sizeof(int), &st, NULL);

        if (st != CL_BUILD_SUCCESS)
        {
            ProgramSource = CLParser(WS "default.cl");
            if (ProgramSource == nullptr) { return 0; }
            Error = CreateProgramWithSource(Context, 1, (const char**)&ProgramSource, NULL);
            if (Error == 0) { free(ProgramSource); return 0; }
            Error = BuildProgram(1, &Device, NULL, NULL, NULL);
            if (Error == 0) { ReleaseProgram(); free(ProgramSource); return 0; }
            free(ProgramSource);
        }

        return 1; 
    }
};



int samples = 8;
void func(GLFWwindow* window, int width, int height)
{
    glViewport(0,0, width, height);
}

void NILAbstractAMain()
{

    NILMesh Mesh;
    NILTriMesh TriMesh;
    int MeshStatus = NILGetMesh(WS "Mesh.obj", Mesh);
    NILMesh ComposedMesh = NILComposeMesh(Mesh);

    srand(time(NULL));

    //Entire GLEW and Window Setup : Default Spec, with breakout components.
    if (!glfwInit())
    {
        // broken
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    //glfwWindowHint(GLFW_SAMPLES, samples);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    //glEnable(GL_MULTISAMPLE);

    NFWMonitors MonitorSelection;
    int MonitorCount;
    MonitorSelection.GetMonitors(&MonitorCount);
    NFWMonitor SelectedMonitor; SelectedMonitor.BecomeMonitor(MonitorSelection.GetMonitor(1));
    NFWMonitor PrimaryMonitor; PrimaryMonitor.BecomePrimaryMonitor();
    NFWWindow MainWindow;
    MainWindow.MakeWindow(400, 400, "main window", NULL, NULL);
    
    MainWindow.SetWindowSizeCallback(func);
    glfwMakeContextCurrent(MainWindow.GetWindow());
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;

    //std::cout << "Debug Status: " << EnableDebugCallback() << std::endl;

    NCILBase CLBase;
    NCILProgram prog; //make toggle connector to CLBase. CLProgram
    CLBase.MakeContextDemo(0, CL_DEVICE_TYPE_GPU, 0, true);
    prog.MakeProgram(CLBase, WS "test.cl");
    cl_device_id Id = CLBase.ReturnDevice();
    size_t MaximumWorkGroupSize = 0;
    int InfoStatus = clGetDeviceInfo(Id, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(size_t), &MaximumWorkGroupSize, NULL);
    int Error = 0;
    NCLCommandQueue qu;
    Error = qu.CreateCommandQueue(CLBase.ReturnContext(), CLBase.ReturnDevice(), NULL);

    char* clFile;
    //compose vertex buffers and element buffers into vertex array.
    NGLVertexArray VertexArray;
    int glStat = VertexArray.GenerateVertexArray();
    glStat = VertexArray.BindVertexArray();
    
    int Num_Particles = ComposedMesh.Vertexes.size();

    NILBuffer vertex(GL_ARRAY_BUFFER);
    NILBuffer color(GL_ARRAY_BUFFER, 2 * sizeof(float) * ComposedMesh.TextureCoordinates.size(), ComposedMesh.TextureCoordinates.data(), GL_STATIC_DRAW);


    int Stat = vertex.Data(4 * sizeof(float) * Num_Particles, ComposedMesh.Vertexes.data(), GL_STATIC_DRAW);
    Stat = vertex.BindBuffer(GL_ARRAY_BUFFER);
    VertexArray.VertexAttribPointer(0, 4, GL_FLOAT, GL_TRUE, sizeof(float) * 4, (void*)0);
    VertexArray.EnableVertexAttribArray(0);
    /*float* Data = (float*)vertex.MapBuffer(GL_WRITE_ONLY);
    
    for (int i = 0; i < Num_Particles*4; i+=4)
    {
        Data[i] = Ranf(-0.5f, 0.5f);
        Data[i + 1] = Ranf(-0.5f, 0.5f);
        Data[i + 2] = Ranf(-0.5f, 0.5f);
        Data[i + 3] = Ranf(-0.5f, 0.5f);
    }*/
    Stat = vertex.UnmapBuffer();
    vertex.Unbind(GL_ARRAY_BUFFER);
    Stat = color.BindBuffer(GL_ARRAY_BUFFER);
    VertexArray.VertexAttribPointer(1, 2, GL_FLOAT, GL_TRUE, sizeof(float) * 2, (void*)0);
    VertexArray.EnableVertexAttribArray(1);

    NILBuffer NormalBuffer(GL_ARRAY_BUFFER, 4 * sizeof(float) * ComposedMesh.Normals.size(), ComposedMesh.Normals.data(), GL_STATIC_DRAW);
    NormalBuffer.BindBuffer(GL_ARRAY_BUFFER);
    VertexArray.VertexAttribPointer(2, 4, GL_FLOAT, GL_TRUE, sizeof(float) * 4, (void*)0);
    VertexArray.EnableVertexAttribArray(2);

    cl_mem dPobj = clCreateFromGLBuffer(CLBase.ReturnContext(), CL_MEM_READ_WRITE, vertex.ReturnBuffer(), &Stat);
    cl_mem cPobj = clCreateFromGLBuffer(CLBase.ReturnContext(), CL_MEM_READ_WRITE, NormalBuffer.ReturnBuffer(), &Stat);

    NCLKernel kernel;
    kernel.CreateKernel(prog.ReturnProgram(), "add");
    kernel.SetKernelArg(0, sizeof(cl_mem), &dPobj);
    kernel.SetKernelArg(1, sizeof(cl_mem), &cPobj);
    kernel.SetKernelArg(2, sizeof(int), (void*)&Num_Particles);
    const size_t globalworkGroupSize = Num_Particles;
    const size_t localworkGroupSize = MaximumWorkGroupSize;
   
    NILProgram Program;
    //const GLchar* feedbackVaryings[] = { "dbg" };
    //int VaryingStatus = Program.SetTransformFeedbackMode(feedbackVaryings, 1, GL_INTERLEAVED_ATTRIBS);
    int VertexStatus = Program.LinkShader(WS "NILVertex.glsl", GL_VERTEX_SHADER);
    int FragmentStatus = Program.LinkShader(WS "NILFragment.glsl", GL_FRAGMENT_SHADER);

    //int GeometryStatus = Program.LinkShader(WS "geometry.glsl", GL_GEOMETRY_SHADER);
    //int TesselationControlStatus = Program.LinkShader(WS "tesscontrol.glsl", GL_TESS_CONTROL_SHADER);
    //int TesselationEvalStatus = Program.LinkShader(WS "tesseval.glsl", GL_TESS_EVALUATION_SHADER);
    int LinkStatus = Program.Link();
    int UseStatus = Program.UseProgram();
    if (LinkStatus == 0 || UseStatus == 0 || VertexStatus == 0 || FragmentStatus == 0) { exit(0); }
    glPointSize(5.0);

    int ResolutionLocation, MouseLocaiton, TimeLocation, CameraLocation;
    Program.GetUniformLocation("resolution", &ResolutionLocation);
    Program.GetUniformLocation("mouse", &MouseLocaiton);
    Program.GetUniformLocation("time", &TimeLocation);
    int ResX = 1, ResY = 1;

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glDepthMask(GL_TRUE);
    float cx = 0, cy = 0, cz = 0;
    while (!glfwWindowShouldClose(MainWindow.GetWindow()))
    {
        glClearColor(0.5f, 1.25f, 1.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        Program.GetUniformLocation("camera", &CameraLocation);
        Program.ProgramUniform3f(CameraLocation, cx, cy, cz);
        Program.GetUniformLocation("resolution", &ResolutionLocation);
        int W = 1, H = 1;
        glfwGetWindowSize(MainWindow.GetWindow(), &W, &H);
        ResX = W; ResY = H;
        Program.ProgramUniform2f(ResolutionLocation, W, H);

        Program.GetUniformLocation("mouse", &MouseLocaiton);
        double MX = 1, MY = 1;
        glfwGetCursorPos(MainWindow.GetWindow(), &MX, &MY);
        char string[55];
        sprintf(string, "mx: %f my: %f", MX / ResX, MY / ResY);
        glfwSetWindowTitle(MainWindow.GetWindow(), string);
        Program.ProgramUniform2f(MouseLocaiton, MX / ResX, MY / ResY);
        Program.GetUniformLocation("time", &TimeLocation);
        Program.ProgramUniform1f(TimeLocation, glfwGetTime());
        float cTime = glfwGetTime();
        kernel.SetKernelArg(3, sizeof(float), (void*)&cTime);
        int st = 0;
        if (glfwGetKey(MainWindow.GetWindow(), GLFW_KEY_SPACE))
        {
            //sub  buffer data and mapping works fine withought releasing, but this requires releasing and reneweal of the interop buffer
            VertexArray.BindVertexArray();
            vertex.BufferData(sizeof(float) * 4 * Num_Particles, ComposedMesh.Vertexes.data(), GL_STATIC_DRAW);
            clReleaseMemObject(dPobj);
            dPobj = clCreateFromGLBuffer(CLBase.ReturnContext(), CL_MEM_READ_WRITE, vertex.ReturnBuffer(), &Stat);

            Program.RecompileProgram();
            Program.UseProgram();

            clFile = CLParser(WS "\\test.cl");
            prog.CreateProgramWithSource(CLBase.ReturnContext(), 1, (const char**)&clFile, NULL);
            prog.BuildProgram(1, &Id, NULL, NULL, NULL);
            
            prog.GetProgramBuildInfo(Id, CL_PROGRAM_BUILD_STATUS, sizeof(int), &st, NULL);
            if (st == CL_BUILD_SUCCESS)
            {
                kernel.CreateKernel(prog.ReturnProgram(), "add");
                kernel.SetKernelArg(0, sizeof(cl_mem), &dPobj);
                kernel.SetKernelArg(1, sizeof(cl_mem), &cPobj);
                kernel.SetKernelArg(2, sizeof(int), (void*)&Num_Particles);
                kernel.SetKernelArg(3, sizeof(float), (void*)&cTime);
                //vertex.Data(sizeof(float) * 4 * Num_Particles, ComposedMesh.Vertexes.data(), GL_STATIC_DRAW);
                
                
                

                //vertex.SubData(vertex.m_size, ComposedMesh.Vertexes.data());
                /*float* map = (float*)vertex.MapBuffer(GL_WRITE_ONLY);
                for(int i = 0; i < Num_Particles; i++)
                {
                    map[i] = Ranf(-1.0, 1.0);
                }
                vertex.UnmapBuffer();*/
                //NormalBuffer.Data(sizeof(float) * 4 * Num_Particles, ComposedMesh.Normals.data(), GL_STATIC_DRAW);
            }
        }
        if (glfwGetKey(MainWindow.GetWindow(), GLFW_KEY_W)) { cz += 0.1; }
        if (glfwGetKey(MainWindow.GetWindow(), GLFW_KEY_S)) { cz -= 0.1; }
        if (glfwGetKey(MainWindow.GetWindow(), GLFW_KEY_D)) { cx += 0.1; }
        if (glfwGetKey(MainWindow.GetWindow(), GLFW_KEY_A)) { cx -= 0.1; }

        if (st == CL_BUILD_SUCCESS)
        {
            Stat = clEnqueueAcquireGLObjects(qu.ReturnCommandQueue(), 1, &dPobj, 0, NULL, NULL);
            Stat = clEnqueueAcquireGLObjects(qu.ReturnCommandQueue(), 1, &cPobj, 0, NULL, NULL);
            kernel.EnqueueNDRangeKernel(qu.ReturnCommandQueue(), 1, NULL, &globalworkGroupSize, &localworkGroupSize, NULL, NULL, NULL);
        }
        glFinish();
        //do not enqueu kernel if command queue did not work, or creating the kernel did not work.
        
        
        
        Stat = clEnqueueReleaseGLObjects(qu.ReturnCommandQueue(), 1, &dPobj, 0, NULL, NULL);
        Stat = clEnqueueReleaseGLObjects(qu.ReturnCommandQueue(), 1, &cPobj, 0, NULL, NULL);
        qu.Finish();

        VertexArray.BindVertexArray();
        
        //if geometry shader enabled guarentee that the primitive type matches
        //if tesselation shader enabled must be in patch format.
        //glDrawArrays(GL_TRIANGLES, 0, Num_Particles);
        glDrawArrays(GL_TRIANGLES, 0, Num_Particles);
        //glDrawElements(GL_TRIANGLES, Mesh.Faces.size(), GL_UNSIGNED_INT, (void*)0);
        glfwSwapBuffers(MainWindow.GetWindow());
        glfwPollEvents();
    }

    glfwTerminate();
    
    exit(1);
}