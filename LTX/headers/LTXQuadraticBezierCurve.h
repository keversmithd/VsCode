#ifndef LTXQUADRATICBEZIER
#define LTXQUADRATICBEZIER

#include "LTXLineSegment.h"


LTXPoint LTXQuadraticCalculation(LTXPoint* Coef, float t)
{
    //printf("\n");
    LTXPoint X = pow((1-t),2) * Coef[0] +  2*(1-t)*t*Coef[1] + pow(t,2)*Coef[2];
    //PrintLTXPoint(X);
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
        return pow((1-t),2)*P0 + 2*(1-t)*t*P1 + pow(t,2)*P2;
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

    void ReadNamed()
    {
        char r1[2] = {(char)(rand() % 26 + 'a'), (char)(rand() % 26 + 'a')};
        char r2[2] = {(char)(rand() % 26 + 'a'), (char)(rand() % 26 + 'a')};
        char r3[2] = {(char)(rand() % 26 + 'a'), (char)(rand() % 26 + 'a')};
        
        PrintLTXLatexPoint(P0, r1);
        PrintLTXLatexPoint(P1, r2);
        PrintLTXLatexPoint(P2, r3);
        printf("\\draw (%c%c) to[quadratic={(%c%c)}] (%c%c);\n", r1[0], r1[1], r2[0],r2[1],r3[0],r3[1]);
    }
    ~LTXQuadraticBezier(){}
};





#endif