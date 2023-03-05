#version 460 core

//ioslines, triangles, quads
//equal_spacing, fractional_even_spacing, fractional_odd_spacing
//ccw, cw

layout(isolines, equal_spacing, ccw) in;


//built-in
//gl_TessCoord, gl_PatchVerticesIn, gl_PrimitiveID

void main()
{
	vec3 p0 = gl_in[0].gl_Position.xyz;
	vec3 p1 = gl_in[1].gl_Position.xyz;
	vec3 p2 = gl_in[2].gl_Position.xyz;
	vec3 pos = (gl_TessCoord.x * p0 + gl_TessCoord.y * p1 + gl_TessCoord.z * p2);
    gl_Position = vec4(pos, 1.0);
}