#ifndef TRIANGULTE_MONOTONE_H
#define TRIANGULTE_MONOTONE_H

#include "../Chapter2Dcel/DCEL.h"
#include "MakeMonotope.h"

#include "TriangulateMonotoneHelper.h"
#include <stack>
#include <algorithm>



bool DifferentChains(float CenterLine, DCELVec* A, DCELVec* B)
{
    int AID = A->id;
    int BID = B->id;
    
    if(A->incident->incident != B->incident->incident)
    {
        return true;
    }

    return (AID < CenterLine) && (BID > CenterLine) || (AID > CenterLine) && (BID < CenterLine) || (AID == CenterLine) || (BID == CenterLine);

    float dxcA = A->vertex.x-CenterLine;
    float dxcB = B->vertex.x-CenterLine;

    return (dxcA > 0 && dxcB < 0) || (dxcA < 0 && dxcB > 0);    

    vec2 a = A->vertex;
    vec2 b = B->vertex;

    vec2 aa = A->incident->next->origin->vertex - A->vertex;
    vec2 bb = B->incident->next->origin->vertex - B->vertex;

    // if(aa.y == 0 && bb.y == 0)
    // {
        
    // }else
    if(aa.y == 0 || bb.y == 0)
    {
        
    }
    else
    {
        return (InteriorToTheRight(A) != InteriorToTheRight(B));
    }
    
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
        P.verticies[i]->id = i;
        SortedVertices.push_back(P.verticies[i]);
    }

    std::sort(SortedVertices.begin(), SortedVertices.end(), MYPrio);

    std::stack<DCELVec*> S;

    int CenterLine = SortedVertices[0]->id;

    S.push(SortedVertices[0]);
    S.push(SortedVertices[1]);

    DCELVec* Temp0 = nullptr;
    DCELVec* Temp1 = nullptr;
    DCELVec* OldG = nullptr;

    for(int j = 2; j < SortedVertices.size(); j++)
    {

        DCELVec* uj = SortedVertices[j];

        if(uj->vertex == vec2(237,300))
        {
            printf("here");
        }

        if(uj->vertex == vec2(460,300))
        {
            printf("here");
        }


        //uj stopping point (91.575989,682.992004)
        uj->render();
        
        if(!S.empty())
        {

            DCELVec* t = S.top();
            t->render();

            

            if(DifferentChains(CenterLine, uj, t))
            {
                
                while(S.size()>0)
                {
                    if(S.top() == nullptr)
                    {
                        S.pop();
                        continue;
                    }

                    if(S.size() == 1)
                    {
                        Temp0 = S.top();
                        OldG = Temp1;
                    }
                    if(S.size() == 2)
                    {
                        Temp1 = S.top();
                        
                    }
                    DCELVec* p = S.top();
                    S.pop();

                    DCELEdge* Diagonal = new DCELEdge(uj);
                    Diagonal->next = p->incident;
                    D.edges.push_back(Diagonal);

                    SpellEdge(uj->vertex, p->incident->origin->vertex);
                }

                
                if(Temp0 != nullptr && Temp1 != nullptr)
                {
                    DCELEdge* Diagonal = new DCELEdge(Temp1);
                    Diagonal->next = Temp0->incident;
                    D.edges.push_back(Diagonal);

                    SpellEdge(Temp1->vertex, Temp0->vertex);
                    
                }

                Temp0 = nullptr;
                Temp1 = nullptr;
                S.push(SortedVertices[j-1]);
                S.push(uj);
                
            }else
            {
                //If this happens this means that there are no other points on the same sweep line, meaning that this last vertex can
                //be abandonded
                //this phase might be able to be replaced with while, vert[j] same side, append to G, pop G

                Temp0 = nullptr;

                DCELVec* p = S.top(); //If somehow the points are the same maybe try to fix this?
                p->render();

                //SpellEdge(uj->vertex, p->vertex);
                S.pop();
                while(!S.empty())
                {
                    DCELVec* G = S.top();

                    G->render();

                    if(uj->vertex == vec2(460,300))
                    {
                        printf("here");
                    }

                    if(DiagonalInside(P,D, uj->vertex, G->vertex))
                    {
                        SpellEdge(uj->vertex, G->vertex);
                        SpellEdge(p->vertex, G->vertex);
                        SpellEdge(uj->vertex, p->vertex);

                        Temp0 = G;
                        //D.edges.push_back(Diagonal);

                        S.pop();

                    }else
                    {
                        break;
                    }
                }
                if(j != SortedVertices.size()-1)
                {

                    //if forward is to the left, then this, if its too the right then that.
                    if(DifferentChains(CenterLine, SortedVertices[j+1], p))
                    {

                        if(Temp0 != nullptr)
                        {

                            S.push(Temp0);
                        }

                        S.push(uj);
                    }else
                    {
                        if(Temp0 != nullptr)
                        {

                            S.push(Temp0);
                        }else if(OldG != nullptr)
                        {
                            S.push(OldG);
                        }

                        
                        S.push(uj);
                        
                    }
                }else
                {
                    S.push(Temp0);
                    S.push(uj);
                }
                //S.push(p);
                
                
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

void ClassifyChains(DCEL& P)
{
    if(P.faces.size() == 1)
    {
        

    }

    int currentChainID = 0;
    for(int f = 0; f < P.faces.size(); f++)
    {

        DCELEdge* IncidentEdge = P.faces[f]->incident;
        DCELEdge* Origin = IncidentEdge;
        while(IncidentEdge != nullptr && IncidentEdge->next != nullptr && IncidentEdge->next != Origin)
        {
            
            if(IsTurnVertex(IncidentEdge->origin))
            {
                currentChainID = (currentChainID == f) ? f+1 : f;
            }
            IncidentEdge = IncidentEdge->next;

        }



    }

}

void TriangulateMonotonePolygon2(DCEL& P, DCEL& D)
{
    std::vector<DCELVec*> SortedVertices;

    for(int i = 0; i < P.verticies.size(); i++)
    {
        P.verticies[i]->id = i;
        SortedVertices.push_back(P.verticies[i]);
    }

    std::sort(SortedVertices.begin(), SortedVertices.end(), MYPrio);

    std::stack<DCELVec*> S;

    int CenterLine = SortedVertices[0]->id;

    S.push(SortedVertices[0]);
    S.push(SortedVertices[1]);

    for(int j = 2; j < SortedVertices.size(); j++)
    {

        DCELVec* uj = SortedVertices[j];

        uj->render();

        if(uj->vertex == vec2(133.000000,46.000000)) //478.000000,249.000000
        {
            printf("here");
        }
        
        if(!S.empty())
        {

            DCELVec* t = S.top();
            t->render();

            if(DifferentChains(CenterLine, uj, t)) //secondary potential problem lies in this function.
            {
                
                while(S.size()>0)
                {
                    DCELVec* p = S.top();
                    S.pop();
                    if(S.size() >= 1)
                    {
                        DCELEdge* Diagonal = new DCELEdge(uj);
                        Diagonal->next = p->incident;
                        D.edges.push_back(Diagonal);

                        SpellEdge(uj->vertex, p->incident->origin->vertex);
                    }
                }

                S.push(SortedVertices[j-1]);
                S.push(uj);
                
            }else
            {

                DCELVec* p = S.top();
                //p->render();
                
                S.pop();

                if(uj->vertex == vec2(460,300))
                {
                    printf("here");
                }
                
                while(!S.empty())
                {
                    DCELVec* G = S.top();

                    G->render();

                    if(DiagonalInside(P,D, uj->vertex, G->vertex)) //problem lies in this, need to solidfy this function, it is not ideal. 
                    {
                        SpellEdge(uj->vertex, G->vertex);
                        //SpellEdge(p->vertex, G->vertex);
                        //SpellEdge(uj->vertex, p->vertex);

                        //D.edges.push_back(Diagonal);

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
    



}



#endif