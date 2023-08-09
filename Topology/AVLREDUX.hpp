#ifndef AVLREDUX_H
#define AVLREDUX_H

#include "Deque.hpp"

template<typename T>
struct avl_node
{
    T value;
    int height;
    avl_node *left = nullptr;
    avl_node *right = nullptr;

    void setThis(avl_node<T>* t)
    {
        this = t;
    }
};

struct avl_parent_box
{
    double x, y;
};

template<typename T>
struct avl_node_parent
{
    double x, y;
    avl_node<T>* node = nullptr;
    avl_parent_box parent;

};

template<typename T>
struct avl_tree
{
    avl_node<T>* root;
    
    int elements;
    int(*c)(const T a, const T b);


    avl_tree(int(*Compare)(const T a, const T b)) : root(nullptr) , elements(0)
    {
        if(Compare == nullptr)
        {
            throw ("Bad");
        }
        c = Compare;
    }

    void ll_rotate(avl_node<T>*& parent)
    {
        avl_node<T>* pr = parent->left;
        parent->left = pr->right;
        pr->right = parent;

        if(pr != nullptr)
        {
            pr->height++;
        }
        parent->height--;

        parent = pr;
    }

    void rr_rotate(avl_node<T>*& parent)
    {
        avl_node<T>* pl = parent->right;
        parent->right = pl->left;
        pl->left = parent;

        if(pl != nullptr)
        {
            pl->height++;
        }
        parent->height--;

        parent = pl;
    }

    void lr_rotate(avl_node<T>*& parent)
    {
        avl_node<T>* t = parent->left;
        rr_rotate(t);
        ll_rotate(parent);
    }
    void rl_rotate(avl_node<T>*& parent)
    {
        avl_node<T>* t = parent->right;
        ll_rotate(t);
        rr_rotate(parent);
    }

    int height(avl_node<T>* t)
    {
        //will traverse all the way down the nodal tree, and basically count all of the nodes until it isn't nullptr.
        int h = 0;
        if(t != nullptr)
        {
            int l_height = (t->left) ? t->left->height : 0;
            int r_height = (t->right) ? t->right->height : 0;
            int max_height = (l_height > r_height) ? l_height : r_height;
            h = max_height;
        }
        return h;
    }

    int difference(avl_node<T>* t) //log n
    {
        if(t != nullptr)
        {
            int l_height = height(t->left);
            int r_height = height(t->right);
            int b_factor = l_height-r_height;
            return b_factor + 1;
        }

        return 0;
    }

    void balance(avl_node<T>*& t)
    {
        int bal_facotr = difference(t);
        if(bal_facotr > 1)
        {
            if(difference(t->left) > 0)
                ll_rotate(t);
            else
                lr_rotate(t);
        }else if (bal_facotr < -1)
        {
            if(difference(t->right) > 0)
                rl_rotate(t);
            else
                rr_rotate(t);
        }

    }


    void insert(T value)
    {
        //assuming that the value is not a duplicate
        if(root == nullptr)
        {
            root = new avl_node<T>();
            root->value = value;
            root->left = nullptr;
            root->right = nullptr;
            root->height = 0;
            return;

        } else
        {
            Deque<avl_node<T>**> fixStack;
            int compare = 0;
            
            avl_node<T>* searchOrb = root;
            avl_node<T>* searchParent = nullptr;
            int lr = 0;

            while(searchOrb != nullptr)
            {
                compare = c(value, searchOrb->value);
                if (compare == 1)
                {  
                    fixStack.addTail(&searchOrb);
                    searchParent = searchOrb;
                    searchParent->height++;
                    searchOrb = searchOrb->left; 
                    lr = 0;
                    
                }else if (compare == 2)
                {
                    fixStack.addTail(&searchOrb);
                    searchParent = searchOrb;
                    searchParent->height++;
                    searchOrb = searchOrb->right;
                    lr = 1;
                    
                }else{
                    
                    while(!fixStack.isEmpty())
                    {
                        //fixStack.removeTail()->height--;
                    }
                    return;
                } 

            }


            searchOrb = new avl_node<T>();
            searchOrb->value = value;
            searchOrb->left = nullptr;
            searchOrb->right = nullptr;
            searchOrb->height = 0;

            (lr == 0) ? searchParent->left = searchOrb : searchParent->right = searchOrb;
            elements++;

            while(!fixStack.isEmpty())
            {
                avl_node<T>** balancingNode = fixStack.removeTail();
                balance(*balancingNode);

                int chekc = 0;
            }

        }


        
    }


    void texorder()
    {
        if(root == nullptr)
        {
            return;
        }

        int initalSpacing = log2(elements);

        Deque<avl_node_parent<T>> q;

        int nodeproccessed = 3;
        int currentLevel = log2(nodeproccessed);
        int tLevel = currentLevel;

        double ypad = 1.0;
        double y = 0.0;



        avl_node_parent<T> origin;
        origin.node = root;
        origin.parent = {0,0};
        origin.x = 0;
        origin.y = 0;
        

        printf("\\draw (%f,%f) circle (10pt) [] node {%d}; \n", origin.x, origin.y, root->height);

        if(root != nullptr && root->left != nullptr)
        {
            avl_node_parent<T> left;;
            left.node = root->left;
            left.parent = {origin.x, origin.y};
            left.x = -initalSpacing;
            left.y = -1;
            q.addTail(left);
        }

        if(root != nullptr && root->right != nullptr)
        {
            avl_node_parent<T> right;
            right.node = root->right;
            right.parent = {origin.x, origin.y};
            right.x = initalSpacing;
            right.y = -1;
            q.addTail(right);
        }
        

        while(!q.isEmpty())
        {
            
            avl_node_parent<T> p = q.removeHead();
            nodeproccessed++;
            if(p.node != nullptr)
            {
                printf("\\draw ($(%f, %f)+(275:10pt)$) -- ($(%f, %f)+(90:10pt)$);\n", p.parent.x, p.parent.y, p.x, p.y);
                printf("\\draw (%f, %f) circle(10pt) [] node {%d};\n", p.x, p.y, p.node->height);
                
                currentLevel = abs(p.y - 1);
                
                double innerSpacing = abs(p.x - p.parent.x)/2.0;

                avl_node_parent<T> leftChild;
                leftChild.parent = {p.x,p.y};
                leftChild.node = p.node->left;
                leftChild.x = p.x - innerSpacing;
                leftChild.y = -currentLevel;

                
                q.addTail(leftChild);

                avl_node_parent<T> rightChild;
                rightChild.parent = {p.x, p.y};
                rightChild.node = p.node->right;
                rightChild.x = p.x + innerSpacing;
                rightChild.y = -currentLevel;

                q.addTail(rightChild);

            }
            
            
        }



    }


};

#endif