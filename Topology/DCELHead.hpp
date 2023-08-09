#ifndef DCEL_HEAD_H
#define DCEL_HEAD_H

#pragma region DCEL_HEAD

struct Vec
{
    float x,y,z;

    bool isZero()
    {
        return (x==0 && y==0 && z==0);
    }

    void operator *=(Vec A)
    {
        x *= A.x;
        y *= A.y;
        z *= A.z;
    }
    void operator *=(float A)
    {
        x *= A;
        y *= A;
        z *= A;
    }

    void operator +=(Vec v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
    }

    void normalize()
    {
        float m = sqrt(x*x + y*y + z*z);
        if(m == 0){
            return;
        }
        x /= m;
        y /= m;
        z /= m;
    }
};

Vec cross(Vec A, Vec B)
{
    return {A.y*B.z - B.y*A.z, -(A.x*B.z-B.x*A.z), (A.x*B.y-B.x*A.y) };
}

float dot(Vec A, Vec B)
{
    return A.x*B.x + A.y*B.y + A.z*B.z;
}

float mag(Vec A)
{
    return sqrt(A.x*A.x + A.y*A.y + A.z*A.z);
}

struct DCELEdge;

struct DCELFace
{
    DCELEdge* incident; //using a possible combination of indices, if possible
};

struct DCELVec
{
    Vec vertex; //cannot remove correctly here.
    DCELEdge* incident;
    int id; 
};

struct DCELEdge
{
    DCELEdge* twin; 
    DCELFace* face; //index
    DCELEdge* next; //index
    DCELEdge* prev; //index
    DCELVec* origin; //index
};

#pragma end region





#endif