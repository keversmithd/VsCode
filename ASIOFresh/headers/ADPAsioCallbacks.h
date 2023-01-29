#ifndef ADPASIOCALLBACKS
#define ADPASIOCALLBACKS

#include "ADPDefaultAsioCallbacks.h"

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