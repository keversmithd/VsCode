#ifndef LTXCUBSOLVE
#define LTXCUBSOLVE
#include <iostream>
#include <stdio.h>
#include "headers/LTXStructures.h"
#include <list>
#include <array>
#include <vector>

bool CubicIntersectionLinear(LTXCubicBezier p0, LTXCubicBezier p1)
{
    //this wouldn't actually work...
    float stepsize = 0.1f;
    float stepcount = 1.0f/stepsize;
    float t = 0;
    LTXPoint p;
    LTXPoint q;

    LTXPoint pq;
    double m;
    float minDistance = 0.1;
    for(int i = 0; i < floor(stepcount); i++)
    {
        p = p0.Sample(t);
        q =  p1.Sample(t);

        pq = q-p;
        m = Magnitude(pq);

        if(m < minDistance)
        {
            return true;
        }

        t+=stepsize;
    }
    return false;
}

LTXPoint operator *(std::array<std::array<double,2>,2>J, LTXPoint P)
{
    
}

bool NewtonRaphsonCubicIntersection(LTXCubicBezier p0, LTXCubicBezier p1)
{   

    struct SubtractiveBezierCurve{

        LTXCubicBezier A;
        LTXCubicBezier B;
        LTXQuadraticBezier APrime;
        LTXQuadraticBezier BPrime;

        SubtractiveBezierCurve(LTXCubicBezier p0, LTXCubicBezier p1) : A(p0), B(p1)
        {
            APrime = p0.Derivative();
            BPrime = p1.Derivative();
        }

        LTXPoint Sample(double u, double v)
        {
            return ((pow((1-u),3)*A.P0) + (3*pow((1-u),2)*u*A.P1)+(3*(1-u)*pow(u,2)*A.P2) + (pow(u,3)*A.P3)) - ((pow((1-v),3)*A.P0) + (3*pow((1-v),2)*v*A.P1)+(3*(1-v)*pow(v,2)*A.P2) + (pow(v,3)*A.P3));
        }

        LTXPoint PartialU(double u)
        {
            return APrime.Sample(u);
        }
        LTXPoint PartialV(double u)
        {
            return BPrime.Sample(u)*-1;
        }


        std::array<std::array<double,2>,2> Jacobian(double u, double v)
        {
            std::array<std::array<double, 2>, 2> J;
            J[0][0] = APrime.Sample(u).x;
            J[0][1] = PartialV(v).x;
            J[1][0] = APrime.Sample(u).y;
            J[1][1] = PartialV(v).y;
            return J;
        }

        double Determinant(double u, double v, std::array<std::array<double,2>,2> J)
        {
            return (J[0][0] - J[1][1])-(J[0][1] - J[1][0]);
        }

        std::array<std::array<double,2>,2> Inverse(double u, double v)
        {
            std::array<std::array<double, 2>, 2> J = Jacobian(u,v);
            double determinant = Determinant(u,v,J);
            if(determinant == 0) {return {};}
            std::array<std::array<double, 2>, 2> I;
            I[0][0] = 1/determinant * J[1][1];
            I[0][1] = 1/determinant * -J[0][1];
            I[1][0] = 1/determinant * -J[1][0];
            I[1][1] = 1/determinant * J[0][0];

            return I;
        }

    };

    SubtractiveBezierCurve  JacobianInverse(p0, p1);
    
    LTXPoint IterativePoint = {0.5, 0.5};
    LTXPoint PreviousPoint = {0.5, 0.5};
    int num_passes = 10;
    double convergence_threshold = 0.1;
    for(int i = 0; i < 10;  i++)
    {
        PreviousPoint = IterativePoint;
        IterativePoint = IterativePoint + JacobianInverse.Inverse(IterativePoint.x, IterativePoint.y)*JacobianInverse.Sample(IterativePoint.x, IterativePoint.y);
        if (Magnitude((IterativePoint - PreviousPoint))<convergence_threshold){ true; } 
    }

}

std::vector<LTXPoint> SolutionsToBezierCurve(LTXCubicBezier p0)
{

    //newton raphson method
    float h = 0.0;
    float x0 = 0.5;
    float x1 = 0.5;
    float r = x0 + h;
    LTXQuadraticBezier Derivative = p0.Derivative();
    for(int i = 0; i < 10; i++)
    {
        x1 = x1 - (p0.Sample(x1).y/Derivative.Sample(x1).y);
    } 


    //secant method

    x0 = 0.4;
    x1 = 0.6;
    float q0 = p0.Sample(x0).y;
    float q1 = p0.Sample(x1).y;
    float x2 = 0.0;
    for(int i = 2; i < 10; i++)
    {
        x2 = x1 - q1 * (x1 - x0) / (q1 - q0);
        x0 = x1;
        q0 = q1;
        x1 = x2;
        q1 = p0.Sample(x2).y;
        if (std::abs(x1 - x0) < 1e-6) {
            break;
        }
    }

}


#endif