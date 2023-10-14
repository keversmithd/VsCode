#ifndef CSV_CELL_H
#define CSV_CELL_H 

#include <string>



struct CSVCell
{
    std::string Value;
    std::string Category;
    int Type;
    int(*Hash)(const std::string currentCell);

    CSVCell() : Value(""),Category(""),Type(0),Hash(nullptr)
    {

    }
    // CSVCell(const CSVCell& Copy) : Value(Copy.Value), Category(Copy.Category), Type(Copy.Type),Hash(Copy.Hash)
    // {

    // }
    int hash()
    {
        return Hash(Value);
    }
    ~CSVCell()
    {
        
    }
};


#endif