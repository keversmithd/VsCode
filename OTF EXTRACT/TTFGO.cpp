#include <iostream>
#include <stdio.h>

#include "PPFFontClassification.h"
#include "PPFFTables.h"
#define WS "X:\\1.4 C++\\Vscode\\OTF EXTRACT\\"
#include "IndexSort.h"
#include "PPCFF.h"
#include "PPTFF/PPTF.h"
using namespace PPFF::FontClassification;

using namespace PPCFF;
using namespace PPFF::Tables;




void RecordCmapSpan(const char** sources, int length)
{
    for(int i = 0; i < length; i++)
    {
        PPFFTableDirectory Table = PopulateTTFDirectory(sources[i]);
        TTFExtractor Extractor(Table, sources[i]);
    }
}

int main()
{

    const char* fontfiles[] = {
        "C:\\Users\\Dust\\Desktop\\exo.regular.otf",
        "C:\\Users\\Dust\\Desktop\\BriosoPro Italic.otf"
        "C:\\Users\\Dust\\Desktop\\Joan-Regular.ttf"
        "C:\\Users\\Dust\\Desktop\\NotoSansJP-Regular.otf"
        "C:\\Users\\Dust\\Desktop\\NotoSansJP-Thin.otf"
    };

    PPFFTableDirectory Table = PopulateTTFDirectory("C:\\Users\\Dust\\Desktop\\Joan-Regular.ttf");

    TTFExtractor Extractor(Table, "C:\\Users\\Dust\\Desktop\\Joan-Regular.ttf");

    Extractor.ExtractMaxP();
    Extractor.ExtractHead();
    Extractor.ExtractLoca();
    Extractor.ExtractCmap();
    Extractor.ExtractGlyf();

    



    return 1;
}