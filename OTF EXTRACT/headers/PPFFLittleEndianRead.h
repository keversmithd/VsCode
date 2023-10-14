#ifndef PPFFLITTLEENDIANREAD
#define PPFFLITTLEENDIANREAD

#include "PPFFDebug.h"

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  ((byte) & 0x80 ? '1' : '0'), \
  ((byte) & 0x40 ? '1' : '0'), \
  ((byte) & 0x20 ? '1' : '0'), \
  ((byte) & 0x10 ? '1' : '0'), \
  ((byte) & 0x08 ? '1' : '0'), \
  ((byte) & 0x04 ? '1' : '0'), \
  ((byte) & 0x02 ? '1' : '0'), \
  ((byte) & 0x01 ? '1' : '0') 

namespace PPFF::Util
{

    uint32_t checksum(uint32_t * tablehead, uint32_t tablelength);

    FILE* OpenFile(int &Errcode, const char* path);


    
    uint64_t LittleEndianSF(uint64_t BigEndian);
    int64_t LittleEndianISF(int64_t BigEndian);

    uint32_t LittleEndianTT(uint32_t BigEndian);
    fpos_t GetPos(FILE* file);
    uint16_t LittleEndianST(uint16_t BigEndian);

    int32_t LittleEndianITT(uint32_t BigEndian);
    int16_t LittleEndianIST(int16_t BigEndian);

    int16_t ReadBigIST(FILE* file);

    float ReadF(FILE* file);

    uint32_t ReadSF(FILE* file);
    uint32_t ReadISF(FILE* file);

    uint32_t ReadTT(FILE* file);
    uint32_t ReadTF(FILE* file);
    uint16_t ReadST(FILE* file);
    uint8_t ReadE(FILE* file);

    int32_t ReadITT(FILE* file);
    int32_t ReadITF(FILE* file);
    int16_t ReadIST(FILE* file);
    int8_t ReadIE(FILE* file);
}


#endif

