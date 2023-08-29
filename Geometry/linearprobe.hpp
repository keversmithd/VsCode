#ifndef STRING_HASH_H
#define STRING_HASH_H


#include <iostream>

#include "hashcodes.hpp"

template<typename T>
class LinearProbe
{
private:
    T* hashData;
    T dummy;
    int capacity;
    int size;
    int resizes;
public:
    LinearProbe(T empty) : dummy(empty), hashData(nullptr), capacity(7), size(0), resizes(0)
    {
        resize();
    }
    void addItem(const T value)
    {
            //If the appension of one element will be greater than capaicty resize the array.
        if(size+1 > capacity/2)
        {
            resize();
        }

        int hashIndex = hashFunc(value);
        bool eo = false;
        int pi = hashIndex;
        //If the hashed index location is marked unknown then search linearly along the array, and even looping the array until an avaiable location is found.
        while(hashData[hashIndex] != dummy && eo == false)
        {
            
            hashIndex = (hashIndex+1)%capacity;

            if(hashIndex == pi)
            {
                eo = true;
            }
            
        }

        if(eo == false)
        {
            hashData[hashIndex] = value;
            size++;
        }
    }
    bool findItem(const T value)
    {
        //Will select hash funciton of item, if the value at that location is not the value it will keep searching until encircled completely once, then it will return false if not found.
        int hashIndex = hashFunc(value);
        bool eo = false;
        bool found = false;
        int pi = hashIndex;

        while(hashData[hashIndex] != value && eo == false && found == false)
        {
            hashIndex = (hashIndex+1)%capacity;
            if(hashIndex == pi)
            {
                eo = true;
            }
            if(hashData[hashIndex] == value)
            {
                found = true;
            }
        }

        if(eo == false && found == false)
        {
            found = true;
        }
        

        return found;
    }
    void removeItem(const T value)
    {
            //will use the find algorithm and then set that value to unknown if it does find other wise, it will just loop around and return.
        int hashIndex = hashFunc(value);
        bool eo = false;
        int pi = hashIndex;
        bool found = false;
        while(eo == false && found == false)
        {
            hashIndex = (hashIndex+1)%capacity;

            found = hashData[hashIndex] == value;
            if(hashIndex == pi)
            {
                eo = true;
            }
            
        }

        if(found == true)
        {
            hashData[hashIndex] = dummy;
            size--;
        }

    }
    void resize()
    {
        //will resize the list to the next prime function.
        int storage = 0;
        if(resizes < Primes_Table.size)
        {
            storage = Primes_Table[resizes];
        }else
        {
            storage = nextPrime(capacity);
        }
        
        T* memBuffer = new T[storage]; 
        int previousCapacity = capacity;
        capacity = storage;

        for(int i = 0; i < capacity; i++)
        {
            memBuffer[i] = dummy;
        }

        int hashIndex, pi;
        bool eo, found;

        
        
        for(int i = 0, z = 0; (i < previousCapacity) || (z < size); i++)
        {
            if(hashData[i] != dummy)
            {
                z++;
                hashIndex = hashFunc(hashData[i]);
                found = false;
                pi = hashIndex;
                eo = false;

                while(found = false && eo == false)
                {
                    hashIndex = (hashIndex + 1) % capacity;
                    if(hashIndex == pi)
                    {
                        eo = true;
                    }

                    found = (memBuffer[hashIndex] == dummy);
                }

                if(found == true)
                {
                    memBuffer[hashIndex] = hashData[i];
                    
                }
            }
        }

        if(hashData != nullptr && hashData != memBuffer)
        {
            delete[] hashData;
        }
        
        hashData = memBuffer;
    }
    void showtable()
    {
        for(int i = 0; i < capacity; i++)
        {
            std::cout << hashData[i] << ", ";
            if(i % 10 == 0)
            {
                std::cout << std::endl;
            }
        }
        std::cout << std::endl;
    }

    void showthere()
    {
        int ps = 0;
        for(int i = 0; i < capacity; i++)
        {
            if(hashData[i] != dummy)
            {
                //std::cout << hashData[i] << ", ";
                if((ps+1) % 10 == 0)
                {
                    //std::cout << std::endl;
                }
                ps++;
            }
        }
        std::cout << ps;
        std::cout << std::endl;
    }

    int hashFunc(T key)
    {
        //provided by jim bailey and team.
        int hashCode = key.hashCode();
        return guas_hash(hashCode, capacity);
    }
    ~LinearProbe()
    {
         //deletes the data if it exists.
        if(hashData != nullptr)
        {
            delete[] hashData;
        }
    }
};

#endif