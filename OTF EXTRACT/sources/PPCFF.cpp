#include "PPCFF.h"

using namespace PPCFF;
using namespace PPFF::Util;

void PPCFF::IndexExtract8(FILE* NameIndexExtract, void* data, uint16_t count) { uint8_t* _data = (uint8_t*)data;  for(int i = 0; i < count+1; i++){ _data[i] =  ReadE(NameIndexExtract);  }} 
void PPCFF::IndexExtract16(FILE* NameIndexExtract, void* data, uint16_t count) 
{ 
    uint16_t* _data = (uint16_t*)data; 
    for(int i = 0; i < count+1; i++)
    { 
        _data[i] = ReadST(NameIndexExtract);  
    }
} 
void PPCFF::IndexExtract24(FILE* NameIndexExtract, void* data, uint16_t count) { uint32_t* _data = (uint32_t*)data; for(int i = 0; i < count+1; i++){ _data[i] = ReadTF(NameIndexExtract);  }} 
void PPCFF::IndexExtract32(FILE* NameIndexExtract, void* data, uint16_t count) { uint32_t* _data = (uint32_t*)data; for(int i = 0; i < count+1; i++){ _data[i] = ReadTT(NameIndexExtract);  }}

void PPCFF::ExtractOffsets8(FILE* NameIndexExtract, uint32_t* data, uint16_t count) { for(int i = 0; i < count+1; i++){ data[i] = ReadE(NameIndexExtract);  } }
void PPCFF::ExtractOffsets16(FILE* NameIndexExtract, uint32_t* data, uint16_t count)
{ 
    for(int i = 0; i < count+1; i++)
    { 
        data[i] = ReadST(NameIndexExtract);  
    }
}
void PPCFF::ExtractOffsets24(FILE* NameIndexExtract, uint32_t* data, uint16_t count) { for(int i = 0; i < count+1; i++){ data[i] = ReadTF(NameIndexExtract);  }}
void PPCFF::ExtractOffsets32(FILE* NameIndexExtract, uint32_t* data, uint16_t count) { for(int i = 0; i < count+1; i++){ data[i] = ReadTT(NameIndexExtract);  }}

