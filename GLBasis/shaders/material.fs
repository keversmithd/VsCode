#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;

uniform Material material;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D ourTexture;

uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
    vec3 ambient = light.ambient * (material.ambient);

    //ambient and diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos-FragPos);
    float diff = max(dot(norm, lightDir),0.0);
    vec3 diffuse = (diff*material.diffuse) * light.diffuse;

    //specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec*material.specular);  


    if(TexCoord.x <= 0.0 || TexCoord.y <= 0.0)
    {
        gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    }else
    {
        //gl_FragColor = texture(ourTexture, TexCoord) * vec4((ambient + diffuse + specular), 1.0);
        gl_FragColor = vec4((ambient + diffuse + specular), 1.0);
    }

    //gl_FragColor = vec4(Normal, 1.0);

    
    
    
}