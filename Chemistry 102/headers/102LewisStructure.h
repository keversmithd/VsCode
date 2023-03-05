#pragma once
#include "math.h"
#include "102Elements.h"
#include "DTOuterQueue.h"

#pragma region OOT_BOND_LENGTH_R
typedef double(*OOTBondSystem)(const int* BondTypes, const int& BondCount, const float& atomic_radius1, const float& atomic_radius2, const float& ionic_charge1, const float& ionic_charge2);

enum OOTBondType
{
    IONIC_BOND = 0, COVALENT_BOND = 1, TYPICAL_BOND = 2, AROMATIC_BOND = 3
};

double OOTionic_bond_length(const int* BondTypes, const int& BondCount, const float& atomic_radius1, const float& atomic_radius2, const float& ionic_charge1, const float& ionic_charge2)
{
    return (atomic_radius1 + atomic_radius2) - 0.3*pow((ionic_charge1 + ionic_charge2),1/2);
}
double OOTcovalent_bond_length(const int* BondTypes, const int& BondCount, const float& atomic_radius1, const float& atomic_radius2, const float& ionic_charge1, const float& ionic_charge2)
{
    double BondCoefficent[4] = {1.0, 0.31, 0.77, 0.75};
    return 0.9 * (atomic_radius1 + atomic_radius2) * BondCoefficent[BondTypes[0]];
}
double OOTtypical_bond_length(const int* BondTypes, const int& BondCount, const float& atomic_radius1, const float& atomic_radius2, const float& ionic_charge1, const float& ionic_charge2)
{
    double BondCoefficent[4] = {1.0, 0.31, 0.77, 0.75};
    return (atomic_radius1 + atomic_radius2) * BondCoefficent[BondTypes[0]];
}
double OOTaromatic_bond_length(const int* BondTypes, const int& BondCount, const float& atomic_radius1, const float& atomic_radius2, const float& ionic_charge1, const float& ionic_charge2)
{
    double value = 0;
    for(int i = 0; i < BondCount; i++)
    {
        value += OOTtypical_bond_length(BondTypes, BondCount, atomic_radius1, atomic_radius2, ionic_charge1, ionic_charge2);
    }
    return value/BondCount;
}
const OOTBondSystem ExcersizeRadius[4]
{
    OOTionic_bond_length, OOTcovalent_bond_length, OOTtypical_bond_length, OOTaromatic_bond_length
};
double OOTbond_length(const OOTBondType& BondSpecification, const int* BondTypes, const int& BondCount, const float& atomic_radius1, const float& atomic_radius2, const float& ionic_charge1, const float& ionic_charge2)
{
    return ExcersizeRadius[BondSpecification](BondTypes, BondCount, atomic_radius1, atomic_radius2, ionic_charge1, ionic_charge2);
}
#pragma endregion

struct OOTLewisMolecular3D
{
    float x, y, z;
};
struct OOTLewisMolecularNode;
struct OOTLewisMolecularEdge
{
    OOTLewisMolecularNode* next;
    int BondType;
    double BondAngleTHETA;
    double BondAnglePHI;
    double BondLength;
    OOTLewisMolecularNode* prev;
};
struct OOTLewisMolecularNode
{
    OOTElement Element;
    OOTLewisMolecular3D Position;
    DTOuterQueue<OOTLewisMolecularEdge> Edges;
    int FormalCharge;
    int LonePairElectrons;
    int Hybridization;
};



