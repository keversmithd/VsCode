#ifndef GEmatd_H_D
#define GEmatd_H_D
#include <initializer_list>
#include <memory>
#include <exception>
#include <math.h>
#include <limits>
#include <iomanip>
#include "GEcommon.h"


struct GEmatd
{
    double* data;
    bool copy;
    int MATRIX_DIMENSION_X;
    int MATRIX_DIMENSION_Y;
    int MATRIX_END_INDEX;
    int MATRIX_SIZE;

    #pragma region Working
    GEmatd(int x, int y) : data(nullptr), MATRIX_DIMENSION_X(0), MATRIX_DIMENSION_Y(0), MATRIX_END_INDEX(0), MATRIX_SIZE(0), copy(false)
    {
        MATRIX_SIZE = x*y;
        data = new double[MATRIX_SIZE];
        MATRIX_DIMENSION_X = x;
        MATRIX_DIMENSION_Y = y;
        MATRIX_END_INDEX = MATRIX_SIZE-1;
    }

    GEmatd(const GEmatd &c) : data(c.data), MATRIX_DIMENSION_X(c.MATRIX_DIMENSION_X), MATRIX_DIMENSION_Y(c.MATRIX_DIMENSION_Y), MATRIX_END_INDEX(c.MATRIX_END_INDEX), MATRIX_SIZE(c.MATRIX_SIZE), copy(true)
    {
        copy = true;
    }
    GEmatd(std::initializer_list<double> L) : data(nullptr), MATRIX_DIMENSION_X(0), MATRIX_DIMENSION_Y(0), MATRIX_END_INDEX(0), MATRIX_SIZE(0), copy(false)
    {
        MATRIX_DIMENSION_Y = L.size();
        MATRIX_DIMENSION_X = 1;

        MATRIX_SIZE = L.size();
        MATRIX_END_INDEX = MATRIX_SIZE-1;
        data = new double[MATRIX_SIZE];

        for(int i = 0; i < L.size(); i++)
        {
            data[i] = *(L.begin() + i);
        }

    }
    GEmatd(int y) : data(nullptr), MATRIX_DIMENSION_X(0), MATRIX_DIMENSION_Y(0), MATRIX_END_INDEX(0), MATRIX_SIZE(0), copy(false)
    {
        MATRIX_SIZE = y;
        data = new double[MATRIX_SIZE];
        MATRIX_DIMENSION_X = 1;
        MATRIX_DIMENSION_Y = y;
        MATRIX_END_INDEX = MATRIX_SIZE-1;
    }

