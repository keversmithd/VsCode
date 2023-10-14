#ifndef PPCFF_H
#define PPCFF_H

#include "PPFFDebug.h"
#include "PPFFTables.h"

#include <functional>
#include <PPChronoPool.h>
#include <vector>


struct Vectoid2
{
    int x;
    int y;
};

namespace PPCFF
{
    struct PPCFFTopDictData;
    struct PPCFFCharstring;

    void IndexExtract8(FILE* NameIndexExtract, void* data, uint16_t count);
    void IndexExtract16(FILE* NameIndexExtract, void* data, uint16_t count);
    void IndexExtract24(FILE* NameIndexExtract, void* data, uint16_t count);
    void IndexExtract32(FILE* NameIndexExtract, void* data, uint16_t count);

    void ExtractOffsets8(FILE* NameIndexExtract, uint32_t* data, uint16_t count);
    void ExtractOffsets16(FILE* NameIndexExtract, uint32_t* data, uint16_t count);
    void ExtractOffsets24(FILE* NameIndexExtract, uint32_t* data, uint16_t count);
    void ExtractOffsets32(FILE* NameIndexExtract, uint32_t* data, uint16_t count);

    int32_t DictDataExtract0(uint8_t* Byte, int& CurrentIndex);
    int32_t DictDataExtract1(uint8_t* Byte, int& CurrentIndex);
    int32_t DictDataExtract2(uint8_t* Byte, int& CurrentIndex);
    int32_t DictDataExtract3(uint8_t* Byte, int& CurrentIndex);
    int32_t DictDataExtract4(uint8_t* Byte, int& CurrentIndex);

    float DictRealExtract(uint8_t* Byte, int& CurrentIndex);

