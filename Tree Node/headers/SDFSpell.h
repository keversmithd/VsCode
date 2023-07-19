#ifndef SDF_SPELL_H
#define SDF_SPELL_H

#include "SDFBoundingPrimitives.h"
#include <string>
#include <iostream>

#include <windows.h>

std::string contextString;
char buffer[256];

bool SetClipboardText(const std::string& text) {
    if (OpenClipboard(nullptr)) {
        // Allocate global memory for the string
        HGLOBAL clipbuffer = GlobalAlloc(GMEM_DDESHARE, text.size() + 1);
        if (clipbuffer != nullptr) {
            // Lock and copy the string into global memory
            char* buffer = static_cast<char*>(GlobalLock(clipbuffer));
            if (buffer != nullptr) {
                strcpy_s(buffer, text.size() + 1, text.c_str());
                GlobalUnlock(clipbuffer);

                // Empty the clipboard and set the new text
                EmptyClipboard();
                if (SetClipboardData(CF_TEXT, clipbuffer) != nullptr) {
                    CloseClipboard();
                    return true;
                }
            }
        }

        CloseClipboard();
    }

    return false;
}

void SpellPoint(const SDFVec3 v3)
{
    std::snprintf(buffer, 256, "(%f,%f,%f)",v3.x, v3.y, v3.z);
    contextString += buffer;
}

void SpellPos(const SDFVec3 v3)
{
    std::snprintf(buffer, 256, "\\draw (%f,%f,%f) circle (5pt);\n",v3.x, v3.y, v3.z);
    contextString += buffer;

}

void AppendPoint(const SDFVec3 v3)
{
    std::snprintf(buffer, 256, "--(%f,%f,%f)",v3.x, v3.y, v3.z);
    contextString += buffer;
}

void SpellBoundingVolume(const SDFBoundingVolume volume)
{

    contextString += "\\draw ";
    SpellPoint({volume.TopLeftFront.x, volume.BottomRightBack.y, volume.TopLeftFront.z});
    AppendPoint({volume.BottomRightBack.x, volume.BottomRightBack.y, volume.TopLeftFront.z});
    AppendPoint({volume.BottomRightBack.x, volume.BottomRightBack.y, volume.BottomRightBack.z});
    AppendPoint({volume.TopLeftFront.x, volume.BottomRightBack.y, volume.BottomRightBack.z});
    contextString += "--cycle ";
    contextString += ";\n";


    contextString += "\\draw ";
    SpellPoint({volume.TopLeftFront.x, volume.TopLeftFront.y, volume.TopLeftFront.z});
    AppendPoint({volume.BottomRightBack.x, volume.TopLeftFront.y, volume.TopLeftFront.z});
    AppendPoint({volume.BottomRightBack.x, volume.TopLeftFront.y, volume.BottomRightBack.z});
    AppendPoint({volume.TopLeftFront.x, volume.TopLeftFront.y, volume.BottomRightBack.z});
    contextString += "--cycle ";
    contextString += ";\n";


    contextString += "\\draw ";
    SpellPoint({volume.TopLeftFront.x, volume.BottomRightBack.y, volume.TopLeftFront.z});
    AppendPoint({volume.TopLeftFront.x, volume.TopLeftFront.y, volume.TopLeftFront.z});
    contextString += "--cycle ";
    contextString += ";\n";

    contextString += "\\draw ";
    SpellPoint({volume.BottomRightBack.x, volume.BottomRightBack.y, volume.TopLeftFront.z});
    AppendPoint({volume.BottomRightBack.x, volume.TopLeftFront.y, volume.TopLeftFront.z});
    contextString += "--cycle ";
    contextString += ";\n";


    contextString += "\\draw ";
    SpellPoint({volume.TopLeftFront.x, volume.BottomRightBack.y, volume.BottomRightBack.z});
    AppendPoint({volume.TopLeftFront.x, volume.TopLeftFront.y, volume.BottomRightBack.z});
    contextString += "--cycle ";
    contextString += ";\n";


    contextString += "\\draw ";
    SpellPoint({volume.BottomRightBack.x, volume.BottomRightBack.y, volume.BottomRightBack.z});
    AppendPoint({volume.BottomRightBack.x, volume.TopLeftFront.y, volume.BottomRightBack.z});
    contextString += "--cycle ";
    contextString += ";\n";

    contextString += "\n\n";
}

