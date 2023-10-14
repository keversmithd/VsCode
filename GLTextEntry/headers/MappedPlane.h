#ifndef MAPPED_PLANE
#define MAPPED_PLANE

#include "LearnOpenglHelper.h"
#include "FGeom.h"
#include "Camera.h"
#include "UVSphereFactory.h"


struct ArgumentPackage
{
    SDFVec3 Verticies[5];
    double Paramters[3];
};

struct RelativeObject
{
    void(*callback)(void* self, ArgumentPackage package);
    void* self;
};

struct MappedViewFrustrum
{
private:
    int memoryDataBack;
    unsigned int* elementData;
    int indices;
    int elementDataBack;
    unsigned int vertexBuffer, vertexArray, elementBuffer;
    NGLProgram program;
    void* memoryData;
    int writeRegion;
    int size;
public:
    std::vector<RelativeObject> OnUpdates;

    MappedViewFrustrum() : writeRegion(0), size(0),
    memoryDataBack(0), indices(0), elementDataBack(0), memoryData(nullptr), elementData(nullptr), program(CreateShader("/shaders/GraphicVector.vs", "/shaders/GraphicVector.fs"))
    {
        CreateFrustrum({0.0f, 0, 0}, {0,0,-1}, {0,1,0});
    }

    void CreateFrustrum(SDFVec3 camera_pos, SDFVec3 Forward, SDFVec3 up_vector)
    {
        int VertexSize = 8*8;
        int ElementSize = 24;
        elementData = new unsigned int[ElementSize];
        SetUpMemoryMap(VertexSize);

        float hfov = 90;
        float vfov = 90;
        float near_dist = 0.1;
        float far_dist = 0.5;

        SDFVec3 right = Cross(Forward, up_vector);
        SDFVec3 up = Cross(right,Forward);

        float hhnear = near_dist * tan((hfov*(3.14159265359/180))/2);
        float hhfar = far_dist * tan(((hfov)*(3.14159265359/180))/2);

        SDFVec3 near_center = camera_pos+ normalize(Forward)*near_dist;
        SDFVec3 far_center = camera_pos+ normalize(Forward)*far_dist;
        

        SDFVec3 near_top_left = near_center + up * hhnear - right * hhnear;
        SDFVec3 near_top_right = near_center + up * hhnear + right * hhnear;
        SDFVec3 near_bottom_left = near_center - up * hhnear - right * hhnear;
        SDFVec3 near_bottom_right = near_center - up * hhnear + right * hhnear;

        SDFVec3 far_top_left = far_center + up * hhfar - right * hhfar;
        SDFVec3 far_top_right = far_center + up * hhfar + right * hhfar;
        SDFVec3 far_bottom_left = far_center - up * hhfar - right * hhfar;
        SDFVec3 far_bottom_right = far_center - up * hhfar + right * hhfar;


        fPoint(near_bottom_left, 0,0, (float*)memoryData, memoryDataBack);
        fPoint(near_bottom_right, 1,0, (float*)memoryData, memoryDataBack);
        fPoint(near_top_right, 1,1, (float*)memoryData, memoryDataBack);
        fPoint(near_top_left, 0,1, (float*)memoryData, memoryDataBack);
        
        
        fPoint(far_bottom_left, 0,0, (float*)memoryData, memoryDataBack);
        fPoint(far_bottom_right, 1,0, (float*)memoryData, memoryDataBack);
        fPoint(far_top_right, 1,1, (float*)memoryData, memoryDataBack);
        fPoint(far_top_left, 0,1, (float*)memoryData, memoryDataBack);
        
        elementData[indices++] = 0;
        elementData[indices++] = 1;

        elementData[indices++] = 1;
        elementData[indices++] = 2;

        elementData[indices++] = 2;
        elementData[indices++] = 3;

        elementData[indices++] = 3;
        elementData[indices++] = 0;

        elementData[indices++] = 0;
        elementData[indices++] = 4;

        elementData[indices++] = 1;
        elementData[indices++] = 5;

        elementData[indices++] = 2;
        elementData[indices++] = 6;
        
        elementData[indices++] = 3;
        elementData[indices++] = 7;
        

        elementData[indices++] = 4;
        elementData[indices++] = 5;

        elementData[indices++] = 5;
        elementData[indices++] = 6;

        elementData[indices++] = 6;
        elementData[indices++] = 7;
        
        elementData[indices++] = 7;
        elementData[indices++] = 4;

        SetUpStaticIndexBuffer();


    }

