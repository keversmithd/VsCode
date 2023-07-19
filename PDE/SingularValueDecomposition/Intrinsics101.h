#ifndef INTRIN_H
#define INTRIN_H

#include <xmmintrin.h>
#include <intrin.h>
#include "stdio.h"



void m256_see(__m256& a, __m256& b)
{
    //__m128 leftHalf =  _mm256_extractf128_ps(b, 0);
    float bank[8];
    //_mm256_store_ps(bank, b);

    __m256 multiplication =_mm256_mul_ps(a, b);
    __m256 hadd = _mm256_hadd_ps(multiplication, multiplication);
    __m128 low128 = _mm256_extractf128_ps(hadd,0);
    __m128 hi128 = _mm256_extractf128_ps(hadd, 1);
    __m128 dotproduct = _mm_add_ps(low128, hi128);

    //00000000
    //bit 1: selects either the first or last four elements from the selected array to be placed at the top of the list
    //bit 2: selects either the first or second vector
    //bit 3: nothing
    //bit 4: if set zeroes the entire first four elements of result

    //repeat for the next
    
    __m256 permutation = _mm256_permute2f128_ps(a,b, 0b00110010);

    //First half of result are from the first vector, last half from second vector
    __m256 blended = _mm256_blend_ps(a, b, 0b11110000);


    //cancels out the right vector entirely
    
    
     //dot information left 4 bits so how far to dot product, the right set say whether to print it in the spot
    __m256 result = _mm256_dp_ps(a, b, 0b11111000);
    

    printf("(%f, %f, %f, %f, %f, %f, %f, %f)\n",bank[0], bank[1], bank[2], bank[3], bank[4], bank[5], bank[6], bank[7]);
    

}

float _m256_dot(__m256 a, __m256 b)
{
    __m256 mul = _mm256_mul_ps(a, b);
    __m256 sum1 = _mm256_hadd_ps(mul, mul);


    __m256 sum2 = _mm256_hadd_ps(sum1, sum1);


}


#endif