#ifndef ADPASIODRIVEDATA
#define ADPASIODRIVEDATA

#include "ADPAsioDriverInfo.h"



enum ADPDataError{
    ASIO_GETCHANNELS_ERROR = 0xF1,
    ASIO_GETBUFFERSIZE_ERROR = 0xF2,
    ASIO_GETSAMPLERATE_ERROR = 0xF3,
    ASIO_SETSAMPLERATE_ERROR = 0xF4,
    ASIO_SAMPLERATERANGE_ERROR = 0xF5,
    ASIO_SAMPLERESET_ERROR = 0xF6,
    ASIO_SAMPLERESETFAIL_ERROR = 0xF7,
    ASIO_DATA_OK = 0xF0,
    ASIO_DATA_BAD = 0xF1
};

struct ADPAsioDriverData : ADPDriverInfo
{
private:
    bool infoInit;
public:
    ADPAsioDriverData();
    ADPDataError GetChannels();
    ADPDataError GetBufferSize();
    ADPDataError GetSampleRate();
    ADPDataError FindSampleRateRangeError();
    bool GetOutputReadiness();
    int SetSampleRate(ASIOSampleRate SampleRate);
    int InitializeDriverInfo();
    ADPDataError InitializeStaticData();
    ~ADPAsioDriverData();
};



#endif