    void UpdateFrustrum(SDFVec3 camera_pos, SDFVec3 Forward, SDFVec3 up_vector, float near_dist, float far_dist, float fov)
    {
        int mback = 0;
        int eback = 0;
        float hfov = fov;
        float vfov = fov;

        SDFVec3 right = Cross(Forward, up_vector);
        right.normalize();
        SDFVec3 up = Cross(right,Forward);
        up.normalize();
    
        float hhnear = near_dist * tan((hfov*(3.14159265359/180))/2);
        float hhfar = far_dist * tan(((hfov)*(3.14159265359/180))/2);

        SDFVec3 near_center = camera_pos+normalize(Forward)*near_dist;
        SDFVec3 far_center = camera_pos+normalize(Forward)*far_dist;
        
        SDFVec3 near_top_left = near_center + up * hhnear - right * hhnear;
        SDFVec3 near_top_right = near_center + up * hhnear + right * hhnear;
        SDFVec3 near_bottom_left = near_center - up * hhnear - right * hhnear;
        SDFVec3 near_bottom_right = near_center - up * hhnear + right * hhnear;

        SDFVec3 far_top_left = far_center + up * hhfar - right * hhfar;
        SDFVec3 far_top_right = far_center + up * hhfar + right * hhfar;
        SDFVec3 far_bottom_left = far_center - up * hhfar - right * hhfar;
        SDFVec3 far_bottom_right = far_center - up * hhfar + right * hhfar;
        

        CallOnUpdates(camera_pos, Forward, up_vector, near_dist, far_dist, fov);


        fPoint(near_bottom_left, 0,0, (float*)memoryData, mback);
        fPoint(near_bottom_right, 1,0, (float*)memoryData, mback);
        fPoint(near_top_right, 1,1, (float*)memoryData, mback);
        fPoint(near_top_left, 0,1, (float*)memoryData, mback);
        
        
        fPoint(far_bottom_left, 0,0, (float*)memoryData, mback);
        fPoint(far_bottom_right, 1,0, (float*)memoryData, mback);
        fPoint(far_top_right, 1,1, (float*)memoryData, mback);
        fPoint(far_top_left, 0,1, (float*)memoryData, mback);
        
        elementData[eback++] = 0;
        elementData[eback++] = 1;

        elementData[eback++] = 1;
        elementData[eback++] = 2;

        elementData[eback++] = 2;
        elementData[eback++] = 3;

        elementData[eback++] = 3;
        elementData[eback++] = 0;

        elementData[eback++] = 0;
        elementData[eback++] = 4;

        elementData[eback++] = 1;
        elementData[eback++] = 5;

        elementData[eback++] = 2;
        elementData[eback++] = 6;
        
        elementData[eback++] = 3;
        elementData[eback++] = 7;
        

        elementData[eback++] = 4;
        elementData[eback++] = 5;

        elementData[eback++] = 5;
        elementData[eback++] = 6;

        elementData[eback++] = 6;
        elementData[eback++] = 7;
        
        elementData[eback++] = 7;
        elementData[eback++] = 4;


    }

    void CallOnUpdates(SDFVec3 camera_pos, SDFVec3 Forward, SDFVec3 up_vector, float near_dist, float far_dist, float fov)
    {
        float hfov = fov;
        float vfov = fov;

        float hhnear = near_dist * tan((hfov*(3.14159265359/180))/2);
        float hhfar = far_dist * tan(((hfov)*(3.14159265359/180))/2);

        SDFVec3 near_center = camera_pos+normalize(Forward)*near_dist;
        SDFVec3 far_center = camera_pos+normalize(Forward)*far_dist;
        
        ArgumentPackage p;
        p.Paramters[0] = hhnear*2;
        p.Paramters[1] = hhfar*2;
        p.Verticies[0] = near_center;
        p.Verticies[1] = far_center;
        
        SDFVec3 right = Cross(Forward, up_vector);
        SDFVec3 up = Cross(right,Forward);

        p.Verticies[2] = right;
        p.Verticies[3] = up;
        p.Verticies[4] = Forward;

        void* s = nullptr;

        for(int i = 0; i < OnUpdates.size(); i++)
        {
            s = OnUpdates[i].self;
            if(OnUpdates[i].callback != nullptr)
            {
                
                OnUpdates[i].callback(s, p);
            }
        }

    }

