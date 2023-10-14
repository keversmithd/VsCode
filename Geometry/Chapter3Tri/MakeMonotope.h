#ifndef MAKE_MONOTOPE_TRI_H
#define MAKE_MONOTOPE_TRI_H 

#include "../Chapter2Dcel/DCEL.h"
#include "../PqueArray.hpp"
#include "../RBTree.h"
#include <unordered_map>

#pragma region VERTEX_TYPES

#define PIF 3.14159265358979323846f

enum VertexTypeEnum
{
    StartVertex = 1,
    SplitVertex = 2,
    EndVertex = 3,
    MergeVertex = 4,
    ErrorVertex = -1
};

bool IsTurnVertex(DCELVec* vertex)
{


    DCELVec* Left = vertex->incident->prev->origin;
    DCELVec* Right = vertex->incident->next->origin;

    // Left->render();
    // Right->render();

    vec2 a = vertex->vertex;
    vec2 b = Left->vertex;
    vec2 c = Right->vertex;

    float bay = a.y-b.y;
    float acy = c.y-a.y;

    if(bay != 0)
    {
        bay /= abs(bay);
    }

    if(acy != 0)
    {
        acy /= abs(acy);
    }

    return (bay != acy);
}

int VertexType(DCELVec* vertex)
{

    DCELVec* Left = vertex->incident->prev->origin;
    DCELVec* Right = vertex->incident->next->origin;

    vec2 a = vertex->vertex;
    //a.display();
    vec2 b = Left->vertex;
    //b.display();
    vec2 c = Right->vertex;
    //c.display();

    if(b.y < a.y && c.y < a.y)
    {   
        vec2 x = b-a;
        vec2 y = c-a;
        //or
        //a = a-b
        //b = c-a

        float d = (x.x * y.x) + (x.y *y.y);
        float m = sqrtf(x.x*x.x + x.y*x.y)*sqrtf(y.x*y.x + y.y*y.y);
        float a = 0.0;
        if(m == 0)
        {
            a = acosf(0.0f);
        }else
        {
            a = acosf(d/m);
        }
        
        return (a < PIF) ? 1 : 2;


    }else if(b.y > a.y && c.y > a.y)
    {
        
        vec2 x = b-a;
        vec2 y = c-a;
        //or
        //a = a-b
        //b = c-a

        float d = (x.x * y.x) + (x.y *y.y);
        float m = sqrtf(x.x*x.x + x.y*x.y)*sqrtf(y.x*y.x + y.y*y.y);
        float a = 0.0;
        if(m == 0)
        {
            a = acosf(0.0f);
        }else
        {
            a = acosf(d/m);
        }
        return (a < PIF) ? 3 : 4;

    }else
    {
        return -1;
    }

}


#pragma endregion

#pragma region INTERIOR_RIGHT

    bool InteriorToTheRight(DCELVec* vi) //If vi is counter clock wise, then if the next point is down, then interior to the right, if up then interior left.
    {
        vec2 a = vi->vertex;
        DCELVec* vip = vi->incident->next->origin;
        vec2 b = vip->vertex;

        if(b.y < a.y)
        {
            return true;
        }else if(a.y == b.y)
        {
            return false;
            // if(b.x > a.x)
            // {
            //     return true;
            // }else
            // {
            //     return false;
            // }

        }else
        {
            return false;
        }

    }

#pragma endregion

#pragma region SEARCH_FOR_LEFT

    int CustomStatus(DCELEdge* e, DCELVec* vi)
    {

        vec2 a = e->origin->vertex;
        vec2 b = vi->vertex;

        if((a.y == b.y) && (a.x == b.x))
        {
            return 0;
        }

        return (a.y > b.y) ? 2 : (a.y == b.y) && (a.x < b.x) ?  2 : 1;

    }

    DCELEdge* SearchForLeft(DCELVec* vi, RBTree<DCELEdge*>& T)
    {
        
        RBNode<DCELEdge*>* Search = T.root;

        while(Search != nullptr)
        {
            
            int SearchStatus = CustomStatus(Search->val, vi);

            if(SearchStatus == 0)
            {
                break;
            }else if(SearchStatus == 1)
            {
                Search = Search->left;
            }else
            {
                Search = Search->right;
            }


        }

        if(Search == nullptr)
        {
            return nullptr;
        }

        return Search->left->val;
    }

#pragma endregion

