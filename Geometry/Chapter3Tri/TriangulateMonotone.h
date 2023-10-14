#ifndef TRIANGULTE_MONOTONE_H
#define TRIANGULTE_MONOTONE_H

#include "../Chapter2Dcel/DCEL.h"
#include "MakeMonotope.h"
#include <stack>
#include <algorithm>

bool DifferentChains(DCELVec* A, DCELVec* B)
{
    return (InteriorToTheRight(A) != InteriorToTheRight(B));
}

bool DiagonalInside(DCEL& P, DCEL& D, vec2 uj, vec2 s)
{
    vec2 J = {0,0};
    DCELEdge* Origin = P.edges[0];
    DCELEdge* Iter = Origin;
    while(Iter != nullptr && Iter->next != nullptr)
    {
        // if(Iter->origin->vertex == vec2(244,738))
        // {
        //     printf("here");
        // }
        bool Intersects = lineIntersection2(uj, s,Iter->origin->vertex,Iter->next->origin->vertex, J);
        bool Is = (uj == Iter->origin->vertex) && (s == Iter->next->origin->vertex); //possibly might need isis,
        
        if(Intersects || Is)
        {

            //SpellPoint(J);
            return false;
        }

        Iter = Iter->next;

        if(Iter == Origin)
        {
            break;
        }

    }

    // for(int i = 0 ; i < D.edges.size(); i++)
    // {
    //     bool Intersects = lineIntersection2(uj, s, D.edges[i]->origin->vertex,D.edges[i]->next->origin->vertex, J);

    //     if(Intersects)
    //     {
    //         return false;
    //     }
    // }


    return true;
    
}


bool MYPrio(DCELVec* A, DCELVec* B)
{
    vec2 a = A->vertex;
    vec2 b = B->vertex;

    if(a.y > b.y)
    {
        return true;
    }else if(a.y == b.y)
    {
        if(a.x < b.x)
        {
            return true;
        }
        return false;
    }else
    {
        return false;
    }
}

void TriangulateMonotonePolygon(DCEL& P, DCEL& D)
{
    std::vector<DCELVec*> SortedVertices;

    for(int i = 0; i < P.verticies.size(); i++)
    {
        SortedVertices.push_back(P.verticies[i]);
    }

    std::sort(SortedVertices.begin(), SortedVertices.end(), MYPrio);

    std::stack<DCELVec*> S;
    S.push(SortedVertices[0]);
    S.push(SortedVertices[1]);

    for(int j = 2; j < SortedVertices.size(); j++)
    {

        DCELVec* uj = SortedVertices[j];

        uj->render();
        
        if(!S.empty())
        {

            DCELVec* t = S.top();
            t->render();

            if(DifferentChains(uj, t))
            {

                while(S.size()>1)
                {

                    DCELVec* p = S.top();
                    S.pop();

                    DCELEdge* Diagonal = new DCELEdge(uj);
                    Diagonal->next = p->incident;
                    D.edges.push_back(Diagonal);

                    SpellEdge(uj->vertex, p->incident->origin->vertex);

                }
                
                S.push(SortedVertices[j-1]);
                S.push(uj);
                
            }else
            {
                DCELVec* p = S.top();
                p->render();
                S.pop();

                while(!S.empty())
                {
                    DCELVec* G = S.top();

                    G->render();

                    SpellEdge(uj->vertex, G->vertex);

                    if(DiagonalInside(P, D, uj->vertex, G->vertex))
                    {
                        DCELEdge* Diagonal = new DCELEdge(uj);
                        Diagonal->next = G->incident;
                        D.edges.push_back(Diagonal);

                        S.pop();

                    }else
                    {
                        break;
                    }


                }

                S.push(p);

                S.push(uj);
            }

        }

    
    }
    

    //Sort by decreasing y coordinate, with left dominance.
    //create empty stack S : verticies of P that still may need diagonals.
    //When we encounter a vertex we add as many diagonals to the verticies on stack as possible.
    
    //From top to bottom pushed to stack, what needs to be triangulated lies above the last vertex, and has been encountered so far.
    //And this portion has a particular shape, like a funnel turned upside down, one boundary is part of a single edge of P and the other are reflex
    //verticies with interior angle of at least 180 and only the highest of the verticies is convex

    //case zero
    //the next vertice vj lies on the same chain as the relfex vertices on the stack
    //or on the opposite chain

    //if it lies on the opposite chain it must be the lower endpoing of the single edge e bounding he funnel.

    //due to the shape of the funnel 


    //descend, push onto th stack


}



#endif