    void SetUpMemoryMap(int MemoryUsage)
    {
        glGenVertexArrays(1, &vertexArray);
        glGenBuffers(1, &vertexBuffer);
        glBindVertexArray(vertexArray);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferStorage(GL_ARRAY_BUFFER, (MemoryUsage)*sizeof(float), 0, GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT);
        memoryData = glMapBufferRange(GL_ARRAY_BUFFER, 0, (MemoryUsage)*sizeof(float), GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT);


        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (GLvoid*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float)*8, (GLvoid*)(sizeof(float) * 3));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float)*8, (GLvoid*)(sizeof(float) * 5));
        glBindVertexArray(0);
    }

    void SetUpStaticIndexBuffer()
    {
        glBindVertexArray(vertexArray);
        glGenBuffers(1, &elementBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, (indices)*sizeof(unsigned int), elementData, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }   

    void SetUpBuffers()
    {
        glGenVertexArrays(1, &vertexArray);
        glBindVertexArray(vertexArray);

        glGenBuffers(1, &vertexBuffer);
        glGenBuffers(1, &elementBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, (indices)*sizeof(unsigned int), elementData, GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, (memoryDataBack+1)*sizeof(float), memoryData, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (GLvoid*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float)*8, (GLvoid*)(sizeof(float) * 3));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float)*8, (GLvoid*)(sizeof(float) * 5));

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void Draw(Camera& camera)
    {
        setMat4(program, "projection", camera.projection);
        setMat4(program, "view", camera.view);
        setFloat(program, "time", glfwGetTime());
        glBindVertexArray(vertexArray);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
        program.UseProgram();
        glDrawElements(GL_LINES, indices+1, GL_UNSIGNED_INT, 0);
    }

    ~MappedViewFrustrum()
    {

    }
};

void UpdateThisMappedPlane(void* MappedPlanePointer, ArgumentPackage thePackage);

struct MappedPlane
{
private:
    float* memoryData;
    unsigned int* elementData;
    unsigned int vertexBuffer, vertexArray;
    unsigned int elementBuffer;
    NGLProgram program;
    int memoryDataBack;
    int elementDataBack;
    int vertices; 
    int indices;

    UVSphereFactory* _factory;

public:
    std::vector<RelativeObject> OnUpdates;

    MappedPlane(UVSphereFactory* factory) : memoryDataBack(0), vertices(0), indices(0), elementDataBack(0), memoryData(nullptr), elementData(nullptr), program(CreateShader("/shaders/GraphicVector.vs", "/shaders/GraphicVector.fs"))
    {
        _factory = factory;
    }

