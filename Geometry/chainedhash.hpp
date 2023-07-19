#ifndef CHAINED_HASH_H
#define CHAINED_HASH_H

#include <list>
#include <vector>
#include <stdint.h>
#include <memory>

#include "ran.hpp"


template<typename T>
struct ChainHash
{
    std::vector<std::list<T>> t; //average length of list is (number of occurences of x in the hash table + 2)
    //number of occurences in list should be 1, nx = 3
    //multiset Iy = {1 if (hash(x) == hash(y)), 0 else}
    //Iy = 
    uint64_t z;
    int n;
    int resizes;

    ChainHash() : n(0), resizes(0), z(dis(gen))
    {
        t.reserve(11);
    }
    bool add(T x)
    {
        bool finding;
        find(x, finding);
        if(finding != false) return false; //no duplicates
        if (n+1 > t.capacity()) resize(); //average number of elements in one of these lists is n/t.length <= 1.
        t[hash(x)].push_back(x);
        n++;
        return true;
    }
    T remove(T x, bool& found)
    {
        int index = hash(x);
        for(int j = 0; j < t[index].size(); j++)
        {
            T value = *(t[index].begin() + j);
            if(value == x)
            {
                t[index].erase(j);
                n--;
                found = true;
                return x;
                
            }

                
        }

        found = false;
        return T();
    }
    T find(T x, bool& found)
    {
        for(T y : t[hash(x)])
            if(y == x)
            {
                found = true;
                return y;
            }
                

        found = false;
        return T();
    }
    void resize()
    {
        
        t.resize(2 * t.capacity());
        for(int i = 0; i < t.size(); i++)
        {
            for(int j = 0; j < t[i].size(); j++)
            {
                T value = t[i].front();
                t[i].pop_front();
                add(value);
            }
        }
    }

    int hash(T x)
    {
       
        // uint32_t multiplier = 0x678DDE6F;
        // uint32_t n = t.capacity();
        // uint32_t hash = x % n;
        // uint32_t d = (0xFFFFFFFF / n) + 0x1;
        // uint32_t i  = (hash * multiplier) / d;
        
        double d = log2(t.capacity());
        int w = 32;
        double twow = pow(2,32);
        uint64_t t = static_cast<uint64_t>(twow);
        
        z = z % (t-1);
        if(z % 2 == 0)
        {
            z += 1;
        }
        uint64_t modvalue = ((z*x) % t);
        uint64_t wd = (w-d);
        uint64_t modex = modvalue >> (w-(uint64_t)d);
       
        // uint64_t z = (rand() % twow-1)+1;
        // int modex = ((z*x) % twow);

        return modex;
    }

    ~ChainHash()
    {

    }
};
#endif