#ifndef PERIOD_EXTRACT_H
#define PERIOD_EXTRACT_H

#include <iostream>
#include <stdio.h>

#define WS "X:\\1.4 C++\\Vscode\\Chemistry 102"
#define DS WS "\\dataset"
#include <stdio.h>
#include <vector>
#include <string.h>
#include "102Elements.h"

enum AbsorbType
{
    DOUBLE = 0,
    INT = 1,
    CHAR = 2,
    STRING = 3,
    NO_TYPE = 4
};

bool DoesNotContain(std::string buffer, char delim)
{
    bool Contained = false;
    for(int i = 0; i < buffer.size(); i++)
    {
        if(buffer.at(i) == delim)
        {
            Contained = true;
        }
    }
    return Contained;
}

bool ContainsAlpha(std::string buffer)
{
    bool Contained = false;
    for(int i = 0; i < buffer.size(); i++)
    {
        if(isalpha(buffer.at(i)))
        {
            Contained = true;
        }
        if(buffer.at(i) == ',')
        {
            Contained = true;
        }

    }
    return Contained;


}
bool isExponent(std::string buffer)
{
    int IEContains = 0;
    int AlphaCount = 0;

    for(int i = 0; i < buffer.size(); i++)
    {
        if(buffer.at(i) == 'E')
        {
            if(buffer.at(i+1) == '-')
            {
                IEContains++;
                i++;
            }
        }else
        {
            if(isalpha(buffer.at(i)))
            {
                AlphaCount++;
            }
        }
    }
    
    return (IEContains == 1 && AlphaCount == 0);

}
AbsorbType GetType(std::string Type)
{
    if(Type.length() == 1 && isalpha(Type.at(0)))
    {
        return CHAR;
    }
    if(Type.length() == 1 && isdigit(Type.at(0)))
    {
        return INT;
    }
    if(isExponent(Type))
    {
        return DOUBLE;
    } 
    bool Dub = DoesNotContain(Type, '.');
    bool Alpha = ContainsAlpha(Type);
    if(Dub && Alpha)
    {
        return STRING;
    }
    if(Dub)
    {
        return DOUBLE;
    }
    if(Alpha)
    {
        return STRING;
    }else
    {
        return INT;
    }
}

double GetDouble(std::string Type)
{
    const char* out = Type.c_str();
    return atof(out);
}

int GetInt(std::string Type)
{
    return atoi(Type.c_str());
}

void lowerString(const char* upper, char* buffer)
{
    int bufferLength = strlen(upper);
    buffer[bufferLength] = '\0';
    for(int i = 0; i < bufferLength; i++)
    {
        buffer[i] = tolower(upper[i]);
    }

}

int E_EXTRACTION()
{
    FILE* elemCSV = NULL;
errno_t elem = fopen_s(&elemCSV, DS "\\ElementData.csv", "rb");
if(elem != 0 || elemCSV == NULL)
{
    return 0;
}
const int FeatureCount = 30;
std::vector<const char*> Features;
for(int i = 0; i < FeatureCount; i++)
{
    std::string Feature;
    int c = 0;
    while (c != ',' && c != '\n')
    {
        c = fgetc(elemCSV);
        if(c != ',' && c != '\n')
        {
            Feature.push_back(c);
        }
     
    }
    char* nChar = (char*)malloc(Feature.size()+1);
    strcpy(nChar, Feature.c_str());
    nChar[Feature.size()] = '\0';
    Features.push_back(nChar);
}
std::vector<const char*> NamesArray;
struct NEQCustom{ const char* name; int period; int group; };
std::vector<NEQCustom> CUSTOMARRAY;
for(int i = 0; i < 118; i++)
{
    NEQCustom Dragger;
    for(int k = 0; k < FeatureCount; k++)
    {
     
        std::string Buffer;
        int c = 0;
        while (c != ',' && c != '\n')
        {
         
            c = fgetc(elemCSV);
            if(c == '\"')
            {
                c = fgetc(elemCSV);
                Buffer.push_back(c);
                while(c != '\"')
                {
                    c = fgetc(elemCSV);
                    if(c != '\"')
                    {
                        Buffer.push_back(c);
                    }
                }
                c = fgetc(elemCSV);
            }
            if(c != ',' && c != '\n')
            {
                Buffer.push_back(c);
            }
        }
        char* xChar = (char*)malloc(Buffer.size()+1);
        strcpy(xChar, Buffer.c_str());
        xChar[Buffer.size()] = '\0';
     
        if(k == 2)
        {
            NamesArray.push_back(xChar); 
            Dragger.name = xChar;
        }
        if(k == 4)
        {
            Dragger.period = atoi(xChar);
        }
        if(k == 3)
        {
            Dragger.group = atoi(xChar);
        }
    }
    CUSTOMARRAY.push_back(Dragger);
}

    FILE* ElectronConfiguration = nullptr;

    errno_t OOTSERR = fopen_s(&ElectronConfiguration, WS "\\102ElectronConfiguration.h", "w");
    if(ElectronConfiguration == NULL || OOTSERR != 0)
    {
        return 0;
    }

}

