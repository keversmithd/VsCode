#ifndef CUSTO
#define CUSTO

#include "ADPAsioCallbacks.h"



//proccessing function

ASIOTime *CustomBufferSwitch(ASIOTime *timeInfo, long index, ASIOBool processNow)
{

    long buffSize = g_adp_buffers->preferredSize;
    static int proccessedSamples = 0;
    //foreach audio object
    for (int i = 0; i < g_adp_buffers->inputBuffers + g_adp_buffers->outputBuffers; i++)
	{
        int channelIndex = g_adp_buffers->bufferInfos[i].channelNum;
        ASIOChannelInfo channelInfo = g_adp_channels->channelInfos[channelIndex];

		if (g_adp_buffers->bufferInfos[i].isInput == false)
		{
            memset (g_adp_buffers->bufferInfos[i].buffers[index], 70*sin(proccessedSamples/100)*sin(proccessedSamples/100), buffSize);
            //memset (g_adp_buffers->bufferInfos[i].buffers[index]+buffSize*3, 50*cos(proccessedSamples/50)*sin(proccessedSamples/50), buffSize);
		}

        if (g_adp_buffers->bufferInfos[i].isInput == true)
        {
            
        }

	}
    proccessedSamples += buffSize;
    return 0L;
};


#endif
