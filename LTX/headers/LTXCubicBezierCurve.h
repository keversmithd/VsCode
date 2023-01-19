#ifndef BEZCURBH
#define BEZCURBH

#include "LTXLineSegment.h"
#include "LTXQuadraticBezierCurve.h"
#include "LTXDeCasteljau.h"

LTXPoint LTXCubicCalculation(LTXPoint* Coef, float t)
{
    printf("\n");
    LTXPoint X = pow((1-t),2) * Coef[0] +  2*(1-t)*t*Coef[1] + pow(t,2)*Coef[2];
    PrintLTXPoint(X);
    return X;
}

struct LTXCubicBezier
{
    LTXPoint P0;
    LTXPoint P1;
    LTXPoint P2;
    LTXPoint P3;
    LTXCubicBezier()
    {
        P0 = LTXPoint(0.0f,0.0f);
        P1 = LTXPoint(0.0f,0.0f);
        P2 = LTXPoint(0.0f,0.0f);
        P3 = LTXPoint(0.0f,0.0f);
        
    }
    LTXCubicBezier(LTXPoint p0, LTXPoint p1, LTXPoint p2, LTXPoint p3)
    {
        P0 = p0;
        P1 = p1;
        P2 = p2;
        P3 = p3;
    }
    LTXCubicBezier(float x, float y, float z, float w, float u, float v, float b, float n)
    {
        P0 =  LTXPoint(x, y);
        P1 =  LTXPoint(z,w);
        P2 =  LTXPoint(u,v);
        P3 =  LTXPoint(b, n);
    }
    LTXQuadraticBezier Derivative()
    {
        LTXQuadraticBezier Derivative;
        Derivative.P0 = 3 * (P1 - P0);
        Derivative.P1 = 3 * (P2 - P1);
        Derivative.P2 = 3 * (P3 - P2);
        return Derivative;
    }
    LTXPoint SubdivideByT(float t)
    {
        LTXPoint A = P0;
        LTXPoint B = P1;
        LTXPoint C = P2;
        LTXPoint D = P3;
        LTXPoint tint = SubdivideLineSegmentByT(A,B, t);
        LTXPoint tint2 =  SubdivideLineSegmentByT(B,C, t);
        LTXPoint tint3 =  SubdivideLineSegmentByT(C,D, t);
        LTXPoint tint4 = SubdivideLineSegmentByT(tint,tint2, t);
        LTXPoint tint5 = SubdivideLineSegmentByT(tint2,tint3, t);
        LTXPoint tint6 = SubdivideLineSegmentByT(tint4, tint5, t);
        return tint6;
    }
    LTXLineSegment TangentSegment(float t)
    {
        LTXPoint Q0 = SubdivideLineSegmentByT(P0, P1, t);
        LTXPoint Q1 = SubdivideLineSegmentByT(P1, P2, t);
        LTXPoint Q2 = SubdivideLineSegmentByT(P2, P3, t);
        LTXPoint L1 = SubdivideLineSegmentByT(Q0, Q1, t);
        LTXPoint L2 = SubdivideLineSegmentByT(Q1, Q2, t);
        LTXLineSegment Tan(L1, L2);
        return Tan;
    }
    LTXLineSegment TangentPoint(float t)
    {
        LTXPoint Curvature[4];
        Curvature[0] = P0;
        Curvature[1] = P1;
        Curvature[2] = P2;
        Curvature[3] = P3;
        LTXLineSegment tPoint = CubicCasteljauTangent(Curvature, 4, t);
        return tPoint;
    }
    LTXPoint Sample(float t)
    {
        
    }
    void Read()
    {
        PrintLTXPoint(P0);
        PrintLTXPoint(P1);
        PrintLTXPoint(P2);
        PrintLTXPoint(P3);
    }
    void ReadNamed()
    {
        char r1[2] = {(char)(rand() % 26 + 'a'), (char)(rand() % 26 + 'a')};
        char r2[2] = {(char)(rand() % 26 + 'a'), (char)(rand() % 26 + 'a')};
        char r3[2] = {(char)(rand() % 26 + 'a'), (char)(rand() % 26 + 'a')};
        char r4[2] = {(char)(rand() % 26 + 'a'), (char)(rand() % 26 + 'a')};
        
        PrintLTXLatexPoint(P0, r1);
        PrintLTXLatexPoint(P1, r2);
        PrintLTXLatexPoint(P2, r3);
        PrintLTXLatexPoint(P3, r4);
        printf("\\draw (%c%c) .. controls (%c%c) and (%c%c) .. (%c%c);\n", r1[0], r1[1], r2[0],r2[1],r3[0],r3[1],r4[0],r4[1]);
    }
    
    
};

