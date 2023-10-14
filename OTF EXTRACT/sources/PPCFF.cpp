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
    //printf("\n b0 %x b1 %x\n", Byte[CurrentIndex], Byte[CurrentIndex+1]);
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

#pragma region TopProccedure
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
#pragma endregion
    
#pragma region CharstringInserts
    void PPCFF::CharStringInsert0(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath){}
    void PPCFF::CharStringInsert1(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath)
    {
        PPCFFHint Hintly;
        Hintly.intArguments.push_back(intStack[0]);
        Hintly.intArguments.push_back(intStack[1]);

        for(int i = 2; i < intIndex; i++)
        {
            Hintly.intArguments.push_back(intStack[i]);
            Hintly.intArguments.push_back(intStack[i+1]);

            i++;
        }
        intIndex = 0;
        floatIndex = 0;
        DataIndex = 0;
        DataEntries = 0;
        

    }
    void PPCFF::CharStringInsert2(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath)
    {
        PPCFFHint Hintly;

        Hintly.intArguments.push_back(intStack[0]);
        Hintly.intArguments.push_back(intStack[1]);

        for(int i = 2; i < intIndex; i++)
        {
            Hintly.intArguments.push_back(intStack[i]);
            Hintly.intArguments.push_back(intStack[i+1]);

            i++;
        }
        intIndex = 0;
        floatIndex = 0;
        DataIndex = 0;
        DataEntries = 0;
    }
    void PPCFF::CharStringInsert3(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath)
    {
        if(OriginOfPath.x != -69 && OriginOfPath.y != -69)
        {
            Line nl;
            nl.curveType = PPCFF_LINE;
            nl.A = pen;
            nl.B = OriginOfPath;
            CharData.Lines.push_back(nl);
            OriginOfPath = {-69,-69};
        }
        pen.y += intStack[0];
        intIndex = 0;
        floatIndex = 0;
        DataIndex = 0;
        DataEntries = 0;

    }
    void PPCFF::CharStringInsert4(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath)
    {
        if(OriginOfPath.x == -69 && OriginOfPath.y == -69)
        {
            OriginOfPath = pen;
        }
        Line nl;
        nl.curveType = PPCFF_LINE;
        for(int i = 0; i < DataEntries; i++)
        {
            // bool CurrentIndex = (DataIndex >> i) & (1);
            // if(CurrentIndex == 0){ /*DictData.FontMatrix[i] = intStack[intIndex];*/ intIndex++; }
            // if(CurrentIndex == 1){ /*DictData.FontMatrix[i] = floatStack[floatIndex];*/ floatIndex++; }
            
            nl.A = pen;
            pen.x += intStack[i];
            pen.y += intStack[i+1];
            nl.B = pen;
            CharData.Lines.push_back(nl);
            
            i++;
        }

        // nl.A = pen;
        // nl.B = Origin;
        // CharData.Lines.push_back(nl);

        intIndex = 0;
        floatIndex = 0;
        DataIndex = 0;
        DataEntries = 0;
        //CharData.ReadGeom();
        
        
    }
    void PPCFF::CharStringInsert5(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath)
    {
        Line nl;
        nl.curveType = PPCFF_LINE;
        if(OriginOfPath.x == -69 && OriginOfPath.y == -69)
        {
            OriginOfPath = pen;
        }
        // }else if(CharData.Lines.back().curveType == PPCFF_CUBIC)
        // {
        //     nl.A =
        // }

        if(intIndex % 2 == 0)
        {
            
            for(int i = 0; i < intIndex; i++)
            {
                int dxa = intStack[i];
                nl.A = pen;
                pen.x += dxa;
                nl.B = pen;
                CharData.Lines.push_back(nl);

                int dyb = intStack[i+1];
                nl.A = pen;
                pen.y += dyb;
                nl.B = pen;
                CharData.Lines.push_back(nl);
                i++;
            }
        }else
        {
            int length = intStack[0];

            nl.curveType = PPCFF_LINE;
            nl.A = pen;
            pen.x += length;
            nl.B = pen;
            CharData.Lines.push_back(nl);

            Vectoid2 L = pen;
            for(int i = 1; i < intIndex; i++)
            {
                int dya = intStack[i];
                nl.A = pen;
                pen.y += dya;
                nl.B = pen;
                CharData.Lines.push_back(nl);

                int dxb = intStack[i+1];
                nl.A = pen;
                pen.x += dxb;
                nl.B = pen;
                CharData.Lines.push_back(nl);
                i++;
            }

            
        }

        // nl.A = pen;
        // nl.B = Origin;
        // CharData.Lines.push_back(nl);

        //CharData.ReadGeom();

        intIndex = 0;
        floatIndex = 0;
        DataIndex = 0;
        DataEntries = 0;
    }
    void PPCFF::CharStringInsert6(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath)
    {
        Line nl;
        nl.curveType = PPCFF_LINE;
        if(OriginOfPath.x == -69 && OriginOfPath.y == -69)
        {
            OriginOfPath = pen;
        }
        if(intIndex % 2 == 0)
        {
            for(int i = 0; i < intIndex; i++)
            {
                int dya = intStack[i];
                nl.A = pen;
                pen.y += dya;
                nl.B = pen;
                CharData.Lines.push_back(nl);

                int dxb = intStack[i+1];
                nl.A = pen;
                pen.x += dxb;
                nl.B = pen;
                CharData.Lines.push_back(nl);
                i++;
            }
        }else
        {
            int length = intStack[0];

            nl.A = pen;
            pen.y += length;
            nl.B = pen;
            CharData.Lines.push_back(nl);

            for(int i = 1; i < intIndex; i++)
            {
                int dxa = intStack[i];
                nl.A = pen;
                pen.x += dxa;
                nl.B = pen;
                CharData.Lines.push_back(nl);

                int dyb = intStack[i+1];
                nl.A = pen;
                pen.y += dyb;
                nl.B = pen;
                CharData.Lines.push_back(nl);
                i++;
            }

            
        }

        // nl.A = pen;
        // nl.B = Origin;
        // CharData.Lines.push_back(nl);

        //CharData.ReadGeom();
        intIndex = 0;
        floatIndex = 0;
        DataIndex = 0;
        DataEntries = 0;

        
    }
    void PPCFF::CharStringInsert7(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath)
    {
        int curves = intIndex/6;

        // if(OriginOfPath.x == -69 && OriginOfPath.y == -69)
        // {
        //     OriginOfPath = pen;
        // }

        for(int i = 0; i < curves; i++)
        {
            int cindex = i*6;

            Line curveLine;
            curveLine.curveType = PPCFF_CUBIC;

            curveLine.A = pen;
            pen.x += intStack[cindex];
            pen.y += intStack[cindex+1];
            curveLine.B = pen;
            pen.x += intStack[cindex+2];
            pen.y += intStack[cindex+3];
            curveLine.C = pen;
            pen.x += intStack[cindex+4];
            pen.y += intStack[cindex+5];
            curveLine.D = pen;
            
            

            CharData.Lines.push_back(curveLine);
        }

        //CharData.ReadGeom();

        intIndex = 0;
        floatIndex = 0;
        DataIndex = 0;
        DataEntries = 0;
    }
    void PPCFF::CharStringInsert8(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath){}
    void PPCFF::CharStringInsert9(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath)
    {
        // if(OriginOfPath.x != -69 && OriginOfPath.y != -69)
        // {
        //     Line nl;
        //     nl.curveType = PPCFF_LINE;
        //     nl.A = pen;
        //     nl.B = OriginOfPath;
        //     CharData.Lines.push_back(nl);
        //     OriginOfPath = {-69,-69};
        // }
        CharData.ReadGeom();
    }
    void PPCFF::CharStringInsert10(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath){}
    void PPCFF::CharStringInsert11(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath)
    {
        if(OriginOfPath.x != -69 && OriginOfPath.y != -69)
        {
            Line nl;
            nl.curveType = PPCFF_LINE;
            nl.A = pen;
            nl.B = OriginOfPath;
            CharData.Lines.push_back(nl);
            OriginOfPath = {-69,-69};
        }
        CharData.ReadGeom();

    }
    void PPCFF::CharStringInsert12(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath)
    {
        PPCFFHint Hintly;
        Hintly.intArguments.push_back(intStack[0]);
        Hintly.intArguments.push_back(intStack[1]);

        for(int i = 2; i < DataEntries; i++)
        {
            // bool CurrentIndex = (DataIndex >> i) & (1);
            // if(CurrentIndex == 0){ /*DictData.FontMatrix[i] = intStack[intIndex];*/ intIndex++; }
            // if(CurrentIndex == 1){ /*DictData.FontMatrix[i] = floatStack[floatIndex];*/ floatIndex++; }
            Hintly.intArguments.push_back(intStack[i]);
        }

        CharData.Hints.push_back(Hintly);
        intIndex = 0;
        floatIndex = 0;
        DataIndex = 0;
        DataEntries = 0;

        Index++;
    }
    void PPCFF::CharStringInsert13(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath)
    {
        PPCFFHint Hintly;

        // Hintly.intArguments.push_back(intStack[0]);
        // Hintly.intArguments.push_back(intStack[1]);
        // Hintly.intArguments.push_back(intStack[2]);
        Hintly.intArguments.push_back(data[++Index]);

        intIndex = 0;
        floatIndex = 0;
        DataIndex = 0;
        DataEntries = 0;
    }
    void PPCFF::CharStringInsert14(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath){}
    void PPCFF::CharStringInsert15(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath)
    {

        if(OriginOfPath.x != -69 && OriginOfPath.y != -69)
        {
            Line nl;
            nl.curveType = PPCFF_LINE;
            nl.A = pen;
            nl.B = OriginOfPath;
            CharData.Lines.push_back(nl);
            //CharData.ReadGeom();
            OriginOfPath = {-69,-69};
        }

        pen.x += intStack[0]; //funits??
        pen.y += intStack[1];

        intIndex = 0;
        floatIndex = 0;
        DataIndex = 0;
        DataEntries = 0;
    }
    void PPCFF::CharStringInsert16(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath)
    {

        pen.x += intStack[0];

        if(OriginOfPath.x != -69 && OriginOfPath.y != -69)
        {
            Line nl;
            nl.A = pen;
            nl.B = OriginOfPath;
            CharData.Lines.push_back(nl);
            OriginOfPath = {-69,-69};
        }

        intIndex = 0;
        floatIndex = 0;
        DataIndex = 0;
        DataEntries = 0;


    }
    void PPCFF::CharStringInsert17(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath){}
    void PPCFF::CharStringInsert18(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath){}
    void PPCFF::CharStringInsert19(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath){}
    void PPCFF::CharStringInsert20(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath){}
    void PPCFF::CharStringInsert21(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath)
    {

        int ArgumentCount = intIndex;
        bool Dy = ArgumentCount%2!=0;

        int NumberOfCurves = (ArgumentCount-Dy)/4;

        Line c;

        

        for(int i = 0; i < NumberOfCurves; i++)
        {
            c.curveType = PPCFF_CUBIC;

            int curveIndex = (i*4)+Dy;

            c.A = pen;

        
            pen.x += intStack[curveIndex];
            pen.y += intStack[0]*(i==0)*(Dy);
            
            c.B = pen;
            
            pen.x += intStack[curveIndex+1];
            pen.y += intStack[curveIndex+2];
            c.C = pen;

            pen.x += intStack[curveIndex+3];

            c.D = pen;

            CharData.Lines.push_back(c);


            
        }
        CharData.ReadGeom();


    }
    void PPCFF::CharStringInsert22(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath)
    {

        //pen.x += intStack[]


    }
    void PPCFF::CharStringInsert23(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath)
    {

    }
    void PPCFF::CharStringInsert24(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath)
    {

        if(OriginOfPath.x == -69 && OriginOfPath.y == -69)
        {
            OriginOfPath = pen;
        }

        Line curveLine;
        curveLine.curveType = PPCFF_CUBIC;
        int CurveIndex = 0;
        if((intIndex%8) != 0)
        {
            curveLine.A = pen;
            pen.y += intStack[0];
            curveLine.B = pen;
            pen.x += intStack[1];
            pen.y += intStack[2];
            curveLine.C = pen;
            pen.x += intStack[3];
            curveLine.D = pen;


            

            bool Oditity = (intIndex % 2 != 0);
            
            int NumberOfCurves = (intIndex-(4 + Oditity))%8;

            if(NumberOfCurves != 0 && !Oditity)
            {
                CharData.Lines.push_back(curveLine);
            }
            
            

            for(int i = 0; i < NumberOfCurves; i++)
            {
                CurveIndex = (i*8)+4;
                curveLine.A = pen;
                pen.x += intStack[CurveIndex];
                curveLine.B = pen;
                pen.x += intStack[CurveIndex+1];
                pen.y += intStack[CurveIndex+2];
                curveLine.C = pen;
                pen.y += intStack[CurveIndex+3];
                curveLine.D = pen;

                CharData.Lines.push_back(curveLine);

                curveLine.A = pen;
                pen.y += intStack[CurveIndex+4];
                curveLine.B = pen;
                pen.x += intStack[CurveIndex+5];
                pen.y += intStack[CurveIndex+6];
                curveLine.C = pen;
                pen.x += intStack[CurveIndex+7];
                curveLine.D = pen;
                if(i < NumberOfCurves-1) CharData.Lines.push_back(curveLine);
                
            }

            if(!Oditity)
            {
                CharData.Lines.push_back(curveLine);
            }else{
                curveLine.D.y += intStack[(NumberOfCurves*8)+4];
                CharData.Lines.push_back(curveLine);

            }

        }else
        {   

            int NumberOfCurves = (intIndex)%8;

            for(int i = 0; i < NumberOfCurves; i++)
            {
                CurveIndex = (i*8)+4;
                curveLine.A = pen;
                pen.y += intStack[CurveIndex];
                curveLine.B = pen;
                pen.x += intStack[CurveIndex+1];
                pen.y += intStack[CurveIndex+2];
                curveLine.C = pen;
                pen.x += intStack[CurveIndex+3];
                curveLine.D = pen;

                CharData.Lines.push_back(curveLine);

                curveLine.A = pen;
                pen.x += intStack[CurveIndex+4];
                curveLine.B = pen;
                pen.x += intStack[CurveIndex+5];
                pen.y += intStack[CurveIndex+6];
                curveLine.C = pen;
                pen.y += intStack[CurveIndex+7];
                curveLine.D = pen;
                if(i < NumberOfCurves-1) CharData.Lines.push_back(curveLine);
            }

            if(intIndex %2 == 0)
            {
                CharData.Lines.push_back(curveLine);
            }else{
                curveLine.D.x += intStack[(NumberOfCurves*8)+4];
                CharData.Lines.push_back(curveLine);
            }
        }

        //CharData.ReadGeom();
        intIndex = 0;
        floatIndex = 0;
        DataIndex = 0;
        DataEntries = 0;
        

    }
    void PPCFF::CharStringInsert25(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath)
    {
        if(OriginOfPath.x == -69 && OriginOfPath.y == -69)
        {
            OriginOfPath = pen;
        }

        Line curveLine;
        curveLine.curveType = PPCFF_CUBIC;
        int CurveIndex = 0;
        if((intIndex%8) != 0)
        {
            curveLine.A = pen;
            pen.x += intStack[0];
            curveLine.B = pen;
            pen.x += intStack[1];
            pen.y += intStack[2];
            curveLine.C = pen;
            pen.y += intStack[3];
            curveLine.D = pen;


            bool Oditity = (intIndex % 2 != 0);
            
            int NumberOfCurves = (intIndex-(4 + Oditity))%8;

            if(NumberOfCurves != 0 && !Oditity)
            {
                CharData.Lines.push_back(curveLine);
            }
            
            

            for(int i = 0; i < NumberOfCurves; i++)
            {
                CurveIndex = (i*8)+4;
                curveLine.A = pen;
                pen.y += intStack[CurveIndex];
                curveLine.B = pen;
                pen.x += intStack[CurveIndex+1];
                pen.y += intStack[CurveIndex+2];
                curveLine.C = pen;
                pen.x += intStack[CurveIndex+3];
                curveLine.D = pen;

                CharData.Lines.push_back(curveLine);

                curveLine.A = pen;
                pen.x += intStack[CurveIndex+4];
                curveLine.B = pen;
                pen.x += intStack[CurveIndex+5];
                pen.y += intStack[CurveIndex+6];
                curveLine.C = pen;
                pen.y += intStack[CurveIndex+7];
                curveLine.D = pen;
                if(i < NumberOfCurves-1) CharData.Lines.push_back(curveLine);
                
            }

            if(!Oditity)
            {
                CharData.Lines.push_back(curveLine);
            }else{
                curveLine.D.x += intStack[(NumberOfCurves*8)+4];
                CharData.Lines.push_back(curveLine);

            }

        }else
        {   

            int NumberOfCurves = (intIndex)%8;

            for(int i = 0; i < NumberOfCurves; i++)
            {
                CurveIndex = (i*8)+4;
                curveLine.A = pen;
                pen.y += intStack[CurveIndex];
                curveLine.B = pen;
                pen.x += intStack[CurveIndex+1];
                pen.y += intStack[CurveIndex+2];
                curveLine.C = pen;
                pen.x += intStack[CurveIndex+3];
                curveLine.D = pen;

                CharData.Lines.push_back(curveLine);

                curveLine.A = pen;
                pen.x += intStack[CurveIndex+4];
                curveLine.B = pen;
                pen.x += intStack[CurveIndex+5];
                pen.y += intStack[CurveIndex+6];
                curveLine.C = pen;
                pen.y += intStack[CurveIndex+7];
                curveLine.D = pen;
                if(i < NumberOfCurves-1) CharData.Lines.push_back(curveLine);
            }

            if(intIndex %2 == 0)
            {
                CharData.Lines.push_back(curveLine);
            }else{
                curveLine.D.y += intStack[(NumberOfCurves*8)+4];
                CharData.Lines.push_back(curveLine);
            }
        }


        intIndex = 0;
        floatIndex = 0;
        DataIndex = 0;
        DataEntries = 0;
    }
    void PPCFF::CharStringInsert26(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath){}
    void PPCFF::CharStringInsert27(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath){}
    void PPCFF::CharStringInsert28(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath){}
    void PPCFF::CharStringInsert29(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath){}
    void PPCFF::CharStringInsert30(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath){}
    void PPCFF::CharStringInsert31(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath){}
    void PPCFF::CharStringInsert32(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath){}
    void PPCFF::CharStringInsert33(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath){}
    void PPCFF::CharStringInsert34(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath){}
    void PPCFF::CharStringInsert35(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath){}
    void PPCFF::CharStringInsert36(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath){}
    void PPCFF::CharStringInsert37(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath){}
    void PPCFF::CharStringInsert38(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath){}
    void PPCFF::CharStringInsert39(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath){}
    void PPCFF::CharStringInsert40(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath){}
    void PPCFF::CharStringInsert41(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath){}
    void PPCFF::CharStringInsert42(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath){}
    void PPCFF::CharStringInsert43(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath){}
    void PPCFF::CharStringInsert44(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath){}
    void PPCFF::CharStringInsert45(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath){}
    void PPCFF::CharStringInsert46(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath){}
    void PPCFF::CharStringInsert47(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath){}
    void PPCFF::CharStringInsert48(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath){}
