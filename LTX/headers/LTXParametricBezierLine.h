#ifndef LTXPARMBEZLINE
#define LTXPARMBEZLINE

#include "LTXVector.h"

LTXPoint CalculateParametricBezierLine(LTXPoint P0, LTXPoint P1, float t)
{
    return 2*(1-t)*(P0)+2*t*(P1);
}

struct LTXParametricBezierLine
{
    LTXPoint P0;
    LTXPoint P1;

    LTXPoint LineVector;
    LTXParametricBezierLine()
    {
        
    }
    LTXParametricBezierLine(LTXPoint p0, LTXPoint p1, LTXPoint p2)
    {
        P0 = p1 - p0;
        P1 = p2 - p1;
        LTXPoint samp1 = CalculateParametricBezierLine(P0, P1, 0.0f);
        LTXPoint samp2 = CalculateParametricBezierLine(P0, P1, 1.0f);
        LineVector = samp2 -  samp1;
    }
    LTXParametricBezierLine(float p0, float p1, float u0, float u1)
    {
        P0 = LTXPoint(p0, p1);
        P1 = LTXPoint(u0, u1);
    }
    LTXPoint Derivate(float t)
    {
        return (-2*P0) + (2*P1);
    }
    LTXPoint ReturnLineVector(){ return LineVector; }
    LTXPoint Sample(float t)
    {
        return P0 + LineVector * t;
    }

    ~LTXParametricBezierLine();
};
#endif