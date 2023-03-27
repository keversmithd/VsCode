#include <iostream>
#include "SDFMeshTree.h"
#include "NILMesh.h"
#include <random>
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

int main()
{
    
    //SDFMesh ModelMesh;
    SDFBoundingVolume ModelVolume = {{-1.0f, 1.0f, -1.0f}, {1.0f, -1.0f, 1.0f}};
    SDFFace InitalFace = GenerateRandomFaceInBoundingVolume(ModelVolume);
    //SDFComposedMesh(WS "OctreeTesting.obj", ModelMesh, ModelVolume);
    
    //std::cout << ModelMesh.faces.size() << std::endl; 
    SDFMeshTree MeshTreeTest(ModelVolume, InitalFace);

    //MeshTreeTest.InsertionOfFaceIntoOctreeAlgorithm1();
    
}