#ifndef TARRAY_H
#define TARRAY_H

template<typename T, int I>
struct TArray
{
    const int size;
    T m_data[I];
    T dummy;

    TArray() : size(I)
    {

    }

    T& operator[](int index)
    {
        if(index >= 0 && index <= size-1)
        {
            return m_data[index];
        }else
        {
            return dummy;
        }
    }
};



template<typename T>
struct CGConstArray
{
    const void* object;
    const int size;
    T dummy;
    T* objects;

    CGConstArray(const void* p_reference, const int elements, T* p_objs) : object(p_reference), size(elements), objects(p_objs)
    {

    }

    T& operator[](int index)
    {
        if(index >= 0 && index <= size-1)
        {
            return objects[index];
        }else
        {
            return dummy;
        }
    }

};
#endif