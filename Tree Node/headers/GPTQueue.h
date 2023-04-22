#ifndef GPTQUEUE
#define GPTQUEUE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <vector>

template<typename T>
struct GPTQueue
{
    int front;
    int rear;
    int size;
    std::vector<T> elements;
    GPTQueue(){ front = 0; rear = -1; size = 0; }
    
    void enqueue(T v)
    {
        rear++;
        elements.insert(elements.begin()+rear, v);
        size++;
    }
    T dequeue()
    {
        T v = elements[front];
        front++;
        size--;
        return v;
    }
    bool empty()
    {
        return size <= 0;
    }
    
};

#endif