#pragma endregion

#pragma region DictData
void PPCFF::PrivateOperatorExtraction0(PPCFFPrivateData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries)
{
    intIndex = 0;
    floatIndex = 0;
    for(int i = 0; i < DataEntries; i++)
    {
        bool CurrentIndex = (DataIndex >> i) & (1);
        if(CurrentIndex == 0){ DictData.BlueValues.push_back(intStack[intIndex]); intIndex++; }
        if(CurrentIndex == 1){ DictData.BlueValues.push_back(floatStack[floatIndex]); floatIndex++; }
    }    
    intIndex = 0;
    floatIndex = 0;
    DataIndex = 0;
    DataEntries = 0;
}
void PPCFF::PrivateOperatorExtraction1(PPCFFPrivateData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries)
{
    intIndex = 0;
    floatIndex = 0;
    for(int i = 0; i < DataEntries; i++)
    {
        bool CurrentIndex = (DataIndex >> i) & (1);
        if(CurrentIndex == 0){ DictData.OtherBlues.push_back(intStack[intIndex]); intIndex++; }
        if(CurrentIndex == 1){ DictData.OtherBlues.push_back(floatStack[floatIndex]); floatIndex++; }
    }    
    intIndex = 0;
    floatIndex = 0;
    DataIndex = 0;
    DataEntries = 0;
}
void PPCFF::PrivateOperatorExtraction2(PPCFFPrivateData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries)
{
    intIndex = 0;
    floatIndex = 0;
    for(int i = 0; i < DataEntries; i++)
    {
        bool CurrentIndex = (DataIndex >> i) & (1);
        if(CurrentIndex == 0){ DictData.FamilyBlues.push_back(intStack[intIndex]); intIndex++; }
        if(CurrentIndex == 1){ DictData.FamilyBlues.push_back(floatStack[floatIndex]); floatIndex++; }
    }    
    intIndex = 0;
    floatIndex = 0;
    DataIndex = 0;
    DataEntries = 0;
}
void PPCFF::PrivateOperatorExtraction3(PPCFFPrivateData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries)
{
    intIndex = 0;
    floatIndex = 0;
    for(int i = 0; i < DataEntries; i++)
    {
        bool CurrentIndex = (DataIndex >> i) & (1);
        if(CurrentIndex == 0){ DictData.FamilyOtherBlues.push_back(intStack[intIndex]); intIndex++; }
        if(CurrentIndex == 1){ DictData.FamilyOtherBlues.push_back(floatStack[floatIndex]); floatIndex++; }
    }    
    intIndex = 0;
    floatIndex = 0;
    DataIndex = 0;
    DataEntries = 0;
}
void PPCFF::PrivateOperatorExtraction4(PPCFFPrivateData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries)
{
    DictData.BlueScale = floatStack[0];

    intIndex = 0;
    floatIndex = 0;
    DataIndex = 0;
    DataEntries = 0;
}
void PPCFF::PrivateOperatorExtraction5(PPCFFPrivateData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries)
{

    if(floatIndex > 0)
    {
        DictData.BlueShift = floatStack[0];
    }else
    {
        DictData.BlueShift = intStack[0];
    }

    intIndex = 0;
    floatIndex = 0;
    DataIndex = 0;
    DataEntries = 0;
}
void PPCFF::PrivateOperatorExtraction6(PPCFFPrivateData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries)
{

    if(floatIndex > 0)
    {
        DictData.BlueFuzz = floatStack[0];
    }else
    {
        DictData.BlueFuzz = intStack[0];
    }

    intIndex = 0;
    floatIndex = 0;
    DataIndex = 0;
    DataEntries = 0;
}
void PPCFF::PrivateOperatorExtraction7(PPCFFPrivateData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries)
{

    if(floatIndex > 0)
    {
        DictData.StdHW = floatStack[0];
    }else
    {
        DictData.StdHW = intStack[0];
    }

    intIndex = 0;
    floatIndex = 0;
    DataIndex = 0;
    DataEntries = 0;
}
void PPCFF::PrivateOperatorExtraction8(PPCFFPrivateData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries)
{
    if(floatIndex > 0)
    {
        DictData.StdVW = floatStack[0];
    }else
    {
        DictData.StdVW = intStack[0];
    }

    intIndex = 0;
    floatIndex = 0;
    DataIndex = 0;
    DataEntries = 0;
}
void PPCFF::PrivateOperatorExtraction9(PPCFFPrivateData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries)
{
    intIndex = 0;
    floatIndex = 0;
    for(int i = 0; i < DataEntries; i++)
    {
        bool CurrentIndex = (DataIndex >> i) & (1);
        if(CurrentIndex == 0){ DictData.StempSnapH.push_back(intStack[intIndex]); intIndex++; }
        if(CurrentIndex == 1){ DictData.StempSnapH.push_back(floatStack[floatIndex]); floatIndex++; }
    }    
    intIndex = 0;
    floatIndex = 0;
    DataIndex = 0;
    DataEntries = 0;
}
void PPCFF::PrivateOperatorExtraction10(PPCFFPrivateData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries)
{
    intIndex = 0;
    floatIndex = 0;
    for(int i = 0; i < DataEntries; i++)
    {
        bool CurrentIndex = (DataIndex >> i) & (1);
        if(CurrentIndex == 0){ DictData.StempSnapV.push_back(intStack[intIndex]); intIndex++; }
        if(CurrentIndex == 1){ DictData.StempSnapV.push_back(floatStack[floatIndex]); floatIndex++; }
    }    
    intIndex = 0;
    floatIndex = 0;
    DataIndex = 0;
    DataEntries = 0;
}
void PPCFF::PrivateOperatorExtraction11(PPCFFPrivateData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries)
{
    DictData.ForceBold = intStack[0];

    intIndex = 0;
    floatIndex = 0;
    DataIndex = 0;
    DataEntries = 0;
}
void PPCFF::PrivateOperatorExtraction12(PPCFFPrivateData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries)
{
    DictData.LanguageGroup = intStack[0];

    intIndex = 0;
    floatIndex = 0;
    DataIndex = 0;
    DataEntries = 0;
}
void PPCFF::PrivateOperatorExtraction13(PPCFFPrivateData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries)
{
    DictData.ExpansionFactor = floatStack[0];

    intIndex = 0;
    floatIndex = 0;
    DataIndex = 0;
    DataEntries = 0;
}
void PPCFF::PrivateOperatorExtraction14(PPCFFPrivateData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries)
{

    if(floatIndex > 0)
    {
        DictData.initalRandomSed = floatStack[0];
    }else
    {
        DictData.initalRandomSed = intStack[0];
    }

    intIndex = 0;
    floatIndex = 0;
    DataIndex = 0;
    DataEntries = 0;


}
void PPCFF::PrivateOperatorExtraction15(PPCFFPrivateData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries)
{

    DictData.Subrs = intStack[0];

    intIndex = 0;
    floatIndex = 0;
    DataIndex = 0;
    DataEntries = 0;

    
}
void PPCFF::PrivateOperatorExtraction16(PPCFFPrivateData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries)
{

    if(floatIndex > 0)
    {
        DictData.defaultWidthX = floatStack[0];
    }else
    {
        DictData.defaultWidthX = intStack[0];
    }

    intIndex = 0;
    floatIndex = 0;
    DataIndex = 0;
    DataEntries = 0;

    
}
void PPCFF::PrivateOperatorExtraction17(PPCFFPrivateData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries)
{
    if(floatIndex > 0)
    {
        DictData.nominalWidthX = floatStack[0];
    }else
    {
        DictData.nominalWidthX = intStack[0];
    }

    intIndex = 0;
    floatIndex = 0;
    DataIndex = 0;
    DataEntries = 0;
}
#pragma endregion

