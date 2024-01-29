#ifndef HASH_CODE_H
#define HASH_CODE_H
#include <random>
#include <cmath>
#include "ran.hpp"


inline bool isPrime(int value)
{
    if (value <= 1)  return false; //if the value is less than 1 return false.
    if (value <= 3)  return true; //if the value is greater than 1 and less than or equal to three , so basically 2 and 3 return true.

    if (value%2 == 0 || value%3 == 0) return false; //other wise if the number is divisble by two or three return false.
   
    for (int i=5; i*i<=value; i=i+6) //tbh don't even understand this, i guess it checks divisibliity of other prime numbers up until value
        if (value%i == 0 || value%(i+2) == 0)
           return false;
   
    return true;
}

inline int previousPrime(int value)
{


    if(value <= 2)
    {
        throw std::out_of_range("prime less than two");
    }
    if(value == 3) return 2;
    if(value == 5) return 3;

    value = ((value-1) % 2 == 0) ? value-2 : value-1;

    while(!isPrime(value))
    {
        value -= 2;
    }
    return value;
}

inline int nextPrime(int value)
{
    if (value <= 1)
        return 2;
 
    int prime = value;
    bool found = false;

    //Will increment value until it is prime.

    while (!found) {
        prime++;
 
        if (isPrime(prime))
            found = true;
    }
 
    return prime;
}

int combineHashCodes(int h1, int h2)
{
    int hash = 17;
    hash = 31 * hash + h1;
    hash = 31 * hash + h2;
    return hash;
}

int hash(int x)
{
    int w = sizeof(x)*8;
    int tw = (int)pow(2,32);
    uint64_t z = (x * 2654435761);
    int hc = z % tw;
    return  hc;
}

int hashCoded(double value)
{
    long bits = static_cast<long>(value);
    int high = (int)(bits >> 31);
    int low = (int)bits;
    return combineHashCodes(high, low);
}

struct Compound_P
{
    double p;
    double q;

    int hashCode()
    {
        long unsigned int z[] = {0x2058cc50L, 0xcb19137eL};
        long long unsigned int zz = 0xbea0107e5067d19dL;

        long h0 = hashCoded(p);
        long h1 = hashCoded(q);
        
        return (int)(((z[0] * h0 + z[1] * h1) * zz) >> 32);
    }
};

int modvs(int k, int m)
{

    double a = sizeof(k)*8;
    double b = (m/2);
    double c = m;
    double e = 2.71828;

    return static_cast<long long int>(a*e*( (pow((k-b),2))/(2*pow(c,2)) )) % m;



    

    
}

int guas_hash(int k, int m)
{
    std::default_random_engine generator(k);
    std::normal_distribution<double> distribution(0.0, 1.0);

    double random_number = distribution(generator);

    double exponent = -std::pow(random_number, 2.0)/2.0;
    double gaussian_value = std::exp(exponent);

    return static_cast< int>(std::round(gaussian_value * m)) % m;
}

int multiplicationMethod(int k, int m)
{
    uint8_t w = sizeof(k) * 8;
    
    double A = 0.5*(sqrt(5)-1);
    double s = k*A;
    double intpart;
    double x = modf(s, &intpart);
    double mx = m*x;
    int hk = floor(mx);

    return hk;
}

struct PrimeTable
{
    int size = 200;
    int primes_table[200] = {7,19,41,73,127,179,241,313,397,491,
    593,709,839,971,1117,1277,1439,1613,1801,1993,
    2203,2417,2647,2879,3121,3373,3637,3911,4201,4493,
    4799,5113,5437,5779,6121,6473,6841,7213,7603,8009,
    8419,8831,9257,9689,10133,10589,11057,11549,12037,12539,
    13043,13567,14107,14639,15187,15739,16301,16879,17467,18059,
    18661,19273,19913,20549,21191,21851,22531,23203,23887,24593,
    25301,26017,26759,27509,28277,29033,29803,30577,31379,32173,
    32983,33797,34631,35491,36341,37199,38069,38953,39839,40739,
    41641,42557,43481,44417,45361,46327,47293,48271,49253,50261,
    51263,52289,53323,54361,55411,56467,57529,58601,59693,60793,
    61909,63029,64151,65287,66431,67589,68767,69941,71129,72337,
    73547,74759,75983,77237,78479,79757,81019,82301,83591,84913,
    86239,87553,88883,90217,91571,92927,94291,95701,97103,98507,
    99923,101341,102763,104207,105649,107101,108571,110051,111533,113027,
    114547,116089,117617,119159,120709,122263,123829,125407,126989,128591,
    130199,131837,133481,135119,136769,138427,140111,141793,143477,145177,
    146891,148609,150343,152077,153841,155593,157363,159157,160967,162779,
    164581,166393,168227,170063,171917,173773,175649,177533,179429,181361,
    183263,185177,187111,189043,190997,192949,194911,196901,198899,200891,
    };

    int operator[](int index)
    {
        if(index < 0 || index >= size)
        {
            return -1;
        }

        return primes_table[index];
    }

} Primes_Table;


#endif