#ifndef INDEXELEMENT
#define INDEXELEMENT
#include <stdint.h>


template<typename T>
struct IndexElement
{
    T element;
    int currentIndex;
    int prevIndex;
    char* string;
    bool operator >(const IndexElement a)
    {
        return this->element > a.element;
    }
    bool operator <(const IndexElement a)
    {
        return this->element < a.element;
    }
    bool operator !=(const IndexElement a)
    {
        return this->element !=  a.element;
    }
};

#endif