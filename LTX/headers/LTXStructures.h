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

LTXPoint ProjectPointToCurve(LTXPoint Subject, Curve Area)
{

    if(Area.type == 0)
    {
        LTXRect boundingArea = Area.Quadratic.BoundingRectangle();
        LTXPoint bottomRight = {boundingArea.topRight.x, boundingArea.bottomLeft.y};
        LTXPoint topLeft = {boundingArea.bottomLeft.x, boundingArea.topRight.y};

        LTXPoint Diagonal1 = boundingArea.topRight-boundingArea.bottomLeft;
        LTXPoint Diagonal2 = topLeft-bottomRight;

        //0 case
        LTXPoint V0 = topLeft-boundingArea.bottomLeft;
        LTXPoint V1 = boundingArea.topRight - bottomRight;
        LTXPoint V2 = boundingArea.topRight - topLeft;
        LTXPoint V3 = bottomRight - boundingArea.bottomLeft;

        LTXPoint P0 = Subject.ProjectOnto(boundingArea.bottomLeft, topLeft);
        LTXPoint P1 = Subject.ProjectOnto(bottomRight, boundingArea.topRight);
        LTXPoint P2 = Subject.ProjectOnto(topLeft, boundingArea.topRight);
        LTXPoint P3 = Subject.ProjectOnto(boundingArea.bottomLeft, bottomRight);

        float MinimumDistance = (Subject-P0).mag();
        LTXPoint Closest = (MinimumDistance);


        //1st case

        float d0 = dot(Diagonal1, Subject);
        float d1 = dot(Diagonal2, Subject);

        if(d0 || d1 == 0)
        {

        }
        

    }
    if(Area.type == 1)
    {

    }

}


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