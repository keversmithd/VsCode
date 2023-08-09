#version 460 core
in vec2 o_uv;

uniform sampler2D atlas;

void main()
{
    vec4 t = texture(atlas, o_uv);
    gl_FragColor = t;
}