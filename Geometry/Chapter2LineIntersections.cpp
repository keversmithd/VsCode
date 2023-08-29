#include <iostream>

#include <random>
#include "CGRead.h"
#include "PqueArray.hpp"
#include "ran.hpp"
#include "AVLBALANCE.hpp"
#include "StatusStructure.hpp"
#include "LIEventPoint.hpp"
#include <unordered_map>
#include <map>
#include <set>

struct StatusSegment
{
    line whole;
};

#pragma region OLD_COMPARE

bool EdgeCompare(const EventPoint A, const EventPoint B)
{
    return (A.part.y > B.part.y);
}

line* EdgeSetInPlane(const plane pl, int I)
{
    line* edges = new line[I];
    std::uniform_real_distribution<float> leftRight(pl.bottomLeft.x, pl.topRight.x);
    std::uniform_real_distribution<float> downUp(pl.bottomLeft.y, pl.topRight.y);
    line lineBuffer;
    float lr = leftRight(mt);
    float du = downUp(mt);

    float lr1 = leftRight(mt);
    float du1 = downUp(mt);
    for(int i = 0; i < I; i++)
    {
        lr = leftRight(mt);
        du = downUp(mt);

        lr1 = leftRight(mt);
        du1 = downUp(mt);

        if(du > du1)
        {
            lineBuffer.start = {lr, du};
            lineBuffer.end = {lr1, du1};
        }else
        {
            lineBuffer.start = {lr1, du1};
            lineBuffer.end = {lr, du};
        }

        
        edges[i] =  lineBuffer;

    }
    return edges;

}

EventPoint* edgeToEventPoints(line* edges, int N)
{
    EventPoint* events = new EventPoint[N*2];
    EventPoint A,B;
    line EdgePlacement;
    int EventPointer = 0;
    for(int i = 0; i < N; i++)
    {
        EdgePlacement = edges[i];
        A.whole = EdgePlacement;
        A.part = EdgePlacement.start;
        events[EventPointer++] = A;
        B.whole = EdgePlacement;
        B.part = EdgePlacement.end;
        events[EventPointer++] = B;
    }

    return events;


}

int eventcompare(const EventPoint p, const EventPoint q)
{
    if (p.part.y > q.part.y)
    {
        return -1;
    }
    else if (p.part.y < q.part.y)
    {
        return 1;
    }
    else
    {
        // if(p.part.x < q.part.y)
        // {
        //     return -1;
        // }
        // else if(p.part.x > q.part.y)
        // {
        //     return 1;
        // }

        return 0;
    }
        
} 

int statuscompare(const EventPoint p, const EventPoint q, float sweepLineY)
{
    line A = p.whole;
    line B = q.whole;

    vec2 AV = {A.end.x - A.start.x, A.end.y - A.start.y};
    vec2 BV = {B.end.x - B.start.x, B.end.y - B.start.y};

    float At = (sweepLineY - A.start.y)/AV.y;
    float Bt = (sweepLineY - B.start.y)/BV.y;

    float AA = A.start.x + At*AV.x;
    float BB = B.start.x + Bt*BV.x;

    float Ax = A.start.y + At*AV.y;
    float Bx = B.start.y + Bt*BV.y;

    if(AA < BB)
    {
        return -1;
    }
    else if (AA > BB)
    {
        return 1;
    }else
    {
       return 0;
    }

    return 0;
    
}

int equalityCompare(const EventPoint a, const EventPoint b)
{
    
    return ((a.whole.start == b.whole.start) && (a.whole.end == b.whole.end));
}

bool interiorCompare(const line a, const vec2 b)
{
    vec2 aV = {a.end.x - a.start.x, a.end.y - a.start.y};
    vec2 t = {(b.x - a.start.x)/aV.x, (b.y - a.start.y)/aV.y};
    if(t.x > 0 && t.x < 1 && t.y > 0 && t.y < 1)
    {
        return true;
    }

    return false;
}

bool IsUpperEndPoint(const EventPoint X)
{
    return (X.part.x == X.whole.start.x && X.part.y == X.whole.start.y);
}

#pragma endregion



std::vector<EventPoint> FindIntersectionNonDegenerate(line* edges, int N)
{
    EventPoint* EventPoints = edgeToEventPoints(edges, (N*2));
    sb_tree<EventPoint, vec2, line> T(statuscompare, equalityCompare, interiorCompare);
    avl_tree<EventPoint> Q(eventcompare);

    for(int i = 0; i < (N*2); i++)
    {   
        Q.insert(EventPoints[i]);
    }

    std::map<vec2, EventPoint> IntersectionList;

    while(!Q.empty())
    {
        EventPoint nextEventPoint = Q.removeTop();

        printf("New Node\n");
        SpellPoint(nextEventPoint.part);
        printf("\n");

        if(IsUpperEndPoint(nextEventPoint))
        {
            T.insertCheckAdjacent(nextEventPoint, IntersectionList);
        }else
        {
            T.remove(nextEventPoint, IntersectionList);
        }
        
    }


    for(auto it = IntersectionList.begin(); it != IntersectionList.end(); ++it)
    {
        SpellPoint(it->first);
    }


}

int EventQueueCompares(EventPoint p, EventPoint q)
{
    if (p.part.y > q.part.y)
    {
        return -1;
    }
    else if (p.part.y < q.part.y)
    {
        return 1;
    }
    else
    {
        if(p.part.x < q.part.y)
        {
            return -1;
        }
        else if(p.part.x > q.part.y)
        {
            return 1;
        }
    }

    return 0;

}

std::vector<vec2> FindIntersectionsBook(line* edges, int N)
{
    EventPoint* EventPoints = edgeToEventPoints(edges, (N*2));
    avl_tree<EventPoint> Q(eventcompare);
    //avl_tree<EventPoint> T()
    for(int i = 0; i < (N*2); i++)
    {   
        Q.insert(EventPoints[i]);
    }
    while(!Q.empty())
    {
        EventPoint T = Q.peek();



        Q.removeTop();


    }

} 



int main()
{

    plane Domain = {{-5.0, -1.0}, {10.0, 1.0}};

    const int NumberOfLines = 5;

    line* EdgeSetRailroads = EdgeSetInPlane(Domain, NumberOfLines);
    DisplayEdgeSet(EdgeSetRailroads, NumberOfLines);
    
    FindIntersectionNonDegenerate(EdgeSetRailroads, NumberOfLines);
    


    


    

    
    
    return -1;
    

}