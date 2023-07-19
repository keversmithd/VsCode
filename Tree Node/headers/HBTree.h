#ifndef _HBTREE
#define _HBTREE

#include "HBTNode.h"

template<typename E>
struct HBTree
{
private:
    HBTNode<E>* m_root;
    bool m_empty;
    bool(*m_lcompare)(E,E);
    bool(*m_rcompare)(E,E);
    bool(*m_ecompare)(E,E);
    bool m_exitcompare;
public:
    HBTree(bool(*lcompare)(E,E), bool(*rcompare)(E,E), bool(*ecompare)(E,E), HBTNode<E>* root = nullptr)
    {
        m_empty = (root == nullptr);
        if(!m_empty){ m_root = root; }
        m_exitcompare = ( lcompare == nullptr || rcompare == nullptr; || ecompare == nullptr; );
        if(!m_exitcompare){ m_lcompare = lcompare; m_rcompare = rcompare; m_ecompare = ecompare; }
    }
    int Search(HBTNode<E>* m_head, E element)
    {
        if(m_exitcompare){return 0;}

        if(m_head == nullptr){return 0;}
        E copyElement = m_head->CopyElement();
        if(m_ecompare(element, copyElement))
        {
            return 1;
        }
        if(m_lcompare(copyElement, element))
        {
            return Search(m_head->left, element);
        }
        if(m_rcompare(copyElement, element))
        {
            return Search(m_head->right, element);
        }

        return 0;
    }
    int SearchIterative(HBTNode<E>* m_head, E element)
    {
        HBTNode<E>* s_current = m_head;

        while(s_current != nullptr)
        {
            E copyElement = s_current->CopyElement();
            if(m_ecompare(element, copyElement))
            {
                return 1;
            }
            else if(m_lcompare(element, copyElement))
            {
                if(s_current->left == nullptr)
                {
                    return 0;
                }
                s_current = s_current->left;
            }
            else
            {
                if(s_current->right == nullptr)
                {
                    return 0;
                }
                s_current = s_current->right;
            }
        }
    }
    int TopDownIterativeSearch(HBTNode<E>* m_head, E element)
    {
        HBTNode<E>* s_current = m_head;

        while(s_current != nullptr)
        {
            E copyElement = s_current->CopyElement();
            if(m_ecompare(element, copyElement))
            {
                return 1;
            }
            else if(m_lcompare(element, copyElement))
            {
                if(s_current->left == nullptr)
                {
                    return 0;
                }
                s_current = s_current->left;
            }
            else
            {
                if(s_current->right == nullptr)
                {
                    return 0;
                }
                s_current = s_current->right;
            }
        }
    }
    int Splay(HBTNode<E>* m_head)
    {
        while(m_head->parent != nullptr)
        {
            if(m_head->parent->parent == nullptr)
            {
                if(m_head->parent->left == nullptr)
                {
                    m_head = right_rotate_splay(m_head);
                }else
                {
                    m_head = left_rotate_splay(m_head);
                }
            }else if(m_head->parent->left == m_head && m_head->parent->parent->left == m_head->parent)
            {
                m_head->parent->parent = right_rotate_splay(m_head->parent->parent);
                m_head = right_rotate_splay(m_head);
            }else if(m_head->parent->right == m_head && m_head->parent->parent->right == m_head->parent)
            {
                m_head->parent->parent = left_rotate_splay(m_head->parent->parent);
                m_head = left_rotate_splay(m_head);
            }else if(m_head->parent->left == m_head && m_head->parent->parent->right == m_head)
            {
                m_head = right_rotate_splay(m_head);
                m_head = left_rotate_splay(m_head);
            }else
            {
                m_head = left_rotate_splay(m_head);
                m_head = right_rotate_splay(m_head);
            }
            
        }
        return m_head;
    }

    int max_height(HBTNode<E>* node1, HBTNode<E>* node2)
    {
        int node1_height = height(node1);
        int node2_height = height(node2);
        return (node1_height > node2_height) ? node1_height : node2_height;
    }

