#version 460 core

layout(location = 0) in vec3 apos;
layout(location = 1) in vec2 uv;

out vec2 o_uv;

void main()
{
    o_uv = uv;
    gl_Position = vec4(apos, 1.0);

}