void DisplayHex(uint8_t* data, int size)
{
    printf("\n");
    for(int i = 0; i < size; i++)
    {
        printf("%X ", data[i]);
        if((i+1) % 15 == 0){printf("\n");}
    }
    printf("\n");
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
    if(NameIndex.Offsets == nullptr)
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
    NameIndex.EndOfTable = NameIndex.ObjectsBegin + (NameIndex.Offsets[NameIndex.count] - NameIndex.Offsets[0]);
    return 0;


    fseek(NameIndexExtract, NameIndex.ObjectsBegin, SEEK_SET);
    for(int i = 0; i < NameIndex.count; i++)
    {
        NameIndex.Objects[i].data = (uint8_t*)malloc(NameIndex.Offsets[i+1]-NameIndex.Offsets[i]);
        fread(NameIndex.Objects[i].data, sizeof(uint8_t), NameIndex.Offsets[i+1]-NameIndex.Offsets[i], NameIndexExtract);
    }
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

    fpos_t Begin; fgetpos(File, &Begin);
    Index.ObjectsBegin = Begin;

    //fseek(File, Index.ObjectsBegin, SEEK_SET);
    
    for(int i = 0; i < Index.count; i++)
    {
        Index.Objects[i].data = (uint8_t*)malloc(Index.Offsets[i+1]-Index.Offsets[i]);
        fread(Index.Objects[i].data, sizeof(uint8_t), Index.Offsets[i+1]-Index.Offsets[i], File);
        Index.Objects[i].size = Index.Offsets[i+1]-Index.Offsets[i];
        printf("\n");
        DisplayHex(Index.Objects[i].data, Index.Offsets[i+1]-Index.Offsets[i]);
        printf("\n");
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


    fpos_t Begin;
    fgetpos(StringDictExtract, &Begin);
    StringIndex.ObjectsBegin = Begin;

    for(int i = 0; i < StringIndex.count; i++)
    {
        StringIndex.Objects[i].data = (uint8_t*)malloc(StringIndex.Offsets[i+1]-StringIndex.Offsets[i]);
        fread(StringIndex.Objects[i].data, sizeof(uint8_t), StringIndex.Offsets[i+1]-StringIndex.Offsets[i], StringDictExtract);
        StringIndex.Objects[i].size = StringIndex.Offsets[i+1]-StringIndex.Offsets[i];

        //DisplayHex(StringIndex.Objects[i].data, StringIndex.Objects[i].size);
        //printf("%s\n",StringIndex.Objects[i].data);
    }

    //fgetpos(StringDictExtract, &Begin);
    StringIndex.EndOfTable = Begin+(StringIndex.Offsets[StringIndex.count]-StringIndex.Offsets[0]);



    fclose(StringDictExtract);
    return 1;
}
int PPCFFExtractor::ExtractGlobalSubroutineIndex()
{
    FILE* File = NULL;
    
    errno_t fErr = fopen_s(&File, FontPath, "rb");
    if(File == NULL || fErr != 0)
    {
        return 0;
    }
    int seekSee = fseek(File, StringIndex.EndOfTable, SEEK_SET); if(seekSee != 0){ fclose(File); return 0; }
    

    GlobalSubroutineIndex.count = ReadST(File);

    if(GlobalSubroutineIndex.count == 0) return -1;

    GlobalSubroutineIndex.offSize = ReadE(File);
    
    int TypeIndex = GlobalSubroutineIndex.offSize-1;

    GlobalSubroutineIndex.Offsets = (uint32_t*)malloc(sizeof(uint32_t) * GlobalSubroutineIndex.count+1);

    GlobalSubroutineIndex.Objects = (PPCFFObjectEntry*)malloc(sizeof(PPCFFObjectEntry)*GlobalSubroutineIndex.count);
    if(GlobalSubroutineIndex.Offsets == nullptr || GlobalSubroutineIndex.Objects == nullptr)
    {
        return 0;
    }
    
    typedef void (*ValueExtraction)(FILE*, uint32_t*, uint16_t);
    ValueExtraction ValueFunctions[4] =
    {
        ExtractOffsets8, ExtractOffsets16, ExtractOffsets24, ExtractOffsets32
    };
    ValueFunctions[TypeIndex](File, GlobalSubroutineIndex.Offsets, GlobalSubroutineIndex.count);

    for(int i = 0; i < GlobalSubroutineIndex.count; i++)
    {
        GlobalSubroutineIndex.Objects[i].data = (uint8_t*)malloc(GlobalSubroutineIndex.Offsets[i+1]-GlobalSubroutineIndex.Offsets[i]);
        fread(GlobalSubroutineIndex.Objects[i].data, sizeof(uint8_t), GlobalSubroutineIndex.Offsets[i+1]-GlobalSubroutineIndex.Offsets[i], File);
        GlobalSubroutineIndex.Objects[i].size = GlobalSubroutineIndex.Offsets[i+1]-GlobalSubroutineIndex.Offsets[i];
    }
    GlobalSubroutineIndex.EndOfTable = GlobalSubroutineIndex.ObjectsBegin + (GlobalSubroutineIndex.Offsets[GlobalSubroutineIndex.count] - GlobalSubroutineIndex.Offsets[0]);

    uint8_t format = ReadE(File);
    uint8_t nCodes = ReadE(File);

    return 1;

    fclose(File);
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
    DisplayHex(Data, size);
    //printf("\n");
    for(int i = 0; i < size; i++)
    {
        //Gather Information about if the current byte is an operator, if so deposit load.

        //printf("0x%x\n", Data[i]);
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
                
                IndexLocation++; 
                FloatIndex++; 
            }
            else
            {
                IntegerBuffer[IntegerIndex] = IntegerExtraction[OperandIndex-1](Data, i);
                IndexMap &= ~(0b00000001 << IndexLocation);
                //printf("Index Map: 0x%x\n", IndexMap);
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

    CharStringsIndex.Offsets = (uint32_t*)malloc(sizeof(uint32_t) * (CharStringsIndex.count + 1));

    CharStringsIndex.Objects = (PPCFFObjectEntry*)malloc(sizeof(PPCFFObjectEntry)*CharStringsIndex.count);
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


    for(int i = 0; i < CharStringsIndex.count; i++)
    {
        CharStringsIndex.Objects[i].data = (uint8_t*)malloc(CharStringsIndex.Offsets[i+1]-CharStringsIndex.Offsets[i]);
        fread(CharStringsIndex.Objects[i].data, sizeof(uint8_t), CharStringsIndex.Offsets[i+1]-CharStringsIndex.Offsets[i], CharstringExtract);
        CharStringsIndex.Objects[i].size = CharStringsIndex.Offsets[i+1]-CharStringsIndex.Offsets[i];
    }

    CharStringsIndex.EndOfTable = CharStringsIndex.ObjectsBegin + (CharStringsIndex.Offsets[CharStringsIndex.count] - CharStringsIndex.Offsets[0]);

    fclose(CharstringExtract);
    return 1;
    
}


PPCFFCharstring PPCFFExtractor::DecodeSingularCharstring()
{

    uint8_t* Data = CharStringsIndex.Objects[6].data;
    int size = CharStringsIndex.Offsets[7]-CharStringsIndex.Offsets[6];
    printf("\n");
    DisplayHex(Data, size);

    typedef int32_t(*Operand32)(uint8_t* Byte, int& CurrentIndex);
    Operand32 IntegerExtraction[5] = { DictDataExtract0, DictDataExtract1, DictDataExtract2, DictDataExtract3, DictDataExtract4};

    typedef void(*Operator32)(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intInde, uint8_t& floatInde, int& inde48, uint64_t& DataInde, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath);

    Operator32 OperatorExtraction[49] = {CharStringInsert0, CharStringInsert1, CharStringInsert2, CharStringInsert3, CharStringInsert4, CharStringInsert5, CharStringInsert6, CharStringInsert7, CharStringInsert8, CharStringInsert9, CharStringInsert10, CharStringInsert11, CharStringInsert12, CharStringInsert13, CharStringInsert14, CharStringInsert15, CharStringInsert16, CharStringInsert17, CharStringInsert18, CharStringInsert19, CharStringInsert20, CharStringInsert21, CharStringInsert22, CharStringInsert23, CharStringInsert24, CharStringInsert25, CharStringInsert26, CharStringInsert27, CharStringInsert28, CharStringInsert29, CharStringInsert30, CharStringInsert31, CharStringInsert32, CharStringInsert33, CharStringInsert34, CharStringInsert35, CharStringInsert36, CharStringInsert37, CharStringInsert38, CharStringInsert39, CharStringInsert40, CharStringInsert41, CharStringInsert42, CharStringInsert43, CharStringInsert44, CharStringInsert45, CharStringInsert46, CharStringInsert47, CharStringInsert48};

    float FloatBuffer[25];
    uint8_t FloatIndex = 0;
    int32_t IntegerBuffer[255];
    uint8_t IntegerIndex = 0;
    int OperatorIndex = 0;
    int OperandIndex = 0;

    uint64_t IndexMap = 0b0000000;
    uint8_t IndexLocation = 0; 

    PPCFFCharstring pc;

    Vectoid2 pen = {0,0};
    Vectoid2 OriginOfPath = {-69,-69};

    int CIDCurrentRange = 0;
    int SubroutineIndex = 0;
    bool CIDSpecificFont = (TopDictData.FDArray != 0);
    int SubroutineIndexSpecifier = (CIDSpecificFont)*(1*(FontSelect.format == 1) + 2*(FontSelect.format == 3));
    
    int CIDRangeIndex = 1;

    if(SubroutineIndexSpecifier == 2)
    {
        CIDCurrentRange = FontSelect.ranges[CIDRangeIndex].first;
        SubroutineIndex = FontSelect.ranges[CIDRangeIndex-1].fd;
    }
    
    int j = 0;
    for(int i = 0; i < size; i++)
    {

        if(SubroutineIndexSpecifier == 1)
        {
            SubroutineIndex = j;
        }else if(SubroutineIndexSpecifier == 2)
        {
            if(j >= CIDCurrentRange)
            {
                CIDRangeIndex++;
                CIDCurrentRange = FontSelect.ranges[CIDRangeIndex].first;
                SubroutineIndex = FontSelect.ranges[CIDRangeIndex-1].fd;
            }
        }

        OperatorIndex = 1 * (Data[i] == 0x01) + 2 * (Data[i] == 0x03) + 3 * (Data[i] == 0x04) + 4 * (Data[i] == 0x05) + 5 * (Data[i] == 0x06) + 6 * (Data[i] == 0x07) + 7 * (Data[i] == 0x08) + 8 * (Data[i] == 0x0a) + 9 * (Data[i] == 0x0b) + 10 * (Data[i] == 0x0c) + 11 * (Data[i] == 0x0e) + 12 * (Data[i] == 0x12) + 13 * (Data[i] == 0x13) + 14 * (Data[i] == 0x14) + 15 * (Data[i] == 0x15) + 16 * (Data[i] == 0x16) + 17 * (Data[i] == 0x17) + 18 * (Data[i] == 0x18) + 19 * (Data[i] == 0x19) + 20 * (Data[i] == 0x1a) + 21 * (Data[i] == 0x1b) + 22 * (Data[i] == 0x1c) + 23 * (Data[i] == 0x1d) + 24 * (Data[i] == 0x1e) + 25 * (Data[i] == 0x1f) + 26 * (Data[i] == 0x0c && Data[i+1] == 0x03) + 27 * (Data[i] == 0x0c && Data[i+1] == 0x04) + 28 * (Data[i] == 0x0c && Data[i+1] == 0x05) + 29 * (Data[i] == 0x0c && Data[i+1] == 0x09) + 30 * (Data[i] == 0x0c && Data[i+1] == 0x0a) + 31 * (Data[i] == 0x0c && Data[i+1] == 0x0b) + 32 * (Data[i] == 0x0c && Data[i+1] == 0x0c) + 33 * (Data[i] == 0x0c && Data[i+1] == 0x0e) + 34 * (Data[i] == 0x0c && Data[i+1] == 0x0f) + 35 * (Data[i] == 0x0c && Data[i+1] == 0x12) + 36 * (Data[i] == 0x0c && Data[i+1] == 0x14) + 37 * (Data[i] == 0x0c && Data[i+1] == 0x15) + 38 * (Data[i] == 0x0c && Data[i+1] == 0x16) + 39 * (Data[i] == 0x0c && Data[i+1] == 0x17) + 40 * (Data[i] == 0x0c && Data[i+1] == 0x18) + 41 * (Data[i] == 0x0c && Data[i+1] == 0x1a) + 42 * (Data[i] == 0x0c && Data[i+1] == 0x1b) + 43 * (Data[i] == 0x0c && Data[i+1] == 0x1c) + 44 * (Data[i] == 0x0c && Data[i+1] == 0x1d) + 45 * (Data[i] == 0x0c && Data[i+1] == 0x1e) + 46 * (Data[i] == 0x0c && Data[i+1] == 0x22) + 47 * (Data[i] == 0x0c && Data[i+1] == 0x23) + 48 * (Data[i] == 0x0c && Data[i+1] == 0x24) + 49 * (Data[i] == 0x0c && Data[i+1] == 0x25);

        if(OperatorIndex != 0)
        {
            
            if(Data[i] == 0xa)
            {

                if(LocalSubroutineIndex.Objects == nullptr)
                {

                }else
                {

                    if(CIDSpecificFont)
                    {

                    }else
                    {
                        uint32_t SubrNumber = IntegerBuffer[0]+LocalSubroutineBias;
                        if(SubrNumber < LocalSubroutineIndex.count)
                        {
                            IntegerIndex = 0;
                            FloatIndex = 0;
                            IndexMap = 0;
                            IndexLocation = 0;
                            CallLocalSubroutine(SubrNumber, pc, FloatBuffer,IntegerBuffer,IntegerIndex,FloatIndex, i, IndexMap, IndexLocation, pen, OriginOfPath);

                        }
                        


                    }

                }

            }else if(OperatorIndex == 23)
            {
                uint32_t SubrNumber = IntegerBuffer[0];
                if(SubrNumber < GlobalSubroutineIndex.count)
                {
                    CallGlobalSubroutine(IntegerBuffer[0], pc, FloatBuffer,IntegerBuffer,IntegerIndex,FloatIndex, i, IndexMap, IndexLocation, pen, OriginOfPath);
                }
                
            }

            OperatorExtraction[OperatorIndex](pc,FloatBuffer,IntegerBuffer,IntegerIndex,FloatIndex, i, IndexMap, IndexLocation, Data, pen, OriginOfPath);

            IndexLocation = 0;
            IndexMap = 0;
        }else
        {
            OperandIndex = (1*(Data[i] != 0x1C && Data[i] != 0x1D && Data[i] != 0x1E && Data[i] >= 32 && Data[i] <= 246)) + (2*(Data[i] != 0x1C && Data[i] != 0x1D && Data[i] != 0x1E && Data[i] >= 247 && Data[i] <= 250)) + (3*(Data[i] != 0x1C && Data[i] != 0x1D && Data[i] != 0x1E && Data[i] >= 251 && Data[i] <= 254)) + (4*(Data[i] == 0x1C)) + (5*(Data[i] == 0x1D)) + (6*(Data[i] == 0x1E));
            if(OperandIndex == 6)
            {
                FloatBuffer[FloatIndex] = DictRealExtract(Data, i);
                IndexMap |= (0b00000001 << IndexLocation);
                
                IndexLocation++; 
                FloatIndex++; 
            }
            else
            {
                IntegerBuffer[IntegerIndex] = IntegerExtraction[OperandIndex-1](Data, i);
                IndexMap &= ~(0b00000001 << IndexLocation);
                IndexLocation++; 
                IntegerIndex++;
            }
        }


    }

    return pc;



}
int PPCFFExtractor::CallLocalSubroutine(int SubrNumber, PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intInde, uint8_t& floatInde, int& inde48, uint64_t& DataInde, uint8_t& DataEntries, Vectoid2& pen, Vectoid2& OriginOfPath)
{
    typedef int32_t(*Operand32)(uint8_t* Byte, int& CurrentIndex);
    Operand32 IntegerExtraction[5] = { DictDataExtract0, DictDataExtract1, DictDataExtract2, DictDataExtract3, DictDataExtract4};

    typedef void(*Operator32)(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intInde, uint8_t& floatInde, int& inde48, uint64_t& DataInde, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath);

    Operator32 OperatorExtraction[49] = {CharStringInsert0, CharStringInsert1, CharStringInsert2, CharStringInsert3, CharStringInsert4, CharStringInsert5, CharStringInsert6, CharStringInsert7, CharStringInsert8, CharStringInsert9, CharStringInsert10, CharStringInsert11, CharStringInsert12, CharStringInsert13, CharStringInsert14, CharStringInsert15, CharStringInsert16, CharStringInsert17, CharStringInsert18, CharStringInsert19, CharStringInsert20, CharStringInsert21, CharStringInsert22, CharStringInsert23, CharStringInsert24, CharStringInsert25, CharStringInsert26, CharStringInsert27, CharStringInsert28, CharStringInsert29, CharStringInsert30, CharStringInsert31, CharStringInsert32, CharStringInsert33, CharStringInsert34, CharStringInsert35, CharStringInsert36, CharStringInsert37, CharStringInsert38, CharStringInsert39, CharStringInsert40, CharStringInsert41, CharStringInsert42, CharStringInsert43, CharStringInsert44, CharStringInsert45, CharStringInsert46, CharStringInsert47, CharStringInsert48};

    uint8_t* Subroutine = LocalSubroutineIndex.Objects[SubrNumber].data;
    int SubroutineSize = LocalSubroutineIndex.Objects[SubrNumber].size;

    DisplayHex(Subroutine,SubroutineSize);

    int OperatorIndex = 0;
    int OperandIndex = 0;

    for(int i = 0; i < SubroutineSize; i++)
    {
        OperatorIndex = 1 * (Subroutine[i] == 0x01) + 2 * (Subroutine[i] == 0x03) + 3 * (Subroutine[i] == 0x04) + 4 * (Subroutine[i] == 0x05) + 5 * (Subroutine[i] == 0x06) + 6 * (Subroutine[i] == 0x07) + 7 * (Subroutine[i] == 0x08) + 8 * (Subroutine[i] == 0x0a) + 9 * (Subroutine[i] == 0x0b) + 10 * (Subroutine[i] == 0x0c) + 11 * (Subroutine[i] == 0x0e) + 12 * (Subroutine[i] == 0x12) + 13 * (Subroutine[i] == 0x13) + 14 * (Subroutine[i] == 0x14) + 15 * (Subroutine[i] == 0x15) + 16 * (Subroutine[i] == 0x16) + 17 * (Subroutine[i] == 0x17) + 18 * (Subroutine[i] == 0x18) + 19 * (Subroutine[i] == 0x19) + 20 * (Subroutine[i] == 0x1a) + 21 * (Subroutine[i] == 0x1b) + 22 * (Subroutine[i] == 0x1c) + 23 * (Subroutine[i] == 0x1d) + 24 * (Subroutine[i] == 0x1e) + 25 * (Subroutine[i] == 0x1f) + 26 * (Subroutine[i] == 0x0c && Subroutine[i+1] == 0x03) + 27 * (Subroutine[i] == 0x0c && Subroutine[i+1] == 0x04) + 28 * (Subroutine[i] == 0x0c && Subroutine[i+1] == 0x05) + 29 * (Subroutine[i] == 0x0c && Subroutine[i+1] == 0x09) + 30 * (Subroutine[i] == 0x0c && Subroutine[i+1] == 0x0a) + 31 * (Subroutine[i] == 0x0c && Subroutine[i+1] == 0x0b) + 32 * (Subroutine[i] == 0x0c && Subroutine[i+1] == 0x0c) + 33 * (Subroutine[i] == 0x0c && Subroutine[i+1] == 0x0e) + 34 * (Subroutine[i] == 0x0c && Subroutine[i+1] == 0x0f) + 35 * (Subroutine[i] == 0x0c && Subroutine[i+1] == 0x12) + 36 * (Subroutine[i] == 0x0c && Subroutine[i+1] == 0x14) + 37 * (Subroutine[i] == 0x0c && Subroutine[i+1] == 0x15) + 38 * (Subroutine[i] == 0x0c && Subroutine[i+1] == 0x16) + 39 * (Subroutine[i] == 0x0c && Subroutine[i+1] == 0x17) + 40 * (Subroutine[i] == 0x0c && Subroutine[i+1] == 0x18) + 41 * (Subroutine[i] == 0x0c && Subroutine[i+1] == 0x1a) + 42 * (Subroutine[i] == 0x0c && Subroutine[i+1] == 0x1b) + 43 * (Subroutine[i] == 0x0c && Subroutine[i+1] == 0x1c) + 44 * (Subroutine[i] == 0x0c && Subroutine[i+1] == 0x1d) + 45 * (Subroutine[i] == 0x0c && Subroutine[i+1] == 0x1e) + 46 * (Subroutine[i] == 0x0c && Subroutine[i+1] == 0x22) + 47 * (Subroutine[i] == 0x0c && Subroutine[i+1] == 0x23) + 48 * (Subroutine[i] == 0x0c && Subroutine[i+1] == 0x24) + 49 * (Subroutine[i] == 0x0c && Subroutine[i+1] == 0x25);

        if(OperatorIndex != 0)
        {

            OperatorExtraction[OperatorIndex](CharData, floatStack, intStack, intInde, floatInde, inde48, DataInde, DataEntries, Subroutine, pen, OriginOfPath);

        }else
        {
            OperandIndex = (1*(Subroutine[i] != 0x1C && Subroutine[i] != 0x1D && Subroutine[i] != 0x1E && Subroutine[i] >= 32 && Subroutine[i] <= 246)) + (2*(Subroutine[i] != 0x1C && Subroutine[i] != 0x1D && Subroutine[i] != 0x1E && Subroutine[i] >= 247 && Subroutine[i] <= 250)) + (3*(Subroutine[i] != 0x1C && Subroutine[i] != 0x1D && Subroutine[i] != 0x1E && Subroutine[i] >= 251 && Subroutine[i] <= 254)) + (4*(Subroutine[i] == 0x1C)) + (5*(Subroutine[i] == 0x1D)) + (6*(Subroutine[i] == 0x1E));
            if(OperandIndex == 6)
            {
                floatStack[floatInde] = DictRealExtract(Subroutine, i);
                DataInde |= (0b00000001 << DataEntries);
                
                DataEntries++; 
                floatInde++; 
            }
            else
            {
                intStack[intInde] = IntegerExtraction[OperandIndex-1](Subroutine, i);
                DataInde &= ~(0b00000001 << DataEntries);
                DataEntries++; 
                intInde++;
            }
        }
            
    }

}
int PPCFFExtractor::CallGlobalSubroutine(int SubrNumber, PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intInde, uint8_t& floatInde, int& inde48, uint64_t& DataInde, uint8_t& DataEntries, Vectoid2& pen, Vectoid2& OriginOfPath)
{
    typedef int32_t(*Operand32)(uint8_t* Byte, int& CurrentIndex);
    Operand32 IntegerExtraction[5] = { DictDataExtract0, DictDataExtract1, DictDataExtract2, DictDataExtract3, DictDataExtract4};

    typedef void(*Operator32)(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intInde, uint8_t& floatInde, int& inde48, uint64_t& DataInde, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath);

    Operator32 OperatorExtraction[49] = {CharStringInsert0, CharStringInsert1, CharStringInsert2, CharStringInsert3, CharStringInsert4, CharStringInsert5, CharStringInsert6, CharStringInsert7, CharStringInsert8, CharStringInsert9, CharStringInsert10, CharStringInsert11, CharStringInsert12, CharStringInsert13, CharStringInsert14, CharStringInsert15, CharStringInsert16, CharStringInsert17, CharStringInsert18, CharStringInsert19, CharStringInsert20, CharStringInsert21, CharStringInsert22, CharStringInsert23, CharStringInsert24, CharStringInsert25, CharStringInsert26, CharStringInsert27, CharStringInsert28, CharStringInsert29, CharStringInsert30, CharStringInsert31, CharStringInsert32, CharStringInsert33, CharStringInsert34, CharStringInsert35, CharStringInsert36, CharStringInsert37, CharStringInsert38, CharStringInsert39, CharStringInsert40, CharStringInsert41, CharStringInsert42, CharStringInsert43, CharStringInsert44, CharStringInsert45, CharStringInsert46, CharStringInsert47, CharStringInsert48};


    uint8_t* Subroutine = GlobalSubroutineIndex.Objects[SubrNumber].data;;
    
    int SubroutineSize = GlobalSubroutineIndex.Objects[SubrNumber].size;

    DisplayHex(Subroutine,SubroutineSize);

    int OperatorIndex = 0;
    int OperandIndex = 0;


    //OriginOfPath = {-69,-69};

    for(int i = 0; i < SubroutineSize; i++)
    {
        OperatorIndex = 1 * (Subroutine[i] == 0x01) + 2 * (Subroutine[i] == 0x03) + 3 * (Subroutine[i] == 0x04) + 4 * (Subroutine[i] == 0x05) + 5 * (Subroutine[i] == 0x06) + 6 * (Subroutine[i] == 0x07) + 7 * (Subroutine[i] == 0x08) + 8 * (Subroutine[i] == 0x0a) + 9 * (Subroutine[i] == 0x0b) + 10 * (Subroutine[i] == 0x0c) + 11 * (Subroutine[i] == 0x0e) + 12 * (Subroutine[i] == 0x12) + 13 * (Subroutine[i] == 0x13) + 14 * (Subroutine[i] == 0x14) + 15 * (Subroutine[i] == 0x15) + 16 * (Subroutine[i] == 0x16) + 17 * (Subroutine[i] == 0x17) + 18 * (Subroutine[i] == 0x18) + 19 * (Subroutine[i] == 0x19) + 20 * (Subroutine[i] == 0x1a) + 21 * (Subroutine[i] == 0x1b) + 22 * (Subroutine[i] == 0x1c) + 23 * (Subroutine[i] == 0x1d) + 24 * (Subroutine[i] == 0x1e) + 25 * (Subroutine[i] == 0x1f) + 26 * (Subroutine[i] == 0x0c && Subroutine[i+1] == 0x03) + 27 * (Subroutine[i] == 0x0c && Subroutine[i+1] == 0x04) + 28 * (Subroutine[i] == 0x0c && Subroutine[i+1] == 0x05) + 29 * (Subroutine[i] == 0x0c && Subroutine[i+1] == 0x09) + 30 * (Subroutine[i] == 0x0c && Subroutine[i+1] == 0x0a) + 31 * (Subroutine[i] == 0x0c && Subroutine[i+1] == 0x0b) + 32 * (Subroutine[i] == 0x0c && Subroutine[i+1] == 0x0c) + 33 * (Subroutine[i] == 0x0c && Subroutine[i+1] == 0x0e) + 34 * (Subroutine[i] == 0x0c && Subroutine[i+1] == 0x0f) + 35 * (Subroutine[i] == 0x0c && Subroutine[i+1] == 0x12) + 36 * (Subroutine[i] == 0x0c && Subroutine[i+1] == 0x14) + 37 * (Subroutine[i] == 0x0c && Subroutine[i+1] == 0x15) + 38 * (Subroutine[i] == 0x0c && Subroutine[i+1] == 0x16) + 39 * (Subroutine[i] == 0x0c && Subroutine[i+1] == 0x17) + 40 * (Subroutine[i] == 0x0c && Subroutine[i+1] == 0x18) + 41 * (Subroutine[i] == 0x0c && Subroutine[i+1] == 0x1a) + 42 * (Subroutine[i] == 0x0c && Subroutine[i+1] == 0x1b) + 43 * (Subroutine[i] == 0x0c && Subroutine[i+1] == 0x1c) + 44 * (Subroutine[i] == 0x0c && Subroutine[i+1] == 0x1d) + 45 * (Subroutine[i] == 0x0c && Subroutine[i+1] == 0x1e) + 46 * (Subroutine[i] == 0x0c && Subroutine[i+1] == 0x22) + 47 * (Subroutine[i] == 0x0c && Subroutine[i+1] == 0x23) + 48 * (Subroutine[i] == 0x0c && Subroutine[i+1] == 0x24) + 49 * (Subroutine[i] == 0x0c && Subroutine[i+1] == 0x25);

        if(OperatorIndex != 0)
        {

            OperatorExtraction[OperatorIndex](CharData, floatStack, intStack, intInde, floatInde, inde48, DataInde, DataEntries, Subroutine, pen, OriginOfPath);

        }else
        {
            OperandIndex = (1*(Subroutine[i] != 0x1C && Subroutine[i] != 0x1D && Subroutine[i] != 0x1E && Subroutine[i] >= 32 && Subroutine[i] <= 246)) + (2*(Subroutine[i] != 0x1C && Subroutine[i] != 0x1D && Subroutine[i] != 0x1E && Subroutine[i] >= 247 && Subroutine[i] <= 250)) + (3*(Subroutine[i] != 0x1C && Subroutine[i] != 0x1D && Subroutine[i] != 0x1E && Subroutine[i] >= 251 && Subroutine[i] <= 254)) + (4*(Subroutine[i] == 0x1C)) + (5*(Subroutine[i] == 0x1D)) + (6*(Subroutine[i] == 0x1E));
            if(OperandIndex == 6)
            {
                floatStack[floatInde] = DictRealExtract(Subroutine, i);
                DataInde |= (0b00000001 << DataEntries);
                
                DataEntries++; 
                floatInde++; 
            }
            else
            {
                intStack[intInde] = IntegerExtraction[OperandIndex-1](Subroutine, i);
                DataInde &= ~(0b00000001 << DataEntries);
                DataEntries++; 
                intInde++;
            }
        }
            
    }

}


int PPCFFExtractor::DecodePrivateDict()
{
    FILE* SubroutineExtraction = NULL;
    errno_t SubroutineError = fopen_s(&SubroutineExtraction, FontPath, "rb");
    int FileStart = CFFTable.offset + TopDictData.Private[1];
    PrivateDictData.DataStart = FileStart;
    int PrivateDictSize = TopDictData.Private[0];
    PPCFFIndex index;

    int seekSee = fseek(SubroutineExtraction, FileStart, SEEK_SET); if(seekSee != 0){ fclose(SubroutineExtraction); return 0; }
    // FillArbitraryIndex(SubroutineExtraction,index,FileStart);
     uint8_t* data = (uint8_t*)malloc(PrivateDictSize);
    fread(data, sizeof(uint8_t), PrivateDictSize, SubroutineExtraction);

    fclose(SubroutineExtraction);

    DisplayHex(data, PrivateDictSize);

    typedef int32_t(*Operand32)(uint8_t* Byte, int& CurrentIndex);
    Operand32 IntegerExtraction[5] = { DictDataExtract0, DictDataExtract1, DictDataExtract2, DictDataExtract3, DictDataExtract4};

    // typedef void(*Operator32)(PPCFFPrivateData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
    void(*OperatorExtraction[18])(PPCFFPrivateData&, float*, int32_t*, uint8_t&, uint8_t&, int&, uint64_t&, uint8_t&) = {PrivateOperatorExtraction0, PrivateOperatorExtraction1, PrivateOperatorExtraction2, PrivateOperatorExtraction3, PrivateOperatorExtraction4, PrivateOperatorExtraction5, PrivateOperatorExtraction6, PrivateOperatorExtraction7, PrivateOperatorExtraction8, PrivateOperatorExtraction9, PrivateOperatorExtraction10, PrivateOperatorExtraction11, PrivateOperatorExtraction12, PrivateOperatorExtraction13, PrivateOperatorExtraction14, PrivateOperatorExtraction15, PrivateOperatorExtraction16, PrivateOperatorExtraction17};


    float FloatBuffer[5];
    uint8_t FloatIndex = 0;
    int32_t IntegerBuffer[25];
    uint8_t IntegerIndex = 0;
    int OperatorIndex = 0;
    int OperandIndex = 0;

    uint64_t IndexMap = 0b0000000;
    uint8_t IndexLocation = 0; 

    for(int i = 0; i < PrivateDictSize; i++)
    {
        int OperatorIndex = (1*(data[i] == 6)) + (2*(data[i] == 7)) + (3*(data[i] == 8)) + (4*(data[i] == 9)) + (5*(data[i] == 0xc && data[i+1] == 9)) + (6*(data[i] == 0xc && data[i+1] == 10)) + (7*(data[i] == 0xc && data[i+1] == 11)) + (8*(data[i] == 10)) + (9*(data[i] == 11)) + (10*(data[i] == 0xc && data[i+1] == 12)) + (11*(data[i] == 0xc && data[i+1] == 13)) + (12*(data[i] == 0xc && data[i+1] == 14)) + (13*(data[i] == 0xc && data[i+1] == 17)) + (14*(data[i] == 0xc && data[i+1] == 18)) + (15*(data[i] == 0xc && data[i+1] == 19)) + (16*(data[i] == 19)) + (17*(data[i] == 20)) + (18*(data[i] == 21));
        
        if(OperatorIndex != 0)
        {
            if(data[i] == 19)
            {
                int i = 0;
            }
            OperatorExtraction[OperatorIndex-1](PrivateDictData, FloatBuffer, IntegerBuffer, IntegerIndex, FloatIndex, i, IndexMap, IndexLocation);
            if(data[i] == 0xc)
            {
                i++;
            }

            
            
            IndexLocation = 0;
            IndexMap = 0;
        }
        else //Gather the operand index condition and extract based on this.
        {
            OperandIndex = (1*(data[i] != 0x1C && data[i] != 0x1D && data[i] != 0x1E && data[i] >= 32 && data[i] <= 246)) + (2*(data[i] != 0x1C && data[i] != 0x1D && data[i] != 0x1E && data[i] >= 247 && data[i] <= 250)) + (3*(data[i] != 0x1C && data[i] != 0x1D && data[i] != 0x1E && data[i] >= 251 && data[i] <= 254)) + (4*(data[i] == 0x1C)) + (5*(data[i] == 0x1D)) + (6*(data[i] == 0x1E));
            if(OperandIndex == 6)
            {
                FloatBuffer[FloatIndex] = DictRealExtract(data, i);
                IndexMap |= (0b00000001 << IndexLocation);
                
                IndexLocation++; 
                FloatIndex++; 
            }
            else
            {
                IntegerBuffer[IntegerIndex] = IntegerExtraction[OperandIndex-1](data, i);
                IndexMap &= ~(0b00000001 << IndexLocation);
                //printf("Index Map: 0x%x\n", IndexMap);
                IndexLocation++; 
                IntegerIndex++;
            }
        }
    }
}
int PPCFFExtractor::ExtractSubrsPrivate()
{
    
    int Offset = PrivateDictData.DataStart + PrivateDictData.Subrs;
    
    FILE* F = NULL;
    errno_t er = fopen_s(&F, FontPath, "rb"); if(F == NULL || er != 0) { return -1; }
    int seekSeek = fseek(F, Offset, SEEK_SET);


    LocalSubroutineIndex.count = ReadST(F);

    LocalSubroutineBias = (107)*(LocalSubroutineIndex.count < 1240) + (1131)*(LocalSubroutineIndex.count < 33900)*!(LocalSubroutineIndex.count < 1240) + (32768)*!(LocalSubroutineIndex.count < 1240)*!(LocalSubroutineIndex.count < 1240);

    LocalSubroutineIndex.offSize = ReadE(F);

    int TypeIndex = LocalSubroutineIndex.offSize-1;

    LocalSubroutineIndex.Offsets = (uint32_t*)malloc(sizeof(uint32_t) * (LocalSubroutineIndex.count + 1));

    LocalSubroutineIndex.Objects = (PPCFFObjectEntry*)malloc(sizeof(PPCFFObjectEntry)*LocalSubroutineIndex.count);
    
    if(LocalSubroutineIndex.Offsets == nullptr || LocalSubroutineIndex.Objects == nullptr)
    {
        return 0;
    }
    
    typedef void (*ValueExtraction)(FILE*, uint32_t*, uint16_t);
    ValueExtraction ValueFunctions[4] =
    {
        ExtractOffsets8, ExtractOffsets16, ExtractOffsets24, ExtractOffsets32
    };
    ValueFunctions[TypeIndex](F, LocalSubroutineIndex.Offsets, LocalSubroutineIndex.count);



    for(int i = 0; i < LocalSubroutineIndex.count; i++)
    {
        LocalSubroutineIndex.Objects[i].size = LocalSubroutineIndex.Offsets[i+1]-LocalSubroutineIndex.Offsets[i];
        LocalSubroutineIndex.Objects[i].data = (uint8_t*)malloc(LocalSubroutineIndex.Objects[i].size);
        fread(LocalSubroutineIndex.Objects[i].data, sizeof(uint8_t), LocalSubroutineIndex.Objects[i].size, F);
    }


    fclose(F);


}
int PPCFFExtractor::ExtractSubroutines()
{
    FILE* SubroutineExtraction = NULL;
    errno_t SubroutineError = fopen_s(&SubroutineExtraction, FontPath, "rb");


    if(GlobalSubroutineIndex.Objects == nullptr)
    {
        if(StringIndex.EndOfTable == 0) ExtractStringIndex();
        ExtractGlobalSubroutineIndex();
    }

    if(TopDictData.FDArray == 0)
    {
        ExtractSubrsPrivate();
    }else{
        

        ExtractFontDictIndex();
        DecodeFontDictData();
        ExtractFontFontDictSelect();


        int Format = FontSelect.format;
        if(Format == 3)
        {
            LocalSubroutineIndex.Objects = (PPCFFObjectEntry*)malloc(sizeof(PPCFFObjectEntry)*FontSelect.nRanges);
            for(int i = 0; i < FontSelect.nRanges; i++)
            {
                Range3 CurrentRange = FontSelect.ranges[i];
                int FID = CurrentRange.fd;
                int DictionaryOffset = FontDictData.Dicts[FID].PrivateDictOffset;
                fseek(SubroutineExtraction,CFFTable.offset+DictionaryOffset,SEEK_SET);
                LocalSubroutineIndex.Objects[i].size = FontDictData.Dicts[FID].PrivateDictSize;
                
                LocalSubroutineIndex.Objects[i].data = (uint8_t*)malloc(LocalSubroutineIndex.Objects[i].size);

                fread(LocalSubroutineIndex.Objects[i].data, sizeof(uint8_t), LocalSubroutineIndex.Objects[i].size, SubroutineExtraction);
            }
        }else
        {



        }

    }
}

int PPCFFExtractor::DecodeSingularCIDFormat3Charstring()
{

    uint8_t* Data = CharStringsIndex.Objects[2].data;
    int size = CharStringsIndex.Offsets[3]-CharStringsIndex.Offsets[2];
    printf("\n");
    DisplayHex(Data, size);

    typedef int32_t(*Operand32)(uint8_t* Byte, int& CurrentIndex);
    Operand32 IntegerExtraction[5] = { DictDataExtract0, DictDataExtract1, DictDataExtract2, DictDataExtract3, DictDataExtract4};

    typedef void(*Operator32)(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intInde, uint8_t& floatInde, int& inde48, uint64_t& DataInde, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath);

    Operator32 OperatorExtraction[49] = {CharStringInsert0, CharStringInsert1, CharStringInsert2, CharStringInsert3, CharStringInsert4, CharStringInsert5, CharStringInsert6, CharStringInsert7, CharStringInsert8, CharStringInsert9, CharStringInsert10, CharStringInsert11, CharStringInsert12, CharStringInsert13, CharStringInsert14, CharStringInsert15, CharStringInsert16, CharStringInsert17, CharStringInsert18, CharStringInsert19, CharStringInsert20, CharStringInsert21, CharStringInsert22, CharStringInsert23, CharStringInsert24, CharStringInsert25, CharStringInsert26, CharStringInsert27, CharStringInsert28, CharStringInsert29, CharStringInsert30, CharStringInsert31, CharStringInsert32, CharStringInsert33, CharStringInsert34, CharStringInsert35, CharStringInsert36, CharStringInsert37, CharStringInsert38, CharStringInsert39, CharStringInsert40, CharStringInsert41, CharStringInsert42, CharStringInsert43, CharStringInsert44, CharStringInsert45, CharStringInsert46, CharStringInsert47, CharStringInsert48};


    float FloatBuffer[25];
    uint8_t FloatIndex = 0;
    int32_t IntegerBuffer[25];
    uint8_t IntegerIndex = 0;
    int OperatorIndex = 0;
    int OperandIndex = 0;

    uint64_t IndexMap = 0b0000000;
    uint8_t IndexLocation = 0; 

    PPCFFCharstring pc;

    Vectoid2 pen = {0,0};

    
    bool CIDSpecificFont = (TopDictData.FDArray != 0);
    int SubroutineIndexSpecifier = (CIDSpecificFont)*(1*(FontSelect.format == 1) + 2*(FontSelect.format == 3));

    int CIDRangeIndex = 1;
    int CIDCurrentRange = FontSelect.ranges[CIDRangeIndex].first;

    int SubroutineIndex = FontSelect.ranges[CIDRangeIndex-1].fd;

    Vectoid2 OriginOfPath = {-69,-69};

    for(int j = 0; j < 1; j++)
    {

        if(SubroutineIndexSpecifier == 0)
        {
            //use some charset 
        }else if(SubroutineIndexSpecifier == 1)
        {
            SubroutineIndex = j;
        }else if(SubroutineIndexSpecifier == 2)
        {
            if(j >= CIDCurrentRange)
            {
                CIDRangeIndex++;
                CIDCurrentRange = FontSelect.ranges[CIDRangeIndex].first;
                SubroutineIndex = FontSelect.ranges[CIDRangeIndex-1].fd;
            }
        }
        

        for(int i = 0; i < size; i++)
        {

            OperatorIndex = 1 * (Data[i] == 0x01) + 2 * (Data[i] == 0x03) + 3 * (Data[i] == 0x04) + 4 * (Data[i] == 0x05) + 5 * (Data[i] == 0x06) + 6 * (Data[i] == 0x07) + 7 * (Data[i] == 0x08) + 8 * (Data[i] == 0x0a) + 9 * (Data[i] == 0x0b) + 10 * (Data[i] == 0x0c) + 11 * (Data[i] == 0x0e) + 12 * (Data[i] == 0x12) + 13 * (Data[i] == 0x13) + 14 * (Data[i] == 0x14) + 15 * (Data[i] == 0x15) + 16 * (Data[i] == 0x16) + 17 * (Data[i] == 0x17) + 18 * (Data[i] == 0x18) + 19 * (Data[i] == 0x19) + 20 * (Data[i] == 0x1a) + 21 * (Data[i] == 0x1b) + 22 * (Data[i] == 0x1c) + 23 * (Data[i] == 0x1d) + 24 * (Data[i] == 0x1e) + 25 * (Data[i] == 0x1f) + 26 * (Data[i] == 0x0c && Data[i+1] == 0x03) + 27 * (Data[i] == 0x0c && Data[i+1] == 0x04) + 28 * (Data[i] == 0x0c && Data[i+1] == 0x05) + 29 * (Data[i] == 0x0c && Data[i+1] == 0x09) + 30 * (Data[i] == 0x0c && Data[i+1] == 0x0a) + 31 * (Data[i] == 0x0c && Data[i+1] == 0x0b) + 32 * (Data[i] == 0x0c && Data[i+1] == 0x0c) + 33 * (Data[i] == 0x0c && Data[i+1] == 0x0e) + 34 * (Data[i] == 0x0c && Data[i+1] == 0x0f) + 35 * (Data[i] == 0x0c && Data[i+1] == 0x12) + 36 * (Data[i] == 0x0c && Data[i+1] == 0x14) + 37 * (Data[i] == 0x0c && Data[i+1] == 0x15) + 38 * (Data[i] == 0x0c && Data[i+1] == 0x16) + 39 * (Data[i] == 0x0c && Data[i+1] == 0x17) + 40 * (Data[i] == 0x0c && Data[i+1] == 0x18) + 41 * (Data[i] == 0x0c && Data[i+1] == 0x1a) + 42 * (Data[i] == 0x0c && Data[i+1] == 0x1b) + 43 * (Data[i] == 0x0c && Data[i+1] == 0x1c) + 44 * (Data[i] == 0x0c && Data[i+1] == 0x1d) + 45 * (Data[i] == 0x0c && Data[i+1] == 0x1e) + 46 * (Data[i] == 0x0c && Data[i+1] == 0x22) + 47 * (Data[i] == 0x0c && Data[i+1] == 0x23) + 48 * (Data[i] == 0x0c && Data[i+1] == 0x24) + 49 * (Data[i] == 0x0c && Data[i+1] == 0x25);

            if(OperatorIndex != 0)
            {
                
                if(OperatorIndex == 8)
                {
                    CallLocalSubroutine(SubroutineIndex, pc, FloatBuffer,IntegerBuffer,IntegerIndex,FloatIndex, i, IndexMap, IndexLocation, pen, OriginOfPath);
                }
                OperatorExtraction[OperatorIndex](pc,FloatBuffer,IntegerBuffer,IntegerIndex,FloatIndex, i, IndexMap, IndexLocation, Data, pen,OriginOfPath);

                
                IndexLocation = 0;
                IndexMap = 0;
            }else
            {
                OperandIndex = (1*(Data[i] != 0x1C && Data[i] != 0x1D && Data[i] != 0x1E && Data[i] >= 32 && Data[i] <= 246)) + (2*(Data[i] != 0x1C && Data[i] != 0x1D && Data[i] != 0x1E && Data[i] >= 247 && Data[i] <= 250)) + (3*(Data[i] != 0x1C && Data[i] != 0x1D && Data[i] != 0x1E && Data[i] >= 251 && Data[i] <= 254)) + (4*(Data[i] == 0x1C)) + (5*(Data[i] == 0x1D)) + (6*(Data[i] == 0x1E));
                if(OperandIndex == 6)
                {
                    FloatBuffer[FloatIndex] = DictRealExtract(Data, i);
                    IndexMap |= (0b00000001 << IndexLocation);
                    
                    IndexLocation++; 
                    FloatIndex++; 
                }
                else
                {
                    IntegerBuffer[IntegerIndex] = IntegerExtraction[OperandIndex-1](Data, i);
                    IndexMap &= ~(0b00000001 << IndexLocation);
                    IndexLocation++; 
                    IntegerIndex++;
                }
            }


        }
    }

    
}
int PPCFFExtractor::DecodeCharstrings()
{
    

    typedef int32_t(*Operand32)(uint8_t* Byte, int& CurrentIndex);
    Operand32 IntegerExtraction[5] = { DictDataExtract0, DictDataExtract1, DictDataExtract2, DictDataExtract3, DictDataExtract4};

    typedef void(*Operator32)(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intInde, uint8_t& floatInde, int& inde48, uint64_t& DataInde, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath);

    Operator32 OperatorExtraction[49] = {CharStringInsert0, CharStringInsert1, CharStringInsert2, CharStringInsert3, CharStringInsert4, CharStringInsert5, CharStringInsert6, CharStringInsert7, CharStringInsert8, CharStringInsert9, CharStringInsert10, CharStringInsert11, CharStringInsert12, CharStringInsert13, CharStringInsert14, CharStringInsert15, CharStringInsert16, CharStringInsert17, CharStringInsert18, CharStringInsert19, CharStringInsert20, CharStringInsert21, CharStringInsert22, CharStringInsert23, CharStringInsert24, CharStringInsert25, CharStringInsert26, CharStringInsert27, CharStringInsert28, CharStringInsert29, CharStringInsert30, CharStringInsert31, CharStringInsert32, CharStringInsert33, CharStringInsert34, CharStringInsert35, CharStringInsert36, CharStringInsert37, CharStringInsert38, CharStringInsert39, CharStringInsert40, CharStringInsert41, CharStringInsert42, CharStringInsert43, CharStringInsert44, CharStringInsert45, CharStringInsert46, CharStringInsert47, CharStringInsert48};


    float FloatBuffer[25];
    uint8_t FloatIndex = 0;
    int32_t IntegerBuffer[25];
    uint8_t IntegerIndex = 0;
    int OperatorIndex = 0;
    int OperandIndex = 0;

    uint64_t IndexMap = 0b0000000;
    uint8_t IndexLocation = 0; 

    

    Vectoid2 pen = {0,0};

    
    bool CIDSpecificFont = (TopDictData.FDArray != 0);
    int SubroutineIndexSpecifier = (CIDSpecificFont)*(1*(FontSelect.format == 1) + 2*(FontSelect.format == 3));

    int CIDRangeIndex = 1;
    int CIDCurrentRange = FontSelect.ranges[CIDRangeIndex].first;

    int SubroutineIndex = FontSelect.ranges[CIDRangeIndex-1].fd;

    Vectoid2 OriginOfPath = {-69,-69};

    uint8_t* Data = nullptr;
    int size = 0;
    printf("\n");
    DisplayHex(Data, size);

    for(int j = 0; j < CharStringsIndex.count; j++)
    {
        PPCFFCharstring pc;
        
        Data = CharStringsIndex.Objects[j].data;
        size = CharStringsIndex.Offsets[j+1]-CharStringsIndex.Offsets[j];

        if(SubroutineIndexSpecifier == 0)
        {
            //use some charset 
        }else if(SubroutineIndexSpecifier == 1)
        {
            SubroutineIndex = j;
        }else if(SubroutineIndexSpecifier == 2)
        {
            if(j >= CIDCurrentRange)
            {
                CIDRangeIndex++;
                CIDCurrentRange = FontSelect.ranges[CIDRangeIndex].first;
                SubroutineIndex = FontSelect.ranges[CIDRangeIndex-1].fd;
            }
        }
        

        for(int i = 0; i < size; i++)
        {

            OperatorIndex = 1 * (Data[i] == 0x01) + 2 * (Data[i] == 0x03) + 3 * (Data[i] == 0x04) + 4 * (Data[i] == 0x05) + 5 * (Data[i] == 0x06) + 6 * (Data[i] == 0x07) + 7 * (Data[i] == 0x08) + 8 * (Data[i] == 0x0a) + 9 * (Data[i] == 0x0b) + 10 * (Data[i] == 0x0c) + 11 * (Data[i] == 0x0e) + 12 * (Data[i] == 0x12) + 13 * (Data[i] == 0x13) + 14 * (Data[i] == 0x14) + 15 * (Data[i] == 0x15) + 16 * (Data[i] == 0x16) + 17 * (Data[i] == 0x17) + 18 * (Data[i] == 0x18) + 19 * (Data[i] == 0x19) + 20 * (Data[i] == 0x1a) + 21 * (Data[i] == 0x1b) + 22 * (Data[i] == 0x1c) + 23 * (Data[i] == 0x1d) + 24 * (Data[i] == 0x1e) + 25 * (Data[i] == 0x1f) + 26 * (Data[i] == 0x0c && Data[i+1] == 0x03) + 27 * (Data[i] == 0x0c && Data[i+1] == 0x04) + 28 * (Data[i] == 0x0c && Data[i+1] == 0x05) + 29 * (Data[i] == 0x0c && Data[i+1] == 0x09) + 30 * (Data[i] == 0x0c && Data[i+1] == 0x0a) + 31 * (Data[i] == 0x0c && Data[i+1] == 0x0b) + 32 * (Data[i] == 0x0c && Data[i+1] == 0x0c) + 33 * (Data[i] == 0x0c && Data[i+1] == 0x0e) + 34 * (Data[i] == 0x0c && Data[i+1] == 0x0f) + 35 * (Data[i] == 0x0c && Data[i+1] == 0x12) + 36 * (Data[i] == 0x0c && Data[i+1] == 0x14) + 37 * (Data[i] == 0x0c && Data[i+1] == 0x15) + 38 * (Data[i] == 0x0c && Data[i+1] == 0x16) + 39 * (Data[i] == 0x0c && Data[i+1] == 0x17) + 40 * (Data[i] == 0x0c && Data[i+1] == 0x18) + 41 * (Data[i] == 0x0c && Data[i+1] == 0x1a) + 42 * (Data[i] == 0x0c && Data[i+1] == 0x1b) + 43 * (Data[i] == 0x0c && Data[i+1] == 0x1c) + 44 * (Data[i] == 0x0c && Data[i+1] == 0x1d) + 45 * (Data[i] == 0x0c && Data[i+1] == 0x1e) + 46 * (Data[i] == 0x0c && Data[i+1] == 0x22) + 47 * (Data[i] == 0x0c && Data[i+1] == 0x23) + 48 * (Data[i] == 0x0c && Data[i+1] == 0x24) + 49 * (Data[i] == 0x0c && Data[i+1] == 0x25);

            if(OperatorIndex != 0)
            {
                
                if(OperatorIndex == 8)
                {
                    CallLocalSubroutine(SubroutineIndex, pc, FloatBuffer,IntegerBuffer,IntegerIndex,FloatIndex, i, IndexMap, IndexLocation, pen, OriginOfPath);
                }
                else if(OperatorIndex == 23)
                {
                    CallGlobalSubroutine(SubroutineIndex, pc, FloatBuffer,IntegerBuffer,IntegerIndex,FloatIndex, i, IndexMap, IndexLocation, pen, OriginOfPath);
                }
                OperatorExtraction[OperatorIndex](pc,FloatBuffer,IntegerBuffer,IntegerIndex,FloatIndex, i, IndexMap, IndexLocation, Data, pen,OriginOfPath);

                
                IndexLocation = 0;
                IndexMap = 0;
            }else
            {
                OperandIndex = (1*(Data[i] != 0x1C && Data[i] != 0x1D && Data[i] != 0x1E && Data[i] >= 32 && Data[i] <= 246)) + (2*(Data[i] != 0x1C && Data[i] != 0x1D && Data[i] != 0x1E && Data[i] >= 247 && Data[i] <= 250)) + (3*(Data[i] != 0x1C && Data[i] != 0x1D && Data[i] != 0x1E && Data[i] >= 251 && Data[i] <= 254)) + (4*(Data[i] == 0x1C)) + (5*(Data[i] == 0x1D)) + (6*(Data[i] == 0x1E));
                if(OperandIndex == 6)
                {
                    FloatBuffer[FloatIndex] = DictRealExtract(Data, i);
                    IndexMap |= (0b00000001 << IndexLocation);
                    
                    IndexLocation++; 
                    FloatIndex++; 
                }
                else
                {
                    IntegerBuffer[IntegerIndex] = IntegerExtraction[OperandIndex-1](Data, i);
                    IndexMap &= ~(0b00000001 << IndexLocation);
                    IndexLocation++; 
                    IntegerIndex++;
                }
            }


        }

        CharstringGeometry.push_back(pc);
    }
    
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
int PPCFFExtractor::ExtractFontDictIndex()
{
    if(TopDictData.FDArray == 0)
    {
        return -1;
    }
    FILE* FontDictExtract = NULL;
    
    errno_t fErr = fopen_s(&FontDictExtract, FontPath, "rb");
    if(FontDictExtract == NULL || fErr != 0)
    {
        return 0;
    }
    int seekSee = fseek(FontDictExtract, TopDictData.FDArray + CFFTable.offset, SEEK_SET); if(seekSee != 0){ fclose(FontDictExtract); return 0; }
    FillArbitraryIndex(FontDictExtract, FontDictIndex, TopDictData.FDArray + CFFTable.offset);
    fclose(FontDictExtract);

}
int PPCFFExtractor::DecodeFontDictData()
{

    if(TopDictData.FDArray == 0)
    {
        return -1;
    }
    typedef int32_t(*Operand32)(uint8_t* Byte, int& CurrentIndex);
    Operand32 IntegerExtraction[5] = { DictDataExtract0, DictDataExtract1, DictDataExtract2, DictDataExtract3, DictDataExtract4};

    float FloatBuffer[5];
    uint8_t FloatIndex = 0;
    int32_t IntegerBuffer[5];
    uint8_t IntegerIndex = 0;
    int OperatorIndex = 0;
    int OperandIndex = 0;

    uint64_t IndexMap = 0b0000000;
    uint8_t IndexLocation = 0; 

    int size = 0;
    uint8_t* Data = nullptr;
    PPCFFFontDict dict;
    for(int i = 0; i < FontDictIndex.count; i++)
    {

        Data = FontDictIndex.Objects[i].data;
        size = FontDictIndex.Objects[i].size;

        for(int j = 0; j < size; j++)
        {
            OperatorIndex = 1 * (Data[j] == 0xc) + 2 *(Data[j] == 0x12);

            if(OperatorIndex != 0)
            {

                if(OperatorIndex == 1)
                {
                    dict.FontNameSID = IntegerBuffer[0];

                    OperandIndex = 0;
                    OperatorIndex = 0;
                    IntegerIndex = 0;
                    FloatIndex = 0;
                    j++;

                }else if(OperatorIndex == 2)
                {
                    dict.PrivateDictSize = IntegerBuffer[0];
                    dict.PrivateDictOffset = IntegerBuffer[1];

                    OperandIndex = 0;
                    OperatorIndex = 0;
                    IntegerIndex = 0;
                    FloatIndex = 0;


                }

                IndexLocation = 0;
                IndexMap = 0;


            }else
            {
                OperandIndex = (1*(Data[j] != 0x1C && Data[j] != 0x1D && Data[j] != 0x1E && Data[j] >= 32 && Data[j] <= 246)) + (2*(Data[j] != 0x1C && Data[j] != 0x1D && Data[j] != 0x1E && Data[j] >= 247 && Data[j] <= 250)) + (3*(Data[j] != 0x1C && Data[j] != 0x1D && Data[j] != 0x1E && Data[j] >= 251 && Data[j] <= 254)) + (4*(Data[j] == 0x1C)) + (5*(Data[j] == 0x1D)) + (6*(Data[j] == 0x1E));

                if(OperandIndex == 6)
                {
                    FloatBuffer[FloatIndex] = DictRealExtract(Data, j);
                    IndexMap |= (0b00000001 << IndexLocation);
                    
                    IndexLocation++; 
                    FloatIndex++; 
                }
                else
                {
                    IntegerBuffer[IntegerIndex] = IntegerExtraction[OperandIndex-1](Data, j);
                    IndexMap &= ~(0b00000001 << IndexLocation);
                    IndexLocation++; 
                    IntegerIndex++;
                }
            }
            

        }

        FontDictData.Dicts.push_back(dict);
    }
}
int PPCFFExtractor::ExtractFontFontDictSelect()
{
    FILE* FontDictSelectExtract = NULL;

    errno_t Open = fopen_s(&FontDictSelectExtract, FontPath, "rb");
    if(FontDictSelectExtract == NULL || Open != 0)
    {
        return 0;
    }
    int seekSee = fseek(FontDictSelectExtract, TopDictData.FDSelect + CFFTable.offset, SEEK_SET); if(seekSee != 0){ fclose(FontDictSelectExtract); return 0; }
    FontSelect.format = ReadE(FontDictSelectExtract);

    if(FontSelect.format == 0)
    {

    }else if(FontSelect.format == 3)
    {
        FontSelect.nRanges = ReadST(FontDictSelectExtract);
        FontSelect.ranges = (Range3*)malloc(sizeof(Range3)*FontSelect.nRanges);

        //fread((void*)FontSelect.ranges, sizeof(Range3), FontSelect.nRanges, FontDictSelectExtract);

        for(int i = 0; i < FontSelect.nRanges; i++)
        {
            uint32_t first = ReadST(FontDictSelectExtract);
            
            uint8_t fd = ReadE(FontDictSelectExtract);
            FontSelect.ranges[i] = Range3(first,fd);

        }

        FontSelect.sentinel = ReadST(FontDictSelectExtract);
    }
}
int PPCFFExtractor::DisplayFontSelect()
{

    if(TopDictData.FDArray == 0)
    {
        return -1;
    }

    FILE* F;
    errno_t er = fopen_s(&F, "X:\\1.4 C++\\Vscode\\OTF EXTRACT\\display.html","w");
    if(F == nullptr || er != 0)
    {

    }

    fprintf(F,"<!DOCTYPE html>\n<html>\n<body>\n");
    fprintf(F,"<ul>\n");
    for(int i = 0; i < FontSelect.nRanges-1; i++)
    {
        fprintf(F,"<li>First: %d : Fd %d : ", FontSelect.ranges[i].first,FontSelect.ranges[i].fd);
        fprintf(F,"Size: %d : Offset: %d : </li>\n", FontDictData.Dicts[FontSelect.ranges[i].fd].PrivateDictSize, FontDictData.Dicts[FontSelect.ranges[i].fd].PrivateDictOffset);
        fprintf(F,"\n <pre class=\"hexa\">\n");
        for(int j = 0; j < LocalSubroutineIndex.Objects[FontSelect.ranges[i].fd].size; j++)
        {
            if(j%10 == 0)
            {
                fprintf(F,"\n");
            }
            fprintf(F,"%x ",LocalSubroutineIndex.Objects[FontSelect.ranges[i].fd].data[j]);
        }
        fprintf(F,"\n</pre>\n");
    }
    fprintf(F,"</ul>\n");
    fprintf(F,"</body>\n</html>\n");
    fclose(F);
}

PPCFFExtractor::~PPCFFExtractor(){}