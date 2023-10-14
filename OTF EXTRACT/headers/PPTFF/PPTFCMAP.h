#ifndef CMAP_H
#define CMAP_H

#include "PPFFTables.h"
#include "PPFFLittleEndianRead.h"

using namespace PPFF::Util;

struct CmapIndex
{
    uint16_t version = 0;
    uint16_t numTables = 0;
};
struct CmapEncoding
{
    uint16_t platformID = 0;
    uint16_t encodingID = 0;
    uint32_t subtableOffset = 0;
};


typedef uint16_t uint16;
typedef int16_t int16;
typedef uint8_t uint8;
typedef uint32_t uint32;
typedef uint32_t Offset32;
typedef uint32_t uint24;

struct FormatPoly
{
    void* self;
    void (*FormatConversion)(void* self, void* userptr);
};

#pragma region EncodingRecordConversion
void EncodingRecordFormat0Convert(void* self, void* userptr);

void EncodingRecordFormat2Convert(void* self, void* userptr);

void EncodingRecordFormat4Convert(void* self, void* userptr);

void EncodingRecordFormat6Convert(void* self, void* userptr);

void EncodingRecordFormat8Convert(void* self, void* userptr);

void EncodingRecordFormat10Convert(void* self, void* userptr);

void EncodingRecordFormat12Convert(void* self, void* userptr);

void EncodingRecordFormat13Convert(void* self, void* userptr);

void EncodingRecordFormat14Convert(void* self, void* userptr);


#pragma endregion
#pragma region EncodingRecordFormat
struct EncodingRecordFormat0
{
    uint16_t format;
    uint16_t length;
    uint16_t language;
    uint8_t* glyphIdArray;
};

struct SequentialMapGroup{
        uint32 startCharCode = 0;
        uint32 endCharCode = 0;  
        uint32 startGlyphID = 0;
};

struct SubHeader
{
    uint16 firstCode = 0;
    uint16 entryCount = 0;
    int16 idDelta = 0;
    uint16 idRangeOffset = 0;
};



struct EncodingRecordFormat2
{
    uint16 format = 0;
    uint16 length = 0;
    uint16 language = 0;
    uint16 subHeaderKeys[256];
    SubHeader* subHeaders = 0;
    uint16* glyphIdArray = 0;
};
struct EncodingRecordFormat4
{
    uint16 format = 0;
    uint16 length = 0;
    uint16 language = 0;
    uint16 segCountX2 = 0;
    uint16 searchRange = 0;
    uint16 entrySelector = 0;
    uint16 rangeShift = 0;
    uint16* endCode = 0;
    uint16 reservedPad = 0;
    uint16* startCode = 0;
    int16* idDelta = 0;
    uint16* idRangeOffsets = 0;
    uint16* glyphIdArray = 0;

    void Decode(char charbattery)
    {   

        uint16_t addition = charbattery+startCode[0];

        uint16_t start = startCode[0];
        uint16_t end = endCode[0];

        uint16_t RangeOffset = idRangeOffsets[0];
        uint16_t id_Delta = idDelta[0];

        

    }



};

struct EncodingRecordFormat6
{
    uint16_t format;
    uint16_t length;
    uint16_t language;
    uint16_t firstCode;
    uint16_t entryCount;
    uint16_t* glyphIdArray;


};
struct EncodingRecordFormat8
{
    uint16 format = 0;
    uint16 reserved = 0;
    uint32 length = 0;
    uint32 language = 0;
    uint8* is32 = 0;
    uint32 numGroups = 0;
    SequentialMapGroup* groups = 0;
};
struct EncodingRecordFormat10
{
    uint16 format = 0;
    uint16 reserved = 0;
    uint32 length = 0;
    uint32 language = 0;
    uint32 startCharCode = 0;
    uint32 numChars = 0;
    uint16* glyphIdArray = 0;
};
struct EncodingRecordFormat12
{
    uint16 format = 0;
    uint16 reserved = 0;
    uint32 length = 0;
    uint32 language = 0;
    uint32 numGroups = 0;
    SequentialMapGroup* groups = 0;
};
struct ConstantMapGroup
{
    uint24 varSelector = 0;
    Offset32 defaultUVSOffset = 0;
    Offset32 nonDefaultUVSOffset = 0;
};
struct EncodingRecordFormat13
{
    

    uint16 format = 0;
    uint16 reserved = 0;
    uint32 length = 0;
    uint32 language = 0;
    uint32 numGroups = 0;
    ConstantMapGroup* groups = 0;
};
struct VariationSelector{
    uint24 varSelector = 0;
    Offset32 defaultUVSOffset = 0;
    Offset32 nonDefaultUVSOffset = 0;
};
struct EncodingRecordFormat14
{
    uint16 format = 0;
    uint32 length = 0;
    uint32 numVarSelectorRecords = 0;
    VariationSelector* varSelector = 0;
};
#pragma endregion


#pragma region F_EncodingRecordFormat0
EncodingRecordFormat0 F_EncodingRecordFormat0(FILE* F);
EncodingRecordFormat2 F_EncodingRecordFormat2(FILE* F);
EncodingRecordFormat4 F_EncodingRecordFormat4(FILE* F);
EncodingRecordFormat6 F_EncodingRecordFormat6(FILE* F);
EncodingRecordFormat8 F_EncodingRecordFormat8(FILE* F);
EncodingRecordFormat10 F_EncodingRecordFormat10(FILE* F);
EncodingRecordFormat12 F_EncodingRecordFormat12(FILE* F);
EncodingRecordFormat13 F_EncodingRecordFormat13(FILE* F);
EncodingRecordFormat14 F_EncodingRecordFormat14(FILE* F);
#pragma endregion


#pragma region ENCODINGRECORDFORMAT

void HandleRecordFormat0(EncodingRecordFormat0 Formula0);
void HandleRecordFormat2(EncodingRecordFormat2 Formula2);
void HandleRecordFormat4(EncodingRecordFormat4 Formula4);
void HandleRecordFormat6(EncodingRecordFormat6 Formula6);
void HandleRecordFormat8(EncodingRecordFormat8 Formula8);
void HandleRecordFormat10(EncodingRecordFormat10 Formula10);
void HandleRecordFormat12(EncodingRecordFormat12 Formula12);
void HandleRecordFormat13(EncodingRecordFormat13 Formula13);
void HandleRecordFormat14(EncodingRecordFormat14 Formula14);


#pragma endregion

#endif