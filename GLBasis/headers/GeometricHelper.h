#ifndef GEOM_HELPER
#define GEOM_HELPER
#include "GeometricAlgorithmCommand.h"
#include "NGL.h"




void LoadCurrentScene(SceneVector& Scenes, NGLBuffer& StaticVertexBuffer, NGLBuffer& StaticNormalBuffer, NGLBuffer& StaticTexcoordBuffer, NGLBuffer& StaticColorBuffer, NGLVertexArray& Attributes)
{
    
    int VertexBufferSize = 0;
    StaticVertexBuffer.BindBuffer(GL_ARRAY_BUFFER);
    StaticVertexBuffer.GetBufferParameteriv(GL_BUFFER_SIZE, &VertexBufferSize);
    
    const StaticScene* currentScene = &Scenes[Scenes.currentScene];
    
    //Optimization, accumulate all object data in the same pool to begin with. Could use chronological pool.
    std::vector<SDFOVec4> sceneObjectvertex;
    for(int i = 0; i < currentScene->Objects.size(); i++)
    {
        //sceneObjectvertex.insert(sceneObjectvertex.end(), currentScene->Objects[i].vertices.begin(), currentScene->Objects[i].vertices.end());
        sceneObjectvertex.insert(sceneObjectvertex.end(), currentScene->Objects[i].vertices.begin(), currentScene->Objects[i].vertices.end());
    }
    
    std::vector<SDFVec3> sceneObjectnormal;
    for(int i = 0; i < currentScene->Objects.size(); i++)
    {
        sceneObjectnormal.insert(sceneObjectnormal.end(), currentScene->Objects[i].normals.begin(), currentScene->Objects[i].normals.end());
    }

    std::vector<SDFVec2> sceneObjecttexcoord;
    for(int i = 0; i < currentScene->Objects.size(); i++)
    {
        sceneObjecttexcoord.insert(sceneObjecttexcoord.end(), currentScene->Objects[i].texcoords.begin(), currentScene->Objects[i].texcoords.end());
    }

    std::vector<SDFVec3> sceneObjectcolor;
    for(int i = 0; i < currentScene->Objects.size(); i++)
    {
        sceneObjectcolor.insert(sceneObjectcolor.end(), currentScene->Objects[i].colors.begin(), currentScene->Objects[i].colors.end());
    }

    Attributes.BindVertexArray();

    StaticVertexBuffer.BindBuffer(GL_ARRAY_BUFFER);
    StaticVertexBuffer.BufferData(sizeof(SDFOVec4)*sceneObjectvertex.size(), sceneObjectvertex.data(), GL_STATIC_DRAW);
    Attributes.VertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    StaticVertexBuffer.Unbind(GL_ARRAY_BUFFER);

    StaticNormalBuffer.BindBuffer(GL_ARRAY_BUFFER);
    StaticNormalBuffer.BufferData(sizeof(SDFVec3)*sceneObjectnormal.size(), sceneObjectnormal.data(), GL_STATIC_DRAW);
    Attributes.VertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    StaticNormalBuffer.Unbind(GL_ARRAY_BUFFER);

    StaticTexcoordBuffer.BindBuffer(GL_ARRAY_BUFFER);
    StaticTexcoordBuffer.BufferData(sizeof(SDFVec2)*sceneObjecttexcoord.size(), sceneObjecttexcoord.data(), GL_STATIC_DRAW);
    Attributes.VertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    StaticTexcoordBuffer.Unbind(GL_ARRAY_BUFFER);

    StaticColorBuffer.BindBuffer(GL_ARRAY_BUFFER);
    StaticColorBuffer.BufferData(sizeof(SDFVec3)*sceneObjectcolor.size(), sceneObjectcolor.data(), GL_STATIC_DRAW);
    Attributes.VertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    StaticColorBuffer.Unbind(GL_ARRAY_BUFFER);

}


#endif