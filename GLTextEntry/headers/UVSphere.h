#ifndef UVSPHERE_H
#define UVSPHERE_H

#include "LearnOpenglHelper.h"
#include "FGeom.h"
#include "Camera.h"

struct UVSphere
{
    SDFVec3 m_Center;

    float* memoryData;
    unsigned int* elementData;

    unsigned int vertexBuffer, vertexArray;
    unsigned int elementBuffer;
    NGLProgram program;
    int memoryDataBack;
    int elementDataBack;
    int vertices; 
    int indices;


    float radius;
    float subdivisions = 6;

    UVSphere(SDFVec3 Center, float p_radius) : radius(p_radius), memoryDataBack(0), vertices(0), indices(0), elementDataBack(0), memoryData(nullptr), elementData(nullptr), program(CreateShader("/shaders/GraphicVector.vs", "/shaders/GraphicVector.fs"))
    {
        m_Center = Center;
        ConstructSphereElement();
        SetUpBuffersElement();
    }

    void ConstructSphereElement()
    {
        float requiredPhi = (2 * M_PI) / subdivisions;
        float requiredTheta = M_PI / subdivisions;

        memoryData = new float[10 * 10 * 32 * 32];
        elementData = new unsigned int[10 * 10 * 10 * 32];

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

                fTriQuad(c1, c2, c3, c4, memoryData, memoryDataBack, elementData, j, indices);
            }
        }



    }

    void DrawElements(Camera& camera)
    {
        glBindVertexArray(vertexArray);
        setMat4(program, "projection", camera.projection);
        setMat4(program, "view", camera.view);
        setFloat(program, "time", glfwGetTime());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
        program.UseProgram();
        glDrawElements(GL_TRIANGLES, indices+1, GL_UNSIGNED_INT, 0);
    }

    void SetUpBuffersElement()
    {
        glGenVertexArrays(1, &vertexArray);
        glBindVertexArray(vertexArray);

        unsigned int vertexBuffer;
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

    ~UVSphere()
    {
        if(memoryData != nullptr)
        {
            delete[] memoryData;
            memoryData = nullptr;
        }

        if(elementData != nullptr)
        {
            delete[] elementData;
            elementData = nullptr;
        }
    }
};

#endif