    HBTNode<E>* right_rotate_splay(HBTNode<E>* m_head)
    {
        if(m_head == nullptr)
        {
            return nullptr;
        }
        HBTNode<E>* left_child = m_head->left;
        HBTNode<E>* left_child_right = left_child->right;

        left_child->right = m_head;
        m_head->left = left_child_right;

        int m_head_left_height = height(m_head->left);
        int m_head_right_height = height(m_head->right);
        m_head->Height = (m_head_left_height > m_head_right_height) ? m_head_left_height : m_head_right_height;
        int m_left_child_left = height(left_child->left);
        int m_left_child_right = height(left_child->right);
        left_child->height =  (m_left_child_left > m_left_child_right) ? m_left_child_left : m_left_child_right;


        return left_child;

    }
    HBTNode<E>* left_rotate_splay(HBTNode<E>* m_head)
    {
        if(m_head == nullptr)
        {
            return nullptr;
        }
        HBTNode<E>* right_child = m_head->right;
        HBTNode<E>* right_child_left = right_child->left;
        right_child->left = m_head;
        m_head->right = right_child_left;

        int m_head_left_height = height(m_head->left);
        int m_head_right_height = height(m_head->right);
        m_head->Height = (m_head_left_height > m_head_right_height) ? m_head_left_height : m_head_right_height;
        int m_left_child_left = height(right_child->left);
        int m_left_child_right = height(right_child->right);
        left_child->height =  (m_left_child_left > m_left_child_right) ? m_left_child_left : m_left_child_right; 

        return right_child;
    }


    HBTNode<E>* right_rotate(HBTNode<E>* node)
    {
        if(node == nullptr)
            return 0;
        HBTNode<E>* left_child = node->left;
        HBTNode<E>* left_child_right = node->left->right;

        left_child->right = node;
        node->left = left_child_right;
        
        node->Height = max_height(node->left, node->right) + 1;
        left_child->Height = max_height(left_child->left, left_child->right) + 1;

        return left_child;
    }
    HBTNode<E>* left_rotate(HBTNode<E>* node)
    {
        if(node == nullptr)
        {
            return 0;
        }
        HBTNode<E>* right_child = node->right;
        HBTNode<E>* right_child_left = node->right->left;
        right_child->left = node;
        node->right = right_child_left;

        node->Height = max_height(node->left, node->right) + 1;
        right_child->Height = max_height(right_child->left, right_child->right) + 1;
        return right_child;

    }
    int height(HBTNode<E>* node)
    {
        if(node == nullptr)
        {
            return -1;
        }
        return node->height;
    }

    int InorderTraversal();
    int PreorderTraversal();
    int BreadthFirstTraversal();
    int DepthFirstTraversal();
    int PostorderTraversal();
    int FindBalance(HBTNode<E>* m_node)
    {
        if (m_node == nullptr)
            return 0;
        return height(m_node->left) - height(m_node->right);
    }
    int Insert(E element)
    {
        m_root = InsertRecursive(m_root, element);
        return 1;
    }
    int Delete(E element)
    {
        m_root = DeleteRecursive(m_root, element);
        return 1;
    }

