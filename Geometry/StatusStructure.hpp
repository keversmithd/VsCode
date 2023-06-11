#ifndef STATUSBALANCE_H
#define STATUSBALANCE_H
#include <vector>
#include "Deque.hpp"
#include <unordered_set>
#include "LIEventPoint.hpp"
#include <unordered_map>

template<typename T>
struct sb_node
{
    T value;
    sb_node *left = nullptr;
    sb_node *right = nullptr;
};

struct sb_parent_box
{
    double x, y;
};

template<typename T>
struct sb_node_parent
{
    double x, y;
    sb_node<T>* node = nullptr;
    sb_parent_box parent;

};

template<typename T, typename P, typename W>
struct sb_tree
{
    sb_node<T>* root;
    int elements;
    int(*c)(const T a, const T b, float sweepLine);
    int(*z)(const P a, const P b);
    bool(*i_c)(const W a, const P b);
    
    sb_tree(int(*Compare)(const T a, const T b, float sweepLine), int(*PartCompare)(const P a, const P b), bool(*InteriorCompare)(const W a, const P b)) : root(nullptr) , elements(0)
    {
        if(Compare == nullptr || PartCompare == nullptr || InteriorCompare == nullptr)
        {
            throw ("Bad");
        }
        c = Compare;
        z = PartCompare;
        i_c = InteriorCompare;
    }
    int height(sb_node<T>* t)
    {
        //will traverse all the way down the nodal tree, and basically count all of the nodes until it isn't nullptr.
        int h = 0;
        if(t != nullptr)
        {
            int l_height = height(t->left);
            int r_height = height(t->right);
            int max_height = (l_height > r_height) ? l_height : r_height;
            h = max_height+1;
        }
        return h;
    }
    int difference(sb_node<T>* t) //log n
    {
        if(t != nullptr)
        {
            int l_height = height(t->left);
            int r_height = height(t->right);
            int b_factor = l_height-r_height;
            return b_factor;
        }

        return 0;
        
    }
    //Possible optimization of keeping the height of the sub tree at each node
    sb_node<T>* rr_rotate(sb_node<T>* parent)
    {
        sb_node<T>* t = nullptr;
        t = parent->right;
        parent->right = t->left;
        t->left = parent;
        return t;
    }

    sb_node<T>* ll_rotate(sb_node<T>* parent)
    {
        sb_node<T>* t = nullptr;
        t = parent->left;
        parent->left = t->right;
        t->right = parent;

        return t;
    }
    sb_node<T>* lr_rotate(sb_node<T>* parent)
    {
        sb_node<T>* t;
        t = parent->left;
        parent->left = rr_rotate(t);
        return ll_rotate(parent);
    }
    sb_node<T>* rl_rotate(sb_node<T>* parent)
    {
        sb_node<T>* t;
        t = parent->right;
        parent->right = ll_rotate(t);
        return rr_rotate(parent);
    }

    sb_node<T>* balance(sb_node<T>* t)
    {
        int bal_facotr = difference(t);
        if(bal_facotr > 1)
        {
            if(difference(t->left) > 0)
                t = ll_rotate(t);
            else
                t = lr_rotate(t);
        }else if (bal_facotr < -1)
        {
            if(difference(t->right) > 0)
                t = rl_rotate(t);
            else
                t = rr_rotate(t);
        }

        return t;
    }

    void insert(T value)
    {
        
        root = insert(root, value);
        elements++;
        
    }
    sb_node<T>* insert(sb_node<T>* r, T v)
    {
        if(r == nullptr)
        {
            r = new sb_node<T>();
            r->value = v;
            r->left = nullptr;
            r->right = nullptr;
           
            return r;
        } else
        {
            float y = v.part.y;
            int compare = c(v, r->value, y);
            if (compare == -1)
            {
                r->left = insert(r->left, v);
                r = balance(r);
            }else if (compare == 1)
            {
                r->right = insert(r->right, v);
                r = balance(r);
            }else
            {
                elements--;
            }
            
            return r;
        }
        
    }



