#ifndef VEC_T
#define VEC_T

#include "math.h"

#include <iostream>

struct vec2;
void SpellTime(const vec2 c, const vec2 v);

struct vec2
{
    float x, y;

    vec2()
    {

    }

    vec2(float _x, float _y) : x(_x), y(_y)
    {

    }

    void display()
    {
        printf("\\draw (%f,%f) circle (2pt);\n", x,y);
    }
    bool operator !=(const vec2 q)
    {
        return (q.x != x && q.y != y);
    }
    bool isZero()
    {
        return (x==0 && y==0);
    }
    void operator *=(vec2 A)
    {
        x *= A.x;
        y *= A.y;
    }
    void operator *=(float A)
    {
        x *= A;
        y *= A;
    }

    void operator +=(vec2 v)
    {
        x += v.x;
        y += v.y;
    }
    void normalize()
    {
        float m = sqrt(x*x + y*y);
        if(m == 0){
            return;
        }
        x /= m;
        y /= m;
    }

    int hash()
    {
        int ix = x;
        int iy = y;
        int ig = (ix ^ iy) + (ix | iy);
        ig = (ig + 0x7ed55d16) + (ig << 12);
        ig = (ig ^ 0xc761c23c) ^ (ig >> 19);
        ig = (ig + 0x165667b1) + (ig << 5);
        ig = (ig + 0xd3a2646c) ^ (ig << 9);
        ig = (ig + 0xfd7046c5) + (ig << 3);
        ig = (ig ^ 0xb55a4f09) ^ (ig >> 16);
        return ig;
    }
};


bool operator ==(const vec2 c, const vec2 d)
{
    return (c.x == d.x && c.y == d.y);
}


vec2 operator*(const vec2 a, const double b)
{
    return {static_cast<float>(a.x * b), static_cast<float>(a.y * b)};
}

vec2 operator*(const vec2 a, const vec2 b)
{
    return {a.x * b.x, a.y * b.y};
}

vec2 operator +(const vec2 a, const vec2 b)
{
    return {a.x + b.x, a.y + b.y};
}

vec2 operator -(const vec2 a, const vec2 b)
{
    return {a.x - b.x, a.y - b.y};
}

double cross(const vec2 a, const vec2 b)
{
    return (a.x * b.y) - (a.y * b.x);
}

double mag(const vec2 a)
{
    return sqrt(pow(a.x,2) + pow(a.y, 2));
}

bool operator <(const vec2 a, const vec2 b)
{
    return (mag(a) < mag(b));
}

vec2 normalize(const vec2 a)
{
    const double m = mag(a);
    return {static_cast<float>(a.x / m), static_cast<float>(a.y / m)};
}

double dot(const vec2 a, const vec2 b)
{
    return (a.x * b.x + a.y * b.y);
}

struct vec2Hash {
    std::size_t operator()(const vec2& v) const {
        std::hash<double> hasher;
        std::size_t seed = 0;
        seed ^= hasher(v.x) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= hasher(v.y) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        return seed;
    }

};

struct vec2Equal {
    bool operator()(const vec2& v1, const vec2& v2) const {
        return v1.x == v2.x && v1.y == v2.y;
    }
};

struct plane
{
    vec2 bottomLeft;
    vec2 topRight;
};

struct line
{
    vec2 start;
    vec2 end;
};

struct doubleline
{
    line x;
    line y;
};


struct rect
{
    vec2 bottomLeft;
    vec2 topRight;

    rect() : bottomLeft(-15955,-15955), topRight(-15955,-15955)
    {

    }

    rect(vec2 a, vec2 b) : bottomLeft(a), topRight(b)
    {

    }


    void scale(const float constant)
    {
        vec2 c = center();
        vec2 cx = (vec2(topRight.x, c.y) - c)*constant;
        vec2 cy = (vec2(c.x, topRight.y) - c)*constant;

        bottomLeft = vec2(c.x-cx.x, c.y-cy.y);
        topRight = vec2(c.x+cx.x, c.y+cy.y);

    }

    vec2 center()
    {
        float mx = bottomLeft.x + ((topRight.x - bottomLeft.x)/2);
        float my = bottomLeft.y + ((topRight.y - bottomLeft.y)/2);

        return {mx,my};
    }

    void scaleby(vec2& p, float constant)
    {
        vec2 c = center();

        vec2 cx = (vec2(topRight.x, c.y)-c);
        vec2 cy = (vec2(c.x, topRight.y)-c);

        vec2 z = p-c;

        vec2 zzx =  (cx*z.x);
        vec2 zzy = (cy*z.x);


        

        SpellTime(c, c+zzx);
        SpellTime(c, c+zzy);


    }

    void render()
    {
        printf("\\draw (%f,%f) rectangle (%f,%f);\n", bottomLeft.x, bottomLeft.y, topRight.x, topRight.y);
    }

    void IncrementBound(vec2 vertex)
    {
        if(bottomLeft == vec2(-15955,-15955) && topRight == vec2(-15955,-15955))
        {
            bottomLeft = vertex;
            topRight = vertex;
        }else
        {
            bottomLeft.x = (vertex.x < bottomLeft.x) ? vertex.x : bottomLeft.x;
            bottomLeft.y = (vertex.y < bottomLeft.y) ? vertex.y : bottomLeft.y;


            topRight.x = (vertex.x > topRight.x) ? vertex.x : topRight.x;
            topRight.y = (vertex.y > topRight.y) ? vertex.y : topRight.y;
        }

    }

};

void SpellTime(const vec2 c, const vec2 v)
{
    printf("\\draw[->] (%f,%f) -- (%f,%f);\n", c.x, c.y, v.x, v.y);
}


bool lineIntersection(const line A, const line B, vec2& intersection)
{
    const vec2 DA = {A.end.x - A.start.x, A.end.y - A.start.y};
    const vec2 DB = {B.end.x - B.start.x, B.end.y - B.start.y};

    const double epsilon = 1e-9; // Tolerance threshold for floating-point comparisons

    double determinant = (DA.x * DB.y) - (DA.y * DB.x);

    if (std::abs(determinant) < epsilon)
    {
        // Lines are parallel or coincident
        return false;
    }

    double s = (A.start.y + (((DA.y * B.start.x) - (DA.y * A.start.x)) / DA.x) - B.start.y) / (DB.y - (DA.y * DB.x / DA.x));
    double t = (B.start.x + (DB.x * s) - A.start.x) / DA.x;

    if (t <= 1 + epsilon && t >= -epsilon && s <= 1 + epsilon && s >= -epsilon)
    {
        intersection.x = A.start.x + DA.x * t;
        intersection.y = A.start.y + DA.y * t;
        return true;
    }

    return false;
}



#endif