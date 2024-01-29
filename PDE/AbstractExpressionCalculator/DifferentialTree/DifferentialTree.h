#ifndef DIFFERENTIAL_TREE_H
#define DIFFERENTIAL_TREE_H

#include <stack>

#include "DifferentialNode.h"

struct IntegralTree
{
    IntegralSymbolTable SymbolTable;
    std::stack<IntegralNode*> root;
    int Elements;

    IntegralTree(std::string Expression) : Elements(0)
    {
        parseInfixParen(Expression);
    }

    void HandleOpenParenthesis(std::string& expression, int& PreviousInsertionLocation, bool& PreviouslyOperand, int& OpenParenthesis, int& IterationIndex)
    {
        //And the root is empty, procceed as normal.
        if(!root.empty())
        {
            IntegralNode* NewTree = new IntegralNode();
            root.push(NewTree);
            PreviouslyOperand = false;
            PreviousInsertionLocation = 0;   
        }
    }

    void HandleClosedParenthesis(std::string& expression, int& PreviousInsertionLocation, bool& PreviouslyOperand, int& OpenParenthesis, int& IterationIndex)
    {
        if(!root.empty())
        {
            IntegralNode* Appending = root.top();
            root.pop();

            IntegralNode* Prepention = root.top();

            if(Prepention->left == nullptr)
            {
                Prepention->left = Appending;
            }else if(Prepention->right == nullptr)
            {
                Prepention->right = Appending;
            }else
            {
                Prepention->right->right = Appending;
            }

        }
    }

    void HandleOperator(std::string& expression, int& PreviousInsertionLocation, bool& PreviouslyOperand, int& OpenParenthesis, int& IterationIndex, IntegralTokenType& OperatorInformation)
    {
        Elements++;
        
        IntegralNode* OperatorNode;
        IterationIndex += (OperatorInformation.TokenString.size() - 1); //Increment the loop forward ahead of the three absorbed signals.

        if(!root.empty())
        {
            IntegralNode* StackPop = root.top();
            if(StackPop->NodeSymbol == "")
            {
                StackPop->NodeSymbol = OperatorInformation.TokenString;
                StackPop->NodeType = OperatorInformation;
            }else
            {
                root.pop();
                OperatorNode = new IntegralNode(OperatorInformation);
                OperatorNode->left = StackPop;
                root.push(OperatorNode);
            }

        }
        PreviouslyOperand = false;
    }

    void HandleOperand(std::string& expression, int& PreviousInsertionLocation, bool& PreviouslyOperand, int& OpenParenthesis, int& IterationIndex)
    {
        std::string Operand = HandlePieceOfOperand(expression, IterationIndex);
        IntegralNode* OperandNode = new IntegralNode();
        OperandNode->NodeSymbol = Operand;
        IterationIndex += (Operand.size()-1);

        if(PreviouslyOperand)
        {
            IntegralNode* Multiplicative = new IntegralNode(SymbolTable.operators("*"));

            if(PreviousInsertionLocation == 0)
            {
                IntegralNode* RootPeek = root.top();
                root.pop();
                Multiplicative->left = RootPeek;
                Multiplicative->right = OperandNode; 
                root.push(Multiplicative);

            }else if(PreviousInsertionLocation == 1)
            {
                IntegralNode* RootPeek = root.top();
                Multiplicative->left = RootPeek->left;
                Multiplicative->right = OperandNode;
                RootPeek->left = Multiplicative;

            }else if(PreviousInsertionLocation == 2)
            {
                IntegralNode* RootPeek = root.top();
                Multiplicative->left = RootPeek->right;
                Multiplicative->right = OperandNode;
                RootPeek->right = Multiplicative;
            }

        }else
        {
            
            if(!root.empty())
            {
                IntegralNode* RootPeek = root.top();

                if(RootPeek->left == nullptr)
                {
                    RootPeek->left = OperandNode;
                    PreviousInsertionLocation = 1;
                    
                }else if(RootPeek->right == nullptr)
                {
                    RootPeek->right = OperandNode;
                    PreviousInsertionLocation = 2;
                }else
                {
                    root.push(OperandNode);
                    PreviousInsertionLocation = 0;
                }

            }else
            {
                root.push(OperandNode);
            }
        }





        PreviouslyOperand = true;
    }

