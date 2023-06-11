#ifndef CH_1_CONVEXHULL
#define CH_1_CONVEXHULL

#include <vector>
#include <algorithm>
#include "vectwo.hpp"
#include "ran.hpp"
#include "CGRead.h"

#pragma region _chrono_pool
// ChronologicalPoolEntry<vec2> ConvexHull(ChronologicalPoolEntry<vec2> P)
// {
//     HeapArray<vec2> Sequence(Compare, P, 0);

//     ChronologicalPoolEntry<vec2> LeftRight = Sequence.Sort();

//     //SpellVector(LeftRight[0], LeftRight[1]);

//     ChronologicalPoolEntry<vec2> UpperHull(0,0);
    
//     vec2 pi;
//     UpperHull.push_back(LeftRight[0]);
//     UpperHull.push_back(LeftRight[1]);

//     //SpellVector(LeftRight[0], LeftRight[1]);

//     int n = LeftRight.size();
//     for(int i = 2; i < n; i++)
//     {
//         pi = LeftRight[i];
        
//         UpperHull.push_back(pi);

//         // SpellVector(UpperHull[UpperHull.tail-2], UpperHull[UpperHull.tail-1]);
//         // SpellVector(UpperHull[UpperHull.tail-1], pi);

//         while(UpperHull.size() > 2 && !RightTurn(UpperHull[UpperHull.tail-2], UpperHull[UpperHull.tail-1], pi))
//         {
//             UpperHull[UpperHull.tail-1] = pi;
//             //UpperHull.detract_back();
//             UpperHull.tail--;
//         }
//         // printf("New Set \n\n");
//         // for(int i = 0; i < UpperHull.size(); i++)
//         // {
//         //     SpellVector(UpperHull[i], "m");
//         // }

//         // int k = 10;

//     }

//     UpperHull.detract_reserve(UpperHull.NumberOfElements-(UpperHull.tail+1));

//     ChronologicalPoolEntry<vec2> LowerHull(0,0);

    
//     LowerHull.push_back(LeftRight[n-1]);
    
//     LowerHull.push_back(LeftRight[n-2]);

//     // printf("New Set \n\n");
//     // for(int i = 0; i < UpperHull.size(); i++)
//     // {
//     //     SpellVector(UpperHull[i], "m");
//     // }

//     for(int i = n-3; i > 0; i--)
//     {
//         pi = LeftRight[i];
//         LowerHull.push_back(pi);
//         while(LowerHull.size() > 2 && !RightTurn(LowerHull[LowerHull.tail-2], LowerHull[LowerHull.tail-1], pi))
//         {
//             LowerHull[LowerHull.tail-1] = LowerHull[LowerHull.tail]; //this delete method does work?
//             //LowerHull.detract_back();
//             LowerHull.tail--;
//         }

//         // printf("New Set \n\n");
//         // for(int i = 0; i < LowerHull.size(); i++)
//         // {
//         //     SpellVector(LowerHull[i], "m");
//         // }
//         // int k = 10;
//     }


//     LowerHull.detract_reserve(LowerHull.NumberOfElements-(LowerHull.tail+1));

//     // printf("New Set \n\n");
//     // for(int i = 0; i < LowerHull.size(); i++)
//     // {
//     //     SpellVector(LowerHull[i], "m");
//     // }
//     // int k = 10;

//     //DisplayDisconnectedEdgeSet(UpperHull);
//     //DisplayDisconnectedEdgeSet(LowerHull);
    
//     UpperHull.AppendAdjacent(LowerHull);
    
//     // printf("New Set \n\n");
//     // for(int i = 0; i < UpperHull.size(); i++)
//     // {
//     //     SpellVector(UpperHull[i], "m");
//     // }

    

//     return UpperHull;
// }

#pragma endregion

std::vector<vec2> SetInPlane(const plane pl, int n)
{   
    if(n < 0)
    {
        return std::vector<vec2>();
    }
    std::uniform_real_distribution<float> leftRight(pl.bottomLeft.x, pl.topRight.x);
    std::uniform_real_distribution<float> downUp(pl.bottomLeft.y, pl.topRight.y);

    std::vector<vec2> elements;
    elements.reserve(n);

    for(int i = 0; i < n; i++)
    {
        elements.push_back({leftRight(mt), downUp(mt)});
    }
    return elements;
}

bool RightTurn(vec2 A, vec2 B,  vec2 C)
{
    vec2 AB = normalize(B-A);
    vec2 BC = normalize(C-B);
    return (cross(AB, BC) < 0);
}

