#include <iostream>
#include "GEmat3.h"
int main()
{
    // GEmat3 Stiffness = {1, 1, -1, 2, -1, 1, -1, 2, 2};
    // GEvec3 Mode = {-2,5,1};
    // Stiffness.display();

    // GEmat3vec3 Result = gaussian(Stiffness, Mode);
    // GEmat3vec3 Result2 = gaussian_one(Stiffness, Mode);

    // Result2.A.display();
    // Result2.B.display();
    // Result.A.display();
    // Result.B.display();


    GEmat3 Stiffness = {2, 1, -1, 3, 2, 1, 2, -1, 2};
    GEvec3 Mode = {1,10,6};
    //Stiffness.display();
    GEmat3vec3 GaussJordan  = gaussian(Stiffness, Mode);
    printf("Gauss Jordan\n");
    GaussJordan.A.display();
    GaussJordan.B.display();

    printf("Gaussian Elimination\n");
    GEmat3vec3 Result = gaussian_one(Stiffness, Mode);
    Result.A.display();
    Result.B.display();

    //GEmat3LU DECOMP = LU(Stiffness, Mode);
    GEvec3 X = LUYX(Stiffness, Mode);



    X.display();


    // DECOMP.L.display();
    // DECOMP.U.display();



}