void SpellTriangle(const SDFFace face)
{
    contextString += "\\draw ";
    SpellPoint(face.v0);
    AppendPoint(face.v1);
    AppendPoint(face.v2);
    contextString += "--cycle ";
    contextString += ";\n";

    contextString += "\n\n";
}


void DrawPoint(const SDFVec3 v3)
{
    printf("\\draw (%f,%f,%f) circle (5pt);\n", v3.x, v3.y, v3.z);
    std::cout <<  "\n\n\n\n";
}

void StartPath(const SDFVec3 v3)
{
    printf("\\draw (%f,%f,%f)", v3.x, v3.y, v3.z);
}

void EndPath(const SDFVec3 v3)
{
    printf(";\n");
}

void AppendPath(const SDFVec3 v3)
{
    printf("--(%f,%f,%f)", v3.x, v3.y, v3.z);
}

void DrawBoundingVolume(const SDFBoundingVolume volume)
{

    StartPath({volume.TopLeftFront.x, volume.BottomRightBack.y, volume.TopLeftFront.z});
    AppendPath({volume.BottomRightBack.x, volume.BottomRightBack.y, volume.TopLeftFront.z});
    AppendPath({volume.BottomRightBack.x, volume.BottomRightBack.y, volume.BottomRightBack.z});
    AppendPath({volume.TopLeftFront.x, volume.BottomRightBack.y, volume.BottomRightBack.z});
    std::cout << "--cycle;\n";
    



    StartPath({volume.TopLeftFront.x, volume.TopLeftFront.y, volume.TopLeftFront.z});
    AppendPath({volume.BottomRightBack.x, volume.TopLeftFront.y, volume.TopLeftFront.z});
    AppendPath({volume.BottomRightBack.x, volume.TopLeftFront.y, volume.BottomRightBack.z});
    AppendPath({volume.TopLeftFront.x, volume.TopLeftFront.y, volume.BottomRightBack.z});
    std::cout << "--cycle;\n";
    



    StartPath({volume.TopLeftFront.x, volume.BottomRightBack.y, volume.TopLeftFront.z});
    AppendPath({volume.TopLeftFront.x, volume.TopLeftFront.y, volume.TopLeftFront.z});
    std::cout << "--cycle;\n";
    


    StartPath({volume.BottomRightBack.x, volume.BottomRightBack.y, volume.TopLeftFront.z});
    AppendPath({volume.BottomRightBack.x, volume.TopLeftFront.y, volume.TopLeftFront.z});
    std::cout << "--cycle;\n";
    



    StartPath({volume.TopLeftFront.x, volume.BottomRightBack.y, volume.BottomRightBack.z});
    AppendPath({volume.TopLeftFront.x, volume.TopLeftFront.y, volume.BottomRightBack.z});
    std::cout << "--cycle;\n";
    



    StartPath({volume.BottomRightBack.x, volume.BottomRightBack.y, volume.BottomRightBack.z});
    AppendPath({volume.BottomRightBack.x, volume.TopLeftFront.y, volume.BottomRightBack.z});
    std::cout << "--cycle; \n";
    

    std::cout <<  "\n\n\n\n";
}



void BeginTexContext()
{
    contextString += "\\documentclass{article} \n \\usepackage{tikz} \n \\usepackage{graphicx} % Required for inserting images \n \\title{daf} \n \\author{Dustin Smith} \n \\date{July 2023}\n \\usetikzlibrary{calc}\n \\usepackage{relsize}\n \\usetikzlibrary{3d}\n \\tikzset{fontscale/.style = {font=\\relsize{#1}}\n } \\begin{document}\n \\begin{tikzpicture}[x={(-1cm,-0.6cm)}, y={(1cm,0cm)}, z={(0cm,1cm)},cube/.style={very thick,black}, grid/.style={very thin,gray}, axis/.style={->,blue,thick}] \\draw[axis] (0,0,0) -- (3,0,0) node[anchor=west]{$x$}; \n \\draw[axis] (0,0,0) -- (0,3,0) node[anchor=west]{$y$};\n \\draw[axis] (0,0,0) -- (0,0,3) node[anchor=west]{$z$}; \n";
}

void EndTexContent()
{
    contextString += "\\end{tikzpicture} \n \\end{document}";
    SetClipboardText(contextString);
}

#endif