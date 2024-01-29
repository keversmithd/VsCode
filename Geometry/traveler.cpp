#include <iostream>
#include <stack>
#include <vector>
#include <unordered_map>


void pathSum(std::string permutation, std::unordered_map<std::string,int>& edges, int& totalWeight, int& minWeight)
{

    std::string temp = "";
    int tempWeight = 0;

    for(int i = 0; i < permutation.size(); i++)
    {
        temp = "";
        temp += permutation[i];
        temp += permutation[i+1];
        

        if(temp.size() > 1)
        {
            if(edges.find(temp) == edges.end())
            {
                printf("Error at %s\n", temp.c_str());
            }
            
            totalWeight += edges[temp];
            tempWeight += edges[temp];
        }
        

    }

    if(tempWeight < minWeight)
    {
        minWeight = tempWeight;

        printf("Min weighted path: %s at %d \n", permutation.c_str(), minWeight);
    }

}

void backtrack(std::string s, int start, std::vector<std::string>& permutations, char* stLocs, int n)
{
    if(start == n)
    {
        s += "a";
        permutations.push_back(s);

    }

    for(int i = start; i < n; i++)
    {
        char temp = s[start];
        s[start] = s[i];
        s[i] = temp;

        backtrack(s, start+1, permutations, stLocs, n);

        temp = s[start];
        s[start] = s[i];
        s[i] = temp;

    }

}

int main()
{
    int pathLength[] = {3,10,6,1,7,2,8,5,4,9};
    char stLocs[] = {'a','b','c','d','e'};
    std::unordered_map<std::string, int> edges = {
        {"ab", 3},
        {"ba",3},
        {"bc",10},
        {"cb",10},
        {"cd",6},
        {"dc",6},
        {"de",1},
        {"ed",1},
        {"ea",7},
        {"ae",7},

        {"ad",4},
        {"da",4},
        {"ac",8},
        {"ca",8},

        {"be",2},
        {"eb",2},
        {"bd",9},
        {"db",9},
        {"ec",5},
        {"ce",5},
    };
    std::vector<std::string> permutations;
    std::string s = "abcde";
    backtrack(s, 0, permutations, stLocs, 5);


    int totalWeigt = 0;
    int minWeight = INT_MAX;

    for(int i = 0; i < permutations.size(); i++)
    {
        pathSum(permutations[i], edges, totalWeigt, minWeight);
    }
    
    printf("Total weight: %d\n", totalWeigt);

    
    



}