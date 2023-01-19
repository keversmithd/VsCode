#include "LTXPoint.h"
#include "LTXLineSegment.h"
#include "LTXVector.h"
#include "LTXCubicBezierCurve.h"
#include "LTXDeCasteljau.h"

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
