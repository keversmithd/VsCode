#ifndef THOMAS_MATRIX_H
#define THOMAS_MATRIX_H

#include "GEmat.h"


void AssembleMatrix()
{

    float dx = 5;
    float J = 20;
    float dt = 0.5; //seconds
    float T = 2; //seconds
    int TSteps = T/dt;
    int XSteps = J/dx;
    float epsilon = dt/(dx*dx);
    GEmat eqSystem(XSteps, TSteps);
    GEmat iVector(XSteps);

    eqSystem.trigDown(-epsilon,(1+2*epsilon),-epsilon);
    
    eqSystem.display();



}


#endif