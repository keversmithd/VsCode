#include <iostream>
#include "GEmat2.h"

int main()
{


    GEmat2 Stiffness = gemat2(1,-1,-1,1);
    GEvec2 Load = {1,2}; 
    GEmat2vec2 GaussJordanPackage = gaussjordan(Stiffness,Load);
    int Status = CheckConsistency(Stiffness);
    GEmat2 GaussF = gaussJordanF(Stiffness, Load);

    GEmat2 Inverse = inverse(Stiffness);

    GaussJordanPackage.A.display();
    GaussF.display();
    GaussJordanPackage.B.display();
    Inverse.display();
    (Inverse*Load).display();


}