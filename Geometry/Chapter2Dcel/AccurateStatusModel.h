#ifndef ACCURATE_STATUS_MODEL_H
#define ACCURATE_STATUS_MODEL_H

#include "DCELIntersection.hpp"
#include <unordered_set>


struct StatusNode
{
    DCELEdge* edge;
    int color;  //1 red, 2 black
    StatusNode* parent = nullptr; // parent
    StatusNode* left;
    StatusNode* right;
    
    StatusNode() : left(nullptr), right(nullptr)
    {

    }
    StatusNode(DCELEdge* _edge) : edge(_edge), left(nullptr), right(nullptr)
    {

    }

    bool isOnLeft() 
    { 
        if(parent)
            return this == parent->left; 
        return false;
    }

    StatusNode* uncle()
    {
        if(parent && parent-parent)
        {
            if(parent->isOnLeft())
            {
                return parent->parent->right;
            }else
            {
                return parent->parent->left;
            }
        }

        return nullptr;

    }

    StatusNode *sibling() {
    // sibling nullptrptr if no parent
        if (parent == nullptr)
            return nullptr;
    
        if (isOnLeft())
            return parent->right;
    
        return parent->left; //gets siblying.
    }

    void moveDown(StatusNode *nParent) {

    if (parent != nullptr) {

      if (isOnLeft()) { //replace this node
        parent->left = nParent;
      } else {
        parent->right = nParent;
      }

    }

    nParent->parent = parent; 
    parent = nParent; 
  }


    bool isLeaf()
    {
        return (left == nullptr && right == nullptr);
    }

    bool HasRedChild() {
        return (left != nullptr && left->color == 1) || (right != nullptr && right->color == 1);
    }

};

int OrientationSpace(DCELEdge* a, DCELEdge* b)
{

    DeconstructedEdge au = DeconstructEdge(a);
    DeconstructedEdge bu = DeconstructEdge(b);

    Vec ao = au.UpperEndPoint;
    Vec at = au.LowerEndPoint;

    Vec bo = bu.UpperEndPoint;
    Vec bt = bu.LowerEndPoint;

    Vec av = a->twin->origin->vertex - a->origin->vertex;
    Vec bv = b->twin->origin->vertex - b->origin->vertex;

    float da0 = cross(ao,bv);
    float da1 = cross(at,bv);

    float db0 = cross(bo,av);
    float db1 = cross(bt,av);

    

    if(da0 > 0 && da1 > 0)
    {
        return 2;
    }else if(da0 > 0 && da1 < 0)
    {
        return 1;
    }else if(da0 < 0 && da1 > 0)
    {
        //a is right, b is left
    }



}



struct IntersectionSet
{
    std::unordered_set<DCELEdge*> L;
    std::unordered_set<DCELEdge*> C;

    void Clear()
    {
        L.clear();
        C.clear();
    }
};

struct StatusTree
{
    StatusNode* root;
    int elements;
    StatusTree() : root(nullptr)
    {

    }

    #pragma region TREE_FUNCTIONS
    void leftRotate(StatusNode *x) {

        StatusNode* nParent = x->right;
  
        if (x == root)
            root = nParent;
    
        x->moveDown(nParent); // replace x right with nParent which is x->right
    
        
        x->right = nParent->left;  //replace x->right with its previous left child


        if (nParent->left != nullptr) //if it exists
            nParent->left->parent = x; //then this left childs parent is now x

        //replace x with x right, replace x right with x->right->left
    
        nParent->left = x;
    }
    void rightRotate(StatusNode* x) {
        // new parent will be node's left child
        StatusNode* nParent = x->left;
    
        // update root if current node is root
        if (x == root)
            root = nParent;
    
        x->moveDown(nParent);
    
        // connect x with new parent's right element
        x->left = nParent->right;
        // connect new parent's right element with node
        // if it is not nullptr
        if (nParent->right != nullptr)
            nParent->right->parent = x;
    
        // connect new parent with x
        nParent->right = x;
    }

    void swapColors(StatusNode* x1, StatusNode* x2) {
        int temp;
        temp = x1->color;
        x1->color = x2->color;
        x2->color = temp;
    }

    void swapValues(StatusNode* u, StatusNode* v) {
        DCELEdge* temp;
        temp = u->edge;
        u->edge = v->edge;
        v->edge = temp;
    }

