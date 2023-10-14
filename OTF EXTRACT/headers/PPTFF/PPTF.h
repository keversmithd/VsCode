#ifndef PPTF_H
#define PPTF_H

#include "PPFFTables.h"
#include "PPFFLittleEndianRead.h"
#include "PPTFF/PPTFCMAP.h"

void DisplayHex(uint8_t* data, int size);

struct TTFGylfFlag
{
    uint8_t FlagByte;
    int Repeats;
};

struct TTFHead
{
    typedef float Fixed;
    typedef int64_t LONGDATETIME;
    uint16 majorVersion = 0;
    uint16 minorVersion = 0;
    Fixed fontRevision = 0;
    uint32 checksumAdjustment = 0;
    uint32 magicNumber = 0;
    uint16 flags = 0;
    uint16 unitsPerEm = 0;
    LONGDATETIME created = 0;
    LONGDATETIME modified = 0;
    int16 xMin = 0;
    int16 yMin = 0;
    int16 xMax = 0;
    int16 yMax = 0;
    uint16 macStyle = 0;
    uint16 lowestRecPPEM = 0;
    int16 fontDirectionHint = 0;
    int16 indexToLocFormat = 0;
    int16 glyphDataFormat = 0;
};
struct TTFLoca
{
    uint16_t* ShortOffsets = nullptr;
    uint32_t* LongOffsets = nullptr;
    bool Long = false;

    uint32_t Offset(int index);

};
struct TTFMaxp
{
    typedef uint32_t Version16Dot16;
    Version16Dot16 version = 0;
    uint16 numGlyphs = 0;
    uint16 maxPoints = 0;
    uint16 maxContours = 0;
    uint16 maxCompositePoints = 0;
    uint16 maxCompositeContours = 0;
    uint16 maxZones = 0;
    uint16 maxTwilightPoints = 0;
    uint16 maxStorage = 0;
    uint16 maxFunctionDefs = 0;
    uint16 maxInstructionDefs = 0;
    uint16 maxStackElements = 0;
    uint16 maxSizeOfInstructions = 0;
    uint16 maxComponentElements = 0;
    uint16 maxComponentDepth = 0;
};
struct TTFGlyfPoint
{
    int16 x;
    int16 y;
    bool OnCurve;
};
struct TTFGlyf
{
    int16 numberOfContours = 0;
    int16 xMin = 0;
    int16 yMin = 0;
    int16 xMax = 0;
    int16 yMax = 0;

    uint16* endPtsOfContours = 0;
    uint16 instructionLength = 0;
    uint8* instructions = 0;
    TTFGylfFlag* flags = 0;
    TTFGlyfPoint* Coordinates = 0;
    // int16* xCoordinates = 0;
    // int16* yCoordinates = 0;
};

struct TTFExtractor
{
private:
    const char* fontPath;
    PPFF::Tables::PPFFTableRecord CMAP;
    CmapIndex cmap;
    CmapEncoding* cmapencodings;
    TTFHead Head;
    TTFLoca Loca;
    TTFMaxp Maxp;
    PPFF::Tables::PPFFTableDirectory Directroy;
public:
    TTFExtractor(PPFF::Tables::PPFFTableDirectory CFFDirectory, const char* FontPath);
    void Checksum();
    int ExtractMaxP();
    int ExtractHead();
    int ExtractLoca();
    int ExtractGlyf();
    int ExtractCmap();
    
    

    ~TTFExtractor();

};


#endif