    double& operator[](const int index)
    {
        if(index < 0 || index > MATRIX_END_INDEX)
        {
            return data[0];
        }

        return data[index];
    }
    const double c(const int index) const
    {
        if(index < 0 || index > MATRIX_END_INDEX)
        {
            return data[0];
        }

        return data[index];
    }
    void swapRows(int rowi, int rowj)
    {
        double temp;
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

    void operator=(std::initializer_list<double> L)
    {

        for(int i = 0; i < L.size(); i++)
        {
            data[i] = *(L.begin() + i);
        }
    }

    GEmatd cpy()
    {
        GEmatd result(MATRIX_DIMENSION_X, MATRIX_DIMENSION_Y);
        memcpy(result.data, data, sizeof(double)*MATRIX_SIZE);
        return result;
    }

    const double operator()(int i, int j)
    {
        if(i > MATRIX_DIMENSION_X || j > MATRIX_DIMENSION_Y || i < 0 || j < 0)
        {
            return data[0];
        }

        return data[(j * MATRIX_DIMENSION_X) + i];


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
                printf("%.8e ", data[ij]);
            }
            printf("|\n");
        }
    }

    GEmatd transpose()
    {
        GEmatd AT(MATRIX_DIMENSION_Y, MATRIX_DIMENSION_X);
        //Limitation check.
        int ColumnIndex = 0; //From 0...3
        int RowIndex = 0; //From 0..1
        int TransposedRowIndex = 0;

        for(int i = 0; i < MATRIX_DIMENSION_X; i++)
        {  
            for(int j = 0; j < MATRIX_DIMENSION_Y; j++)
            {
                
                if(((i*MATRIX_DIMENSION_Y)+j) > AT.MATRIX_END_INDEX || ((j*MATRIX_DIMENSION_X) + i) > MATRIX_END_INDEX)
                {
                    throw std::out_of_range("dimension mismatch");
                }
                AT[(i*MATRIX_DIMENSION_Y)+j] = data[(j*MATRIX_DIMENSION_X) + i];

            }

        }
        return AT;
    }

    void ftranspose()
    {
        int tX = MATRIX_DIMENSION_X;
        MATRIX_DIMENSION_X = MATRIX_DIMENSION_Y;
        MATRIX_DIMENSION_Y = tX;
    }

    double* address(const int index)
    {
        if(index < 0 || index > MATRIX_END_INDEX)
        {
            return &data[0];
        }

        return &data[index];
    }

    GEmatd operator *(const GEmatd other)
    {
        
        if(MATRIX_DIMENSION_X != other.MATRIX_DIMENSION_Y)
        {
            throw std::out_of_range("dimension mismatch multiplication");
        }
        GEmatd r(MATRIX_DIMENSION_Y,other.MATRIX_DIMENSION_X); //don't name things result
        
        
        double sum = 0;
        for(int i = 0; i < MATRIX_DIMENSION_Y; i++)
        {

            for(int j = 0; j < other.MATRIX_DIMENSION_X; j++)
            {
                sum = 0;
                for(int k = 0; k < MATRIX_DIMENSION_X; k++)
                {
                    sum += data[(i*MATRIX_DIMENSION_X) + k] * other.c((k*other.MATRIX_DIMENSION_X) + j);
                }

                r[(i*r.MATRIX_DIMENSION_X) + j] = sum;
            }

        }

        return r;

    }

    void multiply(const GEmatd other, GEmatd& r)
    {
        if(MATRIX_DIMENSION_X != other.MATRIX_DIMENSION_Y)
        {
            throw std::out_of_range("dimension mismatch multiplication");
        }
        r.resize(MATRIX_DIMENSION_Y, other.MATRIX_DIMENSION_X);

        double sum = 0;
        for(int i = 0; i < MATRIX_DIMENSION_Y; i++)
        {

            for(int j = 0; j < other.MATRIX_DIMENSION_X; j++)
            {
                sum = 0;
                for(int k = 0; k < MATRIX_DIMENSION_X; k++)
                {
                    sum += data[(i*MATRIX_DIMENSION_X) + k] * other.c((k*other.MATRIX_DIMENSION_X) + j);
                }

                r[(i*r.MATRIX_DIMENSION_X) + j] = sum;
            }

        }
    }

    GEmatd operator +(const GEmatd other)
    {
        if(MATRIX_DIMENSION_X != other.MATRIX_DIMENSION_X || MATRIX_DIMENSION_Y != other.MATRIX_DIMENSION_Y)
        {
            throw std::out_of_range("dimension mismatch");
        }

        GEmatd r(MATRIX_DIMENSION_X, MATRIX_DIMENSION_Y);

        for(int i = 0; i < MATRIX_DIMENSION_Y; i++)
        {
            for(int j = 0; j < MATRIX_DIMENSION_X; j++)
            {
                r.data[(i*MATRIX_DIMENSION_X) + j] = data[(i*MATRIX_DIMENSION_X) + j] + other.c((i*MATRIX_DIMENSION_X) + j);
            }
        }

        return r;

    }

    GEmatd operator+(const double c)
    {
        GEmatd r(MATRIX_DIMENSION_X, MATRIX_DIMENSION_Y);

        for(int i = 0; i < MATRIX_DIMENSION_Y; i++)
        {
            for(int j = 0; j < MATRIX_DIMENSION_X; j++)
            {
                r.data[(i*MATRIX_DIMENSION_X) + j] =  data[(i*MATRIX_DIMENSION_X) + j] + c;
            }
        }

        return r;
    }

    GEmatd operator-(const double c)
    {
        GEmatd r(MATRIX_DIMENSION_X, MATRIX_DIMENSION_Y);

        for(int i = 0; i < MATRIX_DIMENSION_Y; i++)
        {
            for(int j = 0; j < MATRIX_DIMENSION_X; j++)
            {
                r.data[(i*MATRIX_DIMENSION_X) + j] = data[(i*MATRIX_DIMENSION_X) + j] - c;
            }
        }

        return r;
    }

    GEmatd operator-=(const GEmatd c)
    {
        if(c.MATRIX_END_INDEX > c.MATRIX_DIMENSION_Y < MATRIX_DIMENSION_Y)
        {
            throw std::range_error("bad dims in subtraciton");
        }

        for(int i = 0; i < MATRIX_DIMENSION_Y; i++)
        {
            for(int j = 0; j < MATRIX_DIMENSION_X; j++)
            {
                data[(i*MATRIX_DIMENSION_X) + j] = c.data[(i*c.MATRIX_DIMENSION_X) + j];
            }

        }
    }

    GEmatd operator/(const double c)
    {
        GEmatd r(MATRIX_DIMENSION_X, MATRIX_DIMENSION_Y);

        for(int i = 0; i < MATRIX_DIMENSION_Y; i++)
        {
            for(int j = 0; j < MATRIX_DIMENSION_X; j++)
            {
                r.data[(i*MATRIX_DIMENSION_X) + j] = data[(i*MATRIX_DIMENSION_X) + j]/c;
            }
        }

        return r;
    }

    GEmatd operator -(const GEmatd other)
    {
        if(MATRIX_DIMENSION_X != other.MATRIX_DIMENSION_X || MATRIX_DIMENSION_Y != other.MATRIX_DIMENSION_Y)
        {
            throw std::out_of_range("dimension mismatch");
        }

        GEmatd r(MATRIX_DIMENSION_X, MATRIX_DIMENSION_Y);

        for(int i = 0; i < MATRIX_DIMENSION_Y; i++)
        {
            for(int j = 0; j < MATRIX_DIMENSION_X; j++)
            {
                r.data[(i*MATRIX_DIMENSION_X) + j] = data[(i*MATRIX_DIMENSION_X) + j] - other.c((i*MATRIX_DIMENSION_X) + j);
            }
        }

        return r;
    }

    void divideBy(const double c)
    {

        for(int i = 0; i < MATRIX_DIMENSION_Y; i++)
        {
            for(int j = 0; j < MATRIX_DIMENSION_X; j++)
            {
                data[(i*MATRIX_DIMENSION_X) + j] /= c;
            }
        }
    }

    void mulBy(const double c)
    {
        for(int i = 0; i < MATRIX_DIMENSION_Y; i++)
        {
            for(int j = 0; j < MATRIX_DIMENSION_X; j++)
            {
                data[(i*MATRIX_DIMENSION_X) + j] *= c;
            }
        }
    }

    void subtractBy(const double c)
    {
        for(int i = 0; i < MATRIX_DIMENSION_Y; i++)
        {
            for(int j = 0; j < MATRIX_DIMENSION_X; j++)
            {
                data[(i*MATRIX_DIMENSION_X) + j] -= c;
            }
        }
    }

    void subtractBy(const GEmatd& c)
    {
        for(int i = 0; i < MATRIX_DIMENSION_Y; i++)
        {
            for(int j = 0; j < MATRIX_DIMENSION_X; j++)
            {
                data[(i*MATRIX_DIMENSION_X) + j] -= c.c((i*MATRIX_DIMENSION_X) + j);
            }
        }
    }

    void subtractBy(const GEspan rows, const GEspan cols, GEmatd c)
    {


        for(int i = rows.from-1, k = 0; i < rows.to; i++, k++)
        {
            for(int j = cols.from-1, m = 0; j < cols.to; j++, m++)
            {
                data[(i*MATRIX_DIMENSION_X) + j] -= c[(k*c.MATRIX_DIMENSION_X) + j];
            }
        }
    }

    GEmatd sqr()
    {
        GEmatd result(MATRIX_DIMENSION_X, MATRIX_DIMENSION_Y);

        for(int i = 0; i < MATRIX_DIMENSION_Y; i++)
        {
            for(int j = 0; j < MATRIX_DIMENSION_X; j++)
            {
                result.data[(i*MATRIX_DIMENSION_X) + j] = sqrt(data[(i*MATRIX_DIMENSION_X) + j]);
            }
        }

        return result;
    }

    GEmatd abs()
    {
        GEmatd absoluteReturnValue(MATRIX_DIMENSION_X, MATRIX_DIMENSION_Y);
        memcpy(absoluteReturnValue.data, data, sizeof(double)*MATRIX_DIMENSION_X*MATRIX_DIMENSION_Y);

        for(int i = 0; i < MATRIX_DIMENSION_Y; i++)
        {
            for(int j = 0; j < MATRIX_DIMENSION_X; j++)
            {
                absoluteReturnValue.data[(i*MATRIX_DIMENSION_X) + j] = std::abs(absoluteReturnValue.data[(i*MATRIX_DIMENSION_X) + j]);
            }
        }
        return absoluteReturnValue;
    }

    double sum()
    {
        double s = 0;
        for(int i = 0; i < MATRIX_DIMENSION_Y; i++)
        {
            for(int j = 0; j < MATRIX_DIMENSION_X; j++)
            {
                s += data[(i*MATRIX_DIMENSION_X) + j];
            }
        }
        return s;

    }

    double trace()
    {
        int dig = 0;
        double tsum = 0;
        for(int i = 0; i < MATRIX_DIMENSION_X; i++)
        {

            tsum += data[(dig*MATRIX_DIMENSION_X) + i];
            dig++;
        }
        return tsum;
    }

    double maxCoeff()
    {
        double s = data[0];
        for(int i = 0; i < MATRIX_DIMENSION_Y; i++)
        {
            for(int j = 0; j < MATRIX_DIMENSION_X; j++)
            {
                s = (data[(i*MATRIX_DIMENSION_X) + j] > s) ? data[(i*MATRIX_DIMENSION_X) + j] : s;
            }
        }
        return s;

    }

    double minCoeff()
    {
        double s = data[0];
        for(int i = 0; i < MATRIX_DIMENSION_Y; i++)
        {
            for(int j = 0; j < MATRIX_DIMENSION_X; j++)
            {
                s = (data[(i*MATRIX_DIMENSION_X) + j] < s) ? data[(i*MATRIX_DIMENSION_X) + j] : s;
            }
        }
        return s;
    }

     void setZero()
    {
        for(int i = 0; i < MATRIX_DIMENSION_Y; i++)
        {
            for(int j = 0; j < MATRIX_DIMENSION_X; j++)
            {
                data[(i*MATRIX_DIMENSION_X) + j] = 0;
            }
        }
    }

    bool isZero()
    {
        for(int i = 0; i < MATRIX_DIMENSION_Y; i++)
        {

            for(int j = 0; j < MATRIX_DIMENSION_Y; j++)
            {
                if(data[(i*MATRIX_DIMENSION_X) + j] != 0)
                {
                    return false;
                }
            }

        }

        return true;
    }

    void identity()
    {
        int vdig = 0;
        int hdig = 0;
        for(int i = 0; i < MATRIX_DIMENSION_Y; i++)
        {
            for(int j = 0; j < MATRIX_DIMENSION_X; j++)
            {
                if(i == vdig && j == hdig)
                {
                    data[(i*MATRIX_DIMENSION_X) + j] = 1;
                    vdig++;
                    hdig++;
                }else
                {
                    data[(i*MATRIX_DIMENSION_X) + j] = 0;
                }   
                
            }
        }
    }

    GEmatd subMatrix(GEspan rows, GEspan columns)
    {
        int dr = (rows.to-rows.from)+1;
        int dc = (columns.to-columns.from)+1;
        GEmatd subResult(dc, dr);

        for(int i = rows.from-1, k = 0; i < rows.to; i++, k++)
        {
            for(int j = columns.from-1, l = 0; j < columns.to; j++, l++)
            {
                subResult[(k * dc) + l] = data[(i*MATRIX_DIMENSION_X) + j];
            }
        }

        return subResult;
    }

    void subMatrix(GEspan rows, GEspan columns, GEmatd& subResult)
    {
        int dr = (rows.to-rows.from)+1;
        int dc = (columns.to-columns.from)+1;

        if(subResult.MATRIX_END_INDEX+1 < dr*dc)
        {
            throw std::range_error("Incorrect Dimensional Sub-Matrix");
        }

        subResult.resize(dr, dc);

        for(int i = rows.from-1, k = 0; i < rows.to; i++, k++)
        {
            for(int j = columns.from-1, l = 0; j < columns.to; j++, l++)
            {
                subResult[(k * dc) + l] = data[(i*MATRIX_DIMENSION_X) + j];
            }
        }

    }

    void subMatrix(GEspan rows, GEmatd& subResult)
    {
        int dc = (rows.to-rows.from)+1;

        // if(subResult.MATRIX_DIMENSION_Y < dc)
        // {
        //     throw std::range_error("Incorrect Dimensional Sub-Matrix");
        // }

        for(int i = rows.from-1, k = 0; i < rows.to; i++, k++)
        {
            subResult[k] = data[(i*MATRIX_DIMENSION_X)];
        }

        subResult.resize(dc, 1);

    }

    void setSubMatrix(GEspan rows, GEspan columns, GEmatd A)
    {
        int m = (rows.to-rows.from)+1;
        int n = (columns.to-columns.from)+1;

        if(A.MATRIX_DIMENSION_Y != m && A.MATRIX_DIMENSION_X != n)
        {

            return;

        }

        for(int i = rows.from-1, k = 0; i < rows.to; i++, k++)
        {
            for(int j = columns.from-1, l = 0; j < columns.to; j++, l++)
            {
                data[(i*MATRIX_DIMENSION_X) + j] = A[(k * n) + l];
            }
        }

    }
    void subtractSubMatrix(GEspan rows, GEspan columns, GEmatd other)
    {

        
        int dr = (rows.to-rows.from)+1;
        int dc = (columns.to-columns.from)+1;

        if(MATRIX_END_INDEX+1 < dr*dc)
        {
            throw std::range_error("Incorrect Dimensional Sub-Matrix");
        }

        for(int i = rows.from-1, k = 0; i < rows.to; i++, k++)
        {
            for(int j = columns.from-1, l = 0; j < columns.to; j++, l++)
            {
                data[(i*MATRIX_DIMENSION_X) + j] -= other[(k * other.MATRIX_DIMENSION_X) + l];
            }
        }
    }

    void resize(GEspan r, GEspan c)
    {
        int rows = (r.to-r.from)+1;
        int columns = (c.to-c.from)+1;

        if(rows < 0 || columns < 0 || rows > 100000 || columns > 100000)
        {
            throw std::range_error("Incorrect spans in resize");
        }

        if(rows == MATRIX_DIMENSION_Y && rows == MATRIX_DIMENSION_X)
        {
            return;
        }

        if(rows * columns < (MATRIX_END_INDEX+1))
        {
            MATRIX_DIMENSION_X = columns;
            MATRIX_DIMENSION_Y = rows;
            MATRIX_SIZE = columns*rows;
        }else
        {
            double OldMatrixSize = MATRIX_SIZE*sizeof(double);
            MATRIX_SIZE = rows*columns;
            MATRIX_END_INDEX = MATRIX_SIZE-1;
            MATRIX_DIMENSION_X = columns;
            MATRIX_DIMENSION_Y = rows;

            double* memeBUffer = new double[MATRIX_SIZE];
            memcpy(memeBUffer, data, OldMatrixSize);
            if(data != nullptr)
            {
                delete[] data;
            }
        }

        


    }

    void resize(int rows, int columns)
    {

        if(rows == MATRIX_DIMENSION_Y && rows == MATRIX_DIMENSION_X)
        {
            return;
        }

        if(rows < 0 || columns < 0 || rows > 100000 || columns > 100000)
        {
            throw std::range_error("Incorrect spans in resize");
        }

        if((rows * columns) <= (MATRIX_END_INDEX+1))
        {
            MATRIX_DIMENSION_X = columns;
            MATRIX_DIMENSION_Y = rows;
            MATRIX_SIZE = columns*rows;
        }else
        {
            double OldMatrixSize = MATRIX_SIZE*sizeof(double);  //error where old matrix size is to much
            MATRIX_SIZE = rows*columns;
            MATRIX_END_INDEX = MATRIX_SIZE-1;
            MATRIX_DIMENSION_X = columns;
            MATRIX_DIMENSION_Y = rows;

            double* memBuffer = new double[MATRIX_SIZE];
            memcpy(memBuffer, data, OldMatrixSize);
            if(data != nullptr && data != memBuffer)
            {
                delete[] data;
                data = nullptr;
            }

            data = memBuffer;
        }
    }

    ~GEmatd()
    {
        if(data != nullptr && copy == false)
        {
            delete[] data;
            data = nullptr;
        }
    
    }

    #pragma endregion

    #pragma region Questionable

    GEmatd subColumnVector(int a, int b)
    {
        GEmatd subData(1, (b-a));
        memcpy(subData.data, address(a), sizeof(double)*(b-a));
        return subData;
    }

    GEmatd subRowVector(int a, int b)
    {
        GEmatd subData((b-a), 1);
        memcpy(subData.data, address(a), sizeof(double)*(b-a));
        return subData;
    }

    GEmatd prependColumnVector(double value)
    {
        GEmatd item(MATRIX_DIMENSION_X, MATRIX_DIMENSION_Y+1);
        item.data[0] = value;
        memcpy(item.data+1, data, sizeof(double) * MATRIX_SIZE);
        return item;

    }
    #pragma endregion
   

};




