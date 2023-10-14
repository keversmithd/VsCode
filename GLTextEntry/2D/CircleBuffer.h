#ifndef CIRCLE_BUFFER_H
#define CIRCLE_BUFFER_H

#include "LearnOpenglHelper.h"
#include "FGeom.h"
#include "Camera.h"


struct TwoBuffer
{
    float* memoryData;
    int usedMemoryData;
    int reservedMemoryData;
    unsigned int* elementData;
    int reservedElementData;
    int usedElementData;

    unsigned int vertexBuffer, vertexArray;
    unsigned int elementBuffer;
    NGLProgram program;
    int memoryDataBack;
    int elementDataBack;
    int indices;

    bool BuffersCreated;
    bool BuffersNeedUpdate;

    int PropertyIndex;

    TwoBuffer() : PropertyIndex(0), indices(0), BuffersCreated(false), BuffersNeedUpdate(false), usedMemoryData(0), usedElementData(0), reservedMemoryData(0), reservedElementData(0), memoryDataBack(0), elementDataBack(0), memoryData(nullptr), elementData(nullptr), program(CreateShader("/2D/Shaders/CircleShader.vs", "/2D/Shaders/CircleShader.fs"))
    {

    }

    int CheckMemory(int FloatsRequired, unsigned int IntsRequired)
    {
        
        if(usedMemoryData + FloatsRequired > reservedMemoryData)
        {
            resizeMemoryData(FloatsRequired);
        }

        if(usedElementData+IntsRequired > reservedElementData)
        {
            resizeElementData(IntsRequired);
        }
        BuffersNeedUpdate = true;

        return PropertyIndex++;
    }

    void resizeMemoryData(int required)
    {
        float* memBuffer = new float[(required+reservedMemoryData)*2];
        reservedMemoryData = (required+reservedMemoryData)*2;

        if(memoryData != nullptr && memBuffer != memoryData)
        {
            memcpy(memBuffer, memoryData, usedMemoryData*sizeof(float));
            delete[] memoryData;

            
        }

        memoryData = memBuffer;
    }

    void resizeElementData(int required)
    {
        unsigned int* memBuffer = new unsigned int[(required+reservedElementData)*2];
        reservedElementData = (required+reservedElementData)*2;

        if(elementData != nullptr && memBuffer != elementData)
        {
            memcpy(memBuffer, elementData, usedElementData*sizeof(unsigned int));
            delete[] elementData; 
        }

        elementData = memBuffer;
    }

    void UpdateBuffers()
    {
        if(BuffersCreated == false)
        {
            glGenVertexArrays(1, &vertexArray);
            glBindVertexArray(vertexArray);

            unsigned int vertexBuffer;
            glGenBuffers(1, &vertexBuffer);
            glGenBuffers(1, &elementBuffer);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, (elementDataBack)*sizeof(unsigned int), elementData, GL_STATIC_DRAW);

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

            BuffersCreated = true;
        }else
        {
            glBindVertexArray(vertexArray);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, (elementDataBack+1)*sizeof(unsigned int), NULL, GL_STATIC_DRAW);
            glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, (elementDataBack+1)*sizeof(unsigned int), elementData);

            glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
            glBufferData(GL_ARRAY_BUFFER, (memoryDataBack+1)*sizeof(float), NULL, GL_STATIC_DRAW);
            glBufferSubData(GL_ARRAY_BUFFER, 0, (memoryDataBack+1)*sizeof(float), memoryData);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
            BuffersNeedUpdate = false;
        }
    }

    void Draw(OrthoCamera& MainCamera)
    {
        if(BuffersNeedUpdate == true)
        {
            UpdateBuffers();
            BuffersNeedUpdate = false;
        }
        glBindVertexArray(vertexArray);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
        program.UseProgram();
        setMat4(program, "projection", MainCamera.projection);
        setMat4(program, "view", MainCamera.view);
        glDrawElements(GL_TRIANGLES, (elementDataBack), GL_UNSIGNED_INT, 0);
    }

    ~TwoBuffer()
    {
        if(memoryData != nullptr)
        {
            delete[] memoryData;
        }

        if(elementData != nullptr)
        {
            delete[] elementData;
        }
    }
};


