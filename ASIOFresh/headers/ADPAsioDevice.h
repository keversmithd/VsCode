#ifndef ADP_ASIO_DEVICE_H
#define ADP_ASIO_DEVICE_H

#include <iostream>
#include <stdio.h>
#include <string.h>
#include "ADPAsio.h"
#include "ASIOCustomCallback.h"
#include <memory.h>

struct AsioDevice{

    ADPAsioDriverList app;


    // Current Open Device
    bool DeviceOpen;
    const char* DeviceName;
    int         DeviceIndex;

    //Device Runtime Information
    long hours,minutes,seconds,milliseconds;

    //Asio Engine
    ADPAsioEngine AsioEngine;


    //
    ADPSamplesAndTime samplesandtime;
    ADPAsioCallbacks callbacks;
    ADPDriverInfo driverInfo;
    double SampleRate = 441000;
    ADPAsioChannels channels;
    ADPAsioBuffers buffers;

    AsioDevice() : DeviceOpen(false)
    {
        SetExternals(&samplesandtime, &buffers, &channels);
    }

    int StartAsioDevice(const char* name)
    {

        if(DeviceOpen == true)
        {
            Exit();
        }

        int DriverLoadStatus = app.LoadDriver(name);
        if (!DriverLoadStatus)
        {

            printf("Error loading device.\n");
            return 0;
        }

        int DriverInfoStatus = GetDriverInfo();
        if(!DriverInfoStatus)
        {
            printf("Error loading device.\n");
            return 0;
        }

        int ChannelStatus = channels.GetChannels();
        if (!ChannelStatus)
        {
            printf("Error loading device.\n");
            return 0;
        }

        printf("ASIOGetChannels (inputs: %d, outputs: %d);\n", channels.inputChannels, channels.outputChannels);

        int BufferStatus = buffers.GetBufferSize();
        if (!BufferStatus)
        {
            printf("Error loading device.\n");
            return 0;
        }
        printf("ASIOGetBufferSize (min: %d, max: %d, preferred: %d, granularity: %d);\n",
               buffers.minSize, buffers.maxSize,
               buffers.preferredSize, buffers.granularity);

        int TimeStatus = samplesandtime.GetSampleRate();
        if (!TimeStatus)
        {
            printf("Error loading device.\n");
            return 0;
        }

        printf("ASIOGetSampleRate (sampleRate: %f);\n", samplesandtime.sampleRate);
        int RangeStatus = samplesandtime.FindSampleRangeError();
        if (!RangeStatus)
        {
            printf("Error loading device.\n");
            return 0;
        }

        

        int OutputReadyFlag = samplesandtime.OutputReady();
        printf("ASIOOutputReady(); - %s\n", samplesandtime.postOutput ? "Supported" : "Not supported");

        callbacks.SetDefaultCallbacks();

        int BufferCreationStatus = buffers.CreateBuffers(channels.inputChannels, channels.outputChannels, buffers.preferredSize, callbacks.ReturnCallback_p(), &channels, &samplesandtime);
        if(!BufferCreationStatus){ printf("Error Creating Buffers"); return 0;}

        DeviceOpen = true;

        return 1;
    }

    int GetDriverInfo()
    {
        int InitStatus = driverInfo.InitializeAsioDriverInfo();
        if (!InitStatus)
        {
            printf("Failed to init driver status.\n");
            return -1;
        }
        printf("asioVersion:   %d\n"
               "driverVersion: %d\n"
               "Name:          %s\n"
               "ErrorMessage:  %s\n",
               driverInfo.driverInfo.asioVersion, driverInfo.driverInfo.driverVersion,
               driverInfo.driverInfo.name, driverInfo.driverInfo.errorMessage);
    }

    void OnUpdate()
    {

        //If deltaTime < 100, do not update time.
        double remainder = samplesandtime.tcSamples;
        long hours = (long)(remainder / (SampleRate * 3600));
        remainder -= hours * SampleRate * 3600;
        long minutes = (long)(remainder / (SampleRate * 60));
        remainder -= minutes * SampleRate * 60;
        long seconds = (long)(remainder / SampleRate);
        remainder -= seconds * SampleRate;
        fprintf (stdout, " / TC: %2.2d:%2.2d:%2.2d:%5.5d", (long)hours, (long)minutes, (long)seconds, (long)remainder);
    }

    int Start()
    {
        if(DeviceOpen == false)
        {
            printf("Device not open\n");
            return 0;
        }

        if (!AsioEngine.AsioStart())
        {
            printf("Could not start asio engine");
            Exit();
            return 0;
        }

        return 1;
    }

    int Stop()
    {
        AsioEngine.AsioStop();

        return 1;
    }

    int Exit()
    {
        AsioEngine.AsioStop();
        buffers.DisposeBuffers();
        app.CloseDevice();
        driverInfo.Exit();
        DeviceOpen = false;
        return 1;
    }

    void SetBufferSwitchBehaviour(int (*bufferSwitchTimeInfo)(ASIOTime *timeInfo, long index, ASIOBool processNow, ADPSamplesAndTime *g_adp_samplesandtime, ADPAsioBuffers *g_adp_buffers, ADPAsioChannels *g_adp_channels))
    {
        if(bufferSwitchTimeInfo == nullptr)
        {
            return;
        }
    }

    ~AsioDevice()
    {
        AsioEngine.AsioStop();
        buffers.DisposeBuffers();
        driverInfo.Exit();
        app.CloseDevice();
    }
};


#endif