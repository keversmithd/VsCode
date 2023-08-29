#include <iostream>
#include <vector>
#include "SingularValueDecomposition/GEmat.h"
#include "ThomasMatrix.h"
#include "FiniteDifferenceOneDimension.h"

void DrawResults(std::vector<float> U, float dx)
{
    
    float maxy = U[0];
    float miny = U[0];

    for(int i = 0; i < U.size(); i++)
    {
        printf("\\draw[fill = black] (%f,%f) circle(1pt);\n",  dx*i, U[i]);
        maxy = (U[i] > maxy) ? U[i] : maxy;
        miny = (U[i] < miny) ? U[i] : miny;
    }

    printf("\\draw[step=%f] (%f,%f) grid (%f,%f);", dx, 0, miny, dx*U.size(),maxy);

}

int main()
{
    //SecondCentralDifferences();
    AssembleMatrix();

    int J = 20;
    float tf = 0.05;
    float dx = 1.0/J;

    std::vector<float> dj(J);
    dj.assign(J, 1.1);
    dj[J-1] = 0;

    std::vector<float> eVals;
    eVals.push_back(0);
    std::vector<float> fVals;
    fVals.push_back(0);

    float a = -dx;
    float b = (1+2*dx);
    float c = -dx;


    for(int j = 1; j < J-1; j++)
    {
        eVals.push_back(c/(b-(a*eVals[j-1])));
        fVals.push_back((dj[j] + a*fVals[j-1])/(b - a*eVals[j-1]));
    }

    eVals.push_back(0);
    fVals.push_back(0);

    for(int i = J-2; i >= 0; i--)
    {
        dj[i] = fVals[i]+eVals[i]*dj[i+1];
    }

    DrawResults(dj, dx);

    

    
}