#version 460 core
layout(location = 0) in vec4 a_tex;


void main()
{
	gl_Position = vec4(a_tex.x, a_tex.y, a_tex.z, 1.0);
}