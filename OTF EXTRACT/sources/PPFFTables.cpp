#include "PPFFTables.h"

using namespace PPFF::Util;

PPFF::Tables::PPFFTableDirectory::PPFFTableDirectory()
{
    sfntVersion = 0;
    numTables = 0;
    searchRange = 0;
    entrySelector = 0;
    rangeShift = 0;
    tableRecordOffset = 0;
}
PPFF::Tables::PPFFTableDirectory::~PPFFTableDirectory()
{
    
}

void PPFF::Tables::GetTableHeader(PPFFTableDirectory &TableDirectory, FILE* file)
{
    TableDirectory.sfntVersion = ReadTT(file);
    TableDirectory.numTables = ReadST(file);
    TableDirectory.searchRange = ReadST(file);
    TableDirectory.entrySelector = ReadST(file);
    TableDirectory.rangeShift = ReadST(file);
    TableDirectory.tableRecordOffset = 12;
}

void PPFF::Tables::SortTableFilter(char** TableFilter, uint8_t filterCount)
{
    std::unordered_map<std::string, uint8_t> chronologic;
    const char* TablesIndex[49] = { "avar","BASE","CBDT","CBLC","CFF ","CFF2","cmap","COLR","CPAL","cvar","cvt ","DSIG","EBDT","EBLC","EBSC","fpgm","fvar","gasp","GDEF","glyf","GPOS","GSUB","gvar","hdmx","head","hmtx","HVAR","JSTF","kern","loca","LTSH","MATH","maxp","MERG","meta","MVAR","name","OS/2","PCLT","post","prep","sbix","STAT","SVG","VDMX","vhea","vmtx","VORG","VVAR" };
    for(int i = 0; i < 49; i++)
    {
        chronologic.insert({TablesIndex[i], i});
    }

    IndexElement<uint8_t>*  ElementList = (IndexElement<uint8_t>*)malloc(filterCount * sizeof(IndexElement<int>));
    for(int i = 0; i < filterCount; i++)
    {
        ElementList[i].element = chronologic[TableFilter[i]];
        ElementList[i].string = TableFilter[i];
    }
    QuickSort(ElementList, 0, filterCount-1);
    for(int i = 0; i < filterCount; i++)
    {
        TableFilter[i] = ElementList[i].string;
    }
    free(ElementList);
    chronologic.clear();
}

// void PPFF::Tables::GetTableRecords(PPFFTableDirectory &TableDirectory, FILE* file, const char** tableFilter, uint8_t filterCount, bool filterAdjusted)
// {
//     fpos_t filePos = 0; fgetpos(file, &filePos);
//     if(filePos != TableDirectory.tableRecordOffset)
//     {
//         fseek(file, TableDirectory.tableRecordOffset, SEEK_SET);
//     }
//     if(filterCount == 0)
//     {
//         for(int r = 0; r < TableDirectory.numTables; r++)
//         {
//             PPFF::Tables::PPFFTableRecord TableRecord;
//             fread(TableRecord.Tag, 4, 1, file);
//             TableRecord.Tag[4] = '\0';
//             TableRecord.checksum = ReadTT(file);
//             TableRecord.offset = ReadTT(file);
//             TableRecord.length = ReadTT(file);
//             TableDirectory.tableRecords.insert({TableRecord.Tag,TableRecord});
//         }
//         return;
//     }

//     if(!filterAdjusted)
//     {
//         SortTableFilter((char**)tableFilter, filterCount);
//     }

//     uint8_t remainder = 0;
//     uint8_t max = TableDirectory.numTables;
//     uint8_t r = 0;
//     while(remainder < filterCount && r <= max)
//     {
//         char TagName[5];
//         fread(TagName, 4, 1, file);
//         TagName[4] = '\0';
//         if(strcmp(TagName, tableFilter[remainder]) == 0)
//         {
//             PPFF::Tables::PPFFTableRecord TableRecord;
//             TableRecord.Tag[0] = TagName[0];
//             TableRecord.Tag[1] = TagName[1];
//             TableRecord.Tag[2] = TagName[2];
//             TableRecord.Tag[3] = TagName[3];
//             TableRecord.Tag[4] = TagName[4];
//             TableRecord.checksum = ReadTT(file);
//             TableRecord.offset = ReadTT(file);
//             TableRecord.length = ReadTT(file);
//             TableDirectory.tableRecords.insert({TableRecord.Tag, TableRecord});
//             remainder++;
//         }else
//         {
//             fseek(file, 12, SEEK_CUR);
//         }
//         r++;
//     }
    
