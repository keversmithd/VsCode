#ifndef CG_READ_H
#define CG_READ_H
#include "vectwo.hpp"
#include "TArray.h"
#include "PPChronoPool.h"
#include <stdio.h>

std::string s;

void SpellVector(const vec2 v, const char* name = nullptr)
{
    if(name == nullptr)
    {
        printf("\\draw[->] (0,0) -- (%f,%f);\n", v.x, v.y);
    }else
    {
        printf("\\draw[->] (0,0) -- (%f,%f) node [anchor = north, fontscale=0] {$%s$};\n", v.x, v.y, name);
    }
    
}

void SpellPoint(const vec2 v, const char* name = nullptr)
{
    if(name == nullptr)
    {
        printf("\\draw (%f, %f) circle (1pt);\n",  v.x, v.y);
    }
    else{
        printf("\\draw (%f,%f) circle(1pt) node [fontscale=0] {$%s$};\n", v.x, v.y, name);
    }
}

void SpellVector(const vec2 c, const vec2 v, const char* name = nullptr)
{
    if(name == nullptr)
    {
        printf("\\draw[->] (%f,%f) -- (%f,%f);\n", c.x, c.y, v.x, v.y);
    }else
    {
        printf("\\draw[->] (%f,%f) -- (%f,%f) node  [anchor = north, fontscale=0] {$%s$};\n", c.x, c.y, v.x, v.y, name);
    }
    
}

void DisplayConstantEdgeSet(CGConstArray<line> ar)
{
    for(int i = 0; i < ar.size; i++)
    {
        SpellVector(ar[i].start, ar[i].end);
    }
}

void DisplaySet(ChronologicalPoolEntry<vec2> Set)
{
    for(int i = 0; i < Set.size(); i++)
    {
        SpellPoint(Set[i]);
    }
}

void DisplayEdgeSet(line* Set, int N)
{
    char* s = new char[3];
    s[2] = '\0';
    int c = 1;
    for(int i = 0; i < N; i++)
    {
        s[0] = ' ';
        s[1] = c + 48;
        c++;
        SpellVector(Set[i].start, Set[i].end, s);
    }
}

void DisplayVectorEdgeSet(const std::vector<vec2>& Set)
{   
    int vectorSize = Set.size();
    for(int i = 0; i < vectorSize-1; i++)
    {

        SpellVector(Set[i], Set[i+1]);
    }
}


void DisplayVectorSet(const std::vector<vec2>& Set)
{   

    int vectorSize = Set.size();
    for(int i = 0; i < vectorSize-1; i++)
    {
        SpellPoint(Set[i]);
    }
}


#endif