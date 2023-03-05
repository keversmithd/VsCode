#ifndef OOTE_H
#define OOTE_H
struct OOTElement{
	int AtomicNumber;
	const char* Symbol;
	const char* EnglishName;
	int Group;
	int Period;
	const char* Block;
	int Category;
	double AtomicMass;
	const char* Configuration;
	const char* ShellConfiguration;
	int StandardState;
	double Density;
	double MeltingPoint;
	double BoilingPoint;
	double HeatCapacity;
	double HeatOfFusion;
	double HeatOfVaporization;
	double AtomicRadius;
	double CovalentRadius;
	double VanDerWaalsRadius;
	double Electronegativity;
	const char* OxidationStates;
	double IonizationEnergy;
	double ThermalConductivity;
	double ElectronAffinity;
	double AbundanceCrust;
	double AbundanceUniverse;
	double Discovery;
	bool Radioactive;
	const char* DiscoveredBy;
};
#endif
