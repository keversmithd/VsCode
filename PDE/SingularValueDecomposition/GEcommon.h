#ifndef GE_COMMON
#define GE_COMMON

struct GEspan
{
    int from;
    int to;

    GEspan() : from(-1), to(-1)
    {

    }

    bool Infinity()
    {
        return (from == -1 && to == -1);
    }

    void SetLimits(int MATRIX_DIMENSION)
    {
        if(from == -1)
        {
            from = 1;
        }
        if(to == -1)
        {
            to = MATRIX_DIMENSION;
        }
    }

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

    void decrement()
    {
        from--;
        to--;
    }
};

#endif