#ifndef DECL_H
#define DECL_H


#include <list>
#include <vector>
#include "AccurateStatusModel.h"
#include "../Deque.hpp"
#include "../RBTree.h"
#include "../linearprobe.hpp"
#include "../CGRead.h"
#include "StableArray.h"

struct DCEL
{
    std::vector<DCELVec*> verticies;
    std::vector<DCELEdge*> edges;
    std::vector<DCELFace*> faces;
    
    int id;

    DCEL()
    {

    }

    void AddEdgeExpanded(vec2 a, vec2 b)
    {

        DCELFace* F;


        DCELVec* A;
        DCELVec* B;
        int verticiesSize = verticies.size();

        //alternative would to be to search through each face, and see if this is continuing a previous face, which could be sped up by, updating the incident edge of each face to be the last edge inserted onto it.
        if(verticiesSize > 0 && b == verticies[verticiesSize-1]->vertex)
        {
            A = verticies[verticiesSize-1];
            F = faces.back();
        }else
        {
            DCELVec* A = new DCELVec(a);
            F = new DCELFace();
            faces.push_back(F);
        }

        B = new DCELVec(b);

        int edgeSize = edges.size();

        if(edgeSize > 2)
        {
            DCELEdge* ForwardEdge = edges[edgeSize-2];
            vec2 PreviousVector = ForwardEdge->Vector();
            vec2 CurrentVector = b-a;

            if(cross(CurrentVector, PreviousVector) < 0)
            {
                
            }



        }


    }

    void AddEdge(vec2 a, vec2 b)
    {
        DCELFace* F;

        if(faces.size() == 0 || (edges.back() != nullptr && a != edges.back()->twin->origin->vertex || b == edges.back()->origin->vertex))
        {
            F = new DCELFace();
            faces.push_back(F);
        }else{
            F = faces.back();
        }
        
        DCELVec* A = new DCELVec();
        A->vertex = a;
        
        DCELVec* B = new DCELVec();
        B->vertex = b;

        DCELEdge* AB = new DCELEdge();
        A->incident = AB;
        AB->origin = A;
        AB->face = F;
        AB->next = nullptr;

        DCELEdge* BA = new DCELEdge();
        B->incident = BA;
        BA->origin = B;
        BA->face = F;
        BA->next = nullptr;

        AB->twin = BA;
        BA->twin = AB;

        DCELEdge* back = nullptr;
        DCELEdge* backTwin = nullptr;
        DCELEdge* backback = nullptr;

        if(edges.size() > 0)
        {
            back = edges.back();

            if(back != nullptr)
            {
                backTwin = back->twin;
                back->prev = BA;
            }

            
            AB->prev = backTwin;
            BA->next = back;

            if(backTwin != nullptr)
            {
                backTwin->next = AB;
            }

            if(b == edges[0]->origin->vertex)
            {
                AB->next = edges[0];
                edges[0]->prev = AB;
                edges[0]->twin->next = BA;
                
            }
        }   

        verticies.push_back(A);
        verticies.push_back(B);

        edges.push_back(AB);
        edges.push_back(BA);
        
        

        F->incident = AB;
    }
    
    DCELEdge* NewOriginEdge(vec2 p)
    {
        DCELEdge* NewEdge = new DCELEdge();
        DCELVec* NewVert = new DCELVec();

        NewVert->incident = NewEdge;
        NewVert->vertex = p;

        NewEdge->origin = NewVert;
        NewEdge->next = nullptr;
        NewEdge->prev = nullptr;
        NewEdge->twin = nullptr;
        NewEdge->face = faces.back();

        return NewEdge;
    }
    
