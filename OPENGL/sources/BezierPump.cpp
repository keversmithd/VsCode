#include "BezierPump.h"



struct Vector
{
    float x;
    float y;
    float z;
};



#define WS "X:\\1.4 C++\\Visual Studio Projects\\OpenGL\\OpenGL32\\OpenGL\\"



int BezierPump(GLDEBUGPROC DebugOutput)
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

        glDebugMessageCallback(DebugOutput, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);

    }

    NMLRProgram Program;
    Program.SubmitVertexShaderSource(WS"Bezier.gl");
    Program.SubmitFragmentShaderSource(WS"Bezier.glf");
    Program.Start();
    double increment = 1.0 / 10.0;
    double t = 0;
    std::vector<Vector> spline;
    Vector P0 = {0,0,0}, P1 = {2,0.5,0}, P2 = {-0.5,-0.5,0}, P3 = {1,1,0};

    for (int i = 0; i < 10; i++)
    {
        Vector samplePoint;
        samplePoint.x = pow((1 - t), 3) * P0.x + 3 * pow((1 - t), 2) * t * P1.x + 3 * (1 - t) * pow(t, 2) * P2.x + pow(t, 3) * P3.x;
        //samplePoint.x = cos(t);
        //samplePoint.y = sin(t);
        samplePoint.z = 1;
        samplePoint.y = pow((1 - t), 3) * P0.y + 3 * pow((1 - t), 2) * t * P1.y + 3 * (1 - t) * pow(t, 2) * P2.y + pow(t, 3) * P3.y;
        //samplePoint.z = pow((1 - t), 3) * P0.z + 3 * pow((1 - t), 2) * P1.z + 3 * (1 - t) * pow(t, 2) * P2.z + pow(t, 3) * P3.z;
        t += increment;
        spline.push_back(samplePoint);
    }


    NGLVertexArray vertexarray;
    vertexarray.GenerateVertexArray();

    NGLBuffer vertex, index, tbuf;
    vertex.GenerateBuffer();
    index.GenerateBuffer();
    vertexarray.BindVertexArray();
    vertex.BindBuffer(GL_ARRAY_BUFFER);
    //vertex.BufferData(sizeof(Vector)*spline.size(), &spline.at(0), GL_STATIC_DRAW);
    vertex.BufferData(spline.size() * sizeof(Vector), spline.data(), GL_STATIC_DRAW);
    //vertex.BufferData(sizeof(triangle), triangle, GL_STATIC_DRAW);
    //unsigned int at[] = { 0,1,2,3 };
    unsigned int* at = (unsigned int*)malloc( sizeof(unsigned int) * spline.size() );
    for (int i = 0; i < spline.size(); i++)
    {
        at[i] = i;
    }

    index.BindBuffer(GL_ELEMENT_ARRAY_BUFFER);
    index.BufferData(sizeof(unsigned int) * spline.size(), &at[0], GL_STATIC_DRAW);
    vertexarray.VertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    vertexarray.EnableVertexAttribArray(0);
    vertexarray.UnbindVertexArray();

    index.Unbind(GL_ELEMENT_ARRAY_BUFFER);



    clock_t tClick = 0;
    clock_t dTime = clock();
    clock_t tSin = clock();
    double pTime = 0.0;
    while (!glfwWindowShouldClose(MainWindow.GetWindow()))
    {
        pTime += 0.01;
        tSin = clock();
        dTime = clock();
       
        
        glClearColor(0.5f, 1.25f, 1.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        //Program.RecompileProgram();
        P0.x = cos(pTime);
        P0.y = sin(pTime);
        t = 0.0;
        for (int i = 0; i < spline.size(); i++)
        {
            spline.at(i).x = pow((1 - t), 3) * P0.x + 3 * pow((1 - t), 2) * t * P1.x + 3 * (1 - t) * pow(t, 2) * P2.x + pow(t, 3) * P3.x;
            spline.at(i).y = pow((1 - t), 3) * P0.y + 3 * pow((1 - t), 2) * t * P1.y + 3 * (1 - t) * pow(t, 2) * P2.y + pow(t, 3) * P3.y;
            spline.at(i).z = cos(t);
            t += increment;
        }
        
     
        if (glfwGetKey(MainWindow.GetWindow(), GLFW_KEY_SPACE))
        {
            


        }

        if (glfwGetKey(MainWindow.GetWindow(), GLFW_KEY_I))
        {
            
        }
        
        

        vertexarray.BindVertexArray();
        
        vertex.BindBuffer(GL_ARRAY_BUFFER);
        vertex.InvalidateBufferData();
        vertex.BufferData(spline.size() * sizeof(Vector), spline.data(), GL_STATIC_DRAW);

        int SplineCount = spline.size();
        int counts[] = { SplineCount };
        //glMultiDrawElements(GL_TRIANGLES, counts, GL_UNSIGNED_INT, (const GLvoid**)&at[0], 1);
        glDrawElements(GL_LINES, spline.size(), GL_UNSIGNED_INT, (void*)0);

        glfwSwapBuffers(MainWindow.GetWindow());
        glfwPollEvents();



    }
    exit(1);
    
    return 1;
}
