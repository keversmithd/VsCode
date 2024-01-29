#include <iostream>
#include "DifferentialTree.h"
#include <Windows.h>
int main()
{

    //DLL Test
    
    
    IntegralSymbolTable SymbolTable;
    SymbolTable.OperandTable.set("x y cos");
    SymbolTable.OperatorTable.insertdefault();
    IntegralTree IntegralTimeAlmost("2*x + cos(2x - 4y)");


}