#ifndef THOMAS_MATRIX_H
#define THOMAS_MATRIX_H

#include "GEmat.h"


void AssembleMatrix() //work in progress
{
    float dx = 0.25;
    float J = 4;
    float dt = 0.5; //seconds
    float T = 2; //seconds
    int TSteps = T/dt;
    int XSteps = J/dx;
    float epsilon = dt/(dx*dx);
    GEmat eqSystem(J, J);
    GEmat iVector(J);
    iVector.fill(1.1);
    iVector[0] = 0;
    iVector[J-1] = 0;
    iVector.display();
    eqSystem.trigDown(-dx,(1+2*dx),-dx);
    eqSystem[0] = 0;
    eqSystem[15] = 0;
    eqSystem.display();
    Thomas(eqSystem, iVector);
    eqSystem.display();
    iVector.display();



}


#endif