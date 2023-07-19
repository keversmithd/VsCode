#ifndef UTILS_H
#define UTILS_H

#include "stdio.h"

void swap(float& a, float& b)
{
    const float temp = a;

    a = b;
    b = temp;
}


#endif