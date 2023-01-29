#ifndef ADPASIOCHANNELS
#define ADPASIOCHANNELS

#include "ADPAsioDebug.h"



struct ADPAsioChannels
{
    long           inputChannels;
	long           outputChannels;
    bool           Channelsfetched;
    bool           Infofetched;
    ASIOChannelInfo channelInfos[adp_MaxInputChannels + adp_MaxOutputChannels];
    ADPAsioChannels();
    int GetChannels();
    int GetChannelInfo();
    long NumberOfInputChannels();
    long NumberOfOutputChannels();
    ~ADPAsioChannels();
};



#endif