#include "PPTFF/PPTFCMAP.h"






EncodingRecordFormat0 F_EncodingRecordFormat0(FILE* F)
{
    EncodingRecordFormat0 Record;
    Record.format = 0;

    Record.format = ReadST(F);
    Record.length = ReadST(F);
    Record.language = ReadST(F);
    //Record.glyphIdArray = (uint8*)malloc(sizeof(uint8) * 0);
    //fread(Record.glyphIdArray,sizeof(uint8),0,F);

}
EncodingRecordFormat2 F_EncodingRecordFormat2(FILE* F)
{
    EncodingRecordFormat2 Record;
    Record.format = 2;

    Record.format = ReadST(F);
    Record.length = ReadST(F);
    Record.language = ReadST(F);
    //Record.subHeaderKeys = (uint16*)malloc(sizeof(uint16) * 0);
    //fread(Record.subHeaderKeys,sizeof(uint16),0,F);
}
EncodingRecordFormat4 F_EncodingRecordFormat4(FILE* F)
{
    EncodingRecordFormat4 Record;
    Record.format = 4;

    Record.length = ReadST(F);
    Record.language = ReadST(F);
    Record.segCountX2 = ReadST(F);
    Record.searchRange = ReadST(F);
    Record.entrySelector = ReadST(F);
    Record.rangeShift = ReadST(F);
    Record.endCode = (uint16*)malloc(sizeof(uint16) * Record.segCountX2/2);

    fread(Record.endCode,sizeof(uint16),Record.segCountX2/2,F);

    Record.reservedPad = ReadST(F);
    Record.startCode = (uint16*)malloc(sizeof(uint16) * Record.segCountX2/2);
    fread(Record.startCode,sizeof(uint16),Record.segCountX2/2,F);
    Record.idDelta = (int16*)malloc(sizeof(int16) * Record.segCountX2/2);
    fread(Record.idDelta,sizeof(int16),Record.segCountX2/2,F);
    Record.idRangeOffsets = (uint16*)malloc(sizeof(uint16) * Record.segCountX2/2);
    fread(Record.idRangeOffsets,sizeof(uint16),Record.segCountX2/2,F);
    Record.glyphIdArray = (uint16*)malloc(sizeof(uint16)*Record.segCountX2/2);
    fread(Record.glyphIdArray, sizeof(uint16_t), Record.segCountX2/2, F);

    return Record;

}
EncodingRecordFormat6 F_EncodingRecordFormat6(FILE* F)
{
        EncodingRecordFormat6 Record;
        Record.format = 6;

    Record.format = ReadST(F);
    Record.length = ReadST(F);
    Record.language = ReadST(F);
    Record.firstCode = ReadST(F);
    Record.entryCount = ReadST(F);
    Record.glyphIdArray = (uint16*)malloc(sizeof(uint16) * Record.entryCount);
    fread(Record.glyphIdArray,sizeof(uint16),Record.entryCount,F);
}
EncodingRecordFormat8 F_EncodingRecordFormat8(FILE* F)
{
        EncodingRecordFormat8 Record;
        Record.format = 8;

    Record.format = ReadST(F);
    Record.reserved = ReadST(F);
    Record.length = ReadTT(F);
    Record.language = ReadTT(F);
    Record.is32 = (uint8*)malloc(sizeof(uint8) * 0);
    fread(Record.is32,sizeof(uint8),0,F);
    Record.numGroups = ReadTT(F);
    Record.groups = (SequentialMapGroup*)malloc(sizeof(SequentialMapGroup) * Record.numGroups);
    fread(Record.groups,sizeof(SequentialMapGroup),Record.numGroups,F);
}
EncodingRecordFormat10 F_EncodingRecordFormat10(FILE* F)
{
        EncodingRecordFormat10 Record;
        Record.format = 10;

    Record.format = ReadST(F);
    Record.reserved = ReadST(F);
    Record.length = ReadTT(F);
    Record.language = ReadTT(F);
    Record.startCharCode = ReadTT(F);
    Record.numChars = ReadTT(F);
    Record.glyphIdArray = (uint16*)malloc(sizeof(uint16) * Record.format);
    fread(Record.glyphIdArray,sizeof(uint16),Record.format,F);
}
EncodingRecordFormat12 F_EncodingRecordFormat12(FILE* F)
{
    EncodingRecordFormat12 Record;
    Record.format = 12;

    Record.reserved = ReadST(F);
    Record.length = ReadTT(F);
    Record.language = ReadTT(F);
    Record.numGroups = ReadTT(F);
    Record.groups = (SequentialMapGroup*)malloc(sizeof(SequentialMapGroup) * Record.numGroups);
    for(int i = 0; i < Record.numGroups; i++)
    {
        Record.groups[i].startCharCode = ReadTT(F);
        Record.groups[i].endCharCode = ReadTT(F);
        Record.groups[i].startGlyphID = ReadTT(F);
    }
    return Record;
    //fread(Record.groups,sizeof(SequentialMapGroup),Record.numGroups,F);
}
EncodingRecordFormat13 F_EncodingRecordFormat13(FILE* F)
{
    EncodingRecordFormat13 Record;
    Record.format = 14;

    Record.format = ReadST(F);
    Record.reserved = ReadST(F);
    Record.length = ReadTT(F);
    Record.language = ReadTT(F);
    Record.numGroups = ReadTT(F);
    Record.groups = (ConstantMapGroup*)malloc(sizeof(ConstantMapGroup) * Record.numGroups);
    fread(Record.groups,sizeof(ConstantMapGroup),Record.numGroups,F);
}
EncodingRecordFormat14 F_EncodingRecordFormat14(FILE* F)
{
    EncodingRecordFormat14 Record;
    Record.format = 16;

    Record.format = ReadST(F);
    Record.length = ReadTT(F);
    Record.numVarSelectorRecords = ReadTT(F);
    Record.varSelector = (VariationSelector*)malloc(sizeof(VariationSelector) * Record.numVarSelectorRecords);
    fread(Record.varSelector,sizeof(VariationSelector),Record.numVarSelectorRecords,F);
}


