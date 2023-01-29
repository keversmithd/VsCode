#include "ADPAsioCallbacks.h"




ADPAsioCallbacks::ADPAsioCallbacks()
{
    
}
ASIOCallbacks* ADPAsioCallbacks::ReturnCallback_p()
{
    return &asioCallbacks;
}
ASIOCallbacks& ADPAsioCallbacks::ReturnCallbacks_r()
{
    return asioCallbacks;
}
ASIOCallbacks ADPAsioCallbacks::ReturnCallbacks()
{
    return asioCallbacks;
}
void ADPAsioCallbacks::SetDefaultCallbacks()
{ 
    SetBufferSwitchCallback(bufferSwitch_i);
    SetAsioMessageCallback(asioMessages_i);
    SetBufferSwitchTimeInfo(bufferSwitchTimeInfo_i);
    SetSampleRateChangeCallback(sampleRateChanged_i); 
}
void ADPAsioCallbacks::SetBufferSwitchCallback(void cb_bufferSwitch(long index, ASIOBool processNow))
{
    asioCallbacks.bufferSwitch = cb_bufferSwitch;
}
void ADPAsioCallbacks::SetSampleRateChangeCallback(void cb_sampleRateChanged(ASIOSampleRate sRate))
{
    asioCallbacks.sampleRateDidChange = cb_sampleRateChanged;
}
void ADPAsioCallbacks::SetAsioMessageCallback(long cb_asioMessages(long selector, long value, void* message, double* opt))
{
    asioCallbacks.asioMessage = cb_asioMessages;
}
void ADPAsioCallbacks::SetBufferSwitchTimeInfo(ASIOTime *cb_bufferSwitchTimeInfo(ASIOTime *timeInfo, long index, ASIOBool processNow))
{
    asioCallbacks.bufferSwitchTimeInfo =  cb_bufferSwitchTimeInfo;
}
ADPAsioCallbacks::~ADPAsioCallbacks(){}