GEmatd operator-(const double a, GEmatd A)
{
    GEmatd result(A.MATRIX_DIMENSION_X, A.MATRIX_DIMENSION_Y);

        for(int i = 0; i < A.MATRIX_DIMENSION_Y; i++)
        {
            for(int j = 0; j < A.MATRIX_DIMENSION_X; j++)
            {
                result.data[(i*A.MATRIX_DIMENSION_X) + j] = A.data[(i*A.MATRIX_DIMENSION_X) + j] - a;
            }
        }

        return result;
}

void meq(const GEmatd t, const GEmatd other, GEmatd& r)
{   
    if(t.MATRIX_DIMENSION_X != other.MATRIX_DIMENSION_Y)
    {
        throw std::out_of_range("dimension mismatch multiplication");
    }

    if(r.MATRIX_DIMENSION_X != t.MATRIX_DIMENSION_Y || r.MATRIX_DIMENSION_Y != other.MATRIX_DIMENSION_X)
    {
        r.resize(t.MATRIX_DIMENSION_Y,other.MATRIX_DIMENSION_X);
    }
    double sum = 0;
    for(int i = 0; i < t.MATRIX_DIMENSION_Y; i++)
    {

        for(int j = 0; j < other.MATRIX_DIMENSION_X; j++)
        {
            sum = 0;
            for(int k = 0; k < t.MATRIX_DIMENSION_X; k++)
            {
                sum += t.data[(i*t.MATRIX_DIMENSION_X) + k] * other.c((k*other.MATRIX_DIMENSION_X) + j);
            }

            r[(i*r.MATRIX_DIMENSION_X) + j] = sum;
        }

    }
}

