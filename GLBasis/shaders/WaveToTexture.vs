#version 460 core

layout(location = 0) in vec3 apos;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 normal;

out vec2 o_uv;
out vec3 o_terms;
out vec3 d_terms;


struct WaveInformation
{
    float WavelengthThreshold;
    float AmplitudeThreshold;
    float Speed;
    float dx;
    float dy;
    float z0; //ripple identifier
    float z1; //k identifier
    float z2; //gertsner identifier
};

float randomRange(float min, float max, float seed)
{
    float random = fract(sin(seed) * 43758.5453);  // Generate a random value between 0 and 1
    float range = max - min;
    float scaledRandom = random * range;  // Scale the random value to fit the desired range
    float result = min + scaledRandom;  // Shift the scaled random value to the desired range

    return result;
}

uniform float time;

#define TEXSIZE 256


layout(std140) uniform WaveBuffer {
    WaveInformation waveData[13];
};

float kAmpOverLen = 0.1;

void main()
{
    o_uv = uv;


    gl_Position = vec4(apos, 1.0);
}