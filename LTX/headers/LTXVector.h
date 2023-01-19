#ifndef LTXVEC
#define LTXVEC
#include "math.h"
#include <iostream>
#include "LTXPoint.h"

struct LTXVector
{
  float x;
  float y;
  LTXVector(){
    x = 0;
    y = 0;
  }
  LTXVector(float X, float Y)
  {
      x = X;
      y = Y;
  }
  LTXVector operator -(LTXPoint P)
  {
    LTXVector dir;
    dir.x = x - P.x;
    dir.y = y - P.y;
    return dir;
  }
  ~LTXVector(){}
};





LTXVector Normalize(LTXVector Vec)
{
    float Length = sqrt( pow(Vec.x,2) + pow(Vec.y,2) );
    LTXVector Normalized;
    Normalized.x = Vec.x / Length;
    Normalized.y = Vec.y / Length;
    return Normalized;
}

LTXPoint Cast( LTXPoint P, LTXVector V, float t)
{
    LTXPoint Cast;
    Cast.x = P.x + (V.x * t);
    Cast.y = P.y + (V.y * t);
    return Cast;
}






#endif