#ifndef FACTORIAL_H
#define FACTORIAL_H

int IntegerFactorial(int N)
{
    int Factorial = N;
    for(int i = N-1; i > 0; i--)
    {
        Factorial *= i;
    }
    return Factorial;
}

#endif