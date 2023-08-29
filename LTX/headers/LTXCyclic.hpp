#ifndef LTX_CYCLIC
#define LTX_CYCLIC

#include "LTXStructures.h"


struct LTXCycle
{
    float Radius;
    LTXPoint Center;

    LTXCycle(LTXPoint center, float radius) : Radius(radius), Center(center)
    {

    }

    LTXPoint SampleByT(float T)
    {
        return {(Radius * ((1-T*T)/(1+T*T))) + Center.x, (Radius * ((2*T)/(1+T*T))) + Center.y};
    }

    float SolveFor(LTXPoint PointOnCircle)
    {
        float denom = (-Center.x + Radius + PointOnCircle.x);
        float disc = -1;
        if(denom == 0)
        {
            
        }else
        {
           disc = (Center.x + Radius - PointOnCircle.x)/denom;
        }

        if(disc < 0)
        {
            denom = (Center.y - PointOnCircle.y);

            if(denom == 0)
            {
                return -16969;
            }
            disc = (-Center.y + Radius + PointOnCircle.y)*(Center.y + Radius - PointOnCircle.y);

            float t = -Radius+sqrt(disc);
            LTXPoint Sample1 = SampleByT(t);

            if(PointOnCircle != Sample1)
            {
                return -Radius-sqrt(disc);
            }

            return t;

        }else
        {
            float t = sqrt(disc);
            LTXPoint Sample1 = SampleByT(t);

            if(PointOnCircle != Sample1)
            {
                return -t;
            }

            return t;
        }
    }

};

struct LTXVec3
{
    float x,y,z;

    LTXVec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z)
    {

    }

};

struct LTXCycleLineIntersection
{
    int meets;
    LTXPoint P0;
    LTXPoint P1;
};

LTXCycleLineIntersection MeetsWithCircle(LTXVec3 Line, LTXCycle Circle)
{   
    LTXCycleLineIntersection intersection;
    if(Line.y != 0)
    {
        float a = Line.x;
        float b = Line.y;
        float c = Line.z;

        float x0 = Circle.Center.x;
        float y0  = Circle.Center.y;

        float R = Circle.Radius;

        float x = ((a/b)*(a/b)) + 1;

        float y = (-2*(c/b)*(a/b)) + (2*(a/b)*y0 )- (2*x0);

        float z = ((x0*x0)) + ((y0*y0) )+ ((c/b)*(c/b)) - (2*(c/b)*y0) - (R*R);

        float d = y*y - 4*x*z;

        if(d == 0)
        {
            intersection.meets = 0;
            intersection.P0 = {-16969, -16969};
            intersection.P1 = {-16969, -16969};
            return intersection;
        }

        LTXPoint Sol = QuadraticSolve(x,y,z,d);

        if(d == 0)
        {
            intersection.meets = 1;
            intersection.P0 = {Sol.x, (c/b)-((a/b)*(Sol.x))};
            intersection.P1 = {Sol.y, (c/b)-((a/b)*(Sol.y))};
            return intersection;
        }
        if(d > 0)
        {
            intersection.meets = 2;
            intersection.P0 = {Sol.x, (c/b)-((a/b)*(Sol.x))};
            intersection.P1 = {Sol.y, (c/b)-((a/b)*(Sol.y))};
            return intersection;
        }


    }else if(Line.x != 0)
    {
        float a = Line.x;
        float b = Line.y;
        float c = Line.z;

        float x0 = Circle.Center.x;
        float y0  = Circle.Center.y;

        float R = Circle.Radius;

        float x = ((b/a)*(b/a)) + 1;

        float y = (-2*(c/a)*(b/a)) + (2*(b/a)*x0 )- (2*y0);

        float z = ((x0*x0)) + ((y0*y0) )+ ((c/a)*(c/a)) - (2*(c/a)*x0) - (R*R);

        float d = y*y - 4*x*z;

        if(d == 0)
        {
            intersection.meets = 0;
            intersection.P0 = {-16969, -16969};
            intersection.P1 = {-16969, -16969};
            return intersection;
        }

        LTXPoint Sol = QuadraticSolve(x,y,z,d);

        if(d == 0)
        {
            intersection.meets = 1;
            intersection.P0 = {Sol.x, (c/b)-((a/b)*(Sol.x))};
            intersection.P1 = {Sol.y, (c/b)-((a/b)*(Sol.y))};
            return intersection;
        }
        if(d > 0)
        {
            intersection.meets = 2;
            intersection.P0 = {Sol.x, (c/b)-((a/b)*(Sol.x))};
            intersection.P1 = {Sol.y, (c/b)-((a/b)*(Sol.y))};
            return intersection;
        }
    }



}

LTXVec3 ProportionalJoin(LTXVec3 A, LTXVec3 B)
{
    float a = (A.y - B.y);
    float b = (B.x - A.x);
    float c = (B.x * A.y) - (A.x * B.y);
    return LTXVec3(a, b, c);
}

bool AffinelyParallel(LTXVec3 L1, LTXVec3 L2)
{
    return ((L1.x * L2.y) - (L1.y * L2.x)) == 0;
}

LTXPoint LineMeet(LTXVec3 L1, LTXVec3 L2)
{
    float x = ((L2.y*L1.z)-(L1.y*L2.z))/((L1.x*L2.y)-(L2.x*L1.y));
    float y = ((L1.x * L2.z)-(L2.x*L1.z))/((L1.x*L2.y)-(L2.x*L1.y));
    return LTXPoint(x,y);
}

bool Collinearity(LTXPoint A, LTXPoint B, LTXPoint C)
{
    
    return (A.x * B.y) - (A.x*C.y) + (B.x*C.y) - (C.x*A.y) + (C.x*A.y) - (B.x*A.y) == 0;
}

LTXVec3 Dual(LTXPoint P, LTXCycle C)
{

    float c0 = -C.Center.x*P.x;
    float c1 = -C.Center.y*P.y;
    return {P.x, P.y, C.Radius-c0-c1};
}

float Quadrance(LTXPoint A, LTXPoint B)
{
    //in relation to the dual line, 
    return 1 - pow((((A.x*B.x) + (A.y*B.y)) - 1),2)/(((A.x*A.x + A.y*A.y) - 1)*((B.x*B.x + B.y*B.y) -1));
}

float Spread(LTXVec3 L0, LTXVec3 L1)
{
    return 1 -  pow((L0.x * L1.x + L0.y*L1.y - L0.z*L1.z),2)/((L0.x*L0.x + L0.y*L0.y - L0.z*L0.z)*(L1.x*L1.x + L1.y*L1.y - L1.z*L1.z));
}

void MAIN()
{
    




}





#endif