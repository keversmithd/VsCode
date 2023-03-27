#include <iostream>
#include <stdio.h>
#include <string.h>
#include "ADPAsio.h"
#include "ASIOCustomCallback.h"
#include <memory.h>

void SwitchAsioDevice()
{
    //stop asio device
    //dispose of buffers
}

int main()
{
    ADPAsioDriverList app;
    //int DriverLoadStatus = app.LoadDriver((char*)"Focusrite USB ASIO"); if(!DriverLoadStatus){return 0;}
    int Population = app.PopulateDriverNames(); if(!Population) {return -1;}
    int Printable = app.PrintDevices(); if(!Printable) {return -1;}
    int DeviceOpened = app.OpenDevice(3); if(!DeviceOpened){ return -1; }
    
    ADPDriverInfo driverInfo;
    int InitStatus = driverInfo.InitializeAsioDriverInfo(); if(!InitStatus){return -1;}
    printf ("asioVersion:   %d\n"
					"driverVersion: %d\n"
					"Name:          %s\n"
					"ErrorMessage:  %s\n",
					driverInfo.driverInfo.asioVersion, driverInfo.driverInfo.driverVersion,
					driverInfo.driverInfo.name, driverInfo.driverInfo.errorMessage);
    
    ADPAsioChannels channels;
    int ChannelStatus = channels.GetChannels(); if(!ChannelStatus) { return 0;}
    printf ("ASIOGetChannels (inputs: %d, outputs: %d);\n", channels.inputChannels, channels.outputChannels);
    ADPAsioBuffers buffers;
    int BufferStatus = buffers.GetBufferSize(); if(!BufferStatus){ return 0;}
    printf ("ASIOGetBufferSize (min: %d, max: %d, preferred: %d, granularity: %d);\n",
					 buffers.minSize, buffers.maxSize,
					 buffers.preferredSize, buffers.granularity); 

    ADPSamplesAndTime samplesandtime;
    int TimeStatus = samplesandtime.GetSampleRate(); if(!TimeStatus){return 0;}
    printf ("ASIOGetSampleRate (sampleRate: %f);\n", samplesandtime.sampleRate);
    int RangeStatus = samplesandtime.FindSampleRangeError(); if(!RangeStatus){return 0; }
    int OutputReadyFlag = samplesandtime.OutputReady(); printf ("ASIOOutputReady(); - %s\n", samplesandtime.postOutput ? "Supported" : "Not supported");

    ADPAsioCallbacks callbacks;
    callbacks.SetDefaultCallbacks();
    SetExternals(&samplesandtime, &buffers, &channels);
    callbacks.SetBufferSwitchTimeInfo(CustomBufferSwitch);

    int BufferCreationStatus = buffers.CreateBuffers(channels.inputChannels, channels.outputChannels, buffers.preferredSize, callbacks.ReturnCallback_p(), &channels, &samplesandtime);
    if(!BufferCreationStatus){return 0;}

    ADPAsioEngine AsioEngine;
    double SampleRate = 441000;
    
    if(!AsioEngine.AsioStart()){ buffers.DisposeBuffers(); app.CloseDevice(); return 0;}
    while(!samplesandtime.stopped)
    {
        
        fprintf (stdout, "%d ms / %d ms / %d samples", samplesandtime.sysRefTime, (long)(samplesandtime.nanoSeconds / 1000000.0), (long)samplesandtime.samples);
                            Sleep(100);	// goto sleep for 100 milliseconds
							// create a more readable time code format (the quick and dirty way)

							fprintf (stdout, "%d ms / %d ms / %d samples", samplesandtime.sysRefTime, (long)(samplesandtime.nanoSeconds / 1000000.0), (long)samplesandtime.samples);

							// create a more readable time code format (the quick and dirty way)
							// double remainder = samplesandtime.tcSamples;
							// long hours = (long)(remainder / (SampleRate * 3600));
							// remainder -= hours * SampleRate * 3600;
							// long minutes = (long)(remainder / (SampleRate * 60));
							// remainder -= minutes * SampleRate * 60;
							// long seconds = (long)(remainder / SampleRate);
							// remainder -= seconds * SampleRate;
							// fprintf (stdout, " / TC: %2.2d:%2.2d:%2.2d:%5.5d", (long)hours, (long)minutes, (long)seconds, (long)remainder);
							   fprintf (stdout, "     \r");

							fflush(stdout);
    }

    AsioEngine.AsioStop();
    buffers.DisposeBuffers();
    driverInfo.Exit();
    app.CloseDevice();
    

    
    int disposeStatus = buffers.DisposeBuffers();

    ADPAsioCallbacks cb;
    cb.SetDefaultCallbacks();
    
    //driverInfo.Exit();
    app.CloseDevice();
    return 1;
}