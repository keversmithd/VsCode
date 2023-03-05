#ifndef OOTES_H
#define OOTES_H
#include "102Element.h"

struct Hydrogen : OOTElement{
	Hydrogen()
	{
		AtomicNumber = 1; 
		Symbol = "H"; 
		EnglishName = "Hydrogen"; 
		Group = 1; 
		Period = 1; 
		Block = "s"; 
		Category = 0; 
		AtomicMass = 1.008; 
		Configuration = "1s1"; 
		ShellConfiguration = "1,,,,,,"; 
		StandardState = 0; 
		Density = 0.00008988; 
		MeltingPoint = 14.01; 
		BoilingPoint = 20.28; 
		HeatCapacity = 14.304; 
		HeatOfFusion = 0.117; 
		HeatOfVaporization = 0.904; 
		AtomicRadius = 53; 
		CovalentRadius = 38; 
		VanDerWaalsRadius = 120; 
		Electronegativity = 2.2; 
		OxidationStates = "1"; 
		IonizationEnergy = 1312; 
		ThermalConductivity = 0.1805; 
		ElectronAffinity = 72.769; 
		AbundanceCrust = 1400; 
		AbundanceUniverse = 75; 
		Discovery = 1766; 
		Radioactive = 0; 
		DiscoveredBy = "H. Cavendish"; 
	}
};
struct Helium : OOTElement{
	Helium()
	{
		AtomicNumber = 2; 
		Symbol = "He"; 
		EnglishName = "Helium"; 
		Group = 18; 
		Period = 1; 
		Block = "s"; 
		Category = 7; 
		AtomicMass = 4.002602; 
		Configuration = "1s2"; 
		ShellConfiguration = "2,,,,,,"; 
		StandardState = 0; 
		Density = 0.0001785; 
		MeltingPoint = (int)'N'; 
		BoilingPoint = 4.22; 
		HeatCapacity = 5.193; 
		HeatOfFusion = 0.0138; 
		HeatOfVaporization = 0.0829; 
		AtomicRadius = 31; 
		CovalentRadius = 32; 
		VanDerWaalsRadius = 140; 
		Electronegativity = (int)'N'; 
		OxidationStates = "0"; 
		IonizationEnergy = 2372.3; 
		ThermalConductivity = 0.1513; 
		ElectronAffinity = -50; 
		AbundanceCrust = 0.008; 
		AbundanceUniverse = 23; 
		Discovery = 1868; 
		Radioactive = 0; 
		DiscoveredBy = "P. Janssen, N. Lockyer"; 
	}
};
struct Lithium : OOTElement{
	Lithium()
	{
		AtomicNumber = 3; 
		Symbol = "Li"; 
		EnglishName = "Lithium"; 
		Group = 1; 
		Period = 2; 
		Block = "s"; 
		Category = 1; 
		AtomicMass = 6.94; 
		Configuration = "[He] 2s1"; 
		ShellConfiguration = "2,1,,,,,"; 
		StandardState = 2; 
		Density = 0.534; 
		MeltingPoint = 453.69; 
		BoilingPoint = 1560; 
		HeatCapacity = 3.582; 
		HeatOfFusion = 3; 
		HeatOfVaporization = 136; 
		AtomicRadius = 167; 
		CovalentRadius = 134; 
		VanDerWaalsRadius = 182; 
		Electronegativity = 0.98; 
		OxidationStates = "1"; 
		IonizationEnergy = 520.2; 
		ThermalConductivity = 84.8; 
		ElectronAffinity = 59.632; 
		AbundanceCrust = 20; 
		AbundanceUniverse = 0.0000006; 
		Discovery = 1817; 
		Radioactive = 0; 
		DiscoveredBy = "A. Arfwedson"; 
	}
};
struct Beryllium : OOTElement{
	Beryllium()
	{
		AtomicNumber = 4; 
		Symbol = "Be"; 
		EnglishName = "Beryllium"; 
		Group = 2; 
		Period = 2; 
		Block = "s"; 
		Category = 2; 
		AtomicMass = 9.0121831; 
		Configuration = "[He] 2s2"; 
		ShellConfiguration = "2,2,,,,,"; 
		StandardState = 2; 
		Density = 1.85; 
		MeltingPoint = 1560; 
		BoilingPoint = 2742; 
		HeatCapacity = 1.825; 
		HeatOfFusion = 7.895; 
		HeatOfVaporization = 292; 
		AtomicRadius = 112; 
		CovalentRadius = 90; 
		VanDerWaalsRadius = 153; 
		Electronegativity = 1.57; 
		OxidationStates = "2"; 
		IonizationEnergy = 899.5; 
		ThermalConductivity = 200; 
		ElectronAffinity = -50; 
		AbundanceCrust = 2.8; 
		AbundanceUniverse = 0.0000001; 
		Discovery = 1798; 
		Radioactive = 0; 
		DiscoveredBy = "N. Vauquelin"; 
	}
};
struct Boron : OOTElement{
	Boron()
	{
		AtomicNumber = 5; 
		Symbol = "B"; 
		EnglishName = "Boron"; 
		Group = 13; 
		Period = 2; 
		Block = "p"; 
		Category = 5; 
		AtomicMass = 10.81; 
		Configuration = "[He] 2s2 2p1"; 
		ShellConfiguration = "2,3,,,,,"; 
		StandardState = 2; 
		Density = 2.34; 
		MeltingPoint = 2349; 
		BoilingPoint = 4200; 
		HeatCapacity = 1.026; 
		HeatOfFusion = 50.2; 
		HeatOfVaporization = 508; 
		AtomicRadius = 87; 
		CovalentRadius = 82; 
		VanDerWaalsRadius = 192; 
		Electronegativity = 2.04; 
		OxidationStates = "3"; 
		IonizationEnergy = 800.6; 
		ThermalConductivity = 27.4; 
		ElectronAffinity = 26.989; 
		AbundanceCrust = 10; 
		AbundanceUniverse = 0.0000001; 
		Discovery = 1808; 
		Radioactive = 0; 
		DiscoveredBy = "L. Gay-Lussac, L.J. Thénard"; 
	}
};
struct Carbon : OOTElement{
	Carbon()
	{
		AtomicNumber = 6; 
		Symbol = "C"; 
		EnglishName = "Carbon"; 
		Group = 14; 
		Period = 2; 
		Block = "p"; 
		Category = 0; 
		AtomicMass = 12.011; 
		Configuration = "[He] 2s2 2p2"; 
		ShellConfiguration = "2,4,,,,,"; 
		StandardState = 2; 
		Density = 2.267; 
		MeltingPoint = 3800; 
		BoilingPoint = 4300; 
		HeatCapacity = 0.709; 
		HeatOfFusion = 117; 
		HeatOfVaporization = (int)'N'; 
		AtomicRadius = 67; 
		CovalentRadius = 77; 
		VanDerWaalsRadius = 170; 
		Electronegativity = 2.55; 
		OxidationStates = "-4,-3,-2,-1,0,1,2,3,4"; 
		IonizationEnergy = 1086.5; 
		ThermalConductivity = 140; 
		ElectronAffinity = 121.776; 
		AbundanceCrust = 200; 
		AbundanceUniverse = 0.5; 
		Discovery = -3750; 
		Radioactive = 0; 
		DiscoveredBy = (const char*)"NULL"; 
	}
};
struct Nitrogen : OOTElement{
	Nitrogen()
	{
		AtomicNumber = 7; 
		Symbol = "N"; 
		EnglishName = "Nitrogen"; 
		Group = 15; 
		Period = 2; 
		Block = "p"; 
		Category = 0; 
		AtomicMass = 14.007; 
		Configuration = "[He] 2s2 2p3"; 
		ShellConfiguration = "2,5,,,,,"; 
		StandardState = 0; 
		Density = 0.0012506; 
		MeltingPoint = 63.15; 
		BoilingPoint = 77.36; 
		HeatCapacity = 1.04; 
		HeatOfFusion = 0.72; 
		HeatOfVaporization = 5.57; 
		AtomicRadius = 56; 
		CovalentRadius = 75; 
		VanDerWaalsRadius = 155; 
		Electronegativity = 3.04; 
		OxidationStates = "-3,2,3,4,5"; 
		IonizationEnergy = 1402.3; 
		ThermalConductivity = 0.02583; 
		ElectronAffinity = -0.07; 
		AbundanceCrust = 19; 
		AbundanceUniverse = 0.1; 
		Discovery = 1772; 
		Radioactive = 0; 
		DiscoveredBy = "D. Rutherford"; 
	}
};
struct Oxygen : OOTElement{
	Oxygen()
	{
		AtomicNumber = 8; 
		Symbol = "O"; 
		EnglishName = "Oxygen"; 
		Group = 16; 
		Period = 2; 
		Block = "p"; 
		Category = 0; 
		AtomicMass = 15.999; 
		Configuration = "[He] 2s2 2p4"; 
		ShellConfiguration = "2,6,,,,,"; 
		StandardState = 0; 
		Density = 0.001429; 
		MeltingPoint = 54.36; 
		BoilingPoint = 90.2; 
		HeatCapacity = 0.918; 
		HeatOfFusion = 0.444; 
		HeatOfVaporization = 6.82; 
		AtomicRadius = 48; 
		CovalentRadius = 73; 
		VanDerWaalsRadius = 152; 
		Electronegativity = 3.44; 
		OxidationStates = "-2"; 
		IonizationEnergy = 1313.9; 
		ThermalConductivity = 0.02658; 
		ElectronAffinity = 140.976; 
		AbundanceCrust = 461000; 
		AbundanceUniverse = 1; 
		Discovery = 1771; 
		Radioactive = 0; 
		DiscoveredBy = "W. Scheele"; 
	}
};
struct Fluorine : OOTElement{
	Fluorine()
	{
		AtomicNumber = 9; 
		Symbol = "F"; 
		EnglishName = "Fluorine"; 
		Group = 17; 
		Period = 2; 
		Block = "p"; 
		Category = 6; 
		AtomicMass = 18.99840316; 
		Configuration = "[He] 2s2 2p5"; 
		ShellConfiguration = "2,7,,,,,"; 
		StandardState = 0; 
		Density = 0.001696; 
		MeltingPoint = 53.53; 
		BoilingPoint = 85.03; 
		HeatCapacity = 0.824; 
		HeatOfFusion = 0.51; 
		HeatOfVaporization = 6.62; 
		AtomicRadius = 42; 
		CovalentRadius = 71; 
		VanDerWaalsRadius = 147; 
		Electronegativity = 3.98; 
		OxidationStates = "-1"; 
		IonizationEnergy = 1681; 
		ThermalConductivity = 0.0277; 
		ElectronAffinity = 328.164; 
		AbundanceCrust = 585; 
		AbundanceUniverse = 0.00004; 
		Discovery = 1810; 
		Radioactive = 0; 
		DiscoveredBy = "A.-M. Ampère"; 
	}
};
struct Neon : OOTElement{
	Neon()
	{
		AtomicNumber = 10; 
		Symbol = "Ne"; 
		EnglishName = "Neon"; 
		Group = 18; 
		Period = 2; 
		Block = "p"; 
		Category = 7; 
		AtomicMass = 20.1797; 
		Configuration = "[He] 2s2 2p6"; 
		ShellConfiguration = "2,8,,,,,"; 
		StandardState = 0; 
		Density = 0.0008999; 
		MeltingPoint = 24.56; 
		BoilingPoint = 27.07; 
		HeatCapacity = 1.03; 
		HeatOfFusion = 0.335; 
		HeatOfVaporization = 1.71; 
		AtomicRadius = 38; 
		CovalentRadius = 69; 
		VanDerWaalsRadius = 154; 
		Electronegativity = (int)'N'; 
		OxidationStates = "0"; 
		IonizationEnergy = 2080.7; 
		ThermalConductivity = 0.0491; 
		ElectronAffinity = -120; 
		AbundanceCrust = 0.005; 
		AbundanceUniverse = 0.13; 
		Discovery = 1898; 
		Radioactive = 0; 
		DiscoveredBy = "W. Ramsay, W. Travers"; 
	}
};
struct Sodium : OOTElement{
	Sodium()
	{
		AtomicNumber = 11; 
		Symbol = "Na"; 
		EnglishName = "Sodium"; 
		Group = 1; 
		Period = 3; 
		Block = "s"; 
		Category = 1; 
		AtomicMass = 22.98976928; 
		Configuration = "[Ne] 3s1"; 
		ShellConfiguration = "2,8,1,,,,"; 
		StandardState = 2; 
		Density = 0.971; 
		MeltingPoint = 370.87; 
		BoilingPoint = 1156; 
		HeatCapacity = 1.228; 
		HeatOfFusion = 2.6; 
		HeatOfVaporization = 97.42; 
		AtomicRadius = 190; 
		CovalentRadius = 154; 
		VanDerWaalsRadius = 227; 
		Electronegativity = 0.93; 
		OxidationStates = "1"; 
		IonizationEnergy = 495.8; 
		ThermalConductivity = 142; 
		ElectronAffinity = 52.867; 
		AbundanceCrust = 23600; 
		AbundanceUniverse = 0.002; 
		Discovery = 1807; 
		Radioactive = 0; 
		DiscoveredBy = "H. Davy"; 
	}
};
struct Magnesium : OOTElement{
	Magnesium()
	{
		AtomicNumber = 12; 
		Symbol = "Mg"; 
		EnglishName = "Magnesium"; 
		Group = 2; 
		Period = 3; 
		Block = "s"; 
		Category = 2; 
		AtomicMass = 24.305; 
		Configuration = "[Ne] 3s2"; 
		ShellConfiguration = "2,8,2,,,,"; 
		StandardState = 2; 
		Density = 1.738; 
		MeltingPoint = 923; 
		BoilingPoint = 1363; 
		HeatCapacity = 1.023; 
		HeatOfFusion = 8.48; 
		HeatOfVaporization = 128; 
		AtomicRadius = 145; 
		CovalentRadius = 130; 
		VanDerWaalsRadius = 173; 
		Electronegativity = 1.31; 
		OxidationStates = "2"; 
		IonizationEnergy = 737.7; 
		ThermalConductivity = 156; 
		ElectronAffinity = -40; 
		AbundanceCrust = 23300; 
		AbundanceUniverse = 0.059; 
		Discovery = 1755; 
		Radioactive = 0; 
		DiscoveredBy = "J. Black"; 
	}
};
struct Aluminium : OOTElement{
	Aluminium()
	{
		AtomicNumber = 13; 
		Symbol = "Al"; 
		EnglishName = "Aluminium"; 
		Group = 13; 
		Period = 3; 
		Block = "p"; 
		Category = 4; 
		AtomicMass = 26.9815385; 
		Configuration = "[Ne] 3s2 3p1"; 
		ShellConfiguration = "2,8,3,,,,"; 
		StandardState = 2; 
		Density = 2.698; 
		MeltingPoint = 933.47; 
		BoilingPoint = 2792; 
		HeatCapacity = 0.897; 
		HeatOfFusion = 10.71; 
		HeatOfVaporization = 284; 
		AtomicRadius = 118; 
		CovalentRadius = 118; 
		VanDerWaalsRadius = 184; 
		Electronegativity = 1.61; 
		OxidationStates = "3"; 
		IonizationEnergy = 577.5; 
		ThermalConductivity = 237; 
		ElectronAffinity = 41.762; 
		AbundanceCrust = 82300; 
		AbundanceUniverse = 0.005; 
		Discovery = 1825; 
		Radioactive = 0; 
		DiscoveredBy = "H. C. Ørsted"; 
	}
};
struct Silicon : OOTElement{
	Silicon()
	{
		AtomicNumber = 14; 
		Symbol = "Si"; 
		EnglishName = "Silicon"; 
		Group = 14; 
		Period = 3; 
		Block = "p"; 
		Category = 5; 
		AtomicMass = 28.085; 
		Configuration = "[Ne] 3s2 3p2"; 
		ShellConfiguration = "2,8,4,,,,"; 
		StandardState = 2; 
		Density = 2.3296; 
		MeltingPoint = 1687; 
		BoilingPoint = 3538; 
		HeatCapacity = 0.705; 
		HeatOfFusion = 50.21; 
		HeatOfVaporization = 359; 
		AtomicRadius = 111; 
		CovalentRadius = 111; 
		VanDerWaalsRadius = 210; 
		Electronegativity = 1.9; 
		OxidationStates = "-4,4"; 
		IonizationEnergy = 786.5; 
		ThermalConductivity = 149; 
		ElectronAffinity = 134.068; 
		AbundanceCrust = 282000; 
		AbundanceUniverse = 0.07; 
		Discovery = 1823; 
		Radioactive = 0; 
		DiscoveredBy = "J. Berzelius"; 
	}
};
struct Phosphorus : OOTElement{
	Phosphorus()
	{
		AtomicNumber = 15; 
		Symbol = "P"; 
		EnglishName = "Phosphorus"; 
		Group = 15; 
		Period = 3; 
		Block = "p"; 
		Category = 0; 
		AtomicMass = 30.973762; 
		Configuration = "[Ne] 3s2 3p3"; 
		ShellConfiguration = "2,8,5,,,,"; 
		StandardState = 2; 
		Density = 1.82; 
		MeltingPoint = 317.3; 
		BoilingPoint = 550; 
		HeatCapacity = 0.769; 
		HeatOfFusion = 0.66; 
		HeatOfVaporization = 12.4; 
		AtomicRadius = 98; 
		CovalentRadius = 106; 
		VanDerWaalsRadius = 180; 
		Electronegativity = 2.19; 
		OxidationStates = "-3,3,5"; 
		IonizationEnergy = 1011.8; 
		ThermalConductivity = 0.236; 
		ElectronAffinity = 72.037; 
		AbundanceCrust = 1050; 
		AbundanceUniverse = 0.0007; 
		Discovery = 1669; 
		Radioactive = 0; 
		DiscoveredBy = "H. Brand"; 
	}
};
struct Sulfur : OOTElement{
	Sulfur()
	{
		AtomicNumber = 16; 
		Symbol = "S"; 
		EnglishName = "Sulfur"; 
		Group = 16; 
		Period = 3; 
		Block = "p"; 
		Category = 0; 
		AtomicMass = 32.06; 
		Configuration = "[Ne] 3s2 3p4"; 
		ShellConfiguration = "2,8,6,,,,"; 
		StandardState = 2; 
		Density = 2.067; 
		MeltingPoint = 388.36; 
		BoilingPoint = 717.87; 
		HeatCapacity = 0.71; 
		HeatOfFusion = 1.727; 
		HeatOfVaporization = 45; 
		AtomicRadius = 88; 
		CovalentRadius = 102; 
		VanDerWaalsRadius = 180; 
		Electronegativity = 2.58; 
		OxidationStates = "-2,2,4,6"; 
		IonizationEnergy = 999.6; 
		ThermalConductivity = 0.205; 
		ElectronAffinity = 200.41; 
		AbundanceCrust = 350; 
		AbundanceUniverse = 0.05; 
		Discovery = -2000; 
		Radioactive = 0; 
		DiscoveredBy = (const char*)"NULL"; 
	}
};
struct Chlorine : OOTElement{
	Chlorine()
	{
		AtomicNumber = 17; 
		Symbol = "Cl"; 
		EnglishName = "Chlorine"; 
		Group = 17; 
		Period = 3; 
		Block = "p"; 
		Category = 6; 
		AtomicMass = 35.45; 
		Configuration = "[Ne] 3s2 3p5"; 
		ShellConfiguration = "2,8,7,,,,"; 
		StandardState = 0; 
		Density = 0.003214; 
		MeltingPoint = 171.6; 
		BoilingPoint = 239.11; 
		HeatCapacity = 0.479; 
		HeatOfFusion = 6.406; 
		HeatOfVaporization = 20.41; 
		AtomicRadius = 79; 
		CovalentRadius = 99; 
		VanDerWaalsRadius = 175; 
		Electronegativity = 3.16; 
		OxidationStates = "-1,1,3,5,7"; 
		IonizationEnergy = 1251.2; 
		ThermalConductivity = 0.0089; 
		ElectronAffinity = 348.575; 
		AbundanceCrust = 145; 
		AbundanceUniverse = 0.0001; 
		Discovery = 1774; 
		Radioactive = 0; 
		DiscoveredBy = "W. Scheele"; 
	}
};
struct Argon : OOTElement{
	Argon()
	{
		AtomicNumber = 18; 
		Symbol = "Ar"; 
		EnglishName = "Argon"; 
		Group = 18; 
		Period = 3; 
		Block = "p"; 
		Category = 7; 
		AtomicMass = 39.948; 
		Configuration = "[Ne] 3s2 3p6"; 
		ShellConfiguration = "2,8,8,,,,"; 
		StandardState = 0; 
		Density = 0.0017837; 
		MeltingPoint = 83.8; 
		BoilingPoint = 87.3; 
		HeatCapacity = 0.52; 
		HeatOfFusion = 1.18; 
		HeatOfVaporization = 6.53; 
		AtomicRadius = 71; 
		CovalentRadius = 97; 
		VanDerWaalsRadius = 188; 
		Electronegativity = (int)'N'; 
		OxidationStates = "0"; 
		IonizationEnergy = 1520.6; 
		ThermalConductivity = 0.01772; 
		ElectronAffinity = -96; 
		AbundanceCrust = 3.5; 
		AbundanceUniverse = 0.02; 
		Discovery = 1894; 
		Radioactive = 0; 
		DiscoveredBy = "Lord Rayleig, W. Ramsay"; 
	}
};
struct Potassium : OOTElement{
	Potassium()
	{
		AtomicNumber = 19; 
		Symbol = "K"; 
		EnglishName = "Potassium"; 
		Group = 1; 
		Period = 4; 
		Block = "s"; 
		Category = 1; 
		AtomicMass = 39.0983; 
		Configuration = "[Ar] 4s1"; 
		ShellConfiguration = "2,8,8,1,,,"; 
		StandardState = 2; 
		Density = 0.862; 
		MeltingPoint = 336.53; 
		BoilingPoint = 1032; 
		HeatCapacity = 0.757; 
		HeatOfFusion = 2.321; 
		HeatOfVaporization = 76.9; 
		AtomicRadius = 243; 
		CovalentRadius = 196; 
		VanDerWaalsRadius = 275; 
		Electronegativity = 0.82; 
		OxidationStates = "1"; 
		IonizationEnergy = 418.8; 
		ThermalConductivity = 102.5; 
		ElectronAffinity = 48.383; 
		AbundanceCrust = 20900; 
		AbundanceUniverse = 0.0003; 
		Discovery = 1807; 
		Radioactive = 0; 
		DiscoveredBy = "H. Davy"; 
	}
};
struct Calcium : OOTElement{
	Calcium()
	{
		AtomicNumber = 20; 
		Symbol = "Ca"; 
		EnglishName = "Calcium"; 
		Group = 2; 
		Period = 4; 
		Block = "s"; 
		Category = 2; 
		AtomicMass = 40.078; 
		Configuration = "[Ar] 4s2"; 
		ShellConfiguration = "2,8,8,2,,,"; 
		StandardState = 2; 
		Density = 1.54; 
		MeltingPoint = 1115; 
		BoilingPoint = 1757; 
		HeatCapacity = 0.647; 
		HeatOfFusion = 8.54; 
		HeatOfVaporization = 154.7; 
		AtomicRadius = 194; 
		CovalentRadius = 174; 
		VanDerWaalsRadius = 231; 
		Electronegativity = 1; 
		OxidationStates = "2"; 
		IonizationEnergy = 589.8; 
		ThermalConductivity = 201; 
		ElectronAffinity = 2.37; 
		AbundanceCrust = 41500; 
		AbundanceUniverse = 0.007; 
		Discovery = 1808; 
		Radioactive = 0; 
		DiscoveredBy = "H. Davy"; 
	}
};
struct Scandium : OOTElement{
	Scandium()
	{
		AtomicNumber = 21; 
		Symbol = "Sc"; 
		EnglishName = "Scandium"; 
		Group = 3; 
		Period = 4; 
		Block = "d"; 
		Category = 3; 
		AtomicMass = 44.955908; 
		Configuration = "[Ar] 3d1 4s2"; 
		ShellConfiguration = "2,8,9,2,,,"; 
		StandardState = 2; 
		Density = 2.989; 
		MeltingPoint = 1814; 
		BoilingPoint = 3109; 
		HeatCapacity = 0.568; 
		HeatOfFusion = 14.1; 
		HeatOfVaporization = 332.7; 
		AtomicRadius = 184; 
		CovalentRadius = 144; 
		VanDerWaalsRadius = 211; 
		Electronegativity = 1.36; 
		OxidationStates = "3"; 
		IonizationEnergy = 633.1; 
		ThermalConductivity = 15.8; 
		ElectronAffinity = 18; 
		AbundanceCrust = 22; 
		AbundanceUniverse = 0.000003; 
		Discovery = 1879; 
		Radioactive = 0; 
		DiscoveredBy = "F. Nilson"; 
	}
};
struct Titanium : OOTElement{
	Titanium()
	{
		AtomicNumber = 22; 
		Symbol = "Ti"; 
		EnglishName = "Titanium"; 
		Group = 4; 
		Period = 4; 
		Block = "d"; 
		Category = 3; 
		AtomicMass = 47.867; 
		Configuration = "[Ar] 3d2 4s2"; 
		ShellConfiguration = "2,8,10,2,,,"; 
		StandardState = 2; 
		Density = 4.54; 
		MeltingPoint = 1941; 
		BoilingPoint = 3560; 
		HeatCapacity = 0.523; 
		HeatOfFusion = 14.15; 
		HeatOfVaporization = 425; 
		AtomicRadius = 176; 
		CovalentRadius = 136; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = 1.54; 
		OxidationStates = "3,4"; 
		IonizationEnergy = 658.8; 
		ThermalConductivity = 21.9; 
		ElectronAffinity = 8; 
		AbundanceCrust = 5650; 
		AbundanceUniverse = 0.0003; 
		Discovery = 1791; 
		Radioactive = 0; 
		DiscoveredBy = "W. Gregor"; 
	}
};
struct Vanadium : OOTElement{
	Vanadium()
	{
		AtomicNumber = 23; 
		Symbol = "V"; 
		EnglishName = "Vanadium"; 
		Group = 5; 
		Period = 4; 
		Block = "d"; 
		Category = 3; 
		AtomicMass = 50.9415; 
		Configuration = "[Ar] 3d3 4s2"; 
		ShellConfiguration = "2,8,11,2,,,"; 
		StandardState = 2; 
		Density = 6.11; 
		MeltingPoint = 2183; 
		BoilingPoint = 3680; 
		HeatCapacity = 0.489; 
		HeatOfFusion = 21.5; 
		HeatOfVaporization = 444; 
		AtomicRadius = 171; 
		CovalentRadius = 125; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = 1.63; 
		OxidationStates = "2,3,4,5"; 
		IonizationEnergy = 650.9; 
		ThermalConductivity = 30.7; 
		ElectronAffinity = 50.911; 
		AbundanceCrust = 120; 
		AbundanceUniverse = 0.0001; 
		Discovery = 1801; 
		Radioactive = 0; 
		DiscoveredBy = "M. del Río"; 
	}
};
struct Chromium : OOTElement{
	Chromium()
	{
		AtomicNumber = 24; 
		Symbol = "Cr"; 
		EnglishName = "Chromium"; 
		Group = 6; 
		Period = 4; 
		Block = "d"; 
		Category = 3; 
		AtomicMass = 51.9961; 
		Configuration = "[Ar] 3d5 4s1"; 
		ShellConfiguration = "2,8,13,1,,,"; 
		StandardState = 2; 
		Density = 7.15; 
		MeltingPoint = 2180; 
		BoilingPoint = 2944; 
		HeatCapacity = 0.449; 
		HeatOfFusion = 21; 
		HeatOfVaporization = 339.5; 
		AtomicRadius = 166; 
		CovalentRadius = 127; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = 1.66; 
		OxidationStates = "2,3,6"; 
		IonizationEnergy = 652.9; 
		ThermalConductivity = 93.9; 
		ElectronAffinity = 65.21; 
		AbundanceCrust = 102; 
		AbundanceUniverse = 0.0015; 
		Discovery = 1794; 
		Radioactive = 0; 
		DiscoveredBy = "N. Vauquelin"; 
	}
};
struct Manganese : OOTElement{
	Manganese()
	{
		AtomicNumber = 25; 
		Symbol = "Mn"; 
		EnglishName = "Manganese"; 
		Group = 7; 
		Period = 4; 
		Block = "d"; 
		Category = 3; 
		AtomicMass = 54.938044; 
		Configuration = "[Ar] 3d5 4s2"; 
		ShellConfiguration = "2,8,13,2,,,"; 
		StandardState = 2; 
		Density = 7.44; 
		MeltingPoint = 1519; 
		BoilingPoint = 2334; 
		HeatCapacity = 0.479; 
		HeatOfFusion = 12.91; 
		HeatOfVaporization = 221; 
		AtomicRadius = 161; 
		CovalentRadius = 139; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = 1.55; 
		OxidationStates = "2,3,4,6,7"; 
		IonizationEnergy = 717.3; 
		ThermalConductivity = 7.81; 
		ElectronAffinity = -50; 
		AbundanceCrust = 950; 
		AbundanceUniverse = 0.0008; 
		Discovery = 1774; 
		Radioactive = 0; 
		DiscoveredBy = "W. Scheele"; 
	}
};
struct Iron : OOTElement{
	Iron()
	{
		AtomicNumber = 26; 
		Symbol = "Fe"; 
		EnglishName = "Iron"; 
		Group = 8; 
		Period = 4; 
		Block = "d"; 
		Category = 3; 
		AtomicMass = 55.845; 
		Configuration = "[Ar] 3d6 4s2"; 
		ShellConfiguration = "2,8,14,2,,,"; 
		StandardState = 2; 
		Density = 7.874; 
		MeltingPoint = 1811; 
		BoilingPoint = 3134; 
		HeatCapacity = 0.449; 
		HeatOfFusion = 13.81; 
		HeatOfVaporization = 340; 
		AtomicRadius = 156; 
		CovalentRadius = 125; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = 1.83; 
		OxidationStates = "2,3,6"; 
		IonizationEnergy = 762.5; 
		ThermalConductivity = 80.4; 
		ElectronAffinity = 14.785; 
		AbundanceCrust = 56300; 
		AbundanceUniverse = 0.11; 
		Discovery = -5000; 
		Radioactive = 0; 
		DiscoveredBy = (const char*)"NULL"; 
	}
};
struct Cobalt : OOTElement{
	Cobalt()
	{
		AtomicNumber = 27; 
		Symbol = "Co"; 
		EnglishName = "Cobalt"; 
		Group = 9; 
		Period = 4; 
		Block = "d"; 
		Category = 3; 
		AtomicMass = 58.933194; 
		Configuration = "[Ar] 3d7 4s2"; 
		ShellConfiguration = "2,8,15,2,,,"; 
		StandardState = 2; 
		Density = 8.86; 
		MeltingPoint = 1768; 
		BoilingPoint = 3200; 
		HeatCapacity = 0.421; 
		HeatOfFusion = 16.06; 
		HeatOfVaporization = 377; 
		AtomicRadius = 152; 
		CovalentRadius = 126; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = 1.88; 
		OxidationStates = "2,3"; 
		IonizationEnergy = 760.4; 
		ThermalConductivity = 100; 
		ElectronAffinity = 63.898; 
		AbundanceCrust = 25; 
		AbundanceUniverse = 0.0003; 
		Discovery = 1735; 
		Radioactive = 0; 
		DiscoveredBy = "G. Brandt"; 
	}
};
struct Nickel : OOTElement{
	Nickel()
	{
		AtomicNumber = 28; 
		Symbol = "Ni"; 
		EnglishName = "Nickel"; 
		Group = 10; 
		Period = 4; 
		Block = "d"; 
		Category = 3; 
		AtomicMass = 58.6934; 
		Configuration = "[Ar] 3d8 4s2"; 
		ShellConfiguration = "2,8,16,2,,,"; 
		StandardState = 2; 
		Density = 8.912; 
		MeltingPoint = 1728; 
		BoilingPoint = 3186; 
		HeatCapacity = 0.444; 
		HeatOfFusion = 17.48; 
		HeatOfVaporization = 379; 
		AtomicRadius = 149; 
		CovalentRadius = 121; 
		VanDerWaalsRadius = 163; 
		Electronegativity = 1.91; 
		OxidationStates = "2,3"; 
		IonizationEnergy = 737.1; 
		ThermalConductivity = 90.9; 
		ElectronAffinity = 111.65; 
		AbundanceCrust = 84; 
		AbundanceUniverse = 0.006; 
		Discovery = 1751; 
		Radioactive = 0; 
		DiscoveredBy = "F. Cronstedt"; 
	}
};
struct Copper : OOTElement{
	Copper()
	{
		AtomicNumber = 29; 
		Symbol = "Cu"; 
		EnglishName = "Copper"; 
		Group = 11; 
		Period = 4; 
		Block = "d"; 
		Category = 3; 
		AtomicMass = 63.546; 
		Configuration = "[Ar] 3d10 4s1"; 
		ShellConfiguration = "2,8,18,1,,,"; 
		StandardState = 2; 
		Density = 8.96; 
		MeltingPoint = 1357.77; 
		BoilingPoint = 2835; 
		HeatCapacity = 0.385; 
		HeatOfFusion = 13.26; 
		HeatOfVaporization = 300.4; 
		AtomicRadius = 145; 
		CovalentRadius = 138; 
		VanDerWaalsRadius = 140; 
		Electronegativity = 1.9; 
		OxidationStates = "1,2"; 
		IonizationEnergy = 745.5; 
		ThermalConductivity = 401; 
		ElectronAffinity = 119.235; 
		AbundanceCrust = 60; 
		AbundanceUniverse = 0.000006; 
		Discovery = -9000; 
		Radioactive = 0; 
		DiscoveredBy = (const char*)"NULL"; 
	}
};
struct Zinc : OOTElement{
	Zinc()
	{
		AtomicNumber = 30; 
		Symbol = "Zn"; 
		EnglishName = "Zinc"; 
		Group = 12; 
		Period = 4; 
		Block = "d"; 
		Category = 3; 
		AtomicMass = 65.38; 
		Configuration = "[Ar] 3d10 4s2"; 
		ShellConfiguration = "2,8,18,2,,,"; 
		StandardState = 2; 
		Density = 7.134; 
		MeltingPoint = 692.88; 
		BoilingPoint = 1180; 
		HeatCapacity = 0.388; 
		HeatOfFusion = 7.32; 
		HeatOfVaporization = 115; 
		AtomicRadius = 142; 
		CovalentRadius = 131; 
		VanDerWaalsRadius = 139; 
		Electronegativity = 1.65; 
		OxidationStates = "2"; 
		IonizationEnergy = 906.4; 
		ThermalConductivity = 116; 
		ElectronAffinity = -60; 
		AbundanceCrust = 70; 
		AbundanceUniverse = 0.00003; 
		Discovery = -1000; 
		Radioactive = 0; 
		DiscoveredBy = (const char*)"NULL"; 
	}
};
struct Gallium : OOTElement{
	Gallium()
	{
		AtomicNumber = 31; 
		Symbol = "Ga"; 
		EnglishName = "Gallium"; 
		Group = 13; 
		Period = 4; 
		Block = "p"; 
		Category = 4; 
		AtomicMass = 69.723; 
		Configuration = "[Ar] 3d10 4s2 4p1"; 
		ShellConfiguration = "2,8,18,3,,,"; 
		StandardState = 2; 
		Density = 5.907; 
		MeltingPoint = 302.9146; 
		BoilingPoint = 2673; 
		HeatCapacity = 0.371; 
		HeatOfFusion = 5.59; 
		HeatOfVaporization = 256; 
		AtomicRadius = 136; 
		CovalentRadius = 126; 
		VanDerWaalsRadius = 187; 
		Electronegativity = 1.81; 
		OxidationStates = "3"; 
		IonizationEnergy = 578.8; 
		ThermalConductivity = 40.6; 
		ElectronAffinity = 41; 
		AbundanceCrust = 19; 
		AbundanceUniverse = 0.000001; 
		Discovery = 1875; 
		Radioactive = 0; 
		DiscoveredBy = "P. E. L. de Boisbaudran"; 
	}
};
struct Germanium : OOTElement{
	Germanium()
	{
		AtomicNumber = 32; 
		Symbol = "Ge"; 
		EnglishName = "Germanium"; 
		Group = 14; 
		Period = 4; 
		Block = "p"; 
		Category = 5; 
		AtomicMass = 72.63; 
		Configuration = "[Ar] 3d10 4s2 4p2"; 
		ShellConfiguration = "2,8,18,4,,,"; 
		StandardState = 2; 
		Density = 5.323; 
		MeltingPoint = 1211.4; 
		BoilingPoint = 3106; 
		HeatCapacity = 0.32; 
		HeatOfFusion = 36.94; 
		HeatOfVaporization = 334; 
		AtomicRadius = 125; 
		CovalentRadius = 122; 
		VanDerWaalsRadius = 211; 
		Electronegativity = 2.01; 
		OxidationStates = "-4,2,4"; 
		IonizationEnergy = 762; 
		ThermalConductivity = 60.2; 
		ElectronAffinity = 118.935; 
		AbundanceCrust = 1.5; 
		AbundanceUniverse = 0.00002; 
		Discovery = 1886; 
		Radioactive = 0; 
		DiscoveredBy = "C. A. Winkler"; 
	}
};
struct Arsenic : OOTElement{
	Arsenic()
	{
		AtomicNumber = 33; 
		Symbol = "As"; 
		EnglishName = "Arsenic"; 
		Group = 15; 
		Period = 4; 
		Block = "p"; 
		Category = 5; 
		AtomicMass = 74.921595; 
		Configuration = "[Ar] 3d10 4s2 4p3"; 
		ShellConfiguration = "2,8,18,5,,,"; 
		StandardState = 2; 
		Density = 5.776; 
		MeltingPoint = 1090; 
		BoilingPoint = 887; 
		HeatCapacity = 0.329; 
		HeatOfFusion = 24.44; 
		HeatOfVaporization = 32.4; 
		AtomicRadius = 114; 
		CovalentRadius = 119; 
		VanDerWaalsRadius = 185; 
		Electronegativity = 2.18; 
		OxidationStates = "-3,3,5"; 
		IonizationEnergy = 947; 
		ThermalConductivity = 50.2; 
		ElectronAffinity = 77.65; 
		AbundanceCrust = 1.8; 
		AbundanceUniverse = 0.0000008; 
		Discovery = 300; 
		Radioactive = 0; 
		DiscoveredBy = (const char*)"NULL"; 
	}
};
struct Selenium : OOTElement{
	Selenium()
	{
		AtomicNumber = 34; 
		Symbol = "Se"; 
		EnglishName = "Selenium"; 
		Group = 16; 
		Period = 4; 
		Block = "p"; 
		Category = 0; 
		AtomicMass = 78.971; 
		Configuration = "[Ar] 3d10 4s2 4p4"; 
		ShellConfiguration = "2,8,18,6,,,"; 
		StandardState = 2; 
		Density = 4.809; 
		MeltingPoint = 453; 
		BoilingPoint = 958; 
		HeatCapacity = 0.321; 
		HeatOfFusion = 6.69; 
		HeatOfVaporization = 95.48; 
		AtomicRadius = 103; 
		CovalentRadius = 116; 
		VanDerWaalsRadius = 190; 
		Electronegativity = 2.55; 
		OxidationStates = "-2,2,4,6"; 
		IonizationEnergy = 941; 
		ThermalConductivity = 0.519; 
		ElectronAffinity = 194.958; 
		AbundanceCrust = 0.05; 
		AbundanceUniverse = 0.000003; 
		Discovery = 1817; 
		Radioactive = 0; 
		DiscoveredBy = "J. Berzelius, G. Gahn"; 
	}
};
struct Bromine : OOTElement{
	Bromine()
	{
		AtomicNumber = 35; 
		Symbol = "Br"; 
		EnglishName = "Bromine"; 
		Group = 17; 
		Period = 4; 
		Block = "p"; 
		Category = 6; 
		AtomicMass = 79.904; 
		Configuration = "[Ar] 3d10 4s2 4p5"; 
		ShellConfiguration = "2,8,18,7,,,"; 
		StandardState = 1; 
		Density = 3.122; 
		MeltingPoint = 265.8; 
		BoilingPoint = 332; 
		HeatCapacity = 0.474; 
		HeatOfFusion = 10.57; 
		HeatOfVaporization = 29.96; 
		AtomicRadius = 94; 
		CovalentRadius = 114; 
		VanDerWaalsRadius = 185; 
		Electronegativity = 2.96; 
		OxidationStates = "-1,1,3,5,7"; 
		IonizationEnergy = 1139.9; 
		ThermalConductivity = 0.12; 
		ElectronAffinity = 324.537; 
		AbundanceCrust = 2.4; 
		AbundanceUniverse = 0.0000007; 
		Discovery = 1825; 
		Radioactive = 0; 
		DiscoveredBy = "J. Balard, C. Löwig"; 
	}
};
struct Krypton : OOTElement{
	Krypton()
	{
		AtomicNumber = 36; 
		Symbol = "Kr"; 
		EnglishName = "Krypton"; 
		Group = 18; 
		Period = 4; 
		Block = "p"; 
		Category = 7; 
		AtomicMass = 83.798; 
		Configuration = "[Ar] 3d10 4s2 4p6"; 
		ShellConfiguration = "2,8,18,8,,,"; 
		StandardState = 0; 
		Density = 0.003733; 
		MeltingPoint = 115.79; 
		BoilingPoint = 119.93; 
		HeatCapacity = 0.248; 
		HeatOfFusion = 1.64; 
		HeatOfVaporization = 9.08; 
		AtomicRadius = 88; 
		CovalentRadius = 110; 
		VanDerWaalsRadius = 202; 
		Electronegativity = 3; 
		OxidationStates = "0"; 
		IonizationEnergy = 1350.8; 
		ThermalConductivity = 0.00943; 
		ElectronAffinity = -60; 
		AbundanceCrust = 0.0001; 
		AbundanceUniverse = 0.000004; 
		Discovery = 1898; 
		Radioactive = 0; 
		DiscoveredBy = "W. Ramsay, W. Travers"; 
	}
};
struct Rubidium : OOTElement{
	Rubidium()
	{
		AtomicNumber = 37; 
		Symbol = "Rb"; 
		EnglishName = "Rubidium"; 
		Group = 1; 
		Period = 5; 
		Block = "s"; 
		Category = 1; 
		AtomicMass = 85.4678; 
		Configuration = "[Kr] 5s1"; 
		ShellConfiguration = "2,8,18,8,1,,"; 
		StandardState = 2; 
		Density = 1.532; 
		MeltingPoint = 312.46; 
		BoilingPoint = 961; 
		HeatCapacity = 0.363; 
		HeatOfFusion = 2.19; 
		HeatOfVaporization = 75.77; 
		AtomicRadius = 265; 
		CovalentRadius = 211; 
		VanDerWaalsRadius = 303; 
		Electronegativity = 0.82; 
		OxidationStates = "1"; 
		IonizationEnergy = 403; 
		ThermalConductivity = 58.2; 
		ElectronAffinity = 46.884; 
		AbundanceCrust = 90; 
		AbundanceUniverse = 0.000001; 
		Discovery = 1861; 
		Radioactive = 0; 
		DiscoveredBy = "R. Bunsen, G. R. Kirchhoff"; 
	}
};
struct Strontium : OOTElement{
	Strontium()
	{
		AtomicNumber = 38; 
		Symbol = "Sr"; 
		EnglishName = "Strontium"; 
		Group = 2; 
		Period = 5; 
		Block = "s"; 
		Category = 2; 
		AtomicMass = 87.62; 
		Configuration = "[Kr] 5s2"; 
		ShellConfiguration = "2,8,18,8,2,,"; 
		StandardState = 2; 
		Density = 2.64; 
		MeltingPoint = 1050; 
		BoilingPoint = 1655; 
		HeatCapacity = 0.301; 
		HeatOfFusion = 7.43; 
		HeatOfVaporization = 141; 
		AtomicRadius = 219; 
		CovalentRadius = 192; 
		VanDerWaalsRadius = 249; 
		Electronegativity = 0.95; 
		OxidationStates = "2"; 
		IonizationEnergy = 549.5; 
		ThermalConductivity = 35.4; 
		ElectronAffinity = 5.023; 
		AbundanceCrust = 370; 
		AbundanceUniverse = 0.000004; 
		Discovery = 1787; 
		Radioactive = 0; 
		DiscoveredBy = "W. Cruikshank"; 
	}
};
struct Yttrium : OOTElement{
	Yttrium()
	{
		AtomicNumber = 39; 
		Symbol = "Y"; 
		EnglishName = "Yttrium"; 
		Group = 3; 
		Period = 5; 
		Block = "d"; 
		Category = 3; 
		AtomicMass = 88.90584; 
		Configuration = "[Kr] 4d1 5s2"; 
		ShellConfiguration = "2,8,18,9,2,,"; 
		StandardState = 2; 
		Density = 4.469; 
		MeltingPoint = 1799; 
		BoilingPoint = 3609; 
		HeatCapacity = 0.298; 
		HeatOfFusion = 11.42; 
		HeatOfVaporization = 390; 
		AtomicRadius = 212; 
		CovalentRadius = 162; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = 1.22; 
		OxidationStates = "3"; 
		IonizationEnergy = 600; 
		ThermalConductivity = 17.2; 
		ElectronAffinity = 29.6; 
		AbundanceCrust = 33; 
		AbundanceUniverse = 0.0000007; 
		Discovery = 1794; 
		Radioactive = 0; 
		DiscoveredBy = "J. Gadolin"; 
	}
};
struct Zirconium : OOTElement{
	Zirconium()
	{
		AtomicNumber = 40; 
		Symbol = "Zr"; 
		EnglishName = "Zirconium"; 
		Group = 4; 
		Period = 5; 
		Block = "d"; 
		Category = 3; 
		AtomicMass = 91.224; 
		Configuration = "[Kr] 4d2 5s2"; 
		ShellConfiguration = "2,8,18,10,2,,"; 
		StandardState = 2; 
		Density = 6.506; 
		MeltingPoint = 2128; 
		BoilingPoint = 4682; 
		HeatCapacity = 0.278; 
		HeatOfFusion = 14; 
		HeatOfVaporization = 573; 
		AtomicRadius = 206; 
		CovalentRadius = 148; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = 1.33; 
		OxidationStates = "4"; 
		IonizationEnergy = 640.1; 
		ThermalConductivity = 22.6; 
		ElectronAffinity = 41.81; 
		AbundanceCrust = 165; 
		AbundanceUniverse = 0.000005; 
		Discovery = 1789; 
		Radioactive = 0; 
		DiscoveredBy = "H. Klaproth"; 
	}
};
struct Niobium : OOTElement{
	Niobium()
	{
		AtomicNumber = 41; 
		Symbol = "Nb"; 
		EnglishName = "Niobium"; 
		Group = 5; 
		Period = 5; 
		Block = "d"; 
		Category = 3; 
		AtomicMass = 92.90637; 
		Configuration = "[Kr] 4d4 5s1"; 
		ShellConfiguration = "2,8,18,12,1,,"; 
		StandardState = 2; 
		Density = 8.57; 
		MeltingPoint = 2750; 
		BoilingPoint = 5017; 
		HeatCapacity = 0.265; 
		HeatOfFusion = 30; 
		HeatOfVaporization = 689.9; 
		AtomicRadius = 198; 
		CovalentRadius = 137; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = 1.6; 
		OxidationStates = "3,5"; 
		IonizationEnergy = 652.1; 
		ThermalConductivity = 53.7; 
		ElectronAffinity = 88.516; 
		AbundanceCrust = 20; 
		AbundanceUniverse = 0.0000002; 
		Discovery = 1801; 
		Radioactive = 0; 
		DiscoveredBy = "C. Hatchett"; 
	}
};
struct Molybdenum : OOTElement{
	Molybdenum()
	{
		AtomicNumber = 42; 
		Symbol = "Mo"; 
		EnglishName = "Molybdenum"; 
		Group = 6; 
		Period = 5; 
		Block = "d"; 
		Category = 3; 
		AtomicMass = 95.95; 
		Configuration = "[Kr] 4d5 5s1"; 
		ShellConfiguration = "2,8,18,13,1,,"; 
		StandardState = 2; 
		Density = 10.22; 
		MeltingPoint = 2896; 
		BoilingPoint = 4912; 
		HeatCapacity = 0.251; 
		HeatOfFusion = 37.48; 
		HeatOfVaporization = 617; 
		AtomicRadius = 190; 
		CovalentRadius = 145; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = 2.16; 
		OxidationStates = "2,3,4,5,6"; 
		IonizationEnergy = 684.3; 
		ThermalConductivity = 138; 
		ElectronAffinity = 72.1; 
		AbundanceCrust = 1.2; 
		AbundanceUniverse = 0.0000005; 
		Discovery = 1778; 
		Radioactive = 0; 
		DiscoveredBy = "W. Scheele"; 
	}
};
struct Technetium : OOTElement{
	Technetium()
	{
		AtomicNumber = 43; 
		Symbol = "Tc"; 
		EnglishName = "Technetium"; 
		Group = 7; 
		Period = 5; 
		Block = "d"; 
		Category = 3; 
		AtomicMass = 98; 
		Configuration = "[Kr] 4d5 5s2"; 
		ShellConfiguration = "2,8,18,13,2,,"; 
		StandardState = 2; 
		Density = 11.5; 
		MeltingPoint = 2430; 
		BoilingPoint = 4538; 
		HeatCapacity = (int)'N'; 
		HeatOfFusion = 33.29; 
		HeatOfVaporization = 585.2; 
		AtomicRadius = 183; 
		CovalentRadius = 156; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = 1.9; 
		OxidationStates = "4,7"; 
		IonizationEnergy = 702; 
		ThermalConductivity = 50.6; 
		ElectronAffinity = 53.067; 
		AbundanceCrust = 3.00E-09; 
		AbundanceUniverse = (int)'N'; 
		Discovery = 1937; 
		Radioactive = 1; 
		DiscoveredBy = "C. Perrier and E. Segrè"; 
	}
};
struct Ruthenium : OOTElement{
	Ruthenium()
	{
		AtomicNumber = 44; 
		Symbol = "Ru"; 
		EnglishName = "Ruthenium"; 
		Group = 8; 
		Period = 5; 
		Block = "d"; 
		Category = 3; 
		AtomicMass = 101.07; 
		Configuration = "[Kr] 4d7 5s1"; 
		ShellConfiguration = "2,8,18,15,1,,"; 
		StandardState = 2; 
		Density = 12.37; 
		MeltingPoint = 2607; 
		BoilingPoint = 4423; 
		HeatCapacity = 0.238; 
		HeatOfFusion = 38.59; 
		HeatOfVaporization = 619; 
		AtomicRadius = 178; 
		CovalentRadius = 126; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = 2.2; 
		OxidationStates = "3,4,6"; 
		IonizationEnergy = 710.2; 
		ThermalConductivity = 117; 
		ElectronAffinity = 100.96; 
		AbundanceCrust = 0.001; 
		AbundanceUniverse = 0.0000004; 
		Discovery = 1844; 
		Radioactive = 0; 
		DiscoveredBy = "K. Claus"; 
	}
};
struct Rhodium : OOTElement{
	Rhodium()
	{
		AtomicNumber = 45; 
		Symbol = "Rh"; 
		EnglishName = "Rhodium"; 
		Group = 9; 
		Period = 5; 
		Block = "d"; 
		Category = 3; 
		AtomicMass = 102.9055; 
		Configuration = "[Kr] 4d8 5s1"; 
		ShellConfiguration = "2,8,18,16,1,,"; 
		StandardState = 2; 
		Density = 12.41; 
		MeltingPoint = 2237; 
		BoilingPoint = 3968; 
		HeatCapacity = 0.243; 
		HeatOfFusion = 26.59; 
		HeatOfVaporization = 494; 
		AtomicRadius = 173; 
		CovalentRadius = 135; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = 2.28; 
		OxidationStates = "3,4"; 
		IonizationEnergy = 719.7; 
		ThermalConductivity = 150; 
		ElectronAffinity = 110.27; 
		AbundanceCrust = 0.001; 
		AbundanceUniverse = 0.00000006; 
		Discovery = 1804; 
		Radioactive = 0; 
		DiscoveredBy = "H. Wollaston"; 
	}
};
struct Palladium : OOTElement{
	Palladium()
	{
		AtomicNumber = 46; 
		Symbol = "Pd"; 
		EnglishName = "Palladium"; 
		Group = 10; 
		Period = 5; 
		Block = "d"; 
		Category = 3; 
		AtomicMass = 106.42; 
		Configuration = "[Kr] 4d10"; 
		ShellConfiguration = "2,8,18,18,,,"; 
		StandardState = 2; 
		Density = 12.02; 
		MeltingPoint = 1828.05; 
		BoilingPoint = 3236; 
		HeatCapacity = 0.244; 
		HeatOfFusion = 16.74; 
		HeatOfVaporization = 358; 
		AtomicRadius = 169; 
		CovalentRadius = 131; 
		VanDerWaalsRadius = 163; 
		Electronegativity = 2.2; 
		OxidationStates = "2,4"; 
		IonizationEnergy = 804.4; 
		ThermalConductivity = 71.8; 
		ElectronAffinity = 54.24; 
		AbundanceCrust = 0.015; 
		AbundanceUniverse = 0.0000002; 
		Discovery = 1802; 
		Radioactive = 0; 
		DiscoveredBy = "H. Wollaston"; 
	}
};
struct Silver : OOTElement{
	Silver()
	{
		AtomicNumber = 47; 
		Symbol = "Ag"; 
		EnglishName = "Silver"; 
		Group = 11; 
		Period = 5; 
		Block = "d"; 
		Category = 3; 
		AtomicMass = 107.8682; 
		Configuration = "[Kr] 4d10 5s1"; 
		ShellConfiguration = "2,8,18,18,1,,"; 
		StandardState = 2; 
		Density = 10.501; 
		MeltingPoint = 1234.93; 
		BoilingPoint = 2435; 
		HeatCapacity = 0.235; 
		HeatOfFusion = 11.28; 
		HeatOfVaporization = 254; 
		AtomicRadius = 165; 
		CovalentRadius = 153; 
		VanDerWaalsRadius = 172; 
		Electronegativity = 1.93; 
		OxidationStates = "1,2"; 
		IonizationEnergy = 731; 
		ThermalConductivity = 429; 
		ElectronAffinity = 125.862; 
		AbundanceCrust = 0.075; 
		AbundanceUniverse = 0.00000006; 
		Discovery = -5000; 
		Radioactive = 0; 
		DiscoveredBy = (const char*)"NULL"; 
	}
};
struct Cadmium : OOTElement{
	Cadmium()
	{
		AtomicNumber = 48; 
		Symbol = "Cd"; 
		EnglishName = "Cadmium"; 
		Group = 12; 
		Period = 5; 
		Block = "d"; 
		Category = 3; 
		AtomicMass = 112.414; 
		Configuration = "[Kr] 4d10 5s2"; 
		ShellConfiguration = "2,8,18,18,2,,"; 
		StandardState = 2; 
		Density = 8.69; 
		MeltingPoint = 594.22; 
		BoilingPoint = 1040; 
		HeatCapacity = 0.232; 
		HeatOfFusion = 6.21; 
		HeatOfVaporization = 99.87; 
		AtomicRadius = 161; 
		CovalentRadius = 148; 
		VanDerWaalsRadius = 158; 
		Electronegativity = 1.69; 
		OxidationStates = "2"; 
		IonizationEnergy = 867.8; 
		ThermalConductivity = 96.6; 
		ElectronAffinity = -70; 
		AbundanceCrust = 0.159; 
		AbundanceUniverse = 0.0000002; 
		Discovery = 1817; 
		Radioactive = 0; 
		DiscoveredBy = "S. L Hermann, F. Stromeyer, J.C.H. Roloff"; 
	}
};
struct Indium : OOTElement{
	Indium()
	{
		AtomicNumber = 49; 
		Symbol = "In"; 
		EnglishName = "Indium"; 
		Group = 13; 
		Period = 5; 
		Block = "p"; 
		Category = 4; 
		AtomicMass = 114.818; 
		Configuration = "[Kr] 4d10 5s2 5p1"; 
		ShellConfiguration = "2,8,18,18,3,,"; 
		StandardState = 2; 
		Density = 7.31; 
		MeltingPoint = 429.75; 
		BoilingPoint = 2345; 
		HeatCapacity = 0.233; 
		HeatOfFusion = 3.281; 
		HeatOfVaporization = 231.8; 
		AtomicRadius = 156; 
		CovalentRadius = 144; 
		VanDerWaalsRadius = 193; 
		Electronegativity = 1.78; 
		OxidationStates = "3"; 
		IonizationEnergy = 558.3; 
		ThermalConductivity = 81.8; 
		ElectronAffinity = 28.95; 
		AbundanceCrust = 0.25; 
		AbundanceUniverse = 0.00000003; 
		Discovery = 1863; 
		Radioactive = 0; 
		DiscoveredBy = "F. Reich, T. Richter"; 
	}
};
struct Tin : OOTElement{
	Tin()
	{
		AtomicNumber = 50; 
		Symbol = "Sn"; 
		EnglishName = "Tin"; 
		Group = 14; 
		Period = 5; 
		Block = "p"; 
		Category = 4; 
		AtomicMass = 118.71; 
		Configuration = "[Kr] 4d10 5s2 5p2"; 
		ShellConfiguration = "2,8,18,18,4,,"; 
		StandardState = 2; 
		Density = 7.287; 
		MeltingPoint = 505.08; 
		BoilingPoint = 2875; 
		HeatCapacity = 0.228; 
		HeatOfFusion = 7.03; 
		HeatOfVaporization = 296.1; 
		AtomicRadius = 145; 
		CovalentRadius = 141; 
		VanDerWaalsRadius = 217; 
		Electronegativity = 1.96; 
		OxidationStates = "-4,2,4"; 
		IonizationEnergy = 708.6; 
		ThermalConductivity = 66.8; 
		ElectronAffinity = 107.298; 
		AbundanceCrust = 2.3; 
		AbundanceUniverse = 0.0000004; 
		Discovery = -3500; 
		Radioactive = 0; 
		DiscoveredBy = (const char*)"NULL"; 
	}
};
struct Antimony : OOTElement{
	Antimony()
	{
		AtomicNumber = 51; 
		Symbol = "Sb"; 
		EnglishName = "Antimony"; 
		Group = 15; 
		Period = 5; 
		Block = "p"; 
		Category = 5; 
		AtomicMass = 121.76; 
		Configuration = "[Kr] 4d10 5s2 5p3"; 
		ShellConfiguration = "2,8,18,18,5,,"; 
		StandardState = 2; 
		Density = 6.685; 
		MeltingPoint = 903.78; 
		BoilingPoint = 1860; 
		HeatCapacity = 0.207; 
		HeatOfFusion = 19.79; 
		HeatOfVaporization = 193.43; 
		AtomicRadius = 133; 
		CovalentRadius = 138; 
		VanDerWaalsRadius = 206; 
		Electronegativity = 2.05; 
		OxidationStates = "-3,3,5"; 
		IonizationEnergy = 834; 
		ThermalConductivity = 24.4; 
		ElectronAffinity = 101.059; 
		AbundanceCrust = 0.2; 
		AbundanceUniverse = 0.00000004; 
		Discovery = -3000; 
		Radioactive = 0; 
		DiscoveredBy = (const char*)"NULL"; 
	}
};
struct Tellurium : OOTElement{
	Tellurium()
	{
		AtomicNumber = 52; 
		Symbol = "Te"; 
		EnglishName = "Tellurium"; 
		Group = 16; 
		Period = 5; 
		Block = "p"; 
		Category = 5; 
		AtomicMass = 127.6; 
		Configuration = "[Kr] 4d10 5s2 5p4"; 
		ShellConfiguration = "2,8,18,18,6,,"; 
		StandardState = 2; 
		Density = 6.232; 
		MeltingPoint = 722.66; 
		BoilingPoint = 1261; 
		HeatCapacity = 0.202; 
		HeatOfFusion = 17.49; 
		HeatOfVaporization = 114.1; 
		AtomicRadius = 123; 
		CovalentRadius = 135; 
		VanDerWaalsRadius = 206; 
		Electronegativity = 2.1; 
		OxidationStates = "-2,2,4,6"; 
		IonizationEnergy = 869.3; 
		ThermalConductivity = 3; 
		ElectronAffinity = 190.161; 
		AbundanceCrust = 0.001; 
		AbundanceUniverse = 0.0000009; 
		Discovery = 1782; 
		Radioactive = 0; 
		DiscoveredBy = "F.-J.M. von Reichenstein"; 
	}
};
struct Iodine : OOTElement{
	Iodine()
	{
		AtomicNumber = 53; 
		Symbol = "I"; 
		EnglishName = "Iodine"; 
		Group = 17; 
		Period = 5; 
		Block = "p"; 
		Category = 6; 
		AtomicMass = 126.90447; 
		Configuration = "[Kr] 4d10 5s2 5p5"; 
		ShellConfiguration = "2,8,18,18,7,,"; 
		StandardState = 2; 
		Density = 4.93; 
		MeltingPoint = 386.85; 
		BoilingPoint = 457.4; 
		HeatCapacity = 0.214; 
		HeatOfFusion = 15.52; 
		HeatOfVaporization = 41.57; 
		AtomicRadius = 115; 
		CovalentRadius = 133; 
		VanDerWaalsRadius = 198; 
		Electronegativity = 2.66; 
		OxidationStates = "-1,1,3,5,7"; 
		IonizationEnergy = 1008.4; 
		ThermalConductivity = 0.45; 
		ElectronAffinity = 295.1531; 
		AbundanceCrust = 0.45; 
		AbundanceUniverse = 0.0000001; 
		Discovery = 1811; 
		Radioactive = 0; 
		DiscoveredBy = "B. Courtois"; 
	}
};
struct Xenon : OOTElement{
	Xenon()
	{
		AtomicNumber = 54; 
		Symbol = "Xe"; 
		EnglishName = "Xenon"; 
		Group = 18; 
		Period = 5; 
		Block = "p"; 
		Category = 7; 
		AtomicMass = 131.293; 
		Configuration = "[Kr] 4d10 5s2 5p6"; 
		ShellConfiguration = "2,8,18,18,8,,"; 
		StandardState = 0; 
		Density = 0.005887; 
		MeltingPoint = 161.4; 
		BoilingPoint = 165.03; 
		HeatCapacity = 0.158; 
		HeatOfFusion = 2.27; 
		HeatOfVaporization = 12.64; 
		AtomicRadius = 108; 
		CovalentRadius = 130; 
		VanDerWaalsRadius = 216; 
		Electronegativity = 2.6; 
		OxidationStates = "2,4,6"; 
		IonizationEnergy = 1170.4; 
		ThermalConductivity = 0.00565; 
		ElectronAffinity = -80; 
		AbundanceCrust = 0.00003; 
		AbundanceUniverse = 0.000001; 
		Discovery = 1898; 
		Radioactive = 0; 
		DiscoveredBy = "W. Ramsay, W. Travers"; 
	}
};
struct Caesium : OOTElement{
	Caesium()
	{
		AtomicNumber = 55; 
		Symbol = "Cs"; 
		EnglishName = "Caesium"; 
		Group = 1; 
		Period = 6; 
		Block = "s"; 
		Category = 1; 
		AtomicMass = 132.905452; 
		Configuration = "[Xe] 6s1"; 
		ShellConfiguration = "2,8,18,18,8,1,"; 
		StandardState = 2; 
		Density = 1.873; 
		MeltingPoint = 301.59; 
		BoilingPoint = 944; 
		HeatCapacity = 0.242; 
		HeatOfFusion = 2.09; 
		HeatOfVaporization = 63.9; 
		AtomicRadius = 298; 
		CovalentRadius = 225; 
		VanDerWaalsRadius = 343; 
		Electronegativity = 0.79; 
		OxidationStates = "1"; 
		IonizationEnergy = 375.7; 
		ThermalConductivity = 35.9; 
		ElectronAffinity = 45.505; 
		AbundanceCrust = 3; 
		AbundanceUniverse = 0.00000008; 
		Discovery = 1860; 
		Radioactive = 0; 
		DiscoveredBy = "R. Bunsen, R. Kirchhoff"; 
	}
};
struct Barium : OOTElement{
	Barium()
	{
		AtomicNumber = 56; 
		Symbol = "Ba"; 
		EnglishName = "Barium"; 
		Group = 2; 
		Period = 6; 
		Block = "s"; 
		Category = 2; 
		AtomicMass = 137.327; 
		Configuration = "[Xe] 6s2"; 
		ShellConfiguration = "2,8,18,18,8,2,"; 
		StandardState = 2; 
		Density = 3.594; 
		MeltingPoint = 1000; 
		BoilingPoint = 2170; 
		HeatCapacity = 0.204; 
		HeatOfFusion = 7.12; 
		HeatOfVaporization = 140.3; 
		AtomicRadius = 253; 
		CovalentRadius = 198; 
		VanDerWaalsRadius = 268; 
		Electronegativity = 0.89; 
		OxidationStates = "2"; 
		IonizationEnergy = 502.9; 
		ThermalConductivity = 18.4; 
		ElectronAffinity = 13.954; 
		AbundanceCrust = 425; 
		AbundanceUniverse = 0.000001; 
		Discovery = 1772; 
		Radioactive = 0; 
		DiscoveredBy = "W. Scheele"; 
	}
};
struct Lanthanum : OOTElement{
	Lanthanum()
	{
		AtomicNumber = 57; 
		Symbol = "La"; 
		EnglishName = "Lanthanum"; 
		Group = 3; 
		Period = 6; 
		Block = "d"; 
		Category = 8; 
		AtomicMass = 138.90547; 
		Configuration = "[Xe] 5d1 6s2"; 
		ShellConfiguration = "2,8,18,18,9,2,"; 
		StandardState = 2; 
		Density = 6.145; 
		MeltingPoint = 1193; 
		BoilingPoint = 3737; 
		HeatCapacity = 0.195; 
		HeatOfFusion = 6.2; 
		HeatOfVaporization = 400; 
		AtomicRadius = 195; 
		CovalentRadius = 169; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = 1.1; 
		OxidationStates = "3"; 
		IonizationEnergy = 538.1; 
		ThermalConductivity = 13.4; 
		ElectronAffinity = 45.3; 
		AbundanceCrust = 39; 
		AbundanceUniverse = 0.0000002; 
		Discovery = 1838; 
		Radioactive = 0; 
		DiscoveredBy = "G. Mosander"; 
	}
};
struct Cerium : OOTElement{
	Cerium()
	{
		AtomicNumber = 58; 
		Symbol = "Ce"; 
		EnglishName = "Cerium"; 
		Group = (int)'N'; 
		Period = 6; 
		Block = "f"; 
		Category = 8; 
		AtomicMass = 140.116; 
		Configuration = "[Xe] 4f1 5d1 6s2"; 
		ShellConfiguration = "2,8,18,19,9,2,"; 
		StandardState = 2; 
		Density = 6.77; 
		MeltingPoint = 1068; 
		BoilingPoint = 3716; 
		HeatCapacity = 0.192; 
		HeatOfFusion = 5.46; 
		HeatOfVaporization = 398; 
		AtomicRadius = 158; 
		CovalentRadius = (int)'N'; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = 1.12; 
		OxidationStates = "3,4"; 
		IonizationEnergy = 534.4; 
		ThermalConductivity = 11.3; 
		ElectronAffinity = 62.75; 
		AbundanceCrust = 66.5; 
		AbundanceUniverse = 0.000001; 
		Discovery = 1803; 
		Radioactive = 0; 
		DiscoveredBy = "H. Klaproth, J. Berzelius, W. Hisinger"; 
	}
};
struct Praseodymium : OOTElement{
	Praseodymium()
	{
		AtomicNumber = 59; 
		Symbol = "Pr"; 
		EnglishName = "Praseodymium"; 
		Group = (int)'N'; 
		Period = 6; 
		Block = "f"; 
		Category = 8; 
		AtomicMass = 140.90766; 
		Configuration = "[Xe] 4f3 6s2"; 
		ShellConfiguration = "2,8,18,21,8,2,"; 
		StandardState = 2; 
		Density = 6.773; 
		MeltingPoint = 1208; 
		BoilingPoint = 3793; 
		HeatCapacity = 0.193; 
		HeatOfFusion = 6.89; 
		HeatOfVaporization = 331; 
		AtomicRadius = 247; 
		CovalentRadius = (int)'N'; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = 1.13; 
		OxidationStates = "3"; 
		IonizationEnergy = 527; 
		ThermalConductivity = 12.5; 
		ElectronAffinity = 93; 
		AbundanceCrust = 9.2; 
		AbundanceUniverse = 0.0000002; 
		Discovery = 1885; 
		Radioactive = 0; 
		DiscoveredBy = "C. A. von Welsbach"; 
	}
};
struct Neodymium : OOTElement{
	Neodymium()
	{
		AtomicNumber = 60; 
		Symbol = "Nd"; 
		EnglishName = "Neodymium"; 
		Group = (int)'N'; 
		Period = 6; 
		Block = "f"; 
		Category = 8; 
		AtomicMass = 144.242; 
		Configuration = "[Xe] 4f4 6s2"; 
		ShellConfiguration = "2,8,18,22,8,2,"; 
		StandardState = 2; 
		Density = 7.007; 
		MeltingPoint = 1297; 
		BoilingPoint = 3347; 
		HeatCapacity = 0.19; 
		HeatOfFusion = 7.14; 
		HeatOfVaporization = 289; 
		AtomicRadius = 206; 
		CovalentRadius = (int)'N'; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = 1.14; 
		OxidationStates = "3"; 
		IonizationEnergy = 533.1; 
		ThermalConductivity = 16.5; 
		ElectronAffinity = 184.87; 
		AbundanceCrust = 41.5; 
		AbundanceUniverse = 0.000001; 
		Discovery = 1885; 
		Radioactive = 0; 
		DiscoveredBy = "C. A. von Welsbach"; 
	}
};
struct Promethium : OOTElement{
	Promethium()
	{
		AtomicNumber = 61; 
		Symbol = "Pm"; 
		EnglishName = "Promethium"; 
		Group = (int)'N'; 
		Period = 6; 
		Block = "f"; 
		Category = 8; 
		AtomicMass = 145; 
		Configuration = "[Xe] 4f5 6s2"; 
		ShellConfiguration = "2,8,18,23,8,2,"; 
		StandardState = 2; 
		Density = 7.26; 
		MeltingPoint = 1315; 
		BoilingPoint = 3273; 
		HeatCapacity = (int)'N'; 
		HeatOfFusion = 7.13; 
		HeatOfVaporization = 289; 
		AtomicRadius = 205; 
		CovalentRadius = (int)'N'; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = 1.13; 
		OxidationStates = "3"; 
		IonizationEnergy = 540; 
		ThermalConductivity = 17.9; 
		ElectronAffinity = 12.45; 
		AbundanceCrust = 2.00E-19; 
		AbundanceUniverse = (int)'N'; 
		Discovery = 1942; 
		Radioactive = 1; 
		DiscoveredBy = "S. Wu, E.G. Segrè,d H. Bethe"; 
	}
};
struct Samarium : OOTElement{
	Samarium()
	{
		AtomicNumber = 62; 
		Symbol = "Sm"; 
		EnglishName = "Samarium"; 
		Group = (int)'N'; 
		Period = 6; 
		Block = "f"; 
		Category = 8; 
		AtomicMass = 150.36; 
		Configuration = "[Xe] 4f6 6s2"; 
		ShellConfiguration = "2,8,18,24,8,2,"; 
		StandardState = 2; 
		Density = 7.52; 
		MeltingPoint = 1345; 
		BoilingPoint = 2067; 
		HeatCapacity = 0.197; 
		HeatOfFusion = 8.62; 
		HeatOfVaporization = 192; 
		AtomicRadius = 238; 
		CovalentRadius = (int)'N'; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = 1.17; 
		OxidationStates = "3"; 
		IonizationEnergy = 544.5; 
		ThermalConductivity = 13.3; 
		ElectronAffinity = 15.63; 
		AbundanceCrust = 7.05; 
		AbundanceUniverse = 0.0000005; 
		Discovery = 1879; 
		Radioactive = 0; 
		DiscoveredBy = "P.E.L. de Boisbaudran"; 
	}
};
struct Europium : OOTElement{
	Europium()
	{
		AtomicNumber = 63; 
		Symbol = "Eu"; 
		EnglishName = "Europium"; 
		Group = (int)'N'; 
		Period = 6; 
		Block = "f"; 
		Category = 8; 
		AtomicMass = 151.964; 
		Configuration = "[Xe] 4f7 6s2"; 
		ShellConfiguration = "2,8,18,25,8,2,"; 
		StandardState = 2; 
		Density = 5.243; 
		MeltingPoint = 1099; 
		BoilingPoint = 1802; 
		HeatCapacity = 0.182; 
		HeatOfFusion = 9.21; 
		HeatOfVaporization = 176; 
		AtomicRadius = 231; 
		CovalentRadius = (int)'N'; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = 1.2; 
		OxidationStates = "2,3"; 
		IonizationEnergy = 547.1; 
		ThermalConductivity = 13.9; 
		ElectronAffinity = 83.36; 
		AbundanceCrust = 2; 
		AbundanceUniverse = 0.00000005; 
		Discovery = 1896; 
		Radioactive = 0; 
		DiscoveredBy = "E.-A. Demarçay"; 
	}
};
struct Gadolinium : OOTElement{
	Gadolinium()
	{
		AtomicNumber = 64; 
		Symbol = "Gd"; 
		EnglishName = "Gadolinium"; 
		Group = (int)'N'; 
		Period = 6; 
		Block = "f"; 
		Category = 8; 
		AtomicMass = 157.25; 
		Configuration = "[Xe] 4f7 5d1 6s2"; 
		ShellConfiguration = "2,8,18,25,9,2,"; 
		StandardState = 2; 
		Density = 7.895; 
		MeltingPoint = 1585; 
		BoilingPoint = 3546; 
		HeatCapacity = 0.236; 
		HeatOfFusion = 10.05; 
		HeatOfVaporization = 301.3; 
		AtomicRadius = 233; 
		CovalentRadius = (int)'N'; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = 1.2; 
		OxidationStates = "3"; 
		IonizationEnergy = 593.4; 
		ThermalConductivity = 10.6; 
		ElectronAffinity = 13.22; 
		AbundanceCrust = 6.2; 
		AbundanceUniverse = 0.0000002; 
		Discovery = 1880; 
		Radioactive = 0; 
		DiscoveredBy = "J. C. G. de Marignac"; 
	}
};
struct Terbium : OOTElement{
	Terbium()
	{
		AtomicNumber = 65; 
		Symbol = "Tb"; 
		EnglishName = "Terbium"; 
		Group = (int)'N'; 
		Period = 6; 
		Block = "f"; 
		Category = 8; 
		AtomicMass = 158.92535; 
		Configuration = "[Xe] 4f9 6s2"; 
		ShellConfiguration = "2,8,18,27,8,2,"; 
		StandardState = 2; 
		Density = 8.229; 
		MeltingPoint = 1629; 
		BoilingPoint = 3503; 
		HeatCapacity = 0.182; 
		HeatOfFusion = 10.15; 
		HeatOfVaporization = 391; 
		AtomicRadius = 225; 
		CovalentRadius = (int)'N'; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = 1.2; 
		OxidationStates = "3"; 
		IonizationEnergy = 565.8; 
		ThermalConductivity = 11.1; 
		ElectronAffinity = 112.4; 
		AbundanceCrust = 1.2; 
		AbundanceUniverse = 0.00000005; 
		Discovery = 1843; 
		Radioactive = 0; 
		DiscoveredBy = "G. Mosander"; 
	}
};
struct Dysprosium : OOTElement{
	Dysprosium()
	{
		AtomicNumber = 66; 
		Symbol = "Dy"; 
		EnglishName = "Dysprosium"; 
		Group = (int)'N'; 
		Period = 6; 
		Block = "f"; 
		Category = 8; 
		AtomicMass = 162.5; 
		Configuration = "[Xe] 4f10 6s2"; 
		ShellConfiguration = "2,8,18,28,8,2,"; 
		StandardState = 2; 
		Density = 8.55; 
		MeltingPoint = 1680; 
		BoilingPoint = 2840; 
		HeatCapacity = 0.17; 
		HeatOfFusion = 11.06; 
		HeatOfVaporization = 280; 
		AtomicRadius = 228; 
		CovalentRadius = (int)'N'; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = 1.22; 
		OxidationStates = "3"; 
		IonizationEnergy = 573; 
		ThermalConductivity = 10.7; 
		ElectronAffinity = 33.96; 
		AbundanceCrust = 5.2; 
		AbundanceUniverse = 0.0000002; 
		Discovery = 1886; 
		Radioactive = 0; 
		DiscoveredBy = "P.E.L. de Boisbaudran"; 
	}
};
struct Holmium : OOTElement{
	Holmium()
	{
		AtomicNumber = 67; 
		Symbol = "Ho"; 
		EnglishName = "Holmium"; 
		Group = (int)'N'; 
		Period = 6; 
		Block = "f"; 
		Category = 8; 
		AtomicMass = 164.93033; 
		Configuration = "[Xe] 4f11 6s2"; 
		ShellConfiguration = "2,8,18,29,8,2,"; 
		StandardState = 2; 
		Density = 8.795; 
		MeltingPoint = 1734; 
		BoilingPoint = 2993; 
		HeatCapacity = 0.165; 
		HeatOfFusion = 17; 
		HeatOfVaporization = 251; 
		AtomicRadius = 226; 
		CovalentRadius = (int)'N'; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = 1.23; 
		OxidationStates = "3"; 
		IonizationEnergy = 581; 
		ThermalConductivity = 16.2; 
		ElectronAffinity = 32.61; 
		AbundanceCrust = 1.3; 
		AbundanceUniverse = 0.00000005; 
		Discovery = 1878; 
		Radioactive = 0; 
		DiscoveredBy = "J.-L. Soret"; 
	}
};
struct Erbium : OOTElement{
	Erbium()
	{
		AtomicNumber = 68; 
		Symbol = "Er"; 
		EnglishName = "Erbium"; 
		Group = (int)'N'; 
		Period = 6; 
		Block = "f"; 
		Category = 8; 
		AtomicMass = 167.259; 
		Configuration = "[Xe] 4f12 6s2"; 
		ShellConfiguration = "2,8,18,30,8,2,"; 
		StandardState = 2; 
		Density = 9.066; 
		MeltingPoint = 1802; 
		BoilingPoint = 3141; 
		HeatCapacity = 0.168; 
		HeatOfFusion = 19.9; 
		HeatOfVaporization = 280; 
		AtomicRadius = 226; 
		CovalentRadius = (int)'N'; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = 1.24; 
		OxidationStates = "3"; 
		IonizationEnergy = 589.3; 
		ThermalConductivity = 14.5; 
		ElectronAffinity = 30.1; 
		AbundanceCrust = 3.5; 
		AbundanceUniverse = 0.0000002; 
		Discovery = 1843; 
		Radioactive = 0; 
		DiscoveredBy = "G. Mosander"; 
	}
};
struct Thulium : OOTElement{
	Thulium()
	{
		AtomicNumber = 69; 
		Symbol = "Tm"; 
		EnglishName = "Thulium"; 
		Group = (int)'N'; 
		Period = 6; 
		Block = "f"; 
		Category = 8; 
		AtomicMass = 168.93422; 
		Configuration = "[Xe] 4f13 6s2"; 
		ShellConfiguration = "2,8,18,31,8,2,"; 
		StandardState = 2; 
		Density = 9.321; 
		MeltingPoint = 1818; 
		BoilingPoint = 2223; 
		HeatCapacity = 0.16; 
		HeatOfFusion = 16.84; 
		HeatOfVaporization = 191; 
		AtomicRadius = 222; 
		CovalentRadius = (int)'N'; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = 1.25; 
		OxidationStates = "3"; 
		IonizationEnergy = 596.7; 
		ThermalConductivity = 16.9; 
		ElectronAffinity = 99; 
		AbundanceCrust = 0.52; 
		AbundanceUniverse = 0.00000001; 
		Discovery = 1879; 
		Radioactive = 0; 
		DiscoveredBy = "T. Cleve"; 
	}
};
struct Ytterbium : OOTElement{
	Ytterbium()
	{
		AtomicNumber = 70; 
		Symbol = "Yb"; 
		EnglishName = "Ytterbium"; 
		Group = (int)'N'; 
		Period = 6; 
		Block = "f"; 
		Category = 8; 
		AtomicMass = 173.045; 
		Configuration = "[Xe] 4f14 6s2"; 
		ShellConfiguration = "2,8,18,32,8,2,"; 
		StandardState = 2; 
		Density = 6.965; 
		MeltingPoint = 1097; 
		BoilingPoint = 1469; 
		HeatCapacity = 0.155; 
		HeatOfFusion = 7.66; 
		HeatOfVaporization = 129; 
		AtomicRadius = 222; 
		CovalentRadius = (int)'N'; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = 1.1; 
		OxidationStates = "3"; 
		IonizationEnergy = 603.4; 
		ThermalConductivity = 38.5; 
		ElectronAffinity = -1.93; 
		AbundanceCrust = 3.2; 
		AbundanceUniverse = 0.0000002; 
		Discovery = 1878; 
		Radioactive = 0; 
		DiscoveredBy = "J.C.G. de Marignac"; 
	}
};
struct Lutetium : OOTElement{
	Lutetium()
	{
		AtomicNumber = 71; 
		Symbol = "Lu"; 
		EnglishName = "Lutetium"; 
		Group = (int)'N'; 
		Period = 6; 
		Block = "f"; 
		Category = 8; 
		AtomicMass = 174.9668; 
		Configuration = "[Xe] 4f14 5d1 6s2"; 
		ShellConfiguration = "2,8,18,32,9,2,"; 
		StandardState = 2; 
		Density = 9.84; 
		MeltingPoint = 1925; 
		BoilingPoint = 3675; 
		HeatCapacity = 0.154; 
		HeatOfFusion = 22; 
		HeatOfVaporization = 414; 
		AtomicRadius = 217; 
		CovalentRadius = 160; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = 1.27; 
		OxidationStates = "3"; 
		IonizationEnergy = 523.5; 
		ThermalConductivity = 16.4; 
		ElectronAffinity = 33.4; 
		AbundanceCrust = 0.8; 
		AbundanceUniverse = 0.00000001; 
		Discovery = 1906; 
		Radioactive = 0; 
		DiscoveredBy = "C. A. von Welsbach, G. Urbain"; 
	}
};
struct Hafnium : OOTElement{
	Hafnium()
	{
		AtomicNumber = 72; 
		Symbol = "Hf"; 
		EnglishName = "Hafnium"; 
		Group = 4; 
		Period = 6; 
		Block = "d"; 
		Category = 3; 
		AtomicMass = 178.49; 
		Configuration = "[Xe] 4f14 5d2 6s2"; 
		ShellConfiguration = "2,8,18,32,10,2,"; 
		StandardState = 2; 
		Density = 13.31; 
		MeltingPoint = 2506; 
		BoilingPoint = 4876; 
		HeatCapacity = 0.144; 
		HeatOfFusion = 27.2; 
		HeatOfVaporization = 648; 
		AtomicRadius = 208; 
		CovalentRadius = 150; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = 1.3; 
		OxidationStates = "4"; 
		IonizationEnergy = 658.5; 
		ThermalConductivity = 23; 
		ElectronAffinity = 1.64; 
		AbundanceCrust = 3; 
		AbundanceUniverse = 0.00000007; 
		Discovery = 1922; 
		Radioactive = 0; 
		DiscoveredBy = "D. Coster, G. von Hevesy"; 
	}
};
struct Tantalum : OOTElement{
	Tantalum()
	{
		AtomicNumber = 73; 
		Symbol = "Ta"; 
		EnglishName = "Tantalum"; 
		Group = 5; 
		Period = 6; 
		Block = "d"; 
		Category = 3; 
		AtomicMass = 180.94788; 
		Configuration = "[Xe] 4f14 5d3 6s2"; 
		ShellConfiguration = "2,8,18,32,11,2,"; 
		StandardState = 2; 
		Density = 16.654; 
		MeltingPoint = 3290; 
		BoilingPoint = 5731; 
		HeatCapacity = 0.14; 
		HeatOfFusion = 36.57; 
		HeatOfVaporization = 732.8; 
		AtomicRadius = 200; 
		CovalentRadius = 138; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = 1.5; 
		OxidationStates = "5"; 
		IonizationEnergy = 761; 
		ThermalConductivity = 57.5; 
		ElectronAffinity = 31; 
		AbundanceCrust = 2; 
		AbundanceUniverse = 0.000000008; 
		Discovery = 1802; 
		Radioactive = 0; 
		DiscoveredBy = "G. Ekeberg"; 
	}
};
struct Tungsten : OOTElement{
	Tungsten()
	{
		AtomicNumber = 74; 
		Symbol = "W"; 
		EnglishName = "Tungsten"; 
		Group = 6; 
		Period = 6; 
		Block = "d"; 
		Category = 3; 
		AtomicMass = 183.84; 
		Configuration = "[Xe] 4f14 5d4 6s2"; 
		ShellConfiguration = "2,8,18,32,12,2,"; 
		StandardState = 2; 
		Density = 19.25; 
		MeltingPoint = 3695; 
		BoilingPoint = 5828; 
		HeatCapacity = 0.132; 
		HeatOfFusion = 52.31; 
		HeatOfVaporization = 806.7; 
		AtomicRadius = 193; 
		CovalentRadius = 146; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = 2.36; 
		OxidationStates = "2,3,4,5,6"; 
		IonizationEnergy = 770; 
		ThermalConductivity = 173; 
		ElectronAffinity = 78.76; 
		AbundanceCrust = 1.3; 
		AbundanceUniverse = 0.00000005; 
		Discovery = 1781; 
		Radioactive = 0; 
		DiscoveredBy = "W. Scheele"; 
	}
};
struct Rhenium : OOTElement{
	Rhenium()
	{
		AtomicNumber = 75; 
		Symbol = "Re"; 
		EnglishName = "Rhenium"; 
		Group = 7; 
		Period = 6; 
		Block = "d"; 
		Category = 3; 
		AtomicMass = 186.207; 
		Configuration = "[Xe] 4f14 5d5 6s2"; 
		ShellConfiguration = "2,8,18,32,13,2,"; 
		StandardState = 2; 
		Density = 21.02; 
		MeltingPoint = 3459; 
		BoilingPoint = 5869; 
		HeatCapacity = 0.137; 
		HeatOfFusion = 60.43; 
		HeatOfVaporization = 704; 
		AtomicRadius = 188; 
		CovalentRadius = 159; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = 1.9; 
		OxidationStates = "2,4,6,7"; 
		IonizationEnergy = 760; 
		ThermalConductivity = 48; 
		ElectronAffinity = 5.8273; 
		AbundanceCrust = 0.0007; 
		AbundanceUniverse = 0.00000002; 
		Discovery = 1908; 
		Radioactive = 0; 
		DiscoveredBy = "M. Ogawa"; 
	}
};
struct Osmium : OOTElement{
	Osmium()
	{
		AtomicNumber = 76; 
		Symbol = "Os"; 
		EnglishName = "Osmium"; 
		Group = 8; 
		Period = 6; 
		Block = "d"; 
		Category = 3; 
		AtomicMass = 190.23; 
		Configuration = "[Xe] 4f14 5d6 6s2"; 
		ShellConfiguration = "2,8,18,32,14,2,"; 
		StandardState = 2; 
		Density = 22.61; 
		MeltingPoint = 3306; 
		BoilingPoint = 5285; 
		HeatCapacity = 0.13; 
		HeatOfFusion = 57.85; 
		HeatOfVaporization = 678; 
		AtomicRadius = 185; 
		CovalentRadius = 128; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = 2.2; 
		OxidationStates = "2,3,4,6,8"; 
		IonizationEnergy = 840; 
		ThermalConductivity = 87.6; 
		ElectronAffinity = 106.1; 
		AbundanceCrust = 0.002; 
		AbundanceUniverse = 0.0000003; 
		Discovery = 1803; 
		Radioactive = 0; 
		DiscoveredBy = "S. Tennant"; 
	}
};
struct Iridium : OOTElement{
	Iridium()
	{
		AtomicNumber = 77; 
		Symbol = "Ir"; 
		EnglishName = "Iridium"; 
		Group = 9; 
		Period = 6; 
		Block = "d"; 
		Category = 3; 
		AtomicMass = 192.217; 
		Configuration = "[Xe] 4f14 5d7 6s2"; 
		ShellConfiguration = "2,8,18,32,15,2,"; 
		StandardState = 2; 
		Density = 22.56; 
		MeltingPoint = 2719; 
		BoilingPoint = 4701; 
		HeatCapacity = 0.131; 
		HeatOfFusion = 41.12; 
		HeatOfVaporization = 564; 
		AtomicRadius = 180; 
		CovalentRadius = 137; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = 2.2; 
		OxidationStates = "2,3,4,6"; 
		IonizationEnergy = 880; 
		ThermalConductivity = 147; 
		ElectronAffinity = 150.94; 
		AbundanceCrust = 0.001; 
		AbundanceUniverse = 0.0000002; 
		Discovery = 1803; 
		Radioactive = 0; 
		DiscoveredBy = "S. Tennant"; 
	}
};
struct Platinum : OOTElement{
	Platinum()
	{
		AtomicNumber = 78; 
		Symbol = "Pt"; 
		EnglishName = "Platinum"; 
		Group = 10; 
		Period = 6; 
		Block = "d"; 
		Category = 3; 
		AtomicMass = 195.084; 
		Configuration = "[Xe] 4f14 5d9 6s1"; 
		ShellConfiguration = "2,8,18,32,17,1,"; 
		StandardState = 2; 
		Density = 21.46; 
		MeltingPoint = 2041.4; 
		BoilingPoint = 4098; 
		HeatCapacity = 0.133; 
		HeatOfFusion = 22.17; 
		HeatOfVaporization = 510; 
		AtomicRadius = 177; 
		CovalentRadius = 128; 
		VanDerWaalsRadius = 175; 
		Electronegativity = 2.28; 
		OxidationStates = "2,4"; 
		IonizationEnergy = 870; 
		ThermalConductivity = 71.6; 
		ElectronAffinity = 205.041; 
		AbundanceCrust = 0.005; 
		AbundanceUniverse = 0.0000005; 
		Discovery = 1735; 
		Radioactive = 0; 
		DiscoveredBy = "A. de Ulloa"; 
	}
};
struct Gold : OOTElement{
	Gold()
	{
		AtomicNumber = 79; 
		Symbol = "Au"; 
		EnglishName = "Gold"; 
		Group = 11; 
		Period = 6; 
		Block = "d"; 
		Category = 3; 
		AtomicMass = 196.966569; 
		Configuration = "[Xe] 4f14 5d10 6s1"; 
		ShellConfiguration = "2,8,18,32,18,1,"; 
		StandardState = 2; 
		Density = 19.282; 
		MeltingPoint = 1337.33; 
		BoilingPoint = 3129; 
		HeatCapacity = 0.129; 
		HeatOfFusion = 12.55; 
		HeatOfVaporization = 342; 
		AtomicRadius = 174; 
		CovalentRadius = 144; 
		VanDerWaalsRadius = 166; 
		Electronegativity = 2.54; 
		OxidationStates = "1,3"; 
		IonizationEnergy = 890.1; 
		ThermalConductivity = 318; 
		ElectronAffinity = 222.747; 
		AbundanceCrust = 0.004; 
		AbundanceUniverse = 0.00000006; 
		Discovery = -6000; 
		Radioactive = 0; 
		DiscoveredBy = (const char*)"NULL"; 
	}
};
struct Mercury : OOTElement{
	Mercury()
	{
		AtomicNumber = 80; 
		Symbol = "Hg"; 
		EnglishName = "Mercury"; 
		Group = 12; 
		Period = 6; 
		Block = "d"; 
		Category = 3; 
		AtomicMass = 200.592; 
		Configuration = "[Xe] 4f14 5d10 6s2"; 
		ShellConfiguration = "2,8,18,32,18,2,"; 
		StandardState = 1; 
		Density = 13.5336; 
		MeltingPoint = 234.43; 
		BoilingPoint = 629.88; 
		HeatCapacity = 0.14; 
		HeatOfFusion = 2.29; 
		HeatOfVaporization = 59.11; 
		AtomicRadius = 171; 
		CovalentRadius = 149; 
		VanDerWaalsRadius = 155; 
		Electronegativity = 2; 
		OxidationStates = "1,2"; 
		IonizationEnergy = 1007.1; 
		ThermalConductivity = 8.3; 
		ElectronAffinity = -50; 
		AbundanceCrust = 0.085; 
		AbundanceUniverse = 0.0000001; 
		Discovery = -2000; 
		Radioactive = 0; 
		DiscoveredBy = (const char*)"NULL"; 
	}
};
struct Thallium : OOTElement{
	Thallium()
	{
		AtomicNumber = 81; 
		Symbol = "Tl"; 
		EnglishName = "Thallium"; 
		Group = 13; 
		Period = 6; 
		Block = "p"; 
		Category = 4; 
		AtomicMass = 204.38; 
		Configuration = "[Xe] 4f14 5d10 6s2 6p1"; 
		ShellConfiguration = "2,8,18,32,18,3,"; 
		StandardState = 2; 
		Density = 11.85; 
		MeltingPoint = 577; 
		BoilingPoint = 1746; 
		HeatCapacity = 0.129; 
		HeatOfFusion = 4.14; 
		HeatOfVaporization = 165; 
		AtomicRadius = 156; 
		CovalentRadius = 148; 
		VanDerWaalsRadius = 196; 
		Electronegativity = 1.62; 
		OxidationStates = "1,3"; 
		IonizationEnergy = 589.4; 
		ThermalConductivity = 46.1; 
		ElectronAffinity = 36.4; 
		AbundanceCrust = 0.85; 
		AbundanceUniverse = 0.00000005; 
		Discovery = 1861; 
		Radioactive = 0; 
		DiscoveredBy = "W. Crookes"; 
	}
};
struct Lead : OOTElement{
	Lead()
	{
		AtomicNumber = 82; 
		Symbol = "Pb"; 
		EnglishName = "Lead"; 
		Group = 14; 
		Period = 6; 
		Block = "p"; 
		Category = 4; 
		AtomicMass = 207.2; 
		Configuration = "[Xe] 4f14 5d10 6s2 6p2"; 
		ShellConfiguration = "2,8,18,32,18,4,"; 
		StandardState = 2; 
		Density = 11.342; 
		MeltingPoint = 600.61; 
		BoilingPoint = 2022; 
		HeatCapacity = 0.129; 
		HeatOfFusion = 4.77; 
		HeatOfVaporization = 179.5; 
		AtomicRadius = 154; 
		CovalentRadius = 147; 
		VanDerWaalsRadius = 202; 
		Electronegativity = 1.87; 
		OxidationStates = "2,4"; 
		IonizationEnergy = 715.6; 
		ThermalConductivity = 35.3; 
		ElectronAffinity = 34.4204; 
		AbundanceCrust = 14; 
		AbundanceUniverse = 0.000001; 
		Discovery = -7000; 
		Radioactive = 0; 
		DiscoveredBy = (const char*)"NULL"; 
	}
};
struct Bismuth : OOTElement{
	Bismuth()
	{
		AtomicNumber = 83; 
		Symbol = "Bi"; 
		EnglishName = "Bismuth"; 
		Group = 15; 
		Period = 6; 
		Block = "p"; 
		Category = 4; 
		AtomicMass = 208.9804; 
		Configuration = "[Xe] 4f14 5d10 6s2 6p3"; 
		ShellConfiguration = "2,8,18,32,18,5,"; 
		StandardState = 2; 
		Density = 9.807; 
		MeltingPoint = 544.7; 
		BoilingPoint = 1837; 
		HeatCapacity = 0.122; 
		HeatOfFusion = 11.3; 
		HeatOfVaporization = 179; 
		AtomicRadius = 143; 
		CovalentRadius = 146; 
		VanDerWaalsRadius = 207; 
		Electronegativity = 2.02; 
		OxidationStates = "3,5"; 
		IonizationEnergy = 703; 
		ThermalConductivity = 7.97; 
		ElectronAffinity = 90.924; 
		AbundanceCrust = 0.009; 
		AbundanceUniverse = 0.00000007; 
		Discovery = 1753; 
		Radioactive = 0; 
		DiscoveredBy = "C.F. Geoffroy"; 
	}
};
struct Polonium : OOTElement{
	Polonium()
	{
		AtomicNumber = 84; 
		Symbol = "Po"; 
		EnglishName = "Polonium"; 
		Group = 16; 
		Period = 6; 
		Block = "p"; 
		Category = 5; 
		AtomicMass = 209; 
		Configuration = "[Xe] 4f14 5d10 6s2 6p4"; 
		ShellConfiguration = "2,8,18,32,18,6,"; 
		StandardState = 2; 
		Density = 9.32; 
		MeltingPoint = 527; 
		BoilingPoint = 1235; 
		HeatCapacity = (int)'N'; 
		HeatOfFusion = 13; 
		HeatOfVaporization = 102.91; 
		AtomicRadius = 135; 
		CovalentRadius = (int)'N'; 
		VanDerWaalsRadius = 197; 
		Electronegativity = 2; 
		OxidationStates = "-2,2,4,6"; 
		IonizationEnergy = 812.1; 
		ThermalConductivity = (int)'N'; 
		ElectronAffinity = 183.3; 
		AbundanceCrust = 2.00E-10; 
		AbundanceUniverse = (int)'N'; 
		Discovery = 1898; 
		Radioactive = 1; 
		DiscoveredBy = "P. Curie, M. Curie"; 
	}
};
struct Astatine : OOTElement{
	Astatine()
	{
		AtomicNumber = 85; 
		Symbol = "At"; 
		EnglishName = "Astatine"; 
		Group = 17; 
		Period = 6; 
		Block = "p"; 
		Category = 6; 
		AtomicMass = 210; 
		Configuration = "[Xe] 4f14 5d10 6s2 6p5"; 
		ShellConfiguration = "2,8,18,32,18,7,"; 
		StandardState = 2; 
		Density = 7; 
		MeltingPoint = 575; 
		BoilingPoint = 610; 
		HeatCapacity = (int)'N'; 
		HeatOfFusion = (int)'N'; 
		HeatOfVaporization = 54.39; 
		AtomicRadius = 127; 
		CovalentRadius = (int)'N'; 
		VanDerWaalsRadius = 202; 
		Electronegativity = 2.2; 
		OxidationStates = "-1,1,3,5,7"; 
		IonizationEnergy = 899.003; 
		ThermalConductivity = 1.7; 
		ElectronAffinity = 221.9; 
		AbundanceCrust = 3.00E-20; 
		AbundanceUniverse = (int)'N'; 
		Discovery = 1940; 
		Radioactive = 1; 
		DiscoveredBy = "R. Corson, R. MacKenzie, E. Segrè"; 
	}
};
struct Radon : OOTElement{
	Radon()
	{
		AtomicNumber = 86; 
		Symbol = "Rn"; 
		EnglishName = "Radon"; 
		Group = 18; 
		Period = 6; 
		Block = "p"; 
		Category = 7; 
		AtomicMass = 222; 
		Configuration = "[Xe] 4f14 5d10 6s2 6p6"; 
		ShellConfiguration = "2,8,18,32,18,8,"; 
		StandardState = 0; 
		Density = 0.00973; 
		MeltingPoint = 202; 
		BoilingPoint = 211.3; 
		HeatCapacity = 0.094; 
		HeatOfFusion = 3.247; 
		HeatOfVaporization = 18.1; 
		AtomicRadius = 120; 
		CovalentRadius = 145; 
		VanDerWaalsRadius = 220; 
		Electronegativity = 2.2; 
		OxidationStates = "0,2,6"; 
		IonizationEnergy = 1037; 
		ThermalConductivity = 0.00361; 
		ElectronAffinity = -70; 
		AbundanceCrust = 4.00E-13; 
		AbundanceUniverse = (int)'N'; 
		Discovery = 1899; 
		Radioactive = 1; 
		DiscoveredBy = "E. Rutherford, R. B. Owens"; 
	}
};
struct Francium : OOTElement{
	Francium()
	{
		AtomicNumber = 87; 
		Symbol = "Fr"; 
		EnglishName = "Francium"; 
		Group = 1; 
		Period = 7; 
		Block = "s"; 
		Category = 1; 
		AtomicMass = 223; 
		Configuration = "[Rn] 7s1"; 
		ShellConfiguration = "2,8,18,32,18,8,1"; 
		StandardState = 2; 
		Density = 1.87; 
		MeltingPoint = 300; 
		BoilingPoint = 950; 
		HeatCapacity = (int)'N'; 
		HeatOfFusion = 2; 
		HeatOfVaporization = 65; 
		AtomicRadius = (int)'N'; 
		CovalentRadius = (int)'N'; 
		VanDerWaalsRadius = 348; 
		Electronegativity = 0.7; 
		OxidationStates = "1"; 
		IonizationEnergy = 380; 
		ThermalConductivity = (int)'N'; 
		ElectronAffinity = 46.89; 
		AbundanceCrust = 1.00E-18; 
		AbundanceUniverse = (int)'N'; 
		Discovery = 1939; 
		Radioactive = 1; 
		DiscoveredBy = "M. Perey"; 
	}
};
struct Radium : OOTElement{
	Radium()
	{
		AtomicNumber = 88; 
		Symbol = "Ra"; 
		EnglishName = "Radium"; 
		Group = 2; 
		Period = 7; 
		Block = "s"; 
		Category = 2; 
		AtomicMass = 226; 
		Configuration = "[Rn] 7s2"; 
		ShellConfiguration = "2,8,18,32,18,8,2"; 
		StandardState = 2; 
		Density = 5.5; 
		MeltingPoint = 973; 
		BoilingPoint = 2010; 
		HeatCapacity = 0.094; 
		HeatOfFusion = 8.5; 
		HeatOfVaporization = 113; 
		AtomicRadius = (int)'N'; 
		CovalentRadius = (int)'N'; 
		VanDerWaalsRadius = 283; 
		Electronegativity = 0.9; 
		OxidationStates = "2"; 
		IonizationEnergy = 509.3; 
		ThermalConductivity = 18.6; 
		ElectronAffinity = 9.6485; 
		AbundanceCrust = 9.00E-07; 
		AbundanceUniverse = (int)'N'; 
		Discovery = 1898; 
		Radioactive = 1; 
		DiscoveredBy = "P. Curie, M. Curie"; 
	}
};
struct Actinium : OOTElement{
	Actinium()
	{
		AtomicNumber = 89; 
		Symbol = "Ac"; 
		EnglishName = "Actinium"; 
		Group = 3; 
		Period = 7; 
		Block = "d"; 
		Category = 9; 
		AtomicMass = 227; 
		Configuration = "[Rn] 6d1 7s2"; 
		ShellConfiguration = "2,8,18,32,18,9,2"; 
		StandardState = 2; 
		Density = 10.07; 
		MeltingPoint = 1323; 
		BoilingPoint = 3471; 
		HeatCapacity = 0.12; 
		HeatOfFusion = 14; 
		HeatOfVaporization = 400; 
		AtomicRadius = (int)'N'; 
		CovalentRadius = (int)'N'; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = 1.1; 
		OxidationStates = "3"; 
		IonizationEnergy = 499; 
		ThermalConductivity = 12; 
		ElectronAffinity = 33.77; 
		AbundanceCrust = 5.50E-10; 
		AbundanceUniverse = (int)'N'; 
		Discovery = 1902; 
		Radioactive = 1; 
		DiscoveredBy = "F. O. Giesel"; 
	}
};
struct Thorium : OOTElement{
	Thorium()
	{
		AtomicNumber = 90; 
		Symbol = "Th"; 
		EnglishName = "Thorium"; 
		Group = (int)'N'; 
		Period = 7; 
		Block = "f"; 
		Category = 9; 
		AtomicMass = 232.0377; 
		Configuration = "[Rn] 6d2 7s2"; 
		ShellConfiguration = "2,8,18,32,18,10,2"; 
		StandardState = 2; 
		Density = 11.72; 
		MeltingPoint = 2115; 
		BoilingPoint = 5061; 
		HeatCapacity = 0.113; 
		HeatOfFusion = 13.81; 
		HeatOfVaporization = 514; 
		AtomicRadius = (int)'N'; 
		CovalentRadius = (int)'N'; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = 1.3; 
		OxidationStates = "4"; 
		IonizationEnergy = 587; 
		ThermalConductivity = 54; 
		ElectronAffinity = 112.72; 
		AbundanceCrust = 9.6; 
		AbundanceUniverse = 0.00000004; 
		Discovery = 1829; 
		Radioactive = 1; 
		DiscoveredBy = "J. Berzelius"; 
	}
};
struct Protactinium : OOTElement{
	Protactinium()
	{
		AtomicNumber = 91; 
		Symbol = "Pa"; 
		EnglishName = "Protactinium"; 
		Group = (int)'N'; 
		Period = 7; 
		Block = "f"; 
		Category = 9; 
		AtomicMass = 231.03588; 
		Configuration = "[Rn] 5f2 6d1 7s2"; 
		ShellConfiguration = "2,8,18,32,20,9,2"; 
		StandardState = 2; 
		Density = 15.37; 
		MeltingPoint = 1841; 
		BoilingPoint = 4300; 
		HeatCapacity = (int)'N'; 
		HeatOfFusion = 12.34; 
		HeatOfVaporization = 481; 
		AtomicRadius = (int)'N'; 
		CovalentRadius = (int)'N'; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = 1.5; 
		OxidationStates = "5"; 
		IonizationEnergy = 568; 
		ThermalConductivity = 47; 
		ElectronAffinity = 53.03; 
		AbundanceCrust = 1.40E-06; 
		AbundanceUniverse = (int)'N'; 
		Discovery = 1913; 
		Radioactive = 1; 
		DiscoveredBy = "O. H. Göhring, K. Fajans"; 
	}
};
struct Uranium : OOTElement{
	Uranium()
	{
		AtomicNumber = 92; 
		Symbol = "U"; 
		EnglishName = "Uranium"; 
		Group = (int)'N'; 
		Period = 7; 
		Block = "f"; 
		Category = 9; 
		AtomicMass = 238.02891; 
		Configuration = "[Rn] 5f3 6d1 7s2"; 
		ShellConfiguration = "2,8,18,32,21,9,2"; 
		StandardState = 2; 
		Density = 18.95; 
		MeltingPoint = 1405.3; 
		BoilingPoint = 4404; 
		HeatCapacity = 0.116; 
		HeatOfFusion = 9.14; 
		HeatOfVaporization = 417.1; 
		AtomicRadius = (int)'N'; 
		CovalentRadius = (int)'N'; 
		VanDerWaalsRadius = 186; 
		Electronegativity = 1.38; 
		OxidationStates = "6"; 
		IonizationEnergy = 597.6; 
		ThermalConductivity = 27.5; 
		ElectronAffinity = 50.94; 
		AbundanceCrust = 2.7; 
		AbundanceUniverse = 0.00000002; 
		Discovery = 1789; 
		Radioactive = 1; 
		DiscoveredBy = "H. Klaproth"; 
	}
};
struct Neptunium : OOTElement{
	Neptunium()
	{
		AtomicNumber = 93; 
		Symbol = "Np"; 
		EnglishName = "Neptunium"; 
		Group = (int)'N'; 
		Period = 7; 
		Block = "f"; 
		Category = 9; 
		AtomicMass = 237; 
		Configuration = "[Rn] 5f4 6d1 7s2"; 
		ShellConfiguration = "2,8,18,32,22,9,2"; 
		StandardState = 2; 
		Density = 20.45; 
		MeltingPoint = 917; 
		BoilingPoint = 4273; 
		HeatCapacity = (int)'N'; 
		HeatOfFusion = 3.2; 
		HeatOfVaporization = 336; 
		AtomicRadius = (int)'N'; 
		CovalentRadius = (int)'N'; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = 1.36; 
		OxidationStates = "5"; 
		IonizationEnergy = 604.5; 
		ThermalConductivity = 6.3; 
		ElectronAffinity = 45.85; 
		AbundanceCrust = 3.00E-12; 
		AbundanceUniverse = (int)'N'; 
		Discovery = 1940; 
		Radioactive = 1; 
		DiscoveredBy = "E.M. McMillan, H. Abelson"; 
	}
};
struct Plutonium : OOTElement{
	Plutonium()
	{
		AtomicNumber = 94; 
		Symbol = "Pu"; 
		EnglishName = "Plutonium"; 
		Group = (int)'N'; 
		Period = 7; 
		Block = "f"; 
		Category = 9; 
		AtomicMass = 244; 
		Configuration = "[Rn] 5f6 7s2"; 
		ShellConfiguration = "2,8,18,32,24,8,2"; 
		StandardState = 2; 
		Density = 19.84; 
		MeltingPoint = 912.5; 
		BoilingPoint = 3501; 
		HeatCapacity = (int)'N'; 
		HeatOfFusion = 2.82; 
		HeatOfVaporization = 333.5; 
		AtomicRadius = (int)'N'; 
		CovalentRadius = (int)'N'; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = 1.28; 
		OxidationStates = "4"; 
		IonizationEnergy = 584.7; 
		ThermalConductivity = 6.74; 
		ElectronAffinity = -48.33; 
		AbundanceCrust = 3.00E-11; 
		AbundanceUniverse = (int)'N'; 
		Discovery = 1941; 
		Radioactive = 1; 
		DiscoveredBy = "Glenn T. Seaborg, Arthur C. Wahl, W. Kennedy, E.M. McMillan"; 
	}
};
struct Americium : OOTElement{
	Americium()
	{
		AtomicNumber = 95; 
		Symbol = "Am"; 
		EnglishName = "Americium"; 
		Group = (int)'N'; 
		Period = 7; 
		Block = "f"; 
		Category = 9; 
		AtomicMass = 243; 
		Configuration = "[Rn] 5f7 7s2"; 
		ShellConfiguration = "2,8,18,32,25,8,2"; 
		StandardState = 2; 
		Density = 13.69; 
		MeltingPoint = 1449; 
		BoilingPoint = 2880; 
		HeatCapacity = (int)'N'; 
		HeatOfFusion = 14.39; 
		HeatOfVaporization = (int)'N'; 
		AtomicRadius = (int)'N'; 
		CovalentRadius = (int)'N'; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = 1.13; 
		OxidationStates = "3"; 
		IonizationEnergy = 578; 
		ThermalConductivity = 10; 
		ElectronAffinity = 9.93; 
		AbundanceCrust = 0; 
		AbundanceUniverse = (int)'N'; 
		Discovery = 1944; 
		Radioactive = 1; 
		DiscoveredBy = "G. T. Seaborg, R. A. James, O. Morgan, A. Ghiorso"; 
	}
};
struct Curium : OOTElement{
	Curium()
	{
		AtomicNumber = 96; 
		Symbol = "Cm"; 
		EnglishName = "Curium"; 
		Group = (int)'N'; 
		Period = 7; 
		Block = "f"; 
		Category = 9; 
		AtomicMass = 247; 
		Configuration = "[Rn] 5f7 6d1 7s2"; 
		ShellConfiguration = "2,8,18,32,25,9,2"; 
		StandardState = 2; 
		Density = 13.51; 
		MeltingPoint = 1613; 
		BoilingPoint = 3383; 
		HeatCapacity = (int)'N'; 
		HeatOfFusion = (int)'N'; 
		HeatOfVaporization = (int)'N'; 
		AtomicRadius = (int)'N'; 
		CovalentRadius = (int)'N'; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = 1.28; 
		OxidationStates = "3"; 
		IonizationEnergy = 581; 
		ThermalConductivity = (int)'N'; 
		ElectronAffinity = 27.17; 
		AbundanceCrust = 0; 
		AbundanceUniverse = (int)'N'; 
		Discovery = 1944; 
		Radioactive = 1; 
		DiscoveredBy = "G. T. Seaborg, R. A. James, A. Ghiorso"; 
	}
};
struct Berkelium : OOTElement{
	Berkelium()
	{
		AtomicNumber = 97; 
		Symbol = "Bk"; 
		EnglishName = "Berkelium"; 
		Group = (int)'N'; 
		Period = 7; 
		Block = "f"; 
		Category = 9; 
		AtomicMass = 247; 
		Configuration = "[Rn] 5f9 7s2"; 
		ShellConfiguration = "2,8,18,32,27,8,2"; 
		StandardState = 2; 
		Density = 14.79; 
		MeltingPoint = 1259; 
		BoilingPoint = 2900; 
		HeatCapacity = (int)'N'; 
		HeatOfFusion = (int)'N'; 
		HeatOfVaporization = (int)'N'; 
		AtomicRadius = (int)'N'; 
		CovalentRadius = (int)'N'; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = 1.3; 
		OxidationStates = "3"; 
		IonizationEnergy = 601; 
		ThermalConductivity = 10; 
		ElectronAffinity = -165.24; 
		AbundanceCrust = 0; 
		AbundanceUniverse = (int)'N'; 
		Discovery = 1949; 
		Radioactive = 1; 
		DiscoveredBy = "S. G. Thompson, A. Ghiorso, G. T. Seaborg (UC Berkeley)"; 
	}
};
struct Californium : OOTElement{
	Californium()
	{
		AtomicNumber = 98; 
		Symbol = "Cf"; 
		EnglishName = "Californium"; 
		Group = (int)'N'; 
		Period = 7; 
		Block = "f"; 
		Category = 9; 
		AtomicMass = 251; 
		Configuration = "[Rn] 5f10 7s2"; 
		ShellConfiguration = "2,8,18,32,28,8,2"; 
		StandardState = 2; 
		Density = 15.1; 
		MeltingPoint = 1173; 
		BoilingPoint = 1743; 
		HeatCapacity = (int)'N'; 
		HeatOfFusion = (int)'N'; 
		HeatOfVaporization = (int)'N'; 
		AtomicRadius = (int)'N'; 
		CovalentRadius = (int)'N'; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = 1.3; 
		OxidationStates = "3"; 
		IonizationEnergy = 608; 
		ThermalConductivity = (int)'N'; 
		ElectronAffinity = -97.31; 
		AbundanceCrust = 0; 
		AbundanceUniverse = (int)'N'; 
		Discovery = 1950; 
		Radioactive = 1; 
		DiscoveredBy = "S. G. Thompson, K. Street Jr., A. Ghiorso, G. T. Seaborg (UC Berkeley)"; 
	}
};
struct Einsteinium : OOTElement{
	Einsteinium()
	{
		AtomicNumber = 99; 
		Symbol = "Es"; 
		EnglishName = "Einsteinium"; 
		Group = (int)'N'; 
		Period = 7; 
		Block = "f"; 
		Category = 9; 
		AtomicMass = 252; 
		Configuration = "[Rn] 5f11 7s2"; 
		ShellConfiguration = "2,8,18,32,29,8,2"; 
		StandardState = 2; 
		Density = 8.84; 
		MeltingPoint = 1133; 
		BoilingPoint = 1269; 
		HeatCapacity = (int)'N'; 
		HeatOfFusion = (int)'N'; 
		HeatOfVaporization = (int)'N'; 
		AtomicRadius = (int)'N'; 
		CovalentRadius = (int)'N'; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = 1.3; 
		OxidationStates = "3"; 
		IonizationEnergy = 619; 
		ThermalConductivity = (int)'N'; 
		ElectronAffinity = -28.6; 
		AbundanceCrust = 0; 
		AbundanceUniverse = (int)'N'; 
		Discovery = 1952; 
		Radioactive = 1; 
		DiscoveredBy = "A. Ghiorso et al. (Argonne Laboratory, Los Alamos Laboratory, UC Berkeley)"; 
	}
};
struct Fermium : OOTElement{
	Fermium()
	{
		AtomicNumber = 100; 
		Symbol = "Fm"; 
		EnglishName = "Fermium"; 
		Group = (int)'N'; 
		Period = 7; 
		Block = "f"; 
		Category = 9; 
		AtomicMass = 257; 
		Configuration = "[Rn] 5f12 7s2"; 
		ShellConfiguration = "2,8,18,32,30,8,2"; 
		StandardState = 2; 
		Density = 9.7; 
		MeltingPoint = 1125; 
		BoilingPoint = (int)'N'; 
		HeatCapacity = (int)'N'; 
		HeatOfFusion = (int)'N'; 
		HeatOfVaporization = (int)'N'; 
		AtomicRadius = (int)'N'; 
		CovalentRadius = (int)'N'; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = 1.3; 
		OxidationStates = "3"; 
		IonizationEnergy = 627; 
		ThermalConductivity = (int)'N'; 
		ElectronAffinity = 33.96; 
		AbundanceCrust = 0; 
		AbundanceUniverse = (int)'N'; 
		Discovery = 1952; 
		Radioactive = 1; 
		DiscoveredBy = "A. Ghiorso et al. (Argonne Laboratory, Los Alamos Laboratory, UC Berkeley)"; 
	}
};
struct Mendelevium : OOTElement{
	Mendelevium()
	{
		AtomicNumber = 101; 
		Symbol = "Md"; 
		EnglishName = "Mendelevium"; 
		Group = (int)'N'; 
		Period = 7; 
		Block = "f"; 
		Category = 9; 
		AtomicMass = 258; 
		Configuration = "[Rn] 5f13 7s2"; 
		ShellConfiguration = "2,8,18,32,31,8,2"; 
		StandardState = 2; 
		Density = 10.3; 
		MeltingPoint = 1100; 
		BoilingPoint = (int)'N'; 
		HeatCapacity = (int)'N'; 
		HeatOfFusion = (int)'N'; 
		HeatOfVaporization = (int)'N'; 
		AtomicRadius = (int)'N'; 
		CovalentRadius = (int)'N'; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = 1.3; 
		OxidationStates = "3"; 
		IonizationEnergy = 635; 
		ThermalConductivity = (int)'N'; 
		ElectronAffinity = 93.91; 
		AbundanceCrust = 0; 
		AbundanceUniverse = (int)'N'; 
		Discovery = 1955; 
		Radioactive = 1; 
		DiscoveredBy = "A. Ghiorso, G. Harvey, R. Choppin, S. G. Thompson, G. T. Seaborg (Berkeley Radiation Laboratory)"; 
	}
};
struct Nobelium : OOTElement{
	Nobelium()
	{
		AtomicNumber = 102; 
		Symbol = "No"; 
		EnglishName = "Nobelium"; 
		Group = (int)'N'; 
		Period = 7; 
		Block = "f"; 
		Category = 9; 
		AtomicMass = 259; 
		Configuration = "[Rn] 5f14 7s2"; 
		ShellConfiguration = "2,8,18,32,32,8,2"; 
		StandardState = 2; 
		Density = 9.9; 
		MeltingPoint = 1100; 
		BoilingPoint = (int)'N'; 
		HeatCapacity = (int)'N'; 
		HeatOfFusion = (int)'N'; 
		HeatOfVaporization = (int)'N'; 
		AtomicRadius = (int)'N'; 
		CovalentRadius = (int)'N'; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = 1.3; 
		OxidationStates = "2"; 
		IonizationEnergy = 642; 
		ThermalConductivity = (int)'N'; 
		ElectronAffinity = -223.22; 
		AbundanceCrust = 0; 
		AbundanceUniverse = (int)'N'; 
		Discovery = 1966; 
		Radioactive = 1; 
		DiscoveredBy = "E. D. Donets, V. A. Shchegolev, V. A. Ermakov (JINR Dubna)"; 
	}
};
struct Lawrencium : OOTElement{
	Lawrencium()
	{
		AtomicNumber = 103; 
		Symbol = "Lr"; 
		EnglishName = "Lawrencium"; 
		Group = (int)'N'; 
		Period = 7; 
		Block = "f"; 
		Category = 9; 
		AtomicMass = 266; 
		Configuration = "[Rn] 5f14 7s2 7p1"; 
		ShellConfiguration = "2,8,18,32,32,8,3"; 
		StandardState = 2; 
		Density = 15.6; 
		MeltingPoint = 1900; 
		BoilingPoint = (int)'N'; 
		HeatCapacity = (int)'N'; 
		HeatOfFusion = (int)'N'; 
		HeatOfVaporization = (int)'N'; 
		AtomicRadius = (int)'N'; 
		CovalentRadius = (int)'N'; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = 1.3; 
		OxidationStates = "3"; 
		IonizationEnergy = 470; 
		ThermalConductivity = (int)'N'; 
		ElectronAffinity = -30.04; 
		AbundanceCrust = 0; 
		AbundanceUniverse = (int)'N'; 
		Discovery = 1961; 
		Radioactive = 1; 
		DiscoveredBy = "A. Ghiorso, T. Sikkeland, E. Larsh, M. Latimer (Berkeley Radiation Laboratory)"; 
	}
};
struct Rutherfordium : OOTElement{
	Rutherfordium()
	{
		AtomicNumber = 104; 
		Symbol = "Rf"; 
		EnglishName = "Rutherfordium"; 
		Group = 4; 
		Period = 7; 
		Block = "d"; 
		Category = 3; 
		AtomicMass = 267; 
		Configuration = "[Rn] 5f14 6d2 7s2"; 
		ShellConfiguration = "2,8,18,32,32,10,2"; 
		StandardState = 2; 
		Density = 23.2; 
		MeltingPoint = 2400; 
		BoilingPoint = 5800; 
		HeatCapacity = (int)'N'; 
		HeatOfFusion = (int)'N'; 
		HeatOfVaporization = (int)'N'; 
		AtomicRadius = (int)'N'; 
		CovalentRadius = (int)'N'; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = (int)'N'; 
		OxidationStates = "3,4"; 
		IonizationEnergy = 580; 
		ThermalConductivity = (int)'N'; 
		ElectronAffinity = (int)'N'; 
		AbundanceCrust = 0; 
		AbundanceUniverse = (int)'N'; 
		Discovery = 1969; 
		Radioactive = 1; 
		DiscoveredBy = "A. Ghiorso et al. (Berkeley Radiation Laboratory), I. Zvara et al. (JINR Dubna)"; 
	}
};
struct Dubnium : OOTElement{
	Dubnium()
	{
		AtomicNumber = 105; 
		Symbol = "Db"; 
		EnglishName = "Dubnium"; 
		Group = 5; 
		Period = 7; 
		Block = "d"; 
		Category = 3; 
		AtomicMass = 268; 
		Configuration = "[Rn] 5f14 6d3 7s2"; 
		ShellConfiguration = "2,8,18,32,32,11,2"; 
		StandardState = 2; 
		Density = 29.3; 
		MeltingPoint = (int)'N'; 
		BoilingPoint = (int)'N'; 
		HeatCapacity = (int)'N'; 
		HeatOfFusion = (int)'N'; 
		HeatOfVaporization = (int)'N'; 
		AtomicRadius = (int)'N'; 
		CovalentRadius = (int)'N'; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = (int)'N'; 
		OxidationStates = "5"; 
		IonizationEnergy = (int)'N'; 
		ThermalConductivity = (int)'N'; 
		ElectronAffinity = (int)'N'; 
		AbundanceCrust = 0; 
		AbundanceUniverse = (int)'N'; 
		Discovery = 1970; 
		Radioactive = 1; 
		DiscoveredBy = "A. Ghiorso et al. (Berkeley Radiation Laboratory), V. A. Druin et al. (JINR Dubna)"; 
	}
};
struct Seaborgium : OOTElement{
	Seaborgium()
	{
		AtomicNumber = 106; 
		Symbol = "Sg"; 
		EnglishName = "Seaborgium"; 
		Group = 6; 
		Period = 7; 
		Block = "d"; 
		Category = 3; 
		AtomicMass = 269; 
		Configuration = "[Rn] 5f14 6d4 7s2"; 
		ShellConfiguration = "2,8,18,32,32,12,2"; 
		StandardState = 2; 
		Density = 35; 
		MeltingPoint = (int)'N'; 
		BoilingPoint = (int)'N'; 
		HeatCapacity = (int)'N'; 
		HeatOfFusion = (int)'N'; 
		HeatOfVaporization = (int)'N'; 
		AtomicRadius = (int)'N'; 
		CovalentRadius = (int)'N'; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = (int)'N'; 
		OxidationStates = "4,6"; 
		IonizationEnergy = (int)'N'; 
		ThermalConductivity = (int)'N'; 
		ElectronAffinity = (int)'N'; 
		AbundanceCrust = 0; 
		AbundanceUniverse = (int)'N'; 
		Discovery = 1974; 
		Radioactive = 1; 
		DiscoveredBy = "A. Ghiorso et al. (Berkeley Radiation Laboratory)"; 
	}
};
struct Bohrium : OOTElement{
	Bohrium()
	{
		AtomicNumber = 107; 
		Symbol = "Bh"; 
		EnglishName = "Bohrium"; 
		Group = 7; 
		Period = 7; 
		Block = "d"; 
		Category = 3; 
		AtomicMass = 270; 
		Configuration = "[Rn] 5f14 6d5 7s2"; 
		ShellConfiguration = "2,8,18,32,32,13,2"; 
		StandardState = 2; 
		Density = 37.1; 
		MeltingPoint = (int)'N'; 
		BoilingPoint = (int)'N'; 
		HeatCapacity = (int)'N'; 
		HeatOfFusion = (int)'N'; 
		HeatOfVaporization = (int)'N'; 
		AtomicRadius = (int)'N'; 
		CovalentRadius = (int)'N'; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = (int)'N'; 
		OxidationStates = "3,4,5,7"; 
		IonizationEnergy = (int)'N'; 
		ThermalConductivity = (int)'N'; 
		ElectronAffinity = (int)'N'; 
		AbundanceCrust = 0; 
		AbundanceUniverse = (int)'N'; 
		Discovery = 1981; 
		Radioactive = 1; 
		DiscoveredBy = "G.Münzenberg et al. (GSI Darmstadt)"; 
	}
};
struct Hassium : OOTElement{
	Hassium()
	{
		AtomicNumber = 108; 
		Symbol = "Hs"; 
		EnglishName = "Hassium"; 
		Group = 8; 
		Period = 7; 
		Block = "d"; 
		Category = 3; 
		AtomicMass = 277; 
		Configuration = "[Rn] 5f14 6d6 7s2"; 
		ShellConfiguration = "2,8,18,32,32,14,2"; 
		StandardState = 2; 
		Density = 40.7; 
		MeltingPoint = (int)'N'; 
		BoilingPoint = (int)'N'; 
		HeatCapacity = (int)'N'; 
		HeatOfFusion = (int)'N'; 
		HeatOfVaporization = (int)'N'; 
		AtomicRadius = (int)'N'; 
		CovalentRadius = (int)'N'; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = (int)'N'; 
		OxidationStates = "2,4,6,8"; 
		IonizationEnergy = (int)'N'; 
		ThermalConductivity = (int)'N'; 
		ElectronAffinity = (int)'N'; 
		AbundanceCrust = 0; 
		AbundanceUniverse = (int)'N'; 
		Discovery = 1984; 
		Radioactive = 1; 
		DiscoveredBy = "G. Münzenberg, P. Armbruster et al. (GSI Darmstadt)"; 
	}
};
struct Meitnerium : OOTElement{
	Meitnerium()
	{
		AtomicNumber = 109; 
		Symbol = "Mt"; 
		EnglishName = "Meitnerium"; 
		Group = 9; 
		Period = 7; 
		Block = "d"; 
		Category = 3; 
		AtomicMass = 278; 
		Configuration = "[Rn] 5f14 6d7 7s2"; 
		ShellConfiguration = "2,8,18,32,32,15,2"; 
		StandardState = 2; 
		Density = 37.4; 
		MeltingPoint = (int)'N'; 
		BoilingPoint = (int)'N'; 
		HeatCapacity = (int)'N'; 
		HeatOfFusion = (int)'N'; 
		HeatOfVaporization = (int)'N'; 
		AtomicRadius = (int)'N'; 
		CovalentRadius = (int)'N'; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = (int)'N'; 
		OxidationStates = "1,3,6"; 
		IonizationEnergy = (int)'N'; 
		ThermalConductivity = (int)'N'; 
		ElectronAffinity = (int)'N'; 
		AbundanceCrust = 0; 
		AbundanceUniverse = (int)'N'; 
		Discovery = 1982; 
		Radioactive = 1; 
		DiscoveredBy = "G. Münzenberg, P. Armbruster et al. (GSI Darmstadt)"; 
	}
};
struct Darmstadtium : OOTElement{
	Darmstadtium()
	{
		AtomicNumber = 110; 
		Symbol = "Ds"; 
		EnglishName = "Darmstadtium"; 
		Group = 10; 
		Period = 7; 
		Block = "d"; 
		Category = 3; 
		AtomicMass = 281; 
		Configuration = "[Rn] 5f14 6d8 7s2"; 
		ShellConfiguration = "2,8,18,32,32,16,2"; 
		StandardState = 2; 
		Density = 34.8; 
		MeltingPoint = (int)'N'; 
		BoilingPoint = (int)'N'; 
		HeatCapacity = (int)'N'; 
		HeatOfFusion = (int)'N'; 
		HeatOfVaporization = (int)'N'; 
		AtomicRadius = (int)'N'; 
		CovalentRadius = (int)'N'; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = (int)'N'; 
		OxidationStates = "0,2,8"; 
		IonizationEnergy = (int)'N'; 
		ThermalConductivity = (int)'N'; 
		ElectronAffinity = (int)'N'; 
		AbundanceCrust = 0; 
		AbundanceUniverse = (int)'N'; 
		Discovery = 1994; 
		Radioactive = 1; 
		DiscoveredBy = "S. Hofmann et al. (GSI Darmstadt)"; 
	}
};
struct Roentgenium : OOTElement{
	Roentgenium()
	{
		AtomicNumber = 111; 
		Symbol = "Rg"; 
		EnglishName = "Roentgenium"; 
		Group = 11; 
		Period = 7; 
		Block = "d"; 
		Category = 3; 
		AtomicMass = 282; 
		Configuration = "[Rn] 5f14 6d9 7s2"; 
		ShellConfiguration = "2,8,18,32,32,17,2"; 
		StandardState = 2; 
		Density = 28.7; 
		MeltingPoint = (int)'N'; 
		BoilingPoint = (int)'N'; 
		HeatCapacity = (int)'N'; 
		HeatOfFusion = (int)'N'; 
		HeatOfVaporization = (int)'N'; 
		AtomicRadius = (int)'N'; 
		CovalentRadius = (int)'N'; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = (int)'N'; 
		OxidationStates = "3"; 
		IonizationEnergy = (int)'N'; 
		ThermalConductivity = (int)'N'; 
		ElectronAffinity = 151; 
		AbundanceCrust = 0; 
		AbundanceUniverse = (int)'N'; 
		Discovery = 1994; 
		Radioactive = 1; 
		DiscoveredBy = "S. Hofmann et al. (GSI Darmstadt)"; 
	}
};
struct Copernicium : OOTElement{
	Copernicium()
	{
		AtomicNumber = 112; 
		Symbol = "Cn"; 
		EnglishName = "Copernicium"; 
		Group = 12; 
		Period = 7; 
		Block = "d"; 
		Category = 3; 
		AtomicMass = 285; 
		Configuration = "[Rn] 5f14 6d10 7s2"; 
		ShellConfiguration = "2,8,18,32,32,18,2"; 
		StandardState = 1; 
		Density = 23.7; 
		MeltingPoint = (int)'N'; 
		BoilingPoint = 357; 
		HeatCapacity = (int)'N'; 
		HeatOfFusion = (int)'N'; 
		HeatOfVaporization = (int)'N'; 
		AtomicRadius = (int)'N'; 
		CovalentRadius = (int)'N'; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = (int)'N'; 
		OxidationStates = "0,1,2,4"; 
		IonizationEnergy = (int)'N'; 
		ThermalConductivity = (int)'N'; 
		ElectronAffinity = (int)'N'; 
		AbundanceCrust = 0; 
		AbundanceUniverse = (int)'N'; 
		Discovery = 1996; 
		Radioactive = 1; 
		DiscoveredBy = "S. Hofmann et al. (GSI Darmstadt)"; 
	}
};
struct Nihonium : OOTElement{
	Nihonium()
	{
		AtomicNumber = 113; 
		Symbol = "Nh"; 
		EnglishName = "Nihonium"; 
		Group = 13; 
		Period = 7; 
		Block = "p"; 
		Category = 4; 
		AtomicMass = 286; 
		Configuration = "[Rn] 5f14 6d10 7s2 7p1"; 
		ShellConfiguration = "2,8,18,32,32,18,3"; 
		StandardState = 2; 
		Density = 16; 
		MeltingPoint = 700; 
		BoilingPoint = 1400; 
		HeatCapacity = (int)'N'; 
		HeatOfFusion = (int)'N'; 
		HeatOfVaporization = (int)'N'; 
		AtomicRadius = (int)'N'; 
		CovalentRadius = (int)'N'; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = (int)'N'; 
		OxidationStates = "1,3"; 
		IonizationEnergy = (int)'N'; 
		ThermalConductivity = (int)'N'; 
		ElectronAffinity = 66.6; 
		AbundanceCrust = 0; 
		AbundanceUniverse = (int)'N'; 
		Discovery = 2004; 
		Radioactive = 1; 
		DiscoveredBy = "Y. Oganessian et al. (JINR Dubna), K. Morita et al. (RIKEN Wako, Japan)"; 
	}
};
struct Flerovium : OOTElement{
	Flerovium()
	{
		AtomicNumber = 114; 
		Symbol = "Fl"; 
		EnglishName = "Flerovium"; 
		Group = 14; 
		Period = 7; 
		Block = "p"; 
		Category = 4; 
		AtomicMass = 289; 
		Configuration = "[Rn] 5f14 6d10 7s2 7p2"; 
		ShellConfiguration = "2,8,18,32,32,18,4"; 
		StandardState = 2; 
		Density = 14; 
		MeltingPoint = (int)'N'; 
		BoilingPoint = 210; 
		HeatCapacity = (int)'N'; 
		HeatOfFusion = (int)'N'; 
		HeatOfVaporization = (int)'N'; 
		AtomicRadius = (int)'N'; 
		CovalentRadius = (int)'N'; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = (int)'N'; 
		OxidationStates = "2"; 
		IonizationEnergy = (int)'N'; 
		ThermalConductivity = (int)'N'; 
		ElectronAffinity = (int)'N'; 
		AbundanceCrust = 0; 
		AbundanceUniverse = (int)'N'; 
		Discovery = 1999; 
		Radioactive = 1; 
		DiscoveredBy = "Y. Oganessian et al. (JINR Dubna)"; 
	}
};
struct Moscovium : OOTElement{
	Moscovium()
	{
		AtomicNumber = 115; 
		Symbol = "Mc"; 
		EnglishName = "Moscovium"; 
		Group = 15; 
		Period = 7; 
		Block = "p"; 
		Category = 4; 
		AtomicMass = 290; 
		Configuration = "[Rn] 5f14 6d10 7s2 7p3"; 
		ShellConfiguration = "2,8,18,32,32,18,5"; 
		StandardState = 2; 
		Density = 13.5; 
		MeltingPoint = 700; 
		BoilingPoint = 1400; 
		HeatCapacity = (int)'N'; 
		HeatOfFusion = (int)'N'; 
		HeatOfVaporization = (int)'N'; 
		AtomicRadius = (int)'N'; 
		CovalentRadius = (int)'N'; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = (int)'N'; 
		OxidationStates = "1,3"; 
		IonizationEnergy = (int)'N'; 
		ThermalConductivity = (int)'N'; 
		ElectronAffinity = 35.3; 
		AbundanceCrust = 0; 
		AbundanceUniverse = (int)'N'; 
		Discovery = 2003; 
		Radioactive = 1; 
		DiscoveredBy = "Y. Oganessian et al. (JINR Dubna)"; 
	}
};
struct Livermorium : OOTElement{
	Livermorium()
	{
		AtomicNumber = 116; 
		Symbol = "Lv"; 
		EnglishName = "Livermorium"; 
		Group = 16; 
		Period = 7; 
		Block = "p"; 
		Category = 4; 
		AtomicMass = 293; 
		Configuration = "[Rn] 5f14 6d10 7s2 7p4"; 
		ShellConfiguration = "2,8,18,32,32,18,6"; 
		StandardState = 2; 
		Density = 12.9; 
		MeltingPoint = 709; 
		BoilingPoint = 1085; 
		HeatCapacity = (int)'N'; 
		HeatOfFusion = (int)'N'; 
		HeatOfVaporization = (int)'N'; 
		AtomicRadius = (int)'N'; 
		CovalentRadius = (int)'N'; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = (int)'N'; 
		OxidationStates = "2"; 
		IonizationEnergy = (int)'N'; 
		ThermalConductivity = (int)'N'; 
		ElectronAffinity = 74.9; 
		AbundanceCrust = 0; 
		AbundanceUniverse = (int)'N'; 
		Discovery = 2000; 
		Radioactive = 1; 
		DiscoveredBy = "Y. Oganessian et al. (JINR Dubna)"; 
	}
};
struct Tennessine : OOTElement{
	Tennessine()
	{
		AtomicNumber = 117; 
		Symbol = "Ts"; 
		EnglishName = "Tennessine"; 
		Group = 17; 
		Period = 7; 
		Block = "p"; 
		Category = 4; 
		AtomicMass = 294; 
		Configuration = "[Rn] 5f14 6d10 7s2 7p5"; 
		ShellConfiguration = "2,8,18,32,32,18,7"; 
		StandardState = 2; 
		Density = 7.2; 
		MeltingPoint = 723; 
		BoilingPoint = 883; 
		HeatCapacity = (int)'N'; 
		HeatOfFusion = (int)'N'; 
		HeatOfVaporization = (int)'N'; 
		AtomicRadius = (int)'N'; 
		CovalentRadius = (int)'N'; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = (int)'N'; 
		OxidationStates = "1,3"; 
		IonizationEnergy = (int)'N'; 
		ThermalConductivity = (int)'N'; 
		ElectronAffinity = 165.9; 
		AbundanceCrust = 0; 
		AbundanceUniverse = (int)'N'; 
		Discovery = 2009; 
		Radioactive = 1; 
		DiscoveredBy = "Y. Oganessian et al. (JINR Dubna)"; 
	}
};
struct Oganesson : OOTElement{
	Oganesson()
	{
		AtomicNumber = 118; 
		Symbol = "Og"; 
		EnglishName = "Oganesson"; 
		Group = 18; 
		Period = 7; 
		Block = "p"; 
		Category = 7; 
		AtomicMass = 294; 
		Configuration = "[Rn] 5f14 6d10 7s2 7p6"; 
		ShellConfiguration = "2,8,18,32,32,18,8"; 
		StandardState = 0; 
		Density = 5; 
		MeltingPoint = (int)'N'; 
		BoilingPoint = 350; 
		HeatCapacity = (int)'N'; 
		HeatOfFusion = (int)'N'; 
		HeatOfVaporization = (int)'N'; 
		AtomicRadius = (int)'N'; 
		CovalentRadius = (int)'N'; 
		VanDerWaalsRadius = (int)'N'; 
		Electronegativity = (int)'N'; 
		OxidationStates = "2,4"; 
		IonizationEnergy = (int)'N'; 
		ThermalConductivity = (int)'N'; 
		ElectronAffinity = 5.403; 
		AbundanceCrust = 0; 
		AbundanceUniverse = (int)'N'; 
		Discovery = 2002; 
		Radioactive = 1; 
		DiscoveredBy = "Y. Oganessian et al. (JINR Dubna)"; 
	}
};
#endif
