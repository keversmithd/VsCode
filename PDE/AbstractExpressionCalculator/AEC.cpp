#include <iostream>
#include <string>
#include "AECTree.h"
#include "viewtree.hpp"
#include "POPFix.h"


int main()
{

    // std::cout << "Welcome to interactive inter expression reader parser." << std::endl;
    // std::cout << "Parsing A Simple Function Test 1" << std::endl;

    // std::string Ux =  "512x^4+3 + sin(2x * 12) + cos(3x * 12)";
    
    // AECTree U(Ux);

    // view_tree<AECTreeNode*, AECTreeNode*>7(U.root.top(), U.Elements);
       std::string Ux = "y^2 + 48"; 
       std::string Uy = "512/(12y^(2x + 48)) + cos(cos(415x))";

       POPExpression U(Ux);
       U.evaluate('y', 2);
       U.readExpression();

    

    

}