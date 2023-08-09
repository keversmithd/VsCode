#include <iostream>
#include <vector>
#include "SingularValueDecomposition/GEmat.h"
#include "ThomasMatrix.h"

int main()
{

    AssembleMatrix();

    int J = 20;
    float dt = 0.5;

    std::vector<float> dj(J);
    dj.assign(J, 4);

    std::vector<float> eVals;
    eVals.push_back(0);
    std::vector<float> fVals;
    fVals.push_back(0);

    float dx = dt/((1.0f/J)*(1.0f/J));
    float a = -dx;
    float b = (1+2*dx);
    float c = -dx;

    for(int j = 1; j < J-1; j++)
    {
        eVals.push_back(c/(b-a*eVals[j-1]));
        fVals.push_back((dj[j] + a*fVals[j-1])/2-eVals[j-1]);
    }

    eVals.push_back(0);
    fVals.push_back(0);

    std::vector<float> U(J);
    U[0] = 0;
    U[J-1] = 0;

    for(int i = J-2; i >= 0; i--)
    {
        U[i] = fVals[i]-U[i+1]*eVals[i];
    }
    



}