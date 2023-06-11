#ifndef DOMAIN_BASED_AXIS
#define DOMAIN_BASED_AXIS

#include "LearnOpenglHelper.h"

struct AxisBaseRenderer
{
public:
    vec3* vertex;
    vec3* color;

    int size;
    int capacity;

    NGLProgram AxisShader;
public:
    AxisBaseRenderer()
    {

    }

    void AddGeometry(vec3 item)
    {
        if(size+1 > capacity)
        {
            resize();
        }
        vertex[size] = item;
        size++;
    }

    void Draw()
    {

    }
};

AxisBaseRenderer AxisRenderer;

struct Axis
{
    Axis(vec2 Start, vec2 End, double dx, double dy)
    {

    }
};

#endif