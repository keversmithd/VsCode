#include "PPTFF/PPTF.h"


using namespace PPFF::Util;
    
uint32_t TTFLoca::Offset(int index)
{
    if(Long)
    {
        return PPFF::Util::LittleEndianTT(LongOffsets[index]);
    }else{
        return PPFF::Util::LittleEndianST(ShortOffsets[index]);
    }
}

TTFExtractor::TTFExtractor(PPFF::Tables::PPFFTableDirectory CFFDirectory, const char* FontPath) : fontPath(FontPath), cmapencodings(nullptr), Directroy(CFFDirectory)
{

    CMAP = CFFDirectory.tableRecords["cmap"];



}

int TTFExtractor::ExtractCmap()
{
    FILE* _F = NULL;
    errno_t _openstatus = fopen_s(&_F, fontPath, "rb");
    if(_openstatus != 0 || _F == NULL) return -1;
    fseek(_F, CMAP.offset, SEEK_SET);


    cmap.version = ReadST(_F);
    cmap.numTables = ReadST(_F);
    

    cmapencodings = (CmapEncoding*)malloc(sizeof(CmapEncoding)*cmap.numTables);

    for(int i = 0; i < cmap.numTables; i++)
    {
        cmapencodings[i].platformID = ReadST(_F);
        cmapencodings[i].encodingID = ReadST(_F);
        cmapencodings[i].subtableOffset = ReadTT(_F);
    }

    int subtableOffset = 0;

    for(int i = 0; i < cmap.numTables; i++)
    {

        uint16_t platformId = cmapencodings[i].platformID;
        uint16_t encodingId = cmapencodings[i].encodingID;

        subtableOffset = CMAP.offset + cmapencodings[i].subtableOffset;

        fseek(_F, subtableOffset, SEEK_SET);

        uint16_t format = ReadST(_F);        

       if(format==0){
            EncodingRecordFormat0 RF = F_EncodingRecordFormat0(_F);
            HandleRecordFormat0(RF);
        }
        if(format==2){
            EncodingRecordFormat2 RF = F_EncodingRecordFormat2(_F);
            HandleRecordFormat2(RF);
        }
        if(format==4){
            EncodingRecordFormat4 RF = F_EncodingRecordFormat4(_F);
            HandleRecordFormat4(RF);
        
        }
        if(format==6){
        EncodingRecordFormat6 RF = F_EncodingRecordFormat6(_F);HandleRecordFormat6(RF);}
        if(format==8){
        EncodingRecordFormat8 RF = F_EncodingRecordFormat8(_F);HandleRecordFormat8(RF);}
        if(format==10){
        EncodingRecordFormat10 RF = F_EncodingRecordFormat10(_F);HandleRecordFormat10(RF);}
        if(format==12){
            EncodingRecordFormat12 RF = F_EncodingRecordFormat12(_F);
            HandleRecordFormat12(RF);
        }
        if(format==13){
        EncodingRecordFormat13 RF = F_EncodingRecordFormat13(_F);HandleRecordFormat13(RF);}
        if(format==14){
        EncodingRecordFormat14 RF = F_EncodingRecordFormat14(_F);HandleRecordFormat14(RF);}
    }






}

int TTFExtractor::ExtractMaxP()
{
    FILE* F = nullptr;
    fopen_s(&F, fontPath, "rb");
    if(Directroy.tableRecords.find("maxp") == Directroy.tableRecords.end()) return -1;
    //PPFF::Tables::PPFFTableRecord head = Directroy.tableRecords["head"];
    
    fseek(F, Directroy.tableRecords["maxp"].offset, SEEK_SET);
    Maxp.version = ReadTT(F);
    Maxp.numGlyphs = ReadST(F);
    if(Maxp.version == 0x00010000)
    {
        Maxp.maxPoints = ReadST(F);
        Maxp.maxContours = ReadST(F);
        Maxp.maxCompositePoints = ReadST(F);
        Maxp.maxCompositeContours = ReadST(F);
        Maxp.maxZones = ReadST(F);
        Maxp.maxTwilightPoints = ReadST(F);
        Maxp.maxStorage = ReadST(F);
        Maxp.maxFunctionDefs = ReadST(F);
        Maxp.maxInstructionDefs = ReadST(F);
        Maxp.maxStackElements = ReadST(F);
        Maxp.maxSizeOfInstructions = ReadST(F);
        Maxp.maxComponentElements = ReadST(F);
        Maxp.maxComponentDepth = ReadST(F);
    }
    
}

