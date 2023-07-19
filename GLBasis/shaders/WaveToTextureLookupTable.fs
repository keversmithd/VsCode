#version 460 core

in vec2 o_uv;

//layout(location = 0) out vec3 color;

void main()
{
    //color = vec4(cos(2*3.14*o_uv.x*o_uv.y));
    //color = vec3(o_uv.x);
    gl_FragColor = vec4(cos(2*3.14*o_uv.x), 0, 0, 1);
}