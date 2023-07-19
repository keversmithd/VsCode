#version 460 core

in vec3 normal;
in vec3 tangent;



void main()
{
    gl_FragColor = vec4(normal.x, normal.y, normal.z, 0.0);
}
