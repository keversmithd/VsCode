#ifndef LTXQUADRATICBEZIER
#define LTXQUADRATICBEZIER

#include "LTXLineSegment.h"


LTXPoint LTXQuadraticCalculation(LTXPoint* Coef, float t)
{
    printf("\n");
    LTXPoint X = pow((1-t),2) * Coef[0] +  2*(1-t)*t*Coef[1] + pow(t,2)*Coef[2];
    PrintLTXPoint(X);
    return X;
}

struct LTXQuadraticBezier
{
    LTXPoint P0;
    LTXPoint P1;
    LTXPoint P2;
    
    LTXQuadraticBezier()
    {
        P0 = LTXPoint(0, 0);
        P1 = LTXPoint(0, 0);
        P2 = LTXPoint(0, 0);
    }
    LTXQuadraticBezier(LTXPoint p0, LTXPoint p1, LTXPoint p2)
    {
        P0 = p0;
        P1 = p1;
        P2 = p2;
    }
    LTXPoint Sample(float t)
    {
        LTXPoint Coefs[3];
        Coefs[0] = P0;
        Coefs[1] = P1;
        Coefs[2] = P2;
        return LTXQuadraticCalculation(Coefs, t);
    }
    LTXQuadraticBezier(float p0x, float p0y, float p1x, float p1y, float p2x, float p2y)
    {
        P0 = LTXPoint(p0x, p0y);
        P1 = LTXPoint(p1x, p1y);
        P2 = LTXPoint(p2x, p2y);
    }
    void Read()
    {
        PrintLTXPoint(P0);
        PrintLTXPoint(P1);
        PrintLTXPoint(P2);
    }
    ~LTXQuadraticBezier(){}
};





#endif