#ifndef GRAPHIC_VECTOR_H
#define GRAPHIC_VECTOR_H

#include "LearnOpenglHelper.h"
#include "FGeom.h"
#include "Camera.h"

struct GraphicVector
{
    SDFVec3 m_Start;
    SDFVec3 m_End;
    float* memoryData;
    unsigned int* elementData;

    unsigned int vertexBuffer, vertexArray;
    unsigned int elementBuffer;
    NGLProgram program;
    int memoryDataBack;
    int elementDataBack;
    int vertices; 
    int indices;

    GraphicVector(SDFVec3 Start, SDFVec3 End) : memoryDataBack(0), vertices(0), indices(0), elementDataBack(0), memoryData(nullptr), elementData(nullptr), program(CreateShader("/shaders/GraphicVector.vs", "/shaders/GraphicVector.fs"))
    {
        
        m_Start = Start;
        m_End = End;
        ConstructSquaredAxis();
        SetUpBuffers();
    }

    GraphicVector(const GraphicVector& vector) : memoryDataBack(vector.memoryDataBack), vertices(vector.vertices), indices(vector.indices), elementDataBack(vector.elementDataBack), memoryData(vector.memoryData), elementData(vector.elementData), program(vector.program)
    {
        vertexArray = vector.vertexArray;
    }
    void ConstructSquaredAxis()
    {
        float arrowHeight = 0.05;
        float arrowThickness = 0.05;

        float shaftLength = 0.05;
        float tipLength = 0.5;
        float tipRadius = 0.00;
        float baseRadius = 0.4;
        float shaftRadius = 0.05;

        float SubdivisionFaces = 6;
        float HorizontalDivisions = 1;

        memoryData = new float[20*6*20];

        float borderRadius = 0.2;

        SDFVec3 axis = Subtract(m_End, m_Start);
        SDFVec3 axisnorm = Cross(axis, {1,1,1}); 
        SDFVec3 axisnnorm = Cross(axisnorm, axis);

        int numberOfFaces = (SubdivisionFaces*(HorizontalDivisions+2));
        float axisLength = Mag(axis);
        float axisdx = axisLength/HorizontalDivisions;
        float dr = (2*3.14159265359)/SubdivisionFaces;

        
        SDFVec3 tip_loc = m_End;
        m_End = m_End - (Normalize(axis)*tipLength);
        axis.normalize();
        SDFVec3 p_left = m_Start, p_right = m_End;

        

        SDFVec3 c1,c2,c3,c4, c5;

        for(int i = 0; i < HorizontalDivisions; i++)
        {
            for(float j = 0; j < SubdivisionFaces; j++)
            {
                
                c1 = p_left;
                c2 = {(cos(j*dr)*axisnorm.x) + (sin(j*dr)*axisnnorm.x), (cos(j*dr)*axisnorm.y) + (sin(j*dr)*axisnnorm.y), (cos(j*dr)*axisnorm.z) + (sin(j*dr)*axisnnorm.z)};
                c1 = Add(c1, Multiply(Normalize(c2), borderRadius));

                c2 = p_right;
                c3 = {(cos(j*dr)*axisnorm.x) + (sin(j*dr)*axisnnorm.x), (cos(j*dr)*axisnorm.y) + (sin(j*dr)*axisnnorm.y), (cos(j*dr)*axisnorm.z) + (sin(j*dr)*axisnnorm.z)};
                
                c2 = Add(c2, Multiply(Normalize(c3), borderRadius));
                
                c3 = p_right;
                c4 = {(cos((j+1)*dr)*axisnorm.x) + (sin((j+1)*dr)*axisnnorm.x), (cos((j+1)*dr)*axisnorm.y) + (sin((j+1)*dr)*axisnnorm.y), (cos((j+1)*dr)*axisnorm.z) + (sin((j+1)*dr)*axisnnorm.z)};
                c3 = Add(c3, Multiply(Normalize(c4), borderRadius));

                c4 = p_left;
                c5 = {(cos((j+1)*dr)*axisnorm.x) + (sin((j+1)*dr)*axisnnorm.x), (cos((j+1)*dr)*axisnorm.y) + (sin((j+1)*dr)*axisnnorm.y), (cos((j+1)*dr)*axisnorm.z) + (sin((j+1)*dr)*axisnnorm.z)};
                c4 = Add(p_left, Multiply(Normalize(c5), borderRadius));

                vertices += 6;

                fTriQuad(c1, c2, c3, c4, memoryData, memoryDataBack);

                if(i == 0)
                {
                    c1 = m_End;
                    c2 = {(borderRadius*cos(j*dr)*axisnorm.x) + (borderRadius*sin(j*dr)*axisnnorm.x), (borderRadius*cos(j*dr)*axisnorm.y) + (borderRadius*sin(j*dr)*axisnnorm.y), (borderRadius*cos(j*dr)*axisnorm.z) + (borderRadius*sin(j*dr)*axisnnorm.z)};
                    c1 = Add(c1, Multiply(Normalize(c2), borderRadius));
                    c3 = {(baseRadius*cos(j*dr)*axisnorm.x) + (baseRadius*sin(j*dr)*axisnnorm.x), (baseRadius*cos(j*dr)*axisnorm.y) + (baseRadius*sin(j*dr)*axisnnorm.y), (baseRadius*cos(j*dr)*axisnorm.z) + (baseRadius*sin(j*dr)*axisnnorm.z)};
                    c2 = m_End;
                    c2 = Add(c2, Multiply(Normalize(c3), baseRadius));
                    c4 = {(baseRadius*cos((j+1)*dr)*axisnorm.x) + (baseRadius*sin((j+1)*dr)*axisnnorm.x), (baseRadius*cos((j+1)*dr)*axisnorm.y) + (baseRadius*sin((j+1)*dr)*axisnnorm.y), (baseRadius*cos((j+1)*dr)*axisnorm.z) + (baseRadius*sin((j+1)*dr)*axisnnorm.z)};
                    c3 = m_End;
                    c3 = Add(c3, Multiply(Normalize(c4), baseRadius));
                    c4 = m_End;
                    c5 = {(borderRadius*cos((j+1)*dr)*axisnorm.x) + (borderRadius*sin((j+1)*dr)*axisnnorm.x), (borderRadius*cos((j+1)*dr)*axisnorm.y) + (borderRadius*sin((j+1)*dr)*axisnnorm.y), (borderRadius*cos((j+1)*dr)*axisnorm.z) + (borderRadius*sin((j+1)*dr)*axisnnorm.z)};                  
                    c4 = Add(c4, Multiply(Normalize(c5), borderRadius));

                    vertices += 6;

                    fTriQuad(c1, c2, c3, c4, memoryData, memoryDataBack);

                    c1 = m_End;
                    c2 = {(baseRadius*cos(j*dr)*axisnorm.x) + (baseRadius*sin(j*dr)*axisnnorm.x), (baseRadius*cos(j*dr)*axisnorm.y) + (baseRadius*sin(j*dr)*axisnnorm.y), (baseRadius*cos(j*dr)*axisnorm.z) + (baseRadius*sin(j*dr)*axisnnorm.z)};
                    c1 = Add(c1, Multiply(Normalize(c2), baseRadius));
                    c3 = {(tipRadius*cos(j*dr)*axisnorm.x) + (tipRadius*sin(j*dr)*axisnnorm.x), (tipRadius*cos(j*dr)*axisnorm.y) + (tipRadius*sin(j*dr)*axisnnorm.y), (tipRadius*cos(j*dr)*axisnorm.z) + (tipRadius*sin(j*dr)*axisnnorm.z)};
                    c2 = tip_loc;
                    c2 = Add(c2, Multiply(Normalize(c3), tipRadius));
                    c4 = {(tipRadius*cos((j+1)*dr)*axisnorm.x) + (tipRadius*sin((j+1)*dr)*axisnnorm.x), (tipRadius*cos((j+1)*dr)*axisnorm.y) + (tipRadius*sin((j+1)*dr)*axisnnorm.y), (tipRadius*cos((j+1)*dr)*axisnorm.z) + (tipRadius*sin((j+1)*dr)*axisnnorm.z)};
                    c3 = tip_loc;
                    c3 = Add(c3, Multiply(Normalize(c4), tipRadius));
                    c4 = m_End;
                    c5 = {(baseRadius*cos((j+1)*dr)*axisnorm.x) + (baseRadius*sin((j+1)*dr)*axisnnorm.x), (baseRadius*cos((j+1)*dr)*axisnorm.y) + (baseRadius*sin((j+1)*dr)*axisnnorm.y), (baseRadius*cos((j+1)*dr)*axisnorm.z) + (baseRadius*sin((j+1)*dr)*axisnnorm.z)};                  
                    c4 = Add(c4, Multiply(Normalize(c5), baseRadius));


                    vertices += 6;

                    fTriQuad(c1, c2, c3, c4, memoryData, memoryDataBack);
                }

            }
        }
    }

