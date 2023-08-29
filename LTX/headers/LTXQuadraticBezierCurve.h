#ifndef LTXQUADRATICBEZIER
#define LTXQUADRATICBEZIER

#include "LTXLineSegment.h"





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

    float MedianProjection(LTXPoint Subject)
    {
       LTXPoint TX = SolveForX(Subject.x);

       LTXPoint TY = SolveForY(Subject.y);

       float ClosestXDistance = INT_MAX;
       float BufferDistance = INT_MAX;

       float tx = -1;

       if(TX.x >= 0 && TX.x <= 1)
       {
           ClosestXDistance = (Subject-Sample(TX.x)).mag();
           tx = TX.x;
       }
       if(TX.y >= 0 && TX.y <= 1)
       {
          BufferDistance = (Subject-Sample(TX.y)).mag();
          tx = (BufferDistance < ClosestXDistance) ? TX.y : tx;
       }

       float ty = -1;
       if(TY.x >= 0 && TY.x <= 1)
       {
            ClosestXDistance = (Subject-Sample(TY.x)).mag();
            ty = TY.x;
       }
       if(TY.y >= 0 && TY.y <= 1)
       {
            BufferDistance = (Subject-Sample(TY.y)).mag();
            ty = (BufferDistance < ClosestXDistance) ? TY.y : ty;
       }

       if(tx == -1 && ty == -1)
       {
         return -1;
       }

       if(tx == -1 && ty != -1)
       {
            return ty;
       }

       if(ty == -1 && tx != -1)
       {
            return tx;
       }

       if(tx < ty)
       {
        return tx + (ty-tx)/2;
       }
       
       return ty + (tx + ty)/2;
    }

    float ClosestOfTwoProjection(LTXPoint Subject)
    {
       LTXPoint TX = SolveForX(Subject.x);
       LTXPoint TY = SolveForY(Subject.y);

       float ClosestXDistance = INT_MAX;
       float BufferDistance = INT_MAX;

       float tx = -1;

       if(TX.x >= 0 && TX.x <= 1)
       {
           BufferDistance = (Subject-Sample(TX.x)).mag();
           ClosestXDistance = (BufferDistance < ClosestXDistance) ? BufferDistance : ClosestXDistance;
           tx = TX.x;
       }
       if(TX.y >= 0 && TX.y <= 1)
       {
          BufferDistance = (Subject-Sample(TX.y)).mag();
          ClosestXDistance = (BufferDistance < ClosestXDistance) ? BufferDistance : ClosestXDistance;
          tx = (BufferDistance < ClosestXDistance) ? TX.y : tx;
       }
       if(TY.x >= 0 && TY.x <= 1)
       {
            BufferDistance = (Subject-Sample(TY.x)).mag();
            ClosestXDistance = (BufferDistance < ClosestXDistance) ? BufferDistance : ClosestXDistance;
            tx = (BufferDistance < ClosestXDistance) ? TY.x : tx;
       }
       if(TY.y >= 0 && TY.y <= 1)
       {
            BufferDistance = (Subject-Sample(TY.y)).mag();
            ClosestXDistance = (BufferDistance < ClosestXDistance) ? BufferDistance : ClosestXDistance;
            tx = (BufferDistance < ClosestXDistance) ? TY.y : tx;
       }

        return tx;
    }
    
    float CloserOfTwo(LTXPoint TValues, LTXPoint Subject)
    {

        float tmin = 0;
        float dmin = INT_MAX;
        float dbuff = 0;
        if(TValues.x >= 0 && TValues.x <= 1)
        {   
            dbuff = (Subject-Sample(TValues.x)).mag();
            if(dbuff < dmin)
            {
                dmin = dbuff;
                tmin = TValues.x;
            }

        }

        if(TValues.y >= 0 && TValues.y <= 1)
        {
            dbuff = (Subject-Sample(TValues.y)).mag();
            if(dbuff < dmin)
            {
                dmin = dbuff;
                tmin = TValues.y;
            }
        }

        if(dmin == INT_MAX)
        {
            return -16969;
        }



        return tmin;
    }

    LTXVD4 SolveFor(LTXPoint G)
    {
        LTXVD4 sol;
        LTXPoint A = (P0 - 2*P1 + P2);
        LTXPoint B = (-2*P0 + 2*P1);
        LTXPoint C = P0;

        float a = A.x;
        float b = B.x;
        float c = C.x - G.x;

        float disc = b * b - 4 * a * c;
        float t1, t2;

        if(disc >= 0 && a != 0)
        {
            t1 = (-b + sqrt(disc)) / (2 * a);

            t2 = (-b - sqrt(disc)) / (2 * a);

            if(t1 >= 0 && t1 <= 1)
            {
                sol.x  = t1;
            }

            if(t2 >= 0 && t2 <= 1)
            {
                sol.y  = t2;
            }
        }

        a = A.y;
        b = B.y;
        c = C.y - G.y;

        disc = b * b - 4 * a * c;

        if(disc >= 0 && a != 0)
        {
            t1 = (-b + sqrt(disc)) / (2 * a);
            t2 = (-b - sqrt(disc)) / (2 * a);

            if(t1 >= 0 && t1 <= 1)
            {
                sol.z  = t1;
            }

            if(t2 >= 0 && t2 <= 1)
            {
                sol.w  = t2;
            }
        }

        return sol;
    }

    LTXPoint SolveForY(float Y)
    {

        LTXPoint t = {-69, -69};

        float a = (P0.y - 2*P1.y + P2.y);
        float b = (-2*P0.y + 2*P1.y);
        float c = P0.y - Y;

        float disc = b * b - 4 * a * c;

        if(disc >= 0 && a != 0)
        {
            t.x = (-b + sqrt(disc)) / (2 * a);
            t.y = (-b - sqrt(disc)) / (2 * a);
        }
        return t;

    }

    LTXPoint SolveForX(float X)
    {

        LTXPoint t = {-69, -69};

        float a = (P0.x - 2*P1.x + P2.x);
        float b = (-2*P0.x + 2*P1.x);
        float c = P0.x - X;

        float disc = b * b - 4 * a * c;

        if(disc >= 0 && a != 0)
        {
            t.x = (-b + sqrt(disc)) / (2 * a);
            t.y = (-b - sqrt(disc)) / (2 * a);
        }

        return t;


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



#endif