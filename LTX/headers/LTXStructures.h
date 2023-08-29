#ifndef LTX_STRUCT_H
#define LTX_STRUCT_H

#include "LTXPoint.h"
#include "LTXLineSegment.h"
#include "LTXVector.h"
#include "LTXCubicBezierCurve.h"
#include "LTXDeCasteljau.h"

struct Curve
{
    LTXCubicBezier Cubic;
    LTXQuadraticBezier Quadratic;
    int type;

    Curve(LTXQuadraticBezier quadratic) : Quadratic(quadratic), type(0)
    {

    }

    Curve(LTXCubicBezier cubic) : Cubic(cubic), type(1)
    {

    }

};



LTXPoint ProjectOnto(LTXPoint Position, LTXPoint Normal)
{
    LTXPoint Touch = Normal-Position;
    float Dot = Position.dot(Normal);
    float NM = Normal.mag();
    float NP = Position.mag();

    LTXPoint V = Dot/NM * Normal/NM;

    return Position + V;

}  

float ProjectPointToCurve(LTXPoint Subject, Curve Area)
{
    if(Area.type == 0)
    {
        LTXRect boundingArea = Area.Quadratic.BoundingRectangle();
        boundingArea.ReadNamed();

        LTXPoint bottomRight = {boundingArea.topRight.x, boundingArea.bottomLeft.y};
        LTXPoint topLeft = {boundingArea.bottomLeft.x, boundingArea.topRight.y};

        //0 case
        LTXPoint V0 = topLeft-boundingArea.bottomLeft;
        LTXPoint V1 = boundingArea.topRight - bottomRight;
        LTXPoint V2 = boundingArea.topRight - topLeft;
        LTXPoint V3 = bottomRight - boundingArea.bottomLeft;

        LTXPoint P0 = Subject.ProjectOnto(boundingArea.bottomLeft, topLeft);
        LTXPoint P1 = Subject.ProjectOnto(bottomRight, boundingArea.topRight);
        LTXPoint P2 = Subject.ProjectOnto(topLeft, boundingArea.topRight);
        LTXPoint P3 = Subject.ProjectOnto(boundingArea.bottomLeft, bottomRight);

        float d0 = (Subject-P0).mag();
        float d1 = (Subject-P1).mag();
        float d2 = (Subject-P2).mag();
        float d3 = (Subject-P3).mag();
        
        LTXPoint MinimumDistancePoint = P0;
        float MinimumDistance = d0;
        //Distance Flag : 0 for vertical edges, 1 for horizontal edges.
        int DistanceFlag = 0;
        if((d1 < MinimumDistance))
        {
            MinimumDistance = d1;
            MinimumDistancePoint = P1;
            DistanceFlag = 0;
        }
        if((d2 < MinimumDistance))
        {
            MinimumDistance = d2;
            MinimumDistancePoint = P2;
            DistanceFlag = 1;
        }
        if((d3 < MinimumDistance))
        {
            MinimumDistance = d3;
            MinimumDistancePoint = P3;
            DistanceFlag = 1;
        }

        LTXPoint T;
        if(DistanceFlag == 0)
        {
            T = Area.Quadratic.SolveForY(MinimumDistancePoint.y);
            return Area.Quadratic.CloserOfTwo(T, Subject);
        }

        if(DistanceFlag == 1)
        {
            T = Area.Quadratic.SolveForX(MinimumDistancePoint.y);
            return Area.Quadratic.CloserOfTwo(T, Subject);
        }
        
    }
    if(Area.type == 1)
    {
        LTXRect boundingArea = CubicBounding(Area.Cubic);
        boundingArea.ReadNamed();

        LTXPoint bottomRight = {boundingArea.topRight.x, boundingArea.bottomLeft.y};
        LTXPoint topLeft = {boundingArea.bottomLeft.x, boundingArea.topRight.y};

        //0 case
        LTXPoint V0 = topLeft-boundingArea.bottomLeft;
        LTXPoint V1 = boundingArea.topRight - bottomRight;
        LTXPoint V2 = boundingArea.topRight - topLeft;
        LTXPoint V3 = bottomRight - boundingArea.bottomLeft;

        LTXPoint P0 = Subject.ProjectOnto(boundingArea.bottomLeft, topLeft);
        P0.ReadNamed();
        LTXPoint P1 = Subject.ProjectOnto(bottomRight, boundingArea.topRight);
        P1.ReadNamed();
        LTXPoint P2 = Subject.ProjectOnto(topLeft, boundingArea.topRight);
        P2.ReadNamed();
        LTXPoint P3 = Subject.ProjectOnto(boundingArea.bottomLeft, bottomRight);
        P3.ReadNamed();

        float d0 = (Subject-P0).mag();
        float d1 = (Subject-P1).mag();
        float d2 = (Subject-P2).mag();
        float d3 = (Subject-P3).mag();
        
        LTXPoint MinimumDistancePoint = P0;
        float MinimumDistance = d0;
        //Distance Flag : 0 for vertical edges, 1 for horizontal edges.
        int DistanceFlag = 0;
        if((d1 < MinimumDistance))
        {
            MinimumDistance = d1;
            MinimumDistancePoint = P1;
            DistanceFlag = 0;
        }
        if((d2 < MinimumDistance))
        {
            MinimumDistance = d2;
            MinimumDistancePoint = P2;
            DistanceFlag = 1;
        }
        if((d3 < MinimumDistance))
        {
            MinimumDistance = d3;
            MinimumDistancePoint = P3;
            DistanceFlag = 1;
        }

        CubicSolution T;
        if(DistanceFlag == 0)
        {
            T = Area.Cubic.SolveForY(MinimumDistancePoint.y);
            return Area.Cubic.CloserOfThree(T, Subject);
        }

        if(DistanceFlag == 1)
        {
            T = Area.Cubic.SolveForX(MinimumDistancePoint.y);
            return Area.Cubic.CloserOfThree(T, Subject);
        }
    }

}
//Different types of projections
//Angle of entry projections

void PrintLTXVector(LTXVector A)
{
    printf("( %f , %f )\n", A.x, A.y);
}

void NormalCastByLineSegment()
{
    LTXLineSegment Segment(LTXPoint(-0.1, -0.4), LTXPoint(-0.3, -0.1) );
    LTXPoint Intercept = LineSegmentIntercept(Segment , 4);
    LTXVector PointNormal = LineSegmentPointNormal(Segment, Intercept);
    LTXVector Direction = PointNormal - Intercept;
    LTXPoint Casted = Cast(Intercept, Direction, 0.2);
    PrintLTXPoint(Intercept);
    PrintLTXVector(PointNormal);
    PrintLTXPoint(Casted);
}


#endif