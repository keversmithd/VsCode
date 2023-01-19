#ifndef ADPASIODRIVERLIST
#define ADPASIODRIVERLIST
#include <stdio.h>
#include "asio.h"
#include "asiodrivers.h"
#include "asiosys.h"

struct ADPAsioDriverList 
{
private:
    AsioDrivers Drivers;
    char** driverNames;
    unsigned int numDeviceStrings;
    LONG deviceCount;
    unsigned int currentIndex;
public:
    ADPAsioDriverList();
    int AllocateDeviceStrings(unsigned int numdeviceStrings);
    int FreeDeviceStrings();
    int PopulateDriverNames(long maxDevices = 0);
    int LoadDevice(unsigned int deviceIndex);
    int OpenDevice(unsigned int deviceIndex);
    int CloseDevice();
    int PrintDevices();
    ~ADPAsioDriverList();
};

#endif