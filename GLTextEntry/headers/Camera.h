#ifndef CAMERA_H
#define CAMERA_H

#include "LearnOpenglHelper.h"

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

struct Camera
{
    glm::mat4 projection;
    glm::mat4 view;
    glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
    glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
    float cameraSpeed = 0.5f;
    float lastX = 320, lastY = 240;
    float yaw = -90, pitch = 0;
    float fov = 45;
    bool firstMouse = true;
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    double curPosx = 0.0f;
    double curPosy = 0.0f;
    float currentFrame = 0.0f;
    float lastFrame = 0.0;
    float deltaTime = 0.0;

    Camera()
    {

    }

    void proccessInput(GLFWwindow* window)
    {
        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame; 
        cameraSpeed = 2.0f * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            cameraPos += cameraSpeed * cameraFront;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            cameraPos -= cameraSpeed * cameraFront;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

        glfwGetCursorPos(window, &curPosx, &curPosy);

        projection = glm::perspective(glm::radians(fov), GlobalWindowStats.vx / GlobalWindowStats.vy, 0.1f, 100.0f);
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    }

    void MakeActiveCamera(GLFWwindow* window)
    {
        glfwSetWindowUserPointer(window, this);
        glfwSetCursorPosCallback(window, mouse_callback);
    }

    glm::vec2 ScreenToWorld(float xpos, float ypos)
    {
        float ndcX = (2.0f * xpos) / GlobalWindowStats.vx - 1.0f;
        float ndcY = 1.0f - (2.0f * ypos) / GlobalWindowStats.vy;
        glm::vec4 rayClip = glm::vec4(ndcX, ndcY, -1.0f, 1.0f);
        glm::mat4 iV = glm::inverse(view);
        glm::mat4 invProjection = glm::inverse(projection);
        glm::vec4 rayEye = invProjection * rayClip;
        rayEye = glm::vec4(rayEye.x, rayEye.y, -1.0f, 0.0f); // Z points forward
        glm::mat4 invView = glm::inverse(view);
        glm::vec4 rayWorld = invView * rayEye;
    }

    ~Camera()
    {

    }

};

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{

    Camera* activeCamera = (Camera*)glfwGetWindowUserPointer(window);

    if (activeCamera->firstMouse)
    {
        activeCamera->lastX = xpos;
        activeCamera->lastY = ypos;
        activeCamera->firstMouse = false;
    }

    float xoffset = xpos - activeCamera->lastX;
    float yoffset = activeCamera->lastY - ypos; 
    activeCamera->lastX = xpos;
    activeCamera->lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    activeCamera->yaw   += xoffset;
    activeCamera->pitch += yoffset;

    if(activeCamera->pitch > 89.0f)
        activeCamera->pitch = 89.0f;
    if(activeCamera->pitch < -89.0f)
        activeCamera->pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(activeCamera->yaw)) * cos(glm::radians(activeCamera->pitch));
    direction.y = sin(glm::radians(activeCamera->pitch));
    direction.z = sin(glm::radians(activeCamera->yaw)) * cos(glm::radians(activeCamera->pitch));
    activeCamera->cameraFront = glm::normalize(direction);
}





#endif