#pragma region VERTEX_HANDLING

    void HandleStartVertex(DCELVec* vi, RBTree<DCELEdge*>& T, std::unordered_map<DCELEdge*, DCELVec*>& helper, DCEL& D)
    {
        DCELEdge* ei = vi->incident;
        helper.insert({ei,vi});
        T.insert(ei);
    }

    void HandleEndVertex(DCELVec* vi, RBTree<DCELEdge*>& T, std::unordered_map<DCELEdge*, DCELVec*>& helper, DCEL& D)
    {
        DCELEdge* eimo = vi->incident->prev;
        std::unordered_map<DCELEdge *, DCELVec *>::iterator helperpath = helper.find(eimo);
        if(helperpath != helper.end())
        {
            int vertexType = VertexType(helperpath->second);
            if(vertexType == MergeVertex)
            {
                DCELEdge* Diagonal = new DCELEdge(vi);
                Diagonal->next = helperpath->first;

                D.edges.push_back(Diagonal);
            }
        }
        T.remove(eimo);
    }

    void HandleSplitVertex(DCELVec* vi, RBTree<DCELEdge*>& T, std::unordered_map<DCELEdge*, DCELVec*>& helper, DCEL& D)
    {
        DCELEdge* ej = SearchForLeft(vi, T);
        std::unordered_map<DCELEdge *, DCELVec *>::iterator helperpath = helper.find(ej);
        if(helperpath != helper.end())
        {
            DCELEdge* Diagonal = new DCELEdge(vi);
            Diagonal->next = helperpath->first;

            D.edges.push_back(Diagonal);
        }

        helper[ej] = vi;

    }

    void HandleMergeVertex(DCELVec* vi, RBTree<DCELEdge*>& T, std::unordered_map<DCELEdge*, DCELVec*>& helper, DCEL& D)
    {

        DCELEdge* eimo = vi->incident->prev;
        std::unordered_map<DCELEdge *, DCELVec *>::iterator helperpath = helper.find(eimo);
        if(helperpath != helper.end())
        {
            int vertexType = VertexType(helperpath->second);
            if(vertexType == MergeVertex)
            {
                DCELEdge* Diagonal = new DCELEdge(vi);
                Diagonal->next = helperpath->first;

                D.edges.push_back(Diagonal);
            }
        }
        T.remove(eimo);

        DCELEdge* ej = SearchForLeft(vi, T);
        helperpath = helper.find(ej);
        if(helperpath != helper.end())
        {
            int vertexType = VertexType(helperpath->second);
            if(vertexType == MergeVertex)
            {
                DCELEdge* Diagonal = new DCELEdge(vi);
                Diagonal->next = helperpath->first;

                D.edges.push_back(Diagonal);
            }
        }

        helper[ej] = vi;


    }

    void HandleRegularVertex(DCELVec* vi, RBTree<DCELEdge*>& T, std::unordered_map<DCELEdge*, DCELVec*>& helper, DCEL& D)
    {
        bool AlternativeCase = false;
        if(InteriorToTheRight(vi))
        {
            DCELEdge* eimo = vi->incident->prev;
            std::unordered_map<DCELEdge*, DCELVec*>::iterator found = helper.find(eimo);
            if(found != helper.end())
            {
                if(VertexType(found->second) == MergeVertex)
                {
                    DCELEdge* Diagonal = new DCELEdge(vi);
                    Diagonal->next = found->first;
                    D.edges.push_back(Diagonal);

                    T.remove(eimo);
                    T.insert(vi->incident);
                    helper[vi->incident] = vi;

                }else
                {
                    AlternativeCase = true;
                }
                
            }else
            {
                AlternativeCase = true;
            }

            if(AlternativeCase == true)
            {
                DCELEdge* ej = SearchForLeft(vi, T);

                if(ej == nullptr)
                {
                    return;
                }
                std::unordered_map<DCELEdge*, DCELVec*>::iterator found = helper.find(ej);

                if(found != helper.end())
                {

                    if(VertexType(found->second) == MergeVertex)
                    {
                        DCELEdge* Diagonal = new DCELEdge(vi);
                        Diagonal->next = found->first;
                        D.edges.push_back(Diagonal);
                    }
                }

            }




        }


    }





#pragma endregion




int YPriority(DCELVec* A, DCELVec* B)
{
    vec2 a = A->vertex;
    vec2 b = B->vertex;

    if(a.y > b.y)
    {
        return 2;
    }else if(a.y == b.y)
    {
        if(a.x < b.x)
        {
            return 2;
        }
        return 0;
    }else
    {
        return 1;
    }
}

int YPriorityStatus(DCELEdge* A, DCELEdge* B)
{
    vec2 a = A->origin->vertex;
    vec2 b = B->origin->vertex;

    return (a.y > b.y) ? 2 : (a.y == b.y) && (a.x < b.x) ?  2 : 1;
}


void MakeMonotone(DCEL& SimplePolygon)
{

    bool IsMonotone = true;

    HeapArray<DCELVec*> Q(YPriority);
    for(int i = 0; i < SimplePolygon.verticies.size(); i++)
    {
        Q.push(SimplePolygon.verticies[i]);
    }
    
    DCELVec* vi = nullptr;

    RBTree<DCELEdge*> T(YPriorityStatus);

    std::unordered_map<DCELEdge*, DCELVec*> helper;

    while(!Q.empty())
    {
        vi = Q.extractMax();
        vi->render();
        int vertexType = VertexType(vi);

        if(IsTurnVertex(vi) && vertexType != -1)
        {
            if(vertexType == StartVertex)
            {
                IsMonotone == false;
                HandleStartVertex(vi, T, helper, SimplePolygon);
            }else if(vertexType == SplitVertex)
            {
                IsMonotone == false;
                HandleSplitVertex(vi, T, helper, SimplePolygon);
            }else if(vertexType == EndVertex)
            {
                IsMonotone == false;
                HandleEndVertex(vi, T, helper, SimplePolygon);
            }else if(vertexType == MergeVertex)
            {
                IsMonotone == false;
                HandleEndVertex(vi, T, helper, SimplePolygon);
            }
        }else
        {
            HandleRegularVertex(vi, T, helper, SimplePolygon);
        }

        


    }

    printf("This polygon is monotone = %d\n", IsMonotone);
    //Should not contain horizontal line segments


}


#endif