// }

void PPFF::Tables::GetTableRecords(PPFFTableDirectory &TableDirectory, FILE* file, const char** tableFilter, uint8_t filterCount, bool filterAdjusted)
{
    fpos_t filePos = 0; fgetpos(file, &filePos);


    // std::unordered_map<const char*, const char *> tableFilterMap;
    // for(int i = 0; i < filterCount; i++)
    // {
    //     tableFilterMap.insert(tableFilter[i], tableFilter[i]);
    // }


    if(filePos != TableDirectory.tableRecordOffset)
    {
        fseek(file, TableDirectory.tableRecordOffset, SEEK_SET);
    }
    if(filterCount == 0)
    {
        for(int r = 0; r < TableDirectory.numTables; r++)
        {
            PPFF::Tables::PPFFTableRecord TableRecord;
            fread(TableRecord.Tag, 4, 1, file);
            TableRecord.Tag[4] = '\0';
            TableRecord.checksum = ReadTT(file);
            TableRecord.offset = ReadTT(file);
            TableRecord.length = ReadTT(file);
            TableDirectory.tableRecords.insert({TableRecord.Tag,TableRecord});
        }
        return;
    }
    
    // if(!filterAdjusted)
    // {
    //     SortTableFilter((char**)tableFilter, filterCount);
    // }

    std::unordered_map<std::string, std::string> TableFilter;

    for(int i = 0; i < filterCount; i++)
    {
        TableFilter.insert({tableFilter[i], tableFilter[i]});
    }

    uint8_t remainder = 0;
    uint8_t max = TableDirectory.numTables;
    uint8_t r = 0;
    while(remainder < filterCount && r <= max)
    {
        char TagName[5];
        fread(TagName, 4, 1, file);
        TagName[4] = '\0';
        if(TableFilter.find(TagName) != TableFilter.end())
        {
            PPFF::Tables::PPFFTableRecord TableRecord;
            TableRecord.Tag[0] = TagName[0];
            TableRecord.Tag[1] = TagName[1];
            TableRecord.Tag[2] = TagName[2];
            TableRecord.Tag[3] = TagName[3];
            TableRecord.Tag[4] = TagName[4];
            TableRecord.checksum = ReadTT(file);
            TableRecord.offset = ReadTT(file);
            TableRecord.length = ReadTT(file);
            TableDirectory.tableRecords.insert({TableRecord.Tag, TableRecord});
            remainder++;
        }else
        {
            fseek(file, 12, SEEK_CUR);
        }
        r++;
    }
    
}


PPFF::Tables::PPFFTableDirectory PPFF::Tables::PopulateOTFDirectory(const char*  FontPath)
{
    PPFF::Tables::PPFFTableDirectory Directory;
    FILE* FontFile = NULL; 
    fopen_s(&FontFile, FontPath, "rb");
    if(FontFile != NULL)
    {
        PPFF::Tables::GetTableHeader(Directory, FontFile);
        const char* record[2] = {"maxp", "CFF "};
        PPFF::Tables::GetTableRecords(Directory, FontFile, record, 2, false);
        PPFF::Tables::PPFFTableRecord CFFRecord = Directory.tableRecords["CFF "];
        char* tag = CFFRecord.Tag;
        uint32_t checksum = CFFRecord.checksum;
    }
    return Directory;
}


PPFF::Tables::PPFFTableDirectory PPFF::Tables::PopulateTTFDirectory(const char* FontPath)
{
    PPFF::Tables::PPFFTableDirectory Directory;
    FILE* FontFile = NULL; 
    fopen_s(&FontFile, FontPath, "rb");
    if(FontFile != NULL)
    {
        PPFF::Tables::GetTableHeader(Directory, FontFile);
        const char* record[5] = {"maxp","cmap", "glyf", "loca", "head"};
        PPFF::Tables::GetTableRecords(Directory, FontFile, record, 5, false);
    }
    return Directory;
}