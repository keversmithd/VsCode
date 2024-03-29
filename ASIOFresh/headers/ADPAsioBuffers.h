#ifndef ADPASIOBUFFERS
#define ADPASIOBUFFERS

#include "ADPAsioDebug.h"
#include "ADPAsioChannels.h"
#include "ADPSamplesAndTime.h"

struct ADPAsioBuffers
{
    long           minSize;
	long           maxSize;
	long           preferredSize;
	long           granularity;
    bool           sizeFetched;
    bool           created;
    long           inputBuffers;
	long           outputBuffers;
    ASIOBufferInfo bufferInfos[adp_MaxInputChannels + adp_MaxOutputChannels];
    ADPAsioBuffers();
    int GetBufferSize();
    int MarkBuffersInOut(long numInputChannels, long numOutputChannels);
    int CreateBuffers(long numInputChannels, long numOutputChannels, long bufferSize, ASIOCallbacks* callbacks, ADPAsioChannels* channels, ADPSamplesAndTime* time);
    int DisposeBuffers();
    ~ADPAsioBuffers();
};

#endif