    void ConstructSquaredAxisElement()
    {
        float arrowHeight = 0.05;
        float arrowThickness = 0.05;

        float shaftLength = 0.05;
        float tipLength = 0.5;
        float tipRadius = 0.00;
        float baseRadius = 0.4;
        float shaftRadius = 0.05;
        float lipLength = 0.1;

        float SubdivisionFaces = 5;
        float HorizontalDivisions = 1;

        memoryData = new float[20*6*20];
        elementData = new unsigned int[20*6*20];

        float borderRadius = 0.2;

        SDFVec3 axis = Normalize(Subtract(m_End, m_Start));
        SDFVec3 axisnorm = Cross(axis, {1,0,0}); 
        SDFVec3 axisnnorm = Cross(axisnorm, axis);

        int numberOfFaces = (SubdivisionFaces*(HorizontalDivisions+2));


        float axisLength = Mag(axis);
        float axisdx = axisLength/HorizontalDivisions;
        float dr = (2*3.14159265359)/SubdivisionFaces;

        SDFVec3 p_left = m_Start, p_right = m_End;
        SDFVec3 m_lip = Add(m_End, Multiply(axis, lipLength));


        SDFVec3 tip_loc = Add(m_lip, Multiply(axis, tipLength-lipLength));

        SDFVec3 c1,c2,c3,c4, c5;

        for(int i = 0; i < HorizontalDivisions; i++)
        {
            for(float j = 0; j < SubdivisionFaces; j++)
            {
                
                // vertices += 6;
                // fCircQuad(m_Start, m_End, borderRadius, borderRadius, axisnorm, axisnnorm, j, dr, memoryData, memoryDataBack, elementData, elementDataBack, indices);
                vertices += 6;
                fCircQuad(m_Start, m_End, borderRadius, borderRadius, axisnorm, axisnnorm, j, dr, memoryData, memoryDataBack, elementData, elementDataBack, indices);
                
                if(i == 0)
                {
                    // vertices += 6;
                    // fCircQuad(m_End, m_End, borderRadius, baseRadius, axisnorm, axisnnorm, j, dr, memoryData, memoryDataBack, elementData, elementDataBack, indices);
                    vertices += 6;
                    fCircQuad(m_End, m_End, borderRadius, baseRadius, axisnorm, axisnnorm, j, dr, memoryData, memoryDataBack, elementData, elementDataBack, indices);
                    

                }

                
            }
        }
    }

