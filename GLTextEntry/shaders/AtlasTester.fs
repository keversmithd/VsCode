#version 460 core

in vec2 o_uv;


uniform sampler2D atlas;

void main()
{
    gl_FragColor = vec4(1,0,0,texture(atlas, o_uv).x);
}