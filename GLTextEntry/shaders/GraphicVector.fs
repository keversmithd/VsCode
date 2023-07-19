#version 460 core

in vec2 o_uv;
void main()
{

    gl_FragColor = vec4(o_uv.x, o_uv.x, o_uv.x, 1.0);

}