#ifndef PFFFONTCLASS
#endif

#include <stdio.h>
#include <stdint.h>

#include "PPFFDebug.h"




namespace PPFF::FontClassification
{
    enum SupportedFileType
    {
        PPFCFF = 0xF0,
        PPFNO = 0xFF
    };
    constexpr unsigned int  NumberOfSupportedFileTypes = 1;
    constexpr SupportedFileType SuportedFileTypes[NumberOfSupportedFileTypes] = {PPFCFF};
    bool IsCFFFileType(const char* FontPath);
    constexpr bool(*SupportChecks [NumberOfSupportedFileTypes])(const char* FontPath) = {IsCFFFileType};
    bool IsSupportedFileType(const char* FontPath);
    uint8_t SupportedFileTypeIndex(SupportedFileType FileType);
    SupportedFileType GetFileType(const char* FontPath);
};

