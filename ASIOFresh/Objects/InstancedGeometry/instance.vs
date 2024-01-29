#version 460 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 norm;

uniform mat4 projection;
uniform mat4 view;

out vec2 o_uv;

struct instanceTransform{
    vec4 posScale;
};

layout(std140) uniform instanceTransforms
{
    instanceTransform models[2];
};

void main(){

    o_uv = uv;

    vec4  posFactor = models[gl_InstanceID].posScale;

    

    mat4 modelMatrx = {
        vec4(0.5,0.0,0.0,0.0),
        vec4(0.0,0.5,0.0,0.0),
        vec4(0.0,0.0,0.5,0.0),
        vec4(0.0,0.0,0.0,1.0),
    };

    vec4 position = vec4(vec3((pos.x*posFactor.w)+posFactor.x, (pos.y*posFactor.w)+posFactor.y, (pos.z*posFactor.w)+posFactor.z),1.0);


    gl_Position = projection*view*position;
}