#version 460 core

in vec2 o_tex;
in vec4 o_norm;
uniform float time;
void main()
{
	
	gl_FragColor = vec4(o_norm.y);
}
