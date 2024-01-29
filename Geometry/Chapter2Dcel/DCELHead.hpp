#ifndef DCEL_HEAD_H
#define DCEL_HEAD_H

#pragma region DCEL_HEAD

#include "../vectwo.hpp"
#include "../CGRead.h"

#include "DCELIntersection.hpp"

using Vec = vec2;

struct DCELEdge;

struct DCELFace
{
    DCELEdge* incident; //using a possible combination of indices, if possible

    DCELFace* internal; //link to internal face. could potentially be a vector but just one for now.
    DCELFace* external; //link to an external face if this is inside of a face.

    int verticesStart = 0;

    int edgesStart = 0;

    int vertices = 0;
    
    int edges = 0;

    int id = 0;

    std::vector<DCELEdge*> InnerComponents; //may use may not?

    DCELFace() : incident(nullptr), internal(nullptr), external(nullptr), verticesStart(0), edgesStart(0), vertices(0), edges(0)
    {
        
    }

};

struct DCELVec
{
    Vec vertex; //cannot remove correctly here.
    DCELEdge* incident;
    int id; 

    DCELVec(Vec _vertex) : vertex(_vertex), incident(nullptr)
    {

    }

    DCELVec() : incident(nullptr)
    {

    }


    bool operator >(DCELVec* v)
    {
        return vertex.hash() > v->vertex.hash();
    }
    bool operator <(DCELVec* v)
    {
        return vertex.hash() < v->vertex.hash();
    }
    bool operator !=(DCELVec* v)
    {
        return vertex.hash() != v->vertex.hash();
    }

    void render()
    {
        printf("\\draw (%f,%f) circle (2pt);\n", vertex.x, vertex.y);
    }
    void render(const char* name)
    {
        printf("\\draw (%f,%f) circle (2pt) node [anchor=east] {\\tiny %s};\n", vertex.x, vertex.y, name);
    }
};

struct DCELEdge
{
    DCELEdge* twin; 
    DCELFace* face; //index
    DCELEdge* next; //index
    DCELEdge* prev; //index
    DCELVec* origin; //index

    DCELFace* incident; //incident face


    DCELEdge() : twin(nullptr), face(nullptr), next(nullptr), prev(nullptr), origin(nullptr), incident(nullptr)
    {

    }

    DCELEdge(DCELVec* Origin) : twin(nullptr), face(nullptr), next(nullptr), prev(nullptr), origin(Origin), incident(nullptr)
    {

    }
    DCELEdge(Vec Origin) : twin(nullptr), face(nullptr), next(nullptr), prev(nullptr), origin(nullptr), incident(nullptr)
    {
        origin = new DCELVec(Origin);
    }       



    bool Contains(DCELVec* node)
    {
        Vec e = twin->origin->vertex - origin->vertex;
        Vec v = twin->origin->vertex - node->vertex;

        float d = cross(e,v);

        if(d == 0)
        {
            //contains
        }

        return false;
    }

    void DrawVector()
    {
        if(next != nullptr)
        {
            SpellVector(origin->vertex, next->origin->vertex);
        }
    }

    void display()
    {
        if(next != nullptr)
        {
            SpellEdge(origin->vertex, next->origin->vertex);
        }
    }

    Vec Vector()
    {
        if(next != nullptr)
        {
            return next->origin->vertex - origin->vertex;
        }else
        {
            return vec2(0,0);
        }
    }
};






#pragma end region





#endif