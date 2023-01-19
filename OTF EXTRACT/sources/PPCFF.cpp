#include "PPCFF.h"

using namespace PPCFF;
using namespace PPFF::Util;
PPCFFExtractor::PPCFFExtractor(PPFF::Tables::PPFFTableDirectory CFFDirectory, const char* FontPath)
{
    CFFDirectory = CFFDirectory;
    FontPath = FontPath;
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
    int closeStatus = fclose(HeaderExtract);

}
int PPCFFExtractor::ExtractNameIndex(bool ExtractOffsets, bool ExtractOffsets)
{
    FILE* NameIndexExtract = NULL;
    errno_t fErr = fopen_s(&NameIndexExtract, FontPath, "rb");
    if(NameIndexExtract == NULL || fErr != 0)
    {
        return 0;
    }
    int seekSee = fseek(NameIndexExtract, CFFHeader.hdrSize, SEEK_SET); if(seekSee != 0){ fclose(NameIndexExtract); return 0; }
    NameIndex.count = ReadST(NameIndexExtract);
    NameIndex.offSize = ReadE(NameIndexExtract);
    NameIndex.Offset = malloc((NameIndex.offSize * NameIndex.count)+1);
    if(NameIndex.Offset == nullptr)
    {
        return 0;
    }


    std::function<void(void*, uint16_t)> lambda_func[] = {
        [&NameIndexExtract](void* data, uint16_t count) { uint8_t* _data = (uint8_t*)data;  for(int i = 0; i < count+1; i++){ _data[i] =  ReadE(NameIndexExtract);  } },
        [&NameIndexExtract](void* data, uint16_t count) { uint16_t* _data = (uint16_t*)data; for(int i = 0; i < count+1; i++){ _data[i] = ReadST(NameIndexExtract);  } },
        [&NameIndexExtract](void* data, uint16_t count) { uint32_t* _data = (uint32_t*)data; for(int i = 0; i < count+1; i++){ _data[i] = ReadTF(NameIndexExtract);  } },
        [&NameIndexExtract](void* data, uint16_t count) { uint32_t* _data = (uint32_t*)data; for(int i = 0; i < count+1; i++){ _data[i] = ReadTT(NameIndexExtract);  } }
    };

    int index = NameIndex.offSize-1;
    if(index >=  3 || index < 0)
    {
        free(NameIndex.Offset);
        return 0;
    }
    
    lambda_func[index](NameIndex.Offset, NameIndex.count);
    //mod = i-i%offSize
    //(uint32_t*)data[mod]
    


}

PPCFFExtractor::~PPCFFExtractor(){}