void HandleRecordFormat0(EncodingRecordFormat0 Formula0)
{
    // uint32_t* GlyphIndexValues = new uint32_t[256];
    // for(int i = 0; i < 256; i++)
    // {
    //     GlyphIndexValues[i] = Formula0.glyphIdArray[i];
    // }
}
void HandleRecordFormat2(EncodingRecordFormat2 Formula2)
{
    // int ExampleChar = 223;
    // uint16_t HighByte = ExampleChar & (11110000);
    // uint16_t LowByte = ExampleChar & (00001111);
    
    // uint32_t CurrentByte = ExampleChar*8;

    // for(int i = 0; i < 256; i++)
    // {
    //     int HighByteModulo = HighByte % 256;

    //     uint16_t subHeaderKey = Formula2.subHeaderKeys[i];

    //     SubHeader subHeader = Formula2.subHeaders[i];

    //     uint16_t FirstValidLowByte = subHeader.firstCode;

    //     uint16_t entryCount = subHeader.entryCount;

    //     uint32_t rawRange = entryCount-FirstValidLowByte;

    //     int OffsetOfThisByte = ExampleChar-FirstValidLowByte;
    
    // }
}
void HandleRecordFormat4(EncodingRecordFormat4 Formula4)
{
    uint16_t examplechar = 33;

    for(int i = 0; i < Formula4.segCountX2/2; i++)
    {
        uint16_t endCode = PPFF::Util::LittleEndianST(Formula4.endCode[i]);
        uint16_t startCode = PPFF::Util::LittleEndianST(Formula4.startCode[i]);
        if(examplechar <= endCode && examplechar >= startCode)
        {
            uint16_t idRangeOffset = PPFF::Util::LittleEndianST(Formula4.idRangeOffsets[i]);
            int16_t idDelta = PPFF::Util::LittleEndianIST(Formula4.idDelta[i]);
            if(idRangeOffset == 0)
            {
                uint16_t glyphId = idDelta + examplechar;
                uint16_t innerGlyphId = PPFF::Util::LittleEndianST(Formula4.glyphIdArray[glyphId]);
                int i = 0;

            }else{
                
            }
        }

    }
    



}
void HandleRecordFormat6(EncodingRecordFormat6 Formula6)
{

}
void HandleRecordFormat8(EncodingRecordFormat8 Formula8)
{

}
void HandleRecordFormat10(EncodingRecordFormat10 Formula10)
{

}
void HandleRecordFormat12(EncodingRecordFormat12 Formula12)
{
    return;
    uint32_t exampleChar = 161;

    for(int i = 0; i < Formula12.numGroups; i++)
    {
        SequentialMapGroup CurrentGroup = Formula12.groups[i]; 

        uint32_t StartCode = CurrentGroup.startCharCode;
        uint32_t EndCode = CurrentGroup.endCharCode;

        if(exampleChar <= EndCode && exampleChar >= StartCode)
        {
            uint32_t StartingGlyphId = CurrentGroup.startGlyphID;
            uint32_t Delta = exampleChar - StartCode;
            uint32_t GlyphId = StartingGlyphId+Delta;
            return;
        }

    }


}
void HandleRecordFormat13(EncodingRecordFormat13 Formula13)
{

}
void HandleRecordFormat14(EncodingRecordFormat14 Formula14)
{

}