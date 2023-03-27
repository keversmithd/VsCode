#include <iostream>
#include <stdio.h>

#include "PPFFontClassification.h"
#include "PPFFTables.h"
#define WS "X:\\1.4 C++\\Vscode\\OTF EXTRACT\\"
#include "IndexSort.h"
#include "PPCFF.h"
using namespace PPFF::FontClassification;

int main()
{
    char* FontFilePath = WS "NotoSansJP-Regular.otf";

    SupportedFileType FontType = GetFileType(FontFilePath);
    unsigned int SupportFontIndex = SupportedFileTypeIndex(FontType);
    
    PPFF::Tables::PPFFTableDirectory CFFDirectory = PPFF::Tables::PopulateOTFDirectory(FontFilePath);
    PPCFF::PPCFFExtractor CFFExtractor(CFFDirectory, FontFilePath);
    CFFExtractor.ExtractHeader();
    CFFExtractor.ExtractNameIndex(true);
    CFFExtractor.ExtractTopDictIndex();
    CFFExtractor.DecodeTopDictData();
    //CFFExtractor.ExtractStringIndex();
    CFFExtractor.ExtractCharsets();
    CFFExtractor.ExtractCharstrings();
    
    
    
    
    
    return 1;

}