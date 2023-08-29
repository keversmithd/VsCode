#ifndef INPUT_BOX
#define INPUT_BOX

#include "LearnOpenglHelper.h"
#include "FGeom.h"
#include "Camera.h"

#include "GraphicVector.h"

#include "InputContainer.h"

#include <future>
#include <chrono>
#include <queue>
void ClickConversion(void* Object, GLFWwindow* window, Camera* camera, double xpos, double ypos);

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
    float CuboidThickness = 0.05;
    int j = 0;

    std::queue<int> reDraw;

    std::vector<GraphicVector> drawingVectors;

    InputBoxUpdate(SDFBoundingVolume volume) : m_volume(volume), memoryDataBack(0), vertices(0), indices(0), elementDataBack(0), memoryData(nullptr), elementData(nullptr), program(CreateShader("/shaders/GraphicVector.vs", "/shaders/GraphicVector.fs"))
    {
        ConstructBox();
        SetUpBuffers();

        //Experimental Input Pointer
        Input SelfInputPointer;
        SelfInputPointer.ClickConversion = ClickConversion;
        SelfInputPointer.object = this;
        GlobalInputContainer.Inputs.push_back(SelfInputPointer);

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
        
        memoryData = new float[24*(12)*(sizeof(float)*8)];
        elementData = new unsigned int[6*6*(12)]; //6 indices per face

        SDFVec3 bt = b4-b0;
        bt.normalize();
        SDFVec3 ht = b1-b0;
        ht.normalize();
        SDFVec3 vt = b3-b0;
        vt.normalize();

        ht *= CuboidThickness;
        bt *= CuboidThickness;
        vt *= CuboidThickness;

        AddRectoid(b0+ht,b1-ht);
        AddRectoid(b0-vt,b3+vt);

        AddRectoid(b0+bt,b4-bt); //bt

        AddRectoid(b1-vt,b2+vt);
        AddRectoid(b2-ht,b3+ht);

        AddRectoid(b2+bt,b6-bt); //bt

        AddRectoid(b5-vt,b6+vt);
        AddRectoid(b7+ht,b6-ht);
        AddRectoid(b4+ht,b5-ht);


        AddRectoid(b4-vt,b7+vt);
        AddRectoid(b1+bt,b5-bt); //bt
        AddRectoid(b3+bt,b7-bt); //bt

        
    }
    void ReconstructBox()
    {
        std::lock_guard<std::mutex> lock(dataMutex);
        memoryDataBack = 0; vertices = 0; indices = 0; elementDataBack = 0; j = 0;

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
        
        SDFVec3 bt = b4-b0;
        bt.normalize();
        SDFVec3 ht = b1-b0;
        ht.normalize();
        SDFVec3 vt = b3-b0;
        vt.normalize();

        ht *= CuboidThickness;
        bt *= CuboidThickness;
        vt *= CuboidThickness;


        AddRectoid(b0+ht,b1-ht);
        AddRectoid(b0-vt,b3+vt);

        AddRectoid(b0+bt,b4-bt); //bt

        AddRectoid(b1-vt,b2+vt);
        AddRectoid(b2-ht,b3+ht);

        AddRectoid(b2+bt,b6-bt); //bt

        AddRectoid(b5-vt,b6+vt);
        AddRectoid(b7+ht,b6-ht);
        AddRectoid(b4+ht,b5-ht);


        AddRectoid(b4-vt,b7+vt);
        AddRectoid(b1+bt,b5-bt); //bt
        AddRectoid(b3+bt,b7-bt); //bt

        if(reDraw.empty())
        {
            reDraw.push(1);
        }
        
    }


    void Draw(Camera& camera)
    {
        if(!reDraw.empty())
        {
            reDraw.pop();
            UpdateBuffers();
        }

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
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferSubData(GL_ARRAY_BUFFER, 0, (memoryDataBack+1)*sizeof(float), memoryData);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, (indices)*sizeof(unsigned int), elementData);
    }

    void CheckForClick(GLFWwindow* window, Camera* camera, double xpos, double ypos)
    {
        float ndcX = (2.0f * xpos) / GlobalWindowStats.vx - 1.0f;
        float ndcY = 1.0f - (2.0f * ypos) / GlobalWindowStats.vy;

        // Create a ray in view space
        glm::vec4 rayClip = glm::vec4(ndcX, ndcY, -1.0f, 1.0f);
        glm::mat4 invProjection = glm::inverse(camera->projection);
        glm::vec4 rayEye = invProjection * rayClip;
        rayEye = glm::vec4(rayEye.x, rayEye.y, -1.0f, 0.0f); // Z points forward
        glm::mat4 invView = glm::inverse(camera->view);
        glm::vec4 rayWorld = invView * rayEye;
        printf("Ray World: (%f,%f,%f)\n", rayWorld.x, rayWorld.y, rayWorld.z);
        glm::vec3 rayDir = glm::normalize(glm::vec3(rayWorld));

        // Calculate the ray's origin in world space (camera position)
        glm::vec3 rayOrigin = camera->cameraPos;

        // Perform ray-box intersection with the bounding volume
        float tmin = (m_volume.BottomRightBack.x - rayOrigin.x) / rayDir.x;
        float tmax = (m_volume.TopLeftFront.x - rayOrigin.x) / rayDir.x;

        if (tmin > tmax) std::swap(tmin, tmax);

        float tymin = (m_volume.BottomRightBack.y - rayOrigin.y) / rayDir.y;
        float tymax = (m_volume.TopLeftFront.y - rayOrigin.y) / rayDir.y;

        if (tymin > tymax) std::swap(tymin, tymax);

        if ((tmin > tymax) || (tymin > tmax)) return; // No intersection

        if (tymin > tmin) tmin = tymin;
        if (tymax < tmax) tmax = tymax;

        float tzmin = (m_volume.BottomRightBack.z - rayOrigin.z) / rayDir.z;
        float tzmax = (m_volume.TopLeftFront.z - rayOrigin.z) / rayDir.z;

        if (tzmin > tzmax) std::swap(tzmin, tzmax);

        if ((tmin > tzmax) || (tzmin > tmax)) return; // No intersection

        if (tzmin > tmin) tmin = tzmin;
        if (tzmax < tmax) tmax = tzmax;

        // The ray intersects the bounding volume
        printf("Cursor hovering over bounding volume!\n");

        Drag(window, camera);
    }

    void Drag(GLFWwindow* window, Camera* camera)
    {
        // Stop the previous draggingFuture, if it exists
        if (draggingFuture.valid()) {
            draggingFuture.wait();
        }

        // Start a new draggingFuture
        draggingFuture = std::async(std::launch::async, [this, window, camera]() {
            bool wasDragging = false;
            bool isDragging = (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS);
            
            glm::vec<2,double> PreviousMouse(0,0);
            glfwGetCursorPos(window,  &PreviousMouse.x, &PreviousMouse.y);
            glm::vec<2,double> NewMouse(0,0);
            glm::vec<2,double> DeltaMouse(0,0);

            while (isDragging) {
                if (!wasDragging) {
                    wasDragging = true;
                    std::cout << "Dragging started." << std::endl;
                }

                
                glfwGetCursorPos(window,  &NewMouse.x, &NewMouse.y);
                DeltaMouse = glm::normalize(NewMouse-PreviousMouse);
                

                this->m_volume.BottomRightBack -= {(float)DeltaMouse.x/4, (float)DeltaMouse.y/4};
                this->m_volume.TopLeftFront -= {(float)DeltaMouse.x/4, (float)DeltaMouse.y/4};
                ReconstructBox();

                isDragging = (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS);
                std::this_thread::sleep_for(std::chrono::milliseconds(10));

                PreviousMouse = NewMouse;
            }

            if (wasDragging) {
                std::cout << "Dragging ended." << std::endl;
            }
            
            
        });
    }
    

    ~InputBoxUpdate()
    {
        // if(memoryData != nullptr)
        // {
        //     delete[] memoryData;
        //     memoryData = nullptr;
        // }

        // if(elementData != nullptr)
        // {
        //     delete[] elementData;
        //     elementData = nullptr;
        // }
    }

    private:
        std::thread dragThread;
        std::future<void> draggingFuture;
        std::mutex dataMutex;

};


void ClickConversion(void* Object, GLFWwindow* window, Camera* camera, double xpos, double ypos)
{
    InputBoxUpdate* InputBox = static_cast<InputBoxUpdate*>(Object);
    InputBox->CheckForClick(window, camera, xpos, ypos);
}




#endif