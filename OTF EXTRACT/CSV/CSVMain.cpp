#include <iostream>
#include "CSVOpen.h"
#include "GenericKDTree/GKDTree.hpp"
int main()
{
    CSVDecompile Decompilation("C:/Users/Dust/Desktop/ChaseChecking.CSV");

    GKDTree<CSVCell> Tree(Decompilation.Entries, Decompilation.Categories.size(),Decompilation.Entries.size());
    
}