    void insertCheckAdjacent(T v, std::unordered_map<vec2, doubleline, vec2Hash, vec2Equal>& IntersectionList)
    {
        
        if(root == nullptr)
        {
            root = new sb_node<T>();
            root->value = v;
            root->left = nullptr;
            root->right = nullptr;
            elements++;
            return;
        }
        
        sb_node<T>* iter = root;
        sb_node<T>* parent = nullptr;
        Deque<sb_node<T>*> balanceStack;

        bool lr = false;

        while(iter != nullptr)
        {
            float y = v.part.y;
            int compare = c(v, iter->value, y);
            if (compare == -1)
            {
                balanceStack.addHead(iter);
                parent = iter;
                iter = iter->left;
                lr = false;
                
            }else if (compare == 1)
            {
                balanceStack.addHead(iter);
                parent = iter;
                iter = iter->right;
                lr = true;
            }else
            {
                return;
            }
        }

        iter = new sb_node<T>();
        iter->value = v;
        iter->left = nullptr;
        iter->right = nullptr;
        if(lr)
        {
            parent->right = iter;
        }else{
            parent->left = iter;
        }
        elements++;

        if(parent)
        {
            checkAdjacentIntersections(parent, IntersectionList, v.part.y);
        }


        while(!balanceStack.isEmpty())
        {
            sb_node<T>* unbalanced =  balanceStack.removeHead();
            root = balance(unbalanced);
        }

    }
    

    void checkAdjacentIntersections(sb_node<T>* r, std::unordered_map<vec2, doubleline, vec2Hash, vec2Equal>& IntersectionList, double yline)
    {
        vec2 intersectionPoint1;
        if(r->left && lineIntersection(r->value.whole, r->left->value.whole, intersectionPoint1))
        {
            printf("Intersection Point\n");
            SpellPoint(intersectionPoint1);
            printf("\n");
            if(IntersectionList.find(intersectionPoint1) == IntersectionList.end() && intersectionPoint1.y < yline)
            {
                IntersectionList.insert({intersectionPoint1, {r->value.whole, r->left->value.whole}});
            }
        }

        vec2 intersectionPoint2;
        if(r->right && lineIntersection(r->value.whole, r->right->value.whole, intersectionPoint2) && intersectionPoint2.y < yline)
        {
            printf("Intersection Point\n");
            SpellPoint(intersectionPoint2);
            printf("\n");
            if(IntersectionList.find(intersectionPoint2) == IntersectionList.end())
            {
                IntersectionList.insert({intersectionPoint2, {r->value.whole, r->right->value.whole}});
            }
        }

        vec2 intersectionPoint3;
        if(r->right && r->left && lineIntersection(r->left->value.whole, r->right->value.whole, intersectionPoint3) && intersectionPoint3.y < yline)
        {
            SpellPoint(intersectionPoint3);
            printf("\n");
            if(IntersectionList.find(intersectionPoint3) == IntersectionList.end())
            {
                doubleline insert = {r->left->value.whole, r->right->value.whole};
                IntersectionList.insert({intersectionPoint2, insert});
            }
        }

    }

    void InSetCombination(const T p, std::unordered_set<T, EventPointHash>& U, std::unordered_set<T, EventPointHash>& L, std::unordered_set<T, EventPointHash>& C)
    {
        P point = p.part;
        //binary search for edge with upper point which matches.
        sb_node<T>* iter = root;
        float ylevel = p.part.y;
        sb_node<T>* root = root; //Gather root of tree.
        Deque<sb_node<T>*> s; //Stack

        while(iter != nullptr || !s.isEmpty())
        {
            while(iter != nullptr) //goes down all the way left to last left leaf node, and adds open parenthesis to the stack.
            {
                sb_node<T>* temp = root;
                s.addTail(iter);
                iter = iter->left;
            }

            iter = s.removeTail(); //Gets the top of the node stack.
            
            P upperEndpoint;
            P lowerEndpoint;

            int upperlowerPointCompare = z(iter->value.whole.start, iter->value.whole.end);
            if(upperlowerPointCompare == 1)
            {
                upperEndpoint = iter->value.whole.start;
                lowerEndpoint = iter->value.whole.end;
            }else
            {
                upperEndpoint = iter->value.whole.end;
                lowerEndpoint = iter->value.whole.start;
            }
            
            int i_compare = z(point, upperEndpoint);

            int j_compare = z(point, lowerEndpoint);

            int k_compare = i_c(iter->value.whole, point);

            if(i_compare == 0)
            {
                U.insert(iter->value);
            }
            if(j_compare == 0)
            {
                
                L.insert(iter->value);
            }
            if(k_compare == true)
            {
                C.insert(iter->value);
            }

            iter = iter->right;
        }
    }

