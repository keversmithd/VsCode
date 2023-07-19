#ifndef F_GEOM_H
#define F_GEOM_H

#include "SDFArchive.h"


static const float QuadUvs[] =
{
        0.0, 0.0,
        1.0, 0.0,
        1.0, 1.0,
        0.0, 1.0
};

static SDFVec3 NHolder;

void fPoint(const SDFVec3& A, const int quadsIndex, std::vector<float>& memoryData)
{

    memoryData.push_back(A.x);
    memoryData.push_back(A.y);
    memoryData.push_back(A.z);

    memoryData.push_back(QuadUvs[quadsIndex*2]);
    memoryData.push_back(QuadUvs[(quadsIndex*2)+1]);

    memoryData.push_back(NHolder.x);
    memoryData.push_back(NHolder.y);
    memoryData.push_back(NHolder.z);
}
void fPoint(const SDFVec3& A, float uvx, float uvy, float* memoryData, int& i)
{
    memoryData[i++] = A.x;
    memoryData[i++] = A.y;
    memoryData[i++] = A.z;

    memoryData[i++] = (A.x+1)/2;
    memoryData[i++] = (A.y+1)/2;

    memoryData[i++] = NHolder.x;
    memoryData[i++] = NHolder.y;
    memoryData[i++] = NHolder.z;
}
void fTriQuad(SDFVec3 A, SDFVec3 B, SDFVec3 C, SDFVec3 D, std::vector<float>& memoryData)
{
    NHolder = Cross(Subtract(B, A), Subtract(D,A));

    fPoint(A, 0, memoryData);
    fPoint(B, 1, memoryData);
    fPoint(C, 2, memoryData);

    fPoint(A, 0, memoryData);
    fPoint(C, 2, memoryData);
    fPoint(D, 3, memoryData);

}
void fTriQuad(SDFVec3 A, SDFVec3 B, SDFVec3 C, SDFVec3 D, float* memoryData, int& i)
{
    NHolder = Cross(Subtract(B, A), Subtract(D,A));

    fPoint(A, 0,0, memoryData, i);
    fPoint(B, 1,0, memoryData, i);
    fPoint(C, 1,1, memoryData, i);

    fPoint(A, 0,0, memoryData, i);
    fPoint(C, 1,1, memoryData, i);
    fPoint(D, 0,1, memoryData, i);

}
void fTri(const SDFVec3 A, const SDFVec3 B, const SDFVec3 C, std::vector<float>& memoryData)
{
    NHolder = Cross(Subtract(B, A), Subtract(C,A));

    fPoint(A, 0, memoryData);
    fPoint(B, 1, memoryData);
    fPoint(B, 2, memoryData);
}
void TriangulateQuad(vec3 A, vec3 B, vec3 C, vec3 D, std::vector<vec3>& Verticies, std::vector<vec2>& UVs)
{

    Verticies.push_back(A);
    Verticies.push_back(B);
    Verticies.push_back(C);

    Verticies.push_back(A);
    Verticies.push_back(C);
    Verticies.push_back(D);
    
    vec2 AUV = {1.0, 1.0};
    UVs.push_back(AUV);
    UVs.push_back(AUV);
    UVs.push_back(AUV);

    UVs.push_back(AUV);
    UVs.push_back(AUV);
    UVs.push_back(AUV);

}

std::vector<vec4> SubdividedPlane(float gap, double width, double height, std::vector<vec2>& uvs)
{
    std::vector<vec4> mesh;

    double wstep = width/gap;
    double hstep = height/gap;

    for(int i = 0; i < wstep; i++)
    {
        
        for(int j = 0; j < hstep; j++)
        {
            vec4 bottomLet = {j*gap, 0.0, i*gap, 1.0};
            vec2 bottomUV = {j*gap/width,i*gap/height};
            vec4 bottomRight = {(j+1)*gap, 0.0, i*gap, 1.0};
            vec2 bottomRightUv = {(j+1)*gap/width, i*gap/height};
            vec4 TopRight = {(j+1)*gap, 0.0, (i+1)*gap, 1.0};
            vec2 TopRightUv = {(j+1)*gap/width, (i+1)*gap/height};
            vec4 TopLeft = {(j)*gap, 0.0, (i+1)*gap, 1.0};
            vec2 TopLeftUv = {(j)*gap/width,(i+1)*gap/height};
            
            mesh.push_back(bottomLet);
            uvs.push_back(bottomUV);
            mesh.push_back(bottomRight);
            uvs.push_back(bottomRightUv);
            mesh.push_back(TopRight);
            uvs.push_back(TopRightUv);
            mesh.push_back(bottomLet);
            uvs.push_back(bottomUV);
            mesh.push_back(TopRight);
            uvs.push_back(TopRightUv);
            mesh.push_back(TopLeft);
            uvs.push_back(TopLeftUv);
        }
        

       


    }


    return mesh;

}
struct SubPlane
{
    float* data;
    int byteSize;
    int verts;
};
SubPlane EqualSubdividedPlane(float subDivisions)
{
    float widthPlane = 2.0;
    float heightPlane = 2.0;
    float dx = widthPlane/subDivisions;
    float dy = heightPlane/subDivisions;

    SDFVec3 Origin = {-1,-1,0};

    float* data = (float*)malloc(32*6*subDivisions*subDivisions);
    int k = 0;
    for(int i = 0; i < subDivisions; i++)
    {
        for(int j = 0; j < subDivisions; j++)
        {
            fTriQuad(Add(Origin, {dx*j, dy*i, 0}), Add(Origin, {dx*(j+1), dy*i, 0}), Add(Origin, {dx*(j+1), dy*(i+1), 0}), Add(Origin, {dx*j, dy*(i+1)}), data, k);
        }
    }

    //fTriQuad({-1, -1, 0}, {1, -1, 0}, {1,1,0}, {-1, 1, 0}, data, i);

    return {data, 32*6*subDivisions*subDivisions, 6*subDivisions*subDivisions};
}

#endif