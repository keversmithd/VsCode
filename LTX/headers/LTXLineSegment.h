#ifndef LTXLINESEG
#define LTXLINESEG

#include "LTXVector.h"

double MinTwo(const double original, const double a, const double b)
{
    double min = original;
    min = (a < min) ? a : min;
    min = (b < min) ? b : min;
    return min;
}

double MaxTwo(const double original, const double a, const double b)
{
    double min = original;
    min = (a > min) ? a : min;
    min = (b > min) ? b : min;
    return min;
}

struct LTXVD4
{
    double x,y,z,w;

    LTXVD4() : x(-16969), y(-16969), z(-16969), w(-16969)
    {

    }
};

struct LTXRect
{
    LTXPoint bottomLeft;
    LTXPoint topRight;

    LTXPoint center()
    {
        float mx = bottomLeft.x + ((topRight.x - bottomLeft.x)/2);
        float my = bottomLeft.y + ((topRight.y - bottomLeft.y)/2);

        return {mx,my};
    }

    void ReadNamed()
    {
        char r1[2] = {(char)(rand() % 26 + 'a'), (char)(rand() % 26 + 'a')};
        char r2[2] = {(char)(rand() % 26 + 'a'), (char)(rand() % 26 + 'a')};

        PrintLTXLatexPoint(bottomLeft, r1);
        PrintLTXLatexPoint(topRight, r2);

        printf("\\draw (%c%c) rectangle (%c%c);\n", r1[0], r1[1], r2[0], r2[1]);
    }
};
bool ContainedInBoundingArea(const LTXRect Subject, const LTXRect Area)
{
    return ((Subject.bottomLeft.x >= Area.bottomLeft.x && Subject.bottomLeft.x <= Area.topRight.x) &&
    (Subject.bottomLeft.y >= Area.bottomLeft.y && Subject.bottomLeft.y <= Area.topRight.y));
}
bool ContainedInBoundingArea(const LTXPoint Subject, const LTXRect Area)
{
    return (Subject.x >= Area.bottomLeft.x && Subject.x <= Area.topRight.x) && (Subject.y >= Area.bottomLeft.y && Subject.y <= Area.topRight.y);
}

LTXPoint operator *(const LTXPoint A, const LTXRect Workspace)
{
    float w = Workspace.topRight.x - Workspace.bottomLeft.x;
    float h = Workspace.topRight.y - Workspace.bottomLeft.y;
    return {Workspace.bottomLeft.x + (A.x*w), Workspace.bottomLeft.y + (A.y*h)};
}

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
