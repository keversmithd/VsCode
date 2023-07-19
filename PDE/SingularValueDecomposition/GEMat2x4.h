#ifndef GEMAT_4x2
#define GEMAT_4x2

#include "GEmat2.h"
#include "GEMat4x2.h"

#define FT_MAT_SIZE 8

struct GEmat2x4
{
    float data[FT_MAT_SIZE];

    const int MATRIX_DIMENSION_X = 2;
    const int MATRIX_DIMENSION_Y = 4;
    const int MATRIX_END_INDEX = 7;
    const int MATRIX_SIZE = 8;

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

    GEmat4x2 transpose()
    {
        GEmat4x2 AT;


        //Limitation check.

        int ColumnIndex = 0; //From 0...3
        int RowIndex = 0; //From 0..1
        int TransposedRowIndex = 0;

        for(int i = 0; i < MATRIX_DIMENSION_Y; i++)
        {  
            for(int j = 0; j < MATRIX_DIMENSION_X; j++)
            {

                int TransposedRowIndex = i % MATRIX_DIMENSION_X;
                int TransposedColumnIndex = j + (i > (MATRIX_DIMENSION_X-1))*MATRIX_DIMENSION_X;
                AT[(TransposedRowIndex*MATRIX_DIMENSION_Y)+TransposedColumnIndex] = data[(i*MATRIX_DIMENSION_X)+j];

            }

        }

        

        return AT;
        


    }



};

struct GEmat2x4vec2
{
    GEmat2x4 A;
    GEvec2 B;
};

struct GEmat2x4LU
{
    GEmat2x4 L;
    GEmat2x4 U;
};


GEmat2x4vec2 gaussian(GEmat2x4 A, GEvec2 b)
{

    const int MATRIX_DIMENSION_X = 2;
    const int MATRIX_DIMENSION_Y = 4;
    const int MATRIX_END_INDEX = 7;
    const int MATRIX_SIZE = 8;

    int Pointer = 0;
    int Pointer1 = 0;
    int Pointer2 = 0;
    int C = 0;

    for(int i = 0; i < MATRIX_DIMENSION_Y; i++)
    {
        Pointer = (i*MATRIX_DIMENSION_Y) + i;

        if(A[Pointer] == 0)
        {
            C = 1;
            Pointer = ((i+C)*MATRIX_DIMENSION_X)+i;

            while((i+C) < MATRIX_DIMENSION_Y && A[Pointer] == 0)
            {
                C++;
                Pointer = ((i+C)*MATRIX_DIMENSION_X)+i;
            }

            if(C == MATRIX_DIMENSION_Y)
            {
                break;
            }

            for(int k = 0; k <= MATRIX_DIMENSION_X; k++)
            {
                Pointer = (i*MATRIX_DIMENSION_X)+k;
                Pointer1 = ((i+C)*MATRIX_DIMENSION_X)+k;

                swap(b[i], b[C]);
                swap(A[Pointer], A[Pointer1]);
            }
            
        }

        Pointer1 = (i*MATRIX_DIMENSION_X) + i;

        for(int j = 0; j < MATRIX_DIMENSION_Y; j++)
        {
            if(i != j)
            {
                Pointer = (j*MATRIX_DIMENSION_X)+i;
                
                float pro = A[Pointer]/A[Pointer1];
                
                for(int k = 0; k < MATRIX_DIMENSION_X; k++)
                {
                    Pointer = (i*MATRIX_DIMENSION_X) + k;
                    Pointer2 = (j*MATRIX_DIMENSION_X) + k;

                    A[Pointer2] = A[Pointer2] -  (A[Pointer]) * pro;
                }
                b[j] -= pro * b[i];

            }
        }

    }

    int DiagonalPointer = 0;
    for(int i = 0; i < MATRIX_DIMENSION_X; i++)
    {
        float DiagonalMeasure = A[(DiagonalPointer*MATRIX_DIMENSION_X)+i];
        if(DiagonalMeasure != 1)
        {
            float pro = 1.0/DiagonalMeasure;
            
            for(int k = 0; k < MATRIX_DIMENSION_X; k++)
            {
                A[(DiagonalPointer*MATRIX_DIMENSION_X)+k] *= pro;
            }
            b[DiagonalPointer] *= pro;
        }

        DiagonalPointer++;
    }


    return {A, b};

}


//Attempt at row echelon
// GEmat3vec3 gaussian_one(GEmat3 A, GEvec3 b)
// {
//     int MatrixDimension = MATRIX_DIMENSION;
    
//     int Pointer = 0;
//     int Pointer1 = 0;
//     int Pointer2 = 0;

//     int SearchDepth = 1;

//     float ScryingResult = 0;


//     for(int i = 1; i < MatrixDimension; i++) //From bottom and right two to the top.
//     {
//         for(int j = 0; j < SearchDepth; j++)
//         {
//             Pointer = (i*MatrixDimension)+j;
//             ScryingResult = A[Pointer];

