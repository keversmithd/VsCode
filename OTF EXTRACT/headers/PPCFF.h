#ifndef PPCFF_H
#define PPCFF_H
#include "PPFFDebug.h"
#include "PPFFTables.h"

#include <functional>

namespace PPCFF
{
    struct PPCFFTopDictData;

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
    struct PPCFFHeader
    {
        uint8_t major;
        uint8_t minor;
        uint8_t hdrSize;
        uint8_t OffSize;
        uint32_t EndOfTable;
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
        uint16_t count;
        uint8_t offSize;
        void* Offset;
        uint32_t* Offsets = nullptr;
        PPCFFObjectEntry* Objects = nullptr;
        uint32_t ObjectsBegin;
        uint32_t EndOfTable;
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

    struct PPCFFExtractor
    {
        private:
            PPFF::Tables::PPFFTableDirectory CFFDirectory;
            PPFF::Tables::PPFFTableRecord CFFTable;
            PPCFFHeader CFFHeader;
            PPCFFIndex NameIndex;
            PPCFFIndex TopDictIndex;
            PPCFFIndex StringIndex;
            PPCFFIndex CharStringsIndex;
            PPCFFTopDictData TopDictData;
            const char* FontPath;
        public:
            PPCFFExtractor(PPFF::Tables::PPFFTableDirectory CFFDirectory, const char* FontPath);
            int ExtractHeader();
            int ExtractNameIndex(bool ExtractObjects);
            int FillArbitraryIndex(FILE* File, PPCFFIndex& Index, uint32_t PrevOffset = 0);
            int ExtractTopDictIndex();
            int ExtractStringIndex();
            int DecodeTopDictData();
            int DecodeDictData(uint8_t* Data, int size);
            int ExtractCharstrings();
            int DecodeCharstrings();
            int ExtractCharsets();
            ~PPCFFExtractor();
    };


    


}





#endif