#ifndef LTXDECAST
#define LTXDECAST
#include "LTXLineSegment.h"

void De_Casteljau(LTXPoint* Curve, int N, float t)
{
    if(Curve == nullptr)
    {
        std::cout << "null" << std::endl;
        return;
    }
    printf("\n");
    int n = N;
    
    for(int i = 1; i < n; i++)
    {
        //printf("i:%d\n", i);
        for(int j = 0; j < n-i; j++)
        {
            //printf("j:%d\n", j);
            Curve[j] = Curve[j] * (1-t) + Curve[j+1] * t;
        }
    }
    
    for(int i = 0; i< n; i++)
    {
        PrintLTXPoint(Curve[i]);
    }
}

LTXPoint LTXQuadraticCalculation(LTXPoint* Coef, float t)
{
    //printf("\n");
    LTXPoint X = pow((1-t),2) * Coef[0] +  2*(1-t)*t*Coef[1] + pow(t,2)*Coef[2];
    //PrintLTXPoint(X);
    return X;
}

LTXPoint QuadraticSolve(float a, float b, float c)
{
    if(a == 0)
    {
        return {-16969,-16969};
    }

    float disc = b*b - (4 * a * c);

    if(disc < 0)
    {
        return {-16969,-16969};
    }

    return {(-b + disc)/2*a, (-b - disc)/2*a};
    

}

LTXPoint QuadraticSolve(float a, float b, float c, float disc)
{
    if(a == 0)
    {
        return {-16969,-16969};
    }

    if(disc < 0)
    {
        return {-16969,-16969};
    }

    return {(-b + disc)/2*a, (-b - disc)/2*a};
    
}


struct CubicSolution
{
    double r0 = -16969;
    double r1 = -16969;
    double r2 = -16969;

    void Read()
    {
        if(r1 == -16969 && r2 == -16969)
        {
            printf("Root #1: %f\n", r0);
            return;
        }

        printf("Root #1: %f, Root #2: %f, Root #3: %f\n", r0, r1, r2);
    }
};

CubicSolution cubicsolve(double a, double b, double c, double d)
{
    

    if (a == 0)
    {
        //alert("The coefficient of the cube of x is 0. Please use the utility for a SECOND degree quadratic. No further action taken.");
        LTXPoint QuadraticSolution = QuadraticSolve(b,c,d);
        CubicSolution x;
        x.r0 = QuadraticSolution.x;
        x.r1 = QuadraticSolution.y;
        return x;
    } //End if a == 0
    if (d == 0)
    {
        //alert("One root is 0. Now divide through by x and use the utility for a SECOND degree quadratic to solve the resulting equation for the other two roots. No further action taken.");
        

        double newA = a;
        double newB = b / a;
        double newC = c / a;

        // Solve the resulting quadratic equation
        LTXPoint QuadraticSolution = QuadraticSolve(newB, newC, 0);

        CubicSolution x;
        x.r0 = 0;
        x.r1 = QuadraticSolution.x;
        x.r2 = QuadraticSolution.y;

        return x;
    } //End if d == 0

    CubicSolution PotentialSolution;

    b /= a;
    c /= a;
    d /= a;
    double disc, q, r, dum1, s, t, term1, r13;
    q = (3.0*c - (b*b))/9.0;
    r = -(27.0*d) + b*(9.0*c - 2.0*(b*b));
    r /= 54.0;
    disc = q*q*q + r*r;

    //dataForm.x1Im.value = 0; //The first root is always real.
    term1 = (b/3.0);
    if (disc > 0) { // one root real, two are complex
        s = r + sqrt(disc);
        s = ((s < 0) ? -pow(-s, (1.0/3.0)) : pow(s, (1.0/3.0)));
        t = r - sqrt(disc);
        t = ((t < 0) ? -pow(-t, (1.0/3.0)) : pow(t, (1.0/3.0)));
        PotentialSolution.r0 = -term1 + s + t;
        term1 += (s + t)/2.0;
        PotentialSolution.r1 = PotentialSolution.r2 = -term1;
 
        return PotentialSolution;
    } 

    if (disc == 0){ // All roots real, at least two are equal.
        r13 = ((r < 0) ? pow(-r,(1.0/3.0)) : pow(r,(1.0/3.0)));
        PotentialSolution.r0 = -term1 + 2.0*r13;
        PotentialSolution.r1 = PotentialSolution.r2 = -(r13 + term1);
        return PotentialSolution;
    } // End if (disc == 0)
    // Only option left is that all roots are real and unequal (to get here, q < 0)
    q = -q;
    dum1 = q*q*q;
    dum1 = acos(r/sqrt(dum1));
    r13 = 2.0*sqrt(q);
    PotentialSolution.r0 = -term1 + r13*cos(dum1/3.0);
    PotentialSolution.r1 = -term1 + r13*cos((dum1 + 2.0*M_PI)/3.0);
    PotentialSolution.r2 = -term1 + r13*cos((dum1 + 4.0*M_PI)/3.0);
    return PotentialSolution;
}

LTXLineSegment CubicCasteljauTangent(LTXPoint* Curve, int N,  float t)
{
    if(Curve == nullptr)
    {
        return LTXLineSegment(0,0,0,0);
    }
    int n = N;
    for(int i = 1; i < n; i++)
    {
        for(int j = 0; j < n-i; j++)
        {
            Curve[j] = Curve[j] * (1-t)  + Curve[j+1] * t;
        }
    }
    
    return LTXLineSegment(Curve[0], Curve[1]);
    
    
}

#endif