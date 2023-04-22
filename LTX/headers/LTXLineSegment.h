#ifndef LTXLINESEG
#define LTXLINESEG

#include "LTXVector.h"

struct LTXLineSegment
{
    LTXPoint P;
    LTXPoint Q;
    LTXLineSegment(){}
    LTXLineSegment(LTXPoint p, LTXPoint q){ P=p; Q=q; } 
    LTXLineSegment(float x, float y, float z, float w)
    {
        P.x = x;
        P.y = y;
        Q.x = z;
        Q.y = w;
    }
    
    void Read() { PrintLTXPoint(P); PrintLTXPoint(Q); }

    void ReadNamed()
    {
        char r1[2] = {(char)(rand() % 26 + 'a'), (char)(rand() % 26 + 'a')};
        char r2[2] = {(char)(rand() % 26 + 'a'), (char)(rand() % 26 + 'a')};

        PrintLTXLatexPoint(P, r1);
        PrintLTXLatexPoint(Q, r2);
        
        printf("\\draw (%c%c) -- (%c%c);", r1[0], r1[1], r2[0], r2[1]);
    }
    ~LTXLineSegment(){}
    
};

LTXPoint BisectorLineSegment(LTXPoint A, LTXPoint B)
{
    LTXPoint temp;
    temp.x = A.x + (B.x - A.x)/2;
    temp.y = A.y + (B.y - A.y)/2;
    return temp;
}

LTXPoint BisectorLineSegment(LTXLineSegment Segment)
{
    LTXPoint temp;
    temp.x = Segment.P.x + (Segment.Q.x - Segment.P.x)/2;
    temp.y = Segment.P.y + (Segment.Q.y - Segment.P.y)/2;
    return temp;
}
LTXPoint LineSegmentIntercept(LTXPoint A, LTXPoint B, float t)
{
    LTXPoint temp;
    temp.x = A.x + (B.x - A.x)/t;
    temp.y = A.y + (B.y - A.y)/t;
    return temp;
}
LTXPoint LineSegmentIntercept(LTXLineSegment Segment, float t)
{
    LTXPoint temp;
    temp.x = Segment.P.x + (Segment.Q.x - Segment.P.x)/t;
    temp.y = Segment.P.y + (Segment.Q.y - Segment.P.y)/t;
    return temp;
}
LTXVector LineSegmentPointNormal(LTXLineSegment Seg, LTXPoint Point)
{
    //printf("Segment: Point A ( %f , %f ) \nSegment: Point B ( %f , %f ) \n", Seg.P.x, Seg.P.y, Seg.Q.x, Seg.Q.y);
    float dx = (Seg.Q.x - Seg.P.x);
    float dy = (Seg.Q.y - Seg.P.y);
    //printf("DX: %f, DY: %f \n", dx, dy);
    LTXVector Normal(-dy, dx);
    Normal = Normalize(Normal);
    Normal.x += Point.x;
    Normal.y += Point.y;
    return Normal;
}
LTXPoint SubdivideLineSegmentByT(LTXPoint A, LTXPoint B, float t)
{
    float lx = B.x - A.x;
    float ly = B.y - A.y;
    float rx = lx * t;
    float ry = ly * t;
    A.x = A.x + rx;
    A.y = A.y + ry;
    return A;
}



#endif
