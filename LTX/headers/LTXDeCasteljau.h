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