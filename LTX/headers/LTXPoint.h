#ifndef LTXP
#define LTXP

#include "stdio.h"
#include <math.h>
struct LTXPoint
{
  float x;
  float y;
  LTXPoint(){
    x = 0;
    y = 0;
  }
  LTXPoint(float X, float Y)
  {
      x = X;
      y = Y;
  }
  LTXPoint operator -(const LTXPoint B)
  {
      LTXPoint sub;
      sub.x = x - B.x;
      sub.y = y - B.y;
      return sub;
  }
  
  
  ~LTXPoint(){}
    
};

  LTXPoint operator *(int i, const LTXPoint T)
  {
      LTXPoint sub;
      sub.x = T.x * i;
      sub.y = T.y * i;
      return sub;
  }
  LTXPoint operator *(const LTXPoint T, int i)
  {
      LTXPoint sub;
      sub.x = T.x * i;
      sub.y = T.y * i;
      return sub;
  }
  LTXPoint operator /(const LTXPoint T, const LTXPoint U)
  {
    return {T.x/U.x, T.y/U.y};
  }
  LTXPoint operator *(const LTXPoint T, float t)
  {
      return LTXPoint(T.x * t, T.y * t);
  }
  LTXPoint operator *(double t,const LTXPoint T)
  {
      return LTXPoint(T.x * t, T.y * t);
  }
  LTXPoint operator +(const LTXPoint T, const LTXPoint U )
  {
      return LTXPoint(T.x + U.x, T.y + U.y);
  }
  bool operator !=(const LTXPoint T, const LTXPoint U)
  {
      if(T.x != U.x && T.y != U.y)
      {
          return true;
      }
      return false;
      
  }

double Magnitude(const LTXPoint P)
{
    return sqrt(pow(P.x,2) + pow(P.y,2));
}
void PrintLTXPoint(LTXPoint A)
{
    printf("( %f , %f )\n", A.x, A.y);
}

void PrintLTXLatexPoint(LTXPoint A, const char* name)
{
    printf("\\coordinate (%c%c) at ", name[0], name[1]);
    printf("( %f , %f );\n", A.x, A.y);
}



void PrintPointArray(LTXPoint* values, int num)
{
    for(int i = 0; i < num; i++)
    {
        PrintLTXPoint(values[i]);
    }
}

#endif