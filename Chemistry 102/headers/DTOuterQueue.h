#pragma once

#include <math.h>
#include <vector>
#include <malloc.h>
template<typename T>
struct DTOuterQueue
{
   T backup;
   T* Information;
   int Size;
   int Size_Info;
   int Current_Index;
   int GrowSizeRatio;
   DTOuterQueue(const int& I = 1, const int& GrowthRatio = 3) : Information(nullptr), Size_Info(0), Current_Index(0), GrowSizeRatio(GrowthRatio), Size(0){ if(I > 0){Allocate(I);} }  
   void Push(T Element)
   {
       if(Current_Index >= ((Size_Info)/sizeof(T))){ Reallocate(); } 
       Information[Current_Index] = Element; Current_Index++; Size++;   
   }
   void Allocate(const int& amt)
   {
       FreeData();
       Information = (T*)malloc(sizeof(T)*amt);
       Size_Info = sizeof(T)*amt;
   }
   void Reallocate()
   {
       unsigned short TSize = sizeof(T);
       unsigned short ESize = Size_Info/TSize;
       Size_Info += TSize * GrowSizeRatio * (log(ESize + 1)) + 1;
       Information = (T*)realloc(Information, Size_Info);
       //Size_Info = TSize * (Size_Info/TSize * 2 + 1);
       
   }
   void FreeData()
   {
       if(Information != nullptr)
       {
           free(Information);
           Information = nullptr;
       }
   }
   void Remove(const int& Index)
   {
        if(Index >= 0 && Index < Size_Info/sizeof(T))
        {
            for(int i = Index; i < Size; i++)
            {
                Information[i] = Information[i+1];
            }

            Size--;
            Current_Index--;
        }
        return;
   }
   void Insert(const int& Index, T Value)
   {   
        if(Index >= 0 && Index < Size_Info/sizeof(T))
        {
            if(Current_Index+1 >= ((Size_Info)/sizeof(T))){ Reallocate(); }
            for(int i = Size; i > Index; i--)
            {
                Information[i] = Information[i-1];
            }

            Information[Index] = Value;
            Size++;
            Current_Index++;
        }
   }
   T& operator [](int Index){ if(Index >= 0 && Index < Size_Info/sizeof(T)){ return Information[Index]; } return backup; }
   ~DTOuterQueue(){ free(Information); }
};