    void CreateNormalPlane(SDFVec3 Origin, SDFVec3 Normal, float Width, float Height)
    {

        SDFVec3 ZBase = {0,0,-3};
        if(ZBase /= Normal)
        {
            ZBase.z -= 1;
            ZBase.y = -3;
        }

        SDFVec3 XAxis = Cross(Normal, ZBase);
        SDFVec3 YAxis = Cross(Normal, XAxis);

        if(abs(XAxis.x) < abs(YAxis.x))
        {
            //switch
        }
        if(XAxis.x < 0)
        {
            XAxis *= -1;
        }
        
        if(YAxis.y < 0)
        {
            YAxis *= -1;
        }


        XAxis.normalize();
        YAxis.normalize();
        


        int subdivisions = 10;
        int vs = 8*8*subdivisions*subdivisions;
        int ib = 12*subdivisions*subdivisions;

        //memoryData = new float[vs];
        SetUpMemoryMap(vs);
        elementData = new unsigned int[ib];
        float xstep = Width/subdivisions;
        float ystep = Height/subdivisions;
        SDFVec3 StartingPoint = Origin - (XAxis*(Width/2) + YAxis*(Height/2));
        //-XAxis*((Width/2))
        float Thickness = 0.01;

        for(int i = 0; i < subdivisions; i++)
        {
            for(int j = 0; j < subdivisions; j++)
            {
                SDFVec3 IterativeOrigin = StartingPoint + (XAxis*j*xstep) + (YAxis*i*ystep);
                SDFVec3 NextOrigin = StartingPoint + (XAxis*(j+1)*xstep) + (YAxis*(i)*ystep);
                //_factory->ConstructSphereElement(IterativeOrigin, 0.01, 6);

                SDFVec3 BottomLeft = IterativeOrigin - (YAxis*Thickness);
                SDFVec3 BottomRight = NextOrigin - (YAxis*Thickness);
                SDFVec3 TopRight = NextOrigin + (YAxis*Thickness);
                SDFVec3 TopLeft = IterativeOrigin + (YAxis*Thickness);

                fTriQuad(BottomLeft, BottomRight, TopRight, TopLeft, (float*)memoryData, memoryDataBack, elementData, elementDataBack, indices);

                SDFVec3 TopOrigin = StartingPoint + (XAxis*(j+1)*xstep) + (YAxis*(i+1)*ystep);
                BottomLeft = TopOrigin - (XAxis*Thickness) - (YAxis*Thickness);
                BottomRight = NextOrigin - (XAxis*Thickness) + (YAxis*Thickness);
                TopRight = NextOrigin + (XAxis*Thickness) + (YAxis*Thickness);
                TopLeft = TopOrigin + (XAxis*Thickness) - (YAxis*Thickness);

                fTriQuad(BottomLeft, BottomRight, TopRight, TopLeft, (float*)memoryData, memoryDataBack, elementData, elementDataBack, indices);



            }
        }

        //SetupBuffers();
        SetUpStaticIndexBuffer();
    }

    void UpdateNormalPlane(SDFVec3 Origin, SDFVec3 Normal, float Width, float Height)
    {
        int mback = 0;
        int eback = 0;
        int j = 0;


        SDFVec3 ZBase = {0,1,0};

        SDFVec3 XAxis = Cross(Normal, ZBase);
        SDFVec3 YAxis = Cross(Normal, XAxis);

        if(abs(XAxis.x) < abs(YAxis.x))
        {
            //switch
        }
        if(XAxis.x < 0)
        {
            XAxis *= -1;
        }
        
        if(YAxis.y < 0)
        {
            YAxis *= -1;
        }


        XAxis.normalize();
        YAxis.normalize();
        


        int subdivisions = 10;

        float xstep = Width/subdivisions;
        float ystep = Height/subdivisions;
        SDFVec3 StartingPoint = Origin - (XAxis*(Width/2) + YAxis*(Height/2));
        //-XAxis*((Width/2))
        float Thickness = 0.01;
        for(int i = 0; i < subdivisions; i++)
        {
            for(int j = 0; j < subdivisions; j++)
            {
                // SDFVec3 IterativeOrigin = StartingPoint + (XAxis*j*xstep) + (YAxis*i*ystep);
                SDFVec3 NextOrigin = StartingPoint + (XAxis*(j+1)*xstep) + (YAxis*(i)*ystep);
                SDFVec3 IterativeOrigin = StartingPoint + (XAxis*j*xstep) + (YAxis*i*ystep);
                
                //_factory->ConstructSphereElement(NextOrigin, 0.01, 12);

                SDFVec3 BottomLeft = IterativeOrigin - (YAxis*Thickness);
                SDFVec3 BottomRight = NextOrigin - (YAxis*Thickness);
                SDFVec3 TopRight = NextOrigin + (YAxis*Thickness);
                SDFVec3 TopLeft = IterativeOrigin + (YAxis*Thickness);

                // _factory->ConstructSphereElement(BottomLeft, 0.001, 6);
                // _factory->ConstructSphereElement(BottomRight, 0.001, 6);
                // _factory->ConstructSphereElement(TopRight, 0.001, 6);
                // _factory->ConstructSphereElement(TopLeft, 0.001, 6);

                fTriQuadE(BottomLeft, BottomRight, TopRight, TopLeft, memoryData, mback);

                // fPoint(BottomLeft, 0,0, memoryData, mback);
                // fPoint(BottomRight, 1,0, memoryData, mback);
                // fPoint(TopRight, 1,1, memoryData, mback);
                // fPoint(TopLeft, 0,1, memoryData, mback);


                SDFVec3 TopOrigin = StartingPoint + (XAxis*(j+1)*xstep) + (YAxis*(i+1)*ystep);
                BottomLeft = TopOrigin - (XAxis*Thickness) - (YAxis*Thickness);
                BottomRight = NextOrigin - (XAxis*Thickness) + (YAxis*Thickness);
                TopRight = NextOrigin + (XAxis*Thickness) + (YAxis*Thickness);
                TopLeft = TopOrigin + (XAxis*Thickness) - (YAxis*Thickness);

                fTriQuadE(BottomLeft, BottomRight, TopRight, TopLeft, memoryData, mback);

                // fPoint(BottomLeft, 0,0, memoryData, mback);
                // fPoint(BottomRight, 1,0, memoryData, mback);
                // fPoint(TopRight, 1,1, memoryData, mback);
                // fPoint(TopLeft, 0,1, memoryData, mback);

            }
        }

        CallOnUpdates(Origin, Normal, Width, Height);

    }

