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

    std::vector<DCELEdge*> InnerComponents;
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
};

struct DCELEdge
{
    DCELEdge* twin; 
    DCELFace* face; //index
    DCELEdge* next; //index
    DCELEdge* prev; //index
    DCELVec* origin; //index


    DCELEdge() : twin(nullptr), face(nullptr), next(nullptr), prev(nullptr), origin(nullptr)
    {

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