#ifndef GEN_MAT_h
#define GEN_MAT_H

#include <memory.h>
#include <iostream>

#include "EmptyConst.hpp"

template<int I, int J, typename T>
struct MatG
{
    T entries[I*J];

    void SetAll(const T value)
    {
        memset(entries,  value, sizeof(T)*I*J);
    }

    T& access(int i, int j)
    {
        int index = (j*4)+i;
        if(index >= I*J){return entries[0];}
        return entries[index];
    }
};


template<int I, int J, int K, typename T>
MatG<I,J,T> Toeplitz(T entries[K])
{
    MatG<I,J,T> newMat;
    newMat.SetAll(zero(T()));

    int halfspace = (K/2);
    int datatotransport = 0;
    int column = 0;

    for(int row = 0; row < J; row++)
    {
        datatotransport = K-halfspace;

        while(datatotransport + column > I)
        {
            datatotransport--;
        }

        if(datatotransport != 0)
        {
            memcpy((newMat.entries)+(row*I)+(column), entries+halfspace, sizeof(T)*(datatotransport));
        }
        

        if(halfspace > 0)
        {
            halfspace -=1;
        }

        
        if(row >= 1)
        {
            column++;
        }
        

        

        

    }

    while(halfspace > 0)
    {
        halfspace -= 1;
    }



    
    
    return newMat;
}

template<int I, int J, typename T>
void viewmatg(MatG<I,J,T> g)
{
    for(int i = 0; i < I*J; i++)
    {
        std::cout << g.entries[i] << ", ";
        if((i+1) % I == 0)
        {
            std::cout << std::endl;
        }
    }
}









#endif