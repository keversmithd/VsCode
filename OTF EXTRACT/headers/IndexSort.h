#ifndef INDEXSORT_H
#define INDEXSORT_H

#include "IndexElement.h"
#include <iostream>

template<typename T>
void PrintList(IndexElement<T>* ElementList, int begin, int end)
{
    
    for(int i = begin; i <= end; i++)
    {
        std::cout << ElementList[i].element << " ,  ";
    }
    std::cout << std::endl;
}

template<typename T>
void Swap(IndexElement<T>* ElementList, int t1, int t2)
{
    IndexElement<T> Temp = ElementList[t1];
    ElementList[t1] = ElementList[t2];
    ElementList[t2] = Temp;
}

template<typename T>
void InsertionSort(IndexElement<T>* ElementList, int begin, int end)
{
    for(int i = begin; i < end; i++)
    {
        IndexElement<T> source = ElementList[i];
        int j = i-1;
        while(source < ElementList[j])
        {
            j--;
        }
        
        Swap(ElementList, i, j);
    }
}

template<typename T>
int PivotSelection(IndexElement<T>* ElementList, int begin, int middle, int end)
{
    int Index[3] = {begin, middle, end};
    int SwapList[3] = {0,1,2};
    IndexElement<T> MedianOfThree[3] = {ElementList[begin], ElementList[middle], ElementList[end]};
    
    IndexElement<T> Smallest = MedianOfThree[0];
    IndexElement<T> Largest = MedianOfThree[2];
    IndexElement<T> Median = MedianOfThree[1];
    
    int pivot = 0;
    for(int i = 0; i < 3; i++)
    {
        if(MedianOfThree[i] < Smallest)
        {
            Smallest = MedianOfThree[i];
            SwapList[0] = i;
        }
        if(MedianOfThree[i] > Largest)
        {
            Largest = MedianOfThree[i];
            SwapList[2] = i;
        }
        if(MedianOfThree[i] != Smallest && MedianOfThree[i] != Largest)
        {
            Median = MedianOfThree[i];
            SwapList[1] = i;
        }
    }
    Swap(ElementList, begin, Index[SwapList[0]]);
    Swap(ElementList, middle, Index[SwapList[1]]);
    Swap(ElementList, end, Index[SwapList[2]]);
    return middle;
}

template<typename T>
int Partition(IndexElement<T>* ElementList, int begin, int end)
{
    int middle = begin + (end - begin)/2;
    int Pivot = 0;
    int Selection = (end-begin)+1;
    Pivot = PivotSelection(ElementList, begin, middle, end);
    
    Swap(ElementList, Pivot, end);
    
    IndexElement<T> MedianElement = ElementList[end];
    int stashIndex = begin;
    for(int i = begin; i < end; i++)
    {
        if(ElementList[i] < MedianElement)
        {
            Swap(ElementList, i, stashIndex);
            stashIndex++;
        }
    }
    Swap(ElementList, end, stashIndex);
    return stashIndex;
    
}

template<typename T>
void QuickSort(IndexElement<T>* ElementList, int begin, int end)
{
        if(begin < end)
        {
            int Selection = (end - begin) + 1;
            if(Selection == 2)
            {
                if(ElementList[end] < ElementList[begin])
                {
                    Swap(ElementList, end, begin);
                }
                return;
            }
            if(Selection < 2)
            {
                return;
            }
            int Pivot = Partition(ElementList, begin, end);
            QuickSort(ElementList, begin, Pivot-1);
            QuickSort(ElementList, Pivot+1, end);
        }

}

#endif