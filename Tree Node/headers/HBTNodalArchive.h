#include <iostream>
#include "headers/HBTNode.h"
#include "headers/HBTree.h"
#include "time.h"
#include <limits.h>
#include <math.h>
#include "GPTQueue.h"
#include "IRCAllocator.h"

HBTNode<int>* MakeNode(int n)
{
    HBTNode<int>* Nodes = new HBTNode<int>[n];

    

    for(int i = 1; i < n+1; i++)
    {

        Nodes[i-1].element = rand()%55+1;
        if((2*i)-1 < n)
        {
            Nodes[i-1].left = &Nodes[(2*i)-1];
            Nodes[i-1].parent = &Nodes[i-1];
        }
        if((2*i+1)-1 < n)
        {
            Nodes[i-1].right = &Nodes[(2*i+1)-1];
            Nodes[i-1].parent = &Nodes[i-1];
        }
        
    }
    
    for(int i = 0; i < n; i++)
    {
        //std::cout << Nodes[i].element << std::endl;

    }


    return &Nodes[0];

}

void LookNodes(HBTNode<int>* root)
{
    if(root == nullptr)
        return;
    LookNodes(root->left);
    std::cout << root->element << std::endl;
    LookNodes(root->right);
}

void InorderTraversal(HBTNode<int>* root)
{
    if(root == nullptr)
        return;
    InorderTraversal(root->left);
    std::cout << root->element << std::endl;
    InorderTraversal(root->right);
}

void PreorderTraversal(HBTNode<int>* root)
{
    if(root == nullptr)
        return;

    std::cout << root->element << std::endl;
    InorderTraversal(root->left);
    InorderTraversal(root->right);
}

void BFS(HBTNode<int>* root)
{
    GPTQueue<HBTNode<int>*> q;
    q.enqueue(root);
    int layer = 0;
    while(!q.empty())
    {
        HBTNode<int>* node = q.dequeue();
        
        printf("[ %d ] ", node->element);
        printf("( %f ) ", log2(layer+1));

        if(node->left){
            q.enqueue(node->left);
        }
        if(node->right){
            q.enqueue(node->right);
        }
        layer++;
    }
    std::cout << std::endl;
}

void DFS(HBTNode<int>* root, int depth)
{
    if(root)
    {
        printf("%d (depth %d)\n", root->element, depth);
        DFS(root->left, depth+1);
        DFS(root->right, depth+1);
    }
}

void PostorderTraversal(HBTNode<int>* root)
{
    if(root == nullptr)
        return;

    InorderTraversal(root->left);
    InorderTraversal(root->right);
    std::cout << root->element << std::endl;
}

void RotateRight(HBTNode<int>* &node)
{
    if(node == nullptr)
        return;
    HBTNode<int>* pivot = node->left;
    node->left = pivot->right;
    pivot->right = node;
    node = pivot;
}

void rotateRight(struct HBTNode<int>** root_ref) {
  HBTNode<int>* new_root = (*root_ref)->left;
  (*root_ref)->left = new_root->right;
  new_root->right = *root_ref;
  *root_ref = new_root;
}
void Rebalance(HBTNode<int>* node)
{

}
int Get_Height(HBTNode<int>* root)
{
    if(root == nullptr)
    {
        return 0;
    }
    return root->Height;
}
int Get_Balance(HBTNode<int>* root)
{
    if(root == nullptr)
    {
        return 0;
    }
    return Get_Height(root->left) - Get_Height(root->right);
}
void InsertBreak(HBTNode<int>* root, int key)
{
    if(root == nullptr)
    {
        root = new HBTNode<int>(key);
    }
    while(true)
    {
        if(key < root->element)
        {
            if(root->left == nullptr)
            {
                root->left = new HBTNode<int>(key);
                root->left->parent = root;
                break;
            }
            root = root->left;
        }
        
        if(key > root->element)
        {
            if(root->right == nullptr)
            {
                root->right = new HBTNode<int>(key);
                root->right->parent = root;
                break;
            }
            root = root->right;
        }


        root->Height = 1 + std::max(Get_Height(root->left), Get_Height(root->right));
        root->BalanceFactor = Get_Balance(root);
    }

    
}


bool lintCompare(int e, int e1)
{
    return(e<e1);
}
bool rintCompare(int e, int e1)
{
    return(e>e1);
}
bool equalCompare(int e, int e1)
{
    return(e==e);
}

template<class T, typename Allocator = IRAllocator<T>, int I = 3>
bool DriverAlly()
{
    Allocator NewAllocator;
    NewAllocator.Allocate(4);
}