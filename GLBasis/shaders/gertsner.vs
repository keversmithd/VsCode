#version 460 core
layout (location = 0) in vec4 position;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time;
uniform int numberofwaves;


struct WaveInformation
{
    float WavelengthThreshold;
    float AmplitudeThreshold;
    float Speed;
    float dx;
    float dy;
    float z0;
};

layout(std140) uniform WaveBuffer {
    WaveInformation waveData[5];
};


float randomRange(float min, float max, float seed)
{
    float random = fract(sin(seed) * 43758.5453);  // Generate a random value between 0 and 1
    float range = max - min;
    float scaledRandom = random * range;  // Scale the random value to fit the desired range
    float result = min + scaledRandom;  // Shift the scaled random value to the desired range

    return result;
}

out vec3 normal;
out vec3 tangent;
out vec3 binormal;

void main()
{

    float height = 0.0;
    float L = 0.0;
    float w = 0.0;
    float A = 0.0;
    float S = 0.0;
    vec2 D = vec2(0.0,0.0);
    float phe = 0.0;
    float derx = 0.0;
    float dery = 0.0;

    float hx = 0.0;
    float hy = 0.0;
    float hz = 0.0;

    for(int i = 0; i < numberofwaves; i++)
    {
        
        WaveInformation wave = waveData[i];
        L = randomRange(0.0, wave.WavelengthThreshold, 1717171);
        w = 2/L;
        A = randomRange(0.0, wave.AmplitudeThreshold, 1717171);
        S = randomRange(0.0, wave.Speed, 1717171);
        D = vec2(wave.dx, wave.dy);
        phe = S * w;


        hx +=  wave.z0*A * wave.dx * cos(dot(w*D,position.xz) + phe*time);
        hy +=  wave.z0*A * wave.dy * cos(dot(w*D,position.xz) + phe*time);
        hz +=  A*sin(dot(w*D,position.xz) + phe*time);
    }
    
    
    tangent = vec3(hx,hy,hz);
    normal = vec3(0,1,-hx * hy + hz);

    vec4 apos = vec4(position.x+hx, position.y+hy, position.z+hz, 1.0);


    gl_Position = projection * view * model * apos;
}