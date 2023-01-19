#ifndef LTXBERNCOEF
#define LTXBERNCOEF

#include <iostream>

int IntegerFactorial(int N)
{
    int Factorial = N;
    for(int i = N-1; i > 0; i--)
    {
        Factorial *= i;
    }
    return Factorial;
}

float BinomialCoefficient(int n,  int i)
{
    float Bnc = IntegerFactorial(i);
    if(Bnc == 0)
    {
        return 1;
    }
    float Bni = (IntegerFactorial(n));
    float Bmi = IntegerFactorial(n-i);
    if(Bmi == 0)
    {
        return 1;
    }
    float BC = Bni/(Bnc*Bmi);
    return BC;
}

void BinomialCoefficientVerification()
{
    int n = 3;
    for(int i = 0; i < n+1; i++)
    {
        std::cout << BinomialCoefficient(n, i) << "t^" << i << "(1-t)^" << n-i << "  +  " ;
    }
    std::cout << std::endl << std::endl << std::endl << std::endl; 
    n = n-1;
    for(int i = 0; i < n+1; i++)
    {
        
        std::cout << (n+1) * BinomialCoefficient(n, i) << "t^" << i << "(1-t)^" << n-i << "  +  " ;
    }
    
   std::cout << std::endl << std::endl << std::endl << std::endl ;
}
#endif