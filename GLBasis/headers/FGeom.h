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

    memoryData[i++] = uvx;
    memoryData[i++] = uvy;

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
void fTriQuad(SDFVec3 A, SDFVec3 B, SDFVec3 C, SDFVec3 D, float* memoryData, int& i, float uvscale)
{
    NHolder = Cross(Subtract(B, A), Subtract(D,A));

    fPoint(A, 0,0, memoryData, i);
    fPoint(B, uvscale*1,0, memoryData, i);
    fPoint(C, uvscale*1,uvscale*1, memoryData, i);

    fPoint(A, 0,0, memoryData, i);
    fPoint(C, uvscale*1,uvscale*1, memoryData, i);
    fPoint(D, 0,uvscale*1, memoryData, i);

}

void fTriQuad(SDFVec3 A, SDFVec3 B, SDFVec3 C, SDFVec3 D, float* memoryData, int& i, unsigned int* indexBuffer, int& j, int& indices)
{
    NHolder = Cross(Subtract(B, A), Subtract(D,A));

    fPoint(A, 0,0, memoryData, i);
    fPoint(B, 1,0, memoryData, i);
    fPoint(C, 1,1, memoryData, i);
    fPoint(D, 0,1, memoryData, i);

    indexBuffer[indices++] = j;
    indexBuffer[indices++] = j+1;
    indexBuffer[indices++] = j+2;

    indexBuffer[indices++] = j;
    indexBuffer[indices++] = j+2;
    indexBuffer[indices++] = j+3;

    j+=4;
}



void fCircQuad(const SDFVec3 Start, const SDFVec3 End, float radius0,  float radius1, const SDFVec3 Normal, const SDFVec3 Binormal, float j, float dr, float* memoryData, int& i, unsigned int* indexBuffer, int& b, int& indices)
{
    SDFVec3 c1,c2,c3,c4;
    SDFVec3 LowerRotation, UpperRotation;
    LowerRotation.rotateFrame(Normal, Binormal, j*dr);
    UpperRotation.rotateFrame(Normal, Binormal, (j+1)*dr);
    LowerRotation *= radius0;
    UpperRotation *= radius0;
    c1 = Start;
    c1 += LowerRotation;
    c4 = Start;
    c4 += UpperRotation;

    LowerRotation.normalize();
    UpperRotation.normalize();
    LowerRotation *= radius1;
    UpperRotation *= radius1;
    c2 = End;
    c2 += LowerRotation;
    c3 = End;
    c3 += UpperRotation;
    

    fTriQuad(c1, c2, c3, c4, memoryData, i, indexBuffer, b, indices);
}





void fTri(const SDFVec3 A, const SDFVec3 B, const SDFVec3 C, std::vector<float>& memoryData)
{
    NHolder = Cross(Subtract(B, A), Subtract(C,A));

    fPoint(A, 0, memoryData);
    fPoint(B, 1, memoryData);
    fPoint(B, 2, memoryData);
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
            fTriQuad(Add(Origin, {dx*j, dy*i, 0}), Add(Origin, {dx*(j+1), dy*i, 0}), Add(Origin, {dx*(j+1), dy*(i+1), 0}), Add(Origin, {dx*j, dy*(i+1)}), data, k, 2);
        }
    }

    //fTriQuad({-1, -1, 0}, {1, -1, 0}, {1,1,0}, {-1, 1, 0}, data, i);

    return {data, 32*6*subDivisions*subDivisions, 6*subDivisions*subDivisions};
}

#endif