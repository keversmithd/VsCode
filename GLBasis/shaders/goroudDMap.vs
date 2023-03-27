#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;
layout (location = 2) in vec3 aNorm;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


uniform vec3 lightPos;
uniform vec3 viewPos;

out vec3 diffuse;
out vec3 ambient;
out vec3 specular;



struct Light{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform Light light;

void main()
{
    vec3 FragPos = vec3(model * vec4(aPos, 1.0));

    //ambient and diffuse
    vec3 norm = normalize(aNorm);
    vec3 lightDir = normalize(lightPos-FragPos);
    float diff = max(dot(norm, lightDir),0.0);
    diffuse = light.diffuse * diff;
    ambient = light.ambient;
    
    //specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), light.shininess);
    specular = spec * light.specular; 


    TexCoord = aTex;

    gl_Position = projection * view * model * vec4(aPos, 1.0);
}