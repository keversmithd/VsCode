#ifndef VEC_T
#define VEC_T

#include "math.h"

struct vec2
{
    float x, y;

    bool operator !=(const vec2 q)
    {
        return (q.x != x && q.y != y);
    }
};



vec2 operator*(const vec2 a, const double b)
{
    return {static_cast<float>(a.x * b), static_cast<float>(a.y * b)};
}

vec2 operator +(const vec2 a, const vec2 b)
{
    return {a.x + b.x, a.y + b.y};
}

bool operator==(const vec2 a, const vec2 b)
{
    return (a.x == b.x && a.y == b.y);
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