#include <iostream>
#include <string>
#include "AECTree.h"
#include "POPFix.h"
#include "viewtree.hpp"


int main()
{

    // std::cout << "Welcome to interactive inter expression reader parser." << std::endl;
    // std::cout << "Parsing A Simple Function Test 1" << std::endl;

    std::string Ux =  "cos(processedSamples)";

    POPExpression function;
    function.Parse("5*cos(2)");
    double _multiVal = function.multival({{"processedSamples", 22}, {"sampleRate", 0}});

    printf("_multiVal%f\n", _multiVal);
}