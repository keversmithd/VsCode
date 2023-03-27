#version 330 core

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D ourTexture;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
    //ambient and diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos-FragPos);
    float diff = max(dot(norm, lightDir),0.0);
    vec3 diffuse = diff * lightColor;
    float ambient = 0.1;
    
    //specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  


    if(TexCoord.x <= 0.0 || TexCoord.y <= 0.0)
    {
        gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    }else
    {
        gl_FragColor = texture(ourTexture, TexCoord) * vec4((ambient + diffuse + specular), 1.0);
    }

    //gl_FragColor = vec4(Normal, 1.0);

    
    
    
}