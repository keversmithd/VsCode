#ifndef DIFFERENTIAL_NODE_H
#define DIFFERENTIAL_NODE_H

#include "DifferentialSymbols.h"
#include "DifferentialNodeType.h"

struct IntegralNode
{
    IntegralNode* left; //Left Operand
    IntegralNode* right; //Right Operand
    IntegralNode* integral; //Previous Integral

    IntegralTokenType NodeType;
    std::string NodeSymbol;

    IntegralNode() : left(nullptr),right(nullptr),integral(nullptr), NodeSymbol(""), NodeType(INT_EMPTY)
    {
        
    }

    IntegralNode(IntegralTokenType type) : NodeType(type), NodeSymbol(type.TokenString)
    {

    }

    ~IntegralNode()
    {
        
    }

};

#endif