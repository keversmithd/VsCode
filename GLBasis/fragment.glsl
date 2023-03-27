#version 330 core

in vec2 TexCoord;

struct Material{
    sampler2D diffuse;
    sampler2D specular;
};

uniform Material material;
uniform sampler2D ourTexture;

in vec3 diffuse;
in vec3 specular;
in vec3 ambient;

void main()
{
    vec4 diffuseMap = texture(material.diffuse, TexCoord);
    vec4 specularMap = texture(material.specular, TexCoord);
    vec4 diff = vec4(diffuse,1.0) * diffuseMap;
    vec4 spec = vec4(specular,1.0) * specularMap;

    gl_FragColor = diff + spec + vec4(ambient,1.0);
}