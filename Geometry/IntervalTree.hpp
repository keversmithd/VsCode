#ifndef INTERVAL_TREE
#define INTERVAL_TREE
#include <iostream>
using namespace std;
template<typename T>
struct Interval
{
    T low, high;
};

template<typename T>
struct ITNode
{
    Interval<T> *i;  // 'i' could also be a normal variable
    T max;
    ITNode<T> *left;
    ITNode<T> *right;
};

template<typename T>
ITNode<T>* newNode(Interval<T> i)
{
    ITNode<T> *temp = new ITNode<T>;
    temp->i = new Interval<T>(i);
    temp->max = i.high;
    temp->left = temp->right = nullptr;
    return temp;
};


template<typename T>
ITNode<T> *insert(ITNode<T> *root, Interval<T> i)
{
    // Base case: Tree is empty, new node becomes root
    if (root == NULL)
        return newNode<T>(i);
 
    // Get low value of Interval<T> at root
    int l = root->i->low;
 
    // If root's low value is smaller, then new Interval<T> goes to
    // left subtree
    if (i.low < l)
        root->left = insert(root->left, i);
 
    // Else, new node goes to right subtree.
    else
        root->right = insert(root->right, i);
 
    // Update the max value of this ancestor if needed
    if (root->max < i.high)
        root->max = i.high;
 
    return root;
}

template<typename T>
bool doOVerlap(Interval<T> i1, Interval<T> i2)
{
    if (i1.low <= i2.high && i2.low <= i1.high)
        return true;
    return false;
}

template<typename T>
Interval<T> *overlapSearch(ITNode<T> *root, Interval<T> i)
{
    // Base Case, tree is empty
    if (root == NULL) return NULL;
 
    // If given interval overlaps with root
    if (doOVerlap<T>(*(root->i), i))
        return root->i;
 
    // If left child of root is present and max of left child is
    // greater than or equal to given interval, then i may
    // overlap with an interval is left subtree
    if (root->left != NULL && root->left->max >= i.low)
        return overlapSearch<T>(root->left, i);
 
    // Else interval can only overlap with right subtree
    return overlapSearch<T>(root->right, i);
}
template<typename T>
void inorder(ITNode<T> *root)
{
    if (root == NULL) return;
 
    inorder(root->left);
 
    cout << "[" << root->i->low << ", " << root->i->high << "]"
         << " max = " << root->max << endl;
 
    inorder(root->right);
}


int driver()
{
    
    Interval<int> ints[] = {{15, 20}, {10, 30}, {17, 19},
        {5, 20}, {12, 15}, {30, 40}
    };
    int n = sizeof(ints)/sizeof(ints[0]);
    ITNode<int> *root = NULL;
    for (int i = 0; i < n; i++)
        root = insert<int>(root, ints[i]);
 
    cout << "Inorder traversal of constructed Interval<T> Tree is\n";
    inorder(root);
 
    Interval<int> x = {6, 7};
 
    cout << "\nSearching for Interval<T> [" << x.low << "," << x.high << "]";
    Interval<int> *res = overlapSearch<int>(root, x);
    if (res == NULL)
        cout << "\nNo Overlapping Interval<T>";
    else
        cout << "\nOverlaps with [" << res->low << ", " << res->high << "]";
    return 0;
}

#endif