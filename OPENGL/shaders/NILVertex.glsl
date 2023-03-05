#version 460 core

layout(location = 0) in vec4 a_tex;
layout(location = 1) in vec2 a_texCoord;
layout(location = 2) in vec4 a_norm;
uniform float time;
out vec2 o_tex;
out vec4 o_norm;

mat4 lookAt(vec3 eye, vec3 center, vec3 up){
    vec3 f = normalize(center - eye); //direction from the camera to the center
    vec3 s = normalize(cross(f,up)); //the normal between the direction vector to the object from the camera nd the up vector
    vec3 u = cross(s,f); //a perpendicular normal between the previous normal and of the direction vector
    
    mat4 Result = {
        vec4(s,-dot(s,eye)),
        vec4(u,-dot(u, eye)),
        vec4(-f, dot(f,eye)),
        vec4(0,0,0,1)
    };
    return Result;
}

mat4 perspective(float fov, float aspect, float near, float far)
{
    float f = tan(fov/2.0);
    return mat4(
        1/aspect*f, 0.0, 0.0, 0.0,
        0.0, 1/f, 0.0, 0.0,
        0.0, 0.0, 1/(far-near), 0.3,
        0.0, 0.0, -(1.0*far*near)/(far-near), 1
    );


}

uniform vec2 resolution;
uniform vec2 mouse;
uniform vec3 camera;
void main()
{
	
	vec3 Translation = vec3(0.0, 0.0, 0.0);
    vec3 Rotation = vec3(6.28*cos(time), 0.0, 0.0);
    float Scale = 0.3+(camera.z/100);
    mat4x4 TranslationMatrix = 
    {
        vec4(1.0, 0.0, 0.0, Translation.x),
        vec4(0.0, 1.0, 0.0, Translation.y),
        vec4(0.0, 0.0, 1.0, Translation.z),
        vec4(0.0, 0.0, 0.0, 1.0)
    };
    mat4x4 RotationX =
    {  
        vec4(1.0, 0.0, 0.0, 0.0),
        vec4(0.0, cos(Rotation.x), -sin(Rotation.x), 0.0),
        vec4(0.0, sin(Rotation.x), cos(Rotation.x), 0.0),
        vec4(0.0, 0.0, 0.0, 1.0)
    };
    mat4x4 RotationY =
    {
        vec4(cos(Rotation.y), 0.0, sin(Rotation.y), 0.0),
        vec4(0.0, 1.0, 0.0, 0.0),
        vec4(-sin(Rotation.y), 1.0, cos(Rotation.y), 0.0),
        vec4(0.0, 0.0, 0.0, 1.0)
    };
    mat4x4 RotationZ = 
    {
        vec4(cos(Rotation.z), -sin(Rotation.z), 0.0, 0.0),
        vec4(sin(Rotation.z), cos(Rotation.z), 0.0, 0.0),
        vec4(0.0, 0.0, 1.0, 0.0),
        vec4(0.0, 0.0, 0.0, 1.0)
    };
    mat4x4 ScaleMatrix =
    {
        vec4(1.0, 0.0, 0.0, 0.0),
        vec4(0.0, 1.0, 0.0, 0.0),
        vec4(0.0, 0.0, 1.0, 0.0),
        vec4(0.0, 0.0, 0.0, 1/Scale)
    };
    mat4x4 ModelMatrix = TranslationMatrix * RotationX * RotationY * RotationZ * ScaleMatrix;
	vec3 CameraPosition = vec3(camera.x+mouse.x, -mouse.y, 0.0);
    vec3 CameraUp = vec3(0.0, 1.0, 0.0); 
    vec3 CameraLook = vec3(camera.x+mouse.x, -mouse.y, -1);
    mat4 ViewMatrix  = lookAt(CameraPosition, CameraLook, CameraUp);
    
    float AspectRatio = resolution.x/resolution.y;
    float fov = 100*3.14/180;
    float zNear = 0.01;
    float zFar = 100;
    mat4 PerspectiveMatrix = perspective(fov, AspectRatio, zNear, zFar);
	vec4 Object = a_tex;
	
	Object = (Object * ModelMatrix) * ViewMatrix * PerspectiveMatrix;
	gl_Position = Object;
	o_tex = normalize(a_texCoord);
	o_norm = a_norm * ModelMatrix;
	//o_norm = a_norm;
	
	
	
}