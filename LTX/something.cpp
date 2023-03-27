#include <iostream>
#include <stdio.h>
#include "headers/LTXStructures.h"
#include <list>
#include <array>
#include <vector>
LTXCubicBezier GetThickCurve(LTXCubicBezier p, LTXPoint Delta1, LTXPoint Delta2)
{
    p.P1 = p.P1 + Delta1;
    p.P2 =  p.P2 + Delta2;
    return p;
}

struct MinimumMaximumCubicInfo
{
    bool minimumXControlPoint;
    int minimumcontrolPointInt;
};

std::array<LTXPoint,2> MinimumAndMaximumOfCubicCurve(LTXCubicBezier curve)
{

    //if new maximum/minimum is p0, or p3, continue as normal.

    //if the new maximum/minimum is a control point, run decastlejau to determine the,

    //alternatively simply find maximum and minimums anylitcally,

    std::array<LTXPoint,2> Curvature;
    LTXPoint Minimum = curve.P0;
    LTXPoint Maximum = curve.P1;

    bool minimumXControlPoint;
    int minimumXcontrolPointInt;

    bool minimumYControlPoint;
    int minimumYcontrolPointInt;

    bool maximumXControlPoint;
    int maximumXcontrolPointInt;

    bool maximumYControlPoint;
    int maximumYcontrolPointInt;

    int ControlPointconfiguration[8] = {0,0,0,0,0,0,0,0};

    Minimum.x = (curve.P0.x < Minimum.x) ? curve.P0.x : Minimum.x;
    Minimum.y = (curve.P0.y < Minimum.y) ? curve.P0.y : Minimum.y;

    Minimum.x = (curve.P1.x < Minimum.x) ? (ControlPointconfiguration[0] = 1), (ControlPointconfiguration[1] = 1), curve.P1.x : Minimum.x; //if becomes minimum/maximum at any point between here and doesn't become p3, then maximum/minimum is control point.
    Minimum.y = (curve.P1.y < Minimum.y) ? (ControlPointconfiguration[2] = 1), (ControlPointconfiguration[3] = 1), curve.P1.y : Minimum.y;

    Minimum.x = (curve.P2.x < Minimum.x) ? (ControlPointconfiguration[0] = 1), (ControlPointconfiguration[1] = 2), curve.P2.x : Minimum.x;
    Minimum.y = (curve.P2.y < Minimum.y) ? (ControlPointconfiguration[2] = 1), (ControlPointconfiguration[3] = 2), curve.P2.y : Minimum.y;

    Minimum.x = (curve.P3.x < Minimum.x) ? curve.P3.x : (ControlPointconfiguration[0] = 0), Minimum.x;
    Minimum.y = (curve.P3.y < Minimum.y) ? curve.P3.y :  (ControlPointconfiguration[2] = 0), Minimum.y;

    Maximum.x = (curve.P0.x > Maximum.x) ? curve.P0.x : Maximum.x;
    Maximum.y = (curve.P0.y > Maximum.y) ? curve.P0.y : Maximum.y;

    Maximum.x = (curve.P1.x > Maximum.x) ? curve.P1.x : Maximum.x;
    Maximum.y = (curve.P1.y > Maximum.y) ? curve.P1.y : Maximum.y;

    Maximum.x = (curve.P2.x > Maximum.x) ? curve.P2.x : Maximum.x;
    Maximum.y = (curve.P2.y > Maximum.y) ? curve.P2.y : Maximum.y;

    Maximum.x = (curve.P3.x > Maximum.x) ? curve.P3.x : Maximum.x;
    Maximum.y = (curve.P3.y > Maximum.y) ? curve.P3.y : Maximum.y;

    if(ControlPointconfiguration[0] == 1 || ControlPointconfiguration[2] == 1)
    {
        //solve d' = 0 quadratically

    }

    Curvature[0] = Minimum;
    Curvature[1] = Maximum;

    return Curvature;
}


