#version 460 core
layout(location = 0) in vec3 apos;

uniform mat4 coordinateProjection;
uniform mat4 projection;
uniform mat4 view;


void main()
{
    gl_Position = projection*view*(coordinateProjection*vec4(apos,1.0));
}