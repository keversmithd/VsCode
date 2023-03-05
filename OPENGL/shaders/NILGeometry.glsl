#version 460 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in Data
{
    vec2 pos;
    vec2 texcoords;

} inData[];

out Data
{
    vec2 pos;
    vec2 texcoords;
} outData;

void main()
{
    outData.texcoords = inData[0].texcoords;
    gl_Position = vec4(inData[0].pos,0.0,1.0);
    EmitVertex();
    
    outData.texcoords = inData[1].texcoords;
    gl_Position = vec4(inData[1].pos,0.0,1.0);
    EmitVertex();

    outData.texcoords = inData[2].texcoords;
    gl_Position = vec4(inData[2].pos,0.0,1.0);
    EmitVertex();

    EndPrimitive();

}
