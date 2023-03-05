#version 460 core

layout(vertices = 3) out;

in Data
{
	vec2 texcoords;
    vec2 pos;
} inData[];

out Data
{
	vec2 texcoords;
    vec2 pos;
} outData[];

#define ID gl_InvocationID

void main()
{
	outData[ID].texcoords = inData[ID].texcoords;
    outData[ID].pos = inData[ID].pos;
    if(ID == 0)
    {
        gl_TessLevelInner[0] = 1;
        gl_TessLevelOuter[0] = 1;
        gl_TessLevelOuter[1] = 1;
        gl_TessLevelOuter[2] = 1;
    }
	
}