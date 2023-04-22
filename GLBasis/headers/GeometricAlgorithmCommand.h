#ifndef GEOM_ALG_COMMAND_H
#define GEOM_ALG_COMMAND_H

#include <string>
#include <vector>
#include <chrono>
#include <string>
#include "SDFArchive.h"
struct Material
{
    SDFVec3 ambient;
    SDFVec3 diffuse;
    SDFVec3 specular;
};

struct SceneCamera
{
    SDFVec3 viewDir;
    SDFVec3 camPos;
    SDFVec3 up;
    float fov;
    float zoom;
};

struct SceneLight
{
    SDFVec3 lightPos;
    SDFVec3 ambient;
    SDFVec3 diffuse;
    SDFVec3 specular;
};

struct SceneObject
{
    unsigned int id;
    std::string texture;
    std::vector<SDFOVec4> vertices;
    std::vector<SDFVec3> normals;
    std::vector<SDFVec2> texcoords;
    std::vector<SDFVec3> colors;
    Material material;

    int vertexCount;

    SceneObject(int ID) :  id(ID), vertices(), normals(), texcoords(), colors(), material(), texture("no_texture"), vertexCount(0)
    {
        assert(ID > 0);
    }

    void AddCompleteVertex(const SDFVec3 vertex, const SDFVec3 normal, const SDFVec2 texcoord, const SDFVec3 color)
    {
        vertices.push_back({vertex.x, vertex.y, vertex.z, id});
        normals.push_back(normal); 
        texcoords.push_back(texcoord);
        colors.push_back(color);
        vertexCount++;
    }
    void AddVertex(const SDFVec3 vertex)
    {
        vertices.push_back({vertex.x, vertex.y, vertex.z, id});
        vertexCount++;
    }
    void AddNormal(const SDFVec3 normal)
    {
        normals.push_back(normal);   
    }
    void AddTexcoord(const SDFVec2 texcoord)
    {
        texcoords.push_back(texcoord);
    }
    void AddColor(const SDFVec3 color)
    {
        colors.push_back(color);
    }

    void AddMaterial(const Material objectMaterial)
    {
        material = objectMaterial;
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
        Scenes.push_back(StaticScene());
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
            return -1;
        }
        currentScene++;
    }
    int PreviousScene()
    {
        if(currentScene - 1 < 0)
        {
            return -1;
        }
        currentScene--;
    }

    StaticScene& operator[](int index)
    {
        if(index < 0 || index > Scenes.size())
        {
            throw("Index out of range.");
            return Scenes.at(0);
        }
        return Scenes.at(index);
    }
    ~SceneVector(){}
};



SceneVector SceneCenter;

//Dynamic Scene : Implement
//Interactive Functional Scene, Graphics Injection
//Animatable Events
//Persistent Scene Animations.

#endif