    void remove(T v)
    {
        if(root == nullptr){return;}

        W value = v.whole;
        sb_node<T>* removalSearch = root;
        sb_node<T>* parent = nullptr;
        float yline = v.part.y;
        int lr = -1;
        bool removed = false;
        int compare;
        while(removalSearch != nullptr && removed == false)
        {
            compare = c(v, removalSearch->value, yline);
            if(compare == -1)
            {
                parent = removalSearch;
                lr = 0;
                removalSearch = removalSearch->left;
            }else if(compare == 1)
            {
                parent = removalSearch;
                lr = 1;
                removalSearch = removalSearch->right;
            }else
            {
                if(removalSearch->left != nullptr && removalSearch->right != nullptr)
                {
                    sb_node<T>* temp = removalSearch->right;
                    sb_node<T>* p = removalSearch;

                    while(temp->left != nullptr)
                    {
                        p = temp;
                        temp = temp->left;
                    }

                    removalSearch->value = temp->value;
                    if(p == removalSearch)
                    {
                        removalSearch->right = temp->right;
                    }else
                    {
                        p->left = temp->right;
                    }

                    delete temp;
                    elements--;
                    if(elements == 0)
                    {
                        root = nullptr;
                    }
                    removed = true;
                }else
                {
                    sb_node<T>* temp = removalSearch->left ? removalSearch->left : removalSearch->right;
                    if(temp == nullptr)
                    {
                        if(lr == 0)
                        {
                            parent->left = nullptr;
                        }else if(lr == 1)
                        {
                            parent->right = nullptr;
                        }

                        temp = removalSearch;

                    }else
                    {
                        *removalSearch = *temp;
                    }

                    delete temp;

                    elements--;
                    if(elements == 0)
                    {
                        root = nullptr;
                    }
                    removed = true;
                }
            }
        }


        root = balance(root);
    }

    void remove(T v, std::unordered_map<vec2, doubleline, vec2Hash, vec2Equal>& IntersectionList)
    {
        if(root == nullptr){return;}

        W value = v.whole;
        sb_node<T>* removalSearch = root;
        sb_node<T>* parent = nullptr;
        float yline = v.part.y;
        int lr = -1;
        bool removed = false;
        int compare;
        while(removalSearch != nullptr && removed == false)
        {
            compare = c(v, removalSearch->value, yline);
            if(compare == -1)
            {
                parent = removalSearch;
                lr = 0;
                removalSearch = removalSearch->left;
            }else if(compare == 1)
            {
                parent = removalSearch;
                lr = 1;
                removalSearch = removalSearch->right;
            }else
            {
                if(removalSearch->left != nullptr && removalSearch->right != nullptr)
                {
                    sb_node<T>* temp = removalSearch->right;
                    sb_node<T>* p = removalSearch;

                    while(temp->left != nullptr)
                    {
                        p = temp;
                        temp = temp->left;
                    }

                    removalSearch->value = temp->value;
                    if(p == removalSearch)
                    {
                        removalSearch->right = temp->right;
                    }else
                    {
                        p->left = temp->right;
                    }

                    if(parent)
                        checkAdjacentIntersections(parent, IntersectionList, v.part.y);

                    delete temp;
                    elements--;
                    if(elements == 0)
                    {
                        root = nullptr;
                    }
                    removed = true;
                }else
                {
                    sb_node<T>* temp = removalSearch->left ? removalSearch->left : removalSearch->right;
                    if(temp == nullptr)
                    {
                        if(lr == 0)
                        {
                            parent->left = nullptr;
                        }else if(lr == 1)
                        {
                            parent->right = nullptr;
                        }

                        temp = removalSearch;

                    }else
                    {
                        *removalSearch = *temp;
                    }

                    if(parent)
                        checkAdjacentIntersections(parent, IntersectionList, v.part.y);

                    delete temp;

                    elements--;
                    if(elements == 0)
                    {
                        root = nullptr;
                    }
                    removed = true;
                }
            }
        }


        root = balance(root);
    }


