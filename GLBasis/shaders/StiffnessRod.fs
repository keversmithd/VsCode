#version 460 core

in vec2 o_texcoord;
in vec3 o_normal;
void main()
{
    gl_FragColor = vec4(o_texcoord.x,o_texcoord.x, o_texcoord.x, 1.0);
}
