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
    LTXQuadraticBezier(LTXPoint p0, LTXPoint p1, LTXPoint p2, const LTXRect R)
    {
        P0 = p0*R;
        P1 = p1*R;
        P2 = p2*R;
    }
    LTXPoint Sample(float t)
    {
        return pow((1-t),2)*P0 + 2*(1-t)*t*P1 + pow(t,2)*P2;
    }

    LTXVD4 Solutions()
    {

        LTXVD4 sol;

        double Ax = (P0.x-2*P1.x + P2.x);
        double Bx = (-2*P0.x + 2*P1.x);
        double Cx = (P0.x);

        double xdisc = pow(Bx,2) - ((4)*(Ax)*(Cx));
        if(Ax == 0 || xdisc < 0)
        {
            sol.x = 0;
            sol.y = 0;
        }else
        {
            sol.x = (-Bx + sqrt(xdisc))/(2*Ax);
            sol.y = (-Bx - sqrt(xdisc))/(2*Ax);
        }

        return sol;
    }


    LTXRect BoundingRectangle()
    {

        double MinX = MinTwo(P0.x, P0.x, P2.x);
        double MinY = MinTwo(P0.y, P0.y, P2.y);

        double MaxX = MaxTwo(P0.x, P0.x, P2.x);
        double MaxY = MaxTwo(P0.y, P0.y, P2.y);

        LTXPoint sample;

        float disc = (P0.x - 2*P1.x + P2.x);
        float disc2 = (P0.y - 2*P1.y + P2.y);
        if(disc != 0)
        {
            float t = (P0.x - P1.x)/disc;
            if(t >= 0 && t <= 1)
            {
                sample = Sample(t);

                MinX = (sample.x < MinX) ? sample.x : MinX;
                MaxX = (sample.x > MaxX) ? sample.x : MaxX;
                MinY = (sample.y < MinY) ? sample.y : MinY;
                MaxY = (sample.y > MaxY) ? sample.y : MaxY;
            }
        }

        if(disc2 != 0)
        {
            float t = (P0.y - P1.y)/disc2;
            if(t >= 0 && t <= 1)
            {
                sample = Sample(t);

                MinX = (sample.x < MinX) ? sample.x : MinX;
                MaxX = (sample.x > MaxX) ? sample.x : MaxX;
                MinY = (sample.y < MinY) ? sample.y : MinY;
                MaxY = (sample.y > MaxY) ? sample.y : MaxX;
            }
        }
        

        return {{MinX,MinY},{MaxX, MaxY}};
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

    void Draw()
    {
        printf("\\draw (%f pt, %f pt) to[quadratic={(%f pt %f pt)}] (%f pt %f pt);\n", P0.x, P0.y, P1.x, P1.y, P2.x, P2.y);
    }

    ~LTXQuadraticBezier(){}
};


LTXRect QuadraticBounding(LTXQuadraticBezier Bezier)
{

}


#endif