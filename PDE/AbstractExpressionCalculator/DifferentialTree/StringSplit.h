#ifndef STRING_SPLIT_H
#define STRING_SPLIT_H

#include <vector>
#include <string>

std::vector<std::string> split(std::string str, char delimiter)
{
    int j = 0;
    bool newdelim = false;
    std::vector<std::string> stringSplit;
    stringSplit.push_back("");
    for(int i = 0; i < str.size(); i++)
    {
        if(str[i] == delimiter)
        {
            if(newdelim == true)
            {
                j++;
                stringSplit.push_back("");
                newdelim = false;
            }
        }else
        {
            newdelim = true;
            stringSplit[j].push_back(str[i]);
        }
    }

    return stringSplit;
}


#endif