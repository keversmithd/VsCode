#version 330 core

in vec2 TexCoord;

uniform sampler2D ourTexture;

in vec4 goroud;

void main()
{
     
    gl_FragColor = texture(ourTexture, TexCoord) * goroud;
}