int lowerBandWidth(const GEmatd M)
{
    int lowerBandIndex = -1;
    int m = M.MATRIX_DIMENSION_Y;
    int n = M.MATRIX_DIMENSION_X;
    
    for(int i = 0; i < m; i++)
    {
        if(lowerBandIndex == -1 && M.c((i*n)) == 0)
        {
            lowerBandIndex = i;
        }

        if(M.c((i*n)) != 0)
        {
            lowerBandIndex = -1;
        }


        
    }

    if(lowerBandIndex != -1)
    {
        for(int i = 0; i < n; i++)
        {
            for(int j = lowerBandIndex + i; j < m; j++)
            {
                if(M.c((j*n) + i) != 0)
                {
                    return -1;
                }
            }
        }
    }


    return lowerBandIndex-1;
}
int upperBandWidth(const GEmatd M)
{
    int upperBandIndex = -1;
    int m = M.MATRIX_DIMENSION_Y;
    int n = M.MATRIX_DIMENSION_X;

    for(int i = 0; i < n; i++)
    {
        if(upperBandIndex == -1 && M.c(i) == 0)
        {
            upperBandIndex = i;
        }
        if(M.c(i) != 0)
        {
            upperBandIndex = -1;
        }
    }

    if(upperBandIndex != -1)
    {
        for(int i = 0; i < m; i++)
        {   
            for(int j = upperBandIndex+(i+1); j < n; j++)
            {
                if(M.c((i*n) + j) != 0)
                {
                    return -1;
                }
            }
        }
    }


    return upperBandIndex-1;


}

