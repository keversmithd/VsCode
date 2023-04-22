#include <iostream>
#include <stdio.h>
#include "headers/LTXStructures.h"
#include <list>
#include <array>
#include <vector>
LTXCubicBezier GetThickCurve(LTXCubicBezier p, LTXPoint Delta1, LTXPoint Delta2)
{
    p.P1 = p.P1 + Delta1;
    p.P2 =  p.P2 + Delta2;
    return p;
}

struct MinimumMaximumCubicInfo
{
    bool minimumXControlPoint;
    int minimumcontrolPointInt;
};



std::array<LTXPoint,2> MinimumAndMaximumOfCubicCurve(LTXCubicBezier curve)
{

    LTXQuadraticBezier Derivative = curve.Derivative();

    LTXPoint C = ((curve.P0 * -1) + (curve.P1));
    LTXPoint B = (2*(curve.P0 - (2*curve.P1) + curve.P2));
    LTXPoint A = ((curve.P0 * -1) + (3*curve.P1) - (3*curve.P2) + (curve.P3));

    float tx1 = ((-B.x/2) + sqrt(pow((B.x/2),2) - (A.x * C.x)))/A.x;
    float tx2 = ((-B.x/2) - sqrt(pow((B.x/2),2) - (A.x * C.x)))/A.x;

    float ty1 = ((-B.y/2) + sqrt( pow((B.y/2),2) - (A.y * C.y)))/A.y;
    float ty2 = ((-B.y/2) - sqrt( pow((B.y/2),2) - (A.y * C.y)))/A.y;

    LTXPoint px1 = curve.Sample(tx1);
    LTXPoint px2 = curve.Sample(tx2);
    LTXPoint px3 = curve.Sample(ty1);
    LTXPoint px4 = curve.Sample(ty2);

    px1.ReadNamed();
    px2.ReadNamed();
    px3.ReadNamed();
    px4.ReadNamed();

    std::array<LTXPoint,2> retValue;




    return retValue;
    
    
}

void DrawLTXLine(LTXPoint A, LTXPoint B)
{
    printf("\\draw (%f,%f) -- (%f,%f);\n", A.x, A.y, B.x, B.y);
}

std::array<double, 4> MinMaxGP(LTXCubicBezier curve)
{

    std::array<double, 4> t_solutions;

    double i = curve.P1.x - curve.P0.x;
    double j = curve.P2.x - curve.P1.x;
    double k = curve.P3.x - curve.P2.x;

    double a = (3*i - 6*j + 3*k);
    double b = (6*j - 6*i);
    double c = 3*i;

    double sqrtPart = (b * b) - (4 * a * c);
    bool hasSolution = sqrtPart >= 0;
    if (!hasSolution) {std::cout << " No solution" << std::endl;}


    double t1 = (-b + sqrt(sqrtPart)) / (2 * a);
    double t2 = (-b - sqrt(sqrtPart)) / (2 * a);

    t_solutions[0] = t1;
    t_solutions[1] = t2;

    i = curve.P1.y - curve.P0.y;
    j = curve.P2.y - curve.P1.y;
    k = curve.P3.y - curve.P2.y;

    a = (3*i - 6*j + 3*k);
    b = (6*j - 6*i);
    c = 3*i;

    sqrtPart = (b * b) - (4 * a * c);
    hasSolution = sqrtPart >= 0;
    if (!hasSolution) {std::cout << " No solution" << std::endl;}


    t1 = (-b + sqrt(sqrtPart)) / (2 * a);
    t2 = (-b - sqrt(sqrtPart)) / (2 * a);

    t_solutions[2] = t1;
    t_solutions[3] = t2;

    return t_solutions;

}


struct LTXRect
{
    LTXPoint bottomLeft;
    LTXPoint topRight;

    void ReadNamed()
    {
        char r1[2] = {(char)(rand() % 26 + 'a'), (char)(rand() % 26 + 'a')};
        char r2[2] = {(char)(rand() % 26 + 'a'), (char)(rand() % 26 + 'a')};

        PrintLTXLatexPoint(bottomLeft, r1);
        PrintLTXLatexPoint(topRight, r2);

        printf("\\draw (%c%c) rectangle (%c%c);", r1[0], r1[1], r2[0], r2[1]);
    }
};

LTXRect operator+(LTXRect E, LTXPoint V)
{
    LTXRect ReturnRext;
    ReturnRext.bottomLeft = LTXPoint();
    ReturnRext.topRight = LTXPoint();
    return {E.bottomLeft + V, E.topRight + V};
    
}

