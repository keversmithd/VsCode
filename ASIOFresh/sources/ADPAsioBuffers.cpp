#include "ADPAsioBuffers.h"

ADPAsioBuffers::ADPAsioBuffers()
{
    minSize = 0;
	maxSize = 0;
	preferredSize = 0;
	granularity = 0;
    sizeFetched = false;
    created = false;
}
int ADPAsioBuffers::GetBufferSize()
{
    ASIOError error = ASIOGetBufferSize(&minSize, &maxSize, &preferredSize, &granularity);
    if(error != ASE_OK)
    {
        return 0;
    }
    sizeFetched = true;
    return 1;
}
int ADPAsioBuffers::MarkBuffersInOut(long numInputChannels, long numOutputChannels)
{
    //input buffers
    long i;
    ASIOBufferInfo* info = bufferInfos;

    if (numInputChannels > adp_MaxInputChannels)
		inputBuffers = adp_MaxInputChannels;
	else
		inputBuffers = numInputChannels;
	for(i = 0; i < inputBuffers; i++, info++)
	{
		info->isInput = ASIOTrue;
		info->channelNum = i;
		info->buffers[0] = info->buffers[1] = 0;
	}

    if(numOutputChannels > adp_MaxOutputChannels)
    {
        outputBuffers = adp_MaxOutputChannels;
    }else
    {
        outputBuffers = numOutputChannels;
    }
    for(i = 0; i < outputBuffers; i++, info++)
    {
        info->isInput = ASIOFalse;
        info->channelNum = i;
        info->buffers[0] = info->buffers[1] = 0;
    }
    
    return 1;
}

int ADPAsioBuffers::CreateBuffers(long numInputChannels, long numOutputChannels, long bufferSize, ASIOCallbacks* callbacks, ADPAsioChannels* channels, ADPSamplesAndTime* time)
{
    MarkBuffersInOut(numInputChannels, numOutputChannels);
    long numChannels = numInputChannels + numOutputChannels;
    ASIOError error = ASIOCreateBuffers(bufferInfos, numChannels, bufferSize, callbacks);
    if(error == ASE_OK)
    {
        for(int i = 0; i < numChannels && error == ASE_OK; i++)
        {
            channels->channelInfos[i].channel = bufferInfos[i].channelNum;
			channels->channelInfos[i].isInput = bufferInfos[i].isInput;
			error = ASIOGetChannelInfo(&channels->channelInfos[i]);
        }

        if(error == ASE_OK)
        {
            error = ASIOGetLatencies(&time->inputLatency, &time->outputLatency);
            if(error == ASE_OK)
            {
                printf ("ASIOGetLatencies (input: %d, output: %d);\n", time->inputLatency, time->outputLatency);
            }
        }
    }
    return error == ASE_OK ? 1 : 0;
}
int ADPAsioBuffers::DisposeBuffers()
{
    if(created)
    {
        ASIOError error = ASIODisposeBuffers();
        if(error != ASE_OK)
        {
            return 0;
        }
        created = false;
        return 1;
    }
    return 0;
    

}
ADPAsioBuffers::~ADPAsioBuffers()
{
    DisposeBuffers();
}