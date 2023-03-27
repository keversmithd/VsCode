#ifndef SDFNEIGHBOR_COND
#define SDFNEIGHBOR_COND
#include <SDFArchive.h>
// 0 : BottomLeftFront, 1 : TopLeftFront, 2 : BottomRightFront, 3 : TopRightFront, 4 : BottomLeftBack, 5 : TopLeftBack, 6 : BottomRightBack, 7 : TopRightBack, 8 : Outside
inline SDFBoundingVolume VolumeCondition0(const SDFBoundingVolume Parent)
{
    const SDFVec3 VolumeCenter = CenterOfVolume(Parent);

    const SDFVec3 TopLeftFront = {Parent.TopLeftFront.x, VolumeCenter.y, Parent.TopLeftFront.z};
    const SDFVec3 BottomRightBack = {VolumeCenter.x, Parent.BottomRightBack.y, VolumeCenter.z};
    
    return {TopLeftFront, BottomRightBack};

    
}



#endif