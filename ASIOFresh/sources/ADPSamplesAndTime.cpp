#include "ADPSamplesAndTime.h"

ADPSamplesAndTime::ADPSamplesAndTime()
{
    sampleRate = 0L;
    postOutput = false;
    inputLatency = 0;
	outputLatency = 0;
    nanoSeconds = 0;
	samples = 0;
	tcSamples = 0;
	sysRefTime = 0;      // system reference time, when bufferSwitch() was called
	// Signal the end of processing in this example
}
int ADPSamplesAndTime::GetSampleRate()
{
    ASIOError SampleRateError = ASIOGetSampleRate(&sampleRate);
    _sampleRate = sampleRate;
    if(SampleRateError != ASE_OK)
    {
        return 0;
    }
    return 1;
}
int ADPSamplesAndTime::OutputReady()
{
    ASIOError OutputError = ASIOOutputReady();
    if(OutputError != ASE_OK)
    {
        postOutput = false;
        return 0;
    }
    postOutput = true;
    return 1;
}
int ADPSamplesAndTime::GetLatencies()
{
    ASIOError LatencyError = ASIOGetLatencies(&inputLatency, &outputLatency);
    if(LatencyError != ASE_OK)
    {
        return 0;
    }
    return 1;
}
int ADPSamplesAndTime::GetSamplePosition()
{
    ASIOError SamplePositError = ASIOGetSamplePosition(&tInfo.timeInfo.samplePosition, &tInfo.timeInfo.systemTime);
    if(SamplePositError != ASE_OK)
    {
        return 0;
    }
    return 1;
}
int ADPSamplesAndTime::FindSampleRangeError()
{
    if (sampleRate <= 0.0 || sampleRate > 96000.0)
	{
        if(ASIOCanSampleRate(44100.0) == ASE_OK)
        {
            if(ASIOSetSampleRate(44100.0) == ASE_OK)
            {
                if(ASIOGetSampleRate(&sampleRate) == ASE_OK)
                { printf ("ASIOGetSampleRate (sampleRate: %f);\n", sampleRate); }	
                else
                    return 0;
            }
        }else{
            return 0;
        }
    }
    return 1;
}
ADPSamplesAndTime::~ADPSamplesAndTime(){}