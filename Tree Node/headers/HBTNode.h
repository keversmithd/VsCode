#ifndef _HBTNODE
#define _HBTNODE

template<typename E>
struct HBTNode
{
    E element;
    HBTNode* parent;
    HBTNode* right;
    HBTNode* left;
    int BalanceFactor;
    int Height;
    HBTNode(E _element, HBTNode<E>* left = nullptr, HBTNode<E>* right = nullptr, HBTNode<E>* parent = nullptr) : element(_element), left(left), right(right), parent(parent) Height(1), BalanceFactor(0) {}
    HBTNode(){right = nullptr; left = nullptr; BalanceFactor = 0; Height = 1;}
    E CopyElement(){ return element; }
    E& ReferenceElement(){return element;}
    E* PointElement(return &element; )

    ~HBTNode(){}
};

#endif