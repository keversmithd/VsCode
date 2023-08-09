#ifndef UVSPHERE_H
#define UVSPHERE_H

#include "LearnOpenglHelper.h"
#include "FGeom.h"
#include "Camera.h"



struct UVSphereFactory
{
    float* vertexData;
    int vertexCapacity;
    int vertexDataBack;
    unsigned int* elementData;
    int elementCapacity;
    int elementDataBack;

    int elementIndexHead;

    unsigned int vertexBuffer, vertexArray, elementBuffer;

    NGLProgram program;

    int subdivisions = 6;

    bool BuffersSetUp;

    UVSphereFactory(int Reserve) : vertexDataBack(0), vertexCapacity(0), elementCapacity(0), elementIndexHead(0), elementDataBack(0), vertexData(nullptr), elementData(nullptr), program(CreateShader("/shaders/lightSource.vs", "/shaders/lightSource.fs")), BuffersSetUp(false)
    {
        vertexCapacity = Reserve*sizeof(float)*4;
        elementCapacity = Reserve*sizeof(unsigned int)*6;

        ResizeVertexData();
        ResizeElementData();

    }

    void ConstructSphereElement(SDFVec3 m_Center, float radius)
    {
        float requiredPhi = (2 * M_PI) / subdivisions;
        float requiredTheta = M_PI / subdivisions;
        
        int BytesOfVertex = subdivisions*subdivisions*sizeof(float)*8;
        int BytesOfElement = subdivisions*subdivisions*sizeof(unsigned int)*6;

        if((vertexDataBack*subdivisions*subdivisions*sizeof(float)*8)+BytesOfVertex > vertexCapacity)
        {
            ResizeVertexData();
        }

        if((elementDataBack*subdivisions*subdivisions*sizeof(unsigned int)*6)+BytesOfElement > elementCapacity)
        {
            ResizeElementData();
        }

        SDFVec3 c1, c2, c3, c4;

        int j = 0;

        for (int dp = 0; dp < subdivisions; dp++)
        {
            float phi0 = dp * requiredPhi;
            float phi1 = (dp + 1) * requiredPhi;

            for (int dt = 0; dt < subdivisions; dt++)
            {
                float theta0 = dt * requiredTheta;
                float theta1 = (dt + 1) * requiredTheta; // Fix the calculation here (use dt instead of dp)

                c1 = m_Center;
                c1 += SDFVec3(radius*cos(theta0) * sin(phi0), radius*sin(theta0) * sin(phi0), radius*cos(phi0));
                c2 = m_Center;
                c2 += SDFVec3(radius*cos(theta1) * sin(phi0), radius*sin(theta1) * sin(phi0), radius*cos(phi0));
                c3 = m_Center;
                c3 += SDFVec3(radius*cos(theta1) * sin(phi1), radius*sin(theta1) * sin(phi1), radius*cos(phi1));
                c4 = m_Center;
                c4 += SDFVec3(radius*cos(theta0) * sin(phi1), radius*sin(theta0) * sin(phi1), radius*cos(phi1));

                fTriQuad(c1, c2, c3, c4, vertexData, vertexDataBack, elementData, elementIndexHead, elementDataBack);
            }
        }



    }

