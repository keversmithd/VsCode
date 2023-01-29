#include "ADPAsioDriverInfo.h"

ADPDriverInfo::ADPDriverInfo()
{
    Initialized = false;
}
int ADPDriverInfo::InitializeAsioDriverInfo()
{
    if(Initialized == true)
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
int ADPDriverInfo::Exit()
{
    if(Initialized == false)
    {
        return 0;
    }
    ASIOError inStatus = ASIOExit();
    
    if (inStatus == ASE_OK)
    {
        Initialized = false;
        return 1;
    }
    return 0;
}
ADPDriverInfo::~ADPDriverInfo()
{
    
}