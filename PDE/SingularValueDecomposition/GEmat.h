#ifndef GEMat_H_D
#define GEMAT_H_D
#include <initializer_list>
#include <memory>
#include <exception>
#include <math.h>
#include <limits>

struct GEspan
{
    int from;
    int to;

    GEspan(int j)
    {
        from = j;
        to = j;
    }

    GEspan(int i, int k)
    {
        from = i;
        to = k;
    }
};


struct GEmat
{
    float* data;
    bool copy;
    int MATRIX_DIMENSION_X;
    int MATRIX_DIMENSION_Y;
    int MATRIX_END_INDEX;
    int MATRIX_SIZE;

    GEmat(int x, int y) : data(nullptr), MATRIX_DIMENSION_X(0), MATRIX_DIMENSION_Y(0), MATRIX_END_INDEX(0), MATRIX_SIZE(0), copy(false)
    {
        MATRIX_SIZE = x*y;
        data = new float[MATRIX_SIZE];
        MATRIX_DIMENSION_X = x;
        MATRIX_DIMENSION_Y = y;
        MATRIX_END_INDEX = MATRIX_SIZE-1;
    }

    GEmat(const GEmat &c) : data(c.data), MATRIX_DIMENSION_X(c.MATRIX_DIMENSION_X), MATRIX_DIMENSION_Y(c.MATRIX_DIMENSION_Y), MATRIX_END_INDEX(c.MATRIX_END_INDEX), MATRIX_SIZE(c.MATRIX_SIZE), copy(true)
    {

    }

    float& operator[](const int index)
    {
        if(index < 0 || index > MATRIX_END_INDEX)
        {
            return data[0];
        }

        return data[index];
    }

    const float c(const int index) const
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

    void operator=(std::initializer_list<float> L)
    {
        //memcpy(data, L.begin(), L.size()*sizeof(float));

        for(int i = 0; i < L.size(); i++)
        {
            data[i] = *(L.begin() + i);
        }
    }

    GEmat cpy()
    {
        GEmat result(MATRIX_DIMENSION_X, MATRIX_DIMENSION_Y);
        memcpy(result.data, data, sizeof(float)*MATRIX_SIZE);
        return result;
    }

