#version 460 core

layout(location = 0) in vec3 apos;
layout(location = 1) in vec2 uv;

out vec2 o_uv;

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

layout(std140) uniform WaveBuffer {
    WaveInformation waveData[3];
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

out vec2 o_outerterm;

out vec3 normal;

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
    float k = 0.0;

    //for gertsner calculations

    float Qi = 0.0;

    float hx = 0.0;
    float hy = 0.0;
    float hz = 0.0;


    vec3 gertsnerbinormal = vec3(1,0,0);
    vec3 gertsnertangent = vec3(0,1,0);
    vec3 gertsnernormal = vec3(0,0,1);

    for(int i = 0; i < 3; i++)
    {
        
        WaveInformation wave = waveData[i];

        L = randomRange(0.0, wave.WavelengthThreshold, 1717171);
        w = 2/L;
        A = randomRange(0.0, wave.AmplitudeThreshold, 1717171);
        S = randomRange(0.0, wave.Speed, 1717171);

        //Directional Inward Wave
        if(wave.z0 == 0)
            D = vec2(wave.dx, wave.dy);
        else
            D = normalize(vec2(uv) - vec2(wave.dx, wave.dy));

        phe = S * w;

        if(wave.z2 == 0)
        {
            if(wave.z1 == 0)
            {
                height += A * sin(dot(D, uv) * w  + (time*phe));
                derx += w * D.x * A * cos(dot(D, uv) * w  + (time*phe));
                dery += w * D.y * A * cos(dot(D, uv) * w  + (time*phe));
            }else
            {
                k = wave.z1;
                height += (2*A) * pow((sin(dot(D, uv) * w  + (time*phe))+1)/2, k);
                derx += k * wave.dx * w * A * pow((sin(dot(D, uv) * w  + (time*phe))+1)/2, k-1) * cos(dot(D, uv) * w  + (time*phe));
                dery += w * wave.dy * A * cos(dot(D, uv) * w  + (time*phe));
            }
        }else
        {
            
            Qi = wave.z2/(w*A*3);

            hx +=  Qi*A * wave.dx * cos(dot(w*D,uv) + phe*time);
            hy +=  Qi*A * wave.dy * cos(dot(w*D,uv) + phe*time);
            hz +=  A*sin(dot(w*D,uv) + phe*time);

            float WA = (w*A);
            float S0 = sin(w * dot(D,uv) + (phe*time));
            float C0 = cos(w * dot(D, uv) + (phe*time));

            gertsnerbinormal += vec3(-(Qi * (D.x*D.x) * (WA) * S0),  -(Qi * D.x * D.y * WA * S0), D.x * WA * C0);
            gertsnertangent += vec3(-(Qi * D.x * D.y * WA * S0), -(Qi * (D.y*D.y) * WA * S0), (D.y * WA * C0));
            gertsnernormal += vec3(-(D.x * WA * C0), -(D.y * WA * C0), -(Qi * WA * S0));
        }     
    }

    o_uv.x = derx;
    o_uv.y = dery;

    vec3 tangent = vec3(0,1, dery);
    normal = vec3(-derx, -dery, 1);
    vec3 binormal = vec3(1, 0, derx);
    

    //gertsner calculations
    //normal = vec3(0,1,-hx * hy + hz);
    //tangent = vec3(hx,hy,hz);

    gl_Position = vec4(apos, 1.0);
}