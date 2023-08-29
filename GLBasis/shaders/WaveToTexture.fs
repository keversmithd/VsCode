#version 460 core

in vec2 o_uv;

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
    WaveInformation waveData[3];
};

float hash( vec2 p ) {
	float h = dot(p,vec2(127.1,311.7));	
    return fract(sin(h)*43758.5453123);
}
float noise( in vec2 p ) {
    vec2 i = floor( p );
    vec2 f = fract( p );	
	vec2 u = f*f*(3.0-2.0*f);
    return -1.0+2.0*mix( mix( hash( i + vec2(0.0,0.0) ), 
                     hash( i + vec2(1.0,0.0) ), u.x),
                mix( hash( i + vec2(0.0,1.0) ), 
                     hash( i + vec2(1.0,1.0) ), u.x), u.y);
}
float sea_octave(vec2 uv, float choppy) {
    uv += noise(uv);        
    vec2 wv = 1.0-abs(sin(uv));
    vec2 swv = abs(cos(uv));    
    wv = mix(wv,swv,wv);
    return pow(1.0-pow(wv.x * wv.y,0.65),choppy);
}


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
    float k = 0.0;
    float hx = 0;
    float hy = 0;
    float hz = 0;


    float texelSize = 1.0/TEXSIZE;

    vec3 gertsnerbinormal = vec3(1,0,0);
    vec3 gertsnertangent = vec3(0,1,0);
    vec3 gertsnernormal = vec3(0,0,1);
    
    int numberofwaves = 3;
    
    for(int i = 0; i < numberofwaves; i++)
    {
        WaveInformation wave = waveData[i];
        L = randomRange(4*texelSize, wave.WavelengthThreshold*texelSize, 1717171);
        w = 0.3/L;
        A = randomRange(0.0, wave.AmplitudeThreshold, 1717171);
        S = randomRange(0.0, wave.Speed, 1717171);
        D = vec2(wave.dx, wave.dy);
        phe = S * w;
        
        if(wave.z0 == 0)
            D = vec2(wave.dx, wave.dy);
        else
            D = normalize(vec2(o_uv.xy) - vec2(wave.dx, wave.dy));

        if(wave.z2 == 0)
        {
            if(wave.z1 == 0)
            {
                height += A * sin(dot(D, o_uv) * w  + (time*phe));
                deru += w * D.x * A* (1.0/numberofwaves)*cos(dot(D, o_uv) * w  + (time*phe));
                deru += sea_octave(o_uv-time,dot(D, o_uv));
                derv += w * D.y * A* (1.0/numberofwaves)*cos(dot(D, o_uv) * w  + (time*phe));
                derv += sea_octave(o_uv+time,dot(D, o_uv));
            }else
            {
                k = wave.z1;
                height += (2*A) * pow((sin(dot(D, o_uv) * w  + (time*phe))+1)/2, k);
                deru += k * D.x * w * A * (1.0/numberofwaves)*pow((sin(dot(D, o_uv) * w  + (time*phe))+1)/2, k-1) * cos(dot(D, o_uv) * w  + (time*phe));
                derv += w * D.y * A * (1.0/numberofwaves)*cos(dot(D, o_uv) * w  + (time*phe));
            }
        }else
        {
            float Qi = wave.z2/(w*A*numberofwaves);

            hx +=  Qi*A * wave.dx * (1.0/numberofwaves)*cos(dot(w*D,o_uv) + phe*time);
            hy +=  Qi*A * wave.dy * (1.0/numberofwaves)*cos(dot(w*D,o_uv) + phe*time);
            hz +=  A*(1.0/numberofwaves)*sin(dot(w*D,o_uv) + phe*time);

            float WA = (w*A);
            float S0 = (1.0/numberofwaves)*sin(w * dot(D,o_uv) + (phe*time));
            float C0 = (1.0/numberofwaves)*cos(w * dot(D, o_uv) + (phe*time));

            gertsnerbinormal += vec3(-(Qi * (D.x*D.x) * (WA) * S0),  -(Qi * D.x * D.y * WA * S0), D.x * WA * C0);
            gertsnertangent += vec3(-(Qi * D.x * D.y * WA * S0), -(Qi * (D.y*D.y) * WA * S0), (D.y * WA * C0));
            gertsnernormal += vec3(-(D.x * WA * C0), -(D.y * WA * C0), -(Qi * WA * S0));
        }
        
    }

    // for(int i = 0; i < numberofwaves; i++)
    // {
    //     WaveInformation wave = waveData[i];
    //     L = randomRange(4*texelSize, 32*texelSize, 1717171);
    //     w = 2/L;
    //     A = randomRange(0.3, 0.8, 1717171);
    //     S = randomRange(0.3, 0.2, 1717171);
    //     D = vec2(randomRange(0.3, 0.8, 1717171)*wave.dx, randomRange(0.3, 0.2, 1717171)*wave.dy);
    //     phe = S * w;

    //     if(wave.z0 == 0)
    //         D = vec2(randomRange(0.3, 0.8, 1717171)*wave.dx, randomRange(0.3, 0.2, 1717171)*wave.dy);
    //     else
    //         D = normalize(vec2(o_uv.xy) - vec2(randomRange(0.3, 0.8, 1717171), randomRange(0.3, 0.2, 1717171)));

    //     if(wave.z2 == 0)
    //     {
    //         if(wave.z1 == 0)
    //         {
    //             height += A * sin(dot(D, o_uv) * w  + (time*phe));
    //             deru += w * D.x * A* (1.0/numberofwaves)*cos(dot(D, o_uv) * w  + (time*phe));
    //             derv += w * D.y * A* (1.0/numberofwaves)*cos(dot(D, o_uv) * w  + (time*phe));
    //         }else
    //         {
    //             k = wave.z1;
    //             height += (2*A) * pow((sin(dot(D, o_uv) * w  + (time*phe))+1)/2, k);
    //             deru += k * D.x * w * A * (1.0/numberofwaves)*pow((sin(dot(D, o_uv) * w  + (time*phe))+1)/2, k-1) * cos(dot(D, o_uv) * w  + (time*phe));
    //             derv += w * D.y * A * (1.0/numberofwaves)*cos(dot(D, o_uv) * w  + (time*phe));
    //         }
    //     }else
    //     {
    //         float Qi = wave.z2/(w*A*numberofwaves);

    //         hx +=  Qi*A * wave.dx * (1.0/numberofwaves)*cos(dot(w*D,o_uv) + phe*time);
    //         hy +=  Qi*A * wave.dy * (1.0/numberofwaves)*cos(dot(w*D,o_uv) + phe*time);
    //         hz +=  A*(1.0/numberofwaves)*sin(dot(w*D,o_uv) + phe*time);

    //         float WA = (w*A);
    //         float S0 = (1.0/numberofwaves)*sin(w * dot(D,o_uv) + (phe*time));
    //         float C0 = (1.0/numberofwaves)*cos(w * dot(D, o_uv) + (phe*time));

    //         gertsnerbinormal += vec3(-(Qi * (D.x*D.x) * (WA) * S0),  -(Qi * D.x * D.y * WA * S0), D.x * WA * C0);
    //         gertsnertangent += vec3(-(Qi * D.x * D.y * WA * S0), -(Qi * (D.y*D.y) * WA * S0), (D.y * WA * C0));
    //         gertsnernormal += vec3(-(D.x * WA * C0), -(D.y * WA * C0), -(Qi * WA * S0));
    //     }
        
    // }

    vec3 tangent = vec3(0,1, derv);
    vec3 normal = normalize(vec3(-deru, -derv, 1) + gertsnernormal);
    vec3 binormal = vec3(1, 0, deru);


    gl_FragColor = vec4(0.4,0.4,0.4,1)+vec4(normal,1);

    
}