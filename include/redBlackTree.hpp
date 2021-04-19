#include <iostream>
#include <stack>
#include <queue>
#include <algorithm>
#include <global.hpp>

//https://www.jianshu.com/p/e136ec79235c 参考链接
//bilibili码炫课堂

namespace myDataStructure
{
    enum RBTColor
    {
        RED = 0,
        BLACK = 1
    };
    template <typename T>
    struct RBTNode
    {
        RBTColor color_;
        T data;
        RBTNode<T> *leftChild;
        RBTNode<T> *rightChild;
        RBTNode<T> *parent;
    };
    template <typename T>
    void makePair(RBTNode<T> *child, RBTNode<T> *parent, uint8_t direction);
    template <typename T>
    RBTNode<T> *successor(RBTNode<T> *_src);
    template <typename T>
    class RBTree
    {
    private:
        RBTNode<T> *root_;
        RBTNode<T> *insertUnbalance(RBTNode<T> *_root, T &_key);
        RBTNode<T> *leftRotate(RBTNode<T> *_root);
        RBTNode<T> *rightRotate(RBTNode<T> *_root);
        void setColor(RBTNode<T> *_src, uint8_t _color);
        size_t colorOfNode(RBTNode<T> *_src);
        RBTNode<T> *getBrother(RBTNode<T> *_src);
        void fixAfterRemove(RBTNode<T> *_src);

    public:
        RBTree();
        ~RBTree();

        void insert(T &_key);
        RBTNode<T> *rotate(RBTNode<T> *_root, uint8_t direction);
        void remove(T &_key);
        RBTNode<T> *find(T &_key);
    };

    template <typename T>
    RBTree<T>::RBTree() : root_(NULL)
    {
    }

    template <typename T>
    RBTree<T>::~RBTree()
    {
    }
    template <typename T>
    RBTNode<T> *RBTree<T>::find(T &_key)
    {
        if (!root_)
        {
            return NULL;
        }
        else
        {
            RBTNode<T> *temp = root_;
            while (temp && temp->data != _key)
            {
                if (_key < temp->data)
                {
                    temp = temp->leftChild;
                }
                else
                    (_key > temp->data)
                    {
                        temp = temp->rightChild;
                    }
            }
            return temp;
        }
    }

    template <typename T>
    RBTNode<T> *RBTree<T>::insertUnbalance(RBTNode<T> *_root, T &_key)
    {
        if (_root == NULL)
        {
            _root->color_ = BLACK;
            _root->data = _key;
            return _root;
        }
        RBTNode<T> *temp = _root;
        RBTNode<T> *parent = NULL;
        int direction = 0;
        while (temp)
        {
            parent = temp;
            if (_key < temp->data)
            {
                temp = temp->leftChild;
                direction = 0;
            }
            else if (_key > temp->data)
            {
                temp = temp->rightChild;
                direction = 1;
            }
            else
            {
                return temp;
            }
        }
        RBTNode<T> *newNode = new RBTNode<T>;
        newNode->data = _key;
        newNode->color_ = RED;
        makePair(newNode, parent, direction);
        return newNode;
    }