    void UpdateNormalPlane(SDFVec3 Origin, SDFVec3 Up, SDFVec3 Right, float Width, float Height)
    {

        int mback = 0;
        int eback = 0;
        int j = 0;

        SDFVec3 XAxis = Right;
        SDFVec3 YAxis = Up;

        XAxis.normalize();
        YAxis.normalize();
        
        int subdivisions = 10;

        float xstep = Width/subdivisions;
        float ystep = Height/subdivisions;
        SDFVec3 StartingPoint = Origin - (XAxis*(Width/2) + YAxis*(Height/2));
        //-XAxis*((Width/2))
        float Thickness = 0.01;
        for(int i = 0; i < subdivisions; i++)
        {
            for(int j = 0; j < subdivisions; j++)
            {
                // SDFVec3 IterativeOrigin = StartingPoint + (XAxis*j*xstep) + (YAxis*i*ystep);
                SDFVec3 NextOrigin = StartingPoint + (XAxis*(j+1)*xstep) + (YAxis*(i)*ystep);
                SDFVec3 IterativeOrigin = StartingPoint + (XAxis*j*xstep) + (YAxis*i*ystep);
                
                //_factory->ConstructSphereElement(NextOrigin, 0.01, 12);

                SDFVec3 BottomLeft = IterativeOrigin - (YAxis*Thickness);
                SDFVec3 BottomRight = NextOrigin - (YAxis*Thickness);
                SDFVec3 TopRight = NextOrigin + (YAxis*Thickness);
                SDFVec3 TopLeft = IterativeOrigin + (YAxis*Thickness);

                // _factory->ConstructSphereElement(BottomLeft, 0.001, 6);
                // _factory->ConstructSphereElement(BottomRight, 0.001, 6);
                // _factory->ConstructSphereElement(TopRight, 0.001, 6);
                // _factory->ConstructSphereElement(TopLeft, 0.001, 6);

                fTriQuadE(BottomLeft, BottomRight, TopRight, TopLeft, memoryData, mback);

                // fPoint(BottomLeft, 0,0, memoryData, mback);
                // fPoint(BottomRight, 1,0, memoryData, mback);
                // fPoint(TopRight, 1,1, memoryData, mback);
                // fPoint(TopLeft, 0,1, memoryData, mback);


                SDFVec3 TopOrigin = StartingPoint + (XAxis*(j+1)*xstep) + (YAxis*(i+1)*ystep);
                BottomLeft = TopOrigin - (XAxis*Thickness) - (YAxis*Thickness);
                BottomRight = NextOrigin - (XAxis*Thickness) + (YAxis*Thickness);
                TopRight = NextOrigin + (XAxis*Thickness) + (YAxis*Thickness);
                TopLeft = TopOrigin + (XAxis*Thickness) - (YAxis*Thickness);

                fTriQuadE(BottomLeft, BottomRight, TopRight, TopLeft, memoryData, mback);

                // fPoint(BottomLeft, 0,0, memoryData, mback);
                // fPoint(BottomRight, 1,0, memoryData, mback);
                // fPoint(TopRight, 1,1, memoryData, mback);
                // fPoint(TopLeft, 0,1, memoryData, mback);

            }
        }
    
        CallOnUpdates(Origin, Up, Right, Width, Height);
    }

