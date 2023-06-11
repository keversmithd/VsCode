#ifndef MAT_4_H
#define MAT_4_H

#include "EmptyConst.hpp"

template<typename T>
struct vec2
{
    T entries[2];
};


template<typename T>
struct mat4
{
    T entries[16];

    T& access(int i, int j)
    {
        int index = (j*4)+i;
        if(index >= 16){return entries[0];}
        return entries[index];
    }

    

    
    void setdig(double k)
    {
        int j = 0;
        entries[0] = k;
        entries[5] = k;
        entries[10] = k;
        entries[15] = k;
    }
    void setdig(double k, double c)
    {
        entries[0] = k;
        entries[5] = k;
        entries[10] = k;
        entries[15] = k;

        entries[4] = c;
        entries[9] = c;
        entries[14] = c;

        entries[1] = c;
        entries[6] = c;
        entries[11] = c;
    }

    mat4<T> transpose()
    {
        mat4<T> tran();


        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                tran.access(i,j) = entries[(i*4)+j];
            }
        }

        return tran;
    }

    void operator = (const mat4<T> other)
    {
        memcpy(entries, other.entries, sizeof(T)*16);
    }



};



template<typename T>
struct mfd
{
    T entries[16];

    mfd(double zero = zero(T())) : entries{zero, zero, zero, zero,
                                          zero, zero, zero, zero,
                                          zero, zero, zero, zero,
                                          zero, zero, zero, zero}
    {
        
    }


    T& access(int i, int j)
    {
        int index = (j*4)+i;
        if(index >= 16){return entries[0];}
        return entries[index];
    }

    void setdig(double k)
    {
        int j = 0;
        entries[0] = k;
        entries[5] = k;
        entries[10] = k;
        entries[15] = k;
    }

    void setdig(double k, double c)
    {
        entries[0] = k;
        entries[5] = k;
        entries[10] = k;
        entries[15] = k;

        entries[4] = c;
        entries[9] = c;
        entries[14] = c;

        entries[1] = c;
        entries[6] = c;
        entries[11] = c;
    }

    mfd<T> transpose()
    {
        mfd<T> tran();


        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                tran.access(i,j) = entries[(i*4)+j];
            }
        }

        return tran;
    }

};





#endif

