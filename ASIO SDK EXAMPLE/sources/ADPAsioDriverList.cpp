#include "ADPAsioDriverList.h"
ADPAsioDriverList::ADPAsioDriverList()
    { 
        driverNames = 0;
        numDeviceStrings = 0;
        currentIndex = 0; 
    }
int ADPAsioDriverList::AllocateDeviceStrings(unsigned int numdeviceStrings)
    {
        if(numDeviceStrings || driverNames)
        {
            FreeDeviceStrings();
        }
        driverNames = (char**)(malloc(numdeviceStrings * sizeof(char**))); 
        if(driverNames == nullptr){ return 0; } 
        for(int i = 0; i < numdeviceStrings; i++){ driverNames[i] = (char*)malloc(32);  if(driverNames[i] == nullptr) { return 0; }   }
        numDeviceStrings = numdeviceStrings;
        return 1;
    }
int ADPAsioDriverList::FreeDeviceStrings()
    {
        if(numDeviceStrings)
        {
            for(int i = 0; i < numDeviceStrings; i++)
            {
                free(driverNames[i]);
            }
            free(driverNames);
            numDeviceStrings = 0;
            return 1;
        }
        return 0;
    }
int ADPAsioDriverList::PopulateDriverNames(long maxDevices)
    { 
        
        if(maxDevices == 0) { deviceCount = Drivers.asioGetNumDev(); }
        if(maxDevices != 0) { deviceCount = maxDevices; }
        if(!numDeviceStrings || !driverNames)
        {
            int AllocationSuccesss = AllocateDeviceStrings(deviceCount);
            if(!AllocationSuccesss)
            {
                return 0;
            }
        }
        if(deviceCount)
        {
            Drivers.getDriverNames(driverNames, deviceCount);
            return 1; 
        }
        return 0;
    }
int ADPAsioDriverList::LoadDevice(unsigned int deviceIndex)
    {
        if(currentIndex != 0)
        {
            CloseDevice();
        }
        if(deviceIndex > deviceCount || deviceIndex > numDeviceStrings)
        {
            return 0;
        }
        char* deviceName = driverNames[deviceIndex];
        if(deviceName)
        {
            bool deviceLoaded = Drivers.loadDriver(deviceName);
            if(deviceLoaded){  currentIndex = Drivers.getCurrentDriverIndex(); return 1; }
            return 0;
        }
        return 0;
    }
int ADPAsioDriverList::OpenDevice(unsigned int deviceIndex)
    {
        if(deviceIndex > deviceCount || deviceIndex > numDeviceStrings)
        {
            return 0;
        }
        if(currentIndex != 0)
        {
            CloseDevice();
        }
        char* deviceName = driverNames[deviceIndex];
        if(deviceName)
        {
            int openDriveStatus = Drivers.openDriveByIndex(deviceIndex);
            if(openDriveStatus)
            {
                currentIndex = deviceIndex;
                return 1;
            }
            return 0;
        }
        return 0;
        
    }
int ADPAsioDriverList::CloseDevice()
    {
        Drivers.asioCloseDriver(currentIndex);
        if(Drivers.asioDriverClosed(currentIndex))
        {
            currentIndex = 0;
            return 1;
        }
        return 0;
    }
int ADPAsioDriverList::PrintDevices()
    {
        for(int i = 0; i < numDeviceStrings; i++)
        {
            printf("%s\n", driverNames[i]);
        }
        return 1;
    }
ADPAsioDriverList::~ADPAsioDriverList()
    {
        FreeDeviceStrings();
    }