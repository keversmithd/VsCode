#include "ADPAsioEngine.h"

ADPAsioEngine::ADPAsioEngine() : running(false)
{
    
}
int ADPAsioEngine::AsioStart()
{
    if(running == true)
    {
        return 0;
    }
    ASIOError StartStatus = ASIOStart();
    if(StartStatus != ASE_OK)
    {
        return 0;
    }
    running = true;
    return 1;
}
int ADPAsioEngine::AsioStop()
{
    if(!running)
    {
        return 0;
    }
    ASIOError StopStatus = ASIOStop();
    running = false;
    return 1;   
}
bool ADPAsioEngine::Running()
{
    return running;
}
ADPAsioEngine::~ADPAsioEngine()
{
    AsioStop();
}
