#ifndef OOTELECTRONCONFIG_H
#define OOTELECTRONCONFIG_H
#include "102Constants.h"
#include "DTOuterQueue.h"

enum BlockType{ S = 0, D = 1, P = 2, F = 3};

struct OOTElectronShell
{
    BlockType ShellType;
    int principalNumber;
    int electronsInShell;
    double radius;
    OOTElectronShell(BlockType ShellType, const int& PrincipalNumber = 1, const int& ElectronsInShell = 1)
    { 
        principalNumber = PrincipalNumber;
        electronsInShell = ElectronsInShell;
        radius = BohrRadius * pow(PrincipalNumber,2);
    }

    ~OOTElectronShell()
    {

    }
};

struct OOTElectronConfiguration
{
private:
    DTOuterQueue<OOTElectronShell> Shells;
public:
    OOTElectronConfiguration() : Shells(2, 4){  }
    
    ~OOTElectronConfiguration(){ }
};

#endif