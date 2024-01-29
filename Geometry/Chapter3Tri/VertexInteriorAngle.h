#ifndef VERTEX_INTERIOR_ANGLE
#define VERTEX_INTERIOR_ANGLE 


#include "../Chapter2Dcel/DCEL.h"

DCELVec* FindHelper(DCELVec* vertex)
{
    
}


float InteriorAngleRadians(DCELVec* vertex)
{
    DCELVec* Left = vertex->incident->next->origin;
    DCELVec* Right = vertex->incident->prev->origin;

    vec2 a = vertex->vertex;
    vec2 b = Left->vertex;
    vec2 c = Right->vertex;

    rect bounding;
    bounding.IncrementBound(a);
    bounding.IncrementBound(b);
    bounding.IncrementBound(c);

    bounding.Display();

    vec2 tl = vec2(bounding.bottomLeft.x, bounding.topRight.y);
    vec2 bl = vec2(bounding.topRight.x, bounding.bottomLeft.y);
    
    vec2 le = tl-bounding.bottomLeft;
    vec2 re = bounding.topRight-bl;

    


    float mt1 = sqrtf(le.x*le.x + le.y*le.y)/2;
    float mb1 = sqrtf(re.x*re.x + re.y*re.y)/2;

    le.normalize();
    re.normalize();
    le *= mt1;
    re *= mb1;

    le = bounding.bottomLeft + le;
    re = bl + re;

    le.display();

    SpellEdge(le,re);

    vec2 me = re-le;
    
    vec2 Projection = ProjectOnto(a,le,re);
    vec2 VertexToProjection = Projection-a;
    
    float angle = 0;

    if(VertexToProjection.y < 0)
    {
        //left side
        angle += 3.14159265358979323846f;
    }else if(VertexToProjection.y > 0)
    {
        //right side
        //angle += 3.14159265358979323846f;
    }

    vec2 ab = b-a;
    vec2 ac = c-a;

    angle += acosf(dot(ab,ac)/(mag(ab)*mag(ac)));

    return angle;



}




#endif