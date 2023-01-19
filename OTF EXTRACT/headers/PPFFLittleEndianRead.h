#ifndef PPFFLITTLEENDIANREAD
#define PPFFLITTLEENDIANREAD

#include "PPFFDebug.h"

namespace PPFF::Util
{
    FILE* OpenFile(int &Errcode, const char* path);
    uint32_t LittleEndianTT(uint32_t BigEndian);

    uint16_t LittleEndianST(uint16_t BigEndian);


    uint32_t ReadTT(FILE* file);
    uint32_t ReadTF(FILE* file);
    uint16_t ReadST(FILE* file);
    uint8_t ReadE(FILE* file);
}


#endif

