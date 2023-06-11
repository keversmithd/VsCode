#version 460 core

in vec2 o_uv;



uniform sampler1D table;


in vec2 o_outerterm;

in vec3 normal;

void main()
{
    
    vec4 r = texture(table, o_uv.x);
    gl_FragColor = vec4(normal.x, normal.y, normal.z, 1.0);
}