struct Line
{
    TwoBuffer* MainBuffer;
    SDFVec3 Origin;
    SDFVec3 Destination;
    float Thickness;
    int PropertyIndex;

    Line(SDFVec3 origin, SDFVec3 destination, float thickness, TwoBuffer* TB) : PropertyIndex(0), MainBuffer(TB), Origin(origin), Destination(destination), Thickness(thickness)
    {
        ConstructLine();
    }

    void ConstructLine()
    {
        int tris_memory = 4*8;
        int element_memory = 6;

        SDFVec3 DV = Destination-Origin;
        SDFVec3 E = {-DV.y,DV.x};
        E.normalize();
        E *= Thickness;


        PropertyIndex = MainBuffer->CheckMemory(tris_memory, element_memory);

        fPoint(Origin+E, 0,0, MainBuffer->memoryData, MainBuffer->memoryDataBack);
        fPoint(Destination+E, 1,0, MainBuffer->memoryData, MainBuffer->memoryDataBack);
        fPoint(Destination-E, 1,1, MainBuffer->memoryData, MainBuffer->memoryDataBack);
        fPoint(Origin-E, 0,1, MainBuffer->memoryData, MainBuffer->memoryDataBack);

        MainBuffer->elementData[MainBuffer->elementDataBack++] = MainBuffer->indices;
        MainBuffer->elementData[MainBuffer->elementDataBack++] = MainBuffer->indices+1;
        MainBuffer->elementData[MainBuffer->elementDataBack++] = MainBuffer->indices+2;

        MainBuffer->elementData[MainBuffer->elementDataBack++] = MainBuffer->indices;
        MainBuffer->elementData[MainBuffer->elementDataBack++] = MainBuffer->indices+2;
        MainBuffer->elementData[MainBuffer->elementDataBack++] = MainBuffer->indices+3;

        MainBuffer->indices += 4;
    }
};
struct Circle
{
    SDFVec3 m_Center;
    float f_radius;
    int n_subdivisions;
    TwoBuffer* MainBuffer;
    int PropertyIndex = 0;

    Circle(SDFVec3 Origin, float Radius, int Subdivisions, TwoBuffer* Buffer) : MainBuffer(Buffer)
    {
        
        m_Center = Origin;
        f_radius = Radius;
        n_subdivisions = Subdivisions;
        ConstructCircle();
    }

    void ConstructCircle()
    {
        int tris_memory = (((n_subdivisions*3))*8);
        int element_memory = (n_subdivisions)*3;

        PropertyIndex = MainBuffer->CheckMemory(tris_memory, element_memory);

        float pi = 3.14159265359;
        float subStep  = 2.0*pi/n_subdivisions;

        fPoint(m_Center, 0,0, MainBuffer->memoryData, MainBuffer->memoryDataBack);
        int mainBufferIndicesOrigin = MainBuffer->indices;
        MainBuffer->indices++;
        
        for(int i = 0; i < n_subdivisions; i++)
        {
            //fPoint(m_Center, 0,0, memoryData,  memoryDataBack);
            fPoint({m_Center.x+f_radius*cosf(i*subStep),m_Center.y+f_radius*sinf(i*subStep),m_Center.z+0},1,0,MainBuffer->memoryData,MainBuffer->memoryDataBack);
            fPoint({m_Center.x+f_radius*cosf((i+1)*subStep),m_Center.y+f_radius*sinf((i+1)*subStep),m_Center.z+0},1,1,MainBuffer->memoryData,MainBuffer->memoryDataBack);

            MainBuffer->elementData[MainBuffer->elementDataBack++] = mainBufferIndicesOrigin;
            MainBuffer->elementData[MainBuffer->elementDataBack++] = MainBuffer->indices++;
            MainBuffer->elementData[MainBuffer->elementDataBack++] = MainBuffer->indices++;
        }




    }

    ~Circle()
    {
        
    }
};

    


#endif