void UpperTriangularMultiplication(GEmatd A, GEmatd B,  GEmatd& r)
{

    if(r.MATRIX_DIMENSION_X != A.MATRIX_DIMENSION_Y || r.MATRIX_DIMENSION_Y != B.MATRIX_DIMENSION_X)
    {
        r.resize(A.MATRIX_DIMENSION_Y,B.MATRIX_DIMENSION_X);
    }
    double sum = 0;
    for(int i = 0; i < B.MATRIX_DIMENSION_X;  i++)
    {
        for(int j = i; j < B.MATRIX_DIMENSION_X; j++)
        {
            sum = 0;
            for(int k = i; k <  j; k++)
            {
                sum += A[(i*A.MATRIX_DIMENSION_X) + k]*B[(k*B.MATRIX_DIMENSION_X) + j];
                // 1st row *  1st column : 1
                // 
            }

            r[(i*r.MATRIX_DIMENSION_X)+j] = sum;
        }
    }

}


GEmatd PermutationOfRow(GEmatd I, GEmatd V)
{   
    int VectorLength = V.MATRIX_SIZE;
    int m = I.MATRIX_DIMENSION_Y;
    int n = I.MATRIX_DIMENSION_X;

    GEmatd P(I.MATRIX_DIMENSION_X, I.MATRIX_DIMENSION_Y);

    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {

            P[(i*n) + j] = I[((V[i]-1)*n) + j];


        }
    }

    return P;
        
}
GEmatd PermutationOfColumn(GEmatd I, GEmatd V)
{

    int VectorLength = V.MATRIX_SIZE;
    if(VectorLength != I.MATRIX_DIMENSION_X)
    {
        //bad value
    }
    int m = I.MATRIX_DIMENSION_Y;
    int n = I.MATRIX_DIMENSION_X;

    GEmatd P(I.MATRIX_DIMENSION_X, I.MATRIX_DIMENSION_Y);

    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {

            P[(i*n) + j] = I[(i*n) + (V[j]-1)];
        }
    }


    return P;



}
struct IntegerOctave
{
    char i,j,k;

