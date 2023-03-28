#ifndef GEOM_HELPER
#define GEOM_HELPER
#include "GeometricAlgorithmCommand.h"

int MaximumSceneBufferSize(const SceneVector& Scenes)
{
    unsigned int totalBytes = 0;
    unsigned int maxBytes = 0;

    for(int i = 0; i < Scenes.Scenes.size(); i++)
    {
        totalBytes = 0;

        for(int j = 0; j < Scenes.Scenes[i].Objects.size(); j++)
        {
            totalBytes += Scenes.Scenes[i].Objects[j].colors.size() * sizeof(float)* 3;
            totalBytes += Scenes.Scenes[i].Objects[j].normals.size() * sizeof(float)* 3;
            totalBytes += sizeof(Scenes.Scenes[i].Objects[j].material);
            totalBytes += Scenes.Scenes[i].Objects[j].vertices.size() * sizeof(float)* 3;
            totalBytes += Scenes.Scenes[i].Objects[j].texcoord.size() * sizeof(float)* 2;
        }   

        maxBytes = (totalBytes > maxBytes) ? totalBytes : maxBytes;
    }

    return maxBytes;
}

int BytesInScene(const StaticScene& Scene)
{
    
}

void LoadCurrentScene(const SceneVector& Scenes, NGLBuffer& StaticSceneBuffer, int minimumSceneSize)
{
    const int CurrentSceneIndex = Scenes.currentScene;
    const StaticScene& Retrieval = Scenes.Scenes[CurrentSceneIndex];

}


#endif