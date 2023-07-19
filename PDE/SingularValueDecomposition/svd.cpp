#include <iostream>

#include "GEMat.h"



int main()
{
    GEmat z(1,3);
    z = {0.422650,-0.566,-0.566};
    GEmat b(3,1);
    b = {-1.73,-3.46,-5.196};
    
    (z * b).display();


    int i = 0;

    GEmat y(3,3);

    y = {1,2,3,1,2,3,1,2,3};
    y.display();

    pyqr(y);




    







    return 0;

    


}