    void CallOnUpdates(SDFVec3 Origin, SDFVec3 Up, SDFVec3 Right, float Width, float Height)
    {
        ArgumentPackage P;
        P.Verticies[0] = Origin;
        P.Verticies[1] = Up;
        P.Verticies[2] = Right;

        P.Paramters[0] = Width;
        P.Paramters[1] = Height;

        for(int i = 0; i < OnUpdates.size(); i++)
        {
            if(OnUpdates[i].callback != nullptr)
            {
                OnUpdates[i].callback(OnUpdates[i].self, P);
            }
        }


    }

    void CallOnUpdates(SDFVec3 Origin, SDFVec3 Normal, float Width, float Height)
    {
        ArgumentPackage P;
        P.Verticies[0] = Origin;
        P.Verticies[1] = Normal;

        P.Paramters[0] = Width;
        P.Paramters[1] = Height;

        for(int i = 0; i < OnUpdates.size(); i++)
        {
            if(OnUpdates[i].callback != nullptr)
            {
                OnUpdates[i].callback(OnUpdates[i].self, P);
            }
        }


    }

    void SetUpMemoryMap(int MemoryUsage)
    {
        glGenVertexArrays(1, &vertexArray);
        glGenBuffers(1, &vertexBuffer);
        glBindVertexArray(vertexArray);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferStorage(GL_ARRAY_BUFFER, (MemoryUsage)*sizeof(float), 0, GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT);
        memoryData = (float*)glMapBufferRange(GL_ARRAY_BUFFER, 0, (MemoryUsage)*sizeof(float), GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT);


        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (GLvoid*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float)*8, (GLvoid*)(sizeof(float) * 3));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float)*8, (GLvoid*)(sizeof(float) * 5));
        glBindVertexArray(0);
    }

    void SetUpStaticIndexBuffer()
    {
        glBindVertexArray(vertexArray);
        glGenBuffers(1, &elementBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, (indices)*sizeof(unsigned int), elementData, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }   

    void SetupBuffers()
    {
        glGenVertexArrays(1, &vertexArray);
        glBindVertexArray(vertexArray);

        glGenBuffers(1, &vertexBuffer);
        glGenBuffers(1, &elementBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, (indices)*sizeof(unsigned int), elementData, GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, (memoryDataBack+1)*sizeof(float), memoryData, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (GLvoid*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float)*8, (GLvoid*)(sizeof(float) * 3));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float)*8, (GLvoid*)(sizeof(float) * 5));

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void UpdateBuffers()
    {

        glBindVertexArray(vertexArray);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, (indices)*sizeof(unsigned int), elementData);

        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferSubData(GL_ARRAY_BUFFER, 0, (memoryDataBack+1)*sizeof(float), memoryData);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void Draw(Camera& camera)
    {
        setMat4(program, "projection", camera.projection);
        setMat4(program, "view", camera.view);
        setFloat(program, "time", glfwGetTime());
        glBindVertexArray(vertexArray);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
        program.UseProgram();
        glDrawElements(GL_TRIANGLES, indices+1, GL_UNSIGNED_INT, 0);
    }

    void AttachToViewFrustrum(MappedViewFrustrum* view)
    {
        view->OnUpdates.push_back({UpdateThisMappedPlane,this});
    }

    ~MappedPlane()
    {

    }

};

void UpdateThisMappedPlane(void* MappedPlanePointer, ArgumentPackage thePackage)
{
    MappedPlane* P = (MappedPlane*)MappedPlanePointer;
    float w = thePackage.Paramters[1];
    SDFVec3 origin = thePackage.Verticies[1];
    SDFVec3 norm = thePackage.Verticies[2];

    P->UpdateNormalPlane(origin, thePackage.Verticies[4], w,w);
    //P->UpdateNormalPlane(origin, thePackage.Verticies[3],thePackage.Verticies[2], w,w);
}

void UpdateThisPlaneProjection(void* MappedPlaneProjection, ArgumentPackage P);

struct PlaneProjection
{

    unsigned int vertexBuffer, vertexArray;
    NGLProgram program;

