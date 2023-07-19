#ifndef GEMAT_3
#define GEMAT_3

#define MATRIX_SIZE 9
#define MATRIX_END_INDEX 8
#define MATRIX_DIMENSION 3

#include "stdio.h"
void swap(float& a, float& b)
{
    const float temp = a;

    a = b;
    b = temp;
}

struct GEmat3
{
    float data[MATRIX_SIZE];

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
        for(int j = 0; j < MATRIX_DIMENSION; j++)
        {
            ij = (rowi*MATRIX_DIMENSION) + j;
            jj = (rowj*MATRIX_DIMENSION) + j;
            temp = data[ij];
            data[ij] = data[jj];
            data[jj] = temp;
        }
    }


    void display()
    {
        
        int ij;
        printf("\n");
        for(int i = 0; i < MATRIX_DIMENSION; i++)
        {
            printf("|");
            for(int j = 0; j < MATRIX_DIMENSION; j++)
            {
                ij = (i*MATRIX_DIMENSION)+j;
                printf("%f ", data[ij]);
            }
            printf("|\n");
        }
    }

};

struct GEvec3
{
    float data[MATRIX_DIMENSION];

    void swapRows(int i, int j)
    {
        float temp = data[i];
        data[i] = data[j];
        data[j] = temp;
    }

    float& operator [](const int index)
    {
        if(index < 0 || index > (MATRIX_DIMENSION-1))
        {
            return data[0];
        }
        return data[index];
    }

    void display()
    {
        printf("\n");
        for(int i = 0; i < MATRIX_DIMENSION; i++)
        {
            printf("|%f|\n", data[i]);
        }
    }

};

struct GEmat3vec3
{
    GEmat3 A;
    GEvec3 B;
};

struct GEmat3LU
{
    GEmat3 L;
    GEmat3 U;
};


GEmat3vec3 gaussian(GEmat3 A, GEvec3 b)
{
    int MatrixDimension = MATRIX_DIMENSION;
    
    int Pointer = 0;
    int Pointer1 = 0;
    int Pointer2 = 0;
    int C = 0;

    for(int i = 0; i < MatrixDimension; i++)
    {
        Pointer = (i*MatrixDimension) + i;

        if(A[Pointer] == 0)
        {
            C = 1;
            Pointer = ((i+C)*MatrixDimension)+i;

            while((i+C) < MatrixDimension && A[Pointer] == 0)
            {
                C++;
                Pointer = ((i+C)*MatrixDimension)+i;
            }

            if(C == MATRIX_DIMENSION)
            {
                break;
            }

            for(int k = 0; k <= MatrixDimension; k++)
            {
                Pointer = (i*MatrixDimension)+k;
                Pointer1 = ((i+C)*MatrixDimension)+k;

                swap(b[i], b[C]);
                swap(A[Pointer], A[Pointer1]);
            }
            
        }

        Pointer1 = (i*MatrixDimension) + i;

        for(int j = 0; j < MatrixDimension; j++)
        {
            if(i != j)
            {
                Pointer = (j*MatrixDimension)+i;
                
                float pro = A[Pointer]/A[Pointer1];
                
                for(int k = 0; k < MatrixDimension; k++)
                {
                    Pointer = (i*MatrixDimension) + k;
                    Pointer2 = (j*MatrixDimension) + k;

                    A[Pointer2] = A[Pointer2] -  (A[Pointer]) * pro;
                }
                b[j] -= pro * b[i];

            }
        }

    }

    int DiagonalPointer = 0;
    for(int i = 0; i < MatrixDimension; i++)
    {
        float DiagonalMeasure = A[(DiagonalPointer*MatrixDimension)+i];
        if(DiagonalMeasure != 1)
        {
            float pro = 1.0/DiagonalMeasure;
            
            for(int k = 0; k < MatrixDimension; k++)
            {
                A[(DiagonalPointer*MatrixDimension)+k] *= pro;
            }
            b[DiagonalPointer] *= pro;
        }

        DiagonalPointer++;
    }


    return {A, b};

}