    IntegerOctave(int p_i, int p_j, char p_k) : i(p_i), j(p_j), k('n')
    {

    }
    IntegerOctave(char p_i, int p_j, int p_k) : i('n'), j(p_j), k(p_k)
    {

    }
    IntegerOctave(int p_i, char p_j, int p_k) : i(p_i), j('n'), k(p_k)
    {

    }
    IntegerOctave(char p_i, char p_j, int p_k) : i('n'), j('n'), k(p_k)
    {

    }
    IntegerOctave(int p_i, int p_j, int p_k) : i(p_i), j(p_j), k(p_k)
    {

    }
};
GEmatd OctaveVector(IntegerOctave O, int n)
{

    GEmatd Octave(n);

    if(O.i == 'n')
    {   
        int initalValue = n;
        Octave[0] = initalValue;
        for(int i = 1; i < n; i++)
        {
            initalValue += O.j*O.k;
            Octave[i] = initalValue;
        }
    }else
    if(O.k == 'n')
    {
        for(int i = 0; i < n; i++)
        {
            Octave[i] = O.i + O.j*i;
        }
    }else
    {
        int initalValue = O.i;
        Octave[0] = initalValue;
        for(int i = 1; i < n; i++)
        {
            initalValue += O.j*O.k;
            Octave[i] = initalValue;
        }
    }
    return Octave;
}
GEmatd Combination(GEmatd I, GEmatd v, GEmatd w)
{
    int m = I.MATRIX_DIMENSION_Y;
    int n = I.MATRIX_DIMENSION_X;
    GEmatd R(n,m);

    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {

            R[(i*n) + j] = I[((v[i]-1)*n) + (w[j]-1)];

        }
    }


}


