#include "ADPAsioCallbacks.h"

//externals set from context.

ADPSamplesAndTime* g_adp_samplesandtime;
ADPAsioBuffers*    g_adp_buffers;
ADPAsioChannels*   g_adp_channels;

void SetExternals(ADPSamplesAndTime* smp, ADPAsioBuffers* buffers, ADPAsioChannels* chans)
{
	g_adp_samplesandtime = smp;
	g_adp_buffers = buffers;
	g_adp_channels = chans;
}

#define TEST_RUN_TIME 20

unsigned long get_sys_reference_time_i()
{	// get the system reference time
#if WINDOWS
	return timeGetTime();
#elif MAC
static const double twoRaisedTo32 = 4294967296.;
	UnsignedWide ys;
	Microseconds(&ys);
	double r = ((double)ys.hi * twoRaisedTo32 + (double)ys.lo);
	return (unsigned long)(r / 1000.);
#endif
}

void bufferSwitch_i(long index, ASIOBool processNow)
{	// the actual processing callback.
	// Beware that this is normally in a seperate thread, hence be sure that you take care
	// about thread synchronization. This is omitted here for simplicity.

	// as this is a "back door" into the bufferSwitchTimeInfo a timeInfo needs to be created
	// though it will only set the timeInfo.samplePosition and timeInfo.systemTime fields and the according flags
	ASIOTime  timeInfo;
	memset (&timeInfo, 0, sizeof (timeInfo));

	// get the time stamp of the buffer, not necessary if no
	// synchronization to other media is required.
	
	if(ASIOGetSamplePosition(&timeInfo.timeInfo.samplePosition, &timeInfo.timeInfo.systemTime) == ASE_OK)
		timeInfo.timeInfo.flags = kSystemTimeValid | kSamplePositionValid;

	bufferSwitchTimeInfo_i (&timeInfo, index, processNow);
}

ASIOTime *bufferSwitchTimeInfo_i(ASIOTime *timeInfo, long index, ASIOBool processNow)
{	
    if(g_adp_samplesandtime == nullptr)
    {
        return 0L;
    }
    // the actual processing callback.
	// Beware that this is normally in a seperate thread, hence be sure that you take care
	// about thread synchronization. This is omitted here for simplicity.
	static long processedSamples = 0;
	// store the timeInfo for later use
	g_adp_samplesandtime->tInfo = *timeInfo;
	// get the time stamp of the buffer, not necessary if no
	// synchronization to other media is required
	if (timeInfo->timeInfo.flags & kSystemTimeValid)
		g_adp_samplesandtime->nanoSeconds = ASIO64toDouble(timeInfo->timeInfo.systemTime);
	else
		g_adp_samplesandtime->nanoSeconds = 0;

	if (timeInfo->timeInfo.flags & kSamplePositionValid)
		g_adp_samplesandtime->samples = ASIO64toDouble(timeInfo->timeInfo.samplePosition);
	else
		g_adp_samplesandtime->samples = 0;

	if (timeInfo->timeCode.flags & kTcValid)
		g_adp_samplesandtime->tcSamples = ASIO64toDouble(timeInfo->timeCode.timeCodeSamples);
	else
		g_adp_samplesandtime->tcSamples = 0;

	// get the system reference time
	g_adp_samplesandtime->sysRefTime = get_sys_reference_time_i();

#if WINDOWS && _DEBUG
	// a few debug messages for the Windows device driver developer
	// tells you the time when driver got its interrupt and the delay until the app receives
	// the event notification.
	static double last_samples = 0;
	char tmp[128];
	sprintf (tmp, "diff: %d / %d ms / %d ms / %d samples                 \n", g_adp_samplesandtime->sysRefTime - (long)(g_adp_samplesandtime->nanoSeconds / 1000000.0), g_adp_samplesandtime->sysRefTime, (long)(g_adp_samplesandtime->nanoSeconds / 1000000.0), (long)(g_adp_samplesandtime->samples - last_samples));
	wchar_t wtmp[128];
	mbstowcs(wtmp, tmp, 128+1);
	OutputDebugString (wtmp);
	last_samples = g_adp_samplesandtime->samples;
#endif

	// buffer size in samples
	long buffSize = g_adp_buffers->preferredSize;

	// perform the processing
	for (int i = 0; i < g_adp_buffers->inputBuffers + g_adp_buffers->outputBuffers; i++)
	{
		if (g_adp_buffers->bufferInfos[i].isInput == false)
		{
			// OK do processing for the outputs only
			switch (g_adp_channels->channelInfos[i].type)
			{
			case ASIOSTInt16LSB:
				memset (g_adp_buffers->bufferInfos[i].buffers[index], 0, buffSize * 2); //filling with silence
				break;
			case ASIOSTInt24LSB:		// used for 20 bits as well
				memset (g_adp_buffers->bufferInfos[i].buffers[index], 0, buffSize * 3);
				break;
			case ASIOSTInt32LSB:
				memset (g_adp_buffers->bufferInfos[i].buffers[index], 50*sin(processedSamples)*sin(processedSamples), buffSize * 4);
				break;
			case ASIOSTFloat32LSB:		// IEEE 754 32 bit float, as found on Intel x86 architecture
				memset (g_adp_buffers->bufferInfos[i].buffers[index], 0, buffSize * 4);
				break;
			case ASIOSTFloat64LSB: 		// IEEE 754 64 bit double float, as found on Intel x86 architecture
				memset (g_adp_buffers->bufferInfos[i].buffers[index], 0, buffSize * 8);
				break;

				// these are used for 32 bit data buffer, with different alignment of the data inside
				// 32 bit PCI bus systems can more easily used with these
			case ASIOSTInt32LSB16:		// 32 bit data with 18 bit alignment
			case ASIOSTInt32LSB18:		// 32 bit data with 18 bit alignment
			case ASIOSTInt32LSB20:		// 32 bit data with 20 bit alignment
			case ASIOSTInt32LSB24:		// 32 bit data with 24 bit alignment
				memset (g_adp_buffers->bufferInfos[i].buffers[index], 0, buffSize * 4);
				break;

			case ASIOSTInt16MSB:
				memset (g_adp_buffers->bufferInfos[i].buffers[index], 0, buffSize * 2);
				break;
			case ASIOSTInt24MSB:		// used for 20 bits as well
				memset (g_adp_buffers->bufferInfos[i].buffers[index], 0, buffSize * 3);
				break;
			case ASIOSTInt32MSB:
				memset (g_adp_buffers->bufferInfos[i].buffers[index], 0, buffSize * 4);
				break;
			case ASIOSTFloat32MSB:		// IEEE 754 32 bit float, as found on Intel x86 architecture
				memset (g_adp_buffers->bufferInfos[i].buffers[index], 0, buffSize * 4);
				break;
			case ASIOSTFloat64MSB: 		// IEEE 754 64 bit double float, as found on Intel x86 architecture
				memset (g_adp_buffers->bufferInfos[i].buffers[index], 0, buffSize * 8);
				break;

				// these are used for 32 bit data buffer, with different alignment of the data inside
				// 32 bit PCI bus systems can more easily used with these
			case ASIOSTInt32MSB16:		// 32 bit data with 18 bit alignment
			case ASIOSTInt32MSB18:		// 32 bit data with 18 bit alignment
			case ASIOSTInt32MSB20:		// 32 bit data with 20 bit alignment
			case ASIOSTInt32MSB24:		// 32 bit data with 24 bit alignment
				memset (g_adp_buffers->bufferInfos[i].buffers[index], 0, buffSize * 4);
				break;
			}
		}
	}

	// finally if the driver supports the ASIOOutputReady() optimization, do it here, all data are in place
	if (g_adp_samplesandtime->postOutput)
		ASIOOutputReady();

	if (processedSamples >= g_adp_samplesandtime->sampleRate * TEST_RUN_TIME)	// roughly measured
		g_adp_samplesandtime->stopped = false;
	else
		processedSamples += buffSize;

	return 0L;
}

