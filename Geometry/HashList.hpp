#ifndef HASH_LIST_H
#define HASH_LIST_H
#include <stdexcept>
template<typename T>
struct HashLink //Templated Hash "Link". Stores a value and a next pointer.
{
    T value;
    HashLink<T>* next;
};


template<typename T>
struct HashList //Templated "singly non-circular" linked list.
{
    HashLink<T>* root; //"Head" of linked list.
    HashLink<T>* tail; //"Tail" of linked list.
    bool destroy; //"If this is enabled the destructor will destroy the contents."
    int elements; //The length of the linked list.
    HashList() : root(nullptr), tail(nullptr), elements(0), destroy(false)
    {
        //Sets root and tail to nullptr and elements to zero.
    }

    void AddToEnd(const T value)
    {
        if(root == nullptr) //If the list is empty, then create new node, set next to nullptr, value to value, and root to new node, and tail to new node.
        {
            HashLink<T>* nodal = new HashLink<T>();
            nodal->next = nullptr;
            nodal->value = value;
            root = nodal;
            tail = nodal;
        }else //Other wise create new node, set next to nullptr and value to value, and tail's next to nodal.
        {
            HashLink<T>* nodal = new HashLink<T>();
            nodal->next = nullptr;
            nodal->value = value;

            tail->next = nodal;
            tail = nodal;
        }
        elements++; //Increment elements.
    }

    void remove(const T value) 
    {
        //A function that loops through the list until the value is found, then it deletes the element from the list, and breaks the loop. otherwise, loops entire list and returns element.
        if(root == nullptr)
        {
            throw std::out_of_range("empty linked list");
        }
        HashLink<T>* tip = root;
        HashLink<T>* prev = root;

        bool p1 = false;
        bool found = false;

        while(tip != nullptr && found == false)
        {
            if(tip->value == value)
            {
                if(tip == prev)
                {
                    delete tip;
                    root = nullptr;
                    tail = nullptr;
                    found = true;
                    elements--;
                }else
                {
                    prev->next = tip->next;
                    delete tip;
                    found = true;
                    elements--;
                }
            }else
            {
                tip = tip->next;
                if(p1)
                {
                    prev = prev->next;
                }
            }
            p1 = true;
        }
    }

    T remove(HashLink<T>* prev, HashLink<T>* nodal)
    {
        //A function to remove any item anywhere in the list just using the previous node, and the current node.
        if(nodal == nullptr || prev == nullptr)
        {
            return T();
        }
        T returnValue = nodal->value;
        if(prev == nodal)
        {
            T returnValue = root->value;
            if(nodal->next != nullptr)
            {
                root = nodal->next;
            }
            else
            {
                root = nullptr;
                tail = nullptr;
            }
            delete nodal;
            elements--;
            return returnValue;

        }else if(nodal->next == nullptr)
        {
            prev->next = nullptr;
            
            delete nodal;
            elements--;
            return returnValue;
        }else
        {
            prev->next = nodal->next;
            delete nodal;
            elements--;
            return returnValue;
        }
        
    }

    ~HashList()
    {
        if(destroy) //if destory is enabled.
        {
            //Iterate through list and delete nodes.
            HashLink<T>* nodal = root;
            HashLink<T>* temp = root;

            while(nodal != nullptr)
            {
                temp = nodal;
                nodal = temp->next;
                delete temp;
            }
        }
        
    }

};

#endif