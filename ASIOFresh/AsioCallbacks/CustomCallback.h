#ifndef CUSTOM_CALLBACK_H
#define CUSTOM_CALLBACK_H

#include "ADPSamplesAndTime.h"
#include "ADPAsioBuffers.h"
#include "ADPAsioChannels.h"
#include "math.h"
#include "time.h"
#include <vector>

extern ADPSamplesAndTime *g_adp_samplesandtime;
extern ADPAsioBuffers *g_adp_buffers;
extern ADPAsioChannels *g_adp_channels;

#include "POPFix.h"

#include <Vector>

struct BitSpace
{
    int start;
    int end;

    POPExpression function;
    char expression[50];

    BitSpace()
    {

    }

    BitSpace(int _start, int _end, std::string _expression) : start(_start), end(_end)
    {
        strcpy(expression, _expression.c_str());
        function.Parse(_expression);
    }

    int Evaluate(long processedSamples, double sampleRate)
    {
        double returnValue = function.multival({{"processedSamples", processedSamples}, {"sampleRate", sampleRate}});

        return returnValue; 
    }

};

std::vector<BitSpace> BitSpaces = {
    BitSpace(0, 96 * 2, "40*cos(processedSamples)"),
    BitSpace(96 * 2, 96 * 4, "20*sin(processedSamples)"),
};

ASIOTime *BitSnapper(ASIOTime *timeInfo, long index, ASIOBool processNow)
{
    if (g_adp_samplesandtime == nullptr)
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
    g_adp_samplesandtime->sysRefTime = timeGetTime();

    // buffer size in samples
    long buffSize = g_adp_buffers->preferredSize;
    long maxSize = g_adp_buffers->maxSize;

    float sampleRate = g_adp_samplesandtime->_sampleRate;
    float processedBySample = processedSamples / sampleRate;
    float parameter = processedBySample / 3;

    // perform the processing
    for (int i = 0; i < g_adp_buffers->inputBuffers + g_adp_buffers->outputBuffers; i++)
    {
        if (g_adp_buffers->bufferInfos[i].isInput == false)
        {
            // OK do processing for the outputs only
            switch (g_adp_channels->channelInfos[i].type)
            {
            case ASIOSTInt16LSB:
                memset(g_adp_buffers->bufferInfos[i].buffers[index], 0, buffSize * 2); // filling with silence
                break;
            case ASIOSTInt24LSB: // used for 20 bits as well
                memset(g_adp_buffers->bufferInfos[i].buffers[index], 0, buffSize * 3);
                break;
            case ASIOSTInt32LSB:
                if(BitSpaces.size() <= 0)
                {
                    break;
                }
                for(int k  = 0; k < BitSpaces.size();  k++)
                {
                    memset(((char *)g_adp_buffers->bufferInfos[i].buffers[index]) + BitSpaces[k].start, BitSpaces[k].Evaluate(processedSamples, sampleRate), (BitSpaces[k].end-BitSpaces[k].start));
                }
                break;
            case ASIOSTFloat32LSB: // IEEE 754 32 bit float, as found on Intel x86 architecture
                memset(g_adp_buffers->bufferInfos[i].buffers[index], 0, buffSize * 4);
                break;
            case ASIOSTFloat64LSB: // IEEE 754 64 bit double float, as found on Intel x86 architecture
                memset(g_adp_buffers->bufferInfos[i].buffers[index], 0, buffSize * 8);
                break;

                // these are used for 32 bit data buffer, with different alignment of the data inside
                // 32 bit PCI bus systems can more easily used with these
            case ASIOSTInt32LSB16: // 32 bit data with 18 bit alignment
            case ASIOSTInt32LSB18: // 32 bit data with 18 bit alignment
            case ASIOSTInt32LSB20: // 32 bit data with 20 bit alignment
            case ASIOSTInt32LSB24: // 32 bit data with 24 bit alignment
                memset(g_adp_buffers->bufferInfos[i].buffers[index], 0, buffSize * 4);
                break;

            case ASIOSTInt16MSB:
                memset(g_adp_buffers->bufferInfos[i].buffers[index], 0, buffSize * 2);
                break;
            case ASIOSTInt24MSB: // used for 20 bits as well
                memset(g_adp_buffers->bufferInfos[i].buffers[index], 0, buffSize * 3);
                break;
            case ASIOSTInt32MSB:
                memset(g_adp_buffers->bufferInfos[i].buffers[index], 0, buffSize * 4);
                break;
            case ASIOSTFloat32MSB: // IEEE 754 32 bit float, as found on Intel x86 architecture
                memset(g_adp_buffers->bufferInfos[i].buffers[index], 0, buffSize * 4);
                break;
            case ASIOSTFloat64MSB: // IEEE 754 64 bit double float, as found on Intel x86 architecture
                memset(g_adp_buffers->bufferInfos[i].buffers[index], 0, buffSize * 8);
                break;

                // these are used for 32 bit data buffer, with different alignment of the data inside
                // 32 bit PCI bus systems can more easily used with these
            case ASIOSTInt32MSB16: // 32 bit data with 18 bit alignment
            case ASIOSTInt32MSB18: // 32 bit data with 18 bit alignment
            case ASIOSTInt32MSB20: // 32 bit data with 20 bit alignment
            case ASIOSTInt32MSB24: // 32 bit data with 24 bit alignment
                memset(g_adp_buffers->bufferInfos[i].buffers[index], 0, buffSize * 4);
                break;
            }
        }
    }

    // finally if the driver supports the ASIOOutputReady() optimization, do it here, all data are in place
    if (g_adp_samplesandtime->postOutput)
        ASIOOutputReady();

    processedSamples += buffSize;
    // if (processedSamples >= g_adp_samplesandtime->sampleRate * 3){	// roughly measured
    // 	//g_adp_samplesandtime->stopped = true;
    // }
    // else

    return 0L;
}

#endif