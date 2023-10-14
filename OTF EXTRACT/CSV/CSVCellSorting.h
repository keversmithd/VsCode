#ifndef CSV_CELL_SORTING_H
#define CSV_CELL_SORTING_H 

#include "CSVCell.h"
#include <vector>


int StringHashFunction(const std::string string)
{
    int hash = 0;
    for(int i = 0; i < string.size(); i++)
    {
        hash += string[i];
    }
    return hash;
}

std::vector<std::string> Split(const std::string String, char Delimiter)
{   
    std::vector<std::string> Categories;
    std::string CurrentString ="";
    for(int i = 0; i < String.size(); i++)
    {
        if(String[i] == Delimiter)
        {   
            Categories.push_back(CurrentString);
            CurrentString = "";
            
        }else
        {
            CurrentString += String[i];
        }   
    }

    if(CurrentString != "") Categories.push_back(CurrentString);
    

    return Categories;
}

int DateHash1(const std::string pv)
{
    int Hash = 0;
    std::vector<std::string> DateUnits = Split(pv,'/');
    for(int i = 0; i < DateUnits.size(); i++)
    {
        for(int j = 0; j < DateUnits[i].size(); j++)
        {
            Hash += DateUnits[i][j];
        }
    }

}

bool IsDate(std::string pv, int(*&Hash)(const std::string pv)) //Possible Value
{
    // int NumberOfPatterns = 1;
    // int(*HashFunctions[])(const std::string pv) ={
    //     DateHash1
    // };

    // std::regex patterns[]={
    //     std::regex("([0-9])")
    // };   
    
    // for(int i = 0; i < NumberOfPatterns; i++)
    // {
    //     if (std::regex_search(pv, patterns[i])) {
    //         Hash = HashFunctions[i];
    //         return true;
    //     }
    // }
    
    return false;
}

bool IsTime(std::string pv,int(*&Hash)(const std::string pv))
{
    // int NumberOfPatterns = 1;
    // std::regex patterns[]={
    //     std::regex("([0-9])"),
    // };   
    
    // for(int i = 0; i < NumberOfPatterns; i++)
    // {
    //     if (std::regex_search(pv, patterns[i])) {
    //     return true;
    //     }
    // }

    return false;
}

struct CSVCellSortation
{
    int(*Hash)(const std::string pv);
    int Type;
};

struct CSVCellSorting
{
    int(*DefaultHashFunction)(const std::string pv);
    std::vector<bool(*)(const std::string pv,int(*&Hash)(const std::string pv))> Sortations;
    CSVCellSorting() : DefaultHashFunction(StringHashFunction)
    {
        Sortations.push_back(IsDate);
        Sortations.push_back(IsTime);
    }

    CSVCellSorting(const CSVCellSorting& Copy) : DefaultHashFunction(Copy.DefaultHashFunction), Sortations(Copy.Sortations)
    {

    }
    
    CSVCellSortation DetermineType(const std::string value)
    {
        int(*HashFunction)(const std::string pv);
        for(int i = 0; i < Sortations.size(); i++)
        {
            if(Sortations[i](value,HashFunction) == true)
            {
                return {HashFunction,i};
            }
        }

        return {DefaultHashFunction,-1};
    }
};


#endif