#version 460 core

in vec3 normal;
in vec3 tangent;
in vec3 FragPos;
in vec2 o_uv;

uniform sampler2D NormalMap;

uniform vec3 viewPos;
uniform vec3 lightPos;

void main()
{
    
    gl_FragColor = texture(NormalMap, o_uv);

    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 norm = normalize(normal);
    float diff = max(dot(lightDir, norm),0.0);
    
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec  * vec3(1,1,1); 


    gl_FragColor = vec4(viewPos + lightPos, 1.0) * vec4((0.1 + diff + specular), 1.0);
    //gl_FragColor = vec4(normal, 1.0);
    
}
