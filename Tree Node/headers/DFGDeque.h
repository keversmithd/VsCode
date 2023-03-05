#ifndef GFG_DEQUE
#define GFG_DEQUE


template<typename T, typename Allocator>
struct DFGDeque
{   
    private:
        Allocator DynamicMemory;
    public:
        GFGDeque(); //if I = 0, use an allocator
        int InsertFront();
        int InsertLast();
        int DeleteFront();
        int DeleteLast();
        int GetFront();
        int GetLast();
        int IsEmpty();
        int IsFull();
};


#endif