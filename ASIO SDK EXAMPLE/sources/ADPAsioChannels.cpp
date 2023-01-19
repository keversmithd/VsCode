#include "ADPAsioChannels.h"

ADPAsioChannels::ADPAsioChannels()
{
    inputChannels = 0;
    outputChannels = 0;
    Channelsfetched = false;
    Infofetched = false;

}
int ADPAsioChannels::GetChannels()
{
    
    ASIOError error = ASIOGetChannels(&inputChannels, &outputChannels);
    if(error != ASE_OK)
    {
        return 0;
    }
    Channelsfetched = true;
    return 1;
}
int ADPAsioChannels::GetChannelInfo()
{
    ASIOError error = ASIOGetChannelInfo(channelInfos);
    if(error != ASE_OK)
    {
        return 0;
    }
    Infofetched = true;
    return 1;
}
long ADPAsioChannels::NumberOfInputChannels()
{
    return inputChannels;
}
long ADPAsioChannels::NumberOfOutputChannels()
{
    return outputChannels;
}
ADPAsioChannels::~ADPAsioChannels(){}