    const float operator()(int i, int j)
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
                printf("%f ", data[ij]);
            }
            printf("|\n");
        }
    }

    GEmat transpose()
    {
        GEmat AT(MATRIX_DIMENSION_Y, MATRIX_DIMENSION_X);
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

    float* address(const int index)
    {
        if(index < 0 || index > MATRIX_END_INDEX)
        {
            return &data[0];
        }

        return &data[index];
    }

    GEmat operator *(const GEmat other)
    {
        
        if(MATRIX_DIMENSION_X != other.MATRIX_DIMENSION_Y)
        {
            throw std::out_of_range("dimension mismatch multiplication");
        }
        GEmat r(MATRIX_DIMENSION_Y,other.MATRIX_DIMENSION_X); //don't name things result
        
        
        float sum = 0;
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

    void broken()
    {

        GEmat item(1,3);

        int i = 1;
        i = 1;
        i = 1;
        i = 1;
        i = 1;
    }

    void multiply(const GEmat other, GEmat& r)
    {
        if(MATRIX_DIMENSION_X != other.MATRIX_DIMENSION_Y)
        {
            throw std::out_of_range("dimension mismatch multiplication");
        }
        r.resize(MATRIX_DIMENSION_Y, other.MATRIX_DIMENSION_X);

        float sum = 0;
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

    // GEmat operator *(const float c){

    //     GEmat result(MATRIX_DIMENSION_X, MATRIX_DIMENSION_Y);

    //     for(int i = 0; i < MATRIX_DIMENSION_Y; i++)
    //     {
    //         for(int j = 0; j < MATRIX_DIMENSION_X; j++)
    //         {
    //             result.data[(i*MATRIX_DIMENSION_X) + j] = data[(i*MATRIX_DIMENSION_X) + j]*c;
    //         }
    //     }

    //     return result;
    // }

    GEmat operator +(const GEmat other)
    {
        if(MATRIX_DIMENSION_X != other.MATRIX_DIMENSION_X || MATRIX_DIMENSION_Y != other.MATRIX_DIMENSION_Y)
        {
            throw std::out_of_range("dimension mismatch");
        }

        GEmat r(MATRIX_DIMENSION_X, MATRIX_DIMENSION_Y);

        for(int i = 0; i < MATRIX_DIMENSION_Y; i++)
        {
            for(int j = 0; j < MATRIX_DIMENSION_X; j++)
            {
                r.data[(i*MATRIX_DIMENSION_X) + j] = data[(i*MATRIX_DIMENSION_X) + j] + other.c((i*MATRIX_DIMENSION_X) + j);
            }
        }

        return r;

    }

    GEmat operator+(const float c)
    {
        GEmat r(MATRIX_DIMENSION_X, MATRIX_DIMENSION_Y);

        for(int i = 0; i < MATRIX_DIMENSION_Y; i++)
        {
            for(int j = 0; j < MATRIX_DIMENSION_X; j++)
            {
                r.data[(i*MATRIX_DIMENSION_X) + j] =  data[(i*MATRIX_DIMENSION_X) + j] + c;
            }
        }

        return r;
    }

    GEmat operator-(const float c)
    {
        GEmat r(MATRIX_DIMENSION_X, MATRIX_DIMENSION_Y);

        for(int i = 0; i < MATRIX_DIMENSION_Y; i++)
        {
            for(int j = 0; j < MATRIX_DIMENSION_X; j++)
            {
                r.data[(i*MATRIX_DIMENSION_X) + j] = data[(i*MATRIX_DIMENSION_X) + j] - c;
            }
        }

        return r;
    }

    GEmat operator/(const float c)
    {
        GEmat r(MATRIX_DIMENSION_X, MATRIX_DIMENSION_Y);

        for(int i = 0; i < MATRIX_DIMENSION_Y; i++)
        {
            for(int j = 0; j < MATRIX_DIMENSION_X; j++)
            {
                r.data[(i*MATRIX_DIMENSION_X) + j] = data[(i*MATRIX_DIMENSION_X) + j]/c;
            }
        }

        return r;
    }

    GEmat operator -(const GEmat other)
    {
        if(MATRIX_DIMENSION_X != other.MATRIX_DIMENSION_X || MATRIX_DIMENSION_Y != other.MATRIX_DIMENSION_Y)
        {
            throw std::out_of_range("dimension mismatch");
        }

        GEmat r(MATRIX_DIMENSION_X, MATRIX_DIMENSION_Y);

        for(int i = 0; i < MATRIX_DIMENSION_Y; i++)
        {
            for(int j = 0; j < MATRIX_DIMENSION_X; j++)
            {
                r.data[(i*MATRIX_DIMENSION_X) + j] = data[(i*MATRIX_DIMENSION_X) + j] - other.c((i*MATRIX_DIMENSION_X) + j);
            }
        }

        return r;
    }

    void divideBy(const float c)
    {

        for(int i = 0; i < MATRIX_DIMENSION_Y; i++)
        {
            for(int j = 0; j < MATRIX_DIMENSION_X; j++)
            {
                data[(i*MATRIX_DIMENSION_X) + j] /= c;
            }
        }
    }

    void mulBy(const float c)
    {
        for(int i = 0; i < MATRIX_DIMENSION_Y; i++)
        {
            for(int j = 0; j < MATRIX_DIMENSION_X; j++)
            {
                data[(i*MATRIX_DIMENSION_X) + j] *= c;
            }
        }
    }

    void subtractBy(const float c)
    {
        for(int i = 0; i < MATRIX_DIMENSION_Y; i++)
        {
            for(int j = 0; j < MATRIX_DIMENSION_X; j++)
            {
                data[(i*MATRIX_DIMENSION_X) + j] -= c;
            }
        }
    }

    void subtractBy(const GEmat& c)
    {
        for(int i = 0; i < MATRIX_DIMENSION_Y; i++)
        {
            for(int j = 0; j < MATRIX_DIMENSION_X; j++)
            {
                data[(i*MATRIX_DIMENSION_X) + j] -= c.c((i*MATRIX_DIMENSION_X) + j);
            }
        }
    }

    void subtractBy(const GEspan rows, const GEspan cols, GEmat c)
    {


        for(int i = rows.from-1, k = 0; i < rows.to; i++, k++)
        {
            for(int j = cols.from-1, m = 0; j < cols.to; j++, m++)
            {
                data[(i*MATRIX_DIMENSION_X) + j] -= c[(k*c.MATRIX_DIMENSION_X) + j];
            }
        }
    }

    GEmat sqr()
    {
        GEmat result(MATRIX_DIMENSION_X, MATRIX_DIMENSION_Y);

        for(int i = 0; i < MATRIX_DIMENSION_Y; i++)
        {
            for(int j = 0; j < MATRIX_DIMENSION_X; j++)
            {
                result.data[(i*MATRIX_DIMENSION_X) + j] = sqrt(data[(i*MATRIX_DIMENSION_X) + j]);
            }
        }

        return result;
    }

    GEmat abs()
    {
        GEmat absoluteReturnValue(MATRIX_DIMENSION_X, MATRIX_DIMENSION_Y);
        memcpy(absoluteReturnValue.data, data, sizeof(float)*MATRIX_DIMENSION_X*MATRIX_DIMENSION_Y);

        for(int i = 0; i < MATRIX_DIMENSION_Y; i++)
        {
            for(int j = 0; j < MATRIX_DIMENSION_X; j++)
            {
                absoluteReturnValue.data[(i*MATRIX_DIMENSION_X) + j] = std::abs(absoluteReturnValue.data[(i*MATRIX_DIMENSION_X) + j]);
            }
        }
        return absoluteReturnValue;
    }

    float sum()
    {
        float s = 0;
        for(int i = 0; i < MATRIX_DIMENSION_Y; i++)
        {
            for(int j = 0; j < MATRIX_DIMENSION_X; j++)
            {
                s += data[(i*MATRIX_DIMENSION_X) + j];
            }
        }
        return s;

    }

    float trace()
    {
        int dig = 0;
        float tsum = 0;
        for(int i = 0; i < MATRIX_DIMENSION_X; i++)
        {

            tsum += data[(dig*MATRIX_DIMENSION_X) + i];
            dig++;
        }
        return tsum;
    }

    float maxCoeff()
    {
        float s = data[0];
        for(int i = 0; i < MATRIX_DIMENSION_Y; i++)
        {
            for(int j = 0; j < MATRIX_DIMENSION_X; j++)
            {
                s = (data[(i*MATRIX_DIMENSION_X) + j] > s) ? data[(i*MATRIX_DIMENSION_X) + j] : s;
            }
        }
        return s;

    }

    float minCoeff()
    {
        float s = data[0];
        for(int i = 0; i < MATRIX_DIMENSION_Y; i++)
        {
            for(int j = 0; j < MATRIX_DIMENSION_X; j++)
            {
                s = (data[(i*MATRIX_DIMENSION_X) + j] < s) ? data[(i*MATRIX_DIMENSION_X) + j] : s;
            }
        }
        return s;
    }

    GEmat subColumnVector(int a, int b)
    {
        GEmat subData(1, (b-a));
        memcpy(subData.data, address(a), sizeof(float)*(b-a));
        return subData;
    }

    GEmat subRowVector(int a, int b)
    {
        GEmat subData((b-a), 1);
        memcpy(subData.data, address(a), sizeof(float)*(b-a));
        return subData;
    }

    GEmat prependColumnVector(float value)
    {
        GEmat item(MATRIX_DIMENSION_X, MATRIX_DIMENSION_Y+1);
        item.data[0] = value;
        memcpy(item.data+1, data, sizeof(float) * MATRIX_SIZE);
        return item;

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

    GEmat subMatrix(GEspan rows, GEspan columns)
    {
        int dr = (rows.to-rows.from)+1;
        int dc = (columns.to-columns.from)+1;
        GEmat subResult(dc, dr);

        for(int i = rows.from-1, k = 0; i < rows.to; i++, k++)
        {
            for(int j = columns.from-1, l = 0; j < columns.to; j++, l++)
            {
                subResult[(k * dc) + l] = data[(i*MATRIX_DIMENSION_X) + j];
            }
        }

        return subResult;
    }

    void subMatrix(GEspan rows, GEspan columns, GEmat& subResult)
    {
        

        int dr = (rows.to-rows.from)+1;
        int dc = (columns.to-columns.from)+1;

        if(subResult.MATRIX_DIMENSION_Y < dr || subResult.MATRIX_DIMENSION_X < dc)
        {
            throw std::range_error("Incorrect Dimensional Sub-Matrix");
        }

        for(int i = rows.from-1, k = 0; i < rows.to; i++, k++)
        {
            for(int j = columns.from-1, l = 0; j < columns.to; j++, l++)
            {
                subResult[(k * dc) + l] = data[(i*MATRIX_DIMENSION_X) + j];
            }
        }

    }

    void subMatrix(GEspan rows, GEmat& subResult)
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


    void setSubMatrix(GEspan rows, GEspan columns, GEmat A)
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
    void subtractSubMatrix(GEspan rows, GEspan columns, GEmat A)
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
                data[(i*MATRIX_DIMENSION_X) + j] -= A[(k * n) + l];
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

        if(rows * columns < MATRIX_SIZE)
        {
            MATRIX_DIMENSION_X = columns;
            MATRIX_DIMENSION_Y = rows;
        }else
        {
            float OldMatrixSize = MATRIX_SIZE*sizeof(float);
            MATRIX_SIZE = rows*columns;
            MATRIX_END_INDEX = MATRIX_SIZE-1;
            MATRIX_DIMENSION_X = columns;
            MATRIX_DIMENSION_Y = rows;

            float* memeBUffer = new float[MATRIX_SIZE];
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

        if(rows * columns < MATRIX_SIZE)
        {
            MATRIX_DIMENSION_X = columns;
            MATRIX_DIMENSION_Y = rows;
        }else
        {
            float OldMatrixSize = MATRIX_SIZE*sizeof(float);
            MATRIX_SIZE = rows*columns;
            MATRIX_END_INDEX = MATRIX_SIZE-1;
            MATRIX_DIMENSION_X = columns;
            MATRIX_DIMENSION_Y = rows;

            float* memeBUffer = new float[MATRIX_SIZE];
            memcpy(memeBUffer, data, OldMatrixSize);
            if(data != nullptr)
            {
                delete[] data;
            }
        }
    }

    ~GEmat()
    {
        if(data != nullptr && copy == false)
        {
            delete[] data;
            data = nullptr;
        }
    
    }

};

GEmat operator-(const float a, GEmat A)
{
    GEmat result(A.MATRIX_DIMENSION_X, A.MATRIX_DIMENSION_Y);

        for(int i = 0; i < A.MATRIX_DIMENSION_Y; i++)
        {
            for(int j = 0; j < A.MATRIX_DIMENSION_X; j++)
            {
                result.data[(i*A.MATRIX_DIMENSION_X) + j] = A.data[(i*A.MATRIX_DIMENSION_X) + j] - a;
            }
        }

        return result;
}

// GEmat operator*(const float c, GEmat A){

//         GEmat result(A.MATRIX_DIMENSION_X, A.MATRIX_DIMENSION_Y);

//         for(int i = 0; i < A.MATRIX_DIMENSION_Y; i++)
//         {
//             for(int j = 0; j < A.MATRIX_DIMENSION_X; j++)
//             {
//                 result.data[(i*A.MATRIX_DIMENSION_X) + j] = A.data[(i*A.MATRIX_DIMENSION_X) + j]*c;
//             }
//         }

//         return result;
// }

float dot(GEmat A, GEmat B)
{
    if(A.MATRIX_SIZE != B.MATRIX_SIZE)
    {
        throw std::out_of_range("dimension mismatch");
    }

    float dot = 0;

    for(int i = 0; i < A.MATRIX_SIZE; i++)
    {
        dot += A[i] * B[i];
    }


    return dot;

}

GEmat eye(const int dim)
{
    GEmat result(dim, dim);
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

struct HouseholderReturn
{
    GEmat v;
    float beta;
};

void house(GEmat& v, float& beta)
{

    //house holder vector = x1 - |x||_2 
    //where ||x||2 is the 2-norm of vector x

    int m = v.MATRIX_SIZE;

    float x1 = v(0, 0);
    v[0] = 0;
    float sigma = dot(v,v);

    if(sigma == 0 && x1 >= 0)
    {
        beta = 0;
    }else if(sigma == 0 && x1 < 0)
    {
        beta = -2;
    }else
    {
        float mu = sqrt(pow(x1,2) + sigma);
        if(x1 <= 0)
        {
            v[0] = x1 - mu;
        }else
        {
            v[0] = -sigma/(x1 + mu);
        }

        float v0s = pow(v[0],2);
        beta = (2*v0s)/(sigma + v0s);
        v.divideBy(v[0]);

    }
}

void applyhouseholder(GEmat A)
{
    //A ^ MXN COLUMNS BY ROW
    int m = A.MATRIX_DIMENSION_Y;
    int n = A.MATRIX_DIMENSION_X;

    float beta;
    GEmat vt(1, m);

    GEmat matrixBuffer(n,m);
    GEmat matrixBuffer2(n,m);

    
    for(int j = 1; j < A.MATRIX_DIMENSION_X; j++)
    {
        A.subMatrix({j, m}, j, vt);
        house(vt, beta);
        matrixBuffer.resize({j,m}, {j,n});
        A.subMatrix({j,m}, {j,n}, matrixBuffer);
        A.subMatrix({j,m}, {j,n}, matrixBuffer2);
        vt.ftranspose();
        vt.multiply(matrixBuffer,matrixBuffer2);

        matrixBuffer2.display();
        vt.ftranspose();

        vt.display();
        vt.mulBy(beta);


        


        // A.subtractBy({j,m}, {j,n}, matrixBuffer2);
        // matrixBuffer.resize({j+1, m}, j);
        // vt.ftranspose();
        // vt.subMatrix({2,m-j+1},{0});

    }
}

void testHouseholder(GEmat A)
{
    int m = A.MATRIX_DIMENSION_Y;
    int n = A.MATRIX_DIMENSION_X;
    GEmat matrixBuffer(n,m);
    GEmat matrixBuffer2(n,m);
    float beta;

    GEmat vt(1,m);
    GEmat vs(1,m);

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
    
    GEmat forced = vt * matrixBuffer2;
    forced.display();
    A.subtractBy({j,m}, {j,n}, forced);
    A.display();
    A.setSubMatrix({j+1, m},{j}, vs);

    A.display();

    int e = 0;

}

void pyqr(GEmat A)
{
    int m = A.MATRIX_DIMENSION_X;
    int n = A.MATRIX_DIMENSION_Y;
    float beta;
    GEmat vt(1, n);
    GEmat mB(m,n);
    GEmat i(m,m);


    for(int j = 1; j < 2; j++)
    {
        A.subMatrix({j,m}, {j}, vt);
        house(vt, beta);
        vt.display();
        printf("%f\n", beta);

        
        GEmat out = vt;
        out.ftranspose();
        vt.multiply(out, mB);
        mB.mulBy(beta);

        i.resize(m,m);
        i.identity();

        i.subtractBy(mB);



    }

}




#endif