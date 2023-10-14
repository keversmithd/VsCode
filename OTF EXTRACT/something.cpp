#include <iostream>
#include <stdio.h>

#include "PPFFontClassification.h"
#include "PPFFTables.h"
#define WS "X:\\1.4 C++\\Vscode\\OTF EXTRACT\\"
#include "IndexSort.h"
#include "PPCFF.h"
#include "PPCFFCharstringGeometry.h"

using namespace PPFF::FontClassification;

using namespace PPCFF;
using namespace PPFF::Tables;
int main()
{

        //STILL NO GLOBAL SUBROUTINES, NOT FINISHED ALL THE THINGS.
      //   PPFFTableDirectory Table = PopulateOTFDirectory("C:\\Users\\Dust\\Desktop\\exo.regular.otf");
      //   PPCFFExtractor Extractor(Table, "C:\\Users\\Dust\\Desktop\\exo.regular.otf");

      //   Extractor.ExtractHeader();
      //   Extractor.ExtractNameIndex(false);
      //   Extractor.ExtractTopDictIndex();
      //   Extractor.DecodeTopDictData();
      //   Extractor.DecodePrivateDict();

      //   Extractor.ExtractSubroutines();

      //   Extractor.ExtractCharstrings();
      //   PPCFFCharstring pc = Extractor.DecodeSingularCharstring();
      std::vector<PPCFFVec2> Geometry;
      //   GeometrizeCharstring(pc, 5, Geometry);
      //  SaveToFile(Geometry, "chardata.txt");
       ReadFromFile("chardata.txt", Geometry);
       DisplayGeometry(Geometry);

    return 1;
}