    void fixRedRed(StatusNode* x) {
        // if x is root color it BLACK_BS and return
        if (x == root) { //sends root in anyways, when it could not
            x->color = 0;
            return;
        }
    
        // initialize parent, grandparent, uncle
        StatusNode* parent = x->parent, *grandparent = parent->parent, *uncle = x->uncle();
    
        if (parent->color != 0) { //uses recursion up instead of stack down
            if (uncle != nullptr && uncle->color == 1) {
                // uncle RED_BS, perform recoloring and recurse
                parent->color = 0;
                uncle->color = 0;
                grandparent->color = 1;
                fixRedRed(grandparent);
            } else {
                // Else perform LR, LL, RL, RR
                if (parent->isOnLeft()) {
                if (x->isOnLeft()) {
                    // for left right
                    swapColors(parent, grandparent);
                } else {
                    leftRotate(parent);
                    swapColors(x, grandparent);
                }
                // for left left and left right
                rightRotate(grandparent);
                } else {
                if (x->isOnLeft()) {
                    // for right left
                    rightRotate(parent);
                    swapColors(x, grandparent);
                } else {
                    swapColors(parent, grandparent);
                }
        
                // for right right and right left
                leftRotate(grandparent);
                }

            }
        }
        
    }

    void fixDoubleBlack(StatusNode* x) 
    {
        if (x == root)
        {
            return;
        }

        StatusNode* sibling = x->sibling(), *parent = x->parent;
        if (sibling == nullptr) 
        {
            // No sibling, double BLACK_BS pushed up
            fixDoubleBlack(parent);

        } else {
            if (sibling->color == 1) {
                // Sibling RED_BS
                parent->color = 1;
                sibling->color = 1;
            if (sibling->isOnLeft()) {
            // left case
                rightRotate(parent);
            } else {
            // right case
                leftRotate(parent);
            }
            fixDoubleBlack(x);
            } else {
                // Sibling BLACK_BS
                if (sibling->HasRedChild()) {
                // at least 1 RED_BS children
                    if (sibling->left != nullptr and sibling->left->color == 1) {
                        if (sibling->isOnLeft()) {
                            // left left
                            sibling->left->color = sibling->color;
                            sibling->color = parent->color;
                            rightRotate(parent);
                        } else {
                            // right left
                            sibling->left->color = parent->color;
                            rightRotate(sibling);
                            leftRotate(parent);
                        }
                    } else {
                        if (sibling->isOnLeft()) {
                            // left right
                            sibling->right->color = parent->color;
                            leftRotate(sibling);
                            rightRotate(parent);
                        } else {
                            // right right
                            sibling->right->color = sibling->color;
                            sibling->color = parent->color;
                            leftRotate(parent);
                        }
                    }

                    parent->color = 0;
                } else {
                    sibling->color = 0;
                    if (parent->color == 0)
                    {
                        fixDoubleBlack(parent);
                    }
                    else
                    {
                        parent->color = 0;
                    }
                        
                }
            }
        }
    }

    StatusNode* successor(StatusNode* x) {
        StatusNode* temp = x;
 
        while (temp->left != nullptr)
            temp = temp->left;
    
        return temp;
    }

    StatusNode* BSTreplace(StatusNode* x) {
        // when node have 2 children
        if (x->left != nullptr and x->right != nullptr)
            return successor(x->right);
    
        // when leaf
        if (x->left == nullptr and x->right == nullptr)
            return nullptr;
    
        // when single child
        if (x->left != nullptr)
            return x->left;
        else
            return x->right;
    }

    void deleteNode(StatusNode* v) {
        StatusNode* u = BSTreplace(v);
    
        // True when u and v are both BLACK_BS
        bool uvBlack = ((u == nullptr or u->color == 0) && (v->color == 0));
        StatusNode* parent = v->parent;
    
        if (u == nullptr) {
            // u is nullptr therefore v is leaf
            if (v == root) {
                // v is root, making root nullptr
                root = nullptr;
            } else {
                if (uvBlack) {

                    fixDoubleBlack(v);
                } else {
                    // u or v is RED_BS
                    if (v->sibling() != nullptr)
                        // sibling is not nullptr, make it RED_BS"
                        v->sibling()->color = 1;
                    }
            
                    // delete v from the tree
                    if (v->isOnLeft()) {
                        parent->left = nullptr;
                    } else {
                        parent->right = nullptr;
                    }
            }
            delete v;
            return;
        }
    
        if (v->left == nullptr or v->right == nullptr) {
            // v has 1 child
            if (v == root) {
                // v is root, assign the value of u to v, and delete u
                v->edge= u->edge;
                v->left = v->right = nullptr;
                delete u;
            } else {
                // Detach v from tree and move u up
                if (v->isOnLeft()) {
                    parent->left = u;
                } else {
                    parent->right = u;
                }

                delete v;
                u->parent = parent;
                if (uvBlack) {
                // u and v both BLACK_BS, fix double BLACK_BS at u
                    fixDoubleBlack(u);
                } else {
                // u or v RED_BS, color u BLACK_BS
                 u->color = 0;
                }
            }
            return;
        }
    
        // v has 2 children, swap values with successor and recurse
        swapValues(u, v);
        deleteNode(u);
  }

