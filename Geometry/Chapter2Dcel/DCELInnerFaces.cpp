
#include <iostream>
#include <stdio.h>

#include "DCEL.h"

int main()
{

    std::vector<vec2> MeshWithInnerFace = {
        {4,0},
        {4,30},
        {15,30},
        {56,36},
        {75,45},
        {327,665},
        {312,707},
        {394,737},
        {645,46},
        {665,36},
        {709,30},
        {721,30},
        {721,0},
        {464,0},
        {464,30},
        {478,30},
        {530,36},
        {552,46},
        {478,249},
        {216,249},
        {133,46},
        {156,36},
        {207,30},
        {221,30},
        {221,0},
        {4,0},
        {-69,-69},
        {237,300},
        {460,300},
        {355,589},
        {237,300},
    };

    printf("Update DCEL implementation to contain access to inner faces, distinguish between interior and exterior boundaries.");

    //Iterate through 12 vertice | Test topology viewer.

    DCEL LetterTypography;

    for(int i = 0; i < MeshWithInnerFace.size(); i++)
    {
        LetterTypography.FaceExtraAppendPoint(MeshWithInnerFace[i]);
    }

    LetterTypography.MakeLoopOnActiveFace();

    
    LetterTypography.DCELTopologyToLatex();


}