#ifndef SDFARCH_H
#define SDFARCH_H
#include <vector>
#include <math.h>


inline float GetMin(float x1, float x2, float x3)
{
        float minX;
        minX = (x1 < x2) ? x1 : x2;
        minX = (x3 < minX) ? x3 : minX;
        return minX;
}
inline float GetMax(float x1, float x2, float x3)
{
        float maxX;
        maxX = (x1 > x2) ? x1 : x2;
        maxX = (x3 > maxX) ? x3 : maxX;
        return maxX;
}

struct SDFVec3
{
    float x,y,z;
};

struct SDFFace
{
    SDFVec3 v0;
    SDFVec3 v1;
    SDFVec3 v2;
    SDFVec3 Normal;
};



struct SDFMesh
{
    std::vector<SDFFace> faces;
};

struct SDFMeshNode
{
    SDFFace Face;
};

struct SDFBoundingVolume
{
    SDFVec3 TopLeftFront;
    SDFVec3 BottomRightBack;
};

struct SDFParaLine
{
    SDFVec3 Origin;
    SDFVec3 Direction;
};

struct SDFRay
{
    SDFVec3 Origin;
    SDFVec3 Direction;
};

struct SDFPlane
{
    SDFVec3 BottomLeft;
    SDFVec3 BottomRight;
    SDFVec3 TopLeft;
    SDFVec3 TopRight;
};

struct SDFPlaneEquation
{
    float x,y,z,c;
};


    inline SDFVec3 CenterOfVolume(const SDFBoundingVolume volume)
    {
        float ZDepth = volume.BottomRightBack.z - volume.TopLeftFront.z;
        float XDepth = volume.BottomRightBack.x - volume.TopLeftFront.x;
        float YDepth = volume.TopLeftFront.y - volume.BottomRightBack.y;
        return {XDepth/2, YDepth/2, ZDepth/2};
    }
inline float Mag(const SDFVec3 vec)
{
    return sqrt(pow(vec.x,2) + pow(vec.y,2) + pow(vec.z,2));
}
inline float Dot(const SDFVec3 vec1, const SDFVec3 vec2)
{
    return (vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z);
}
inline float DistanceToPlane(const SDFVec3 PQ, const SDFVec3 N)
{
    return (abs(Dot(PQ, N)))/(Mag(N));
}
inline SDFVec3 Add(const SDFVec3 a, const SDFVec3 b)
{
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}
inline SDFVec3 Subtract(const SDFVec3 P, const SDFVec3 Q)
{
    return {P.x - Q.x, (P.y - Q.y), P.z - Q.z};
}
inline SDFVec3 Multiply(const SDFVec3 P, const SDFVec3 Q)
{
    return {P.x * Q.x, P.y * Q.y, P.z * Q.z};
}
inline SDFVec3 Multiply(const SDFVec3 P, float f)
{
    return {P.x * f, P.y * f, P.z * f};
}
inline SDFVec3 Multiply(float f, const SDFVec3 P)
{
    return {P.x * f, P.y * f, P.z * f};
}
inline SDFVec3 Divide(const SDFVec3 P, float f)
{
    return {P.x / f, P.y / f, P.z /f};
}
inline SDFVec3 Divide(const SDFVec3 P, SDFVec3 Q)
{
    return {P.x / Q.x, P.y/Q.y, P.z/Q.z};
}
inline SDFVec3 Cross(const SDFVec3 vec1, const SDFVec3 vec2)
{
    return {(vec1.y * vec2.z) - (vec2.y * vec2.z),-((vec1.x * vec2.z) - (vec2.x * vec1.z)), (vec1.x * vec2.y) - (vec2.x * vec1.y)};
}
inline SDFVec3 FinitePlaneNormal(const SDFPlane nPlane)
{
    return Cross(Subtract(nPlane.BottomRight,nPlane.BottomLeft), Subtract(nPlane.TopRight, nPlane.TopLeft));
}
inline SDFVec3 Normalize(const SDFVec3 n)
{
    float mag = Mag(n);
    return {n.x /mag, n.y/mag, n.z/mag};
}
inline SDFVec3 ParametricLineSample(const SDFVec3 Direction, const SDFVec3 Start, float t)
{
    return {Start.x + (Direction.x * t), Start.y + (Direction.y * t), Start.z + (Direction.z * t)};
}
inline SDFVec3 IntersectionOFParalines(const SDFParaLine p1, const SDFParaLine p2)
{
    
}

