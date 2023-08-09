#include <iostream>
#include "DCEL.h"

struct TreeNode
{
    int val;
    TreeNode* right;
    TreeNode* left;
    TreeNode(const int v) : val(v)
    {

    }
};

int main()
{
    TreeNode* root = new TreeNode(0);
    root->left = new TreeNode(1);
    
    auto parent = root;
    auto nParent = new TreeNode(2);
    parent->left = nParent;
    parent = nParent;




    DCEL newCel;
}