    T removeTop()
    {
        if(root == nullptr)
        {
            return T();
        }

        sb_node<T>* parent = nullptr;
        sb_node<T>* current = root;

        while(current->left != nullptr)
        {
            parent = current;
            current = parent->left;
        }

        if(parent == nullptr)
        {
            root = current->right;
        }else
        {
            parent->left = current->right;
        }
        return current->value;
    }
    T peek()
    {
        if(root == nullptr)
        {
            return T();
        }

        sb_node<T>* current = root;
        while(current->left != nullptr)
        {
            current = current->left;
        }

        return current->value;
    }
    bool empty()
    {
        return (elements == 0);
    }
    
    void inorder()
    {
        inorder(root);
    }
    void postexorder()
    {
        postorder(root);
    }

    void postorder(sb_node<T>* t)
    {
        if(t == nullptr)
        {
            return;
        }
        postorder(t->left);
        postorder(t->right);
        SpellVector(t->value.whole.start, t->value.whole.end);
        
    }
    void inorder(sb_node<T>* t)
    {
        if(t == nullptr)
        {
            return;
        }
        inorder(t->left);
        SpellVector(t->value.whole.start, t->value.whole.end);
        inorder(t->right);
    }

    void rootorder()
    {
        int levels = log2(elements);

        int nodeproccessed = 1;
        int currentLevel = log2(nodeproccessed);
        int tLevel = currentLevel;

        Deque<sb_node<T>*> q;
        q.addTail(root);

        while(!q.isEmpty())
        {
            sb_node<T>* p = q.removeHead();
            if(p != nullptr)
            {

            
            currentLevel = log2(nodeproccessed);
            for(tLevel = tLevel; tLevel != currentLevel; tLevel++)
            {
                printf("\n");
            }
            printf("%d ", p->value);
            nodeproccessed++;

            q.addTail(p->left);
            q.addTail(p->right);
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

        Deque<sb_node_parent<T>> q;

        int nodeproccessed = 3;
        int currentLevel = log2(nodeproccessed);
        int tLevel = currentLevel;

        double ypad = 1.0;
        double y = 0.0;



        sb_node_parent<T> origin;
        origin.node = root;
        origin.parent = {0,0};
        origin.x = 0;
        origin.y = 0;

        printf("\\draw (%f,%f) circle (10pt) [] node {%f}; \n", origin.x, origin.y, root->value.whole.start.y);

        if(root != nullptr && root->left != nullptr)
        {
            sb_node_parent<T> left;;
            left.node = root->left;
            left.parent = {origin.x, origin.y};
            left.x = -initalSpacing;
            left.y = -1;
            q.addTail(left);
        }

        if(root != nullptr && root->right != nullptr)
        {
            sb_node_parent<T> right;
            right.node = root->right;
            right.parent = {origin.x, origin.y};
            right.x = initalSpacing;
            right.y = -1;
            q.addTail(right);
        }
        

        while(!q.isEmpty())
        {
            
            sb_node_parent<T> p = q.removeHead();
            nodeproccessed++;
            if(p.node != nullptr)
            {
                printf("\\draw ($(%f, %f)+(275:10pt)$) -- ($(%f, %f)+(90:10pt)$);\n", p.parent.x, p.parent.y, p.x, p.y);
                printf("\\draw (%f, %f) circle(10pt) [] node {%f};\n", p.x, p.y, p.node->value.whole.start.y);
                
                currentLevel = abs(p.y - 1);
                
                double innerSpacing = abs(p.x - p.parent.x)/2.0;

                sb_node_parent<T> leftChild;
                leftChild.parent = {p.x,p.y};
                leftChild.node = p.node->left;
                leftChild.x = p.x - innerSpacing;
                leftChild.y = -currentLevel;

                
                q.addTail(leftChild);

                sb_node_parent<T> rightChild;
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