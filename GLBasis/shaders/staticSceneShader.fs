#version 460 core

in vertexData
{
    vec2 uv;
    vec3 normal;
    vec3 color;
}   inData;

void main()
{
    vec3 color = inData.color;
    gl_FragColor = vec4(color.x, color.y, color.z, 1.0);
}






