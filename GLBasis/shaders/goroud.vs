#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;
layout (location = 2) in vec3 aNorm;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

out vec4 goroud;

void main()
{
    vec3 FragPos = vec3(model * vec4(aPos, 1.0));

    //ambient and diffuse
    vec3 norm = normalize(aNorm);
    vec3 lightDir = normalize(lightPos-FragPos);
    float diff = max(dot(norm, lightDir),0.0);
    vec3 diffuse = diff * lightColor;
    float ambient = 0.1;
    
    //specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 8);
    vec3 specular = specularStrength * spec * lightColor; 

    goroud = vec4((ambient + diffuse + specular), 1.0);

    TexCoord = aTex;



    gl_Position = projection * view * model * vec4(aPos, 1.0);
}