void sampleRateChanged_i(ASIOSampleRate sRate)
{
	// do whatever you need to do if the sample rate changed
	// usually this only happens during external sync.
	// Audio processing is not stopped by the driver, actual sample rate
	// might not have even changed, maybe only the sample rate status of an
	// AES/EBU or S/PDIF digital input at the audio device.
	// You might have to update time/sample related conversion routines, etc.
}

//----------------------------------------------------------------------------------
long asioMessages_i(long selector, long value, void* message, double* opt)
{
	// currently the parameters "value", "message" and "opt" are not used.
	long ret = 0;
	switch(selector)
	{
		case kAsioSelectorSupported:
			if(value == kAsioResetRequest
			|| value == kAsioEngineVersion
			|| value == kAsioResyncRequest
			|| value == kAsioLatenciesChanged
			// the following three were added for ASIO 2.0, you don't necessarily have to support them
			|| value == kAsioSupportsTimeInfo
			|| value == kAsioSupportsTimeCode
			|| value == kAsioSupportsInputMonitor)
				ret = 1L;
			break;
		case kAsioResetRequest:
			// defer the task and perform the reset of the driver during the next "safe" situation
			// You cannot reset the driver right now, as this code is called from the driver.
			// Reset the driver is done by completely destruct is. I.e. ASIOStop(), ASIODisposeBuffers(), Destruction
			// Afterwards you initialize the driver again.
			g_adp_samplesandtime->stopped;  // In this sample the processing will just stop
			ret = 1L;
			break;
		case kAsioResyncRequest:
			// This informs the application, that the driver encountered some non fatal data loss.
			// It is used for synchronization purposes of different media.
			// Added mainly to work around the Win16Mutex problems in Windows 95/98 with the
			// Windows Multimedia system, which could loose data because the Mutex was hold too long
			// by another thread.
			// However a driver can issue it in other situations, too.
			ret = 1L;
			break;
		case kAsioLatenciesChanged:
			// This will inform the host application that the drivers were latencies changed.
			// Beware, it this does not mean that the buffer sizes have changed!
			// You might need to update internal delay data.
			ret = 1L;
			break;
		case kAsioEngineVersion:
			// return the supported ASIO version of the host application
			// If a host applications does not implement this selector, ASIO 1.0 is assumed
			// by the driver
			ret = 2L;
			break;
		case kAsioSupportsTimeInfo:
			// informs the driver wether the asioCallbacks.bufferSwitchTimeInfo() callback
			// is supported.
			// For compatibility with ASIO 1.0 drivers the host application should always support
			// the "old" bufferSwitch method, too.
			ret = 1;
			break;
		case kAsioSupportsTimeCode:
			// informs the driver wether application is interested in time code info.
			// If an application does not need to know about time code, the driver has less work
			// to do.
			ret = 0;
			break;
	}
	return ret;
}

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