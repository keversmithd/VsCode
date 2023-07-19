#ifndef VIEW_TREE_HPP
#define VIEW_TREE_HPP

#include "Deque.hpp"

struct view_parent_box
{
    double x, y;
};

template<typename T, typename N>
struct view_node_parent
{
    double x, y;
    N node = nullptr;
    view_parent_box parent;
};

template<typename T, typename N>
void view_tree(N root, int elements)
{
    if(root == nullptr)
    {
        return;
    }

    int initalSpacing = log2(elements);

    Deque<view_node_parent<T,N>> q;

    int nodeproccessed = 3;
    int currentLevel = log2(nodeproccessed);
    int tLevel = currentLevel;

    double ypad = 1.0;
    double y = 0.0;



    view_node_parent<T,N> origin;
    origin.node = root;
    origin.parent = {0,0};
    origin.x = 0;
    origin.y = 0;

    if(root->Data.c_str()[0] == '^')
    {
        printf("\\draw (%f,%f) circle (10pt) [] node {%s}; \n", origin.x, origin.y, "\\textasciicircum");
    }else
    {
        printf("\\draw (%f,%f) circle (10pt) [] node {%s}; \n", origin.x, origin.y, root->Data.c_str());
    }
    
    //printf("\\draw (%f, %f) circle(10pt) [anchor = north east] node {%d};\n", origin.x, origin.y, root->height);

    if(root != nullptr && root->left != nullptr)
    {
        view_node_parent<T,N> left;;
        left.node = root->left;
        left.parent = {origin.x, origin.y};
        left.x = -initalSpacing;
        left.y = -1;
        q.addTail(left);
    }

    if(root != nullptr && root->right != nullptr)
    {
        view_node_parent<T,N> right;
        right.node = root->right;
        right.parent = {origin.x, origin.y};
        right.x = initalSpacing;
        right.y = -1;
        q.addTail(right);
    }
    

    while(!q.isEmpty())
    {
        
        view_node_parent<T,N> p = q.removeHead();
        nodeproccessed++;
        if(p.node != nullptr)
        {
            printf("\\draw ($(%f, %f)+(275:10pt)$) -- ($(%f, %f)+(90:10pt)$);\n", p.parent.x, p.parent.y, p.x, p.y);

            if(p.node->Data.c_str()[0] == '^')
            {
                printf("\\draw (%f, %f) circle(10pt) [] node {%s};\n", p.x, p.y, "\\textasciicircum");
            }else
            {
                printf("\\draw (%f, %f) circle(10pt) [] node {%s};\n", p.x, p.y, p.node->Data.c_str());
            }

            
            //printf("\\draw (%f, %f) circle(10pt) [anchor = north east] node {%d};\n", p.x, p.y, p.node->height);
            
            currentLevel = abs(p.y - 1);
            
            double innerSpacing = abs(p.x - p.parent.x)/2.0;

            view_node_parent<T,N> leftChild;
            leftChild.parent = {p.x,p.y};
            leftChild.node = p.node->left;
            leftChild.x = p.x - innerSpacing;
            leftChild.y = -currentLevel;

            q.addTail(leftChild);

            view_node_parent<T,N> rightChild;
            rightChild.parent = {p.x, p.y};
            rightChild.node = p.node->right;
            rightChild.x = p.x + innerSpacing;
            rightChild.y = -currentLevel;

            q.addTail(rightChild);

        }
        
        
    }
}


#endif