//permutation of columns across a matrix and permutations

double dot(GEmatd A, GEmatd B)
{
    if(A.MATRIX_SIZE != B.MATRIX_SIZE)
    {
        throw std::out_of_range("dimension mismatch");
    }

    double dot = 0;

    for(int i = 0; i < A.MATRIX_SIZE; i++)
    {
        dot += A[i] * B[i];
    }


    return dot;

}

GEmatd eyed(const int dim)
{
    GEmatd result(dim, dim);
    int vdig = 0;
    int hdig = 0;
    for(int i = 0; i < result.MATRIX_DIMENSION_Y; i++)
    {
        for(int j = 0; j < result.MATRIX_DIMENSION_X; j++)
        {
            if(i == vdig && j == hdig)
            {
                result.data[(i*result.MATRIX_DIMENSION_X) + j] = 1;
                vdig++;
                hdig++;
            }else
            {
                result.data[(i*result.MATRIX_DIMENSION_X) + j] = 0;
            }   
            
        }
    }

    return result;

}

void h_hol(GEmatd& x, double& beta)
{
    double alpha = x[0];
    x[0] = 0;
    double s = dot(x,x);
    if(s == 0)
    {
        beta = 0;
    }else
    {
        double t = sqrt(pow(alpha,2) + s);
        if(alpha <= 0)
        {
            x[0] = alpha - t;
        }else
        {
            x[0] = -s/(alpha+t);
        }

        double v0s = pow(x[0],2);

        beta = (2 * v0s)/(s + v0s);
        x.divideBy(x[0]);
    }

}

