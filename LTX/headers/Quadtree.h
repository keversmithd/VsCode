#ifndef QUAD_TREE_H
#define QUAD_TREE_H

#include "QuadtreeHead.h"
#include "Deque.hpp"

template<typename T>
struct Quadtree
{
private:
    LTXRect BoundingArea;
    Quadtree<T>* children[4];
    std::vector<T> data;
    
public:

    Quadtree(LTXRect boundingArea) : BoundingArea(boundingArea)
    {
        children[0] = nullptr;
        children[1] = nullptr;
        children[2] = nullptr;
        children[3] = nullptr;
    }

    void insert(T value, LTXRect boundingArea)
    {

        if(ContainedInBoundingArea(boundingArea, BoundingArea))
        {
            std::vector<Quadrant> IntersectedQuadrants = QuadrantsIntersected(boundingArea, BoundingArea);

            for(int i = 0; i < IntersectedQuadrants.size(); i++)
            {
                int quadrantId = IntersectedQuadrants[i].quadrantId;

                if(children[quadrantId] == nullptr)
                {
                    children[quadrantId] = new Quadtree<T>(IntersectedQuadrants[i].boundingArea);
                }else
                {
                    //place this item in this node
                    children[quadrantId]->insert(value, boundingArea);
                }
                
            }
        }
    }

    T findClosest(LTXPoint query)
    {
        
        int quadrantOfPoint = QuadrantOfPoint(query, BoundingArea);


        if(quadrantOfPoint != 0)
        {
            if(children[quadrantOfPoint] == nullptr)
            {
                


            }else
            {
                children[quadrantOfPoint]->findClosest(query);
            }


        }
        

    }

    void removal(T value, LTXRect boundingArea)
    {

        if(ContainedInBoundingArea(boundingArea, BoundingArea))
        {
            std::vector<Quadrant> IntersectedQuadrants = QuadrantsIntersected(boundingArea, BoundingArea);

            for(int i = 0; i < IntersectedQuadrants.size(); i++)
            {
                int quadrantId = IntersectedQuadrants[i].quadrantId;

                if(children[quadrantId] != nullptr)
                {
                    //children[quadrantId] = new Quadtree<T>(IntersectedQuadrants[i].boundingArea);

                    //find and remove inside of vector

                    children[quadrantId]->removal(value, boundingArea);

                }
                
            }
        }

    }

    void del(Quadtree<T>* n)
    {
        if(n == nullptr)
        {
            return;
        }

        del(n->children[0]);
        del(n->children[1]);
        del(n->children[2]);
        del(n->children[3]);

        delete n;

    }


    ~Quadtree()
    {
        //del(this);
    }

};


#endif