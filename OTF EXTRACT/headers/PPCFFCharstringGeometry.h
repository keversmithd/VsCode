#ifndef PPCFF_CHAR_STRING_GEOM
#define PPCFF_CHAR_STRING_GEOM 
#include "PPCFF.h"
#include <windows.h>


#pragma region VECTOR_H
struct PPCFFVec2
{
    float x,y;

    PPCFFVec2(const Vectoid2 ivec2)
    {
        x = ivec2.x;
        y = ivec2.y;
    }

    PPCFFVec2(float _x, float _y)
    {
        x = _x;
        y = _y;
    }

    ~PPCFFVec2()
    {

    }
};
#pragma endregion

#pragma region Sampling_AGENTS
PPCFFVec2 SampleCubic(PPCFF::Line CubicInformation, float t)
{
    return {powf((1-t),3)*CubicInformation.A.x + 3*powf((1-t),2)*t*CubicInformation.B.x + 3*(1-t)*powf(t,2)*CubicInformation.C.x + powf(t,3)*CubicInformation.D.x,
            powf((1-t),3)*CubicInformation.A.y + 3*powf((1-t),2)*t*CubicInformation.B.y + 3*(1-t)*powf(t,2)*CubicInformation.C.y + powf(t,3)*CubicInformation.D.y};
}

PPCFFVec2 SampleQuadratic(PPCFF::Line QuadraticInformation, float t)
{
    return {powf((1-t),2)*QuadraticInformation.A.x + 2*(1-t)*t*QuadraticInformation.C.x + powf(t,2)*QuadraticInformation.C.x,
    powf((1-t),2)*QuadraticInformation.A.y + 2*(1-t)*t*QuadraticInformation.C.y + powf(t,2)*QuadraticInformation.C.y};
}
#pragma endregion

void GeometrizeCharstring(PPCFF::PPCFFCharstring& Charstring, int Resolution, std::vector<PPCFFVec2>& Geometry)
{
    float step = 1.0f/Resolution;
    for(int i = 0; i < Charstring.Lines.size(); i++)
    {
        switch(Charstring.Lines[i].curveType)
        {
            case PPCFF::PPCFF_LINE:

                //printf("\\draw[fill = black] (%d,%d) -- (%d,%d);\n", Charstring.Lines[i].A.x, Charstring.Lines[i].A.y, Charstring.Lines[i].B.x, Charstring.Lines[i].B.y);
                Geometry.push_back(Charstring.Lines[i].A);
                Geometry.push_back(Charstring.Lines[i].B);

                break;
            case PPCFF::PPCFF_QUADRATIC:
                for(int j = 0; j <= Resolution; j++)
                {
                    Geometry.push_back(SampleQuadratic(Charstring.Lines[i], j*step));
                }
                break;
            case PPCFF::PPCFF_CUBIC:
                for(int j = 0; j <= Resolution; j++)
                {
                    PPCFFVec2 Geom = SampleCubic(Charstring.Lines[i], j*step);
                    //printf("\\draw[fill = black] (%f,%f) circle (1pt);\n", Geom.x, Geom.y);
                    Geometry.push_back(Geom);
                }
                break;
            default:
                break;


        }

    }


    // for(int i = 0; i < Geometry.size()-1; i++)
    // {
    //     printf("\\draw[fill = black] (%f,%f) -- (%f,%f);\n", Geometry[i].x, Geometry[i].y, Geometry[i+1].x,  Geometry[i+1].y);
    // }

    

}

std::string CurrentDirectoryWindows()
{
    CHAR buffer[255];
    GetCurrentDirectory(255,buffer);
    // char Buffer[255];
    // wcstombs(Buffer, buffer, 255);
    return buffer;
}

void SaveToFile(std::vector<PPCFFVec2>& Geometry, std::string source)
{
    std::string filepath = CurrentDirectoryWindows()+"\\"+source;

    FILE* F;
    fopen_s(&F, filepath.c_str(), "w");
    int s = Geometry.size();
    fprintf(F, "%d\n", s);
    
    for(int i = 0; i < Geometry.size(); i++)
    {
        fprintf(F, "%f %f\n", Geometry[i].x, Geometry[i].y);
    }


    fclose(F);
}

void ReadFromFile(std::string source, std::vector<PPCFFVec2>& ExportedGeometry)
{
    std::string filepath = CurrentDirectoryWindows()+"\\"+source;

    FILE* F;
    fopen_s(&F, filepath.c_str(), "rb");
    
    int size;
    fscanf(F, "%d\n", &size);
    //ExportedGeometry.reserve(size);
    
    for(int i = 0; i < size; i++)
    {
        float x,y;
        fscanf(F, "%f %f\n", &x, &y);
        ExportedGeometry.push_back({x,y});
        // fread(&ExportedGeometry[i].x, sizeof(float), 1, F);
        // fread(&ExportedGeometry[i].y, sizeof(float), 1, F);
    }


    fclose(F);
}

void DisplayGeometry(std::vector<PPCFFVec2>& Geometry)
{
    printf("std::vector<vec2> vertices = {\n");
    for(int i = 0; i < Geometry.size(); i++)
    {
        printf("{%f,%f},\n", Geometry[i].x, Geometry[i].y);
    }
    printf("};\n");
}

#endif