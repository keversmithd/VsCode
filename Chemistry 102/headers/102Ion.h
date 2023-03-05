#ifndef OOTION_H
#define OOTION_H
#include <vector>
#include "102Elements.h"
#include "102ElementArray.h"
#include <iostream>

struct OOTAtomicOrbital
{
    
};

struct OOTElectronConfiguration
{
    //full extend electron configuration
};

struct OOTAtom : OOTElement
{
    //inherits from element, but also has other values, like an electorn configuration
    //updated ionization energies
};

struct OOTIon
{
    //Also considered a point charge
    //because the monoatomic ion, or poly atomic ion has greater or less electrons than protons,
    std::vector<OOTAtom> Atoms;
    bool polyatomic;
    bool monoatomic;
    float charge;
    bool cation; //positively charged ion with fewer electrons than protons, in essence, lost electrons to become an ion
    bool anion; //is a negatively charged ion with more electrons than protons, in bonding essence, gained electrons to become an ion
};

struct OOTChemicalCompound
{
    std::vector<OOTAtom> Atoms;
};


struct OOTElectrostaticForces; //the forces attracting two ions
struct OOTIonicBond; //a type chemical bond that involves electrostatic attratcion or sharp electronegativites.
//factors that play into the bond are relative electronegativities, relative ionization energies, electron affinities, geometry, crystal structure, coordination number, surrounding counterion,
//and the distance is usally large.
//typically formed between metal and non metal.
struct OOTIonicCompound
{
    
    std::vector<OOTIon> Cations;
    std::vector<OOTIon> Anions;
    std::vector<OOTElectrostaticForces> Forces;


};

#endif