    void HandleToken(std::string& expression, int& PreviousInsertionLocation, bool& PreviouslyOperand, int& OpenParenthesis, int& IterationIndex)
    {
        if(expression[IterationIndex] == '(')
        {
            HandleOpenParenthesis(expression,PreviousInsertionLocation,PreviouslyOperand,OpenParenthesis,IterationIndex);
        }
        else if (expression[IterationIndex] == ')')
        {
            HandleClosedParenthesis(expression,PreviousInsertionLocation,PreviouslyOperand,OpenParenthesis,IterationIndex);
        }else
        {
            IntegralTokenType OperatorInformation = isOperator(expression, IterationIndex);
            if(OperatorInformation.TokenString != "0")
            {
                HandleOperator(expression,PreviousInsertionLocation,PreviouslyOperand,OpenParenthesis,IterationIndex,OperatorInformation);
            }else
            {
                HandleOperand(expression,PreviousInsertionLocation,PreviouslyOperand,OpenParenthesis,IterationIndex);
            }

        }
    }

    void parseInfixParen(std::string expression)
    {
        int OpenParenthesis = 0;
        

        bool PreviouslyOperand = false;
        int PreviousInsertionLocation = 0;


        for(int i = 0; i < expression.size(); i++)
        {
            if(expression[i] != ' ')
            {
                HandleToken(expression, PreviousInsertionLocation, PreviouslyOperand, OpenParenthesis, i);
            }

                
        }
    }

    IntegralTokenType isOperator(std::string value, int index)
    {   
        IntegralTokenType NodeType;
        std::string OperatorExtraction = std::to_string(value[index]);
        auto It = SymbolTable.OperatorTable.Map.find(OperatorExtraction);

        if(It != SymbolTable.OperatorTable.Map.end())
        {
            NodeType = It->second;
            return NodeType;
        }else
        {
            
            OperatorExtraction.clear();
            for(int i = 0; i < SymbolTable.OperatorTable.MaxLength; i++)
            {
                OperatorExtraction.push_back(value[index+i]);
            }
            
            It = SymbolTable.OperatorTable.Map.find(OperatorExtraction);

            while(It == SymbolTable.OperatorTable.Map.end() && OperatorExtraction.size() > 1)
            {
                OperatorExtraction.pop_back();
                It = SymbolTable.OperatorTable.Map.find(OperatorExtraction);
            }
        }
        
        if(OperatorExtraction.size() > 1)
        {
            NodeType = It->second;
            return NodeType;
        }else
        {
            NodeType.TokenString = "0";
            NodeType.TokenType = INT_EMPTY;
            return NodeType;
        }
    }

    std::string HandlePieceOfOperand(std::string value, int i)
    {
        std::string OperandExpression = "";
        OperandExpression += value[i];

        bool IsNumberBasedOperand = ((value[i] >= 48 && value[i] <= 57));

        for(int j = i+1; j < value.size(); j++)
        {
            char piece  = value[j];

            if(IsNumberBasedOperand)
            {
                if ((piece >= 48 && piece <= 57) || (piece == '.'))
                {
                    OperandExpression += piece;
                }
                else if(piece == 'E')
                {
                    OperandExpression += piece;
                    OperandExpression += value[j+1];
                    j++;
                }else
                {
                    j = value.size();
                }

            }else
            {
                if (value[j] == '*' || value[j] == '+' || value[j] == '-' || value[j] == '/' || value[j] == '^')
                {
                    j = value.size();
                }
                else if(piece >= 65 && piece <= 122)
                {
                    OperandExpression += piece;

                }else
                {
                    j = value.size();
                }
            }
            

        }

        return OperandExpression;
    }

    std::string inOrder()
    {
        std::string InOrderDisplay = ""; //Return string with information about the traversal.

        IntegralNode* Root = root.top();

        if(Root == nullptr)
        {
            return "";
        }

        std::stack<IntegralNode*> Stack;

        while(Root != nullptr || !Stack.empty())
        {

            while(Root != nullptr)
            {
                Stack.push(Root);
                Root = Root->left;
            }

            Root = Stack.top();
            Stack.pop();

            InOrderDisplay += Root->NodeSymbol;

            Root = Root->right;
        }



        return InOrderDisplay;

        
    }


};






#endif