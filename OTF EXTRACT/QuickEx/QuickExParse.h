#ifndef QUICK_EX_PARSE_H
#define QUICK_EX_PARSE_H 

#include <string>
#include "QuickExOperator.h"

#pragma region QX_PARSE_INFO
struct QXParseInfo
{
    bool SuccessfulParse;
    int ParseBegin;
    int ParseEnd;
    std::string CaptureString;

    QXParseInfo() : SuccessfulParse(false), ParseBegin(0), ParseEnd(0), CaptureString("")
    {

    }

    QXParseInfo(bool ParseStatus) : SuccessfulParse(ParseStatus), ParseBegin(0), ParseEnd(0)
    {

    }

    QXParseInfo(bool ParseStatus, int RangeBegin, int RangeEnd) : SuccessfulParse(ParseStatus), ParseBegin(RangeBegin), ParseEnd(RangeEnd)
    {

    }

    ~QXParseInfo()
    {

    }
};
#pragma endregion

#pragma region QX_PARSE
QXParseInfo QX_PARSE_CHARACTER_RANGE(std::string Body, int& BodyIndex, QXCapture CaptureCode, const int BodyEnd) 
{

    QXParseInfo ParsingInfo;
    ParsingInfo.ParseBegin = BodyIndex;

    int RangeBegin = CaptureCode.CharacterRange.Start;
    int RangeEnd = CaptureCode.CharacterRange.End;


    while(BodyIndex != BodyEnd && Body[BodyIndex] >= RangeBegin && Body[BodyIndex] <= RangeEnd)
    {
        ParsingInfo.CaptureString += Body[BodyIndex];
        BodyIndex++;
    }

    ParsingInfo.ParseEnd = BodyIndex;

    if(ParsingInfo.ParseEnd != ParsingInfo.ParseBegin)
    {
        ParsingInfo.SuccessfulParse = true;
    }

    return ParsingInfo;

}

QXParseInfo QX_PARSE_STRING_LITERAL(std::string Body, int& BodyIndex, QXCapture CaptureCode, const int BodyEnd)
{

    QXParseInfo ParsingInfo;
    ParsingInfo.ParseBegin = BodyIndex;
    int CaptureLength = CaptureCode.FullStringCapture.size();
    char BodyCode = 0;
    
    for(int i = 0; i < CaptureLength; i++)
    {
        BodyCode = Body[BodyIndex++];
        if(CaptureCode.FullStringCapture[i] == Body[BodyIndex++])
        {
            ParsingInfo.CaptureString += BodyCode;
        }else
        {
            return ParsingInfo;
        }
    }

    ParsingInfo.ParseEnd = BodyIndex;
    ParsingInfo.SuccessfulParse = true;


}

QXParseInfo QX_PARSE_OPERATOR(std::string Body, int& BodyIndex, QXCapture CaptureCode, const int BodyEnd)
{

    QXParseInfo ParsingInfo;
    ParsingInfo.ParseBegin = BodyIndex;
    
    while(BodyIndex)

    ParsingInfo.ParseEnd = BodyIndex;
    ParsingInfo.SuccessfulParse = true;

    while(BodyIndex != BodyEnd && CaptureCode.OperatorFunction(Body[BodyIndex]))
    {
        ParsingInfo.CaptureString += Body[BodyIndex];
        BodyIndex++;
    }

}

#pragma endregion

#pragma region QX_MATCH

struct QXMatch
{
    std::string FullCapture;
    int RangeBegin;
    int RangeEnd;
};

#pragma endregion

#endif