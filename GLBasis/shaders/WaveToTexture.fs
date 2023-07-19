#version 460 core

in vec2 o_uv;
in vec3 o_terms;
in vec3 d_terms;

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


uniform sampler1D LookUp;

void main()
{
    float height = 0.0;
    float L = 0.0;
    float w = 0.0;
    float A = 0.0;
    float S = 0.0;
    vec2 D = vec2(0.0,0.0);
    float phe = 0.0;
    float deru = 0.0;
    float derv = 0.0;
    float derx = 0.0;
    float dery = 0.0;

    float texelSize = 1.0/TEXSIZE;

    for(int i = 0; i < 13; i++)
    {
        WaveInformation wave = waveData[i];
        L = randomRange(4*texelSize, wave.WavelengthThreshold*texelSize, 1717171);

        w = 0.5/L;
        A = randomRange(0.0, wave.AmplitudeThreshold, 1717171);

        S = randomRange(0.0, wave.Speed, 1717171);
        D = vec2(wave.dx, wave.dy);
        phe = S * w;
        
        height += A * sin(dot(D, o_uv) * w  + (time*phe));
        deru += w * D.x * A * 1/13*cos(dot(D, o_uv) * w  + (time*phe));
        derv += w * D.y * A * 1/13* cos(dot(D, o_uv) * w  + (time*phe));
        derx += 2*3.14 * A/L * D.x * 1/13 * cos(dot(D, o_uv) * w  + (time*phe));
        dery += 2*3.14 * A/L * D.y * 1/13 * cos(dot(D, o_uv) * w  + (time*phe));
    }

    gl_FragColor = vec4(o_terms.x*texture(LookUp, o_terms.z));
    gl_FragColor = vec4(0.4,0.4,0.4,1) + vec4((deru+derv)/13);
    //gl_FragColor = vec4(height);
    //gl_FragColor = vec4(o_terms.x * cos(o_terms.y));
    //gl_FragColor = vec4(cos(o_terms.z));

    //gl_FragColor = vec4(height);
    
}