    HBTNode<E>* MinValueNode(HBTNode<E>* node)
    {
        HBTNode<E>* current = node;
        while(current->left != nullptr)
        {
            current = current->left;
        }
        return current;
    }
    HBTNode<E>* DeleteRecursive(HBTNode<E>* m_head, E element)
    {
        if(m_head == NULL)
            return m_head;
        
        if(m_lcompare(element, m_head->element))
        {
            m_head->left = DeleteRecursive(m_head->left, element);
        }else if (m_rcompare(element, m_head->element))
        {
            m_head->right = DeleteRecursive(m_head->right, element);
        }else
        {
            if( (m_head->left == nullptr) || (m_head->right == nullptr))
            {
                HBTNode<E>* temp = m_head->left ? m_head->left : m_head->right;
                if(temp == nullptr)
                {
                    temp = m_head;
                    m_head = nullptr;
                }else
                {
                    *m_head = *temp;
                    free(temp);
                }
                
            }else
            {
                HBTNode<E>* temp = MinValueNode(m_head->right);
                m_head->element = temp->element;
                m_head->right = DeleteRecursive(m_head->right, temp->element);
            }
        }

        if(m_head == nullptr)
        {
            return m_head;
        }

        m_head->Height = 1 + height_max(m_head->left, m_head->right);

        int BalanceFactor = FindBalance(m_head);
        
        if(BalanceFactor > 1 && FindBalance(m_head->left) >= 0)
        {
            return right_rotate(m_head);

        }
        if(BalanceFactor > 1 && FindBalance(m_head->left) < 0)
        {
            m_head->left = left_rotate(m_head->left);
            return right_rotate(m_head);
        }
        if(BalanceFactor < -1 && FindBalance(m_head->right) <= 0)
        {
            return left_rotate(m_head);
        }
        if(BalanceFactor < -1 && FindBalance(m_head->right) > 0)
        {
            m_head->right = right_rotate(m_head->right);
            return left_rotate(m_head);
        }

        return m_head;
    }
    HBTNode<E>* InsertRecursive(HBTNode<E>* m_head, E element)
    {
        if(m_root == nullptr)
        {
            m_root = new HBTNode<E>(element);
            return 1;
        }
        if(m_lcompare(element, m_root->element))
        {
            m_head->left = InsertRecursive(m_head->left, element);
        }else if(m_rcompare(element, m_root->element))
        {
            m_head->right = InsertRecursive(m_read->right, element);
        }else
        {
            return m_head;
        }

        m_head->Height = 1 + height_max(m_head->left, m_head->right);
        int BalanceFactor = FindBalance(m_head);
        if(BalanceFactor > 1 && m_lcompare(element, m_head->left->element))
        {
            return right_rotate(m_head);
        }
        if(BalanceFactor < -1 && m_rcompare(element, m_head->right->element))
        {
            return left_rotate(m_head);
        }
        if(BalanceFactor > 1 && m_rcompare(element, m_head->left->element))
        {
            m_head->left = left_rotate(m_head->left);
            return right_rotate(m_head);
        }
        if(BalanceFactor < -1 && m_lcompare(element, m_head->right->element))
        {
            m_head->right = right_rotate(m_head->right);
            return left_rotate(m_head);
        }

        return m_head;

    }
    int InsertIterative(E element)
    {
        if(m_root == nullptr)
        {
            m_root = new HBTNode<E>(element);
            return 1;
        }
        HBTNode<E>* m_iter = m_root;
        HBTNode<E>* m_parent = nullptr;
        while(m_iter != nullptr)
        {
            m_parent = m_iter;
            if(m_lcompare(element, m_iter->element))
            {
                m_iter = m_iter->left;
                
            }
            else if(m_rcompare(element, m_iter->element))
            {
                m_iter = m_iter->right;

            }else if(m_ecompare(element, m_iter->element))
            {
                return 0;
            }
        }
        
        //if it was inserted into the right tree, the right tree increases

        m_iter = new HBTNode<E>(element, nullptr, nullptr, m_parent);
        for(m_iter = m_iter; m_iter != nullptr;)
        {
            m_parent = m_iter;
            m_iter->Height = 1 + max_height(m_iter->left, m_iter->right);
            int Balance = FindBalance(m_iter);

            if(Balance > 1 && m_lcompare(element, m_iter->left->element))
            {
                m_iter = right_rotate(m_iter);
                m_parent->right = m_iter;

            }
            if(Balance < -1 && m_rcompare(element, m_iter->right->element))
            {
                m_iter = left_rotate(m_iter);
                m_parent->left = m_iter;
            }
            if(Balance > 1 && m_rcompare(element, m_iter->left->element))
            {
                m_iter->left = left_rotate(m_iter->left);
                m_iter = right_rotate(m_iter);
                m_parent->right = m_iter;
            }
            if(Balance < -1 && m_lcompare(element, m_iter->right->element))
            {
                m_iter->right = right_rotate(m_iter->right);
                m_iter = left_rotate(m_iter);
                m_parent->left = m_iter;
            }

            if(m_lcompare(element, m_iter->element))
            {
                m_iter = m_iter->left;
            } else
            {
                m_iter = m_iter->rigth;
            }

        }

    }
    int Delete();
    int Intersection();
    int Join(HBTNode<E>* secondaryRoot)
    {
        
    }
    int Split();
    int Union();

};



#endif