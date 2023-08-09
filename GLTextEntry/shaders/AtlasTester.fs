#version 460 core

in vec2 o_uv;


uniform sampler2D atlas;

void main()
{
    vec4 texColor = texture(atlas, o_uv);

    gl_FragColor = vec4(texColor.x,1,1,texColor.x);
}