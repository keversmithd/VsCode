#include <iostream>

#include "GEMat.h"
#include "GEMatd.h"


int main()
{
    

    GEmatd y(2,4);

    y[0] = 1;

    y = {2,1,4,3,6,5,8,7};

    GEmatd O = OctaveVector({1,2,8}, 4);
    O.display();

    y.display();

    GEmatd P = PermutationOfColumn(y, GEmatd({2,1}));

    

    P.display();




    







    return 0;

    


}