    void ConstructSquaredAxisElementAppended()
    {
        float arrowHeight = 0.05;
        float arrowThickness = 0.05;

        float shaftLength = 0.05;
        float tipLength = 0.5;
        float tipRadius = 0.00;
        float baseRadius = 0.4;
        float shaftRadius = 0.05;

        float SubdivisionFaces = 10;
        float HorizontalDivisions = 1;

        memoryData = new float[20*6*20];
        elementData = new unsigned int[20*6*20];

        float borderRadius = 0.2;

        SDFVec3 axis = Normalize(Subtract(m_End, m_Start));
        SDFVec3 axisnorm = Cross(axis, {1,0,0}); 
        SDFVec3 axisnnorm = Cross(axisnorm, axis);

        int numberOfFaces = (SubdivisionFaces*(HorizontalDivisions+2));

        float axisLength = Mag(axis);
        SDFVec3 axisdx = axis * (axisLength/HorizontalDivisions);

        float dr = (2*3.14159265359)/SubdivisionFaces;

        SDFVec3 tip_loc = Add(m_End, Multiply(axis, tipLength));

        SDFVec3 c1,c2,c3,c4,c5;

        int CurrentIndice = 0;

        //Use the trajectory axis rotation by margin zero to start sequence.
        SDFVec3 Rotator, Origin;
        Origin = m_Start;
        

        int OriginIndice = -1;
        
        for(int i = 0; i <= HorizontalDivisions+1; i++)
        {
            if(i < HorizontalDivisions+1)
            {
                Origin += axisdx;
            }
            

            if(i == 0 || i == HorizontalDivisions+1)
            {
                fPoint(Origin, 0,0, memoryData, memoryDataBack);
                OriginIndice = CurrentIndice;
            }

            for(int j = 0; j < SubdivisionFaces; j++)
            {
                Rotator.rotateFrame(axisnorm, axisnnorm, (j+(j>0))*dr);
                Rotator *= borderRadius;

                if(i == 0 || i == HorizontalDivisions+1)
                {
                    
                    c1 = Origin;
                    c1 += Rotator;
                    
                    
                    fPoint(c1, 1,0, memoryData, memoryDataBack); //origin already in

                    if(j == 0)
                    {
                        c2 = Origin;
                        Rotator.rotateFrame(axisnorm, axisnnorm, (j+1)*dr);
                        Rotator *= borderRadius;
                        c2 += Rotator;

                        fPoint(c2, 1,1, memoryData, memoryDataBack);
                        elementData[indices++] = CurrentIndice++;
                        elementData[indices++] = CurrentIndice++;
                        elementData[indices++] = CurrentIndice++;


                    }else{
                        
                        elementData[indices++] = OriginIndice;
                        elementData[indices++] = CurrentIndice-1;
                        elementData[indices++] = CurrentIndice++;   
                    }
                }else
                {   

                    c1 = Origin;
                    c1 += Rotator;
                    c2 = Origin;

                    fPoint(c1, 1,0, memoryData, memoryDataBack);

                    if(j == 0)
                    {
                        Rotator.rotateFrame(axisnorm, axisnnorm, (j+1)*dr);
                        Rotator *= borderRadius;
                        c2 += Rotator;
                        fPoint(c2, 1,1, memoryData, memoryDataBack);



                        elementData[indices++] = (CurrentIndice)-(SubdivisionFaces+1);
                        elementData[indices++] = CurrentIndice++;
                        elementData[indices++] = CurrentIndice;

                        elementData[indices++] = (CurrentIndice-1)-(SubdivisionFaces+1);
                        elementData[indices++] = CurrentIndice;
                        elementData[indices++] = (CurrentIndice)-(SubdivisionFaces+1);
                        CurrentIndice++;
                    }else{

                        elementData[indices++] = (CurrentIndice-1)-(SubdivisionFaces+1);
                        elementData[indices++] = CurrentIndice-1;
                        elementData[indices++] = CurrentIndice;

                        
                        elementData[indices++] = (CurrentIndice-1)-(SubdivisionFaces+1);
                        elementData[indices++] = CurrentIndice;

                        elementData[indices++] = (CurrentIndice)-(SubdivisionFaces+1);
                        CurrentIndice++;
                    }

                }

            }
        }
    }

    void Draw(Camera& camera)
    {
        glBindVertexArray(vertexArray);
        setMat4(program, "projection", camera.projection);
        setMat4(program, "view", camera.view);
        setFloat(program, "time", glfwGetTime());
        program.UseProgram();
        glDrawArrays(GL_TRIANGLES, 0, vertices);
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

    void SetUpBuffers()
    {
        glGenVertexArrays(1, &vertexArray);
        glBindVertexArray(vertexArray);

        unsigned int vertexBuffer;
        glGenBuffers(1, &vertexBuffer);

        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, memoryDataBack*sizeof(float), memoryData, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (GLvoid*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float)*8, (GLvoid*)(sizeof(float) * 3));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float)*8, (GLvoid*)(sizeof(float) * 5));

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

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

    ~GraphicVector()
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





#endif