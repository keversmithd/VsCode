#version 460 core

layout(triangles, equal_spacing, ccw) in;

in Data
{
	vec2 texcoords;
	vec2 pos;
} inData[];

out Data
{
	vec2 texcoords;
	vec2 pos;
} outData;


void main()
{
	outData.pos =
    gl_TessCoord[0] * inData[0].pos  +
    gl_TessCoord[1] * inData[1].pos +
    gl_TessCoord[2] * inData[2].pos;

    outData.texcoords =
    gl_TessCoord[0] * inData[0].texcoords +
    gl_TessCoord[1] * inData[1].texcoords +
    gl_TessCoord[2] * inData[2].texcoords;

    gl_Position = vec4(outData.pos,0.0, 1.0);
	
}