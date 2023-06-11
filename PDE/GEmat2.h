#ifndef GEMAT2_H
#define GEMAT2_h

#include "stdio.h"

struct GEmat2
{
    float data[4];

    float& operator[](const int index)
    {
        if(index < 0 || index > 3)
        {
            return data[0];
        }

        return data[index];
    }

    void swapRows()
    {
        const float temp1 = data[0];
        const float temp2 = data[1];

        data[0] = data[2];
        data[1] = data[3];
        data[2] = temp1;
        data[3] = temp2; 
    }

    void multiplyRow(const int selector, const float constant)
    {
        if(selector < 0 || selector > 1)
        {
            return;
        }

        data[0 + (selector+(selector > 0))] *= constant;
        data[1 + (selector+(selector > 0))] *= constant;
    }

    void display()
    {
        printf("\n|% f % f|\n|% f % f|\n", data[0], data[1], data[2], data[3]);
    }

};

struct GEvec2
{
    float data[2];

    void swapRows()
    {
        const float temp = data[0];
        data[0] = data[1];
        data[1] = temp;
    }

    float& operator [](const int index)
    {
        if(index < 0 || index > 1)
        {
            return data[0];
        }
        return data[index];
    }

    void display()
    {
        printf("\n|%f|\n|%f|\n", data[0], data[1]);
    }

};

struct GEmat2vec2
{
    GEmat2 A;
    GEvec2 B;
};

GEmat2 gemat2(float x, float y, float z, float w)
{
    GEmat2 newmat;
    newmat.data[0] = x;
    newmat.data[1] = y;
    newmat.data[2] = z;
    newmat.data[3] = w;

    return newmat;
}

GEvec2 operator *(const GEmat2 A, const GEvec2 x)
{
    const float a = A.data[0],b = A.data[1],c = A.data[2],d = A.data[3];
    GEvec2 result;
    result[0] = (A.data[0] * x.data[0])+(A.data[1]*x.data[1]);
    result[1] = (A.data[2] * x.data[0]) +(A.data[3]*x.data[1]);
    return result;
}

GEmat2 gaussjordan(GEmat2 m2)
{
    float requiredConstantOperation;
    
    if(m2[0] == 0)
    {
        if(m2[2] != 0)
        {
            m2.swapRows();
        }else
        {
            if(m2[1] != 0 && m2[1] != 1)
            {
                requiredConstantOperation = 1/m2[1];
                m2[0] *= requiredConstantOperation;
                m2[1] *= requiredConstantOperation;  
            }
        }
        
    }

    if(m2[0] != 0 && m2[0] != 1)
    {
        requiredConstantOperation = 1/m2[0];
        m2[0] *= requiredConstantOperation;
        m2[1] *= requiredConstantOperation;
    }

    if (m2.data[0] != 0)
    {
        requiredConstantOperation = -m2[2]/m2[0];
        m2[2] += requiredConstantOperation*m2[0];
        m2[3] += requiredConstantOperation*m2[1];

        if(m2[3] != 0 && m2[3] != 1)
        {
            requiredConstantOperation = 1/m2[3];
            m2[3] *= requiredConstantOperation;
        }

        if(m2.data[3] != 0)
        {
            requiredConstantOperation = -m2[1]/m2[3];
            m2[0] += requiredConstantOperation*m2[2];
            m2[1] += requiredConstantOperation*m2[3];
        }

    }

   
    
    return m2;
}

void swap(float& a, float& b)
{
    const float temp = a;

    a = b;
    b = temp;
}

