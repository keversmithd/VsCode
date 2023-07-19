#ifndef SDFBOUNDINGPRIMS
#define SDFBOUNDINGPRIMS

#include "SDFArchive.h"

bool PointContainedWithinBoundingVolumeBoolean(const SDFVec3 point, const SDFBoundingVolume BoundingVolume)
{
    bool xrange = (point.x >= BoundingVolume.TopLeftFront.x && point.x <= BoundingVolume.BottomRightBack.x);
    bool yrange = (point.y >= BoundingVolume.BottomRightBack.y && point.y <= BoundingVolume.TopLeftFront.y);
    bool zrange = (point.z >= BoundingVolume.TopLeftFront.z && point.z <= BoundingVolume.BottomRightBack.z);

    if(!xrange || !yrange || !zrange)
    {
        std::cout << "hello" << std::endl;
    }
    return (xrange && yrange && zrange);
}

bool IntersectsThisBoundingVolumeBoolean(const SDFBoundingVolume T, const SDFBoundingVolume BoundingVolume)
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

bool RightTurn(SDFVec2 A, SDFVec2 B,  SDFVec2 C)
{
    SDFVec2 AB = B-A;
    AB.normalize();
    SDFVec2 BC = C-B;
    BC.normalize();

    return (cross(AB, BC) < 0);
}

SDFVec2 ProjectDownPlane(const SDFVec3 vector, const SDFVec3 PlanarNormal, const SDFVec3 PlanePoint)
{
    const SDFVec3 YAxis = Cross(PlanarNormal, PlanePoint);
    const SDFVec3 XAxis = Cross(PlanarNormal, YAxis);

    return {dot(vector,XAxis)/dot(XAxis,XAxis),dot(vector,YAxis)/dot(YAxis,YAxis)};

}

int OctaneOfPoint(const SDFVec3 point, const SDFBoundingVolume BoundingVolume)
{
    const SDFVec3 centerOfVolume = CenterOfVolume(BoundingVolume);
    // 0 : BottomLeftFront, 1 : TopLeftFront, 2 : BottomRightFront, 3 : TopRightFront, 4 : BottomLeftBack, 5 : TopLeftBack, 6 : BottomRightBack, 7 : TopRightBack, 8 : Outside
    if(!PointContainedWithinBoundingVolumeBoolean(point, BoundingVolume)){ return 8; }
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

SDFBoundingVolume VolumeOfChild(int childIndex, const SDFBoundingVolume BoundingVolume)
{
    const SDFVec3 centerOfParentVolume = CenterOfVolume(BoundingVolume);

    switch(childIndex)
    {
        case 0:
            return {{BoundingVolume.TopLeftFront.x, centerOfParentVolume.y, BoundingVolume.TopLeftFront.z},{centerOfParentVolume.x, BoundingVolume.BottomRightBack.y, centerOfParentVolume.z}};
        case 1:
            return {{BoundingVolume.TopLeftFront.x, BoundingVolume.TopLeftFront.y, BoundingVolume.TopLeftFront.z},{centerOfParentVolume.x, centerOfParentVolume.y, centerOfParentVolume.z}};
        case 2:
            return {{centerOfParentVolume.x, centerOfParentVolume.y, BoundingVolume.TopLeftFront.z},{BoundingVolume.BottomRightBack.x,  BoundingVolume.BottomRightBack.y, centerOfParentVolume.z}};
        case 3:
            return {{centerOfParentVolume.x, BoundingVolume.TopLeftFront.y, BoundingVolume.TopLeftFront.z},{BoundingVolume.BottomRightBack.x,  centerOfParentVolume.y , centerOfParentVolume.z}};
        case 4:
            return{{BoundingVolume.TopLeftFront.x, BoundingVolume.BottomRightBack.y, centerOfParentVolume.z},{centerOfParentVolume.x, centerOfParentVolume.y, BoundingVolume.BottomRightBack.z}};
        case 5:
            return {{BoundingVolume.TopLeftFront.x, BoundingVolume.TopLeftFront.y, centerOfParentVolume.z},{centerOfParentVolume.x,  centerOfParentVolume.y, BoundingVolume.BottomRightBack.z}};
        case 6:
            return {{centerOfParentVolume.x, centerOfParentVolume.y, centerOfParentVolume.z},{BoundingVolume.BottomRightBack.x,  BoundingVolume.BottomRightBack.y, BoundingVolume.BottomRightBack.z}};
        case 7:
            return {{centerOfParentVolume.x, BoundingVolume.TopLeftFront.y, centerOfParentVolume.z},{BoundingVolume.BottomRightBack.x, centerOfParentVolume.y, BoundingVolume.BottomRightBack.z}};
    }
}



#endif