inline SDFVec3 CenterOfFinitePlane(const SDFPlane nPlane)
{
    SDFVec3 LeftCross = Subtract(nPlane.TopLeft, nPlane.BottomRight);

    SDFVec3 RightCross = Subtract(nPlane.TopRight, nPlane.BottomLeft);

    float a0 = nPlane.BottomRight.x;
    float c0 = LeftCross.x;

    float a1 = nPlane.BottomLeft.x;
    float c1 = RightCross.x;

    float s = (a0 + ((c0*a1)/a0) - 1 - a1)/(c1 - (c0*c1)/a0);

    float t = (a1 + c1*s - a0)/c0;

    return ParametricLineSample(LeftCross, nPlane.BottomLeft, t);
}
inline SDFVec3 CenterOfFace(const SDFFace nFace)
{
    SDFVec3 MidPoint1 = Add(nFace.v0, Multiply(Subtract(nFace.v1, nFace.v0),0.5));
    SDFVec3 MidVector1 = Subtract(nFace.v2, MidPoint1);
    
    SDFVec3 MidPoint2 = Add(nFace.v1, Multiply(Subtract(nFace.v2, nFace.v1),0.5));
    SDFVec3 MidVector2 = Subtract(nFace.v0, MidPoint2);
    
    

    //SDFVec3 L1 = {MidPoint1.x + MidVector1.x * t, MidPoint1.y + MidVector1.y *t, MidPoint1.z + MidVector1.z * t};
    //SDFVec3 L2 = {MidPoint2.x + MidVector2.x * s, MidPoint2.y + MidVector2.y *s, MidPoint2.z + MidVector2.z * s};

    float a0y = MidPoint1.y;
    float c0y = MidVector1.y;
    float a1x = MidPoint2.x;
    float a0x = MidPoint1.x;
    float c0x = MidVector1.x;
    float a1y = MidPoint2.y;
    float c1y = MidVector2.y;
    float c1x = MidVector2.x;
    float a1z = MidPoint2.z;
    float c1z = MidVector2.z;
    float a0z = MidPoint1.z;
    float c0z = MidVector1.z;

    float s = (a0y + c0y * ((a1x - a0x)/c0x) - a1y)/(c1y - ((c0y*c1x)/c0x));
    float t = (a1z + (c1z*s) - a0z)/(c0z);



    /*float denom = c0x * c1y - c1x * c0y;
if (abs(denom) < EPSILON) {
    // The lines are parallel, no intersection point
    return false;
}

// Calculate the parameters t and s of the intersection point
float t = ((a1z - a0z) * c1y + (a0y - a1y) * c1z) / denom;
float s = ((a1x - a0x) * c0y + (a0y - a1y) * c0x) / denom;*/

//gp alternative

//alternative with cross product

//Vector definition.
    SDFVec3 P = Subtract(MidPoint2, MidPoint1);
    SDFVec3 C0 = Cross(P, MidVector2);
    SDFVec3 C1 = Cross(P, MidVector1);

    SDFVec3 C = Cross(MidVector1, MidVector2);

    float m = pow(C.x,2) + pow(C.y,2) + pow(C.z,2);
    SDFVec3 t1 = Divide(Multiply(C0,  C), m);
    SDFVec3 t2 = Divide(Multiply(C1, C), m);
    


}
inline SDFVec3 HalfBetweenPoints(const SDFVec3 P, const SDFVec3 Q)
{
    return Add(P, Divide(Subtract(Q,P),2));
}
inline SDFVec3 PointOnFinitePlane(const SDFPlane nPlane)
{
    
}

