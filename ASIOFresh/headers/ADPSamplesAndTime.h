#ifndef ADPSAMPTIME
#define ADPSAMPTIME

#include "ADPAsioDebug.h"

struct ADPSamplesAndTime
{
    ASIOSampleRate sampleRate;
    bool    postOutput;
    long    inputLatency;
	long    outputLatency;
    double  nanoSeconds;
	double  samples;
	double  tcSamples;
    ASIOTime   tInfo;			// time info state
	unsigned long  sysRefTime;      // system reference time, when bufferSwitch() was called
	// Signal the end of processing in this example
	bool           stopped;
    ADPSamplesAndTime();
    int GetSampleRate();
    int OutputReady();
    int GetLatencies();
    int GetSamplePosition();
    int FindSampleRangeError();
    ~ADPSamplesAndTime();

};

#endif