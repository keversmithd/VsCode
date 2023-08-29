#ifndef RBSTree_H_DIST
#define RBSTree_H_DIST


#include "Chapter2Dcel/Dcel.h"
#include <queue>

enum RBSColor { RED_BS = 1, BLACK_BS = 0 };

template<typename T>
struct RBSNode {
    T val; // data
    RBSColor color; // 1-RED_BS, 0-BLACK_BS
    RBSNode<T>* parent = nullptr; // parent
    RBSNode<T>* right = nullptr; // right-child
    RBSNode<T>* left = nullptr; // left child

    RBSNode<T>(T n)
    {
        val = n;
        color = RED_BS;
    }
        // returns pointer to uncle
    RBSNode<T>* uncle() 
    {
        if (parent == nullptr || parent->parent == nullptr)
        {
            return nullptr;
        }
        if (parent->isOnLeft())
        {
            return parent->parent->right; //different parent, aunt or uncle, or parents sibling.
        }
        else
        {
            return parent->parent->left;
        }  
  }
    
    // check if node is left child of parent
  bool isOnLeft() { return this == parent->left; }
 
  // returns pointer to sibling
  RBSNode<T> *sibling() {
    // sibling nullptrptr if no parent
    if (parent == nullptr)
      return nullptr;
 
    if (isOnLeft())
      return parent->right;
 
    return parent->left; //gets siblying.
  }
 
  void moveDown(RBSNode<T> *nParent) {

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

  bool hasredChild() {
    return (left != nullptr && left->color == RED_BS) ||
           (right != nullptr && right->color == RED_BS);
  }
};



struct RBSTree{
public:
    RBSNode<DCELEdge*>* root;
    int elements;
    int(*compare)(DCELEdge* a, DCELEdge* b, float status);


public:
  //testing
  

public:
  //priorty queue

  RBSNode<DCELEdge*>* peek()
  {

    if(root == nullptr)
    {
        return nullptr;
    }

    RBSNode<DCELEdge*>* least = root;

    while(least->left != nullptr)
    {
      least = least->left;
    }

    return least;
  }

  DCELEdge* removeTop()
  {

    if(root == nullptr)
    {
        throw std::range_error("nothing to remove");
        return nullptr;
    }

    RBSNode<DCELEdge*>* least = peek();

    DCELEdge* temp = least->val;
    deleteNode(least);
    return temp;

  }

