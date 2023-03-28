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
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

struct SceneCamera
{
    glm::vec3 viewDir;
    glm::vec3 camPos;
    glm::vec3 up;
    float fov;
    float zoom;
};

struct SceneLight
{
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


    SceneObject() :  id("0"), vertices(), normals(), texcoord(), colors(), indexes(), material()
    {

    }

    int AddVertex(){} //updates size,
    int AddNormal(){} //updates size,

    int SizeOfVertexData()
    {
        return (vertices.size() * (sizeof(float) * 3)) + (normals.size() * (sizeof(float) * 3)) + (texcoord.size() * (sizeof(float) * 2)) + (colors.size() * (sizeof(float) * 3));
    }
    
};

struct StaticScene
{
    int SceneVertexBufferSize;

    std::vector<SceneObject> Objects;
    std::vector<SceneLight> Lights;
    std::vector<SceneCamera> Cameras;

    StaticScene(){}

    void PushObject(const SceneObject& Object)
    {
        Objects.push_back(Object);
        
    }

    StaticScene(const StaticScene& Scene) : SceneVertexBufferSize(0)
    {
        Objects = Scene.Objects;
        Lights = Scene.Lights;
        Cameras = Scene.Cameras;
    }
    
};

struct SceneVector
{
    SceneVector() :  endOfScenes(0), currentScene(0)
    {

    }
    std::vector<StaticScene> Scenes;
    int endOfScenes;
    int CreateNewScene()
    {
        Scenes.push_back(StaticScene());
        return ++endOfScenes;
    }
    int currentScene = 0;
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

    StaticScene* operator[](int index)
    {
        if(index < 0 || index > Scenes.size())
        {
            throw("Index out of range.");
            return nullptr;
        }
        return Scenes.data()+index;
    }
    ~SceneVector(){}
};


SceneVector SceneCenter;

//Dynamic Scene : Implement
//Interactive Functional Scene, Graphics Injection
//Animatable Events
//Persistent Scene Animations.

#endif