inline const SDFPlane PlanarIntersection(SDFVec3 Direction, SDFBoundingVolume BoundingVolume)
{
    //define local coordinate system for bounding volume.
    const SDFVec3 Origin = CenterOfVolume(BoundingVolume);
    const SDFVec3 XAxis = {Origin.x + 1, 0,0};
    float HeightOfBoundingVolume = BoundingVolume.TopLeftFront.y;

    float DirectionalYReach = Origin.y + Direction.y;
    
    if(DirectionalYReach > HeightOfBoundingVolume)
    {
        SDFVec3 TPBottomLeft = {BoundingVolume.TopLeftFront.x, BoundingVolume.TopLeftFront.y, BoundingVolume.TopLeftFront.z};
        SDFVec3 TPBottomRight = {BoundingVolume.BottomRightBack.x, BoundingVolume.TopLeftFront.y, BoundingVolume.TopLeftFront.z};
        SDFVec3 TPTopRight = {BoundingVolume.BottomRightBack.x, BoundingVolume.TopLeftFront.y,  BoundingVolume.BottomRightBack.z};
        SDFVec3 TPTopLeft = {BoundingVolume.TopLeftFront.x, BoundingVolume.TopLeftFront.y, BoundingVolume.BottomRightBack.z};
        SDFPlane ReturnPlane;
        ReturnPlane.TopLeft = TPTopLeft;
        ReturnPlane.TopRight = TPTopRight;
        ReturnPlane.BottomLeft = TPBottomLeft;
        ReturnPlane.BottomRight = TPBottomRight;

        return ReturnPlane;
    }

    //Left Plane Definition
    SDFVec3 LPBottomLeft = {BoundingVolume.TopLeftFront.x, BoundingVolume.BottomRightBack.y, BoundingVolume.BottomRightBack.z};
    SDFVec3 LPBottomRight = {BoundingVolume.TopLeftFront.x, BoundingVolume.BottomRightBack.y, BoundingVolume.TopLeftFront.z};
    SDFVec3 LPTopRight = {BoundingVolume.TopLeftFront.x, BoundingVolume.TopLeftFront.y, BoundingVolume.TopLeftFront.z};
    SDFVec3 LPTopLeft = {BoundingVolume.TopLeftFront.x, BoundingVolume.TopLeftFront.y, BoundingVolume.BottomRightBack.z};


    //calculate dot product with the boxes x axis
    float XDot = Dot(Direction, XAxis)/(Mag(XAxis)*Mag(Direction));
    //calculat dot product with the y axis

    //the threshold is the height of the bounding volume and the y component of the vector

    //if dot on y is positive and within generalized threshold based on bounding volume wall size
    //if dot on y is negative and within absolute value of generalized threshhold than the plane is top

    //figure out generalzied threshold

    //if dot x greater than 0.71, right plane
    //if dot x less than 0.71, left plane
    //else if vector.y < 0 bottom plane
    //else if vector.y > 0 top plane

}
inline const SDFVec3 IntersectionOfLineAndPlane(SDFRay Ray, SDFPlane plane)
{
    const SDFVec3 BottomEdge = Subtract(plane.BottomRight, plane.BottomLeft);
    const SDFVec3 LeftEdge = Subtract(plane.TopLeft, plane.BottomLeft);
    const SDFVec3 PlanarNormal = Cross(BottomEdge, LeftEdge);
    float Intercept = Dot(PlanarNormal, Multiply(plane.BottomLeft, -1));
    float TCoefficent = Dot(PlanarNormal, Ray.Direction);
    float Constant = Dot(PlanarNormal, Ray.Origin);
    float t = (-Intercept - Constant)/TCoefficent;
    return Add(Ray.Origin, Multiply(Ray.Direction, t));
}

inline bool PointContainedWithinBoundingVolumeBoolean(const SDFBoundingVolume BoundingVolume,const SDFVec3 point)
    {
        bool xrange = (point.x >= BoundingVolume.TopLeftFront.x && point.x <= BoundingVolume.BottomRightBack.x);
        bool yrange = (point.y >= BoundingVolume.BottomRightBack.y && point.y <= BoundingVolume.TopLeftFront.y);
        bool zrange = (point.z >= BoundingVolume.TopLeftFront.z && point.y <= BoundingVolume.BottomRightBack.z);
        return (xrange && yrange && zrange);
        if(point.x >= BoundingVolume.TopLeftFront.x && point.x <= BoundingVolume.BottomRightBack.x)
        {
            //inxrange
        }
        if(point.y >= BoundingVolume.BottomRightBack.y && point.y <= BoundingVolume.TopLeftFront.y)
        {
            //inyrange
        }
        if(point.z >= BoundingVolume.TopLeftFront.z && point.y <= BoundingVolume.BottomRightBack.z)
        {
            //inzrange
        }
    }

