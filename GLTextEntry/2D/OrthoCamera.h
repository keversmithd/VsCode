#ifndef ORTHO_CAMERA_H
#define ORTHO_CAMERA_H
#include <Camera.h>

void ortho_scroll_callback(GLFWwindow* window, double xpos, double ypos);

struct OrthoCamera : Camera
{
    glm::mat4 projection;
    glm::mat4 view;
    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
    float cameraZoom = 1.0f;

    float cameraSpeed = 0.5f;
    float lastX = 320, lastY = 240;
    bool firstMouse = true;

    double curPosx = 0.0f;
    double curPosy = 0.0f;
    float currentFrame = 0.0f;
    float lastFrame = 0.0;
    float deltaTime = 0.0;

    bool dragging;

    OrthoCamera() : dragging(false)
    {
        lastX = 0.5;
        lastY = 0.5;
    }

    void proccessInput(GLFWwindow* window)
    {

        // if(glfwGetMouseButton(GLFW_MOUSE_BUTTON_LEFT, GLFW_KEY_DOWN))
        // {
        //     glfwGetCursorPos(window, &curPosx,&curPosy);
        //     curPosx = 2.0*(curPosx/GlobalWindowStats.vx)-1.0;
        //     curPosy = 2.0*(curPosx/GlobalWindowStats.vy)-1.0;

        //     cameraPos += glm::vec3(curPosx, curPosy,0)-glm::vec3(lastX,lastY,0);


        //     dragging = true;
        // }else
        // {
        //     dragging = false;
        // }

        

        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame; 
        cameraSpeed = 2.0f * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            cameraPos += glm::vec3(0,1,0)*cameraSpeed;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            cameraPos -= glm::vec3(0,1,0)*cameraSpeed;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            cameraPos -= glm::vec3(1,0,0)*cameraSpeed;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            cameraPos += glm::vec3(1,0,0)*cameraSpeed;


        
        glfwGetCursorPos(window, &curPosx, &curPosy);

        

        float left = 0.0f;
        float right = 1.0f;
        float top = 1.0f;
        float bottom = 0.0f;

        float ar = ((right-left)*GlobalWindowStats.vx)/((top-bottom)*GlobalWindowStats.vy);

        projection[0][0] = 1.0f;
        projection[0][1] = 0.0f;
        projection[0][2] = 0.0f;
        projection[0][3] = 0.0f;

        projection[1][0] = 0.0f;
        projection[1][1] = ar;
        projection[1][2] = 0.0f;
        projection[1][3] = 0.0f;

        projection[2][0] = 0.0f;
        projection[2][1] = 0.0f;
        projection[2][2] = 1.0f;
        projection[2][3] = 0.0f;

        // left+(right-left)/2
        // bottom+(top-bottom)/2
        projection[3][0] = 0.0;
        projection[3][1] = 0.0;
        projection[3][2] = 0.0f;
        projection[3][3] = 1.0f;


        view[0][0] = cameraZoom;
        view[0][1] = 0.0f;
        view[0][2] = 0.0f;
        view[0][3] = 0.0f;

        view[1][0] = 0.0f;
        view[1][1] = cameraZoom;
        view[1][2] = 0.0f;
        view[1][3] = 0.0f;

        view[2][0] = 0.0f;
        view[2][1] = 0.0f;
        view[2][2] = -cameraZoom;
        view[2][3] = 0.0f;

        view[3][0] = -cameraPos.x;
        view[3][1] = -cameraPos.y;
        view[3][2] = cameraPos.z;
        view[3][3] = 1.0f;

        
    }

    void MakeActiveCamera(GLFWwindow* window)
    {
        glfwSetWindowUserPointer(window, this);
        //glfwSetCursorPosCallback(window, ortho_mouse_callback);
        glfwSetScrollCallback(window, ortho_scroll_callback);
    }

    glm::vec2 ScreenToWorld(float xpos, float ypos)
    {
        // float ndcX = (2.0f * xpos) / GlobalWindowStats.vx - 1.0f;
        // float ndcY = 1.0f - (2.0f * ypos) / GlobalWindowStats.vy;
        // glm::vec4 rayClip = glm::vec4(ndcX, ndcY, -1.0f, 1.0f);
        // glm::mat4 iV = glm::inverse(view);
        // glm::mat4 invProjection = glm::inverse(projection);
        // glm::vec4 rayEye = invProjection * rayClip;
        // rayEye = glm::vec4(rayEye.x, rayEye.y, -1.0f, 0.0f); // Z points forward
        // glm::mat4 invView = glm::inverse(view);
        // glm::vec4 rayWorld = invView * rayEye;
    }

    ~OrthoCamera()
    {

    }


};

void ortho_scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    OrthoCamera* C = (OrthoCamera*)glfwGetWindowUserPointer(window);

    C->cameraZoom += (yoffset/abs(yoffset)) * 0.1;
}



#endif