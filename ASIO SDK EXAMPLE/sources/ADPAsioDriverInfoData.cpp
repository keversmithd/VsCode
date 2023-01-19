#include "ADPAsioDriverInfoData.h"


ADPAsioDriverData::ADPAsioDriverData()
{
    infoInit = false;
}
ADPDataError ADPAsioDriverData::GetChannels()
{
    ASIOError ChannelError = ASIOGetChannels(&inputChannels, &outputChannels);
    if(ChannelError != ASE_OK)
    {
        return ASIO_GETCHANNELS_ERROR;
    }
    return ASIO_DATA_OK;

}
ADPDataError ADPAsioDriverData::GetBufferSize()
{
    ASIOError BufferError = ASIOGetBufferSize(&minSize, &maxSize, &preferredSize, &granularity);
    if(BufferError != ASE_OK)
    {
        return ASIO_GETBUFFERSIZE_ERROR;
    }
    return ASIO_DATA_OK;
}
ADPDataError ADPAsioDriverData::GetSampleRate()
{
    ASIOError SampleRateError = ASIOGetSampleRate(&sampleRate);
    if(SampleRateError != ASE_OK)
    {
        return ASIO_GETSAMPLERATE_ERROR;
    }
    return ASIO_DATA_OK;
}
ADPDataError ADPAsioDriverData::FindSampleRateRangeError()
{
	if (sampleRate <= 0.0 || sampleRate > 96000.0)
	{
        if(ASIOCanSampleRate(44100.0) == ASE_OK)
        {
            if(ASIOSetSampleRate(44100.0) == ASE_OK)
		{
			if(ASIOGetSampleRate(&sampleRate) == ASE_OK)
			{ }	
			else
				return ASIO_SAMPLERESET_ERROR;
		}
		    return ASIO_SAMPLERESETFAIL_ERROR;
        }
		return ASIO_SAMPLERESETFAIL_ERROR;
	}
    return ASIO_DATA_OK;
}
bool ADPAsioDriverData::GetOutputReadiness()
{
    ASIOError outputFlag = ASIOOutputReady();
    if(outputFlag == ASE_OK)
    {
        postOutput = true;
        return true;
    }
        postOutput = false;
        return false;
}
int ADPAsioDriverData::SetSampleRate(ASIOSampleRate SampleRate)
{
    ASIOError setError = ASIOSetSampleRate(SampleRate);
    if(setError == ASE_OK)
    {
        return ASIO_DATA_OK;
    }
    return ASIO_SETSAMPLERATE_ERROR;
}
int ADPAsioDriverData::InitializeDriverInfo()
{
    if (ASIOInit (&driverInfo) == ASE_OK)
    {
        infoInit = true;
        return 1;
    }
    return 0;
}
ADPDataError ADPAsioDriverData::InitializeStaticData()
{
    if(InitializeDriverInfo())
    {   
        ADPDataError ChannelError = GetChannels();
        if(ChannelError != ASIO_DATA_OK) { return ChannelError; }
        ADPDataError BufferSizeError = GetBufferSize();
        if(BufferSizeError != ASIO_DATA_OK) { return BufferSizeError; }
        ADPDataError SampleRateError = GetSampleRate();
        if(SampleRateError != ASIO_DATA_OK) { return SampleRateError; }
        ADPDataError SampleRateRangeError = FindSampleRateRangeError();
        if(SampleRateRangeError != ASIO_DATA_OK) { return SampleRateRangeError; }
        bool OutputFlag = GetOutputReadiness();
        return ASIO_DATA_OK;
    }
    return ASIO_DATA_BAD;
    
}
ADPAsioDriverData::~ADPAsioDriverData(){}



