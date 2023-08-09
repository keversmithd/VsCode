#ifndef DISTANCE_BASED_TREE
#define DISTANCE_BASED_TREE
#include <queue>

enum COLOR { RED = 1, BLACK = 0 };

template<typename T>
struct RBNode {
    T val; // data
    COLOR color; // 1-red, 0-black
    RBNode<T>* parent = nullptr; // parent
    RBNode<T>* right = nullptr; // right-child
    RBNode<T>* left = nullptr; // left child

    RBNode<T>(T n)
    {
        val = n;
        color = RED;
    }
        // returns pointer to uncle
    RBNode<T>* uncle() 
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
  RBNode<T> *sibling() {
    // sibling nullptrptr if no parent
    if (parent == nullptr)
      return nullptr;
 
    if (isOnLeft())
      return parent->right;
 
    return parent->left; //gets siblying.
  }
 
  void moveDown(RBNode<T> *nParent) {

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

  bool hasRedChild() {
    return (left != nullptr && left->color == RED) ||
           (right != nullptr && right->color == RED);
  }
};


template<typename T>
struct RBTree{
public:
    RBNode<T>* root;
    int elements;
    int(*compare)(T a, T b);


public:
  //testing
  

public:
  //priorty queue

  RBNode<T>* peek()
  {

    if(root == nullptr)
    {
        return nullptr;
    }

    RBNode<T>* least = root;

    while(least->left != nullptr)
    {
      least = least->left;
    }

    return least;
  }

  T removeTop()
  {

    if(root == nullptr)
    {
        throw std::range_error("nothing to remove");
        return T();
    }

    RBNode<T>* least = peek();

    T temp = least->val;
    deleteNode(least);
    return temp;

  }

  bool empty()
  {
    return elements > 0;
  }

public:
    RBTree(int(*comp)(T a, T b)) : root(nullptr), elements(0), compare(comp)
    {

    }
    void leftRotate(RBNode<T> *x) {

        RBNode<T> *nParent = x->right;
  
        if (x == root)
            root = nParent;
    
        x->moveDown(nParent); // replace x right with nParent which is x->right
    
        
        x->right = nParent->left;  //replace x->right with its previous left child


        if (nParent->left != nullptr) //if it exists
            nParent->left->parent = x; //then this left childs parent is now x

        //replace x with x right, replace x right with x->right->left
    
        nParent->left = x;
    }


    void rightRotate(RBNode<T> *x) {
        // new parent will be node's left child
        RBNode<T> *nParent = x->left;
    
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
 
  void swapColors(RBNode<T> *x1, RBNode<T> *x2) {
    COLOR temp;
    temp = x1->color;
    x1->color = x2->color;
    x2->color = temp;
  }
 
  void swapValues(RBNode<T> *u, RBNode<T> *v) {
    T temp;
    temp = u->val;
    u->val = v->val;
    v->val = temp;
  }
 
  // fix red red at given node
  void fixRedRed(RBNode<T> *x) {
    // if x is root color it black and return

    if (x == root) { //sends root in anyways, when it could not
      x->color = BLACK;
      return;
    }
 
    // initialize parent, grandparent, uncle
    RBNode<T> *parent = x->parent, *grandparent = parent->parent, *uncle = x->uncle();
 
    if (parent->color != BLACK) { //uses recursion up instead of stack down
      if (uncle != nullptr && uncle->color == RED) {
        // uncle red, perform recoloring and recurse
        parent->color = BLACK;
        uncle->color = BLACK;
        grandparent->color = RED;
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
 
  // find node that do not have a left child
  // in the subtree of the given node
  RBNode<T> *successor(RBNode<T> *x) {
    RBNode<T> *temp = x;
 
    while (temp->left != nullptr)
        temp = temp->left;
 
    return temp;
  }
 
  // find node that replaces a deleted node in BST
  RBNode<T> *BSTreplace(RBNode<T> *x) {
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
  void deleteNode(RBNode<T> *v) {
    RBNode<T> *u = BSTreplace(v);
 
    // True when u and v are both black
    bool uvBlack = ((u == nullptr or u->color == BLACK) && (v->color == BLACK));
    RBNode<T> *parent = v->parent;
 
    if (u == nullptr) {
      // u is nullptr therefore v is leaf
      if (v == root) {
        // v is root, making root nullptr
        root = nullptr;
      } else {
        if (uvBlack) {
          // u and v both black
          // v is leaf, fix double black at v
          fixDoubleBlack(v);
        } else {
          // u or v is red
          if (v->sibling() != nullptr)
            // sibling is not nullptr, make it red"
            v->sibling()->color = RED;
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
        if (uvBlack) {
          // u and v both black, fix double black at u
          fixDoubleBlack(u);
        } else {
          // u or v red, color u black
          u->color = BLACK;
        }
      }
      return;
    }
 
    // v has 2 children, swap values with successor and recurse
    swapValues(u, v);
    deleteNode(u);
  }

  bool remove(T value)
  {
    if(root == nullptr)
    {
        return false;
    }

    bool found = false;
    RBNode<T>* iterativeNode = root;

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
    
  void fixDoubleBlack(RBNode<T> *x) {
    if (x == root)
      // Reached root
      return;
 
    RBNode<T> *sibling = x->sibling(), *parent = x->parent;
    if (sibling == nullptr) {
      // No sibling, double black pushed up
      fixDoubleBlack(parent);
    } else {
      if (sibling->color == RED) {
        // Sibling red
        parent->color = RED;
        sibling->color = BLACK;
        if (sibling->isOnLeft()) {
          // left case
          rightRotate(parent);
        } else {
          // right case
          leftRotate(parent);
        }
        fixDoubleBlack(x);
      } else {
        // Sibling black
        if (sibling->hasRedChild()) {
          // at least 1 red children
          if (sibling->left != nullptr and sibling->left->color == RED) {
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
          parent->color = BLACK;
        } else {
          // 2 black children
          sibling->color = RED;
          if (parent->color == BLACK)
            fixDoubleBlack(parent);
          else
            parent->color = BLACK;
        }
      }
    }
  }
 
 
public:
  RBNode<T> *getRoot() { return root; }
 
  // searches for given value
  // if found returns the node (used for delete)
  // else returns the last node while traversing (used in insert)

  RBNode<T> *search(T n, int& lr) {

    RBNode<T> *temp = root;
    int compar = 0;
    while (temp != nullptr) {
      compar = compare(n, temp->val);
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
  void insert(T n) {
    RBNode<T> *newNode = new RBNode<T>(n); //default is red even though should be opposite of parent
    if (root == nullptr) {
      // when root is nullptr
      // simply insert value at root
      newNode->color = BLACK; //if root its black
      root = newNode;
      elements++;
    } else {
      int lr = 0;
      RBNode<T> *temp = search(n, lr);
 
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
 
      // fix red red violation if exists
      fixRedRed(newNode);
      elements++;
    }
  }
 
  // utility function that deletes the node with given value
  void deleteByVal(int n) {
    if (root == nullptr)
      // Tree is empty
      return;
 
    RBNode<T> *v = search(n), *u;
 
    if (v->val != n) {
      //cout << "No node found to delete with value:" << n << endl;
      return;
    }
 
    deleteNode(v);
  }
 
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