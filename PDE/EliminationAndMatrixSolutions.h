#ifndef MAT_SOLVE_H
#define MAT_SOLVE_H
#include "mat4.hpp"

template<typename T>
void toRowEchelong(mat4<T> Matrix)
{
    double workValue; 


    int pivotSequence[] = {4, 8, 9}; //sequence of pivots to change for an Upper Triangular Matrix

    int currentRow;
    int workColumn;
    int workRow;
    int workIndex = 0;
    double x = 0;

    for(int i = 0; i < 3; i++)
    {

        int pivotValue = pivotSequence[i]; //we are jumping to the pivot based on the pivot sequence array.
        double pivotEntry = Matrix.entries[pivotValue]; //pivot Entry is the value at the specific index.

        currentRow = (pivotValue+1) % 4; //Current row  measures the pivot index by its row order
        workColumn = (currentRow > 0) ? (pivotValue/(currentRow * 4)) : pivotValue; //Work Column is the column that the pivotValue is in
        workRow = (workRow != 0) ? currentRow-1 : 0; //Sets the work row one up from the pivot

        while(Matrix.access(workColumn, workRow) == 0 && workRow > 0) //looks for no zeros
        {
            workRow--;
        }

        //if Matrix at workRow == 0, throw();

        workIndex = (workColumn) + (workRow * 4); //current index of the basis item

        workValue = Matrix.entries[workIndex]; //value is at the work index.

        x = -pivotEntry/workValue; //x = (a + bx = c) x = (-pivotEntry)/workValue

        int currentIndex = pivotValue;

        for(int j = 0; j < 3; j++)
        {
            Matrix.entries[currentIndex] += x * Matrix.entries[workIndex];

            currentIndex++;
            workIndex++;
        }

    }
}

template<typename T>
vec2<mat4<T>> GeneralGaussJordanElimination(mat4<T> Matrix)
{
    mat4<T> Upper = Matrix;
    int n = 4; //n is the number of rows in the matrix
    int searchDepth = 1;

    T e,f;
    int w = 4;

    int ei = 0; 
    int fi = 0;

    double x = 0;

    int currentRow;
    int currentColumn;

    int upperRow;
    int upperColumn;

    int eii = 0;
    int fii = 0;

    for(int i = 1; i < n; i++)
    {
        for(int j = 0; j < searchDepth; j++)
        {
            ei = j+(i*n);
            e = Upper.entries[ei];

            if(e != 0)
            {
                
                currentColumn = ((ei) % n);
                currentRow = ei/n;
                
   
                fi = ei - (n); //index above ei
                f = Upper.entries[fi]; //element at fi

                while(f == 0 && fi > currentRow)
                {
                    fi -= n;
                    f = Upper.entries[fi];
                }
                
                upperColumn = (fi) % n;
                upperRow = fi/n;


                eii = currentColumn+(currentRow*n);
                fii = upperColumn+(upperRow*n);
                

                x = -e/f;

                for(int k = 0; k < n; k++)
                {
                    Upper.entries[eii+k] += Upper.entries[fii+k]*x;
                }
            }

        }

        searchDepth++;
    }


    double determinant = Upper.entries[0]; //determinant of the upper triangle

    for(int i = 1, j = 1; i < n; i++)
    {
        int d = j + (i*n);
        determinant *= Upper.entries[d];
        j++;

    }

    std::cout << determinant << std::endl;


    return {Upper,Upper};
}   




#endif