int P_EXTRACTION()
{
    
    // FILE* elemCSV = NULL;
    // errno_t elem = fopen_s(&elemCSV, DS "\\ElementData.csv", "rb");
    // if(elem != 0 || elemCSV == NULL)
    // {
    //     return 0;
    // }
    // const int FeatureCount = 30;
    // std::vector<const char*> Features;
    // for(int i = 0; i < FeatureCount; i++)
    // {
    //     std::string Feature;

    //     int c = 0;
    //     while (c != ',' && c != '\n')
    //     {
    //         c = fgetc(elemCSV);
    //         if(c != ',' && c != '\n')
    //         {
    //             Feature.push_back(c);
    //         }
            
    //     }
    //     char* nChar = (char*)malloc(Feature.size()+1);
    //     strcpy(nChar, Feature.c_str());
    //     nChar[Feature.size()] = '\0';
    //     Features.push_back(nChar);
    // }
    // std::vector<const char*> NamesArray;
    // struct NEQCustom{ const char* name; int period; int group; };
    // std::vector<NEQCustom> CUSTOMARRAY;
    // for(int i = 0; i < 118; i++)
    // {
    //     NEQCustom Dragger;
    //     for(int k = 0; k < FeatureCount; k++)
    //     {
            
    //         std::string Buffer;
    //         int c = 0;
    //         while (c != ',' && c != '\n')
    //         {
                
    //             c = fgetc(elemCSV);
    //             if(c == '\"')
    //             {
    //                 c = fgetc(elemCSV);
    //                 Buffer.push_back(c);
    //                 while(c != '\"')
    //                 {
    //                     c = fgetc(elemCSV);
    //                     if(c != '\"')
    //                     {
    //                         Buffer.push_back(c);
    //                     }
    //                 }
    //                 c = fgetc(elemCSV);
    //             }
    //             if(c != ',' && c != '\n')
    //             {
    //                 Buffer.push_back(c);
    //             }
    //         }
    //         char* xChar = (char*)malloc(Buffer.size()+1);
    //         strcpy(xChar, Buffer.c_str());
    //         xChar[Buffer.size()] = '\0';
            
    //         if(k == 2)
    //         {
    //             NamesArray.push_back(xChar); 
    //             Dragger.name = xChar;
    //         }
    //         if(k == 4)
    //         {
    //             Dragger.period = atoi(xChar);
    //         }
    //         if(k == 3)
    //         {
    //             Dragger.group = atoi(xChar);
    //         }
    //     }
    //     CUSTOMARRAY.push_back(Dragger);
    // }
    
    

    // FILE* OOTElementsArrayFile = NULL;
    // errno_t OOTSERR = fopen_s(&OOTElementsArrayFile, WS "\\102ElementArray.h", "w");
    // if(OOTElementsArrayFile == NULL || OOTSERR != 0)
    // {
    //     return 0;
    // }
    // fprintf(OOTElementsArrayFile, "%s\n%s\n", "#ifndef OOTES_ARRAY_H", "#define OOTES_ARRAY_H");
    // fprintf(OOTElementsArrayFile, "%s\n", "#include \"102Elements.h\"");
    // fprintf(OOTElementsArrayFile, "%s\n", "struct OOTElementsStorage{");
    // fprintf(OOTElementsArrayFile, "%s\n", "private: ");
    // for(int i = 0; i < NamesArray.size(); i++)
    // {
    //     char buffer[24];
    //     lowerString(NamesArray.at(i), buffer);
    //     fprintf(OOTElementsArrayFile, "%s %s;\n", NamesArray.at(i), buffer);
    // }
    // fprintf(OOTElementsArrayFile, "%s", "OOTElement OOTElementArray[118] = \n{");
    // for(int i = 0; i < NamesArray.size(); i++)
    // {
    //     char buffer[24];
    //     lowerString(NamesArray.at(i), buffer);
    //     fprintf(OOTElementsArrayFile, "%s", buffer);
    //     if(i != NamesArray.size()-1)
    //     {
    //         fprintf(OOTElementsArrayFile, "%c", ',');
    //     }
    //     if((i+1) % 10 == 0)
    //     {
    //         fprintf(OOTElementsArrayFile, "%c", '\n');
    //     }
    // }
    


    // fprintf(OOTElementsArrayFile, "%s\n", "};");

    // fprintf(OOTElementsArrayFile, "%s\n", "enum class OOTElementIndexes {");
    // for(int i = 0; i < NamesArray.size(); i++)
    // {
    //     fprintf(OOTElementsArrayFile, "%s%s%d", NamesArray.at(i), " = ", i);
    //     if(i != NamesArray.size()-1)
    //     {
    //         fprintf(OOTElementsArrayFile, "%c", ',');
    //     }
    //     if((i+1) % 10 == 0)
    //     {
    //         fprintf(OOTElementsArrayFile, "%c", '\n');
    //     }
    // }
    // fprintf(OOTElementsArrayFile, "%s\n", "};");
    
    // struct NobelGasIindex{ const char* name; int index; };
    // std::vector<NobelGasIindex> NobelGasIndexes;
    // fprintf(OOTElementsArrayFile, "%s\n", "OOTElement NobleGases[7] = {");
    // for(int i = 0, j = 0; i < CUSTOMARRAY.size(); i++)
    // {
    //     NEQCustom Iterative = CUSTOMARRAY.at(i);
    //     if(Iterative.name == "Neon")
    //     {
    //         std::cout << "neon" << std::endl;
    //     }
    //     if(Iterative.period <= 7)
    //     {
    //         if(Iterative.group ==  18)
    //         {
    //             char buffer[24];
    //             lowerString(Iterative.name, buffer);
    //             fprintf(OOTElementsArrayFile, "%s,\n", buffer);
    //             NobelGasIindex nobIndex;
    //             nobIndex.name = Iterative.name;
    //             nobIndex.index = j;
    //             NobelGasIndexes.push_back(nobIndex);
    //             j++;
    //         }
    //     }
    // }
    // fprintf(OOTElementsArrayFile, "%s\n", "};");

    // fprintf(OOTElementsArrayFile, "%s\n", "enum class OOTNobelGasIndexes {");

    // for(int i = 0; i < NobelGasIndexes.size(); i++)
    // {
    //     fprintf(OOTElementsArrayFile, "%s = %d", NobelGasIndexes.at(i).name, NobelGasIndexes.at(i).index);

    //     if(i != NobelGasIndexes.size()-1)
    //     {
    //         fprintf(OOTElementsArrayFile, "%c", ',');
    //     }
    //     if((i+1)%4 == 0)
    //     {
    //         fprintf(OOTElementsArrayFile, "%c", '\n');
    //     }
    // }
    // fprintf(OOTElementsArrayFile, "%s\n", "};");

    // fprintf(OOTElementsArrayFile, "%s\n", "};");

    // fprintf(OOTElementsArrayFile, "%s\n", "#endif");
    // fclose(OOTElementsArrayFile);

    // FILE* OOTElementsFile = NULL;
    // errno_t OOTESERR = fopen_s(&OOTElementsFile, WS "\\102Elements.h", "w");
    // if(OOTElementsFile == NULL || OOTESERR != 0)
    // {
    //     return 0;
    // }
    // fprintf(OOTElementsFile, "%s\n%s\n", "#ifndef OOTES_H", "#define OOTES_H");
    // fprintf(OOTElementsFile, "#include \"102Element.h\";\n");

    // std::vector<const char*> Temp;
    // const char* TypeList[] = {"double", "int", "char", "string"};
    // const char* Oxi = "OxidationStates\0";
    // for(int i = 0; i < 118; i++)
    // {
        
    //     for(int k = 0; k < FeatureCount; k++)
    //     {
    //         std::string Buffer;
    //         int c = 0;
    //         while (c != ',' && c != '\n')
    //         {
                
    //             c = fgetc(elemCSV);
    //             if(c == '\"')
    //             {
    //                 c = fgetc(elemCSV);
    //                 Buffer.push_back(c);
    //                 while(c != '\"')
    //                 {
    //                     c = fgetc(elemCSV);
    //                     if(c != '\"')
    //                     {
    //                         Buffer.push_back(c);
    //                     }
    //                 }
    //                 c = fgetc(elemCSV);
    //             }
    //             if(c != ',' && c != '\n')
    //             {
    //                 Buffer.push_back(c);
    //             }
    //         }
    //         char* xChar = (char*)malloc(Buffer.size()+1);
    //         strcpy(xChar, Buffer.c_str());
    //         xChar[Buffer.size()] = '\0';
            
    //         Temp.push_back(xChar);
    //     }

    //     fprintf(OOTElementsFile, "struct %s : OOTElement{\n", Temp.at(2));
    //     fprintf(OOTElementsFile, "\t%s()\n\t{\n\t\t", Temp.at(2));
        
    //     for(int j = 0; j < FeatureCount; j++)
    //     {
    //         if(j == FeatureCount-1)
    //         {
    //             AbsorbType AType = GetType(Temp.at(j));
    //             if(Temp.at(j)[0] == '\0')
    //             {
    //                 fprintf(OOTElementsFile, "%s = (%s)\"%s\"; \n\t",  Features[j], "const char*", "NULL");
    //             }else
    //             {
    //                 if(AType == CHAR)
    //                 {
    //                     fprintf(OOTElementsFile, "%s = \"%s\"; \n\t",  Features[j], Temp.at(j));
    //                 }else if(AType == STRING)
    //                 {
    //                     fprintf(OOTElementsFile, "%s = \"%s\"; \n\t",  Features[j], Temp.at(j));
    //                 }else{ fprintf(OOTElementsFile, "%s = %s; \n\t",  Features[j], Temp.at(j));  }
    //             }

    //         }else
    //         {
    //             AbsorbType AType = GetType(Temp.at(j));
    //             if(Temp.at(j)[0] == '\0')
    //             {
    //                 fprintf(OOTElementsFile, "%s = (%s)\'%s\'; \n\t\t",  Features[j], TypeList[AType], "N");
    //             }
    //             else
    //             {
                    
    //                 if(j ==  21)
    //                 {
    //                     fprintf(OOTElementsFile, "%s = \"%s\"; \n\t\t",  Features[j], Temp.at(j));
    //                 }else
    //                 {
    //                     if(AType == CHAR)
    //                     {
    //                         fprintf(OOTElementsFile, "%s = \"%s\"; \n\t\t",  Features[j], Temp.at(j));
    //                     }else if(AType == STRING)
    //                     {
    //                         fprintf(OOTElementsFile, "%s = \"%s\"; \n\t\t",  Features[j], Temp.at(j));
    //                     }
    //                     else
    //                     {
    //                         fprintf(OOTElementsFile, "%s = %s; \n\t\t",  Features[j], Temp.at(j));
    //                     }
    //                 }
    //             }
                
    //         }
    //     }
    //     fprintf(OOTElementsFile, "}\n");

    //     fprintf(OOTElementsFile, "};\n");

    //     Temp.clear();
    // }


    // fprintf(OOTElementsFile, "%s\n", "#endif");


    // fclose(OOTElementsFile);
    // fclose(elemCSV);
    // const int shellCount = 7;

    // const char* types[30] = {
    //     "int","const char*", "const char*", "int", "int", "char", "int", "double", "const char*", "const char*", "int", "double", "double", "double", "double", "double", "double", "double", "double", "double", "double", "double", "double", "double", "double", "double", "double", "double", "bool", "const char*"
    // };

    // FILE* elementaryPeriodic = NULL;
    // const char* elementary = WS "\\102Element.h";
    // errno_t elemOp = fopen_s(&elementaryPeriodic, elementary, "w");
    // if(elementaryPeriodic == NULL || elemOp != 0)
    // {
    //     return 0;
    // }
    // fprintf(elementaryPeriodic, "%s\n%s\n", "#ifndef OOTE_H", "#define OOTE_H");
    // fprintf(elementaryPeriodic, "struct OOTElement{\n");

    // for(int i = 0; i < FeatureCount; i++)
    // {
    //     fprintf(elementaryPeriodic, "\t%s %s;\n", types[i], Features.at(i));
    // }
    // fprintf(elementaryPeriodic, "};\n");
    // fprintf(elementaryPeriodic, "%s\n", "#endif");
    // std::cout << DS << std::endl;
    // fclose(elementaryPeriodic);




    return 1;
}

#endif