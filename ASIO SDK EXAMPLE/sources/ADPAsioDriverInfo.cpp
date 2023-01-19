#include "ADPAsioDriverInfo.h"

ADPDriverInfo::ADPDriverInfo()
{
    Initialized = false;
}
int ADPDriverInfo::InitializeAsioDriverInfo()
{
    if(Initialized = true)
    {
        return 0;
    }
    ASIOError inStatus = ASIOInit(&driverInfo);
    if (inStatus == ASE_OK)
    {
        Initialized = true;
        return 1;
    }
    return 0;
}
ADPDriverInfo::~ADPDriverInfo()
{
    
}