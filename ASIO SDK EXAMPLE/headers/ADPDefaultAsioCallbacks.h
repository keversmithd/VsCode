#ifndef ADPDEFAULTCALLBACKS
#define ADPDEFAULTCALLBACKS

#include "ADPSamplesAndTime.h"
#include "ADPAsioBuffers.h"
#include "ADPAsioChannels.h"


extern ADPSamplesAndTime* g_adp_samplesandtime;
extern ADPAsioBuffers*    g_adp_buffers;
extern ADPAsioChannels*   g_adp_channels;

unsigned long get_sys_reference_time_i();
void bufferSwitch_i(long index, ASIOBool processNow);
ASIOTime *bufferSwitchTimeInfo_i(ASIOTime *timeInfo, long index, ASIOBool processNow);
void sampleRateChanged_i(ASIOSampleRate sRate);
long asioMessages_i(long selector, long value, void* message, double* opt);



#endif