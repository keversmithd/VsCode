#ifndef DECL_H
#define DECL_H


#include <list>
#include <vector>
#include "Deque.hpp"
#include "RBTree.h"
#include "RBStatus.hpp"
#include "DCELIntersection.hpp"




struct DCEL
{
    std::vector<DCELVec*> verticies;
    std::vector<DCELEdge*> edges;
    std::vector<DCELFace*> faces;

    DCEL()
    {

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

    void LineIntersection()
    {
        RBTree<DCELVec*> Q(VerticleArrangement);
        RBSTree<DCELEdge*> T(PlanarArrangement);

        std::vector<Vec> IntersectionPoints;

        for(int i = 0; i < verticies.size(); i++)
        {
            Q.insert(verticies[i]);
        }

        while(!Q.empty())
        {
            DCELVec* QueuePoint = Q.removeTop();
            
            if(IsUpperEndPoint(QueuePoint))
            {
                T.insert(QueuePoint->incident, QueuePoint->vertex.y);
            }else
            {
                T.remove(QueuePoint->incident->twin);
            }
            

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

    ~DCEL()
    {

    }
};




DCEL OverlayOfTwoSubdivisions(DCEL graph1, DCEL graph2)
{
    RBTree<DCELVec*> Q(VerticleArrangement);
    RBSTree<DCELEdge*> T(PlanarArrangement);

    std::vector<Vec> IntersectionPoints;

    graph1.insert(graph2);


    for(int i = 0; i < graph1.verticies.size(); i++)
    {
        Q.insert(graph1.verticies[i]);
    }

    
    while(!Q.empty())
    {
        DCELVec* QueuePoint = Q.removeTop();
        //if event point involves edges only one of the sets
        //other wise we must link the edges by the intersection point
        
        if(IsUpperEndPoint(QueuePoint))
        {
            T.insert(QueuePoint->incident, QueuePoint->vertex.y);
        }else
        {
            T.remove(QueuePoint->incident->twin);
        }
        
    }
}





#endif