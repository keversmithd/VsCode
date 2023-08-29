#ifndef LTXP
#define LTXP

#include "stdio.h"
#include <math.h>
#define PI 3.14159265359

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
  void normalize()
  {
    float m = sqrt(x*x + y*y);
    if(m == 0)
    {
      x=0;
      y=0;
      return;
    }
    x/=m;
    y/=m;

  }
  void operator +=(const LTXPoint R)
  {
    x += R.x;
    y += R.y;
  }
  void operator *=(const float V)
  {
    x*=V;
    y*=V;
  }
  inline LTXPoint operator -(LTXPoint A)
  {
    A.x = x - A.x;
    A.y = y - A.y;
    return A;
  }
  inline LTXPoint operator*(LTXPoint C)
  {
    C.x *= x;
    C.y *= y;
    return C;
  }
  inline LTXPoint operator*(int C)
  {
    return {x*C, y*C};
  }
  inline LTXPoint operator*(float A)
  {
    return {x*A,y*A};
  }
  inline LTXPoint operator+(LTXPoint B)
  {
    return {x+B.x, y+B.y};
  }

  inline LTXPoint operator-(){
    return {-x, -y};
  }
  inline LTXPoint operator/(float C)
  {
      return {x/C, y/C};
  }

  inline float dot(const LTXPoint A)
  {
    return {x*A.x + y*A.y};
  }

  void operator/=(const float V)
  {
    if(V == 0)
    {
      x = 0;
      y = 0;
      return;
    }
    x /= V;
    y /= V;
  }

  float mag()
  {
    return sqrt(x*x + y*y);
  }

  void ReadNamed()
  {
    char r1[2] = {(char)(rand() % 26 + 'a'), (char)(rand() % 26 + 'a')};
    printf("\\coordinate (%s) at ( %f pt, %f pt);\n", r1, x, y);
    printf("\\draw (%s) circle (2pt);\n", r1);
  }
  
  void rotate(float degrees, LTXPoint center)
  {
    float rads = degrees*(PI/180.0);
    x -= center.x;
    y -= center.y;

    float new_x = x * cos(rads) - y * sin(rads);
    float new_y = x * sin(rads) + y * cos(rads);

    x = new_x + center.x;
    y = new_y + center.y;

  }


  void reflectLine(LTXPoint AXA, LTXPoint AXB)
  {
    LTXPoint axis = AXB-AXA;
    LTXPoint n = {-axis.y, axis.x};
    LTXPoint T = {x,y};

    LTXPoint V = T-AXA;

    float am = axis.mag();
    float vd = V.dot(axis);
    float nm = n.mag();

    if(am == 0 || nm == 0)
    {
      return;
    }

    LTXPoint A = AXA + (axis/am)*(vd/am);
    LTXPoint P =  (n/nm) * (V.dot(n)/n.mag());

    x=A.x - P.x;
    y=A.y - P.y;
  }

  LTXPoint ProjectOnto(LTXPoint AX, LTXPoint AY)
  {
      LTXPoint axis = AY-AX;
      LTXPoint T = {x,y};
      LTXPoint V = AX-T;

      float am = axis.mag();
      float Vd = -(V.dot(axis))/(am*am);

      Vd = (Vd < 0) ? 0 : (Vd > 1) ? 1 : Vd;
      
      return AX + (axis*Vd);
  }

  void reflect(LTXPoint axis)
  {
    LTXPoint n = {-axis.y,axis.x};
    
    LTXPoint A = {x,y};
    float magA = A.mag();
    float magN = n.mag();
    if(magA*magN == 0)
    {
      return;
    }
    LTXPoint reflection = (n/n.mag())*2*(n.dot(A)/(magN));

    x -= reflection.x;
    y -= reflection.y;
    
  }

  ~LTXPoint(){}
    
};


  LTXPoint rotate(LTXPoint v, float degrees)
  {
    float rads = degrees*(PI/180.0);
    return {v.x*cos(rads)-v.y*sin(rads), v.x*sin(rads)+v.y*cos(rads)};
  }

  float dot(LTXPoint A, LTXPoint B)
  {
    return ((A.x*B.x) + (A.y*B.y));

  }


  LTXPoint pow(const LTXPoint A, int B)
  {
    return {pow(A.x,B), pow(A.y, B)};
  }
  LTXPoint sqrt(const LTXPoint A)
  {
    return {sqrt(A.x), sqrt(A.y)};
  }
  LTXPoint operator *(int i, const LTXPoint T)
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

  LTXPoint operator *(double t,const LTXPoint T)
  {
      return LTXPoint(T.x * t, T.y * t);
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

float angle(LTXPoint A, LTXPoint B)
{
  
}


inline LTXPoint Normalize(const LTXPoint P)
{
  double mag = Magnitude(P);
  return {P.x / mag, P.y / mag};
}




void PrintLTXPoint(LTXPoint A)
{
    printf("( %f , %f )\n", A.x, A.y);
}

void PrintLTXLatexPoint(LTXPoint A, const char* name)
{
    printf("\\coordinate (%c%c) at ", name[0], name[1]);
    printf("( %f pt , %f pt );\n", A.x, A.y);
}



void PrintPointArray(LTXPoint* values, int num)
{
    for(int i = 0; i < num; i++)
    {
        PrintLTXPoint(values[i]);
    }
}

#endif