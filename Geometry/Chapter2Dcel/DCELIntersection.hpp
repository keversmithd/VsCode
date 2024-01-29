#ifndef DCEL_INTERSECT_H
#define DCEL_INTERSECT_H

#include "DCELHead.hpp"


int VerticleArrangement(DCELVec* vert1, DCELVec* vert2)
{
    
    if(vert1->vertex.y < vert2->vertex.y)
    {
        return 1;
    }else if (vert1->vertex.y > vert2->vertex.y)
    {
        return 2;
    }else if (vert1->vertex.x == vert2->vertex.x)
    {
        return 0;
    }else if (vert1->vertex.x < vert2->vertex.x)
    {
        return 1;
    }else if (vert1->vertex.x > vert2->vertex.x)
    {
        return 2;
    }

    return 0;
}

int PlanarArrangement(DCELEdge* vert1, DCELEdge* vert2, float status)
{

    Vec a0 = vert1->origin->vertex;
    Vec b0 = vert1->twin->origin->vertex;
    Vec a1 = vert2->origin->vertex;
    Vec b1 = vert2->twin->origin->vertex;

    // Vec V0; V0.x = b0.x - a0.x; V0.y = b0.y - a0.y; V0.z = b0.z - a0.z;
    // Vec V1; V1.x = b1.x - a1.x; V1.y = b1.y - a1.y; V1.z = b1.z - a1.z;
    // Vec V2; V2.x = b0.x - a0.x; V2.y = b0.y - b0.y; V2.z = b0.z-a0.z;

    // float MagnitudeOrigin = mag(cross(V1,V2));
    // float MagnitudeDestination = mag(cross(V1,V0));
    
    // if(cross(V0,V1).isZero() || MagnitudeDestination == 0 || MagnitudeOrigin == 0)
    // {
    //     return 0;
    // }

    // int s = (dot(V0,V1) > 0) ? 1 : -1;
    // V0 *= (MagnitudeOrigin/MagnitudeDestination)*s;
    // a0 += V0;

    Vec V0; V0.x = b0.x - a0.x; V0.y = b0.y - a0.y;
    float edge1T = (status-vert1->origin->vertex.y)/V0.y;

    

    Vec V1; V1.x = b1.x - a1.x; V1.y = b1.y - a1.y;
    float edge2T = (status-vert2->origin->vertex.y)/V1.y;

    V0.normalize();
    V1.normalize();

    V0 *= edge1T;
    V1 *= edge2T;
    

    if(V0.x < V1.x)
    {
        return 1;
    }else if (V0.x > V1.x)
    {
        return 2;
    }

    return 0;
}

bool ParametricIntersection(DCELEdge* edge1, DCELEdge* edge2, Vec& i)
{
    i = edge1->origin->vertex;
    Vec b0 = edge1->twin->origin->vertex;
    Vec a1 = edge2->origin->vertex;
    Vec b1 = edge2->twin->origin->vertex;

    Vec V0; V0.x = b0.x - i.x; V0.y = b0.y - i.y;
    Vec V1; V1.x = b1.x - a1.x; V1.y = b1.y - a1.y;
    Vec V2; V2.x = a1.x - i.x; V2.y = a1.y - i.y;

    float MagnitudeOrigin = abs(cross(V1,V2));
    float MagnitudeDestination = abs(cross(V1,V0));
    
    if(cross(V0,V1) == 0 || MagnitudeDestination == 0 || MagnitudeOrigin == 0)
    {
        return false;
    }

    int s = (dot(V0,V1) > 0) ? 1 : -1;
    V0 *= (MagnitudeOrigin/MagnitudeDestination)*s;
    i += V0;

    return true;
}

bool IsUpperEndPoint(DCELVec* vert)
{
    return VerticleArrangement(vert, vert->incident->twin->origin) == 2;
}

struct DeconstructedEdge
{
    Vec UpperEndPoint;
    Vec LowerEndPoint;
};

DeconstructedEdge DeconstructEdge(DCELEdge* node)
{
    DeconstructedEdge ret;
    if(IsUpperEndPoint(node->origin))
    {
        ret.UpperEndPoint = node->origin->vertex;
        ret.LowerEndPoint = node->twin->origin->vertex;
    }else
    {
        ret.UpperEndPoint = node->twin->origin->vertex;
        ret.LowerEndPoint = node->origin->vertex;
    }

    return {{0,0},{0,0}};
}

#endif