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
    rect BoundingContainer;
    int id;

    bool CounterClockwise;
    vec2 Origin;

    DCEL() : CounterClockwise(false), id(-1)
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
                if(Back->origin->vertex.x == p.x && Back->origin->vertex.y == p.y)
                {
                    return;
                }
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
                verticies.push_back(V->origin);
                edges.push_back(E);
                edges.push_back(V);
            }else
            {
                DCELEdge* Back = edges.back();
                if(Back->origin->vertex.x == p.x && Back->origin->vertex.y == p.y)
                {
                    return;
                }
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
                verticies.push_back(V->origin);
                edges.push_back(E);
                edges.push_back(V);
            }

            
        }



    }
    void MakeLoop()
    {
        edges.back()->next = edges[0];
        edges[0]->prev = edges.back();
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

            SpellEdge(origin, destination);

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
    void NextDisplay()
    {
        
        DCELEdge* Prev = nullptr;
        DCELEdge* Next = edges[0];
        DCELEdge* Origin = Next;
        while(Next != Prev && Next != nullptr && Next->next != nullptr)
        {
            SpellEdge(Next->origin->vertex, Next->next->origin->vertex);
            Prev = Next;
            Next = Next->next;

            if(Next == Origin)
            {
                break;
            }
            
        }

    }

    //Methods for traversing DCEL given it has internal more than one disconnected faces.
    DCELEdge* AppendingEdge = nullptr; //Edge to append to.
    DCELFace* ActiveFace = nullptr; //Currently selected face.
    
    void FaceExtraAppendPoint(vec2 p)
    {

        if(p.x == -69 && p.y == -69)
        {
            MakeLoopOnActiveFace();
            AppendingEdge = nullptr;
            return;
        }

        if(AppendingEdge == nullptr)
        {
            //Create a new face,edge,etc
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

            AppendingEdge = NewEdge;
            ActiveFace = NewFace;

            ActiveFace->verticesStart = verticies.size()-1;
            ActiveFace->edgesStart = edges.size()-1;
            ActiveFace->vertices = 1;
            ActiveFace->edges = 1;

            ActiveFace->incident = NewEdge;

            NewEdge->incident = NewFace;



        }else if(ActiveFace->vertices == 1)
        {
            
            DCELVec* NextVertex = new DCELVec(p);
            DCELVec* TwinVertex = new DCELVec(p);

            DCELEdge* NextEdge = new DCELEdge(NextVertex);
            DCELEdge* TwinEdge = new DCELEdge(TwinVertex);

            NextVertex->incident = NextEdge;
            TwinVertex->incident = TwinEdge;

            NextEdge->incident = ActiveFace;
            TwinEdge->incident = ActiveFace;

            AppendingEdge->next = NextEdge;
            AppendingEdge->next->prev = AppendingEdge;

            AppendingEdge->twin = TwinEdge;
            //NextEdge->twin->next = AppendingEdge

            AppendingEdge = NextEdge;

            verticies.push_back(NextVertex);
            edges.push_back(NextEdge);

            ActiveFace->vertices += 1;
            ActiveFace->edges += 1;



        }else
        {
            DCELVec* NextVertex = new DCELVec(p);
            DCELVec* TwinVertex = new DCELVec(p);


            DCELEdge* NextEdge = new DCELEdge(NextVertex);
            DCELEdge* TwinEdge = new DCELEdge(TwinVertex);

            NextVertex->incident = NextEdge;
            TwinVertex->incident = TwinEdge;

            NextEdge->incident = ActiveFace;
            TwinEdge->incident = ActiveFace;

            AppendingEdge->next = NextEdge;
            AppendingEdge->next->prev = AppendingEdge;

            AppendingEdge->twin = TwinEdge;
            AppendingEdge->twin->next = AppendingEdge->prev->twin;

            AppendingEdge->prev->twin->prev = TwinEdge;

            verticies.push_back(NextVertex);
            edges.push_back(NextEdge);

            ActiveFace->vertices += 1;
            ActiveFace->edges += 1;

            AppendingEdge = NextEdge;

        }


    }

    void MakeLoopOnActiveFace()
    {

        DCELEdge* StartEdge = edges[ActiveFace->edgesStart];
        DCELEdge* EndEdge = edges[(ActiveFace->edgesStart + ActiveFace->edges)-1];
        DCELEdge* MinusOne = edges[(ActiveFace->edgesStart)+ActiveFace->edges-2];

        DCELEdge* NextTwinEdge = new DCELEdge(StartEdge->origin->vertex);
        NextTwinEdge->next = MinusOne->twin;
        NextTwinEdge->prev = StartEdge->twin;
        EndEdge->twin = NextTwinEdge;
        
        StartEdge->twin->next = NextTwinEdge;

        EndEdge->next = StartEdge;
        StartEdge->prev = EndEdge;
    }

    void DCELTopologyToLatex()
    {
        
        for(int f = 1; f < faces.size(); f++)
        {
            DCELEdge* IncidentEdge = faces[f]->incident;
            DCELEdge* OriginEdge = IncidentEdge;

            printf("\n");

            while(IncidentEdge->next != nullptr && IncidentEdge->next != OriginEdge)
            {
                vec2 NextOrigin = IncidentEdge->origin->vertex;
                vec2 NextDestination = IncidentEdge->next->origin->vertex;

                vec2 DeltaNext = {NextDestination.x - NextOrigin.x, NextDestination.y - NextOrigin.x};
                vec2 NormalNext = {-DeltaNext.y, DeltaNext.x};

                printf("\\draw[fill=black] (%f,%f) circle (0.5pt);\n", NextOrigin.x, NextOrigin.y);
                printf("\\draw[fill=black] (%f,%f) circle (0.5pt);\n", NextDestination.x, NextDestination.y);
                printf("\\draw[->] (%f,%f) -- (%f,%f);\n", NextOrigin.x, NextOrigin.y, NextDestination.x, NextDestination.y);

                float innerSeperation = 0.1;
                float normalM = sqrt(NormalNext.x*NormalNext.x + NormalNext.y*NormalNext.y);
                vec2 TwinOrigin = IncidentEdge->twin->origin->vertex;
                TwinOrigin.x += innerSeperation*(NormalNext.x/normalM);
                TwinOrigin.y += innerSeperation*(NormalNext.y/normalM);
                vec2 TwinDestination = IncidentEdge->twin->next->origin->vertex;
                TwinDestination.x += innerSeperation*(NormalNext.x/normalM);
                TwinDestination.y += innerSeperation*(NormalNext.y/normalM);

                printf("\\draw[fill=black] (%f,%f) circle (0.1pt);\n", TwinOrigin.x, TwinOrigin.y);
                printf("\\draw[fill=black] (%f,%f) circle (0.1pt);\n", TwinDestination.x, TwinDestination.y);
                printf("\\draw[->] (%f,%f) -- (%f,%f);\n", TwinOrigin.x, TwinOrigin.y, TwinDestination.x, TwinDestination.y);

                IncidentEdge=IncidentEdge->next;

            }
        
        }

        

    }

    ~DCEL()
    {

    }
};









#endif