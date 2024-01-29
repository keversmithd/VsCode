#ifndef DIFFERENTIAL_SYMBOLS
#define DIFFERENTIAL_SYMBOLS

#include <unordered_map>
#include <string>
#include "StringSplit.h"

enum IntegralNodeTypeEnum
{
    INT_EMPTY,
    INT_NUMERIC_CONSTANT,
    INT_VARIABLE,
    INT_FUNCTION,
    INT_OPERATOR
};

struct IntegralTokenType
{
    std::string TokenString;
    //Encoding : -1 Empty : 0 Numeric Constant : 1 Variable : 2 Function : 3 Operator
    //Precedence: 
    IntegralNodeTypeEnum TokenType;
    int Precedence;

    IntegralTokenType()
    {
        
    }

    IntegralTokenType(IntegralNodeTypeEnum tokenType) : TokenType(tokenType)
    {
        switch(tokenType)
        {
            case INT_EMPTY:
                TokenString = "";
                break;
            default:
                TokenString = "";
                break;
        }
    }
    IntegralTokenType(IntegralNodeTypeEnum tokenType, std::string token) : TokenType(tokenType), TokenString(token)
    {
        
    }

    IntegralTokenType(IntegralNodeTypeEnum tokenType, std::string token, int precedence) : TokenType(tokenType), Precedence(precedence), TokenString(token)
    {

    }


    ~IntegralTokenType()
    {

    }

};

struct OperatorStructure
{
    std::unordered_map<std::string, IntegralTokenType> Map;
    int MaxLength;

    OperatorStructure() : MaxLength(0)
    {

    }

    void insertdefault()
    {
        Map.insert({{"^"},{INT_OPERATOR, "^", 4}});
        Map.insert({{"*"},{INT_OPERATOR, "*", 3}});
        Map.insert({{"/"},{INT_OPERATOR, "/", 3}});
        Map.insert({{"+"},{INT_OPERATOR, "+", 2}});
        Map.insert({{"-"},{INT_OPERATOR, "-", 2}});

    }

    IntegralTokenType operator [](std::string key)
    {
        return Map[key];
    }

    ~OperatorStructure()
    {

    }
};

struct OperandStructure
{
    std::unordered_map<std::string, IntegralTokenType> Map;
    int MaxLength;
    OperandStructure() : MaxLength(0)
    {

    }

    OperandStructure(std::string operands) : MaxLength(0)
    {
        std::vector<std::string> Operands = split(operands, ' ');
        for(int i = 0; i < Operands.size(); i++)
        {
            if(Operands[i].size() > MaxLength) MaxLength = Operands[i].size();
            Map.insert({Operands[i], {INT_VARIABLE,Operands[i]}});
        }
    }

    void set(std::string operands)
    {
        std::vector<std::string> Operands = split(operands, ' ');
        for(int i = 0; i < Operands.size(); i++)
        {
            if(Operands[i].size() > MaxLength) MaxLength = Operands[i].size();
            Map.insert({Operands[i], {INT_VARIABLE,Operands[i]}});
        }
    }

    IntegralTokenType operator [](std::string key)
    {
        return Map[key];
    }

    ~OperandStructure()
    {

    }
};

struct IntegralSymbolTable
{
    OperatorStructure OperatorTable;
    OperandStructure OperandTable;

    IntegralSymbolTable()
    {

    }

    IntegralTokenType operators(std::string key)
    {
        return OperatorTable[key];
    }

    ~IntegralSymbolTable()
    {

    }
};

#endif