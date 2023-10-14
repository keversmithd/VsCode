#ifndef PPFFTABLES
#define PPFFTABLES
#include "PPFFDebug.h"
#include <string>
#include <string.h>
#include <unordered_map>
#include "IndexSort.h"
namespace PPFF::Tables
{
    struct PPFFTableRecord
    {
        char Tag[5];
        uint32_t checksum;
        uint32_t  offset;
        uint32_t length;
    };

    struct PPFFTableDirectory
    {
        uint32_t sfntVersion;
        uint16_t numTables;
        uint16_t searchRange;
        uint16_t entrySelector;
        uint16_t rangeShift;
        uint8_t tableRecordOffset;
        std::unordered_map<std::string, PPFFTableRecord> tableRecords;
        PPFFTableDirectory();
        ~PPFFTableDirectory();
    };
    

    void SortTableFilter(char** TableFilter, uint8_t filterCount);
    void GetTableHeader(PPFFTableDirectory &TableDirectory, FILE* file);
    void GetTableRecords(PPFFTableDirectory &TableDirectory, FILE* file, const char** tableFilter = 0, uint8_t filterCount = 0, bool filterAdjusted = false);
    PPFFTableDirectory PopulateOTFDirectory(const char* FontPath);
    PPFFTableDirectory PopulateTTFDirectory(const char* FontPath);
    
    


}

#endif