//Attempt at row echelon
GEmat3vec3 gaussian_one(GEmat3 A, GEvec3 b)
{
    int MatrixDimension = MATRIX_DIMENSION;
    
    int Pointer = 0;
    int Pointer1 = 0;
    int Pointer2 = 0;

    int SearchDepth = 1;

    float ScryingResult = 0;


    for(int i = 1; i < MatrixDimension; i++) //From bottom and right two to the top.
    {
        for(int j = 0; j < SearchDepth; j++)
        {
            Pointer = (i*MatrixDimension)+j;
            ScryingResult = A[Pointer];

            if(ScryingResult != 0)
            {
                ScryingResult = A[Pointer-MatrixDimension]; //Right above scrying result, guarenteed to hit do to I starting at one.
                Pointer1 = i-1;

                while(ScryingResult == 0 && Pointer1 >= 0) //Search down column for non zero or at the bounds of the matrix. (IMPLEMENT DOWN TO CURRENT ROW)
                {
                    Pointer1--;
                    ScryingResult = A[(Pointer1*MatrixDimension)+j];
                    
                }

                if(Pointer1 < 0)
                {
                    break;
                }

                float pro = -A[Pointer]/ScryingResult;
                
                for(int k = 0; k < MatrixDimension; k++)
                {   
                    A[(i*MatrixDimension) + k] += pro*A[(Pointer1*MatrixDimension)+k];
                }
                b[i] += pro*b[Pointer1];

            }
        }

        SearchDepth++;
    }


    //possibly use back substition
    int DiagonalPointer = 0;
    for(int i = 0; i < MatrixDimension; i++)
    {
        float DiagonalMeasure = A[(DiagonalPointer*MatrixDimension)+i];
        if(DiagonalMeasure != 1)
        {
            float pro = 1.0/DiagonalMeasure;
            
            for(int k = 0; k < MatrixDimension; k++)
            {
                if(A[(DiagonalPointer*MatrixDimension)+k] != 0)
                {
                    A[(DiagonalPointer*MatrixDimension)+k] *= pro;
                }
            }
            b[DiagonalPointer] *= pro;
        }

        DiagonalPointer++;
    }

    b[(MatrixDimension-1)] /= A[(MatrixDimension*MatrixDimension)-1]; //Calculate last term in the vector.

    int LeftShift = 2; //A left shift variable for when cancelation starts in the matrix.

    for(int i = (MatrixDimension-2); i >= 0; i--) //Move backward
    {
        for(int j = (MatrixDimension-1); j > (MatrixDimension-LeftShift); j--)
        {
            b[i] -= b[j]*A[(i*MatrixDimension)+j];
        }   

        b[i] /= A[(i*MatrixDimension)+(MatrixDimension-LeftShift)];

        LeftShift++;
    }

    return {A, b};
    return {A, b};

}

GEmat3vec3 gaussian_two(GEmat3 A, GEvec3 b)
{
    int MatrixDimension = MATRIX_DIMENSION;
    
    int Pointer = 0;
    int Pointer1 = 0;
    int Pointer2 = 0;

    int SearchDepth = 1;

    float ScryingResult = 0;


    for(int i = 1; i < MatrixDimension; i++) //From bottom and right two to the top.
    {
        for(int j = 0; j < SearchDepth; j++)
        {
            Pointer = (i*MatrixDimension)+j;
            ScryingResult = A[Pointer];

            if(ScryingResult != 0)
            {
                ScryingResult = A[Pointer-MatrixDimension]; //Right above scrying result, guarenteed to hit do to I starting at one.
                Pointer1 = i-1;

                while(ScryingResult == 0 && Pointer1 >= 0) //Search down column for non zero or at the bounds of the matrix. (IMPLEMENT DOWN TO CURRENT ROW)
                {
                    Pointer1--;
                    ScryingResult = A[(Pointer1*MatrixDimension)+j];
                    
                }

                if(Pointer1 < 0)
                {
                    break;
                }

                float pro = -A[Pointer]/ScryingResult;
                
                for(int k = 0; k < MatrixDimension; k++)
                {   
                    A[(i*MatrixDimension) + k] += pro*A[(Pointer1*MatrixDimension)+k];
                }
                b[i] += pro*b[Pointer1];

            }
        }

        SearchDepth++;
    }


    b[(MatrixDimension-1)] /= A[(MatrixDimension*MatrixDimension)-1]; //Calculate last term in the vector.

    int LeftShift = 2; //A left shift variable for when cancelation starts in the matrix.

    for(int i = (MatrixDimension-2); i >= 0; i--) //Move backward
    {
        for(int j = (MatrixDimension-1); j > (MatrixDimension-LeftShift); j--)
        {
            b[i] -= b[j]*A[(i*MatrixDimension)+j];
        }   

        b[i] /= A[(i*MatrixDimension)+(MatrixDimension-LeftShift)];

        LeftShift++;
    }

    return {A, b};

}

