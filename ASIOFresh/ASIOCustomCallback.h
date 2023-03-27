#ifndef CUSTO
#define CUSTO

#include "ADPAsioCallbacks.h"

struct AudioObject
{
    bool input;
    int channel;
    int type;
    int Function(){ int audioData =  1; return audioData; }
    
};

ASIOTime *CustomBufferSwitch(ASIOTime *timeInfo, long index, ASIOBool processNow)
{
    long buffSize = g_adp_buffers->preferredSize;
    static int proccessedSamples = 0;
    //foreach audio object
    for (int i = 0; i < g_adp_buffers->inputBuffers + g_adp_buffers->outputBuffers; i++)
	{
		if (g_adp_buffers->bufferInfos[i].isInput == false)
		{
            memset (g_adp_buffers->bufferInfos[i].buffers[index], 70*sin(proccessedSamples/100)*sin(proccessedSamples/100), buffSize);
            memset (g_adp_buffers->bufferInfos[i].buffers[index]+buffSize*3, 50*cos(proccessedSamples/50)*sin(proccessedSamples/50), buffSize);
        
		}
	}
    proccessedSamples += buffSize;
    return 0L;
};


#endif
