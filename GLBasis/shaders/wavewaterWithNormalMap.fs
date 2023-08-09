#version 460 core

in vec3 normal;
in vec3 tangent;
in vec3 FragPos;
in vec2 o_uv;

uniform sampler2D NormalMap;

struct Light{
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    vec4 position;
};

layout(std140) uniform LightBuffer {
    Light lightData[3];
};


void main()
{
    gl_FragColor = texture(NormalMap, o_uv);
    gl_FragColor = vec4(o_uv.x)*lightData[0].ambient;
}
