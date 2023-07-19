#ifndef POP_FIX_H
#define POP_FIX_H

#include <string>
#include <stack>
#include <vector>
#include <unordered_map>

enum POPNodeType
{
    POP_CONSTANT,
    POP_VARIABLE,
    POP_FUNCTION,
    POP_OPERATOR,
    POP_PLUS = 43,
    POP_MINUS = 45,
    POP_DIVIDE = 47,
    POP_MULTIPLY = 42,
    POP_EXPONENT = 94,
    POP_LEFT_PAREN,
    POP_RIGHT_PAREN,
    POP_COS,
    POP_SIN,
    POP_LOG,
    POP_LN,
    POP_EXPRESSION
};

const int precedenceTable[] =
{
    1,2,3,4
    //+, -, /, *, ^
};

const bool associativityTable[] =
{
    false, true, false, true
    //+, -, /, *, ^
};

struct POPNode
{
    std::string Data;
    POPNodeType NodeType;
    int Precendence;
};

struct POPExpression
{
    std::vector<POPNode> PostFixExpression;
    

    POPExpression(std::string expression)
    {
        parseInfixParen(expression);
    }

    void parseInfixParen(std::string expression)
    {
        std::stack<POPNode> OperationalStack;
        POPNode TopTemp;
        int TopTempPrecedence = 0;

        int StringSize = expression.size();

        int OperatorPrecedence = 0;
        int TopTempAssociativity = 0;
        int OperatorAssociativity = 0;

        bool PreviouslyOperand = false;

        for(int i = 0; i < StringSize; i++)
        {
            if(expression[i] == ' ')
            {

            }
            else if(expression[i] == '(')
            {
                OperationalStack.push({"(", POP_LEFT_PAREN, 0});
                PostFixExpression.push_back({"(", POP_LEFT_PAREN, 0});
                PreviouslyOperand = false;

            }else if (expression[i] == ')')
            {
                bool match = false; //Instead of releasing the parenthesis we are keeping the parenthesis in the post fix expression for differentiation.

                while(!OperationalStack.empty() && OperationalStack.top().NodeType != POP_LEFT_PAREN)
                {
                    PostFixExpression.push_back(OperationalStack.top());
                    OperationalStack.pop();
                    match = true;
                }

                if(match != true)
                {
                    //error
                }
                
                PostFixExpression.push_back({")", POP_RIGHT_PAREN, 0});
                OperationalStack.pop();

                PreviouslyOperand = false;
            }
            else
            {
                std::string Operator = isOperator(expression, i);
                OperatorPrecedence = precedence(Operator.c_str()[0]);
                OperatorAssociativity = associativity(Operator.c_str()[0]);        


                if(Operator != "0")
                {

                    if(!OperationalStack.empty())
                    {

                    TopTemp = OperationalStack.top();
                    TopTempAssociativity = associativity(TopTemp.Data.c_str()[0]);
                    
                    bool CompletedAssociativity = false;
                    while(!OperationalStack.empty() && CompletedAssociativity == false)
                    {
                        TopTemp = OperationalStack.top();

                        if((TopTemp.Precendence >= OperatorPrecedence))
                        {
                            OperationalStack.pop();
                            PostFixExpression.push_back(TopTemp);

                        }else
                        {
                            CompletedAssociativity = true;
                        }

                    }
                    }
                    OperationalStack.push({Operator, (POPNodeType)Operator[0], OperatorPrecedence});

                    PreviouslyOperand = false;

                }else
                {  
                    bool ConstantStatus = false;
                    std::string Operand = HandlePieceOfOperand(expression, i, ConstantStatus);
                    i += Operand.size()-1;
                    PostFixExpression.push_back({Operand, (ConstantStatus == true) ? POP_CONSTANT : POP_VARIABLE, 0});
                    if(PreviouslyOperand == true)
                    {
                        OperationalStack.push({"*", POP_MULTIPLY, 5});
                    }
                    PreviouslyOperand = true;
                }


            }

            


        }

        while(!OperationalStack.empty())
        {
            TopTemp = OperationalStack.top();
            OperationalStack.pop();
            PostFixExpression.push_back(TopTemp);
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
    bool isOperator(char value)
    {
        if (value == '*' || value == '+' || value == '-' || value == '/' || value == '^')
        {
            return true;
        }

        return false;
    }
    std::string HandlePieceOfOperand(std::string value, int i, bool& constant)
    {
        std::string OperandExpression = "";
        OperandExpression += value[i];

        bool IsNumberBasedOperand = ((value[i] >= 48 && value[i] <= 57));
        constant = IsNumberBasedOperand;


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

    int precedence(char Operator)
    {
        return (Operator == '/') ? 3 : (Operator == '*') ? 3 : (Operator == '+') ? 2 : (Operator == '-') ? 2 : (Operator == '^') ? 4 : 0;
    }
    int associativity(char Operator)
    {
        return (Operator == '+' || Operator == '-' || Operator == '/' || Operator == '*') ? 1 : 2;
    }


    double evaluate(char symbol, double value)
    {
        std::stack<POPNode> OperandStack;

        POPNode OperandTemp;

        //POP pool matrix
        POPNode PopPool1;
        POPNode PopPool2;
        double Argument1;
        double Argument2;
        double ResultZ;

        std::string Result;

        if(PostFixExpression.empty())
        {
            return 0.0;
        }

        for(int i = 0; i < PostFixExpression.size(); i++)
        {
            OperandTemp = PostFixExpression[i];

            switch(OperandTemp.NodeType)
            {
                case POP_CONSTANT:
                    OperandStack.push(OperandTemp);
                    break;
                case POP_VARIABLE:
                    if(OperandTemp.Data[0] == symbol)
                    {
                        OperandTemp.Data = std::to_string(value);
                        OperandStack.push(OperandTemp);

                    }else
                    {
                        OperandStack.push(OperandTemp);
                    }
                    break;
                case POP_PLUS:
                    PopPool1 = OperandStack.top();
                    OperandStack.pop();
                    PopPool2 = OperandStack.top();
                    OperandStack.pop();
                    Result = PopPool2.Data + " + " + PopPool1.Data;

                    if(ConstantEvaluable(Result) == true)
                    {
                        Argument1 = atof(PopPool1.Data.c_str());
                        Argument2 = atof(PopPool2.Data.c_str());

                        ResultZ = Argument1 + Argument2;

                        Result = std::to_string(ResultZ);

                        OperandStack.push({Result, POP_CONSTANT, 1});
                    }else
                    {



                        OperandStack.push({Result, POP_EXPRESSION, 1});
                    }
                    break;


                case POP_DIVIDE:
                    PopPool1 = OperandStack.top();
                    OperandStack.pop();
                    PopPool2 = OperandStack.top();
                    OperandStack.pop();
                    Result = PopPool2.Data + " / " + PopPool1.Data;
                    if(ConstantEvaluable(Result) == true)
                    {
                        Argument1 = atof(PopPool2.Data.c_str());
                        Argument2 = atof(PopPool1.Data.c_str());

                        ResultZ = Argument1 / Argument2;

                        Result = std::to_string(ResultZ);

                        OperandStack.push({Result, POP_CONSTANT, 1});
                    }else
                    {
                        OperandStack.push({Result, POP_EXPRESSION, 1});
                    }

                    break;
                    
                case POP_MULTIPLY:
                    PopPool1 = OperandStack.top();
                    OperandStack.pop();
                    PopPool2 = OperandStack.top();
                    OperandStack.pop();
                    Result = PopPool2.Data + " * " + PopPool1.Data;

                    if(ConstantEvaluable(Result) == true)
                    {
                        Argument1 = atof(PopPool2.Data.c_str());
                        Argument2 = atof(PopPool1.Data.c_str());

                        ResultZ = Argument1 * Argument2;

                        Result = std::to_string(ResultZ);

                        OperandStack.push({Result, POP_CONSTANT, 1});
                    }else
                    {
                        //we know have a slightly more complicated expression
                        OperandStack.push({Result, POP_EXPRESSION, 1});
                    }

                    break;
                case POP_EXPONENT:
                    PopPool1 = OperandStack.top();
                    OperandStack.pop();
                    PopPool2 = OperandStack.top();
                    OperandStack.pop();
                    Result = PopPool2.Data + "^" + PopPool1.Data;

                    if(ConstantEvaluable(Result) == true)
                    {
                        Argument1 = atof(PopPool2.Data.c_str());
                        Argument2 = atof(PopPool1.Data.c_str());

                        ResultZ = pow(Argument1, Argument2);

                        Result = std::to_string(ResultZ);

                        OperandStack.push({Result, POP_CONSTANT, 1});
                    }else
                    {
                        //we know have a slightly more complicated expression
                        OperandStack.push({Result, POP_EXPRESSION, 1});
                    }
                    break;


                
                default:
                    break;

            }


        }


        int v = 0;


    }

    double ConstantEvaluable(std::string value)
    {
        
        for(int i = 0; i < value.size(); i++)
        {
            if(isOperator(value[i]) || ((value[i] >= 48 && value[i] <= 57) || (value[i] == '.') || (value[i]) == ' '))
            {
            }else
            {
                return false;
            }
        }

        return true;

    }

    std::string SimplifyExpression(std::string expression)
    {
        std::unordered_map<char, double> LikeTermCoefficients;
        double ConstantTerm = 0;
        
        for(int i = 0; i < expression.size(); i++)
        {
            if(isalpha(expression[i]))
            {
                if(LikeTermCoefficients.find(expression[i]) != LikeTermCoefficients.end())
                {

                }else
                {
                    //LikeTermCoefficients.insert(expression[i], )
                }
            }


        }




        

    }

    void readExpression()
    {
        for(int i = 0; i < PostFixExpression.size(); i++)
        {
            printf("'%s' ", PostFixExpression[i].Data.c_str());
        }
    }


};

#endif