//             if(ScryingResult != 0)
//             {
//                 ScryingResult = A[Pointer-MatrixDimension]; //Right above scrying result, guarenteed to hit do to I starting at one.
//                 Pointer1 = i-1;

//                 while(ScryingResult == 0 && Pointer1 >= 0) //Search down column for non zero or at the bounds of the matrix. (IMPLEMENT DOWN TO CURRENT ROW)
//                 {
//                     Pointer1--;
//                     ScryingResult = A[(Pointer1*MatrixDimension)+j];
                    
//                 }

//                 if(Pointer1 < 0)
//                 {
//                     break;
//                 }

//                 float pro = -A[Pointer]/ScryingResult;
                
//                 for(int k = 0; k < MatrixDimension; k++)
//                 {   
//                     A[(i*MatrixDimension) + k] += pro*A[(Pointer1*MatrixDimension)+k];
//                 }
//                 b[i] += pro*b[Pointer1];

//             }
//         }

//         SearchDepth++;
//     }


//     //possibly use back substition
//     int DiagonalPointer = 0;
//     for(int i = 0; i < MatrixDimension; i++)
//     {
//         float DiagonalMeasure = A[(DiagonalPointer*MatrixDimension)+i];
//         if(DiagonalMeasure != 1)
//         {
//             float pro = 1.0/DiagonalMeasure;
            
//             for(int k = 0; k < MatrixDimension; k++)
//             {
//                 if(A[(DiagonalPointer*MatrixDimension)+k] != 0)
//                 {
//                     A[(DiagonalPointer*MatrixDimension)+k] *= pro;
//                 }
//             }
//             b[DiagonalPointer] *= pro;
//         }

//         DiagonalPointer++;
//     }

//     b[(MatrixDimension-1)] /= A[(MatrixDimension*MatrixDimension)-1]; //Calculate last term in the vector.

//     int LeftShift = 2; //A left shift variable for when cancelation starts in the matrix.

//     for(int i = (MatrixDimension-2); i >= 0; i--) //Move backward
//     {
//         for(int j = (MatrixDimension-1); j > (MatrixDimension-LeftShift); j--)
//         {
//             b[i] -= b[j]*A[(i*MatrixDimension)+j];
//         }   

//         b[i] /= A[(i*MatrixDimension)+(MatrixDimension-LeftShift)];

//         LeftShift++;
//     }

//     return {A, b};
//     return {A, b};

// }

// GEmat3vec3 gaussian_two(GEmat3 A, GEvec3 b)
// {
//     int MatrixDimension = MATRIX_DIMENSION;
    
//     int Pointer = 0;
//     int Pointer1 = 0;
//     int Pointer2 = 0;

//     int SearchDepth = 1;

//     float ScryingResult = 0;


//     for(int i = 1; i < MatrixDimension; i++) //From bottom and right two to the top.
//     {
//         for(int j = 0; j < SearchDepth; j++)
//         {
//             Pointer = (i*MatrixDimension)+j;
//             ScryingResult = A[Pointer];

//             if(ScryingResult != 0)
//             {
//                 ScryingResult = A[Pointer-MatrixDimension]; //Right above scrying result, guarenteed to hit do to I starting at one.
//                 Pointer1 = i-1;

//                 while(ScryingResult == 0 && Pointer1 >= 0) //Search down column for non zero or at the bounds of the matrix. (IMPLEMENT DOWN TO CURRENT ROW)
//                 {
//                     Pointer1--;
//                     ScryingResult = A[(Pointer1*MatrixDimension)+j];
                    
//                 }

//                 if(Pointer1 < 0)
//                 {
//                     break;
//                 }

//                 float pro = -A[Pointer]/ScryingResult;
                
//                 for(int k = 0; k < MatrixDimension; k++)
//                 {   
//                     A[(i*MatrixDimension) + k] += pro*A[(Pointer1*MatrixDimension)+k];
//                 }
//                 b[i] += pro*b[Pointer1];

//             }
//         }

//         SearchDepth++;
//     }


//     b[(MatrixDimension-1)] /= A[(MatrixDimension*MatrixDimension)-1]; //Calculate last term in the vector.

//     int LeftShift = 2; //A left shift variable for when cancelation starts in the matrix.

//     for(int i = (MatrixDimension-2); i >= 0; i--) //Move backward
//     {
//         for(int j = (MatrixDimension-1); j > (MatrixDimension-LeftShift); j--)
//         {
//             b[i] -= b[j]*A[(i*MatrixDimension)+j];
//         }   

//         b[i] /= A[(i*MatrixDimension)+(MatrixDimension-LeftShift)];

//         LeftShift++;
//     }

//     return {A, b};

// }

// GEmat3LU LU(GEmat3 A, GEvec3 b)
// {
//     int MatrixDimension = MATRIX_DIMENSION;
    
//     GEmat3LU LU;

//     int DiagonalStart = 0;
    
