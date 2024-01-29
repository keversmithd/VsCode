#ifndef TRIANGLULATE_MONOTONE_HELPER
#define TRIANGLULATE_MONOTONE_HELPER 

#include "../Chapter2Dcel/DCEL.h"
#include "MakeMonotope.h"

bool DiagonalInside(DCEL& P, DCEL& D, vec2 uj, vec2 s)
{
    vec2 J = vec2(0,0);

    for(int i = 0 ; i < P.edges.size(); i++)
    {
        bool Intersects = lineIntersection2(uj, s, P.edges[i]->origin->vertex,P.edges[i]->next->origin->vertex, J);
        //P.edges[i]->display();
        if(Intersects)
        {
            return false;
        }
    }
    for(int i = 0 ; i < D.edges.size(); i++)
    {
        bool Intersects = lineIntersection2(uj, s, D.edges[i]->origin->vertex,D.edges[i]->next->origin->vertex, J);

        if(Intersects)
        {
            return false;
        }
    }


    return true;
    
}




#endif