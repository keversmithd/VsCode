#ifndef QUICK_X_OPERATOR_H
#define QUICK_X_OPERATOR_H

#include <vector>
#include <string>
#include <unordered_map>

#pragma region QXCaptureType
enum QXCaptureQuantifier
{
    QX_ONE_OR_MORE,
    QX_ZERO_OR_MORE,
};
enum QXCaptureType
{
    QX_CHARACTERS_RANGE,
    QX_STRING_LITERAL,
    QX_OPERATOR_FUNCTION,
    QX_GROUP_INDICATOR,
};



struct QXRange
{
    int Start;
    int End;
};

struct QXCapture
{
    
    QXRange CharacterRange;
    std::string FullStringCapture;
    QXCaptureType CaptureType;
    int(*OperatorFunction)(char value);
    
    QXCapture(QXRange _CharacterRange, std::string _FullStringCapture, QXCaptureType _CaptureType) : CharacterRange(_CharacterRange), FullStringCapture(_FullStringCapture),CaptureType(_CaptureType), OperatorFunction(nullptr)
    {

    }
    QXCapture(QXRange _CharacterRange, QXCaptureType _CaptureType) : CharacterRange(_CharacterRange), FullStringCapture(),CaptureType(_CaptureType),OperatorFunction(nullptr)
    {

    }   
    QXCapture(std::string _FullStringCapture, QXCaptureType _CaptureType) : CharacterRange(), FullStringCapture(_FullStringCapture),CaptureType(_CaptureType), OperatorFunction(nullptr)
    {

    }
    QXCapture(QXCaptureType _CaptureType) : CharacterRange(), FullStringCapture(),CaptureType(_CaptureType), OperatorFunction(nullptr)
    {

    }
    QXCapture(int(*_OperatorFunction)(char value), QXCaptureType _CaptureType) : CharacterRange(), FullStringCapture(),CaptureType(_CaptureType), OperatorFunction(_OperatorFunction)
    {

    }


};

#pragma endregion
  
#pragma region QXOperatorFunctionsList
int QXOperator0(char value)
{
    return (value >= 48 && value <= 57);
}
//operator S or something for any character 
int QXOperator1(char value)
{
    return (value >= 33 && value <= 126);
}
#pragma endregion

#pragma region QXOperators

struct QXOperatorArrayEntry
{
    char OperatorToken;
    int(*QxOperatorFunction)(char value);

    QXOperatorArrayEntry(char _OperatorToken, int(*_OperatorFunction)(char value)) : OperatorToken(_OperatorToken), QxOperatorFunction(_OperatorFunction)
    {
        
    }


};



struct QxOperatorTable
{
    std::unordered_map<char, int> QxOperatorsIndexMap;
    std::vector<int(*)(char symbol)> QxOperatorsFunctions;

    void RegisterOperatorsArray(QXOperatorArrayEntry* QXOperatorArray, int OperatorsLength)
    {
        for(int i = 0; i < OperatorsLength; i++)
        {
            InsertQXOperator(QXOperatorArray[i].OperatorToken, QXOperatorArray[i].QxOperatorFunction);
        }
    }


    int QXOperatorIndex(char OperatorChar)
    {
        
    }

    bool In(char Operator)
    {
        return (QxOperatorsIndexMap.find(Operator) != QxOperatorsIndexMap.end());
    }

    int OperatorIndex(char Operator)
    {
        std::unordered_map<char,int>::iterator It = QxOperatorsIndexMap.find(Operator);
        if(It != QxOperatorsIndexMap.end())
        {
            return It->second;
        }else
        {
            return -1;
        }
        
    }

    void InsertQXOperator(char Operator, int(*OperatorFunction)(char value))
    {
        QxOperatorsFunctions.push_back(OperatorFunction);
        QxOperatorsIndexMap.insert({Operator,QxOperatorsFunctions.size()-1});
    }



    int QXOperatorIndex(char PotentialOperator)
    {
        std::unordered_map<char,int>::iterator SearchIteration = QxOperatorsIndexMap.find(PotentialOperator);
        if(SearchIteration != QxOperatorsIndexMap.end())
        {
            return SearchIteration->second;
        }

        return -1;
    }

    int ProcessQXOperator(char PotentialOperator)
    {

    }

};

QxOperatorTable GlobalOperatorTable;

#pragma endregion

#pragma region QXCompress
void QXCompress0(std::string& regexPattern, int& RegexIndex, std::vector<QXCapture>& CaptureCodes)
{
    int EndOfPattern = regexPattern.size()-1;
    
    int OperandIndex = 0;
    while(regexPattern[RegexIndex] != ']' && RegexIndex != EndOfPattern)
    {
        if(RegexIndex < EndOfPattern-2)
        {
            if(regexPattern[RegexIndex+1] == '-')
            {
                char StartChar = regexPattern[RegexIndex];
                char EndChar = regexPattern[RegexIndex+2];
                QXCapture CaptureCode({StartChar,EndChar},"",QX_CHARACTERS_RANGE);
                CaptureCodes.push_back(CaptureCode);
                OperandIndex++;
                RegexIndex+=3;
            }
        }
        else
        {
            char StartChar = regexPattern[RegexIndex];
            QXCapture CaptureCode(std::to_string(StartChar),QX_STRING_LITERAL);
            CaptureCodes.push_back(CaptureCode);
            RegexIndex++;
        }
    }


}

void QXCompress1(std::string& regexPattern, int& RegexIndex, std::vector<QXCapture>& CaptureCodes)
{
    std::string ExactString = "";
    while(regexPattern[RegexIndex] >= 33 && regexPattern[RegexIndex] <= 126)
    {
        ExactString += regexPattern[RegexIndex];
        RegexIndex++;
    }
    QXCapture CaptureCode(ExactString, QX_STRING_LITERAL);
    CaptureCodes.push_back(CaptureCode);
}

void QXCompress2(std::string& regexPattern, int& RegexIndex, std::vector<QXCapture>& CaptureCodes)
{
    int OperatorChar = regexPattern[RegexIndex];
    

    RegexIndex++;
}
#pragma endregion

#pragma region QXEscapeSeq

    void QXEscape(std::string& RegexPattern, int& RegexIndex, std::vector<QXCapture>& CaptureCodes, QxOperatorTable& OperatorTable, const int PatternLength)
    {
        if(RegexIndex+1 > PatternLength-1)
        {
            RegexIndex+=2;
            return;
        }
        int OperatorIndex = OperatorTable.OperatorIndex(RegexPattern[RegexIndex+1]);
        if(RegexPattern[RegexIndex+1] >= 33 && RegexPattern[RegexIndex+1] <= 126 && OperatorIndex == -1)
        {
            QXCapture Refresh(std::to_string(RegexPattern[RegexIndex+1]), QX_STRING_LITERAL);
            CaptureCodes.push_back(Refresh);
            RegexIndex+=2;
            return;
        }else
        {
            QXCapture Refresh(OperatorTable.QxOperatorsFunctions[OperatorIndex], QX_OPERATOR_FUNCTION);
            CaptureCodes.push_back(Refresh);
            RegexIndex+=2;
            return;
        }
    }

#pragma endregion

#endif