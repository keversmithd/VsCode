#include "PPFFLittleEndianRead.h"

using namespace PPFF::Util;

FILE* PPFF::Util::OpenFile(int &Errcode, const char* path)
{
    FILE* SourceFile = NULL;
    errno_t Error = fopen_s(&SourceFile, path, "rb");
    if(Error != 0)
    {
        Errcode = 0;
        return nullptr;
    }
    if(SourceFile == NULL)
    {
        Errcode = 0;
        return nullptr;
    }
    return SourceFile;
}

uint32_t PPFF::Util::LittleEndianTT(uint32_t BigEndian)
{
    uint32_t Little = BigEndian;
    uint32_t Buffer = BigEndian;
    Little = (Buffer & 0xff000000) >> 24 | (Buffer & 0x00ff0000) >> 8 | (Buffer & 0x0000ff00) << 8 | (Buffer & 0x000000ff) << 24;

    return Little;
}


uint16_t PPFF::Util::LittleEndianST(uint16_t BigEndian)
{
    uint16_t Little = BigEndian;
    uint16_t Buffer = BigEndian;
    Little = (Buffer & 0xff00) >> 8 | (Buffer & 0x00ff) << 8;
    return Little;
}

uint32_t PPFF::Util::ReadTT(FILE* file)
{
    int errcode = 0;
    uint32_t buffer = 0;
    fread(&buffer, 4, 1, file);
    return LittleEndianTT(buffer);
}

uint16_t PPFF::Util::ReadST(FILE* file)
{
    uint16_t buffer = 0;
    fread(&buffer, 2, 1, file);
    
    return PPFF::Util::LittleEndianST(buffer);
}

uint32_t PPFF::Util::ReadTF(FILE* file)
{
    uint32_t buffer = 0;
    fread(&buffer, 3, 1, file);
    buffer = buffer & 0x00FFFFFF;
    buffer = buffer >> 16 | buffer << 16 | buffer & 0x0000FF00;
    return buffer;
}

uint8_t PPFF::Util::ReadE(FILE* file)
{
    uint8_t buffer = 0;
    fread(&buffer, 1,1, file);
    return buffer;

}