    void AppendPoint(vec2 p)
    {   
        if(faces.size() == 0) //if this is a new face
        {
            DCELFace* NewFace = new DCELFace();
            DCELEdge* NewEdge = new DCELEdge();
            DCELVec* NewVert = new DCELVec();

            NewVert->incident = NewEdge;
            NewVert->vertex = p;

            NewEdge->origin = NewVert;
            NewEdge->next = nullptr;
            NewEdge->prev = nullptr;
            NewEdge->twin = nullptr;
            NewEdge->face = NewFace;

            verticies.push_back(NewVert);
            edges.push_back(NewEdge);
            faces.push_back(NewFace);
        }else
        {   
            
            if(edges.size() == 1)
            {
                DCELEdge* Back = edges.back();
                DCELEdge* Psuedoback = NewOriginEdge(Back->origin->vertex);
                DCELEdge* V = NewOriginEdge(p);
                DCELEdge* E = NewOriginEdge(p);

                Back->next = V;
                V->prev = Back;

                E->next = Psuedoback;
                Psuedoback->prev = E;

                Back->twin = E;
                E->twin = Back;

                edges.push_back(Psuedoback);
                edges.push_back(E);
                edges.push_back(V);
            }else
            {
                DCELEdge* Back = edges.back();
                int BackIndex = edges.size()-2;
                DCELEdge* Twinback = edges[BackIndex];

                DCELEdge* E = NewOriginEdge(p);
                DCELEdge* V = NewOriginEdge(p);

                Back->next = V;
                V->prev = Back;

                E->next = Twinback;
                Twinback->prev = E;

                Back->twin  = E;
                E->twin = Back;
                
                edges.push_back(E);
                edges.push_back(V);
            }

            
        }
    }

    void VisitAllEdgesIncidentToVertex(DCELVec* vert)
    {
        DCELEdge* incident = vert->incident;
        DCELEdge* startingEdge = incident;
        //just all incident edges and twins?

        while(incident != nullptr && incident != startingEdge)
        {
            incident = incident->next->twin;
        }
    }

    void WalkAroundFace(DCELFace* face)
    {
        DCELEdge* next = face->incident;
        DCELEdge* startingEdge = next;
        while(next != nullptr && next != startingEdge)
        {
            next = next->next;
        }
    }

    void insert(DCEL GraphStructure)
    {
        for(int i = 0; i < GraphStructure.verticies.size(); i++)
        {
            verticies.push_back(GraphStructure.verticies[i]);
        }

        for(int i = 0; i < GraphStructure.edges.size(); i++)
        {
            edges.push_back(GraphStructure.edges[i]);
        }

        for(int i = 0; i < GraphStructure.faces.size(); i++)
        {
            faces.push_back(GraphStructure.faces[i]);
        }


    }

    void traverse()
    {
        int PolygonSize = verticies.size();

        DCELEdge* iter = verticies[0]->incident;
        DCELEdge* origin = iter;

        while(iter != nullptr && iter->next != nullptr && iter->next != origin){
            iter->origin->render();
            iter->next->origin->render();
            iter = iter->next;
        }
    }

    void reverseTraverse()
    {
        DCELEdge* iter = edges[0];
        DCELEdge* origin = edges[0];

        while(iter != nullptr && iter->prev != nullptr && iter->prev != origin){
            iter->origin->render();
            iter->prev->origin->render();
            iter = iter->prev;
        }
    }


    void display()
    {
        DCELEdge* iter = edges[0];
        DCELEdge* origin = iter;

        if (iter == nullptr || iter->twin->origin == nullptr) {
            return;
        }

        rect thisBound;
        do
        {
            vec2 origin = iter->origin->vertex;
            vec2 destination = iter->twin->origin->vertex;

            thisBound.IncrementBound(origin);
            thisBound.IncrementBound(destination);

            SpellVector(origin, destination);

            iter = iter->next;
        } while (iter != nullptr && iter->twin != nullptr && iter->twin->origin != nullptr && iter != origin);
        
            
    }
    void SeeAllEdges()
    {
        for(int i = 0; i < edges.size(); i++)
        {
            edges[i]->DrawVector();
        }
    }


    ~DCEL()
    {

    }
};









#endif