    std::vector<SDFVec3> _verts;
    SDFVec3 _Origin, _XAxis, _YAxis;

    float* pp;

    

    PlaneProjection(SDFVec3 Origin, SDFVec3 Normal, float Width, float Height, std::vector<SDFVec3> verts) :  _Origin(Origin), _verts(verts), program(CreateShader("/shaders/PlaneProjection.vs", "/shaders/PlaneProjection.fs"))
    {
        SDFVec3 ZBase = {0,0,-3};
        if(ZBase /= Normal)
        {
            ZBase.z -= 1;
            ZBase.y = -3;
        }

        SDFVec3 XAxis = Cross(Normal, ZBase);
        SDFVec3 YAxis = Cross(Normal, XAxis);

        if(abs(XAxis.x) < abs(YAxis.x))
        {
            //switch
        }
        if(XAxis.x < 0)
        {
            XAxis *= -1;
        }
        
        if(YAxis.y < 0)
        {
            YAxis *= -1;
        }


        XAxis.normalize();
        YAxis.normalize();
        int subdivisions = 10;

        float xstep = Width/subdivisions;
        float ystep = Height/subdivisions;

        _XAxis = XAxis*xstep;
        _YAxis = YAxis*ystep;

        pp = new float[16];
        for(int i =0; i < 16; i++)
        {
            pp[i] = 0.0f;
        }
        SetUpBuffersElement();
    }

    float* projectionMatrix()
    {
        // pp[0] = _XAxis.x;
        // pp[1] = _XAxis.y;
        // pp[2] = _XAxis.z;

        // pp[4] = _YAxis.x;
        // pp[5] = _YAxis.y;
        // pp[6] = _YAxis.z;
        // pp[10] = 1;

        // pp[12] = _Origin.x;
        // pp[13] = _Origin.y;
        // pp[14] = _Origin.z;
        float pz[] = {
            _XAxis.x,_XAxis.y,_XAxis.z,0,
            _YAxis.x,_YAxis.y,_YAxis.z,0,
            0,0,1,0,
            _Origin.x,_Origin.y,_Origin.z,1
        };
        for(int i = 0; i < 16; i++)
        {
            pp[i] = pz[i];
        }

        return pp;
    }

    void Draw(Camera& camera)
    {
        glBindVertexArray(vertexArray);
        setMat4(program, "coordinateProjection", projectionMatrix());
        setMat4(program, "projection", camera.projection);
        setMat4(program, "view", camera.view);
        program.UseProgram();
        glDrawArrays(GL_LINES, 0, _verts.size());
    }

    void SetUpBuffersElement()
    {
        glGenVertexArrays(1, &vertexArray);
        glBindVertexArray(vertexArray);
        glGenBuffers(1, &vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, (_verts.size())*sizeof(float)*3, _verts.data(), GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void AttachToMappedPlane(MappedPlane& Plane)
    {
        Plane.OnUpdates.push_back({UpdateThisPlaneProjection, this});
    }

    ~PlaneProjection()
    {

    }
};

void UpdateThisPlaneProjection(void* MappedPlaneProjection, ArgumentPackage P)
{
    PlaneProjection* MappedProjection = (PlaneProjection*)MappedPlaneProjection;

    SDFVec3 Origin = P.Verticies[0];
    SDFVec3 Normal = P.Verticies[1];

    float Width = P.Paramters[0];
    float Height = P.Paramters[1];

    SDFVec3 ZBase = {0,1,0};

    SDFVec3 XAxis = Cross(Normal, ZBase);
    SDFVec3 YAxis = Cross(Normal, XAxis);

    if(abs(XAxis.x) < abs(YAxis.x))
    {
        //switch
    }
    if(XAxis.x < 0)
    {
        XAxis *= -1;
    }
    
    if(YAxis.y < 0)
    {
        YAxis *= -1;
    }


    XAxis.normalize();
    YAxis.normalize();
    
    int subdivisions = 10;

    float xstep = Width/subdivisions;
    float ystep = Height/subdivisions;

    
    

    MappedProjection->_Origin = Origin;
    MappedProjection->_XAxis = XAxis*xstep;
    MappedProjection->_YAxis = YAxis*ystep;
    
}

#endif