#ifndef LIGHTS_H
#define LIGHTS_H
#include <vector>
#include "LearnOpenglHelper.h"
#include "FGeom.h"
#include "Camera.h"


struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct LightRenderingFactory
{
private:
    NGLProgram program;

    int subdivisions = 4;
public:
    LightRenderingFactory()
    {

    }

    int AddLight(vec4 m_Center, vec4 color)
    {
        
    }

    void UpdateLight(int ithLight)
    {

    }

    ~LightRenderingFactory()
    {

    }

};

LightRenderingFactory lightFactory;


struct Light{
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    vec4 position;
    Light(vec4 am, vec4 dif, vec4 spec, vec4 pos) : ambient(am), diffuse(dif), specular(spec), position(pos)
    {
        lightFactory.AddLight(pos, dif);
    }
};



#endif