int TTFExtractor::ExtractHead()
{
    FILE* F = nullptr;
    fopen_s(&F, fontPath, "rb");
    if(Directroy.tableRecords.find("head") == Directroy.tableRecords.end()) return -1;
    //PPFF::Tables::PPFFTableRecord head = Directroy.tableRecords["head"];
    
    fseek(F, Directroy.tableRecords["head"].offset, SEEK_SET);

    Head.majorVersion = ReadST(F);
    Head.minorVersion = ReadST(F);
    Head.fontRevision = ReadF(F);
    Head.checksumAdjustment = ReadTT(F);
    Head.magicNumber = ReadTT(F);
    Head.flags = ReadST(F);
    Head.unitsPerEm = ReadST(F);
    Head.created = ReadISF(F);
    Head.modified = ReadISF(F);
    Head.xMin = ReadIST(F);
    Head.yMin = ReadIST(F);
    Head.xMax = ReadIST(F);
    Head.yMax = ReadIST(F);
    Head.macStyle = ReadST(F);
    Head.lowestRecPPEM = ReadST(F);
    Head.fontDirectionHint = ReadIST(F);
    Head.indexToLocFormat = ReadIST(F);
    Head.glyphDataFormat = ReadIST(F);

    fclose(F);
}


int TTFExtractor::ExtractLoca()
{
    FILE* F = nullptr;
    fopen_s(&F, fontPath, "rb");
    if(Directroy.tableRecords.find("loca") == Directroy.tableRecords.end()) return -1;
    //PPFF::Tables::PPFFTableRecord head = Directroy.tableRecords["head"];
    
    fseek(F, Directroy.tableRecords["loca"].offset, SEEK_SET);

    int n = Maxp.numGlyphs+1;
    
    if(Head.indexToLocFormat == 0)
    {
        Loca.ShortOffsets = (uint16_t*)malloc(n*sizeof(uint16_t));
        fread(Loca.ShortOffsets, sizeof(uint16_t), n+1, F);
        Loca.Long = false;
    }else if(Head.indexToLocFormat == 1)
    {
        Loca.LongOffsets = (uint32_t*)malloc(n*sizeof(uint32_t));
        fread(Loca.LongOffsets, sizeof(uint32_t), n+1, F);
        Loca.Long = true;
    }
}

void TTFExtractor::Checksum()
{
    uint32_t CurrentCheckSum = CMAP.checksum;
    int SeekLocation = CMAP.offset;
    FILE* F = NULL;
    errno_t er = fopen_s(&F, fontPath, "rb");
    if(F == NULL || er != 0) return;
    fseek(F, SeekLocation, SEEK_SET);

    int Length = CMAP.length;
    uint32_t* tablePointer = (uint32_t*)malloc(Length);
    fread(tablePointer, sizeof(uint8_t), Length, F);
    PPFF::Util::checksum(tablePointer,Length);
    //Incorrect checksum
    fclose(F);
}

