#ifndef INPUT_BOX
#define INPUT_BOX

#include "LearnOpenglHelper.h"
#include "FGeom.h"
#include "Camera.h"

#include "GraphicVector.h"

struct InputBoxUpdate
{
    SDFBoundingVolume m_volume;
    float* memoryData;
    unsigned int* elementData;

    unsigned int vertexBuffer, vertexArray;
    unsigned int elementBuffer;
    NGLProgram program;
    int memoryDataBack;
    int elementDataBack;
    int vertices; 
    int indices;
    float CuboidThickness = 0.1;
    int j = 0;

    std::vector<GraphicVector> drawingVectors;

    
    InputBoxUpdate(SDFBoundingVolume volume) : m_volume(volume), memoryDataBack(0), vertices(0), indices(0), elementDataBack(0), memoryData(nullptr), elementData(nullptr), program(CreateShader("/shaders/GraphicVector.vs", "/shaders/GraphicVector.fs"))
    {
        ConstructBox();
        SetUpBuffers();
    }
    
    void AddRectoid(SDFVec3 a, SDFVec3 b)
    {

        const SDFVec3 axis = b-a;
        SDFVec3 xnorm = Cross(SDFVec3(0,1,0),axis);
        if(Mag(xnorm) == 0)
        {
            xnorm = Cross(SDFVec3(1,0,0), axis);
        }
        xnorm.normalize();
        xnorm*=CuboidThickness;
        SDFVec3 ynorm = Cross(xnorm,  axis);
        ynorm.normalize();
        ynorm*=CuboidThickness;

        
        fTriQuad(a-xnorm-ynorm, a+xnorm-ynorm, a+xnorm+ynorm, a-xnorm+ynorm, memoryData,  memoryDataBack, elementData, j, indices);
        fTriQuad(b-xnorm-ynorm, b+xnorm-ynorm, b+xnorm+ynorm, b-xnorm+ynorm, memoryData,  memoryDataBack, elementData, j, indices);

        fTriQuad(a+xnorm-ynorm, b+xnorm-ynorm, b+xnorm+ynorm, a+xnorm+ynorm, memoryData,  memoryDataBack, elementData, j, indices);
        fTriQuad(a-xnorm-ynorm, b-xnorm-ynorm, b-xnorm+ynorm, a-xnorm+ynorm, memoryData,  memoryDataBack, elementData, j, indices);

        fTriQuad(a+ynorm-xnorm, b+ynorm-xnorm, b+ynorm+xnorm, a+ynorm+xnorm, memoryData,  memoryDataBack, elementData, j, indices);
        fTriQuad(a-ynorm-xnorm, b-ynorm-xnorm, b-ynorm+xnorm, a-ynorm+xnorm, memoryData,  memoryDataBack, elementData, j, indices);
    }

    void ConstructBox()
    {


        //bottom left front
        const SDFVec3 b0 = SDFVec3(m_volume.TopLeftFront.x, m_volume.BottomRightBack.y, m_volume.TopLeftFront.z);
        //bottom right front
        const SDFVec3 b1 = SDFVec3(m_volume.BottomRightBack.x, m_volume.BottomRightBack.y, m_volume.TopLeftFront.z);
        //bottom right back
        const SDFVec3 b2 = SDFVec3(m_volume.BottomRightBack.x, m_volume.BottomRightBack.y, m_volume.BottomRightBack.z);
        //bottom left back
        const SDFVec3 b3 = SDFVec3(m_volume.TopLeftFront.x, m_volume.BottomRightBack.y, m_volume.BottomRightBack.z);

       
        //top left front
        const SDFVec3 b4 = SDFVec3(m_volume.TopLeftFront.x, m_volume.TopLeftFront.y, m_volume.TopLeftFront.z);
        //top right front
        const SDFVec3 b5 = SDFVec3(m_volume.BottomRightBack.x, m_volume.TopLeftFront.y, m_volume.TopLeftFront.z);
        //top right back
        const SDFVec3 b6 = SDFVec3(m_volume.BottomRightBack.x, m_volume.TopLeftFront.y, m_volume.BottomRightBack.z);
        //top left back
        const SDFVec3 b7 = SDFVec3(m_volume.TopLeftFront.x, m_volume.TopLeftFront.y, m_volume.BottomRightBack.z);
        
        // SDFVec3 TB1 = b1-b0;
        // TB1 *= CuboidThickness;
        // SDFVec3 TB2 = b3-b2;
        // TB2 *= CuboidThickness;

        // SDFVec3 TT1 = b5-b4;
        // TT1 *= CuboidThickness;
        // SDFVec3 TT2 = b6-b7;
        // TT2 *= CuboidThickness;
        
        //16 verts per rectoid
        //6 faces per rectoid

        memoryData = new float[24*(12)*(sizeof(float)*8)];
        elementData = new unsigned int[6*6*(12)]; //6 indices per face

        //fTriQuad(b0, b1, b2, b3, memoryData,  memoryDataBack, elementData, j, indices);

        SDFVec3 bt = b4-b0;
        SDFVec3 ht = b1-b0;
        SDFVec3 vt = b3-b0;
        ht *= (CuboidThickness/2);
        bt*=CuboidThickness/2;
        vt *= CuboidThickness/2;

        AddRectoid(b0+ht,b1-ht);
        AddRectoid(b0-vt,b3+vt);

        AddRectoid(b0+bt,b4-bt); //bt

        AddRectoid(b2+vt,b1-vt);
        AddRectoid(b2-ht,b3+ht);

        AddRectoid(b2+bt,b6-bt); //bt

        AddRectoid(b6+vt,b5-vt);
        AddRectoid(b6-ht,b7+ht);
        AddRectoid(b4+ht,b5-ht);


        AddRectoid(b4-vt,b7+vt);
        AddRectoid(b1+bt,b5-bt); //bt
        AddRectoid(b3+bt,b7-bt); //bt
    }

    void Draw(Camera& camera)
    {
        glBindVertexArray(vertexArray);
        setMat4(program, "projection", camera.projection);
        setMat4(program, "view", camera.view);
        setFloat(program, "time", glfwGetTime());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
        program.UseProgram();
        glDrawElements(GL_TRIANGLES, indices+1, GL_UNSIGNED_INT, 0);

        for(int i = 0; i < drawingVectors.size(); i++)
        {
            drawingVectors[i].Draw(camera);
        }
    }

    void SetUpBuffers()
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

    void CheckForClick(GLFWwindow* window, Camera& camera)
    {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos,&ypos);
        glm::mat4 viewproji = glm::inverse(camera.projection*camera.view);
        
        
        




    }

    ~InputBoxUpdate()
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