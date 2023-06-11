#version 460 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texcoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 o_texcoord;
out vec3 o_normal;

uniform vec2 nodalDisplacement;
uniform vec3 nodalLocation[2];
uniform vec3 forceDirection;

void main()
{   

    vec3 originalPos = position;

    vec3 start = nodalLocation[0];
    vec3 end = nodalLocation[1];
    vec3 axis = end - start;
    float L = length(axis);
    float startLength = length(originalPos - start);
    float x = startLength / length(axis);

    float shape1 = (1-(x/L))*nodalDisplacement.x;
    float shape2 = (x/L)*nodalDisplacement.y;
    
    // Compute the interpolated texture coordinate based on the displacement factor
    o_texcoord = vec2(x, nodalDisplacement.x);

    vec3 shapeDirection = forceDirection*shape1*shape2;
    vec3 deformedPos = originalPos+shapeDirection;
    
    

    // Transform the deformed position using the provided matrices
    gl_Position = projection * view * model * vec4(deformedPos, 1.0);

    // Pass the original normal to the fragment shader
    o_normal = normal;
}