    template <typename T>
    void RBTree<T>::insert(T &_key)
    {
        if (root_ == NULL)
        {
            insertUnbalance(root_, _key);
            return;
        }
        else
        {
            RBTNode<T> *retNode = insertUnbalance(root_, _key);
            RBTNode<T> *parent, *gparent;
            while (parent = retNode->parent && parent->color_ == RED)
            {
                gparent = parent->parent;
                if (parent == gparent->leftChild)
                {
                    if (gparent->rightChild && gparent->rightChild->color_ == RED)
                    {
                        setColor(gparent, RED);
                        setColor(parent, BLACK);
                        setColor(gparent->rightChild, BLACK);
                        setColor(retNode, RED);
                        retNode = gparent;
                        continue;
                    }
                    else if (!getBrother(parent) || colorOfNode(getBrother(parent)) == BLACK)
                    {
                        if (retNode = parent->right)
                        {
                            rotate(parent, LEFT);
                            RBTNode<T> *temp = parent;
                            parent = retNode;
                            retNode = temp;
                        }
                        rotate(gparent, RIGHT);
                        setColor(gparent, RED);
                        setColor(parent, BLACK);
                        setColor(retNode, RED);
                    }
                }
                else
                {
                    if (gparent->leftChild && gparent->leftChild->color_ == RED)
                    {
                        setColor(gparent, RED);
                        setColor(retNode, RED);
                        setColor(parent, BLACK);
                        setColor(gparent->leftChild, BLACK);
                        retNode = gparent;
                        continue;
                    }
                    else if (!gparent->leftChild || colorOfNode(gparent->leftChild) == BLACK)
                    {
                        if (retNode = parent->leftChild)
                        {
                            rotate(parent, LEFT);
                            RBTNode<T> *temp = parent;
                            parent = retNode;
                            retNode = parent;
                        }
                        rotate(parent);
                        setColor(parent, BLACK);
                        setColor(gparent, RED);
                        setColor(retNode, RED);
                    }
                }
                setColor(root_, BLACK);
            }
        }
    }
    template <typename T>
    void RBTree<T>::remove(T &_key)
    {
        RBTNode<T> *replace = NULL;
        RBTNode<T> *successor = NULL;
        RBTNode<T> *_src = find(_key);
        if (_src)
        {
            if (_src->leftChild && _src->rightChild)
            {
                successor = successor(_src);
                _src->data = successor->data;
            }
            RBTNode<T> *replace = (successor->leftChild != NULL) ? successor->leftChild : successor->rightChild;
            if (replace)
            {
                replace->parent = successor->parent;
                if (successor->parent == NULL)
                {
                    root_ = replace;
                }
                if (successor->parent->leftChild)
                {
                    replace = successor->parent->leftChild;
                }
                else
                {
                    replace = successor->parent->rightChild;
                }
                RBTColor color = replace->color_;
                replace->color_ = successor->color_;

                successor->leftChild = successor->parent = successor->rightChild = NULL;
                delete successor;
                if (color == BLACK)
                {
                    fixAfterRemove(replace);
                }
            }
            else if (successor->parent == NULL)
            {
                root_ = NULL;
            }
            else
            {
                if (successor->color_ == BLACK)
                {
                    fixAfterRemove(successor);
                }
                if (successor->parent->leftChild == successor)
                {
                    successor->parent->leftChild = NULL;
                }
                else
                {
                    successor->parent->rightChild = NULL;
                }
                delete successor;
            }
        }
        else
        {
            return;
        }
    }
    template <typename T>
    void RBTree<T>::fixAfterRemove(RBTNode<T> *_src)
    {
        RBTNode<T> *parent = NULL;
        RBTNode<T> *sibling = NULL;
        while (_src != root_ && _src->color_ == BLACK)
        {
            parent = _src->parent;
            if (_src == parent->leftChild)
            {
                sibling = parent->rightChild;
                if (colorOfNode(sibling) == RED)
                {
                    rotate(parent, LEFT);
                    setColor(sibling, BLACK);
                    setColor(parent, RED);
                    rotate(parent, LEFT);
                    sibling = parent->rightChild;
                }
                if ((sibling->leftChild == NULL && sibling->rightChild == NULL) || (sibling->leftChild->color_ == BLACK && sibling->rightChild->color_ == BLACK))
                {
                    setColor(sibling, RED);
                    _src = parent;
                }
                else
                {
                    if (sibling->rightChild->color_ == BLACK)
                    {
                        setColor(sibling->leftChild, BLACK);
                        setColor(sibling, RED);
                        rotate(sibling, RIGHT);
                        sibling = parent->rightChild;
                    }
                    setColor(sibling, parent->color_);
                    setColor(parent, BLACK);
                    setColor(sibling->rightChild, BLACK);
                    rotate(parent, LEFT);
                    _src = root;
                }
            }
            else
            {
                sibling = parent->leftChild;
                if (colorOfNode(sibling) == RED)
                {
                    rotate(parent, RIGHT);
                    setColor(sibling, BLACK);
                    setColor(parent, RED);
                    rotate(parent, RIGHT);
                    sibling = parent->leftChild;
                }
                if ((sibling->rightChild == NULL && sibling->leftChild == NULL) || (sibling->leftChild->color_ == BLACK && sibling->rightChild->color_ == BLACK))
                {
                    setColor(sibling, RED);
                    _src = parent;
                }
                else
                {
                    if (sibling->leftChild->color_ == BLACK)
                    {
                        setColor(sibling->rightChild, BLACK);
                        setColor(sibling, RED);
                        rotate(sibling, LEFT);
                        sibling = parent->LEFTChild;
                    }
                    setColor(sibling, parent->color_);
                    setColor(parent, BLACK);
                    setColor(sibling->leftChild, BLACK);
                    rotate(parent, RIGHT);
                    _src = root;
                }
            }
        }
        setColor(_src, BLACK);
    }

    template <typename T>
    RBTNode<T> *RBTree<T>::rotate(RBTNode<T> *_root, uint8_t direction)
    {
        RBTNode<T> *temp = NULL;
        switch (direciton)
        {
        case LEFT:
            temp = leftRotate(_root);
            break;
        case RIGHT:
            temp = rightRotate(_root);
            break;
        default:
            break;
        }
        return temp;
    }

    template <typename T>
    RBTNode<T> *RBTree<T>::leftRotate(RBTNode<T> *_root)
    {
        RBTNode<T> *parent = _root;
        RBTNode<T> *RChild = parent->rightChild;
        RBTNode<T> *RLGrandson = RChild->leftChild;

        makePair(RLGrandson, parent, RIGHT);
        makePair(parent, RChild, LEFT);
        return RChild;
    }
    template <typename T>
    RBTNode<T> *RBTree<T>::rightRotate(RBTNode<T> *_root)
    {
        RBTNode<T> *parent = _root;
        RBTNode<T> *LChild = parent->leftChild;
        RBTNode<T> *LRGrandson = LChild->rightChild;

        makePair(LRGrandson, parent, LEFT);
        makePair(parent, LChild, RIGHT);
        return LChild
    }
    template <typename T>
    void RBTree<T>::setColor(RBTNode<T> *_src, uint8_t _color)
    {
        if (_src == NULL)
        {
            return;
        }
        _src->color_ = _color;
    }
    template <typename T>
    size_t RBTree<T>::colorOfNode(RBTNode<T> *_src)
    {
        return (size_t)_src->color_;
    }
    template <typename T>
    RBTNode<T> *RBTree<T>::getBrother(RBTNode<T> *_src)
    {
        RBTNode<T> *parent = _src->parent;
        if (_src == parent->leftChild)
        {
            return parent->rightChild;
        }
        else
        {
            return parent->leftChild;
        }
    }
    template <typename T>
    void makePair(RBTNode<T> *child, RBTNode<T> *parent, uint8_t direction)
    {
        child->parent = parent;
        if (direction)
        {
            parent->rightChild = child;
        }
        else
        {
            parent->leftChild = child;
        }
    }

    template <typename T>
    RBTNode<T> *successor(RBTNode<T> *_src)
    {
        RBTNode<T> *temp = _src->rightChild;
        while (temp->leftChild)
        {
            temp = temp->leftChild;
        }
        return temp;
    }
} // namespace myDataStructure
