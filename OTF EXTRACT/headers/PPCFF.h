#ifndef PPCFF_H
#define PPCFF_H
#include "PPFFDebug.h"
#include "PPFFTables.h"

#include <functional>
namespace PPCFF
{


    struct PPCFFHeader
    {
        uint8_t major;
        uint8_t minor;
        uint8_t hdrSize;
        uint8_t OffSize;
    };
    struct PPCFFIndex
    {
        uint16_t count;
        uint8_t offSize;
        void* Offset;
        uint8_t* data;
        fpos_t End;
    };


    struct PPCFFExtractor
    {
        private:
            PPFF::Tables::PPFFTableDirectory CFFDirectory;
            PPFF::Tables::PPFFTableRecord CFFTable;
            PPCFFHeader CFFHeader;
            PPCFFIndex NameIndex;
            const char* FontPath;
        public:
            PPCFFExtractor(PPFF::Tables::PPFFTableDirectory CFFDirectory, const char* FontPath);
            int ExtractHeader();
            int ExtractNameIndex(bool ExtractOffsets, bool ExtractOffsets);
            ~PPCFFExtractor();


    };


    


}





#endif