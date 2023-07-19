#ifndef CHAINED_HASH_H
#define CHAINED_HASH_H

#include <list>
#include <vector>
#include <stdint.h>
#include <memory>

#include "ran.hpp"

template<typename T>
struct ChainHashNode
{
    T data;
    ChainHashNode* next = nullptr;

};

template<typename T>
struct ChainHashList
{
    ChainHashNode<T>* head;
    ChainHashNode<T>* tail;
    int m_size;

    ChainHashList() : head(nullptr), tail(nullptr), m_size(0)
    {

    }

    void push_back(const T x)
    {
        
        ChainHashNode<T>* node = new ChainHashNode<T>();
        node->data = x;

        if(head == nullptr)
        {
            head = node;
            tail = node;
        }else
        {
            tail->next = node;
            tail = tail->next;
        }

        m_size++;
    }
    int size()
    {
        return m_size;
    }

    T front()
    {
        return head->data;
    }

    void pop_front()
    {
        if(head != nullptr)
        {
            ChainHashNode<T>* node = head;
            head = head->next;
            delete node;

           m_size--;      
        }
    }

    bool empty()
    {
        return (m_size == 0);
    }

};

template<typename T>
struct ChainHash
{
    ChainHashList<T>* t; //average length of list is (number of occurences of x in the hash table + 2)
    //number of occurences in list should be 1, nx = 3
    //multiset Iy = {1 if (hash(x) == hash(y)), 0 else}
    //Iy = 
    uint64_t z;
    int n;
    int resizes;
    int capacity;
    int re;

    ChainHash() : n(0), resizes(0), z(dis(gen)), capacity(0), t(nullptr), re(2)
    {

    }

    bool add(T x)
    {
        bool finding;
        find(x, finding);
        if(finding != false) return false; //no duplicates
        if (n+1 > capacity) resize(); //average number of elements in one of these lists is n/t.length <= 1.
        int hashIndex = hash(x);
        t[hashIndex].push_back(x);
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
        if(n == 0)
        {
            found = false;
            return T();
        }
        int hashIndex = hash(x);
        int LinkedListSize = t[hashIndex].size();
        ChainHashNode<T>* y = t[hashIndex].head;
        while(y != nullptr)
        {
            if(y->data == x)
            {
                found = true;
                return y->data;
            }

            y = y->next;
        }
        found = false;
        return T();
    }
    void resize()
    {
        ChainHashList<T>* memBuffer = new ChainHashList<T>[((re+1) * 2)];
        for(int i = 0; i < capacity; i++)
        {
            for(int j = 0; j < t[i].size(); j++)
            {
                T value = t[i].front();
                t[i].pop_front();
                memBuffer[hash(value)].push_back(value);
            }
        }

        if(t != nullptr && t != memBuffer)
        {
            delete[] t;
        }

        t = memBuffer;

        capacity = ((re+1) * 2);
    }

    int hash(T x)
    {
       
        // uint32_t multiplier = 0x678DDE6F;
        // uint32_t n = t.capacity();
        // uint32_t hash = x % n;
        // uint32_t d = (0xFFFFFFFF / n) + 0x1;
        // uint32_t i  = (hash * multiplier) / d;
        
        double d = log2(capacity);
        int w = 32;
        double twow = pow(2,32);
        uint64_t t = static_cast<uint64_t>(twow);
        
        z = z % (t-1);
        if(z % 2 == 0)
        {
            z += 1;
        }
        uint64_t modvalue = ((z*x.hash()) % t);
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