#ifndef ADPASIOCALLBACKS
#define ADPASIOCALLBACKS

#include "ADPSamplesAndTime.h"
#include "ADPAsioBuffers.h"
#include "ADPAsioChannels.h"
#include "math.h"
#include "time.h"
#include <vector>

extern ADPSamplesAndTime* g_adp_samplesandtime;
extern ADPAsioBuffers*    g_adp_buffers;
extern ADPAsioChannels*   g_adp_channels;

void SetExternals(ADPSamplesAndTime* smp, ADPAsioBuffers* buffers, ADPAsioChannels* chans);

unsigned long get_sys_reference_time_i();

void bufferSwitch_i(long index, ASIOBool processNow);
ASIOTime *bufferSwitchTimeInfo_i(ASIOTime *timeInfo, long index, ASIOBool processNow);
void sampleRateChanged_i(ASIOSampleRate sRate);
long asioMessages_i(long selector, long value, void* message, double* opt);


struct ADPAsioCallbacks
{
private:
    ASIOCallbacks asioCallbacks;
public:
    ADPAsioCallbacks();
    ASIOCallbacks* ReturnCallback_p();
    ASIOCallbacks& ReturnCallbacks_r();
    ASIOCallbacks ReturnCallbacks();
    void SetDefaultCallbacks();
    void SetBufferSwitchCallback(void cb_bufferSwitch(long index, ASIOBool processNow));
    void SetSampleRateChangeCallback(void cb_sampleRateChanged(ASIOSampleRate sRate));
    void SetAsioMessageCallback(long cb_asioMessages(long selector, long value, void* message, double* opt));
    void SetBufferSwitchTimeInfo(ASIOTime *cb_bufferSwitchTimeInfo(ASIOTime *timeInfo, long index, ASIOBool processNow));
    ~ADPAsioCallbacks();
};




#endif