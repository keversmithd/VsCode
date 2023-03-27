#ifndef GEOM_ALG_COMMAND_H
#define GEOM_ALG_COMMAND_H

#include "NGL.h"
#include <string>
#include <vector>
#include <chrono>
#include <glm/glm.hpp>
#include <string>

struct Material
{
    std::string id;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

struct SceneCamera
{
    std::string id;
    glm::vec3 viewDir;
    glm::vec3 camPos;
    glm::vec3 up;
    float fov;
    float zoom;
};

struct SceneLight
{
    std::string id;
    glm::vec3 lightPos;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

struct SceneObject
{
    std::string id;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texcoord;
    std::vector<glm::vec3> colors;
    std::vector<unsigned int> indexes;
    Material material;
    const char* texture;

    
};

struct StaticScene
{
    std::vector<SceneObject> Objects;
    std::vector<SceneLight> Lights;
    std::vector<SceneCamera> Cameras;

    StaticScene(const StaticScene& Scene)
    {
        Objects = Scene.Objects;
        Lights = Scene.Lights;
        Cameras = Scene.Cameras;
    }
    StaticScene()
    {

    }
};

struct SceneVector
{
    SceneVector(){}
    int currentScene = 0;
    std::vector<StaticScene> Scenes;
    int NextScene(){
        if(currentScene + 1 > Scenes.size())
        {
            return;
        }
        currentScene++;
    }
    int PreviousScene()
    {
        if(currentScene - 1 < 0)
        {
            return;
        }
        currentScene--;
    }
    ~SceneVector(){}
};


SceneVector SceneCenter;

//Dynamic Scene : Implement
//Interactive Functional Scene, Graphics Injection
//Animatable Events
//Persistent Scene Animations.

#endif