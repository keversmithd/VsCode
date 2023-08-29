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

uniform vec3 viewPos;

void main()
{
    Light CurrentLight = lightData[0];
    vec3 diffuse = vec3(0);
    vec3 tnorm = normalize(texture(NormalMap, o_uv).xyz);
    vec3 norm = normalize(normal)+tnorm;
    vec3 lightDir = vec3(0);

    // CurrentLight = lightData[0];
    lightDir = normalize(CurrentLight.position.xyz-FragPos);
    float d = max(dot(norm, lightDir), 0.0);
    diffuse += d*CurrentLight.diffuse.xyz;

    float specularStrength = 0.2;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * CurrentLight.specular.xyz; 

    gl_FragColor = vec4(0,0.2,0.4,0.8)*vec4(diffuse+specular+vec3(1,1,1),1);

}
