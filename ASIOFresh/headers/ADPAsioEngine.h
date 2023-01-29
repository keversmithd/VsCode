#ifndef ADPASIOENG
#define ADPASIOENG

#include "ADPAsioDebug.h"


struct ADPAsioEngine
{
private:
    bool running;
public:
    ADPAsioEngine();
    int AsioStart();
    int AsioStop();
    bool Running();
    ~ADPAsioEngine();
};

#endif