int32_t PPCFF::DictDataExtract0(uint8_t* Byte, int& CurrentIndex)
{
    int32_t ReturnValue = Byte[CurrentIndex]-139;
    return ReturnValue;
}
int32_t PPCFF::DictDataExtract1(uint8_t* Byte, int& CurrentIndex)
{
    int32_t ReturnValue = (Byte[CurrentIndex]-247)*256+Byte[CurrentIndex+1]+108;
    CurrentIndex++;
    return ReturnValue;
}
int32_t PPCFF::DictDataExtract2(uint8_t* Byte, int& CurrentIndex)
{
    int32_t ReturnValue = -(Byte[CurrentIndex]-251)*256-Byte[CurrentIndex+1]-108;
    CurrentIndex++;
    return ReturnValue;
}
int32_t PPCFF::DictDataExtract3(uint8_t* Byte, int& CurrentIndex)
{
    CurrentIndex++;
    printf("\n b0 %x b1 %x\n", Byte[CurrentIndex], Byte[CurrentIndex+1]);
    int32_t ReturnValue = (Byte[CurrentIndex] << 8) | Byte[CurrentIndex+1];
    CurrentIndex++;
    return ReturnValue;
}
int32_t PPCFF::DictDataExtract4(uint8_t* Byte, int& CurrentIndex)
{
    CurrentIndex++;
    int32_t ReturnValue = Byte[CurrentIndex]<< 24 | Byte[CurrentIndex+1] << 16 | Byte[CurrentIndex+2] << 8 | Byte[CurrentIndex+3];
    CurrentIndex += 3;
    return ReturnValue;
}
float PPCFF::DictRealExtract(uint8_t* Byte, int& CurrentIndex)
{
    uint8_t UnitC = 0x00;
    unsigned char Nibbler = 0x00;
    char FloatingBuffer[20];
    uint8_t FloatingBufferIndex = 0;

    CurrentIndex++;
    uint8_t MaxSteps = 100;

    int Exponent = 0;
    
    int Condition = 0;
    
    bool PositiveExponent = false;
    bool NegativeExponent = false;
    printf("\n");
    for(int i = CurrentIndex; i < CurrentIndex+MaxSteps; i++)
    {
        UnitC = Byte[i];
        printf("0x%x\n",UnitC);
        printf("0x%x\n", Byte[i]);
        Nibbler = UnitC >> 4;
        printf("0x%x\n", Nibbler);
        Condition = (1 * (Nibbler == 0x0A)) + (2 * (Nibbler == 0x0B)) + (3 * (Nibbler == 0x0C)) + (4 * (Nibbler == 0x0D)) + (5 * (Nibbler == 0x0E)) + (6 * (Nibbler == 0x0F));
        if(Condition == 0) { FloatingBuffer[FloatingBufferIndex] = Nibbler+48; FloatingBufferIndex++;}
        if(Condition == 1) { FloatingBuffer[FloatingBufferIndex] =  '.'; FloatingBufferIndex++; } 
        if(Condition == 2) { PositiveExponent = true; NegativeExponent = false; Exponent = UnitC & 0x0F;}
        if(Condition == 3) { NegativeExponent = true; PositiveExponent = false; Exponent = UnitC & 0x0F;}
        if(Condition == 5){ FloatingBuffer[FloatingBufferIndex] = '-'; FloatingBufferIndex++;}
        if(Condition == 6){ UnitC = 0x0F; i = i+MaxSteps; }
        
        Nibbler = UnitC & 0x0F;
        printf("0x%x\n", Nibbler);
        Condition = (1 * (Nibbler == 0x0A)) + (2 * (Nibbler == 0x0B)) + (3 * (Nibbler == 0x0C)) + (4 * (Nibbler == 0x0D)) + (5 * (Nibbler == 0x0E)) + (6 * (Nibbler == 0x0F));
        if(Condition == 0) { FloatingBuffer[FloatingBufferIndex] = Nibbler+48; FloatingBufferIndex++;}
        if(Condition == 1) { FloatingBuffer[FloatingBufferIndex] =  '.'; FloatingBufferIndex++; } 
        if(Condition == 5){ FloatingBuffer[FloatingBufferIndex] = '-'; FloatingBufferIndex++;}
        if(Condition == 6){ i = i+MaxSteps; }

        CurrentIndex++;
    }
    FloatingBuffer[FloatingBufferIndex] = '\0';
    printf("%s", FloatingBuffer);
    float value = atof(FloatingBuffer);
    Exponent = (PositiveExponent) ? Exponent : -Exponent;
    value *= pow(10, Exponent);
    CurrentIndex--;
    return value;

}
void PPCFF::NameInsert0(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries)
{
    DictData.version = intStack[0];
    intIndex = 0;
    floatIndex = 0;
}
void PPCFF::NameInsert1(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries)
{
    DictData.notice = intStack[0];
    intIndex = 0;
    floatIndex = 0;
}
void PPCFF::NameInsert2(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries)
{
    DictData.copyright = intStack[0];
    intIndex = 0;
    floatIndex = 0;
    index++;
}
void PPCFF::NameInsert3(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries)
{
    DictData.FullName = intStack[0];
    intIndex = 0;
    floatIndex = 0;
}
void PPCFF::NameInsert4(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries)
{
    DictData.FamilyName = intStack[0];
    intIndex = 0;
    floatIndex = 0;
}
void PPCFF::NameInsert5(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries)
{
    DictData.Weight = intStack[0];
    intIndex = 0;
    floatIndex = 0;
}
void PPCFF::NameInsert6(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries)
{
    DictData.isFixedPitch = intStack[0];
    intIndex = 0;
    floatIndex = 0;
    index++;
}
void PPCFF::NameInsert7(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries)
{
    if(floatIndex > 0)
    {
        DictData.ItalicAngle = floatStack[0];
    }else
    {
        DictData.ItalicAngle = intStack[0];
    }
    intIndex = 0;
    floatIndex = 0;
    index++;
}
void PPCFF::NameInsert8(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries)
{
    if(floatIndex > 0)
    {
        DictData.UnderlinePosition = floatStack[0];
    }else
    {
        DictData.UnderlinePosition = intStack[0];
    }
    intIndex = 0;
    floatIndex = 0;
    index++;
}
void PPCFF::NameInsert9(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries)
{
    if(floatIndex > 0)
    {
        DictData.UnderlineThickness = floatStack[0];
    }else
    {
        DictData.UnderlineThickness = intStack[0];
    }
    intIndex = 0;
    floatIndex = 0;
    index++;
}
void PPCFF::NameInsert10(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries)
{
    if(floatIndex > 0)
    {
        DictData.PaintType = floatStack[0];
    }else
    {
        DictData.PaintType = intStack[0];
    }
    intIndex = 0;
    floatIndex = 0;
    index++;
}
void PPCFF::NameInsert11(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries)
{
    if(floatIndex > 0)
    {
        DictData.CharstringType = floatStack[0];
    }else
    {
        DictData.CharstringType = intStack[0];
    }
    intIndex = 0;
    floatIndex = 0;
    index++;
}
void PPCFF::NameInsert12(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries)
{
    for(int i = 0; i < DataEntries; i++)
    {
        bool CurrentIndex = (DataIndex >> i) & (1);
        if(CurrentIndex == 0){ DictData.FontMatrix[i] = intStack[intIndex]; intIndex++; }
        if(CurrentIndex == 1){ DictData.FontMatrix[i] = floatStack[floatIndex]; floatIndex++; }
    }    
    intIndex = 0;
    floatIndex = 0;
    DataIndex = 0;
    DataEntries = 0;

    index++;
}
void PPCFF::NameInsert13(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries)
{
    if(floatIndex > 0)
    {
        DictData.UniqueID = floatStack[0];
    }else
    {
        DictData.UniqueID = intStack[0];
    }
    intIndex = 0;
    floatIndex = 0;
}
void PPCFF::NameInsert14(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries)
{
    intIndex = 0;
    floatIndex = 0;
    for(int i = 0; i < DataEntries; i++)
    {
        bool CurrentIndex = (DataIndex >> i) & (1);
        if(CurrentIndex == 0){ DictData.FontBBox[i] = intStack[intIndex]; intIndex++; }
        if(CurrentIndex == 1){ DictData.FontBBox[i] = floatStack[floatIndex]; floatIndex++; }
    }    
    intIndex = 0;
    floatIndex = 0;
    DataIndex = 0;
    DataEntries = 0;
}
void PPCFF::NameInsert15(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries)
{
    if(floatIndex > 0)
    {
        DictData.StrokeWidth = floatStack[0];
    }else
    {
        DictData.StrokeWidth = intStack[0];
    }
    intIndex = 0;
    floatIndex = 0;
    index++;
}
void PPCFF::NameInsert16(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries)
{
    for(int i = 0; i < DataEntries; i++)
    {
        bool CurrentIndex = (DataIndex >> i) & (1);
        if(CurrentIndex == 0){ DictData.XUID[i] = intStack[intIndex]; intIndex++; }
        if(CurrentIndex == 1){ DictData.XUID[i] = floatStack[floatIndex]; floatIndex++; }
    }    
    intIndex = 0;
    floatIndex = 0;
    DataIndex = 0;
    DataEntries = 0;

}
void PPCFF::NameInsert17(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries)
{
    if(floatIndex > 0)
    {
        DictData.charset = floatStack[0];
    }else
    {
        DictData.charset = intStack[0];
    }
    intIndex = 0;
    floatIndex = 0;
}
void PPCFF::NameInsert18(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries)
{
    if(floatIndex > 0)
    {
        DictData.Encoding = floatStack[0];
    }else
    {
        DictData.Encoding = intStack[0];
    }
    intIndex = 0;
    floatIndex = 0;
}
void PPCFF::NameInsert19(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries)
{
    if(floatIndex > 0)
    {
        DictData.CharStrings = floatStack[0];
    }else
    {
        DictData.CharStrings = intStack[0];
    }
    intIndex = 0;
    floatIndex = 0;
}
void PPCFF::NameInsert20(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries)
{
    DictData.Private[0] = intStack[0];
    DictData.Private[1] = intStack[1];
    intIndex = 0;
    floatIndex = 0;
}
void PPCFF::NameInsert21(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries)
{
    if(floatIndex > 0)
    {
        DictData.SyntheticBase = floatStack[0];
    }else
    {
        DictData.SyntheticBase = intStack[0];
    }
    intIndex = 0;
    floatIndex = 0;
    index++;
}
void PPCFF::NameInsert22(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries)
{
    if(floatIndex > 0)
    {
        DictData.PostScript = floatStack[0];
    }else
    {
        DictData.PostScript = intStack[0];
    }
    intIndex = 0;
    floatIndex = 0;
    index++;
}
void PPCFF::NameInsert23(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries)
{
    if(floatIndex > 0)
    {
        DictData.BaseFontName = floatStack[0];
    }else
    {
        DictData.BaseFontName = intStack[0];
    }
    intIndex = 0;
    floatIndex = 0;
    index++;
}
void PPCFF::NameInsert24(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries)
{
    for(int i = 0; i < DataEntries; i++)
    {
        bool CurrentIndex = (DataIndex >> i) & (1);
        if(CurrentIndex == 0){ DictData.BaseFontBlend[i] = intStack[intIndex]; intIndex++; }
        if(CurrentIndex == 1){ DictData.BaseFontBlend[i] = floatStack[floatIndex]; floatIndex++; }
    }    
    intIndex = 0;
    floatIndex = 0;
    DataIndex = 0;
    DataEntries = 0;

    index++;
}
void PPCFF::NameInsert25(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries)
{
    DictData.ros.SID1 = intStack[0];
    DictData.ros.SID2 = intStack[1];
    if(floatIndex > 0)
    {
        DictData.ros.number = floatStack[0];
    }else
    {
        DictData.ros.number = intStack[2];
    }
    intIndex = 0;
    floatIndex = 0;
    index++;
}
void PPCFF::NameInsert26(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries)
{
    if(floatIndex > 0)
    {
        DictData.CIDFontVersion = floatStack[0];
    }else
    {
        DictData.CIDFontVersion = intStack[0];
    }
    intIndex = 0;
    floatIndex = 0;
    index++;
}
void PPCFF::NameInsert27(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries)
{
    if(floatIndex > 0)
    {
        DictData.CIDFontRevision = floatStack[0];
    }else
    {
        DictData.CIDFontRevision = intStack[0];
    }
    intIndex = 0;
    floatIndex = 0;
    index++;
}
void PPCFF::NameInsert28(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries)
{
    if(floatIndex > 0)
    {
        DictData.CIDFontType = floatStack[0];
    }else
    {
        DictData.CIDFontType = intStack[0];
    }
    intIndex = 0;
    floatIndex = 0;
    index++;
}
void PPCFF::NameInsert29(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries)
{
    if(floatIndex > 0)
    {
        DictData.CIDCount = floatStack[0];
    }else
    {
        DictData.CIDCount = intStack[0];
    }
    intIndex = 0;
    floatIndex = 0;
    index++;
}
void PPCFF::NameInsert30(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries)
{
    if(floatIndex > 0)
    {
        DictData.UIDBase = floatStack[0];
    }else
    {
        DictData.UIDBase = intStack[0];
    }
    intIndex = 0;
    floatIndex = 0;
    index++;
}
void PPCFF::NameInsert31(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries)
{
    if(floatIndex > 0)
    {
        DictData.FDArray = floatStack[0];
    }else
    {
        DictData.FDArray = intStack[0];
    }
    intIndex = 0;
    floatIndex = 0;
    index++;
}
void PPCFF::NameInsert32(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries)
{
    if(floatIndex > 0)
    {
        DictData.FDSelect = floatStack[0];
    }else
    {
        DictData.FDSelect = intStack[0];
    }
    intIndex = 0;
    floatIndex = 0;
    index++;
}
void PPCFF::NameInsert33(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries)
{
    if(floatIndex > 0)
    {
        DictData.FontName = floatStack[0];
    }else
    {
        DictData.FontName = intStack[0];
    }
    intIndex = 0;
    floatIndex = 0;
    index++;
}

