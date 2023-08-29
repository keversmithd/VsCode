#ifndef STABLE_ARRAY_H
#define STABLE_ARRAY_H

#include <cstring>

template<typename T>
struct StableArray
{
private:
    T* data;
    int size;
    int capacity;
public:
    StableArray() : size(0), capacity(2), data(nullptr)
    {
        resize();
    }


    int find(T value)
    {
        int begin = 0;
        int end = size-1;
        int i = 0;
        for(i = (begin+end)/2; data[i] != value && (end-begin) > 0; i = (begin+end)/2)
        {

            if(value < data[i])
            {
                end = i;
            }else if(value > data[i])
            {
                begin = i+1;
            }
        }

        return (data[i] == value) ? i : -1;
    }

    std::vector<int> findAll(T value)
    {
        std::vector<int> v;
        int ip = find(value);

        if(ip == -1)
        {
            return v;
        }

        v.push_back(ip);

        for(int l = ip-1, r = ip+1; (l >= 0 && r < size) && (data[l] == value || data[r] == value);)
        {

            if(l >= 0 && data[l] == value)
            {
                v.push_back(l);
                l--;
            }

            if(r < size && data[r] == value)
            {
                v.push_back(r);
                r++;
            }

        }

        return v;
    }

    T operator[](const int index)
    {
        if(index < 0 || index > size-1)
        {
            return T();
        }

        return data[index];
    }

    void remove(T value)
    {
        int ind = find(value);

        if(ind == -1)
        {
            return;
        }

        for(int i = ind; i < size-1; i++)
        {
            data[ind] = data[ind+1];
        }

        size--;

    }

    void insert(T value)
    {

        if((size+1) > capacity)
        {
            resize();
        }


        data[size] = value;

        for(int i = size; i > 0 && data[i] < data[i-1]; i--)
        {
            T temp = data[i-1];
            data[i-1] = data[i];
            data[i] = temp;
        }

        size++;


    }


    void resize()
    {
        T* memBuffer = new T[capacity*2];

        if(data != nullptr && data != memBuffer)
        {
            memcpy(memBuffer, data, sizeof(T)*size);
            delete[] data;

        }

        capacity = capacity*2;

        data = memBuffer;
        




    }

    ~StableArray(){

        if(data != nullptr)
        {
            delete[] data;
            data = nullptr;
        }
    }


};

#endif