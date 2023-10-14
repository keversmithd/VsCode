#ifndef CSV_OPEN_H
#define CSV_OPEN_H 

#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>

#include "CSVCellSorting.h"



struct CSVDecompile
{
public:
    const char* SourceFile;
    char Delimiter;
    std::vector<std::string> Categories;
    std::vector<std::vector<CSVCell>> Entries;
    CSVCellSorting Sorter;
    
public:
    
    CSVDecompile(const char* source, CSVCellSorting SortCells) : SourceFile(source), Delimiter('\0'), Sorter(SortCells)
    {
        ReadAll();
    }
    CSVDecompile(const char* source) : SourceFile(source), Delimiter('\0'), Sorter()
    {
        ReadAll();
    }

    void IdentifyDelimiter(std::string RawData)
    {
        std::unordered_map<char,int> CommonChars;
        char MostCommonChar = 'x';
        int MostCommonAmount = 0;
        for(int i = 0; i < RawData.size(); i++)
        {
            if(RawData[i] >= 33 && RawData[i] <=47)
            {
                if(CommonChars.find(RawData[i]) == CommonChars.end())
                {
                    CommonChars.insert({RawData[i],1});
                }else
                {
                    CommonChars[RawData[i]]++;
                }

                if(CommonChars[RawData[i]] > MostCommonAmount)
                {
                    MostCommonChar = RawData[i];
                    MostCommonAmount = CommonChars[RawData[i]];
                }
            }
            

            
        }

        Delimiter = MostCommonChar;
        

    }

    void ReadAll()
    {
        std::vector<std::string> Lines;

        std::ifstream file(SourceFile);
        if (!file.is_open()) {
            printf("Error opening the file");
            return; // Exit with an error code  
        }

        std::string line;
        while (std::getline(file, line)) {
            Lines.push_back(line);
        }

        file.close();
        
        IdentifyDelimiter(Lines[0]);
        Categories = Split(Lines[0], Delimiter);
        GenerateCells(Lines);
    }

    void CSVSplit(std::string String)
    {
        std::string CurrentString;
        int CategoryNumber = 0;
        std::vector<CSVCell> Subvector;
        CSVCell ExampleCell;
        
        // int InnerCount = 0;
        for(int i = 0; i < String.size(); i++)
        {
            if(String[i] == Delimiter)
            {
                if(CategoryNumber < Categories.size()-1)
                {
                    ExampleCell.Value = CurrentString;
                    ExampleCell.Category = Categories[CategoryNumber];
                    CSVCellSortation CellStatus = Sorter.DetermineType(CurrentString);
                    // ExampleCell.Hash = CellStatus.Hash;
                    // ExampleCell.Type = CellStatus.Type;
                    Subvector.push_back(ExampleCell);
                    
                    
                    CurrentString = "";
                    CategoryNumber++;
                }else
                {
                    
                }
                
            }else
            {
                CurrentString += String[i];
            }
        }

        Entries.push_back(Subvector);
        
    }

    void GenerateCells(const std::vector<std::string>& Lines)
    {
        for(int i = 1; i < Lines.size(); i++)
        {
            CSVSplit(Lines[i]);
            
        }

    }

    

    ~CSVDecompile()
    {

    }
};

#endif