#ifndef GE_COMMON
#define GE_COMMON

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

#endif