struct LTXCCWCubicList
{
private:
    std::list<LTXCubicBezier> edgeList;
    std::array<LTXPoint,2> Extrema;
public:
    LTXCCWCubicList(){}

    void UpdateExtrema(LTXCubicBezier curve)
    {
        Extrema[0].x = (curve.P0.x < Extrema[0].x) ? curve.P0.x : Extrema[0].x;
        Extrema[0].y = (curve.P0.y < Extrema[0].y) ? curve.P0.y : Extrema[0].y;

        Extrema[0].x = (curve.P1.x < Extrema[0].x) ? curve.P1.x : Extrema[0].x;
        Extrema[0].y = (curve.P1.y < Extrema[0].y) ? curve.P1.y : Extrema[0].y;

        Extrema[0].x = (curve.P2.x < Extrema[0].x) ? curve.P2.x : Extrema[0].x;
        Extrema[0].y = (curve.P2.y < Extrema[0].y) ? curve.P2.y : Extrema[0].y;

        Extrema[0].x = (curve.P3.x < Extrema[0].x) ? curve.P3.x : Extrema[0].x;
        Extrema[0].y = (curve.P3.y < Extrema[0].y) ? curve.P3.y : Extrema[0].y;

        Extrema[1].x = (curve.P0.x > Extrema[1].x) ? curve.P0.x : Extrema[1].x;
        Extrema[1].y = (curve.P0.y > Extrema[1].y) ? curve.P0.y : Extrema[1].y;

        Extrema[1].x = (curve.P1.x > Extrema[1].x) ? curve.P1.x : Extrema[1].x;
        Extrema[1].y = (curve.P1.y > Extrema[1].y) ? curve.P1.y : Extrema[1].y;

        Extrema[1].x = (curve.P2.x > Extrema[1].x) ? curve.P2.x : Extrema[1].x;
        Extrema[1].y = (curve.P2.y > Extrema[1].y) ? curve.P2.y : Extrema[1].y;

        Extrema[1].x = (curve.P3.x > Extrema[1].x) ? curve.P3.x : Extrema[1].x;
        Extrema[1].y = (curve.P3.y > Extrema[1].y) ? curve.P3.y : Extrema[1].y;
    }

    void Append(LTXCubicBezier Bezier)
    {
        if(edgeList.empty())
        {
            edgeList.push_back(Bezier);
            Extrema = MinimumAndMaximumOfCubicCurve(Bezier);
            return;
        }
        UpdateExtrema(Bezier);
        LTXCubicBezier EndOfList = edgeList.back();
        Bezier.P0 = EndOfList.P3;
        edgeList.push_back(Bezier);
    }

    void NormalizedAppension(LTXCubicBezier Bezier, float Scalar)
    {

    }


    void DrawOut()
    {
        for(std::list<LTXCubicBezier>::iterator i = edgeList.begin(); i != edgeList.end(); i++)
        {
            (*i).ReadNamed();
        }
    }

    void DrawExtrema()
    {
        printf("\\draw (%f,%f) rectangle (%f,%f);", Extrema[0].x, Extrema[0].y, Extrema[1].x, Extrema[1].y);
    }



    ~LTXCCWCubicList(){}
};

int main()
{
    LTXCubicBezier a(1.0, 2.0, 1.5, 2.3, 2.5, -0.2, 3.0, 0.0);
    LTXCubicBezier dual = GetThickCurve(a, LTXPoint(0.2, 0.4), LTXPoint(0.4, 0.3));
    LTXCubicBezier dual2 = GetThickCurve(dual, LTXPoint(0.2, 2), LTXPoint(0.4, 0.3));
    LTXCCWCubicList newCube;
    
    newCube.Append(a);
    newCube.Append(dual);
    newCube.Append(dual2);

    float t = 0.0;
    float stepsize = 1.0/1.0;

    for(int i = 0; i < 10; i++)
    {
        
    }
    
    newCube.DrawOut();
    newCube.DrawExtrema();
    
    return 1;
   
}