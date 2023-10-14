#ifndef UVSPHEREF_H
#define UVSPHEREF_H

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
    bool BuffersSetup;
    bool BuffersNeedUpdate;

    UVSphereFactory(int Reserve) : BuffersNeedUpdate(false), vertexDataBack(0), vertexCapacity(0), elementCapacity(0), elementIndexHead(0), elementDataBack(0), vertexData(nullptr), elementData(nullptr), program(CreateShader("shaders/SphereFactory.vs", "shaders/SphereFactory.fs")), BuffersSetup(false)
    {
        vertexCapacity = 6*6*Reserve*4*sizeof(float)*8;
        elementCapacity = 6*6*Reserve*sizeof(unsigned int)*6;

        ResizeVertexData(0);
        ResizeElementData(0);

    }

    void ConstructSphereElement(SDFVec3 m_Center, float radius, int subdivisions)
    {
        float requiredPhi = (2 * M_PI) / subdivisions;
        float requiredTheta = M_PI / subdivisions;
        
        int BytesOfVertex = subdivisions*subdivisions*4*sizeof(float)*8;
        int BytesOfElement = subdivisions*subdivisions*sizeof(unsigned int)*6;

        if(((vertexDataBack+1)*sizeof(float))+BytesOfVertex > vertexCapacity)
        {
            ResizeVertexData(BytesOfVertex);
        }

        if(((elementDataBack+1)*sizeof(unsigned int))+BytesOfElement > elementCapacity)
        {
            ResizeElementData(BytesOfElement);
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

        if(BuffersSetup == true)
        {
            BuffersNeedUpdate = true;
        }
    }

    void ResizeVertexData(int AdditionalCapacity)
    {
        float* memBuffer = (float*)malloc(2*(vertexCapacity+AdditionalCapacity));
        if(vertexData != nullptr && vertexData != memBuffer)
        {
            memcpy(memBuffer, vertexData, (vertexDataBack+1)*sizeof(float));
            free(vertexData);
            vertexData = nullptr;
        }
        vertexData = memBuffer;
        vertexCapacity = 2*(vertexCapacity+AdditionalCapacity);
    }

    void ResizeElementData(int AdditionalCapacity)
    {
        unsigned int* memBuffer = (unsigned int*)malloc(2*(elementCapacity+AdditionalCapacity));
        if(elementData != nullptr && elementData != memBuffer)
        {
            memcpy(memBuffer, elementData, (elementDataBack+1)*sizeof(unsigned int));
            free(elementData);
            elementData = nullptr;
        }
        elementData = memBuffer;
        elementCapacity = 2*(elementCapacity+AdditionalCapacity);
    }

    void DrawElements(Camera& camera)
    {

        if(BuffersSetup == false)
        {
            SetUpBuffersElement();
        }else if(BuffersNeedUpdate == true)
        {
            UpdateBuffers();
        }


        glBindVertexArray(vertexArray);
        setMat4(program, "projection", camera.projection);
        setMat4(program, "view", camera.view);
        //setFloat(program, "time", glfwGetTime());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
        program.UseProgram();
        glDrawElements(GL_TRIANGLES, (elementDataBack+1), GL_UNSIGNED_INT, 0);
    }

    void SetUpBuffersElement()
    {
        glGenVertexArrays(1, &vertexArray);
        glBindVertexArray(vertexArray);

        glGenBuffers(1, &vertexBuffer);
        glGenBuffers(1, &elementBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, (elementDataBack+1)*sizeof(unsigned int), elementData, GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, (vertexDataBack+1)*sizeof(float), vertexData, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (GLvoid*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float)*8, (GLvoid*)(sizeof(float) * 3));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float)*8, (GLvoid*)(sizeof(float) * 5));

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        BuffersSetup = true;
    }
    void UpdateBuffers()
    {
        glBindVertexArray(vertexArray);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, (elementDataBack+1)*sizeof(unsigned int), NULL, GL_STATIC_DRAW);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, (elementDataBack+1)*sizeof(unsigned int), elementData);

        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, (vertexDataBack+1)*sizeof(float), NULL, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, (vertexDataBack+1)*sizeof(float), vertexData);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        BuffersNeedUpdate = false;
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

        glDeleteBuffers(1, &vertexBuffer);
        glDeleteBuffers(1, &elementBuffer);
    }
};





struct UVSphereF
{
private:
    int vertexStart;
    int elementStart;

public:
    UVSphereF(SDFVec3 location, float radius, int subdivsions, UVSphereFactory& factory)
    {
        factory.ConstructSphereElement(location, radius, subdivsions);
    }

    UVSphereF()
    {

    }

    ~UVSphereF()
    {
        
    }
};




#endif