int TTFExtractor::ExtractGlyf()
{
    if(Directroy.tableRecords.find("glyf") == Directroy.tableRecords.end()) return -1;
    uint32_t GlyfTableOffset = Directroy.tableRecords["glyf"].offset;
    int GlyphToExtract = 0;
    int GlyphOffset = Loca.Offset(GlyphToExtract);
    int GlyphSize = Loca.Offset(GlyphToExtract+1)-GlyphOffset;

    TTFGlyf Glyph;

    FILE* F = nullptr;
    fopen_s(&F, fontPath, "rb");
    fseek(F, GlyfTableOffset+GlyphOffset, SEEK_SET);

    Glyph.numberOfContours = ReadIST(F);
    if(Glyph.numberOfContours == -1)
    {
        printf("Composite Glyph: %d\n",-1);
        return -1;
    }
    Glyph.xMin = ReadIST(F);
    Glyph.yMin = ReadIST(F);
    Glyph.xMax = ReadIST(F);
    Glyph.yMax = ReadIST(F);

    Glyph.endPtsOfContours = (uint16_t*)malloc(Glyph.numberOfContours*sizeof(uint16_t));
    fread(Glyph.endPtsOfContours, sizeof(uint16_t), Glyph.numberOfContours, F);

    Glyph.instructionLength = ReadST(F);
    Glyph.instructions = (uint8_t*)malloc(Glyph.instructionLength*sizeof(uint8_t));
    fread(Glyph.instructions, sizeof(uint8_t), Glyph.instructionLength, F);

    int NumberOfPoints = PPFF::Util::LittleEndianST(Glyph.endPtsOfContours[Glyph.numberOfContours-1]);

    Glyph.flags = (TTFGylfFlag*)malloc(NumberOfPoints*sizeof(TTFGylfFlag));

    int NumberOfFlags = NumberOfPoints;
    for(int i = 0; i < NumberOfFlags; i++)
    {
        Glyph.flags[i].FlagByte = ReadE(F);

        printf("Flag #%d:"BYTE_TO_BINARY_PATTERN"\n", i+1, BYTE_TO_BINARY(Glyph.flags[i].FlagByte));

        bool REPEAT_FLAG = (Glyph.flags[i].FlagByte & (0b00001000)) > 0;

        if(REPEAT_FLAG)
        {
            Glyph.flags[i].Repeats = ReadE(F);
            NumberOfFlags -= Glyph.flags[i].Repeats;
            
        }else
        {
            Glyph.flags[i].Repeats = 0;
        }
        
    }

    Glyph.Coordinates = (TTFGlyfPoint*)malloc(sizeof(TTFGlyfPoint)*NumberOfFlags);

    TTFGylfFlag FlagContainer;
    uint8_t FlagByte;
    int FlagRepeats = 0;
    int PointIndex = 0;
    for(int i = 0; i < NumberOfFlags; i++)
    {

        FlagContainer = Glyph.flags[i];
        FlagByte = FlagContainer.FlagByte;
        FlagRepeats = FlagContainer.Repeats;

        for(int j = 0; j < FlagRepeats+1; j++)
        {
            if((FlagByte & 0b00000010) > 0) 
            {
                if((FlagByte & 0b000010000) > 0)
                {
                    Glyph.Coordinates[PointIndex].x = ReadE(F);
                }else
                {
                    Glyph.Coordinates[PointIndex].x = ReadE(F)*-1;
                }
            }else if ((FlagByte & 0b000010000) > 0)
            {
                Glyph.Coordinates[PointIndex].x = Glyph.Coordinates[PointIndex-1].x;
            }else
            {
                //two bytes and interprested as a signed two byte integer
                Glyph.Coordinates[PointIndex].x = ReadBigIST(F);
            }

            if((FlagByte & 0b00000001)>0)
            {
                Glyph.Coordinates[PointIndex].OnCurve = true;
            }else
            {
                Glyph.Coordinates[PointIndex].OnCurve = false;
            }

            
            PointIndex++;
        }

        
    }

    PointIndex = 0;
    for(int i = 0; i < NumberOfFlags; i++)
    {

        FlagContainer = Glyph.flags[i];
        FlagByte = FlagContainer.FlagByte;
        FlagRepeats = FlagContainer.Repeats;

        for(int j = 0; j < FlagRepeats+1; j++)
        {
            if((FlagByte & 0b00000100) > 0) 
            {
                if((FlagByte & 0b000100000) > 0)
                {
                    Glyph.Coordinates[PointIndex].y = ReadE(F);
                }else
                {
                    Glyph.Coordinates[PointIndex].y = ReadE(F)*-1;
                }
            }else if ((FlagByte & 0b000100000) > 0)
            {
                Glyph.Coordinates[PointIndex].y = Glyph.Coordinates[PointIndex-1].y;
            }else
            {
                //two bytes and interprested as a signed two byte integer
                Glyph.Coordinates[PointIndex].y = ReadBigIST(F);
            }

            if((FlagByte & 0b00000001)>0)
            {
                Glyph.Coordinates[PointIndex].OnCurve = true;
            }else
            {
                Glyph.Coordinates[PointIndex].OnCurve = false;
            }

            
            PointIndex++;
        }
        

    }


    
    


}

TTFExtractor::~TTFExtractor()
{

}