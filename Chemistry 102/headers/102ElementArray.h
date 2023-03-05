#ifndef OOTES_ARRAY_H
#define OOTES_ARRAY_H
#include "102Elements.h"
struct OOTElementsStorage{
private: 
Hydrogen hydrogen;
Helium helium;
Lithium lithium;
Beryllium beryllium;
Boron boron;
Carbon carbon;
Nitrogen nitrogen;
Oxygen oxygen;
Fluorine fluorine;
Neon neon;
Sodium sodium;
Magnesium magnesium;
Aluminium aluminium;
Silicon silicon;
Phosphorus phosphorus;
Sulfur sulfur;
Chlorine chlorine;
Argon argon;
Potassium potassium;
Calcium calcium;
Scandium scandium;
Titanium titanium;
Vanadium vanadium;
Chromium chromium;
Manganese manganese;
Iron iron;
Cobalt cobalt;
Nickel nickel;
Copper copper;
Zinc zinc;
Gallium gallium;
Germanium germanium;
Arsenic arsenic;
Selenium selenium;
Bromine bromine;
Krypton krypton;
Rubidium rubidium;
Strontium strontium;
Yttrium yttrium;
Zirconium zirconium;
Niobium niobium;
Molybdenum molybdenum;
Technetium technetium;
Ruthenium ruthenium;
Rhodium rhodium;
Palladium palladium;
Silver silver;
Cadmium cadmium;
Indium indium;
Tin tin;
Antimony antimony;
Tellurium tellurium;
Iodine iodine;
Xenon xenon;
Caesium caesium;
Barium barium;
Lanthanum lanthanum;
Cerium cerium;
Praseodymium praseodymium;
Neodymium neodymium;
Promethium promethium;
Samarium samarium;
Europium europium;
Gadolinium gadolinium;
Terbium terbium;
Dysprosium dysprosium;
Holmium holmium;
Erbium erbium;
Thulium thulium;
Ytterbium ytterbium;
Lutetium lutetium;
Hafnium hafnium;
Tantalum tantalum;
Tungsten tungsten;
Rhenium rhenium;
Osmium osmium;
Iridium iridium;
Platinum platinum;
Gold gold;
Mercury mercury;
Thallium thallium;
Lead lead;
Bismuth bismuth;
Polonium polonium;
Astatine astatine;
Radon radon;
Francium francium;
Radium radium;
Actinium actinium;
Thorium thorium;
Protactinium protactinium;
Uranium uranium;
Neptunium neptunium;
Plutonium plutonium;
Americium americium;
Curium curium;
Berkelium berkelium;
Californium californium;
Einsteinium einsteinium;
Fermium fermium;
Mendelevium mendelevium;
Nobelium nobelium;
Lawrencium lawrencium;
Rutherfordium rutherfordium;
Dubnium dubnium;
Seaborgium seaborgium;
Bohrium bohrium;
Hassium hassium;
Meitnerium meitnerium;
Darmstadtium darmstadtium;
Roentgenium roentgenium;
Copernicium copernicium;
Nihonium nihonium;
Flerovium flerovium;
Moscovium moscovium;
Livermorium livermorium;
Tennessine tennessine;
Oganesson oganesson;
public:
OOTElement OOTElementArray[118] = 
{hydrogen,helium,lithium,beryllium,boron,carbon,nitrogen,oxygen,fluorine,neon,
sodium,magnesium,aluminium,silicon,phosphorus,sulfur,chlorine,argon,potassium,calcium,
scandium,titanium,vanadium,chromium,manganese,iron,cobalt,nickel,copper,zinc,
gallium,germanium,arsenic,selenium,bromine,krypton,rubidium,strontium,yttrium,zirconium,
niobium,molybdenum,technetium,ruthenium,rhodium,palladium,silver,cadmium,indium,tin,
antimony,tellurium,iodine,xenon,caesium,barium,lanthanum,cerium,praseodymium,neodymium,
promethium,samarium,europium,gadolinium,terbium,dysprosium,holmium,erbium,thulium,ytterbium,
lutetium,hafnium,tantalum,tungsten,rhenium,osmium,iridium,platinum,gold,mercury,
thallium,lead,bismuth,polonium,astatine,radon,francium,radium,actinium,thorium,
protactinium,uranium,neptunium,plutonium,americium,curium,berkelium,californium,einsteinium,fermium,
mendelevium,nobelium,lawrencium,rutherfordium,dubnium,seaborgium,bohrium,hassium,meitnerium,darmstadtium,
roentgenium,copernicium,nihonium,flerovium,moscovium,livermorium,tennessine,oganesson};
enum class OOTElementIndexes {
Hydrogen = 0,Helium = 1,Lithium = 2,Beryllium = 3,Boron = 4,Carbon = 5,Nitrogen = 6,Oxygen = 7,Fluorine = 8,Neon = 9,
Sodium = 10,Magnesium = 11,Aluminium = 12,Silicon = 13,Phosphorus = 14,Sulfur = 15,Chlorine = 16,Argon = 17,Potassium = 18,Calcium = 19,
Scandium = 20,Titanium = 21,Vanadium = 22,Chromium = 23,Manganese = 24,Iron = 25,Cobalt = 26,Nickel = 27,Copper = 28,Zinc = 29,
Gallium = 30,Germanium = 31,Arsenic = 32,Selenium = 33,Bromine = 34,Krypton = 35,Rubidium = 36,Strontium = 37,Yttrium = 38,Zirconium = 39,
Niobium = 40,Molybdenum = 41,Technetium = 42,Ruthenium = 43,Rhodium = 44,Palladium = 45,Silver = 46,Cadmium = 47,Indium = 48,Tin = 49,
Antimony = 50,Tellurium = 51,Iodine = 52,Xenon = 53,Caesium = 54,Barium = 55,Lanthanum = 56,Cerium = 57,Praseodymium = 58,Neodymium = 59,
Promethium = 60,Samarium = 61,Europium = 62,Gadolinium = 63,Terbium = 64,Dysprosium = 65,Holmium = 66,Erbium = 67,Thulium = 68,Ytterbium = 69,
Lutetium = 70,Hafnium = 71,Tantalum = 72,Tungsten = 73,Rhenium = 74,Osmium = 75,Iridium = 76,Platinum = 77,Gold = 78,Mercury = 79,
Thallium = 80,Lead = 81,Bismuth = 82,Polonium = 83,Astatine = 84,Radon = 85,Francium = 86,Radium = 87,Actinium = 88,Thorium = 89,
Protactinium = 90,Uranium = 91,Neptunium = 92,Plutonium = 93,Americium = 94,Curium = 95,Berkelium = 96,Californium = 97,Einsteinium = 98,Fermium = 99,
Mendelevium = 100,Nobelium = 101,Lawrencium = 102,Rutherfordium = 103,Dubnium = 104,Seaborgium = 105,Bohrium = 106,Hassium = 107,Meitnerium = 108,Darmstadtium = 109,
Roentgenium = 110,Copernicium = 111,Nihonium = 112,Flerovium = 113,Moscovium = 114,Livermorium = 115,Tennessine = 116,Oganesson = 117};
OOTElement NobleGases[7] = {
helium,
neon,
argon,
krypton,
xenon,
radon,
oganesson,
};
enum class OOTNobelGasIndexes {
Helium = 0,Neon = 1,Argon = 2,Krypton = 3,
Xenon = 4,Radon = 5,Oganesson = 6};
} ElementStorage;


#endif