inline int OctaneOfPoint(const SDFBoundingVolume BoundingVolume, const SDFVec3 point)
    {
        const SDFVec3 centerOfVolume = CenterOfVolume(BoundingVolume);
        // 0 : BottomLeftFront, 1 : TopLeftFront, 2 : BottomRightFront, 3 : TopRightFront, 4 : BottomLeftBack, 5 : TopLeftBack, 6 : BottomRightBack, 7 : TopRightBack, 8 : Outside
        if(!PointContainedWithinBoundingVolumeBoolean(BoundingVolume, point)){ return 8; }
        return ((4 * (point.z > centerOfVolume.z)) + (2 * (point.x > centerOfVolume.x)) + (point.y > centerOfVolume.y));
        int ReturnIndex = 0;
        if(point.z > centerOfVolume.z)
        {
            ReturnIndex += 4;
        }
        if(point.x > centerOfVolume.x)
        {
            ReturnIndex += 2;
        }
        if(point.y > centerOfVolume.y)
        {
            ReturnIndex += 1;
        }
    }

inline const SDFBoundingVolume CalculateBoundingVolumeOfMesh(const SDFMesh& Model)
{
    
}

inline SDFBoundingVolume GetVolumeOfFace(const SDFFace face)
{
        SDFBoundingVolume NewVolume;
        float minX = 2147483647, maxX = -2147483647;
        float minY = 2147483647, maxY = -2147483647;
        float minZ = 2147483647, maxZ = -2147483647;

        minX = GetMin(face.v0.x, face.v1.x, face.v2.x);
        maxX = GetMax(face.v0.x, face.v1.x, face.v2.x);

        minY = GetMin(face.v0.y, face.v1.y, face.v2.y);
        maxY = GetMax(face.v0.y, face.v1.y, face.v2.y);

        minZ = GetMin(face.v0.z, face.v1.z, face.v2.z);
        maxZ = GetMax(face.v0.z, face.v1.z, face.v2.z);

        NewVolume.TopLeftFront = {minX, maxY, minZ};
        NewVolume.BottomRightBack = {maxX, minY, maxZ};
        return NewVolume;
}

inline bool IntersectsThisBoundingVolumeBooleanT(const SDFBoundingVolume T, const SDFBoundingVolume BoundingVolume)
    {
        float WThisVolume = BoundingVolume.BottomRightBack.x - BoundingVolume.TopLeftFront.x;
        float HThisVolume = BoundingVolume.TopLeftFront.y - BoundingVolume.BottomRightBack.y;
        float DThisVolume = BoundingVolume.BottomRightBack.z - BoundingVolume.TopLeftFront.z;

        bool XRange = (T.TopLeftFront.x < BoundingVolume.BottomRightBack.x && T.BottomRightBack.x > BoundingVolume.TopLeftFront.x) || (T.BottomRightBack.x < BoundingVolume.BottomRightBack.x && T.TopLeftFront.x > BoundingVolume.TopLeftFront.x);
        bool YRange = (T.TopLeftFront.y > BoundingVolume.BottomRightBack.y && T.BottomRightBack.y < BoundingVolume.TopLeftFront.y) || (T.BottomRightBack.y > BoundingVolume.BottomRightBack.y && T.TopLeftFront.y < BoundingVolume.TopLeftFront.y);
        bool ZRange = (T.TopLeftFront.z < BoundingVolume.BottomRightBack.z && T.BottomRightBack.z > BoundingVolume.TopLeftFront.z) || (T.BottomRightBack.z < BoundingVolume.BottomRightBack.z && T.TopLeftFront.z > BoundingVolume.TopLeftFront.z);


        if(T.TopLeftFront.x < BoundingVolume.BottomRightBack.x && T.BottomRightBack.x > BoundingVolume.TopLeftFront.x)
        {
            //In X Range
        }

        if(T.BottomRightBack.x < BoundingVolume.BottomRightBack.x && T.TopLeftFront.x > BoundingVolume.TopLeftFront.x)
        {
            //In X Range
        }

        if(T.TopLeftFront.y > BoundingVolume.BottomRightBack.y && T.BottomRightBack.y < BoundingVolume.TopLeftFront.y)
        {
            //In Y Range
        }

        if(T.BottomRightBack.y > BoundingVolume.BottomRightBack.y && T.TopLeftFront.y < BoundingVolume.TopLeftFront.y)
        {
            //In Y Range
        }
        

        if(T.TopLeftFront.z < BoundingVolume.BottomRightBack.z && T.BottomRightBack.z > BoundingVolume.TopLeftFront.z)
        {
            //In Z Range
        }

        if(T.BottomRightBack.z < BoundingVolume.BottomRightBack.z && T.TopLeftFront.z > BoundingVolume.TopLeftFront.z)
        {
            //In Z Range
        }

        return (XRange & YRange & ZRange);

    }

#endif

