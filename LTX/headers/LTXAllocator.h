#ifndef LTXALLOC
#define LTXALLOC

#include "memory.h"

template<typename T>
struct LTXAllocator
{
private:
    T defaultT;
    T* mem;
    int reserved;
    int index;
    bool empty;
    bool corrupt;
public:
    LTXAllocator()
    {
        mem = nullptr;
        reserved = 0;
        index = 0;
        empty = true;
        corrupt = true;
    }
    LTXAllocator(int num)
    {
        int ReservationStatus = Reserve(num);
        if(!ReservationStatus)
        {
            corrupt = true;
            reserved = 0;
            index = 0;
            empty = true;
        }
        index = 0;
    }
    LTXAllocator(int num, T* cpy)
    {
        int ReservationStatus = Reserve(num);
        if(!ReservationStatus)
        {
            corrupt = true;
            reserved = 0;
            index = 0;
            empty = true;
        }else
        {
            reserved = num;
            index = 0;

            int CopyStatus = Copy(cpy, num);
            if(!CopyStatus)
            {
                corrupt = true;
                index = 0;
            }
            else
            {
                corrupt = false;
                index += num;
            }
        }
    }
    int Copy(T* cpy, int num)
    {
        if(empty || corrupt || reserved < num)
        {
            return 0;
        }
        errno_t copyerror  = memcpy_s(mem, num*sizeof(T), cpy, num*sizeof(T));
        if(copyerror != 0)
        {
            return 0;
        }
        return 1; 
    }
    int Reserve(int num)
    {
        if(empty)
        {
            void* tBlock = malloc(num * sizeof(T));
            if(tBlock)
            {
                mem = (T*)tBlock;
                empty = false;
                reserved = num;
                corrupt = false;
                return 1;
            }
            return 0;
        }
        return 0;
    }
    int Free()
    {
        if(!empty && !corrupt && reserved != 0)
        {
            if(mem)
            {
                free(mem);
                empty = true;
                reserved = 0;
                corrupt = false;
                index = 0;
                return 1;
            }
            return 0;
        }
        return 1;
    }
    int Allocate(int num)
    {
        if(empty)
        {
            int ReservationStatus = Reserve(num);
            return ReservationStatus;
        }
        int ReallocationStatus = Reallocate(num);
        return ReallocationStatus;

    }
    int Reallocate(int num)
    {
        if(empty)
        {
            int ReservationStatus = Reserve(num);
            return ReservationStatus;
        }
        if(mem)
        {
            mem = (T*)realloc(mem, (reserved + num)*sizeof(T));
            if(mem)
            {
                reserved += num;
                corrupt = false;
                empty = false;
                return 1;
            }
            return 0;
        }
        return 0;

    }
    int Push(T unit)
    {
        if(empty)
        {
            int ReservationStatus = Reserve(1);
            if(!ReservationStatus)
            {
                return 0;
            }
        }

        if(index >= reserved-1)
        {
            int ReallocationStatus = Reallocate(1);
            if(!ReallocationStatus)
            {
                return 0;
            }
        }

        //checks if not default value if so then skip or reallocate.
        mem[index] = unit;
        index++;
        return 1;

    }
    int ShiftRight(int amt, int unit)
    {
        int SpaceNeeded = amt;
        int Space = reserved - index;
        if(amt > Space)
        {
            int ReallocationStatus = Reallocate(amt-Space);
        }
    }
    int Insert(T el, int unit)
    {
        if(unit > index)
        {
            if(unit > (reserved-1))
            {
                int NeededLength = unit - (reserved-1);
                int ReservationStatus = Reallocate(NeededLength);
                if(!ReservationStatus){return 0;}
            }
            mem[unit] = el;
            return 1;
        }
        



    }
    T& operator [](int index)
    {
        if(index <= reserved - 1)
        {
            return mem[index];
        }
        return mem[0];

    }
    ~LTXAllocator()
    {
        Free();
    }

};

#endif