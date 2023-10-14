#ifndef QUICK_X_H
#define QUICK_X_H 

#include "string.h"
#include <string>
#include <vector>

#include "QuickExOperator.h"
#include "QuickExParse.h"

struct QX
{
    std::vector<std::string> Groups;
    std::vector<std::string> Matches;
    std::string RegexPattern;
    std::string Value;

    std::vector<QXCapture> Capture;
    std::vector<QXParseInfo> ParseInfo;

    bool RegexPatternUpdated;

    QxOperatorTable OperatorTable;
    int CurrentGroup;

    QX(std::string regexPattern, std::string value) : CurrentGroup(-1), RegexPattern(regexPattern), Value(value), RegexPatternUpdated(false)
    {
        CompressRegexExpression();
    }

    void StartGroup()
    {
        Capture.push_back(QX_GROUP_INDICATOR);
    }
    void EndGroup()
    {
    }


    void CompressRegexExpression()
    {
        const int PatternLength = RegexPattern.size();

        for(int i = 0; i < PatternLength; i++)
        {
            
            if(RegexPattern[i] == '(')
            {
                StartGroup();
            }
            if(RegexPattern[i] == ')')
            {
                EndGroup();
            }

            if(RegexPattern[i] == '[')
            {
                QXCompress0(RegexPattern, i, Capture);
            }
            if(RegexPattern[i] == '\\')
            {
                QXEscape(RegexPattern,i, Capture, OperatorTable, PatternLength);
            }else
            if(RegexPattern[i] >= 33 && RegexPattern[i] <= 126 && !OperatorTable.In(RegexPattern[i]))
            {
                QXCompress1(RegexPattern, i, Capture);
            }
        }
    }

    bool FitsPattern(int& currentIndex, const int BodyEnd)
    {
        QXCaptureType CaptureType;
        QXParseInfo ParseInfo;
        QXMatch Match;
        Match.RangeBegin = currentIndex;

        for(int i = 0; i < Capture.size(); i++)
        {
            CaptureType = Capture[i].CaptureType;

            if(CaptureType == QX_CHARACTERS_RANGE)
            {
                ParseInfo = QX_PARSE_CHARACTER_RANGE(Value, currentIndex, Capture[i], BodyEnd);
                if(ParseInfo.SuccessfulParse)
                {
                    Match.FullCapture += ParseInfo.CaptureString;


                }else
                {
                    return false;
                }
            }
            

        }
    }

    void ParseBody()
    {
        for(int i = 0; i < Value.size(); i++)
        {
            
        }

    }


    #pragma region PatternMatching
    bool MatchesCharacterRange(int& RegexIndex, int& ValueIndex, std::string& Match)
    {
        for(int i = RegexIndex; i < RegexPattern.size(); i++)
        {
            if(RegexPattern[i] == '[')
            {
                
            }
            
        }
    }

    bool MatchesGroup(const std::string RegexPattern, int& RegIndex, const std::string Value, int& ValueIndex)
    {
        for(int i = RegIndex; i < RegexPattern.size(); i++)
        {
            if(RegexPattern[i] == ']')
            {
                i = RegexPattern.size();
            }
            RegIndex++;
        }
    }

    bool FitsPattern(int& ValueIndex, std::string& Match)
    {
        for(int i = 0; i < RegexPattern.size(); i++)
        {
            if(RegexPattern[i] == '[')
            {
                
            }
            
        }

    }

    void ProccessPattern()
    {
        std::string CurrentMatch;
        for(int i = 0; i < Value.size(); i++)
        {
            if(FitsPattern(i, CurrentMatch))
            {
                
            }
        }
    }

    #pragma endregion
};




#endif