#ifndef RBSTree_H_DIST
#define RBSTree_H_DIST
#include <queue>

enum RBSColor { RED = 1, BLACK = 0 };

template<typename T>
struct RBSNode {
    T val; // data
    RBSColor color; // 1-red, 0-black
    RBSNode<T>* parent = nullptr; // parent
    RBSNode<T>* right = nullptr; // right-child
    RBSNode<T>* left = nullptr; // left child

    RBSNode<T>(T n)
    {
        val = n;
        color = RED;
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

  bool hasRedChild() {
    return (left != nullptr && left->color == RED) ||
           (right != nullptr && right->color == RED);
  }
};


template<typename T>
struct RBSTree{
public:
    RBSNode<T>* root;
    int elements;
    int(*compare)(T a, T b, float status);


public:
  //testing
  

public:
  //priorty queue

  RBSNode<T>* peek()
  {

    if(root == nullptr)
    {
        return nullptr;
    }

    RBSNode<T>* least = root;

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

    RBSNode<T>* least = peek();

    T temp = least->val;
    deleteNode(least);
    return temp;

  }

  bool empty()
  {
    return elements > 0;
  }

public:
    RBSTree(int(*comp)(T a, T b, float status)) : root(nullptr), elements(0), compare(comp)
    {

    }
    void leftRotate(RBSNode<T> *x) {

        RBSNode<T> *nParent = x->right;
  
        if (x == root)
            root = nParent;
    
        x->moveDown(nParent); // replace x right with nParent which is x->right
    
        
        x->right = nParent->left;  //replace x->right with its previous left child


        if (nParent->left != nullptr) //if it exists
            nParent->left->parent = x; //then this left childs parent is now x

        //replace x with x right, replace x right with x->right->left
    
        nParent->left = x;
    }


    void rightRotate(RBSNode<T> *x) {
        // new parent will be node's left child
        RBSNode<T> *nParent = x->left;
    
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
 
  void swapColors(RBSNode<T> *x1, RBSNode<T> *x2) {
    RBSColor temp;
    temp = x1->color;
    x1->color = x2->color;
    x2->color = temp;
  }
 
  void swapValues(RBSNode<T> *u, RBSNode<T> *v) {
    T temp;
    temp = u->val;
    u->val = v->val;
    v->val = temp;
  }
 
  // fix red red at given node
  void fixRedRed(RBSNode<T> *x) {
    // if x is root color it black and return

    if (x == root) { //sends root in anyways, when it could not
      x->color = BLACK;
      return;
    }
 
    // initialize parent, grandparent, uncle
    RBSNode<T> *parent = x->parent, *grandparent = parent->parent, *uncle = x->uncle();
 
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
  RBSNode<T> *successor(RBSNode<T> *x) {
    RBSNode<T> *temp = x;
 
    while (temp->left != nullptr)
        temp = temp->left;
 
    return temp;
  }
 
  // find node that replaces a deleted node in BST
  RBSNode<T> *BSTreplace(RBSNode<T> *x) {
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
  void deleteNode(RBSNode<T> *v) {
    RBSNode<T> *u = BSTreplace(v);
 
    // True when u and v are both black
    bool uvBlack = ((u == nullptr or u->color == BLACK) && (v->color == BLACK));
    RBSNode<T> *parent = v->parent;
 
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
    RBSNode<T>* iterativeNode = root;

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
    
  void fixDoubleBlack(RBSNode<T> *x) {
    if (x == root)
      // Reached root
      return;
 
    RBSNode<T> *sibling = x->sibling(), *parent = x->parent;
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
  RBSNode<T> *getRoot() { return root; }
 
  // searches for given value
  // if found returns the node (used for delete)
  // else returns the last node while traversing (used in insert)

  RBSNode<T> *search(T n, int& lr, float status) {

    RBSNode<T> *temp = root;
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
 

  void CheckIntersectionsOfNode(RBSNode<T>* node, int level = 0)
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
      IntersectionStatus = ParametricIntersection(node->val, node->left->val, IntersectionStatus);
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

  RBSNode<T> *searchAndIntersect(T n,  int& lr, float status)
  {
    std::vector<Vec> IntersectionPoints;

    RBSNode<T> *temp = root;
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
  void insert(T n, float status) {
    RBSNode<T> *newNode = new RBSNode<T>(n); //default is red even though should be opposite of parent
    if (root == nullptr) {
      // when root is nullptr
      // simply insert value at root
      newNode->color = BLACK; //if root its black
      root = newNode;
      elements++;
    } else {
      int lr = 0;
      RBSNode<T> *temp = search(n, lr, status);
 
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
 
    RBSNode<T> *v = search(n), *u;
 
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