void LTXCubicToC1(LTXCubicBezier* Curves, unsigned int count)
{
    LTXCubicBezier Entry;
    LTXCubicBezier Next;
    for(int i = 0; i < count; i++)
    {
        Entry = Curves[i];
        Next = Curves[i+1];
        if(Next.P2 != ((2*Entry.P3) - Entry.P2))
        {
            Next.P2 = (2*Entry.P3 - Entry.P2);
        }
    }
}

LTXPoint* SliceCubicBezier(LTXPoint* points, float t)
{
    float x1 = points[0].x;
    float y1 = points[0].y;
    
    float x2 = points[1].x;
    float y2 = points[1].y;
    
    float x3 = points[2].x;
    float y3 = points[2].y;
    
    float x4 = points[3].x;
    float y4 = points[3].y;
    
    float x12 = (x2-x1)*t+x1;
    float y12 = (y2-y1)*t+y1;

    float x23 = (x3-x2)*t+x2;
    float y23 = (y3-y2)*t+y2;

    float x34 = (x4-x3)*t+x3;
    float y34 = (y4-y3)*t+y3;

    float x123 = (x23-x12)*t+x12;
    float y123 = (y23-y12)*t+y12;

    float x234 = (x34-x23)*t+x23;
    float y234 = (y34-y23)*t+y23;

    float x1234 = (x234-x123)*t+x123;
    float y1234 = (y234-y123)*t+y123;
     
    static LTXPoint Sub[4];
    Sub[0] = LTXPoint(x1,y1);
    Sub[1] = LTXPoint(x12,y12);
    Sub[2] = LTXPoint(x123,y123);
    Sub[3] = LTXPoint(x1234,y1234);
    //Aa And Bb Are the control points and Cc
    return Sub;
}

LTXPoint* SegmentsOfCubicBezier(LTXPoint* values, float t)
{
    LTXPoint A = values[0];
    LTXPoint B = values[1];
    LTXPoint C = values[2];
    LTXPoint D = values[3];
    
    LTXPoint tint = SubdivideLineSegmentByT(A,B, t);
    LTXPoint tint2 =  SubdivideLineSegmentByT(B,C, t);
    LTXPoint tint3 =  SubdivideLineSegmentByT(C,D, t);
    
    LTXPoint tint4 = SubdivideLineSegmentByT(tint,tint2, t);
    LTXPoint tint5 = SubdivideLineSegmentByT(tint2,tint3, t);
    
    LTXPoint tint6 = SubdivideLineSegmentByT(tint4, tint5, t);

    static LTXPoint Sub[6] = {tint, tint2, tint3, tint4, tint5, tint6};
    return Sub;
    
}

LTXPoint SubdivideCubicBezierCurveByT(LTXCubicBezier Curve, float t)
{
    LTXPoint A = Curve.P0;
    LTXPoint B = Curve.P1;
    LTXPoint C = Curve.P2;
    LTXPoint D = Curve.P3;
    LTXPoint tint = SubdivideLineSegmentByT(A,B, t);
    LTXPoint tint2 =  SubdivideLineSegmentByT(B,C, t);
    LTXPoint tint3 =  SubdivideLineSegmentByT(C,D, t);
    LTXPoint tint4 = SubdivideLineSegmentByT(tint,tint2, t);
    LTXPoint tint5 = SubdivideLineSegmentByT(tint2,tint3, t);
    LTXPoint tint6 = SubdivideLineSegmentByT(tint4, tint5, t);
    return tint6;
}



#endif