    #pragma region TopProccedure
    void NameInsert0(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
    void NameInsert1(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
    void NameInsert2(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
    void NameInsert3(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
    void NameInsert4(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
    void NameInsert5(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
    void NameInsert6(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
    void NameInsert7(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
    void NameInsert8(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
    void NameInsert9(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
    void NameInsert10(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
    void NameInsert11(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
    void NameInsert12(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
    void NameInsert13(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
    void NameInsert14(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
    void NameInsert15(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
    void NameInsert16(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
    void NameInsert17(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
    void NameInsert18(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
    void NameInsert19(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
    void NameInsert20(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
    void NameInsert21(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
    void NameInsert22(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
    void NameInsert23(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
    void NameInsert24(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
    void NameInsert25(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
    void NameInsert26(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
    void NameInsert27(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
    void NameInsert28(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
    void NameInsert29(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
    void NameInsert30(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
    void NameInsert31(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
    void NameInsert32(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
    void NameInsert33(PPCFFTopDictData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
    #pragma endregion

 #pragma region CharstringInsert
    void CharStringInsert0(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath);
    void CharStringInsert1(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, 
Vectoid2& OriginOfPath);
    void CharStringInsert2(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, 
Vectoid2& OriginOfPath);
    void CharStringInsert3(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, 
Vectoid2& OriginOfPath);
    void CharStringInsert4(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, 
Vectoid2& OriginOfPath);
    void CharStringInsert5(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, 
Vectoid2& OriginOfPath);
    void CharStringInsert6(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, 
Vectoid2& OriginOfPath);
    void CharStringInsert7(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, 
Vectoid2& OriginOfPath);
    void CharStringInsert8(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, 
Vectoid2& OriginOfPath);
    void CharStringInsert9(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, 
Vectoid2& OriginOfPath);
    void CharStringInsert10(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath);
    void CharStringInsert11(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath);
    void CharStringInsert12(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath);
    void CharStringInsert13(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath);
    void CharStringInsert14(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath);
    void CharStringInsert15(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath);
    void CharStringInsert16(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath);
    void CharStringInsert17(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath);
    void CharStringInsert18(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath);
    void CharStringInsert19(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath);
    void CharStringInsert20(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath);
    void CharStringInsert21(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath);
    void CharStringInsert22(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath);
    void CharStringInsert23(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath);
    void CharStringInsert24(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath);
    void CharStringInsert25(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath);
    void CharStringInsert26(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath);
    void CharStringInsert27(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath);
    void CharStringInsert28(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath);
    void CharStringInsert29(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath);
    void CharStringInsert30(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath);
    void CharStringInsert31(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath);
    void CharStringInsert32(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath);
    void CharStringInsert33(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath);
    void CharStringInsert34(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath);
    void CharStringInsert35(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath);
    void CharStringInsert36(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath);
    void CharStringInsert37(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath);
    void CharStringInsert38(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath);
    void CharStringInsert39(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath);
    void CharStringInsert40(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath);
    void CharStringInsert41(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath);
    void CharStringInsert42(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath);
    void CharStringInsert43(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath);
    void CharStringInsert44(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath);
    void CharStringInsert45(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath);
    void CharStringInsert46(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath);
    void CharStringInsert47(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath);
    void CharStringInsert48(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& Index, uint64_t& DataIndex, uint8_t& DataEntries, uint8_t* data, Vectoid2& pen, Vectoid2& OriginOfPath);
 #pragma endregion

    struct PPCFFHeader
    {
        uint8_t major= 0;
        uint8_t minor= 0;
        uint8_t hdrSize= 0;
        uint8_t OffSize= 0;
        uint32_t EndOfTable= 0;
    };
    struct PPCFFObjectEntry
    {
        uint8_t* data = nullptr;
        int size = 0;
        ~PPCFFObjectEntry()
        {
            if(data != nullptr)
            {
                free(data);
            }
            
        }
    };
    struct PPCFFIndex
    {
        uint16_t count = 0;
        uint8_t offSize = 0;
        void* Offset = nullptr;
        uint32_t* Offsets = nullptr;
        PPCFFObjectEntry* Objects = nullptr;
        uint32_t ObjectsBegin = 0;
        uint32_t EndOfTable = 0;

        PPCFFIndex() : count(0), offSize(0), Offset(nullptr), Offsets(nullptr), Objects(nullptr), ObjectsBegin(0), EndOfTable(0)
        {
            
        }

        ~PPCFFIndex()
        {
            if(Objects != nullptr)
            {
                free(Objects);
            }
            if(Offsets != nullptr)
            {
                free(Offsets);
            }
        }
    };  
    struct PPCFFTopDictData
    {
        struct ROS{ uint16_t SID1 = 0; uint16_t SID2 = 0; uint32_t number = 0; };
        uint16_t version = 0; //SID-2BYTE
        uint16_t notice = 0; 
        uint16_t copyright = 0;
        uint16_t FullName = 0;
        uint16_t FamilyName = 0;
        uint16_t Weight = 0;
        bool isFixedPitch = 0;
        int32_t ItalicAngle = 0;         //number is integer or real number
        int32_t UnderlinePosition = 0;
        uint32_t UnderlineThickness = 0;
        uint32_t PaintType = 0;
        uint32_t CharstringType = 0;
        float FontMatrix[6] = {0,0,0,0,0,0};
        uint32_t UniqueID = 0;
        float FontBBox[4] = {0,0,0,0};
        uint32_t StrokeWidth = 0;
        uint32_t* XUID = 0;
        uint32_t charset = 0;
        uint32_t Encoding = 0;
        uint32_t CharStrings = 0;
        uint32_t Private[2] = {0,0};
        uint32_t SyntheticBase = 0;
        uint16_t PostScript = 0;
        uint16_t BaseFontName = 0;
        uint32_t* BaseFontBlend = 0;
        ROS ros;
        uint32_t CIDFontVersion = 0;
        uint32_t CIDFontRevision = 0;
        uint32_t CIDFontType = 0;
        uint32_t CIDCount = 0;
        uint32_t UIDBase = 0;
        uint32_t FDArray = 0;
        uint32_t FDSelect = 0;
        uint16_t FontName = 0;
    };
    struct PPCFFPrivateData
    {
        uint32_t DataStart = 0;
        std::vector<int> BlueValues;
        std::vector<int> OtherBlues;
        std::vector<int> FamilyBlues;
        std::vector<int> FamilyOtherBlues;
        float BlueScale = 0;
        float BlueShift= 0;
        float BlueFuzz= 0;
        float StdHW= 0;
        float StdVW= 0;
        std::vector<int> StempSnapH;
        std::vector<int> StempSnapV;
        bool ForceBold= 0;
        float LanguageGroup= 0;
        float ExpansionFactor= 0;
        float initalRandomSed= 0;
        uint32_t Subrs= 0;
        float defaultWidthX= 0;
        float nominalWidthX= 0;
    };


    #pragma region PrivateDict
        void PrivateOperatorExtraction0(PPCFFPrivateData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
        void PrivateOperatorExtraction1(PPCFFPrivateData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
        void PrivateOperatorExtraction2(PPCFFPrivateData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
        void PrivateOperatorExtraction3(PPCFFPrivateData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
        void PrivateOperatorExtraction4(PPCFFPrivateData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
        void PrivateOperatorExtraction5(PPCFFPrivateData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
        void PrivateOperatorExtraction6(PPCFFPrivateData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
        void PrivateOperatorExtraction7(PPCFFPrivateData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
        void PrivateOperatorExtraction8(PPCFFPrivateData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
        void PrivateOperatorExtraction9(PPCFFPrivateData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
        void PrivateOperatorExtraction10(PPCFFPrivateData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
        void PrivateOperatorExtraction11(PPCFFPrivateData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
        void PrivateOperatorExtraction12(PPCFFPrivateData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
        void PrivateOperatorExtraction13(PPCFFPrivateData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
        void PrivateOperatorExtraction14(PPCFFPrivateData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
        void PrivateOperatorExtraction15(PPCFFPrivateData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
        void PrivateOperatorExtraction16(PPCFFPrivateData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
        void PrivateOperatorExtraction17(PPCFFPrivateData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);
    #pragma endregion

    struct PPCFFHint
    {
        std::vector<int> intArguments;
    };

    enum PPCFFCurveType
    {
        PPCFF_QUADRATIC,
        PPCFF_CUBIC,
        PPCFF_LINE,
    };

    struct PPCFFCurve
    {
        int curveType;
        std::vector<int> intArguments;
    };

    struct Range3
    {
        uint16_t first = 0;
        uint8_t fd = 0;


        Range3(uint16_t _first, uint8_t _fd) : first(_first), fd(_fd)
        {

        }
        void display()
        {
            printf("<li>First: %d : Fd %d</li>\n", first,fd);
        }

    };

    struct PPCFFFontSelect
    {
        uint8_t format = 0;
        uint8_t* fds = nullptr;

        uint8_t nRanges = 0;
        Range3* ranges = nullptr;
        uint16_t sentinel = 0;
    };

    struct Line
    {
        Vectoid2 A;
        Vectoid2 B;
        Vectoid2 C;
        Vectoid2 D;

        PPCFFCurveType curveType;

        Line()
        {

        }

        Line(Vectoid2 _A, Vectoid2 _B) : A(_A), B(_B), curveType(PPCFF_LINE)
        {

        }

        Line(Vectoid2 _A, Vectoid2 _B, Vectoid2 _C) : A(_A), B(_B), C(_C), curveType(PPCFF_QUADRATIC)
        {

        }


        

        // ~Line()
        // {

        // }
    };

    struct PPCFFCharstring
    {
        std::vector<PPCFFHint> Hints;
        std::vector<PPCFFCurve> Curves;
        std::vector<Vectoid2> Geom;
        std::vector<Line> Lines;

        void ReadGeom()
        {

            printf("\n\n\n\n NEW CHARSTRING \n\n\n\n");
            for(int i = 0; i < Lines.size(); i++)
            {
                switch(Lines[i].curveType)
                {
                    case PPCFF_LINE:
                        printf("\\draw[fill = black] (%d,%d) -- (%d,%d) node {$%d$};\n", Lines[i].A.x, Lines[i].A.y, Lines[i].B.x, Lines[i].B.y, i);
                        break;
                    case PPCFF_QUADRATIC:
                        printf("\\draw (%d, %d) to[quadratic={(%d, %d)}] (%d, %d);\n", Lines[i].A.x, Lines[i].A.y, Lines[i].B.x, Lines[i].B.y, Lines[i].C.x, Lines[i].C.y);
                        break;
                    case PPCFF_CUBIC:
                        printf("\\draw (%d, %d) .. controls (%d, %d) and (%d,%d) .. (%d,%d);\n", Lines[i].A.x, Lines[i].A.y, Lines[i].B.x, Lines[i].B.y, Lines[i].C.x, Lines[i].C.y, Lines[i].D.x, Lines[i].D.y);
                        break;
                    default:
                        break;


                }
                
            }

            printf("\n\n\n\n NEW CHARSTRING \n\n\n\n");
        }

    };
    
    struct PPCFFFontDict
    {
        uint32_t FontNameSID = 0;
        uint32_t PrivateDictSize = 0;
        uint32_t PrivateDictOffset = 0;
    };

    struct PPCFFFontDictData
    {
        std::vector<PPCFFFontDict> Dicts;
        
    };

    struct PPCFFSubroutines
    {
        uint8_t* data = nullptr;
        int size = 0;
    };

    struct PPCFFExtractor
    {
        private:
            PPFF::Tables::PPFFTableDirectory CFFDirectory;
            PPFF::Tables::PPFFTableRecord CFFTable;
            PPCFFHeader CFFHeader;
            PPCFFIndex NameIndex;
            PPCFFIndex TopDictIndex;
            PPCFFIndex FontDictIndex;
            PPCFFIndex StringIndex;
            PPCFFIndex CharStringsIndex;
            PPCFFIndex GlobalSubroutineIndex;
            PPCFFIndex LocalSubroutineIndex;


            PPCFFTopDictData TopDictData;
            PPCFFFontDictData FontDictData;
            PPCFFFontSelect FontSelect;

            PPCFFPrivateData PrivateDictData;
            uint16_t LocalSubroutineBias = 0;

            std::vector<PPCFFCharstring> CharstringGeometry;

            const char* FontPath;
        public:
            PPCFFExtractor(PPFF::Tables::PPFFTableDirectory CFFDirectory, const char* FontPath);
            int ExtractHeader();
            int ExtractNameIndex(bool ExtractObjects);
            int FillArbitraryIndex(FILE* File, PPCFFIndex& Index, uint32_t PrevOffset = 0);
            int ExtractTopDictIndex();
            int ExtractStringIndex();
            int ExtractGlobalSubroutineIndex();
            int DecodeTopDictData();
            int DecodeDictData(uint8_t* Data, int size);
            int ExtractCharstrings();

            int ExtractCharsets();
            int ExtractFontDictIndex();
            int ExtractFontFontDictSelect();
            int DecodeFontDictData();
            int ExtractFormatThreeSubroutines();
            int ExtractSubroutines();
            int DecodePrivateDict();
            int ExtractSubrsPrivate();

            PPCFFCharstring DecodeSingularCharstring();
            int DecodeCharstrings();
            int CallLocalSubroutine(int Charnumber, PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intInde, uint8_t& floatInde, int& inde48, uint64_t& DataInde, uint8_t& DataEntries, Vectoid2& pen, Vectoid2& OriginOfPath);
            int CallGlobalSubroutine(int SubrNumber, PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intInde, uint8_t& floatInde, int& inde48, uint64_t& DataInde, uint8_t& DataEntries, Vectoid2& pen, Vectoid2& OriginOfPath);
            int DecodeSingularCIDFormat3Charstring();
            int DisplayFontSelect();
            ~PPCFFExtractor();
    };


    


}





#endif