GEmat3LU LU(GEmat3 A, GEvec3 b)
{
    int MatrixDimension = MATRIX_DIMENSION;
    
    GEmat3LU LU;

    int DiagonalStart = 0;
    
    for(int i = 0; i < MatrixDimension; i++)
    {
        LU.L[(i*MatrixDimension) + DiagonalStart] = 1;
        for(int j = DiagonalStart+1; j < MatrixDimension; j++)
        {
            LU.L[(i*MatrixDimension) + j] = 0;
        }
        DiagonalStart++;
    }

    int Pointer = 0;
    int Pointer1 = 0;
    int Pointer2 = 0;

    int SearchDepth = 1;

    float ScryingResult = 0;


    for(int i = 1; i < MatrixDimension; i++) //From bottom and right two to the top.
    {
        for(int j = 0; j < SearchDepth; j++)
        {
            Pointer = (i*MatrixDimension)+j;
            ScryingResult = A[Pointer];

            if(ScryingResult != 0)
            {
                ScryingResult = A[Pointer-MatrixDimension]; //Right above scrying result, guarenteed to hit do to I starting at one.
                Pointer1 = i-1;

                while(ScryingResult == 0 && Pointer1 >= 0) //Search down column for non zero or at the bounds of the matrix. (IMPLEMENT DOWN TO CURRENT ROW)
                {
                    Pointer1--;
                    ScryingResult = A[(Pointer1*MatrixDimension)+j];
                    
                }

                if(Pointer1 < 0)
                {
                    break;
                }

                float pro = -A[Pointer]/ScryingResult;
                
                for(int k = 0; k < MatrixDimension; k++)
                {   
                    A[(i*MatrixDimension) + k] += pro*A[(Pointer1*MatrixDimension)+k];
                    
                    
                }

                LU.L[(i*MatrixDimension) + j] = -pro;
                
            }
        }

        SearchDepth++;
    }


    LU.U = A;

    return LU; 
}

GEvec3 LUYX(GEmat3 A, GEvec3 b)
{
    int MatrixDimension = MATRIX_DIMENSION;
    
    GEmat3LU LU;

    int DiagonalStart = 0;
    
    for(int i = 0; i < MatrixDimension; i++)
    {
        LU.L[(i*MatrixDimension) + DiagonalStart] = 1;
        for(int j = DiagonalStart+1; j < MatrixDimension; j++)
        {
            LU.L[(i*MatrixDimension) + j] = 0;
        }
        DiagonalStart++;
    }

    int Pointer = 0;
    int Pointer1 = 0;
    int Pointer2 = 0;

    int SearchDepth = 1;

    float ScryingResult = 0;


    for(int i = 1; i < MatrixDimension; i++) //From bottom and right two to the top.
    {
        for(int j = 0; j < SearchDepth; j++)
        {
            Pointer = (i*MatrixDimension)+j;
            ScryingResult = A[Pointer];

            if(ScryingResult != 0)
            {
                ScryingResult = A[Pointer-MatrixDimension]; //Right above scrying result, guarenteed to hit do to I starting at one.
                Pointer1 = i-1;

                while(ScryingResult == 0 && Pointer1 >= 0) //Search down column for non zero or at the bounds of the matrix. (IMPLEMENT DOWN TO CURRENT ROW)
                {
                    Pointer1--;
                    ScryingResult = A[(Pointer1*MatrixDimension)+j];
                    
                }

                if(Pointer1 < 0)
                {
                    break;
                }

                float pro = -A[Pointer]/ScryingResult;
                
                for(int k = 0; k < MatrixDimension; k++)
                {   
                    A[(i*MatrixDimension) + k] += pro*A[(Pointer1*MatrixDimension)+k];
                    
                    
                }

                LU.L[(i*MatrixDimension) + j] = -pro;
                
            }
        }

        SearchDepth++;
    }

    

    //Algorithm for solving a lower triangular matrix equation


    int Variables = 1;
    for(int i = 1; i < MatrixDimension; i++)
    {
        for(int j = 0; j < Variables; j++)
        {
            b[i] -= b[j]*LU.L[(i*MatrixDimension)+j];
        }

        Variables++;
    }

    //Algorithm for solving an upper triangular matrix equation after the recent decomposition

    //Solve bottom equation


    b[(MatrixDimension-1)] /= A[(MatrixDimension*MatrixDimension)-1]; //Calculate last term in the vector.

    int LeftShift = 2; //A left shift variable for when cancelation starts in the matrix.

    for(int i = (MatrixDimension-2); i >= 0; i--) //Move backward
    {
        for(int j = (MatrixDimension-1); j > (MatrixDimension-LeftShift); j--)
        {
            b[i] -= b[j]*A[(i*MatrixDimension)+j];
        }   

        b[i] /= A[(i*MatrixDimension)+(MatrixDimension-LeftShift)];

        LeftShift++;
    }
    

    return b;

    //LUX = B
    //UX = Y
    //SOLVE U

}


#endif