std::array<double, 4> CubicExtrema(LTXCubicBezier curve)
{

    std::array<double, 4> t_solutions;

    double i = curve.P1.x - curve.P0.x;
    double j = curve.P2.x - curve.P1.x;
    double k = curve.P3.x - curve.P2.x;

    double a = (3*i - 6*j + 3*k);
    double b = (6*j - 6*i);
    double c = 3*i;

    double sqrtPart = (b * b) - (4 * a * c);
    bool hasSolution = sqrtPart >= 0;
    if (!hasSolution) {return std::array<double, 4>{ {-1,-1,-1,-1}};}


    double t1 = (-b + sqrt(sqrtPart)) / (2 * a);
    double t2 = (-b - sqrt(sqrtPart)) / (2 * a);

    t_solutions[0] = t1;
    t_solutions[1] = t2;

    i = curve.P1.y - curve.P0.y;
    j = curve.P2.y - curve.P1.y;
    k = curve.P3.y - curve.P2.y;

    a = (3*i - 6*j + 3*k);
    b = (6*j - 6*i);
    c = 3*i;


    t1 = (-b + sqrt(sqrtPart)) / (2 * a);
    t2 = (-b - sqrt(sqrtPart)) / (2 * a);
    
    t_solutions[2] = t1;
    t_solutions[3] = t2;
    
    return t_solutions;

}

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

void CubicFormula(double a, double b, double c, double d)
{
    double x = 0.0;
    double t = x + (b/(3*a));
    double p = ((3*a*c)-(pow(b,2)))/(3*pow(a,2));
    double q = ((2*pow(b,3))-(9*a*b*c) + (27*pow(a,2)*d))/(27*pow(a,3));
}

struct QuadraticSolution
{
    double x0;
    double x1;
};

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

CubicSolution CubicRootFormulaRobotBroken(double a, double b, double c, double d)
{
    double a0 = d;
double a1 = c;
double a2 = b;
double d3 = a;

double p = ((3*a1)-(pow(a2,2)))/3.0f;
double q = ((9*a1*a2)-(27*a0)-(2*pow(a2,3)))/27.0f;

// cubic discriminant
double delta = pow(q/3.0f, 2.0f) + pow(p/3.0f, 3.0f);
std::cout << delta << std::endl;
if (delta > 0) {
    // three distinct real roots
    double sqrt_delta = sqrt(delta);
    double u = cbrt((-q/2.0f) + sqrt_delta);
    double v = cbrt((-q/2.0f) - sqrt_delta);
    double root1 = u + v - a2 / 3.0f;
    double root2 = -0.5 * (u + v) - a2 / 3.0f + sqrt(3.0) * 0.5 * (u - v);
    double root3 = -0.5 * (u + v) - a2 / 3.0f - sqrt(3.0) * 0.5 * (u - v);

    return {root1, root2, root3};
} else if (delta == 0) {
    // one real root (repeated root)
    double root1 = -cbrt(q/2.0f) - a2/3.0f;

    return {root1, -16969, -16969};
} else {
    // complex roots (delta < 0)
    double theta = acos(-q / (2.0f * sqrt(-(p / 3.0f) * (p / 3.0f) * (p / 3.0f))));
    double root1 = 2.0f * sqrt(-(p / 3.0f)) * cos(theta / 3.0f) - a2 / 3.0f;
    double root2 = 2.0f * sqrt(-(p / 3.0f)) * cos((theta + 2.0f * M_PI) / 3.0f) - a2 / 3.0f;
    double root3 = 2.0f * sqrt(-(p / 3.0f)) * cos((theta + 4.0f * M_PI) / 3.0f) - a2 / 3.0f;

    return {root1, root2, root3};
}
}

struct LTXParaline
{
    LTXPoint inital;
    LTXPoint direction;

    LTXParaline(LTXPoint A, LTXPoint B)
    {
        direction = B-A;
        inital = A;
    }

    LTXPoint Sample(double t)
    {
        return inital + (t*direction);
    }

};



LTXRect CubicBounding(LTXCubicBezier curve)
{
    const std::array<double, 4> Extrema = MinMaxGP(curve);

    double MinX = MinTwo(curve.P0.x, curve.P0.x, curve.P3.x);
    double MinY = MinTwo(curve.P0.y, curve.P0.y, curve.P3.y);

    double MaxX = MaxTwo(curve.P0.x, curve.P0.x, curve.P3.x);
    double MaxY = MaxTwo(curve.P0.y, curve.P0.y, curve.P3.y);

    LTXPoint Sample;

    for(int i = 0; i < 4; i++)
    {
        

        if(Extrema[i] >= 0 && Extrema[i] <= 1)
        {
            Sample = curve.Sample(Extrema[i]);
            MinX = (Sample.x < MinX) ? Sample.x : MinX;
            MinY = (Sample.y < MinY) ? Sample.y : MinY;
            MaxX = (Sample.x > MaxX) ? Sample.x : MaxX;
            MaxY = (Sample.y > MaxY) ? Sample.y : MaxY;
        }
    }

    return {{MinX, MinY}, {MaxX, MaxY}};

}



