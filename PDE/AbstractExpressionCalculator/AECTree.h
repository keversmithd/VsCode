#ifndef AEC_TREE
#define AEC_TREE

#include <stack>
#include <string>
#include "chainedhash.hpp"


enum AECNodeType
{
    AEC_CONSTANT,
    AEC_VARIABLE,
    AEC_FUNCTION,
    AEC_OPERATOR
};


struct AECTreeNode
{
    std::string Data;
    AECTreeNode* left = nullptr;
    AECTreeNode* right = nullptr;

};


struct AECOperator
{
    std::string Key;
    int value;

    AECOperator() : Key(""), value(0)
    {

    }

    int hash()
    {
        int hashIndex = 0;
        for(int i = 0; i < Key.size(); i++)
        {
            hashIndex += Key[i];
        }
        return hashIndex;
    }

    bool operator == (AECOperator A)
    {
        return (this->Key == A.Key);
    }

    ~AECOperator()
    {

    }


};

//Put AECNode Inside of AECTree

struct AECTree
{
public:
    std::stack<AECTreeNode*> root;
    ChainHash<AECOperator> OperatorTable;
    int MaxSizeOfOperator;
    int Elements;
public:
    AECTree(const std::string expression) : MaxSizeOfOperator(3), Elements(0)
    {
        AECOperator sin; sin.Key = "sin"; sin.value = 22;
        AECOperator cos; sin.Key = "sin"; sin.value = 22;
        OperatorTable.add(sin);
        OperatorTable.add(cos);
        parseInfixParen(expression);
    }

    void parseInfixParen(const std::string expression)
    {
        int OpenParenthesis = 0;
        

        bool PreviouslyOperand = false;
        int PreviousInsertionLocation = 0;


        for(int i = 0; i < expression.size(); i++)
        {
            if(expression[i] != ' ')
            {
                if(expression[i] == '(')
                {
                    //And the root is empty, procceed as normal.
                    if(!root.empty())
                    {
                        AECTreeNode* NewTree = new AECTreeNode();
                        root.push(NewTree);
                        PreviouslyOperand = false;
                        PreviousInsertionLocation = 0;
                        
                    }

                }
                else if (expression[i] == ')')
                {
                    if(!root.empty())
                    {
                        AECTreeNode* Appending = root.top();
                        root.pop();

                        AECTreeNode* Prepention = root.top();

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


                }else
                {
                    Elements++;
                    std::string OperatorString = isOperator(expression, i);
                    if(OperatorString != "0")
                    {
                        
                        AECTreeNode* OperatorNode;
                        i += (OperatorString.size() - 1); //Increment the loop forward ahead of the three absorbed signals.

                        if(!root.empty())
                        {
                            AECTreeNode* StackPop = root.top();
                            if(StackPop->Data == "")
                            {
                                StackPop->Data = OperatorString;
                            }else
                            {
                                root.pop();
                                OperatorNode = new AECTreeNode();
                                OperatorNode->Data = OperatorString;
                                OperatorNode->left = StackPop;
                                root.push(OperatorNode);
                            }

                        }
                        PreviouslyOperand = false;
                        

                    }else
                    {

                        std::string Operand = HandlePieceOfOperand(expression, i);

                        AECTreeNode* OperandNode = new AECTreeNode();
                        OperandNode->Data = Operand;

                        i += (Operand.size()-1);

                        if(PreviouslyOperand)
                        {
                            AECTreeNode* Multiplicative = new AECTreeNode();
                            Multiplicative->Data = '*';

                            if(PreviousInsertionLocation == 0)
                            {
                                AECTreeNode* RootPeek = root.top();
                                root.pop();
                                Multiplicative->left = RootPeek;
                                Multiplicative->right = OperandNode; 
                                root.push(Multiplicative);

                            }else if(PreviousInsertionLocation == 1)
                            {
                                AECTreeNode* RootPeek = root.top();
                                Multiplicative->left = RootPeek->left;
                                Multiplicative->right = OperandNode;
                                RootPeek->left = Multiplicative;

                            }else if(PreviousInsertionLocation == 2)
                            {
                                AECTreeNode* RootPeek = root.top();
                                Multiplicative->left = RootPeek->right;
                                Multiplicative->right = OperandNode;
                                RootPeek->right = Multiplicative;
                            }

                        }else
                        {
                            
                            if(!root.empty())
                            {
                                AECTreeNode* RootPeek = root.top();

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

                }
            }
        }
    }

    

    std::string isOperator(std::string value, int i)
    {
        std::string OperatorExtraction = "";

        if((value[i] >= 48 && value[i] <= 57))
        {
            return "0";
        }

        if (value[i] == '*' || value[i] == '+' || value[i] == '-' || value[i] == '/' || value[i] == '^')
        {
            return OperatorExtraction + value[i];
        }


        return "0";
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

        AECTreeNode* Root = root.top();

        if(Root == nullptr)
        {
            return "";
        }

        std::stack<AECTreeNode*> Stack;

        while(Root != nullptr || !Stack.empty())
        {

            while(Root != nullptr)
            {
                Stack.push(Root);
                Root = Root->left;
            }

            Root = Stack.top();
            Stack.pop();

            InOrderDisplay += Root->Data;

            Root = Root->right;
        }



        return InOrderDisplay;

        
    }

    ~AECTree()
    {

    }
};




#endif