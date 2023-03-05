#include "NFWDriver.h"


void APIENTRY glDebugyOutput(GLenum source, GLenum type, unsigned int id, GLenum severity,
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



int NFWMain()
{
	if (!glfwInit())
	{
		// broken
	}
    
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	NFWMonitors MonitorSelection;
	int MonitorCount;
	MonitorSelection.GetMonitors(&MonitorCount);
	NFWMonitor SelectedMonitor; SelectedMonitor.BecomeMonitor(MonitorSelection.GetMonitor(1));
	NFWMonitor PrimaryMonitor; PrimaryMonitor.BecomePrimaryMonitor();
	NFWWindow MainWindow; MainWindow.MakeWindow(400, 400, "main window", NULL, NULL);
    //MainWindow.SetWindowMonitor(NULL, 0, 0, 400, 400, GLFW_DONT_CARE);

    glfwMakeContextCurrent(MainWindow.GetWindow());

    glfwSwapInterval(1);


    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;
    
    int flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
    {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

        glDebugMessageCallback(glDebugyOutput, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }

    NMLRProgram Program;
    const GLchar* feedbackVaryings[] = { "vDebugOutput" };
    int VaryingStatus = Program.SetTransformFeedbackMode(feedbackVaryings, 1, GL_INTERLEAVED_ATTRIBS);
    Program.Start();
    Program.UseProgram();
    GLint loc;
    Program.GetUniformLocation("h_tex1", &loc);

    

#pragma region StaticShader
    int error = 0;
    NGLProgram nglProgram;
    error = nglProgram.CreateProgram();
    NGLShader nglVertexShader; error = nglVertexShader.CreateShader(GL_VERTEX_SHADER);
    NGLShader nglFragmentShader; error = nglFragmentShader.CreateShader(GL_FRAGMENT_SHADER);
    char* vertexSource = NGLParseShader(WS "vertex.glsl");
    char* fragmentSource = NGLParseShader(WS "fragment.glsl");
    error = nglVertexShader.ShaderSource(1, (const char**)&vertexSource, NULL);
    error = nglFragmentShader.ShaderSource(1, (const char**)&fragmentSource, NULL);
    error = nglVertexShader.CompileShader();
    error = nglFragmentShader.CompileShader();
    GLsizei LogLength = 0;
    error = nglVertexShader.GetInfoLog(NULL, &LogLength, NULL);
    GLint isCompiled = 0;
    error = nglVertexShader.GetShaderiv(GL_COMPILE_STATUS, &isCompiled);

    if (!isCompiled)
    {
        char* VertexLog = (char*)malloc(LogLength);
        error = nglVertexShader.GetInfoLog(LogLength, NULL, VertexLog);
        printf("%s\n", VertexLog);
        free(VertexLog);
    }
    error = nglFragmentShader.GetShaderiv(GL_COMPILE_STATUS, &isCompiled);
    if (!isCompiled)
    {
        error = nglFragmentShader.GetInfoLog(NULL, &LogLength, NULL);
        char* FragmentLog = (char*)malloc(LogLength);
        error = nglFragmentShader.GetInfoLog(LogLength, NULL, FragmentLog);
        printf("%s\n", FragmentLog);
        free(FragmentLog);
    }
    error = nglProgram.AttachShader(nglVertexShader.ReturnShader());
    error = nglProgram.AttachShader(nglFragmentShader.ReturnShader());
    error = nglProgram.LinkProgram();
    error = nglProgram.UseProgram();
    GLint  linkStatus = 0;
    error = nglProgram.GetProgramiv(GL_LINK_STATUS, &linkStatus);


    //research bindless textures for efficiency
#pragma endregion
    
    float TexplaneData[16]
    {
        -1.0f, -1.0f, 0.0f, 0.0f,
         1.0f, -1.0f, 1.0f, 0.0f,
         1.0f, 1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 0.0f, 1.0f
    };

    NGLVertexArray vertexarray;
    vertexarray.GenerateVertexArray();

    NGLBuffer vertex, index, tbuf;
    vertex.GenerateBuffer();
    index.GenerateBuffer();
    vertexarray.BindVertexArray();
    vertex.BindBuffer(GL_ARRAY_BUFFER);
    vertex.BufferData(sizeof(TexplaneData), TexplaneData, GL_STATIC_DRAW);
    unsigned int at[] = { 0,1,2,3,2,0 }; //2,0

    index.BindBuffer(GL_ELEMENT_ARRAY_BUFFER);
    index.BufferData(sizeof(at), at, GL_STATIC_DRAW);
    vertexarray.VertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    vertexarray.EnableVertexAttribArray(0);
    vertexarray.UnbindVertexArray();

    index.Unbind(GL_ELEMENT_ARRAY_BUFFER);

    float TexplaneDat[16]
    {
         1.0f, -1.0f, 0.3f, 0.0f,
         1.0f, 0.2f, 1.0f, 0.0f,
         1.0f, 1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 0.0f, 1.0f
    };





    tbuf.GenerateBuffer();
    tbuf.BindBuffer(GL_TEXTURE_BUFFER);
    tbuf.BufferDataType(GL_TEXTURE_BUFFER, sizeof(TexplaneDat), TexplaneDat, GL_STATIC_DRAW);
    NGLTexture texBuffer;
    texBuffer.GenerateTexture();
    glActiveTexture(GL_TEXTURE0);
    texBuffer.BindTexture(GL_TEXTURE_BUFFER);
    texBuffer.TexBuffer(GL_RGBA32F, vertex.ReturnBuffer());

    NMLBufferTexture texBuffer2;
    texBuffer2.AttachBuffer(1, GL_RGBA32F, tbuf.ReturnBuffer());
    texBuffer2.BindTextureUnit(2);

    NMLUniformBufferBlock ubo;
    ubo.CreateUniformBufferBlock(0, sizeof(TexplaneData), TexplaneDat, GL_STATIC_DRAW);
    GLuint blockIndex; 

    Program.GetUniformBlockIndex("MyBlock", &blockIndex);
    Program.UniformBlockBinding(blockIndex, 0);

    GLint texBuffer2Index;
    Program.GetUniformLocation("h_tex1", &texBuffer2Index);

    
    //if buffer size is too small : onces per vertex : then undefined.

    GLuint tbo;
    glGenBuffers(1, &tbo);
    glBindBuffer(GL_ARRAY_BUFFER, tbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 24, nullptr, GL_STATIC_READ);
    
    NMLTransformFeedback ntbo;
    ntbo.CreateTransformFeedback();
    ntbo.BindTransformFeedback();
    ntbo.TransformFeedbackData(sizeof(float) * 24, nullptr, GL_STATIC_READ);
    

    void* datav = (void*)malloc(sizeof(float) * 24);
    float* datavf;
    
    clock_t tClick = 0;
    clock_t dTime;
    clock_t tSin;
    
    NGLStateManagement state;
    state.ClipControl(GL_UPPER_LEFT, GL_NEGATIVE_ONE_TO_ONE);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glEnable(GL_PRIMITIVE_RESTART); 
    //glPrimitiveRestartIndex(0);


    int frameBufferStatus = 0;
    NGLTexture FramebufferTexture;
    frameBufferStatus = FramebufferTexture.GenerateTexture();
    frameBufferStatus = FramebufferTexture.BindTexture(GL_TEXTURE_2D);
    frameBufferStatus = FramebufferTexture.TexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 400, 400, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    frameBufferStatus = FramebufferTexture.TextureParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    frameBufferStatus = FramebufferTexture.TextureParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    NGLTexture FramebufferDepthStencil;
    FramebufferDepthStencil.GenerateTexture();
    FramebufferDepthStencil.BindTexture(GL_TEXTURE_2D);
    FramebufferDepthStencil.TexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, 400, 400, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);

    NGLFramebuffer fr;
    frameBufferStatus = fr.GenerateFramebuffer();
    frameBufferStatus = fr.BindFramebuffer(GL_FRAMEBUFFER);

    frameBufferStatus = fr.NamedFramebufferTexture(GL_COLOR_ATTACHMENT0, FramebufferTexture.ReturnTexture(), 0);
    frameBufferStatus = fr.NamedFramebufferTexture(GL_DEPTH_STENCIL_ATTACHMENT, FramebufferDepthStencil.ReturnTexture(), 0);


    /*NGLRenderbuffer rb;
    rb.GenerateRenderbuffer();
    rb.BindRenderbuffer();
    rb.RenderbufferStorage(GL_DEPTH24_STENCIL8, 400, 400);
    rb.Unbind();

    fr.FramebufferRenderbuffer(GL_DEPTH24_STENCIL8, rb.ReturnRenderBuffer());*/
    frameBufferStatus = fr.CheckFramebufferStatus(GL_FRAMEBUFFER);
    frameBufferStatus = fr.UnbindFramebuffer(GL_FRAMEBUFFER);


    GLint timeloc;
    Program.GetUniformLocation("time", &timeloc);
    double time = 0.0;
	while (!glfwWindowShouldClose(MainWindow.GetWindow()))
	{
        time = glfwGetTime();
        dTime = clock();
        tSin = dTime - tClick;
        glClearColor(0.5f, 1.25f, 1.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        Program.RecompileProgram();
        //Program.UseProgram();
        //Program.UniformBlockBinding(blockIndex, 0);
        //Program.ProgramUniform1i(loc, 2);
        
        Program.GetUniformLocation("time", &timeloc);
        if (timeloc >= 0)
        {
            Program.ProgramUniform1f(timeloc, timeloc);
        }
        
        if (glfwGetKey(MainWindow.GetWindow(), GLFW_KEY_SPACE))
        {
            vertexarray.BindVertexArray();
            NGLBuffer postBuffer; postBuffer.GenerateBuffer(); postBuffer.BindBuffer(GL_ARRAY_BUFFER);
            postBuffer.BufferData(sizeof(TexplaneDat), TexplaneDat, GL_STATIC_DRAW);
            vertexarray.VertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
            vertexarray.EnableVertexAttribArray(1);
            vertexarray.UnbindVertexArray();
        }
        if (glfwGetKey(MainWindow.GetWindow(), GLFW_KEY_I))
        {
            fr.BindFramebuffer(GL_READ_FRAMEBUFFER);
            glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
            glBlitFramebuffer(0, 0, 400, 400, 0, 0, 400, 400, GL_COLOR_BUFFER_BIT, GL_NEAREST);
            fr.UnbindFramebuffer(GL_READ_FRAMEBUFFER);
        }
            
        vertexarray.BindVertexArray();

        //glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, tbo);
        glBindBufferRange(GL_TRANSFORM_FEEDBACK_BUFFER, 0, tbo, 0, sizeof(float) * 24); //the number has to be the same as the buffer, and everything else.
        ntbo.BindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0);

        glBeginTransformFeedback(GL_TRIANGLES);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

        const GLsizei counts[] = { 6, 6 };
        fr.BindFramebuffer(GL_FRAMEBUFFER);
        glMultiDrawElements(GL_TRIANGLES, counts, GL_UNSIGNED_INT, (const GLvoid**) & at[0], 1);
        fr.UnbindFramebuffer(GL_FRAMEBUFFER);
        glEndTransformFeedback();
        glFlush();
        

        if (glfwGetKey(MainWindow.GetWindow(), GLFW_KEY_T) && tSin > 200)
        {
            tClick = clock();

            //glGetBufferSubData(GL_TRANSFORM_FEEDBACK_BUFFER, 0, sizeof(float) * 4, datav);
            ntbo.GetBufferSubData(0, sizeof(float) * 4, datav);
            datavf = (float*)datav;
            printf("(%f,%f,%f,%f)\n", datavf[0], datavf[1], datavf[2], datavf[3]);
        }

        glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, 0);
        glfwSwapBuffers(MainWindow.GetWindow());
        glfwPollEvents();

        

	}

    exit(1);
    return 1;
}