bool LeftOfDirectedLineSegment(const vec2 x, const vec2 p, const vec2 q)
{

    bool suggestion = ((q.x - p.x)*(x.y - p.y) - (q.y - p.y)*(x.x - p.x)) > 0;
    
    //SpellPoint(x, "x");
    //SpellVector(p,q, "pq");
    
    const vec2 Derivative = q-p;
    //SpellVector(Derivative, "D");
    const vec2 HalfPoint = p + Derivative*0.5;
    //SpellPoint(HalfPoint, "H");

    const vec2 InwardHalfNormal = normalize({-Derivative.y, Derivative.x});
    //SpellVector(InwardHalfNormal, "HF");
    const vec2 Split = x - HalfPoint;
    //SpellVector(Split, "S");

    double d = dot(Split, InwardHalfNormal);
    //printf("Proccedure Clear: Prediction: %s, Dot: %f\n", (suggestion == true) ? "true" : "false", d);
    return ((q.x - p.x)*(x.y - p.y) - (q.y - p.y)*(x.x - p.x))>0;
    

    return (d < 0);
}

struct less_than_key
{
    inline bool operator() (const vec2 A, const vec2 B)
    {
       return (A.x < B.x);
    }
};

std::vector<vec2> ConvexHull(std::vector<vec2> P)
{
    // HeapArray<vec2> Sequence(Compare, P, 0);

    // ChronologicalPoolEntry<vec2> LeftRight = Sequence.Sort();
    std::sort(P.begin(), P.end(), less_than_key());

    //SpellVector(LeftRight[0], LeftRight[1]);

    std::vector<vec2> UpperHull;
    
    vec2 pi;
    UpperHull.push_back(P[0]);
    UpperHull.push_back(P[1]);

    //SpellVector(LeftRight[0], LeftRight[1]);

    int n = P.size();
    for(int i = 2; i < n; i++)
    {
        pi = P[i];
        
        UpperHull.push_back(pi);

        // SpellVector(UpperHull[UpperHull.tail-2], UpperHull[UpperHull.tail-1]);
        // SpellVector(UpperHull[UpperHull.tail-1], pi);
        int UpperHullSize = UpperHull.size(); 
        while(UpperHullSize > 2 && !RightTurn(UpperHull[UpperHullSize-3], UpperHull[UpperHullSize-2], pi))
        {
            UpperHull[UpperHullSize-2] = pi;

            //UpperHull.detract_back();
            UpperHullSize--;
        }
    }


    std::vector<vec2> LowerHull;

    
    LowerHull.push_back(P[n-1]);
    
    LowerHull.push_back(P[n-2]);

    for(int i = n-3; i > 0; i--)
    {
        pi = P[i];
        LowerHull.push_back(pi);
        
        int LowerHullSize = LowerHull.size();
        while(LowerHullSize > 2 && !RightTurn(LowerHull[LowerHullSize-3], LowerHull[LowerHullSize-2], pi))
        {
            LowerHull[LowerHullSize-2] = LowerHull[LowerHullSize-1]; //this delete method does work?
            //LowerHull.detract_back();
            LowerHullSize--;
        }

        // printf("New Set \n\n");
        // for(int i = 0; i < LowerHull.size(); i++)
        // {
        //     SpellVector(LowerHull[i], "m");
        // }
        // int k = 10;
    }

    for(int i = 0; i < LowerHull.size(); i++)
    {
        UpperHull.push_back(LowerHull[i]);
    }
    
    return UpperHull;
}

std::vector<vec2> SlowConvexHull(std::vector<vec2> Set)
{
    int n = Set.size();
    std::vector<vec2> ConvexHull(n);
    
    bool edgeFound = true;
    //for all ordered paris in P * P with p not equal to q
    vec2 p;
    vec2 q;

    for(int i = 0; i < n; i++)
    {
        p = Set[i];

        for(int j = 0; j < n; j++)
        {
            if(Set[j] != p)
            {
                q = Set[j];
                edgeFound = true;
                bool runon = false;
                int k = 0;
                for(k = 0; (k < n) && edgeFound == true; k++)
                {
                    if(p != Set[k] && q != Set[k])
                    {
                        runon = true;
                        if(LeftOfDirectedLineSegment(Set[k], p, q))
                        {
                            edgeFound = false;
                        }
                    }
                }

                if(edgeFound == true && runon == true)
                {
                    ConvexHull.push_back(p);
                    ConvexHull.push_back(q);
                }
            }
            
        }

    }

    return ConvexHull;

}

#endif