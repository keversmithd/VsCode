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
    bool Leaf;
    
public:

    Quadtree(LTXRect boundingArea) : BoundingArea(boundingArea), Leaf(true)
    {
        children[0] = nullptr;
        children[1] = nullptr;
        children[2] = nullptr;
        children[3] = nullptr;
    }

    void redistribute()
    {
        for(int i = 0; i < data.size(); i++)
        {
            insert(data[i], data[i].Bounding());
        }
        Leaf = false;
        data.clear();
    }

    void insert(T value, LTXRect boundingArea)
    {
        //boundingArea.Display();
        if(ContainedInBoundingArea(boundingArea, BoundingArea))
        {
            std::vector<Quadrant> IntersectedQuadrants = QuadrantsIntersected(boundingArea, BoundingArea);

            for(int i = 0; i < IntersectedQuadrants.size(); i++)
            {
                int quadrantId = IntersectedQuadrants[i].quadrantId;

                if(children[quadrantId] == nullptr)
                {
                    children[quadrantId] = new Quadtree<T>(IntersectedQuadrants[i].boundingArea);
                    children[quadrantId]->data.push_back(value);
                }else
                {
                    if(children[quadrantId]->Leaf && children[quadrantId]->data.size() < 1)
                    {
                        children[quadrantId]->data.push_back(value);

                    }else if(children[quadrantId]->Leaf)
                    {
                        children[quadrantId]->redistribute();
                        children[quadrantId]->insert(value, boundingArea);
                    }
                    
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

    void Display()
    {
        BoundingArea.Display();

        for(int i = 0; i < data.size(); i++)
        {
            data[i].Display();
        }
        for(int i = 0; i < 4; i++)
        {
            if(children[i] != nullptr)
            {
                children[i]->Display();
            }
        }
    }


    ~Quadtree()
    {
        //del(this);
    }

};


#endif