#version 460 core

in vec3 normal;
in vec3 tangent;

void main()
{
    gl_FragColor = vec4(tangent.x, tangent.y, normal.z, 1.0);
}
