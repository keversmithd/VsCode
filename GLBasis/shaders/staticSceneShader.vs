#version 460 core
//Fourth location in position is the integer id, that indexes into a static uniform buffer.

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;
layout (location = 3) in vec3 color;


layout(std430, binding = 0) buffer objectMetaData{
    mat4 data[];
};

out vertexData
{
    vec2 uv;
    vec3 normal;
    vec3 color;
} outData;


void main()
{
    outData.uv = uv;
    outData.normal = normal;
    outData.color = color;
    gl_Position = vec4(position.x, position.y, position.z, 1.0);
}