  bool empty()
  {
    return elements > 0;
  }

public:
    RBSTree(int(*comp)(DCELEdge* a, DCELEdge* b, float status)) : root(nullptr), elements(0), compare(comp)
    {

    }
    void leftRotate(RBSNode<DCELEdge*> *x) {

        RBSNode<DCELEdge*> *nParent = x->right;
  
        if (x == root)
            root = nParent;
    
        x->moveDown(nParent); // replace x right with nParent which is x->right
    
        
        x->right = nParent->left;  //replace x->right with its previous left child


        if (nParent->left != nullptr) //if it exists
            nParent->left->parent = x; //then this left childs parent is now x

        //replace x with x right, replace x right with x->right->left
    
        nParent->left = x;
    }
    void rightRotate(RBSNode<DCELEdge*> *x) {
        // new parent will be node's left child
        RBSNode<DCELEdge*> *nParent = x->left;
    
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
 
  void swapColors(RBSNode<DCELEdge*> *x1, RBSNode<DCELEdge*> *x2) {
    RBSColor temp;
    temp = x1->color;
    x1->color = x2->color;
    x2->color = temp;
  }
 
  void swapValues(RBSNode<DCELEdge*> *u, RBSNode<DCELEdge*> *v) {
    DCELEdge* temp;
    temp = u->val;
    u->val = v->val;
    v->val = temp;
  }
 
  // fix RED_BS RED_BS at given node
  void fixRED_BSRED_BS(RBSNode<DCELEdge*> *x) {
    // if x is root color it BLACK_BS and return

    if (x == root) { //sends root in anyways, when it could not
      x->color = BLACK_BS;
      return;
    }
 
    // initialize parent, grandparent, uncle
    RBSNode<DCELEdge*> *parent = x->parent, *grandparent = parent->parent, *uncle = x->uncle();
 
    if (parent->color != BLACK_BS) { //uses recursion up instead of stack down
      if (uncle != nullptr && uncle->color == RED_BS) {
        // uncle RED_BS, perform recoloring and recurse
        parent->color = BLACK_BS;
        uncle->color = BLACK_BS;
        grandparent->color = RED_BS;
        fixRED_BSRED_BS(grandparent);
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
 
  // find node that do not have a left child
  // in the subtree of the given node
  RBSNode<DCELEdge*> *successor(RBSNode<DCELEdge*> *x) {
    RBSNode<DCELEdge*> *temp = x;
 
    while (temp->left != nullptr)
        temp = temp->left;
 
    return temp;
  }
 
  // find node that replaces a deleted node in BST
  RBSNode<DCELEdge*> *BSTreplace(RBSNode<DCELEdge*> *x) {
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
 
  // deletes the given node
  void deleteNode(RBSNode<DCELEdge*> *v) {
    RBSNode<DCELEdge*> *u = BSTreplace(v);
 
    // True when u and v are both BLACK_BS
    bool uvBLACK_BS = ((u == nullptr or u->color == BLACK_BS) && (v->color == BLACK_BS));
    RBSNode<DCELEdge*> *parent = v->parent;
 
    if (u == nullptr) {
      // u is nullptr therefore v is leaf
      if (v == root) {
        // v is root, making root nullptr
        root = nullptr;
      } else {
        if (uvBLACK_BS) {
          // u and v both BLACK_BS
          // v is leaf, fix double BLACK_BS at v
          fixDoubleBLACK_BS(v);
        } else {
          // u or v is RED_BS
          if (v->sibling() != nullptr)
            // sibling is not nullptr, make it RED_BS"
            v->sibling()->color = RED_BS;
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
        v->val = u->val;
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
        if (uvBLACK_BS) {
          // u and v both BLACK_BS, fix double BLACK_BS at u
          fixDoubleBLACK_BS(u);
        } else {
          // u or v RED_BS, color u BLACK_BS
          u->color = BLACK_BS;
        }
      }
      return;
    }
 
    // v has 2 children, swap values with successor and recurse
    swapValues(u, v);
    deleteNode(u);
  }

  bool remove(DCELEdge* value)
  {
    if(root == nullptr)
    {
        return false;
    }

    bool found = false;
    RBSNode<DCELEdge*>* iterativeNode = root;

    while(found == false && iterativeNode != nullptr)
    {
        if(value < iterativeNode->val)
        {
            iterativeNode = iterativeNode->left;
        }else
        if(value > iterativeNode->val)
        {
            iterativeNode = iterativeNode->right;
        }else
        {
            found = true;
        }
    }

    if(found == true)
    {
        deleteNode(iterativeNode);
    }

  }
    
  void fixDoubleBLACK_BS(RBSNode<DCELEdge*> *x) {
    if (x == root)
      // Reached root
      return;
 
    RBSNode<DCELEdge*> *sibling = x->sibling(), *parent = x->parent;
    if (sibling == nullptr) {
      // No sibling, double BLACK_BS pushed up
      fixDoubleBLACK_BS(parent);
    } else {
      if (sibling->color == RED_BS) {
        // Sibling RED_BS
        parent->color = RED_BS;
        sibling->color = BLACK_BS;
        if (sibling->isOnLeft()) {
          // left case
          rightRotate(parent);
        } else {
          // right case
          leftRotate(parent);
        }
        fixDoubleBLACK_BS(x);
      } else {
        // Sibling BLACK_BS
        if (sibling->hasredChild()) {
          // at least 1 RED_BS children
          if (sibling->left != nullptr and sibling->left->color == RED_BS) {
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
          parent->color = BLACK_BS;
        } else {
          // 2 BLACK_BS children
          sibling->color = RED_BS;
          if (parent->color == BLACK_BS)
            fixDoubleBLACK_BS(parent);
          else
            parent->color = BLACK_BS;
        }
      }
    }
  }
 
 
public:
  RBSNode<DCELEdge*> *getRoot() { return root; }
 
  // searches for given value
  // if found returns the node (used for delete)
  // else returns the last node while traversing (used in insert)

  RBSNode<DCELEdge*> *search(DCELEdge* n, int& lr, float status) {

    RBSNode<DCELEdge*> *temp = root;
    int compar = 0;
    while (temp != nullptr) {
      compar = compare(n, temp->val, status);
      if (compar == 1) {
        if (temp->left == nullptr)
        {
          lr = 1;
          break;
        } else {
          temp = temp->left;
        }
        } else if (compar == 0) {
          lr = 0;
          break;
        } else if (compar == 2)
        {
          lr = 2;
          break;
        }
        else
        {
            temp = temp->right;
        }  
      }
      return temp;
    
  }
 

  void CheckIntersectionsOfNode(RBSNode<DCELEdge*>* node, int level = 0)
  {
    if(node == nullptr || level > 4)
    {
      return ;
    }


    //if intersection point is the vertex of the edge here
    bool IntersectionStatus = false;
    Vec IntersectionPoint;
    if(node->left)
    {
      IntersectionStatus = ParametricIntersection(node->val, node->left->val, IntersectionPoint);
      if(IntersectionStatus)
      {

      }
    }

    if(node->right)
    {
      IntersectionStatus = ParametricIntersection(node->val, node->right->val, IntersectionPoint);
      if(IntersectionStatus)
      {
        //register intersection point
      }
    }
    
    level++;
    CheckIntersectionsOfNode(node->left, level);
    CheckIntersectionsOfNode(node->right, level);
  }

  RBSNode<DCELEdge*> *searchAndIntersect(DCELEdge* n,  int& lr, float status)
  {
    std::vector<Vec> IntersectionPoints;

    RBSNode<DCELEdge*> *temp = root;
    int compar = 0;
    while (temp != nullptr) {
      
      CheckIntersectionsOfNode(temp, 4);
      compar = compare(n, temp->val, status);
      if (compar == 1) {
        if (temp->left == nullptr)
        {
          lr = 1;
          break;
        } else {
          temp = temp->left;
        }
        } else if (compar == 0) {
          lr = 0;
          break;
        } else if (compar == 2)
        {
          lr = 2;
          break;
        }
        else
        {
            temp = temp->right;
        }  
      }
      return temp;
  }

  // inserts the given value to tree
  void insert(DCELEdge* n, float status) {
    
    RBSNode<DCELEdge*> *newNode = new RBSNode<DCELEdge*>(n); //default is RED_BS even though should be opposite of parent
    if (root == nullptr) {
      // when root is nullptr
      // simply insert value at root
      newNode->color = BLACK_BS; //if root its BLACK_BS
      root = newNode;
      elements++;
    } else {
      int lr = 0;
      RBSNode<DCELEdge*> *temp = search(n, lr, status);
 
      if (lr == 0) {
        // return if value already exists
        return;
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
      fixRED_BSRED_BS(newNode);
      elements++;
    }
  }


  
 
  // utility function that deletes the node with given value
  // void deleteByVal(int n, float status) {
  //   if (root == nullptr)
  //     // Tree is empty
  //     return;
 
  //   RBSNode<DCELEdge*> *v = search(n, status), *u;
 
  //   if (v->val != n) {
  //     //cout << "No node found to delete with value:" << n << endl;
  //     return;
  //   }
 
  //   deleteNode(v);
  // }
 
//   // prints inorder of the tree
//   void printInOrder() {
//     cout << "Inorder: " << endl;
//     if (root == nullptr)
//       cout << "Tree is empty" << endl;
//     else
//       inorder(root);
//     cout << endl;
//   }
 
//   // prints level order of the tree
//   void printLevelOrder() {
//     cout << "Level order: " << endl;
//     if (root == nullptr)
//       cout << "Tree is empty" << endl;
//     else
//       levelOrder(root);
//     cout << endl;
//   }
};

#endif