#include <iostream>

#include <string>
#include <vector>
#include <memory.h>
#include "FiniteDifferenceOneDimension.h"


struct vec3
{
    double x,y,t;
};




int main()
{
    
    vec2 Domain = {0,1};
    double SpaceStepsRequired = 20; //Meters
    double TimeFinish = 1.0; //1 Hour

    double dt = 0.05; //Seconds
    double dx = 1.0/SpaceStepsRequired; //Centimeters

    double t0 = 0.0; 
    double x0 = 0;
    double x1 = 0;

    double epsilon = (dt)/(dx*dx);


    int TDimension = (TimeFinish/dt);
    int XDimension = SpaceStepsRequired;

    double results[XDimension][TDimension];


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
    


    


    return 0;
}