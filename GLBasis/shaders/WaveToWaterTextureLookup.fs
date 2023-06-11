#version 460 core



in vec2 o_uv;

uniform sampler1D WaveTexture;

void main()
{
    vec4 r = texture(WaveTexture, o_uv.x);

    gl_FragColor = r;
}