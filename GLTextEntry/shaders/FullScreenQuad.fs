#version 460 core
in vec2 o_uv;

uniform sampler2D atexture;

void main()
{
    vec4 t = texture(atexture, o_uv);
    gl_FragColor = t;
}