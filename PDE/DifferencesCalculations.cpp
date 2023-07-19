#include <iostream>

#include <string>
#include <vector>
#include <memory.h>
#include "FiniteDifferenceOneDimension.h"


int main()
{

    vec2 Domain = {0,1};
    double SpaceStepsRequired = 20; //Meters
    double TimeFinish = 0.05; //1 Hour

    double dt = 0.0013; //Seconds
    double dx = 1.0/SpaceStepsRequired; //Centimeters

    double t0 = 0.0; 
    double x0 = 0;
    double x1 = 0;

    double epsilon = (dt)/(dx*dx);


    int TDimension = (TimeFinish/dt);
    int XDimension = SpaceStepsRequired;

    double** results = new double*[TDimension];
    for (int i = 0; i < TDimension; i++) {
        results[i] = new double[XDimension];
    }

    for(int t = 0; t < TDimension; t++)
    {
        for(int s = 0; s < XDimension; s++)
        {
            if(s == 0)
            {
                results[t][s] = x0;
            }else if(s == (XDimension-1))
            {
                results[t][s] = x1;

            }else if(t == 0)
            {   

                double js = s/(float)XDimension;
                if(js >= 0 && js <= 1.0/2.0)
                {
                    results[t][s] = (2*js);
                }else if(js >= 1.0/2.0 && js <= 1.0)
                {
                    results[t][s] = (2-(2*js));
                }
            }else
            {
                double rightvalue = results[t-1][s+1];
                double leftvalue = results[t-1][s-1];
                double currentvalue = results[t-1][s];

                results[t][s] = currentvalue + (epsilon *(rightvalue - (2*currentvalue) + leftvalue ));
                
            }
        }
    }
    
    //forier expansion of the forward difference scheme using the formula,
    //add together the backward difference scheme with respect to x
    //delta 2x

    DrawResults(results, TDimension, XDimension, dt, dx, 25);
}