GEmat2 gaussJordanF(GEmat2 m2, GEvec2 v2)
{
    int MatrixDegree = 2;

    int IdentityIndex = 0;

    //Column Movement
    int ColumnTransversal = 0;
    int ColumaryIndex = 0;

    //Row Movement
    int UpperRowIndex = 0;
    int LowerRowIndex = 0;

    int Flag = 0;

    int RowMovement = 0;



    for(int i = 0; i < MatrixDegree; i++)
    {
        IdentityIndex = (i*MatrixDegree)+i;

        if(m2[IdentityIndex] == 0) //If the identity index is zero.
        {
            ColumnTransversal = 1;
            ColumaryIndex = ((i+ColumnTransversal)*MatrixDegree)+i; //Look at the descending columnary numbers in the column.

            while((i+ColumnTransversal) < MatrixDegree && m2[ColumaryIndex] == 0) //To the bottom of the matrix do not stop until a non zero is found.
            {
                ColumaryIndex++;
                ColumaryIndex = ((i+ColumnTransversal)*MatrixDegree)+i;
            }

            if((i+ColumnTransversal) == MatrixDegree)
            {
                Flag = 1; //If the loop reached all the way to then end withought finding a non zero break and set flag.
                break;
            }

            for(int j = i, k = 0; k <= MatrixDegree; k++)
            {
                UpperRowIndex = (j*MatrixDegree)+k;
                LowerRowIndex = ((j+ColumaryIndex)*MatrixDegree)+k;
                swap(m2[UpperRowIndex], m2[LowerRowIndex]);
            }
        }


        for(int j = 0; j < MatrixDegree; j++)
        {
            if(i != j)
            {
                RowMovement = (j*MatrixDegree)+i;
                float pro = m2[RowMovement]/m2[IdentityIndex];
                
                for(int k = 0; k < MatrixDegree; k++)
                {
                    UpperRowIndex = (i*MatrixDegree) + k;
                    LowerRowIndex = (j*MatrixDegree) + k;

                    m2[LowerRowIndex] = m2[LowerRowIndex] -  (m2[UpperRowIndex]) * pro;
                }

            }
        }


    }

    return m2;
}

int CheckConsistency(GEmat2 m2)
{

    int MatrixDegree = 2;

    int flag = 3;
    int i, j;
    float sum;
     
    // flag == 2 for infinite solution
    // flag == 3 for No solution
    for (i = 0; i < MatrixDegree; i++)
    {
        sum = 0;
        for (j = 0; j < MatrixDegree; j++)       
            sum = sum + m2[(i*MatrixDegree) + j];
        if (sum == m2[(i*MatrixDegree) + j])
            flag = 2;       
    }
    return flag;
}

GEmat2 inverse(GEmat2 matrix)
{
    float a = matrix[0],b = matrix[1],c = matrix[2],d = matrix[3];
    float det = (a*d)-(b*c);
    if( ((a*d)-(b*c)) == 0 )
    {
        return matrix;
    }
    
    matrix[0] = d/det;
    matrix[1] = -b/det;
    matrix[2] = -c/det;
    matrix[3] = a/det;

    return matrix;

}

GEmat2vec2 gaussjordan(GEmat2 m2, GEvec2 v2)
{

    float requiredConstantOperation;

    if(m2[0] == 0)
    {
        if(m2[2] != 0)
        {
            m2.swapRows();
            v2.swapRows();
        }else
        {
            if(m2[1] != 0 && m2[1] != 1)
            {
                requiredConstantOperation = 1/m2[1];
                m2[0] *= requiredConstantOperation;
                m2[1] *= requiredConstantOperation;
                v2[0] *= requiredConstantOperation;  
            }
        }
        
    }

    if(m2[0] != 0 && m2[0] != 1)
    {
        requiredConstantOperation = 1/m2[0];
        m2[0] *= requiredConstantOperation;
        m2[1] *= requiredConstantOperation;
        v2[0] *= requiredConstantOperation;
        
    }

    if (m2.data[0] != 0)
    {
        requiredConstantOperation = -m2[2]/m2[0];
        m2[2] += requiredConstantOperation*m2[0];
        m2[3] += requiredConstantOperation*m2[1];
        v2[1] += requiredConstantOperation*v2[0];

        if(m2[3] != 0 && m2[3] != 1)
        {
            requiredConstantOperation = 1/m2[3];
            m2[3] *= requiredConstantOperation;
            v2[1] *= requiredConstantOperation;
        }

        if(m2.data[3] != 0)
        {
            requiredConstantOperation = -m2[1]/m2[3];
            m2[0] += requiredConstantOperation*m2[2];
            m2[1] += requiredConstantOperation*m2[3];
            v2[0] += requiredConstantOperation*v2[1];
        }

    }
    
    GEmat2vec2 mx;
    mx.A = m2;
    mx.B = v2;

    return mx;

}




#endif