//     for(int i = 0; i < MatrixDimension; i++)
//     {
//         LU.L[(i*MatrixDimension) + DiagonalStart] = 1;
//         for(int j = DiagonalStart+1; j < MatrixDimension; j++)
//         {
//             LU.L[(i*MatrixDimension) + j] = 0;
//         }
//         DiagonalStart++;
//     }

//     int Pointer = 0;
//     int Pointer1 = 0;
//     int Pointer2 = 0;

//     int SearchDepth = 1;

//     float ScryingResult = 0;


//     for(int i = 1; i < MatrixDimension; i++) //From bottom and right two to the top.
//     {
//         for(int j = 0; j < SearchDepth; j++)
//         {
//             Pointer = (i*MatrixDimension)+j;
//             ScryingResult = A[Pointer];

//             if(ScryingResult != 0)
//             {
//                 ScryingResult = A[Pointer-MatrixDimension]; //Right above scrying result, guarenteed to hit do to I starting at one.
//                 Pointer1 = i-1;

//                 while(ScryingResult == 0 && Pointer1 >= 0) //Search down column for non zero or at the bounds of the matrix. (IMPLEMENT DOWN TO CURRENT ROW)
//                 {
//                     Pointer1--;
//                     ScryingResult = A[(Pointer1*MatrixDimension)+j];
                    
//                 }

//                 if(Pointer1 < 0)
//                 {
//                     break;
//                 }

//                 float pro = -A[Pointer]/ScryingResult;
                
//                 for(int k = 0; k < MatrixDimension; k++)
//                 {   
//                     A[(i*MatrixDimension) + k] += pro*A[(Pointer1*MatrixDimension)+k];
                    
                    
//                 }

//                 LU.L[(i*MatrixDimension) + j] = -pro;
                
//             }
//         }

//         SearchDepth++;
//     }


//     LU.U = A;

//     return LU; 
// }

// GEvec3 LUYX(GEmat3 A, GEvec3 b)
// {
//     int MatrixDimension = MATRIX_DIMENSION;
    
//     GEmat3LU LU;

//     int DiagonalStart = 0;
    
//     for(int i = 0; i < MatrixDimension; i++)
//     {
//         LU.L[(i*MatrixDimension) + DiagonalStart] = 1;
//         for(int j = DiagonalStart+1; j < MatrixDimension; j++)
//         {
//             LU.L[(i*MatrixDimension) + j] = 0;
//         }
//         DiagonalStart++;
//     }

//     int Pointer = 0;
//     int Pointer1 = 0;
//     int Pointer2 = 0;

//     int SearchDepth = 1;

//     float ScryingResult = 0;


//     for(int i = 1; i < MatrixDimension; i++) //From bottom and right two to the top.
//     {
//         for(int j = 0; j < SearchDepth; j++)
//         {
//             Pointer = (i*MatrixDimension)+j;
//             ScryingResult = A[Pointer];

//             if(ScryingResult != 0)
//             {
//                 ScryingResult = A[Pointer-MatrixDimension]; //Right above scrying result, guarenteed to hit do to I starting at one.
//                 Pointer1 = i-1;

//                 while(ScryingResult == 0 && Pointer1 >= 0) //Search down column for non zero or at the bounds of the matrix. (IMPLEMENT DOWN TO CURRENT ROW)
//                 {
//                     Pointer1--;
//                     ScryingResult = A[(Pointer1*MatrixDimension)+j];
                    
//                 }

//                 if(Pointer1 < 0)
//                 {
//                     break;
//                 }

//                 float pro = -A[Pointer]/ScryingResult;
                
//                 for(int k = 0; k < MatrixDimension; k++)
//                 {   
//                     A[(i*MatrixDimension) + k] += pro*A[(Pointer1*MatrixDimension)+k];
                    
                    
//                 }

//                 LU.L[(i*MatrixDimension) + j] = -pro;
                
//             }
//         }

//         SearchDepth++;
//     }

    

//     //Algorithm for solving a lower triangular matrix equation


//     int Variables = 1;
//     for(int i = 1; i < MatrixDimension; i++)
//     {
//         for(int j = 0; j < Variables; j++)
//         {
//             b[i] -= b[j]*LU.L[(i*MatrixDimension)+j];
//         }

//         Variables++;
//     }

//     //Algorithm for solving an upper triangular matrix equation after the recent decomposition

//     //Solve bottom equation


//     b[(MatrixDimension-1)] /= A[(MatrixDimension*MatrixDimension)-1]; //Calculate last term in the vector.

//     int LeftShift = 2; //A left shift variable for when cancelation starts in the matrix.

//     for(int i = (MatrixDimension-2); i >= 0; i--) //Move backward
//     {
//         for(int j = (MatrixDimension-1); j > (MatrixDimension-LeftShift); j--)
//         {
//             b[i] -= b[j]*A[(i*MatrixDimension)+j];
//         }   

//         b[i] /= A[(i*MatrixDimension)+(MatrixDimension-LeftShift)];

//         LeftShift++;
//     }
    

//     return b;

//     //LUX = B
//     //UX = Y
//     //SOLVE U

// }


#endif