#include <iostream>
#include "SDFMeshTree.h"
#include "SDFIterativeTree.h"
#include "NILMesh.h"
#include <random>
#include <SDFSpell.h>
#include <SDFOctree.h>

#define WS "X:\\1.4 C++\\Vscode\\Tree Node\\"

double ranF(double min, double max)
{
    float ran = ((float) rand()) / (float)RAND_MAX;
    float diff = max - min;
    float r = ran * diff;
    return min + r;
}

SDFFace GenerateRandomFaceInBoundingVolume(const SDFBoundingVolume boundingVolume)
{
    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> disX(boundingVolume.TopLeftFront.x, boundingVolume.BottomRightBack.x);
    std::uniform_real_distribution<float> disY(boundingVolume.BottomRightBack.y, boundingVolume.TopLeftFront.y);
    std::uniform_real_distribution<float> disZ(boundingVolume.TopLeftFront.z, boundingVolume.BottomRightBack.z);

    return {SDFVec3({disX(gen), disY(gen), disZ(gen)}), SDFVec3({disX(gen), disY(gen), disZ(gen)}), SDFVec3({disX(gen), disY(gen), disZ(gen)}), SDFVec3({disX(gen), disY(gen), disZ(gen)})};
}


struct Object
{
    SDFBoundingVolume boundingVolume;
    int currentIndex = 0;
    SDFOctree<Object>* tree;
};


int main()
{
    BeginTexContext();

    //SDFMesh ModelMesh;
    SDFBoundingVolume ModelVolume = {{-1.0f, 1.0f, -1.0f}, {1.0f, -1.0f, 1.0f}};

    SpellBoundingVolume(ModelVolume);

    std::vector<Object> FacesToInsert;

    for(int i = 0; i < 1; i++)
    {
        const SDFFace face = GenerateRandomFaceInBoundingVolume(ModelVolume);
        const SDFBoundingVolume v = GetVolumeOfFace(face);
        FacesToInsert.push_back({v});
    }

    SDFOctree<Object> octree(ModelVolume);
    DrawBoundingVolume(ModelVolume);
    for(int i = 0; i < FacesToInsert.size(); i++)
    {
        octree.insertBoundingVolume(&FacesToInsert[0]);
    }

    
    


    EndTexContent(); 
}