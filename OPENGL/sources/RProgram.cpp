#include "RProgram.h"

char* RParse(const char* file)
{
    FILE* f;
    fopen_s(&f, file, "rb");
    if(f)
    {
        fpos_t endpos = 0;
        fseek(f, 0, SEEK_END);
        fgetpos(f, &endpos);
        fseek(f, 0, SEEK_SET);
        char* buffer = (char*)malloc(endpos+1);
        fread(buffer, endpos, 1, f);
        buffer[endpos] = '\0';
        fclose(f);
        return buffer;
    }
    else
    {
        printf("%s\n", "Warning file not readable, brace for corrupt memory.");
        return nullptr;
    }
}

