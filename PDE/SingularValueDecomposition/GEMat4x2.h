#ifndef GEmat4x2_H
#define GEmat4x2_H


#include "utils.h"


struct GEmat4x2
{
    float data[8];

    const int MATRIX_DIMENSION_X = 4;
    const int MATRIX_DIMENSION_Y = 2;
    const int MATRIX_SIZE = 8;
    const int MATRIX_END_INDEX = 7;

    

    float& operator[](const int index)
    {
        if(index < 0 || index > MATRIX_END_INDEX)
        {
            return data[0];
        }

        return data[index];
    }

    void swapRows(int rowi, int rowj)
    {
        float temp;
        int ij,jj;
        for(int j = 0; j < MATRIX_DIMENSION_X; j++)
        {
            ij = (rowi*MATRIX_DIMENSION_Y) + j;
            jj = (rowj*MATRIX_DIMENSION_Y) + j;
            temp = data[ij];
            data[ij] = data[jj];
            data[jj] = temp;
        }
    }


    void display()
    {
        
        int ij;
        printf("\n");
        for(int i = 0; i < MATRIX_DIMENSION_Y; i++)
        {
            printf("|");
            for(int j = 0; j < MATRIX_DIMENSION_X; j++)
            {
                ij = (i*MATRIX_DIMENSION_X)+j;
                printf("%f ", data[ij]);
            }
            printf("|\n");
        }
    }

};


#endif