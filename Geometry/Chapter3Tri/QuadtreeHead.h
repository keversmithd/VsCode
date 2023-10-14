#ifndef QUAD_TREE_HEAD_H
#define QUAD_TREE_HEAD_H


#include <vector>

#include "../vectwo.hpp"

bool ContainedInBoundingArea(const rect Subject, const rect Area)
{
    return ((Subject.bottomLeft.x >= Area.bottomLeft.x && Subject.bottomLeft.x <= Area.topRight.x) &&
    (Subject.bottomLeft.y >= Area.bottomLeft.y && Subject.bottomLeft.y <= Area.topRight.y));
}

bool IntersectsBoundingArea(const rect Subject, const rect Area)
{

    return ((Subject.bottomLeft.x >= Area.bottomLeft.x) && (Subject.bottomLeft.x <= Area.topRight.x) || (Subject.topRight.x >= Area.bottomLeft.x) && (Subject.bottomLeft.x <= Area.topRight.x)) 
    && ((Subject.bottomLeft.y >= Area.bottomLeft.y) && (Subject.bottomLeft.y <= Area.topRight.y) || (Subject.topRight.y >= Area.bottomLeft.y) && (Subject.bottomLeft.y <= Area.topRight.y));

}

struct Quadrant
{
    rect boundingArea;
    int quadrantId;
};

std::vector<Quadrant> QuadrantsIntersected(const rect Subject, const rect Area)
{
    std::vector<Quadrant> TheVector;


    vec2 MidPoint;
   
    MidPoint.x = Area.bottomLeft.x + ((Area.topRight.x - Area.bottomLeft.x)/2);
    MidPoint.y = Area.bottomLeft.y + ((Area.topRight.y - Area.bottomLeft.y)/2);


    rect BottomLeft = {{Area.bottomLeft.x, Area.bottomLeft.y}, {MidPoint.x, MidPoint.y}};
    //BottomLeft.Display();
    rect TopLeft = {{Area.bottomLeft.x, MidPoint.y}, {MidPoint.x, Area.topRight.y}};
    //TopLeft.Display();
    rect BottomRight = {{MidPoint.x, Area.bottomLeft.y}, {Area.topRight.x, MidPoint.y}};
    //BottomRight.Display();
    rect TopRight = {{MidPoint.x, MidPoint.y}, {Area.topRight.x, Area.topRight.y}};
    //TopRight.Display();


    if(IntersectsBoundingArea(Subject, BottomLeft))
    {
        TheVector.push_back({BottomLeft, 0});
    }
    if(IntersectsBoundingArea(Subject, TopLeft))
    {
        TheVector.push_back({TopLeft, 3});
    }
    if(IntersectsBoundingArea(Subject, BottomRight))
    {
        TheVector.push_back({BottomRight, 1});
    }
    if(IntersectsBoundingArea(Subject, TopRight))
    {
        TheVector.push_back({TopRight, 2});
    }

    return TheVector;


}





#endif