void house(GEmatd& v, double& beta)
{

    //house holder vector = x1 - |x||_2 
    //where ||x||2 is the 2-norm of vector x

    int m = v.MATRIX_SIZE;

    double x1 = v(0, 0);
    v[0] = 0;
    double sigma = dot(v,v);

    if(sigma == 0 && x1 >= 0)
    {
        beta = 0;
    }else if(sigma == 0 && x1 < 0)
    {
        beta = -2;
    }else
    {
        double mu = sqrt(pow(x1,2) + sigma);
        if(x1 <= 0)
        {
            v[0] = x1 - mu;
        }else
        {
            v[0] = -sigma/(x1 + mu);
        }

        double v0s = pow(v[0],2);
        beta = (2*v0s)/(sigma + v0s);
        v.divideBy(v[0]);

    }
}


void applyhouseholder(GEmatd A)
{
    
    int m = A.MATRIX_DIMENSION_Y;
    int n = A.MATRIX_DIMENSION_X;

    double beta;
    GEmatd vt(1, m);

    GEmatd matrixBuffer(n,m);
    GEmatd matrixBuffer2(n,m);
    GEmatd matrixBuffer3(n,m);

    

    for(int j = 1; j < m; j++)
    {

        A.subMatrix({j, m}, j, vt);
        vt.display();
        h_hol(vt, beta);
        // vt.display();

        A.subMatrix({j,m}, {j,n}, matrixBuffer);
        GEmatd vtemp = vt;
        vtemp.ftranspose();
        meq(vt, vtemp, matrixBuffer2);
        matrixBuffer2.display();

        meq(matrixBuffer2, matrixBuffer, matrixBuffer3);
        matrixBuffer3.display();
        matrixBuffer3.mulBy(beta);
        matrixBuffer3.display();
        
        A.subtractSubMatrix({j,m},{j,n}, matrixBuffer3);

        A.display();
        vt.subMatrix({2,m-j+1},matrixBuffer);
        A.setSubMatrix({j+1,m},{j}, matrixBuffer);
        A.display();
    }
}

void testHouseholder(GEmatd A)
{
    int m = A.MATRIX_DIMENSION_Y;
    int n = A.MATRIX_DIMENSION_X;
    GEmatd matrixBuffer(n,m);
    GEmatd matrixBuffer2(n,m);
    double beta;

    GEmatd vt(1,m);
    GEmatd vs(1,m);

    int j = 1;
    
    A.subMatrix({j, m}, j, vt);
    vt.display();

    house(vt, beta);

    vt.display();
    vt.subMatrix({2, m-j+1}, vs);

    vt.display();
    matrixBuffer.resize({j,m}, {j,n});
    A.subMatrix({j,m}, {j,n}, matrixBuffer);
    matrixBuffer.display();
    A.subMatrix({j,m}, {j,n}, matrixBuffer2);
    vt.ftranspose();
    vt.display();

    vt.multiply(matrixBuffer, matrixBuffer2);

    matrixBuffer2.display();
    vt.ftranspose();
    vt.mulBy(beta);
    vt.display();
    matrixBuffer2.display();
    
    GEmatd forced = vt * matrixBuffer2;
    forced.display();
    A.subtractBy({j,m}, {j,n}, forced);
    A.display();
    A.setSubMatrix({j+1, m},{j}, vs);

    A.display();

    int e = 0;

}

void pyqr(GEmatd A)
{
    int m = A.MATRIX_DIMENSION_X;
    int n = A.MATRIX_DIMENSION_Y;
    double beta;
    GEmatd vt(1, n);
    GEmatd mB(m,n);
    GEmatd i(m,m);


    for(int j = 1; j < 2; j++)
    {
        A.subMatrix({j,m}, {j}, vt);
        house(vt, beta);
        vt.display();
        printf("%f\n", beta);

        
        GEmatd out = vt;
        out.ftranspose();
        vt.multiply(out, mB);
        mB.mulBy(beta);

        i.resize(m,m);
        i.identity();

        i.subtractBy(mB);



    }

}




#endif