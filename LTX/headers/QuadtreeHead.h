#ifndef QUAD_TREE_HEAD_H
#define QUAD_TREE_HEAD_H

#include  "LTXStructures.h"
#include <vector>





struct Quadrant
{
    LTXRect boundingArea;
    int quadrantId;
};

std::vector<Quadrant> QuadrantsIntersected(const LTXRect Subject, const LTXRect Area)
{
    std::vector<Quadrant> TheVector;

    LTXPoint MidPoint;
    MidPoint.x = Area.bottomLeft.x + ((Area.topRight.x - Area.bottomLeft.x)/2);
    MidPoint.y = Area.bottomLeft.y + ((Area.topRight.y - Area.bottomLeft.y)/2);


    LTXRect BottomLeft = {{Area.bottomLeft.x, Area.bottomLeft.x}, {MidPoint.x, MidPoint.y}};

    LTXRect TopLeft = {{Area.bottomLeft.x, MidPoint.y}, {MidPoint.x, Area.topRight.y}};

    LTXRect BottomRight = {{MidPoint.x, Area.bottomLeft.y}, {Area.topRight.x, MidPoint.y}};

    LTXRect TopRight = {{MidPoint.x, MidPoint.y}, {Area.topRight.x, Area.topRight.y}};


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

int QuadrantOfPoint(const LTXPoint Subject, const LTXRect Area)
{
    LTXPoint MidPoint;
    MidPoint.x = Area.bottomLeft.x + ((Area.topRight.x - Area.bottomLeft.x)/2);
    MidPoint.y = Area.bottomLeft.y + ((Area.topRight.y - Area.bottomLeft.y)/2);
    if(ContainedInBoundingArea(Subject, Area))
    {
        //1 bottom left: 2 bottom right: 3: top left, 4: top right
        return 1*(Subject.x < MidPoint.x) + 2*(Subject.x > MidPoint.x) + 2*(Subject.y > MidPoint.y);
    }
    
    return 0;
}



#endif