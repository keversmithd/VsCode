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
    long i;
	ASIOError result;
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
    return 1;
}

int ADPAsioBuffers::CreateBuffers(long numInputChannels, long numOutputChannels, long bufferSize, ASIOCallbacks* callbacks)
{
    MarkBuffersInOut(numInputChannels, numOutputChannels);
    long numChannels = numInputChannels + numOutputChannels;
    ASIOError error = ASIOCreateBuffers(bufferInfos, numChannels, bufferSize, callbacks);
    if(error != ASE_OK)
    {
        return 0;
    }
    created = true;
    return 1;
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