    void remove(DCELEdge* e)
    {
        int lrSt;
        StatusNode* pred = explicitsearch(e, lrSt);
        if(lrSt == 0)
        {
            deleteNode(pred);
            elements--;
        }

        
        
    }

    StatusNode* explicitsearch(DCELEdge* n, int& lr) 
    {
        StatusNode* temp = root;
        StatusNode* p;
        int compar = 0;
        while (temp != nullptr) {
            compar = OrientationSpace(n, temp->edge);
            if (compar == 1) {
                p = temp;
                lr = 1;
                temp = temp->left;
            } else if (compar == 0) {
                lr = 0;
                p = temp;
                temp = nullptr;
            } else if (compar == 2)
            {
                p = temp;
                lr = 2;
                temp = temp->right;
            } 
        }

        return p;
    }

    StatusNode* insert(DCELEdge* n) {
        
        StatusNode* newNode = new StatusNode(n); //default is RED_BS even though should be opposite of parent
        if (root == nullptr) {
            // when root is nullptr
            // simply insert value at root
            newNode->color = 0; //if root its BLACK_BS
            root = newNode;
            elements++;
        } else {
            int lr = 0;

            StatusNode* temp = explicitsearch(n, lr);
        
            if (lr == 0) {
                // return if value already exists
                return nullptr;
            }
        
            // if value is not found, search returns the node
            // where the value is to be inserted
        
            // connect new node to correct node
            newNode->parent = temp;
        
            if (lr == 1)
                temp->left = newNode;
            else
                temp->right = newNode;
        
            // fix RED_BS RED_BS violation if exists
            fixRedRed(newNode);
            elements++;

            return newNode;
        }
    }

    #pragma endregion

    int NodalRelation(DCELVec* eventPoint, DCELEdge* statusEdge)
    {
        DeconstructedEdge e = DeconstructEdge(statusEdge);
        Vec a = eventPoint->vertex;

        if(a == e.UpperEndPoint)
        {
            return 0;
        }
        else if(a == e.LowerEndPoint)
        {
            return 1;
        }else if(statusEdge->Contains(eventPoint))
        {
            return 2;
        }
    }

    
    bool Empty()
    {
        return (elements == 0);
    }
    void AllWhichContain(DCELVec* point, IntersectionSet& Sets)
    {
        StatusNode* u = root, *prev = nullptr, *next = nullptr;
        

        int RelationStatus;
        while(u != nullptr) //while u not nullptr
        {
            if(prev == u->parent) //the root will always match this clause and go left, will then go left again and so on until no nodes, and then will come back to the root.
            {
                RelationStatus = NodalRelation(point, u->edge);
                if(RelationStatus == 0)
                {
                    
                }else if(RelationStatus == 1)
                {
                    Sets.L.insert(u->edge);
                }else if(RelationStatus == 2)
                {
                    Sets.C.insert(u->edge);
                }

                if(u->left != nullptr) next = u->left; //use left
                else if(u->right != nullptr) next = u->right; //or use right
                else next = u->parent; //okay just use parent

            }else if (prev == u->left) //other wise if prev was a left, then go right
            {
                if (u->right != nullptr) next = u->right; //use right
                else next = u->parent; //okay just use a parent
            }else
            {
                //visit here
                next = u->parent; //otherwise u = parent
            }

            prev = u; //prev equals previous
            u = next; //u = next
        }
    }

};


template<typename T>
void Union(std::unordered_set<T>& A, std::unordered_set<T>& B, std::unordered_set<T>& C)
{


    for(auto it = A.begin(); it != A.end(); it++)
    {
        T v = *it;
        C.insert(v);
    }

    for(auto it = B.begin(); it != B.end(); it++)
    {
        T v = *it;
        C.insert(v);
    }
}

#endif