struct LTXCCWCubicList
{
private:
    LTXRect BoundingContainer;
    std::list<LTXCubicBezier> edgeList;
    std::array<LTXPoint,2> Extrema;
public:
    LTXCCWCubicList(){}

    void UpdateExtrema(LTXCubicBezier curve)
    {
        const std::array<double, 4> Extrema = MinMaxGP(curve);
        BoundingContainer.bottomLeft.x = MinTwo(BoundingContainer.bottomLeft.x, curve.P0.x, curve.P3.x);
        BoundingContainer.bottomLeft.y = MinTwo(BoundingContainer.bottomLeft.y, curve.P0.y, curve.P3.y);

        BoundingContainer.topRight.x = MaxTwo(BoundingContainer.topRight.x, curve.P0.x, curve.P3.x);
        BoundingContainer.topRight.y = MaxTwo(BoundingContainer.topRight.y, curve.P0.y, curve.P3.y);

        LTXPoint Sample;

        for(int i = 0; i < 4; i++)
        {

            if(Extrema[i] >= 0 && Extrema[i] <= 1)
            {
                Sample = curve.Sample(Extrema[i]);
                BoundingContainer.bottomLeft.x = (Sample.x < BoundingContainer.bottomLeft.x) ? Sample.x : BoundingContainer.bottomLeft.x;
                BoundingContainer.bottomLeft.y = (Sample.y < BoundingContainer.bottomLeft.y) ? Sample.y : BoundingContainer.bottomLeft.y;
                BoundingContainer.topRight.x = (Sample.x > BoundingContainer.topRight.x) ? Sample.x : BoundingContainer.topRight.x;
                BoundingContainer.topRight.y = (Sample.y > BoundingContainer.topRight.y) ? Sample.y : BoundingContainer.topRight.y;
            }
        }

    }

    void Append(LTXCubicBezier Bezier)
    {
        if(edgeList.empty())
        {
            edgeList.push_back(Bezier);
            UpdateExtrema(Bezier);

            return;
        }
        UpdateExtrema(Bezier);
        LTXCubicBezier EndOfList = edgeList.back();
        Bezier.P0 = EndOfList.P3;
        edgeList.push_back(Bezier);
    }

    void NormalizedAppension(LTXCubicBezier Bezier)
    {
        //Gather Bounding Box Coordinates.
        LTXCubicBezier End = edgeList.back();
        const LTXRect BoundingContainerOfEnd = CubicBounding(End);

        LTXQuadraticBezier Derivative = End.Derivative();
        //Generate Tangent Vector at T = 1
        LTXPoint TangentVector = Derivative.Sample(1.0);


    }


    void DrawOut()
    {
        for(std::list<LTXCubicBezier>::iterator i = edgeList.begin(); i != edgeList.end(); i++)
        {
            (*i).ReadNamed();
        }
    }

    
    ~LTXCCWCubicList(){}
};