    void UpdateSphereElement(SDFVec3 m_Center, float radius, int index)
    {
        int RequestedVertexIndex = index*(subdivisions*subdivisions*8);
        int RequestedElementIndex = index*(subdivisions*subdivisions*6);
        int RequestedElementIndexHead = index*(subdivisions*subdivisions*4);

        float requiredPhi = (2 * M_PI) / subdivisions;
        float requiredTheta = M_PI / subdivisions;

        SDFVec3 c1, c2, c3, c4;

        int j = 0;

        for (int dp = 0; dp < subdivisions; dp++)
        {
            float phi0 = dp * requiredPhi;
            float phi1 = (dp + 1) * requiredPhi;

            for (int dt = 0; dt < subdivisions; dt++)
            {
                float theta0 = dt * requiredTheta;
                float theta1 = (dt + 1) * requiredTheta; // Fix the calculation here (use dt instead of dp)

                c1 = m_Center;
                c1 += SDFVec3(radius*cos(theta0) * sin(phi0), radius*sin(theta0) * sin(phi0), radius*cos(phi0));
                c2 = m_Center;
                c2 += SDFVec3(radius*cos(theta1) * sin(phi0), radius*sin(theta1) * sin(phi0), radius*cos(phi0));
                c3 = m_Center;
                c3 += SDFVec3(radius*cos(theta1) * sin(phi1), radius*sin(theta1) * sin(phi1), radius*cos(phi1));
                c4 = m_Center;
                c4 += SDFVec3(radius*cos(theta0) * sin(phi1), radius*sin(theta0) * sin(phi1), radius*cos(phi1));

                fTriQuad(c1, c2, c3, c4, vertexData, RequestedVertexIndex, elementData, RequestedElementIndexHead, RequestedElementIndex);
            }
        }

        glBindBuffer(GL_VERTEX_ARRAY, vertexBuffer);
        glBufferSubData(GL_VERTEX_ARRAY, RequestedElementIndex*sizeof(float), (subdivisions*subdivisions*8)*sizeof(float), elementData+RequestedElementIndex);
        

    }

    void ResizeVertexData()
    {
        float* memBuffer = (float*)malloc(2*vertexCapacity);
        if(vertexData != nullptr && vertexData != memBuffer)
        {
            memcpy(vertexData, memBuffer, (vertexDataBack+1)*subdivisions*subdivisions*sizeof(float)*4);
            free(vertexData);
            vertexData = nullptr;
        }
        vertexData = memBuffer;
        vertexCapacity = 2*vertexCapacity;

    }

    void ResizeElementData()
    {
        unsigned int* memBuffer = (unsigned int*)malloc(2*elementCapacity);
        if(elementData != nullptr && elementData != memBuffer)
        {
            memcpy(elementData, memBuffer, (elementDataBack+1)*subdivisions*subdivisions*sizeof(unsigned int)*6);
            free(elementData);
            elementData = nullptr;
        }
        elementData = memBuffer;
        vertexCapacity = 2*vertexCapacity;
    }

    

    void DrawElements(Camera& camera)
    {

        if(BuffersSetUp == false)
        {
            SetUpBuffersElement();
        }
        glBindVertexArray(vertexArray);
        setMat4(program, "projection", camera.projection);
        setMat4(program, "view", camera.view);
        setFloat(program, "time", glfwGetTime());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
        program.UseProgram();
        glDrawElements(GL_TRIANGLES, (elementDataBack+1), GL_UNSIGNED_INT, 0);
    }

    void SetUpBuffersElement()
    {
        glGenVertexArrays(1, &vertexArray);
        glBindVertexArray(vertexArray);

        unsigned int vertexBuffer;
        glGenBuffers(1, &vertexBuffer);
        glGenBuffers(1, &elementBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, (elementDataBack+1)*subdivisions*subdivisions*sizeof(unsigned int)*6, elementData, GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, (vertexDataBack+1)*subdivisions*subdivisions*sizeof(float)*4, vertexData, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (GLvoid*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float)*8, (GLvoid*)(sizeof(float) * 3));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float)*8, (GLvoid*)(sizeof(float) * 5));

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    ~UVSphereFactory()
    {
        if(vertexData != nullptr)
        {
            delete[] vertexData;
            vertexData = nullptr;
        }

        if(elementData != nullptr)
        {
            delete[] elementData;
            elementData = nullptr;
        }
    }
};

UVSphereFactory SphereFactory(3);

struct UVSphere
{
    UVSphere(float radius,  SDFVec3 location)
    {
        SphereFactory.ConstructSphereElement(location, radius);
    }
};


#endif