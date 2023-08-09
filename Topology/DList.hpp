#ifndef DL_LIST_HPP
#define DL_LIST_HPP


template<typename T>
struct DLNode
{
    T value;
    DLNode* next;
    DLNode* prev;
};

template<typename T>
struct DLList
{
    DLNode<T>* head;
    DLNode<T>* tail;

    DLList() : head(nullptr), tail(nullptr)
    {

    }


    void AddTail(const T value){

        if(tail == nullptr)
        {
            head = new DLNode<T>();

            head->value = value;
            head->next = nullptr;
            head->prev = nullptr;
            tail = head;
        
            return;
        }

        DLNode<T>* next = new DLNode<T>();
        next.prev = tail;
        next.next = nullptr;
        tail->next = next;

    }

    void AddHead(const T value)
    {
        if(tail == nullptr)
        {
            head = new DLNode<T>();

            head->value = value;
            head->next = nullptr;
            head->prev = nullptr;
            tail = head;
        
            return;
        }

        DLNode<T>* next = new DLNode<T>();
        next.prev = tail;
        next.next = nullptr;
        tail->next = next;
    }

    ~DLList()
    {

    }

};


#endif