CubicSolution cubicsolve(double a, double b, double c, double d)
{
    

    if (a == 0)
    {
        //alert("The coefficient of the cube of x is 0. Please use the utility for a SECOND degree quadratic. No further action taken.");
        return CubicSolution();
    } //End if a == 0

    if (d == 0)
    {
        //alert("One root is 0. Now divide through by x and use the utility for a SECOND degree quadratic to solve the resulting equation for the other two roots. No further action taken.");
        return CubicSolution();
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

CubicSolution LineCubicIntersection(LTXCubicBezier curve, LTXParaline line)
{
    LTXPoint a = (curve.P3 - (3*curve.P2) + (3*curve.P1) - curve.P0);
    LTXPoint b = ((3*curve.P2) - (6*curve.P1) + (3*curve.P0));
    LTXPoint c = ((3*curve.P1) - (3*curve.P0));
    LTXPoint d = (curve.P0);

    //s = ((a,b,c,d)x - line.initial)/line.direction
    //s = ((a,b,c,d)x)/line.direction - (line.inital)/line.direction
    if(line.direction.x == 0)
    {
        line.direction.x += 0.01; line.direction.y += 0.01;
    };
    double dex = (d.x-line.inital.x);
    double ycubic[4] =
    {
        (a.x/line.direction.x)*line.direction.y, (b.x/line.direction.x)*line.direction.y, (c.x/line.direction.x)*line.direction.y, ((dex/line.direction.x)*line.direction.y)+line.inital.y
    };

    //plug into y function

    //(a,b,c,d)y = line.inital.y + line.direction.y(ycubic)

    double xcubic[4] =
    {
        a.y-ycubic[0], b.y-ycubic[1], c.y-ycubic[2], d.y-ycubic[3]
    };

    CubicSolution x = cubicsolve(xcubic[0], xcubic[1], xcubic[2], xcubic[3]);

    std::cout << std::endl << "Beginning of solutions" << std::endl;

    LTXPoint s0 = curve.Sample(x.r0);
    //s0.ReadNamed();
    LTXPoint s1 = curve.Sample(x.r1);
    //s1.ReadNamed();
    LTXPoint s2 = curve.Sample(x.r2);
    //s2.ReadNamed();

    //assert which solutions are correct

    
    double ax31 = (a.x * pow(x.r0,3))/line.direction.x;
    double bx31 = (b.x * pow(x.r0,2))/line.direction.x;
    double cx31 = (c.x * x.r0)/line.direction.x;
    double dx31 = (d.x-line.inital.x)/line.direction.x;

    double y1 = ((a.x * pow(x.r0,3))/line.direction.x) + ((b.x * pow(x.r0,2))/line.direction.x) + ((c.x * x.r0)/line.direction.x) + ((d.x-line.inital.x)/line.direction.x);
    double y2 = ((a.x * pow(x.r1,3))/line.direction.x) + ((b.x * pow(x.r1,2))/line.direction.x) + ((c.x * x.r1)/line.direction.x) + ((d.x-line.inital.x)/line.direction.x);
    double y3 = ((a.x * pow(x.r2,3))/line.direction.x) + ((b.x * pow(x.r2,2))/line.direction.x) + ((c.x * x.r2)/line.direction.x) + ((d.x-line.inital.x)/line.direction.x);

    if(y1 <= -5.7887187949745567e-06 || y1 >= 1.0)
    {
        std::cout << "y1 not a solution" << std::endl;
    }
    if(y2 <= -5.7887187949745567e-06 || y2 >= 1.0)
    {
        std::cout << "y2 not a solution" << std::endl;
    }
    if(y3 < -5.7887187949745567e-06 || y3 >= 1.0)
    {
        std::cout << "y3 not a solution" << std::endl;
    }

    LTXPoint lineSmpl = line.Sample(y1);
    lineSmpl.ReadNamed();
    lineSmpl = line.Sample(y2);
    lineSmpl.ReadNamed();
    lineSmpl = line.Sample(y3);
    lineSmpl.ReadNamed();


    

    



}

//Detangler Algorithm

//Planar Orthographic Projection Of Control Points between -1.0 and 1.0

//

int main()
{
    srand(time(NULL));

    double t = 0.5;

    LTXCubicBezier t0(0.0, 2.02, -1.0, 0.0, 1.0, 3.0, -1.0, 0.0);
    t0.ReadNamed();
    LTXQuadraticBezier t1 = t0.Derivative();

    LTXPoint TangentVector = t1.Sample(t);

    LTXRect Rect = CubicBounding(t0);
    Rect.ReadNamed();

    // LTXPoint LineOrigin = {-1.0, 0.8};
    // LTXPoint LineDestination = {1.0, 2.0};

    // LTXParaline IntersectionLine(LineOrigin, LineDestination);

    // LineCubicIntersection(t0, IntersectionLine);
    


    
    
    //Tangent Thing
    
    double AreaOfRect = (Rect.topRight.x - Rect.bottomLeft.x)*(Rect.topRight.y - Rect.bottomLeft.y);
    LTXPoint Nextantial = t0.Sample(t) + (AreaOfRect/2)*Normalize(TangentVector);
    LTXLineSegment a1(t0.Sample(t), Nextantial);
    LTXRect TangentRect = {a1.P, a1.Q};
    TangentRect.ReadNamed();
    a1.ReadNamed();

    LTXParaline LeftEdge(TangentRect.bottomLeft, {TangentRect.bottomLeft.x, TangentRect.topRight.y});

    LineCubicIntersection(t0, LeftEdge);

    double a = 1.0;
    double b = 12.0;
    double c = 14.0;
    double d = 4.0;
    CubicSolution sol = cubicsolve(a, b, c, d);
    //sol.Read();    


    
    
    return 1;
   
}