void DisplayHex(uint8_t* data, int size)
{
    for(int i = 0; i < size; i++)
    {
        printf("%X ", data[i]);
        if((i+1) % 15 == 0){printf("\n");}
    }
}

PPCFFExtractor::PPCFFExtractor(PPFF::Tables::PPFFTableDirectory _CFFDirectory, const char* _FontPath)
{
    CFFDirectory = _CFFDirectory;
    FontPath = _FontPath;
}
int PPCFFExtractor::ExtractHeader()
{

    if(CFFDirectory.tableRecords.find("CFF ") == CFFDirectory.tableRecords.end())
    {
        return 0;
    }
    CFFTable = CFFDirectory.tableRecords["CFF "];
    
    FILE* HeaderExtract = NULL;
    errno_t fErr = fopen_s(&HeaderExtract, FontPath, "rb");
    if(HeaderExtract == NULL || fErr != 0)
    {
        return 0;
    }
    int seekSee = fseek(HeaderExtract, CFFTable.offset, SEEK_SET); if(seekSee != 0){ fclose(HeaderExtract); return 0; }

    CFFHeader.major = ReadE(HeaderExtract);
    CFFHeader.minor = ReadE(HeaderExtract);
    CFFHeader.hdrSize = ReadE(HeaderExtract);
    CFFHeader.OffSize = ReadE(HeaderExtract);
    CFFHeader.EndOfTable = CFFTable.offset + CFFHeader.OffSize + (CFFHeader.OffSize == 3);
    int closeStatus = fclose(HeaderExtract);
    return closeStatus;

}
int PPCFFExtractor::ExtractNameIndex(bool ExtractObjects)
{
    FILE* NameIndexExtract = NULL;
    errno_t fErr = fopen_s(&NameIndexExtract, FontPath, "rb");
    if(NameIndexExtract == NULL || fErr != 0)
    {
        return 0;
    }
    int seekSee = fseek(NameIndexExtract, CFFHeader.EndOfTable, SEEK_SET); if(seekSee != 0){ fclose(NameIndexExtract); return 0; }

    NameIndex.count = ReadST(NameIndexExtract);
    NameIndex.offSize = ReadE(NameIndexExtract);
    NameIndex.Offsets = (uint32_t*)malloc((NameIndex.offSize * NameIndex.count)+1);
    NameIndex.Objects = (PPCFFObjectEntry*)malloc(sizeof(PPCFFObjectEntry)*NameIndex.count);
    if(NameIndex.Offset == nullptr)
    {
        return 0;
    }

    std::function<void (void*, uint16_t)> lambda_func[] = {
    [&NameIndexExtract](void* data, uint16_t count) { uint8_t* _data = (uint8_t*)data;  for(int i = 0; i < count+1; i++){ _data[i]  = ReadE(NameIndexExtract);  } },
    [&NameIndexExtract](void* data, uint16_t count) { uint16_t* _data = (uint16_t*)data; for(int i = 0; i < count+1; i++){ _data[i] = ReadST(NameIndexExtract);  } },
    [&NameIndexExtract](void* data, uint16_t count) { uint32_t* _data = (uint32_t*)data; for(int i = 0; i < count+1; i++){ _data[i] = ReadTF(NameIndexExtract);  } },
    [&NameIndexExtract](void* data, uint16_t count) { uint32_t* _data = (uint32_t*)data; for(int i = 0; i < count+1; i++){ _data[i] = ReadTT(NameIndexExtract);  } }
    };
    
    typedef void (*ExtractionMethod)(FILE*, void*, uint16_t);
    ExtractionMethod ExtractionFunctions[4] = 
    {
        IndexExtract8,  IndexExtract16,  IndexExtract24,  IndexExtract32
    };

    typedef void (*ValueExtraction)(FILE*, uint32_t*, uint16_t);
    ValueExtraction ValueFunctions[4] =
    {
        ExtractOffsets8, ExtractOffsets16, ExtractOffsets24, ExtractOffsets32
    };

    int TypeIndex = NameIndex.offSize-1;
    ValueFunctions[TypeIndex](NameIndexExtract, NameIndex.Offsets, NameIndex.count);
    NameIndex.ObjectsBegin = (CFFHeader.EndOfTable + 3) + (NameIndex.offSize * NameIndex.count+1);

    fseek(NameIndexExtract, NameIndex.ObjectsBegin, SEEK_SET);
    for(int i = 0; i < NameIndex.count; i++)
    {
        NameIndex.Objects[i].data = (uint8_t*)malloc(NameIndex.Offsets[i+1]-NameIndex.Offsets[i]);
        fread(NameIndex.Objects[i].data, sizeof(uint8_t), NameIndex.Offsets[i+1]-NameIndex.Offsets[i], NameIndexExtract);
    }
    std::cout << NameIndex.Objects[0].data << std::endl;
    NameIndex.EndOfTable = NameIndex.ObjectsBegin + (NameIndex.Offsets[NameIndex.count] - NameIndex.Offsets[0]);
    return 1;    
}
int PPCFFExtractor::FillArbitraryIndex(FILE* File, PPCFFIndex& Index, uint32_t PrevOffset)
{
    Index.count = ReadST(File);
    Index.offSize = ReadE(File);
    int TypeIndex = Index.offSize-1;
    Index.Offsets = (uint32_t*)malloc(sizeof(uint32_t) * Index.count+1);
    Index.Objects = (PPCFFObjectEntry*)malloc(sizeof(PPCFFObjectEntry)*Index.count);
    if(Index.Offsets == nullptr || Index.Objects == nullptr)
    {
        return 0;
    }
    
    typedef void (*ValueExtraction)(FILE*, uint32_t*, uint16_t);
    ValueExtraction ValueFunctions[4] =
    {
        ExtractOffsets8, ExtractOffsets16, ExtractOffsets24, ExtractOffsets32
    };
    ValueFunctions[TypeIndex](File, Index.Offsets, Index.count);
    Index.ObjectsBegin = (PrevOffset + 3) + (Index.offSize * Index.count+1);

    fseek(File, Index.ObjectsBegin, SEEK_SET);
    
    for(int i = 0; i < Index.count; i++)
    {
        Index.Objects[i].data = (uint8_t*)malloc(Index.Offsets[i+1]-Index.Offsets[i]);
        fread(Index.Objects[i].data, sizeof(uint8_t), Index.Offsets[i+1]-Index.Offsets[i], File);
        Index.Objects[i].size = Index.Offsets[i+1]-Index.Offsets[i];
        DisplayHex(Index.Objects[i].data, Index.Offsets[i+1]-Index.Offsets[i]);
        printf("%s\n",Index.Objects[i].data);
    }
    Index.EndOfTable = Index.ObjectsBegin + (Index.Offsets[Index.count] - Index.Offsets[0]);
    return 1;
}
int PPCFFExtractor::ExtractTopDictIndex()
{
    FILE* TopDictExtract = NULL;
    
    errno_t fErr = fopen_s(&TopDictExtract, FontPath, "rb");
    if(TopDictExtract == NULL || fErr != 0)
    {
        return 0;
    }
    int seekSee = fseek(TopDictExtract, NameIndex.EndOfTable, SEEK_SET); if(seekSee != 0){ fclose(TopDictExtract); return 0; }
    FillArbitraryIndex(TopDictExtract, TopDictIndex, NameIndex.EndOfTable);

    fclose(TopDictExtract);
}
int PPCFFExtractor::ExtractStringIndex()
{
    FILE* StringDictExtract = NULL;
    
    errno_t fErr = fopen_s(&StringDictExtract, FontPath, "rb");
    if(StringDictExtract == NULL || fErr != 0)
    {
        return 0;
    }
    //TopDictIndex.EndOfTable = 337430;
    int seekSee = fseek(StringDictExtract, TopDictIndex.EndOfTable, SEEK_SET); if(seekSee != 0){ fclose(StringDictExtract); return 0; }
    StringIndex.count = ReadST(StringDictExtract);
    StringIndex.offSize = ReadE(StringDictExtract);
    int TypeIndex = StringIndex.offSize-1;
    //main problem here is the number of bytes required of each type is not properly being converted into bytes of u32 type, and so the offsets array is in shambles.
    
    //StringIndex.Offsets = (uint32_t*)malloc((StringIndex.offSize * (StringIndex.count+StringIndex.offSize)));
    StringIndex.Offsets = (uint32_t*)malloc(sizeof(uint32_t) * StringIndex.count + 1);
    StringIndex.Objects = (PPCFFObjectEntry*)malloc(sizeof(PPCFFObjectEntry)*StringIndex.count);
    if(StringIndex.Offsets == nullptr || StringIndex.Objects == nullptr)
    {
        return 0;
    }
    
    typedef void (*ValueExtraction)(FILE*, uint32_t*, uint16_t);
    ValueExtraction ValueFunctions[4] =
    {
        ExtractOffsets8, ExtractOffsets16, ExtractOffsets24, ExtractOffsets32
    };
    ValueFunctions[TypeIndex](StringDictExtract, StringIndex.Offsets, StringIndex.count);
    StringIndex.ObjectsBegin = (TopDictIndex.EndOfTable + 3) + (StringIndex.offSize * StringIndex.count+1);

    fseek(StringDictExtract, StringIndex.ObjectsBegin+1, SEEK_SET);
    
    for(int i = 0; i < StringIndex.count; i++)
    {
        StringIndex.Objects[i].data = (uint8_t*)malloc(StringIndex.Offsets[i+1]-StringIndex.Offsets[i]);
        fread(StringIndex.Objects[i].data, sizeof(uint8_t), StringIndex.Offsets[i+1]-StringIndex.Offsets[i], StringDictExtract);
        StringIndex.Objects[i].size = StringIndex.Offsets[i+1]-StringIndex.Offsets[i];

        //DisplayHex(StringIndex.Objects[i].data, StringIndex.Offsets[i+1]-StringIndex.Offsets[i]);
        //printf("%s\n",StringIndex.Objects[i].data);
     
    }
    StringIndex.EndOfTable = StringIndex.ObjectsBegin + (StringIndex.Offsets[StringIndex.count] - StringIndex.Offsets[0]);

    fclose(StringDictExtract);
    return 1;
}
int PPCFFExtractor::DecodeDictData(uint8_t* Data, int size)
{
    typedef int32_t(*Operand32)(uint8_t* Byte, int& CurrentIndex);
    Operand32 IntegerExtraction[5] = { DictDataExtract0, DictDataExtract1, DictDataExtract2, DictDataExtract3, DictDataExtract4};
    typedef void(*Operator32)(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
    Operator32 OperatorExtraction[33] = {NameInsert0, NameInsert1, NameInsert2, NameInsert3, NameInsert4, NameInsert5, NameInsert6, NameInsert7, NameInsert8, NameInsert9, NameInsert10, NameInsert11, NameInsert12, NameInsert13, NameInsert14, NameInsert15, NameInsert16, NameInsert17, NameInsert18, NameInsert19, NameInsert20, NameInsert21, NameInsert22, NameInsert23, NameInsert24, NameInsert25, NameInsert26, NameInsert27, NameInsert28, NameInsert29, NameInsert30, NameInsert31, NameInsert32};
    
    float FloatBuffer[5];
    uint8_t FloatIndex = 0;
    int32_t IntegerBuffer[5];
    uint8_t IntegerIndex = 0;
    int OperatorIndex = 0;
    int OperandIndex = 0;

    uint64_t IndexMap = 0b0000000;
    uint8_t IndexLocation = 0; 

    for(int i = 0; i < size; i++)
    {
        //Gather Information about if the current byte is an operator, if so deposit load.
        if(Data[i] == 0x0C && Data[i+1] == 0x03)
        {
            printf("here");
        }
        OperatorIndex = (1 * (Data[i] == 0x00)) +  (2 * (Data[i] == 0x01)) +  (3 * (Data[i] == 0x0C && Data[i+1] == 0x00)) + (4 * (Data[i] == 0x02)) +  (5 * (Data[i] == 0x03)) +  (6 * (Data[i] == 0x04)) +  (7 * (Data[i] == 0x0C && Data[i+1] == 0x01)) +  (8 * (Data[i] == 0x0C && Data[i+1] == 0x02)) +  (9 * (Data[i] == 0x0C && Data[i+1] == 0x03)) +  (10 * (Data[i] == 0x0C && Data[i+1] == 0x04)) +  (11 * (Data[i] == 0x0C && Data[i+1] == 0x05)) +  (12 * (Data[i] == 0x0C && Data[i+1] == 0x06)) +  (13 * (Data[i] == 0x0C && Data[i+1] == 0x07)) +  (14 * (Data[i] == 0x0D)) +  (15 * (Data[i] == 0x05)) +  (16 * (Data[i] == 0x0C && Data[i+1] == 0x08)) +  (17 * (Data[i] == 0x0E)) +  (18 * (Data[i] == 0x0F)) +  (19 * (Data[i] == 0x10)) +  (20 * (Data[i] == 0x11)) +  (21 * (Data[i] == 0x12)) +  (22 * (Data[i] == 0x0C && Data[i+1] == 0x14)) +  (23 * (Data[i] == 0x0C && Data[i+1] == 0x15)) +  (24 * (Data[i] == 0x0C && Data[i+1] == 0x16)) +  (25 * (Data[i] == 0x0C && Data[i+1] == 0x17)) +  (26 * (Data[i] == 0x0C && Data[i+1] == 0x1E)) +  (27 * (Data[i] == 0x0C && Data[i+1] == 0x1F)) +  (28 * (Data[i] == 0x0C && Data[i+1] == 0x20)) +  (29 * (Data[i] == 0x0C && Data[i+1] == 0x21)) +  (30 * (Data[i] == 0x0C && Data[i+1] == 0x22)) +  (31 * (Data[i] == 0x0C && Data[i+1] == 0x23)) +  (32 * (Data[i] == 0x0C && Data[i+1] == 0x24)) +  (33 * (Data[i] == 0x0C && Data[i+1] == 0x25));
        
        if(OperatorIndex != 0)
        {
            OperatorExtraction[OperatorIndex-1](TopDictData, FloatBuffer, IntegerBuffer, IntegerIndex, FloatIndex, i, IndexMap, IndexLocation);
            IndexLocation = 0;
        }
        else //Gather the operand index condition and extract based on this.
        {
            OperandIndex = (1*(Data[i] != 0x1C && Data[i] != 0x1D && Data[i] != 0x1E && Data[i] >= 32 && Data[i] <= 246)) + (2*(Data[i] != 0x1C && Data[i] != 0x1D && Data[i] != 0x1E && Data[i] >= 247 && Data[i] <= 250)) + (3*(Data[i] != 0x1C && Data[i] != 0x1D && Data[i] != 0x1E && Data[i] >= 251 && Data[i] <= 254)) + (4*(Data[i] == 0x1C)) + (5*(Data[i] == 0x1D)) + (6*(Data[i] == 0x1E));
            if(OperandIndex == 6)
            {
                FloatBuffer[FloatIndex] = DictRealExtract(Data, i);
                IndexMap &= ~(0b00000001 << IndexLocation);
                printf("Index Map: 0x%x\n", IndexMap);
                IndexLocation++; 
                FloatIndex++; 
            }
            else
            {
                IntegerBuffer[IntegerIndex] = IntegerExtraction[OperandIndex-1](Data, i);
                IndexMap |= (0b00000001 << IndexLocation);
                printf("Index Map: 0x%x\n", IndexMap);
                IndexLocation++; 
                IntegerIndex++;
            }
        }
        // bool Operator0 = (Data[i] == 0x00);
        // bool Operator1 = (Data[i] == 0x01);
        // bool Operator2 = (Data[i] == 0x0C && Data[i+1] == 0x00);
        // bool Operator3 = (Data[i] == 0x02);
        // bool Operator4 = (Data[i] == 0x03);
        // bool Operator5 = (Data[i] == 0x04);
        // bool Operator6 = (Data[i] == 0x0C && Data[i+1] == 0x01);
        // bool Operator7 = (Data[i] == 0x0C && Data[i+1] == 0x02);
        // bool Operator8 = (Data[i] == 0x0C && Data[i+1] == 0x03);
        // bool Operator9 = (Data[i] == 0x0C && Data[i+1] == 0x04);  
        // bool Operator10 = (Data[i] == 0x0C && Data[i+1] == 0x05);
        // bool Operator11 = (Data[i] == 0x0C && Data[i+1] == 0x06);
        // bool Operator12 = (Data[i] == 0x0C && Data[i+1] == 0x07);
        // bool Operator13 = (Data[i] == 0x0D);
        // bool Operator14 = (Data[i] == 0x05);
        // bool Operator15 = (Data[i] == 0x0C && Data[i+1] == 0x08);
        // bool Operator16 = (Data[i] == 0x0E);
        // bool Operator17 = (Data[i] == 0x0F);
        // bool Operator18 = (Data[i] == 0x10);
        // bool Operator19 = (Data[i] == 0x11);
        // bool Operator20 = (Data[i] == 0x12);
        // bool Operator21 = (Data[i] == 0x0C && Data[i+1] == 0x14);
        // bool Operator22 = (Data[i] == 0x0C && Data[i+1] == 0x15);
        // bool Operator23 = (Data[i] == 0x0C && Data[i+1] == 0x16);
        // bool Operator24 = (Data[i] == 0x0C && Data[i+1] == 0x17);
        // bool Operator25 = (Data[i] == 0x0C && Data[i+1] == 0x1E);
        // bool Operator26 = (Data[i] == 0x0C && Data[i+1] == 0x1F);
        // bool Operator27 = (Data[i] == 0x0C && Data[i+1] == 0x20);
        // bool Operator28 = (Data[i] == 0x0C && Data[i+1] == 0x21);
        // bool Operator29 = (Data[i] == 0x0C && Data[i+1] == 0x22);
        // bool Operator30 = (Data[i] == 0x0C && Data[i+1] == 0x23);
        // bool Operator31 = (Data[i] == 0x0C && Data[i+1] == 0x24);
        // bool Operator32 = (Data[i] == 0x0C && Data[i+1] == 0x25);
        // bool Operator33 = (Data[i] == 0x0C && Data[i+1] == 0x26);

        // bool IndexZero = (Data[i] != 0x1C && Data[i] != 0x1D && Data[i] != 0x1E && Data[i] >= 32 && Data[i] <= 246);
        // bool IndexOne = (Data[i] != 0x1C && Data[i] != 0x1D && Data[i] != 0x1E && Data[i] >= 247 && Data[i] <= 250);
        // bool IndexTwo = (Data[i] != 0x1C && Data[i] != 0x1D && Data[i] != 0x1E && Data[i] >= 251 && Data[i] <= 254);
        // bool IndexThree = (Data[i] == 0x1C);
        // bool IndexFour = (Data[i] == 0x1D);
        // bool RealNumber = (Data[i] == 0x1E);
    }
    return 1;

}
int PPCFFExtractor::DecodeTopDictData()
{
    typedef int32_t(*Operand32)(uint8_t* Byte, int& CurrentIndex);
    Operand32 IntegerExtraction[5] = { DictDataExtract0, DictDataExtract1, DictDataExtract2, DictDataExtract3, DictDataExtract4};
    typedef void(*Operator32)(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
    Operator32 OperatorExtraction[33] = {NameInsert0, NameInsert1, NameInsert2, NameInsert3, NameInsert4, NameInsert5, NameInsert6, NameInsert7, NameInsert8, NameInsert9, NameInsert10, NameInsert11, NameInsert12, NameInsert13, NameInsert14, NameInsert15, NameInsert16, NameInsert17, NameInsert18, NameInsert19, NameInsert20, NameInsert21, NameInsert22, NameInsert23, NameInsert24, NameInsert25, NameInsert26, NameInsert27, NameInsert28, NameInsert29, NameInsert30, NameInsert31, NameInsert32};
    
    float FloatBuffer[5];
    uint8_t FloatIndex = 0;
    int32_t IntegerBuffer[5];
    uint8_t IntegerIndex = 0;
    int OperatorIndex = 0;
    int OperandIndex = 0;

    uint64_t IndexMap = 0b0000000;
    uint8_t IndexLocation = 0; 

    int size = TopDictIndex.Objects[0].size;
    uint8_t* Data = TopDictIndex.Objects[0].data;
    printf("\n");
    for(int i = 0; i < size; i++)
    {
        //Gather Information about if the current byte is an operator, if so deposit load.

        printf("0x%x\n", Data[i]);
        OperatorIndex = (1 * (Data[i] == 0x00)) +  (2 * (Data[i] == 0x01)) +  (3 * (Data[i] == 0x0C && Data[i+1] == 0x00)) + (4 * (Data[i] == 0x02)) +  (5 * (Data[i] == 0x03)) +  (6 * (Data[i] == 0x04)) +  (7 * (Data[i] == 0x0C && Data[i+1] == 0x01)) +  (8 * (Data[i] == 0x0C && Data[i+1] == 0x02)) +  (9 * (Data[i] == 0x0C && Data[i+1] == 0x03)) +  (10 * (Data[i] == 0x0C && Data[i+1] == 0x04)) +  (11 * (Data[i] == 0x0C && Data[i+1] == 0x05)) +  (12 * (Data[i] == 0x0C && Data[i+1] == 0x06)) +  (13 * (Data[i] == 0x0C && Data[i+1] == 0x07)) +  (14 * (Data[i] == 0x0D)) +  (15 * (Data[i] == 0x05)) +  (16 * (Data[i] == 0x0C && Data[i+1] == 0x08)) +  (17 * (Data[i] == 0x0E)) +  (18 * (Data[i] == 0x0F)) +  (19 * (Data[i] == 0x10)) +  (20 * (Data[i] == 0x11)) +  (21 * (Data[i] == 0x12)) +  (22 * (Data[i] == 0x0C && Data[i+1] == 0x14)) +  (23 * (Data[i] == 0x0C && Data[i+1] == 0x15)) +  (24 * (Data[i] == 0x0C && Data[i+1] == 0x16)) +  (25 * (Data[i] == 0x0C && Data[i+1] == 0x17)) +  (26 * (Data[i] == 0x0C && Data[i+1] == 0x1E)) +  (27 * (Data[i] == 0x0C && Data[i+1] == 0x1F)) +  (28 * (Data[i] == 0x0C && Data[i+1] == 0x20)) +  (29 * (Data[i] == 0x0C && Data[i+1] == 0x21)) +  (30 * (Data[i] == 0x0C && Data[i+1] == 0x22)) +  (31 * (Data[i] == 0x0C && Data[i+1] == 0x23)) +  (32 * (Data[i] == 0x0C && Data[i+1] == 0x24)) +  (33 * (Data[i] == 0x0C && Data[i+1] == 0x25));
        if(OperatorIndex != 0)
        {
            OperatorExtraction[OperatorIndex-1](TopDictData, FloatBuffer, IntegerBuffer, IntegerIndex, FloatIndex, i, IndexMap, IndexLocation);
            IndexLocation = 0;
            IndexMap = 0;
        }
        else //Gather the operand index condition and extract based on this.
        {
            OperandIndex = (1*(Data[i] != 0x1C && Data[i] != 0x1D && Data[i] != 0x1E && Data[i] >= 32 && Data[i] <= 246)) + (2*(Data[i] != 0x1C && Data[i] != 0x1D && Data[i] != 0x1E && Data[i] >= 247 && Data[i] <= 250)) + (3*(Data[i] != 0x1C && Data[i] != 0x1D && Data[i] != 0x1E && Data[i] >= 251 && Data[i] <= 254)) + (4*(Data[i] == 0x1C)) + (5*(Data[i] == 0x1D)) + (6*(Data[i] == 0x1E));
            if(OperandIndex == 6)
            {
                FloatBuffer[FloatIndex] = DictRealExtract(Data, i);
                IndexMap |= (0b00000001 << IndexLocation);
                
                printf("Index Map: 0x%x\n", IndexMap);
                IndexLocation++; 
                FloatIndex++; 
            }
            else
            {
                IntegerBuffer[IntegerIndex] = IntegerExtraction[OperandIndex-1](Data, i);
                IndexMap &= ~(0b00000001 << IndexLocation);
                printf("Index Map: 0x%x\n", IndexMap);
                IndexLocation++; 
                IntegerIndex++;
            }
        }
    }
    return 1;
}
int PPCFFExtractor::ExtractCharstrings()
{
    if(TopDictData.CharStrings == 0){return 0;}
    FILE* CharstringExtract = NULL;
    
    errno_t fErr = fopen_s(&CharstringExtract, FontPath, "rb");
    if(CharstringExtract == NULL || fErr != 0)
    {
        return 0;
    }
    int Delta = CFFTable.offset + TopDictData.CharStrings;
    
    int seekSee = fseek(CharstringExtract, TopDictData.CharStrings + CFFTable.offset, SEEK_SET); if(seekSee != 0){ fclose(CharstringExtract); return 0; }
    CharStringsIndex.count = ReadST(CharstringExtract);
    CharStringsIndex.offSize = ReadE(CharstringExtract);
    int TypeIndex = CharStringsIndex.offSize-1;
    //main problem here is the number of bytes required of each type is not properly being converted into bytes of u32 type, and so the offsets array is in shambles.
    
    //StringIndex.Offsets = (uint32_t*)malloc((StringIndex.offSize * (StringIndex.count+StringIndex.offSize)));
    CharStringsIndex.Offsets = (uint32_t*)malloc(sizeof(uint32_t) * CharStringsIndex.count + 1);
    CharStringsIndex.Objects = (PPCFFObjectEntry*)malloc(sizeof(PPCFFObjectEntry)*StringIndex.count);
    if(CharStringsIndex.Offsets == nullptr || CharStringsIndex.Objects == nullptr)
    {
        return 0;
    }
    
    typedef void (*ValueExtraction)(FILE*, uint32_t*, uint16_t);
    ValueExtraction ValueFunctions[4] =
    {
        ExtractOffsets8, ExtractOffsets16, ExtractOffsets24, ExtractOffsets32
    };
    ValueFunctions[TypeIndex](CharstringExtract, CharStringsIndex.Offsets, CharStringsIndex.count);
    CharStringsIndex.ObjectsBegin = (Delta + 3) + (CharStringsIndex.offSize * CharStringsIndex.count+1);

    fseek(CharstringExtract, CharStringsIndex.ObjectsBegin+2, SEEK_SET);
    //bingo mode!
    for(int i = 0; i < CharStringsIndex.count; i++)
    {
        CharStringsIndex.Objects[i].data = (uint8_t*)malloc(CharStringsIndex.Offsets[i+1]-CharStringsIndex.Offsets[i]);
        fread(CharStringsIndex.Objects[i].data, sizeof(uint8_t), CharStringsIndex.Offsets[i+1]-CharStringsIndex.Offsets[i], CharstringExtract);
        CharStringsIndex.Objects[i].size = CharStringsIndex.Offsets[i+1]-CharStringsIndex.Offsets[i];

        DisplayHex(CharStringsIndex.Objects[i].data, CharStringsIndex.Offsets[i+1]-CharStringsIndex.Offsets[i]);
        //printf("%s\n",StringIndex.Objects[i].data);
     
    }
    CharStringsIndex.EndOfTable = CharStringsIndex.ObjectsBegin + (CharStringsIndex.Offsets[CharStringsIndex.count] - CharStringsIndex.Offsets[0]);

    fclose(CharstringExtract);
    return 1;
    
}
int PPCFFExtractor::DecodeCharstrings()
{
    uint8_t* data;
    int i = 0;
    bool hstem = (data[i] == 0x01);
    int operatorIndex = 1 * (data[i] == 0x01) + 2 * (data[i] == 0x03) + 3 * (data[i] == 0x04) + 4 * (data[i] == 0x05) + 5 * (data[i] == 0x06) + 6 * (data[i] == 0x07) + 7 * (data[i] == 0x08) + 8 * (data[i] == 0x0a) + 9 * (data[i] == 0x0b) + 10 * (data[i] == 0x0c) + 11 * (data[i] == 0x0e) + 12 * (data[i] == 0x12) + 13 * (data[i] == 0x13) + 14 * (data[i] == 0x14) + 15 * (data[i] == 0x15) + 16 * (data[i] == 0x16) + 17 * (data[i] == 0x17) + 18 * (data[i] == 0x18) + 19 * (data[i] == 0x19) + 20 * (data[i] == 0x1a) + 21 * (data[i] == 0x1b) + 22 * (data[i] == 0x1c) + 23 * (data[i] == 0x1d) + 24 * (data[i] == 0x1e) + 25 * (data[i] == 0x1f) + 26 * (data[i] == 0x0c && data[i+1] == 0x03) + 27 * (data[i] == 0x0c && data[i+1] == 0x04) + 28 * (data[i] == 0x0c && data[i+1] == 0x05) + 29 * (data[i] == 0x0c && data[i+1] == 0x09) + 30 * (data[i] == 0x0c && data[i+1] == 0x0a) + 31 * (data[i] == 0x0c && data[i+1] == 0x0b) + 32 * (data[i] == 0x0c && data[i+1] == 0x0c) + 33 * (data[i] == 0x0c && data[i+1] == 0x0e) + 34 * (data[i] == 0x0c && data[i+1] == 0x0f) + 35 * (data[i] == 0x0c && data[i+1] == 0x12) + 36 * (data[i] == 0x0c && data[i+1] == 0x14) + 37 * (data[i] == 0x0c && data[i+1] == 0x15) + 38 * (data[i] == 0x0c && data[i+1] == 0x16) + 39 * (data[i] == 0x0c && data[i+1] == 0x17) + 40 * (data[i] == 0x0c && data[i+1] == 0x18) + 41 * (data[i] == 0x0c && data[i+1] == 0x1a) + 42 * (data[i] == 0x0c && data[i+1] == 0x1b) + 43 * (data[i] == 0x0c && data[i+1] == 0x1c) + 44 * (data[i] == 0x0c && data[i+1] == 0x1d) + 45 * (data[i] == 0x0c && data[i+1] == 0x1e) + 46 * (data[i] == 0x0c && data[i+1] == 0x22) + 47 * (data[i] == 0x0c && data[i+1] == 0x23) + 48 * (data[i] == 0x0c && data[i+1] == 0x24) + 49 * (data[i] == 0x0c && data[i+1] == 0x25);
    

}
int PPCFFExtractor::ExtractCharsets()
{
    if(TopDictData.charset == 0){return 0;}
    FILE* CharsetExtract = NULL;
    
    errno_t fErr = fopen_s(&CharsetExtract, FontPath, "rb");
    if(CharsetExtract == NULL || fErr != 0)
    {
        return 0;
    }
    fseek(CharsetExtract, TopDictData.charset + CFFTable.offset, SEEK_SET);
    uint8_t TableVersion = ReadE(CharsetExtract);
    fclose(CharsetExtract);

}



PPCFFExtractor::~PPCFFExtractor(){}