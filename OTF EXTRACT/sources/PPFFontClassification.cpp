#include "PPFFontClassification.h"

bool PPFF::FontClassification::IsCFFFileType(const char* FontPath)
{
    FILE* SourceFile = NULL;
    errno_t Error = fopen_s(&SourceFile, FontPath, "rb");
    if(Error != 0)
    { 
        return false;
    }
    if(SourceFile == NULL)
    {
        return false;
    }
    uint32_t sfntVersion = PPFF::Util::ReadTT(SourceFile);
    if(sfntVersion = 0x4F54544F)
    {
        return true;
    }
    return false;
}

bool PPFF::FontClassification::IsSupportedFileType(const char* FontPath)
{
    for(int s = 0; s < NumberOfSupportedFileTypes; s++)
    {
        if(SupportChecks[s](FontPath))
        {
            return true;
        }
    }
    return false;
}
uint8_t PPFF::FontClassification::SupportedFileTypeIndex(PPFF::FontClassification::SupportedFileType FileType)
{
    return FileType & 0x0F;
}
PPFF::FontClassification::SupportedFileType PPFF::FontClassification::GetFileType(const char* FontPath)
{
    for(int s = 0; s < NumberOfSupportedFileTypes; s++)
    {   
        if(SupportChecks[s](FontPath))
        {
            return PPFF::FontClassification::SuportedFileTypes[s];
        }
    }
    return PPFNO;
}