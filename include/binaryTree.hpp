#ifndef _FATSHARKS_BSTREE_H_
#define _FATSHARKS_BSTREE_H_

#include <iostream>
#include <memory>
#include <stack>
#include <queue>
#include <global.hpp>

//遍历参考链接：https://www.jianshu.com/p/456af5480cee
//https://blog.csdn.net/qq_38684427/article/details/107708469　mirror遍历

namespace myDataStructure
{

    template <typename T>
    class BTree
    {
    private:
        TreeNode<T> *root_;
        int height_;
        int size_;

        int get_height(TreeNode<T> *_root); //recursive

        

    public:
        BTree();
        BTree(BTree &_src); //recursive
        ~BTree();

        TreeNode<T> *createRecur(TreeNode<T> *_src); //recursive
        TreeNode<T> *create(TreeNode<T> *_src);      //non-recursive

        BTree &operator=(const BTree &_src); //recursive

        void preOrderRecur(TreeNode<T> *_root);
        void preOrderStack(TreeNode<T> *_root);

        void inOrderRecur(TreeNode<T> *_root);
        void inOrderStack(TreeNode<T> *_root);

        void postOrderRecur(TreeNode<T> *_root);
        void postOrderStack1(TreeNode<T> *_root);
        void postOrderStack2(TreeNode<T> *_root);

        void levelTravel(TreeNode<T> *_root);
        void mirrorTravel(TreeNode<T> *_root);

        int getHeight(TreeNode<T> *_root);
        int getSize(TreeNode<T> *_root);

        void destory(TreeNode<T> *_root); //recursive

        TreeNode<T> *ancester(TreeNode<T> *_root, TreeNode<T> *p, TreeNode<T> *q); //https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree/solution/236-er-cha-shu-de-zui-jin-gong-gong-zu-xian-hou-xu/
    };

    template <typename T>
    BTree<T>::BTree() : root_(NULL), height_(0), size_(0)
    {
    }
    template <typename T>
    BTree<T>::BTree(BTree<T> &_src) : height_(_src.height_), size_(_src.size_)
    {
        root_ = createRecur(_src.root_);
    }
    template <typename T>
    TreeNode<T> *createRecur(TreeNode<T> *_src)
    {
        TreeNode<T> *head = NULL;
        if (_src == NULL)
            return NULL;
        else
        {
            head = new TreeNode<T>(_src->data);
            head->leftChild = createRecur(_src->leftChild);
            head->rightChild = createRecur(_src->rightChild);
        }
        return head;
    }

    template <typename T>
    TreeNode<T> *create(TreeNode<T> *_src)
    {
        if (_src == NULL)
            return NULL;
        std::stack<TreeNode<T> *> TStackSrc, TStackDest;
        TreeNode<T> *newRoot = new TreeNode<T>;
        newRoot->data = _src->data;
        TStackSrc.push(_src);
        TStackDest.push(newRoot);
        while (!TStackSrc.empty())
        {
            TreeNode<T> *srcNode = TStackSrc.top();
            TreeNode<T> *destNode = TStackDest.top();
            destNode->data = srcNode->data;
            TStackSrc.pop();
            TStackDest.pop();
            if (srcNode->rightChild)
            {
                TStackSrc.push(srcNode->rightChild);
                destNode->rightChild = new TreeNode<T>;
                TStackDest.push(destNode->rightChild);
            }
            if (srcNode->leftChild)
            {
                TStackSrc.push(srcNode->leftChild);
                destNode->leftChild = new TreeNode<T>;
                TStackDest.push(destNode->leftChild);
            }
        }
        return newRoot;
    }

    template <typename T>
    BTree<T> &BTree<T>::operator=(const BTree<T> &_src)
    {
        if (_src.root_)
            return NULL;
        else
        {
            destory(root_);
            root_ = createRecur(_src.root_);
        }
        size_ = _src.size_;
        height_ = _src.height_;
        return *this;
    }

    template <typename T>
    BTree<T>::~BTree()
    {
        destory(root_);
    }
    template <typename T>
    void BTree<T>::destory(TreeNode<T> *_root)
    {
        if (_root)
        {
            destory(_root->leftChild);
            destory(_root->rightChild);
            delete _root;
            _root = NULL;
            height_ = size_ = 0;
        }
    }

    template <typename T>
    void BTree<T>::preOrderRecur(TreeNode<T> *_root)
    {
        if (_root != NULL)
        {
            std::cout << _root->data << " ";
            preOrderRecur(_root->leftChild);
            preOrderRecur(_root->rightChild);
        }
    }

    template <typename T>
    void BTree<T>::preOrderStack(TreeNode<T> *_root)
    {
        if (_root == NULL)
            return;
        std::stack<TreeNode<T> *> TStack;
        TStack.push(_root);
        while (!TStack.empty())
        {
            TreeNode<T> *temp = TStack.top();
            std::cout << temp->data << " ";
            TStack.pop();
            if (temp->rightChild)
            {
                TStack.push(temp->rightChild);
            }
            if (temp->leftChild)
            {
                TStack.push(temp->leftChild);
            }
        }
        std::cout << std::endl;
    }

    template <typename T>
    void BTree<T>::inOrderRecur(TreeNode<T> *_root)
    {
        if (_root == NULL)
            return;
        inOrderRecur(_root->leftChild);
        std::cout << _root->data << " ";
        inOrderRecur(_root->rightChild);
    }

    template <typename T>
    void BTree<T>::inOrderStack(TreeNode<T> *_root)
    {
        if (_root == NULL)
            return;
        std::stack<TreeNode<T> *> TStack;
        TreeNode<T> *temp = _root;
        while (temp || !TStack.empty())
        {
            if (temp)
            {
                TStack.push(temp);
                temp = temp->leftChild;
            }
            else
            {
                temp = TStack.top();
                TStack.pop();
                std::cout << temp->data << " ";
                temp = temp->rightChild;
            }
        }
        std::cout << std::endl;
    }

    template <typename T>
    void BTree<T>::postOrderRecur(TreeNode<T> *_root)
    {
        postOrderRecur(_root->leftChild);
        postOrderRecur(_root->rightChild);
        std::cout << _root->data << " ";
    }

    template <typename T>
    void BTree<T>::postOrderStack1(TreeNode<T> *_root)
    {
        if (_root == NULL)
            return;
        std::stack<TreeNode<T> *> TStack1, TStack2;
        TStack1->push(_root);
        TreeNode<T> *temp;
        while (!TStack1->empty())
        {
            temp = TStack1->top();
            TStack1->pop();
            TStack2->push(temp);
            if (temp->leftChild)
                TStack1->push(temp->leftChild);
            if (temp->rightChild)
                TStack1->push(temp->rightChild);
        }
        while (!TStack2->empty())
        {
            temp = TStack2->top();
            std::cout << temp->data << " ";
            TStack2->pop();
        }
        std::cout << std::endl;
    }
    template <typename T>
    void BTree<T>::postOrderStack2(TreeNode<T> *_root)
    {
        if (_root)
            return;
        std::stack<TreeNode<T> *> TStack;
        TreeNode<T> *temp = _root;
        TreeNode<T> *lastvist = _root;
        while (temp || !TStack.empty())
        {
            while (temp)
            {
                TStack.push(temp);
                temp = temp->leftChild;
            }
            temp = TStack.top();
            if (temp->rightChild == NULL || lastvist == temp->rightChild)
            {
                std::cout << temp->data << " ";
                lastvist = temp;
                temp = NULL;
                TStack.pop();
            }
            else
                temp = temp->rightChild;
        }
        std::cout << std::endl;
    }


    template <typename T>
    void BTree<T>::levelTravel(TreeNode<T> *_root)
    {
        if (_root == NULL)
            return;
        std::queue<TreeNode<T> *> *que;
        que->push(_root);
        TreeNode<T> *temp;
        while (!que->empty())
        {
            temp = que->front();
            std::cout << temp->data << " ";
            que->pop();
            if (temp->leftChild)
                que->push(temp->leftChild);
            if (temp->rightChild)
                que->push(temp->rightChild);
        }
        std::cout << std::endl;
    }

    template<typename T> void mirrorTravel(TreeNode<T> *_root)
    {
        if(!_root)
            return;
        TreeNode<T> *cur;
        while (cur)
        {
            if (cur->leftChild)
            {
                TreeNode<T> *fatherPtr = cur->leftChild;
                while (fatherPtr->rightChild && fatherPtr->rightChild != cur) //fatherPtr->rightChild == cur代表已经第二次遍历到根节点了
                {
                    fatherPtr = fatherPtr->rightChild;
                }
                if(fatherPtr->rightChild == NULL)
                {
                    fatherPtr->rightChild = cur;
                    std::cout<< cur->data;
                    cur = cur->leftChild;
                    continue;
                }
                fatherPtr->rightChild = NULL;
            }
            else
            {
                std::cout<< cur->data;
            }
            cur = cur->right;
        }
        
    }

    template <typename T>
    int BTree<T>::getHeight(TreeNode<T> *_root)
    {
        int height;
        if (_root == NULL)
            height = height_ = 0;
        else
            height = height_ = MAX(getHeight(_root->left), getHeight(_root->right)) + 1;
        return height;
    }

    template <typename T>
    int BTree<T>::getSize(TreeNode<T> *_root)
    {
        int size = 0;
        int leftSize, rightSize;
        if (_root != NULL)
            return size;
        else
        {
            leftSize = getSize(_root->leftChild) + 1;
            rightSize = getSize(_root->rightChild) + 1;
        }
        size = size_ = leftSize + rightSize - 1;
        return size;
    }

    template <typename T>
    TreeNode<T> *BTree<T>::ancester(TreeNode<T> *_root, TreeNode<T> *p, TreeNode<T> *q)
    {
        if (_root == NULL || _root = p || _root = q)
            return _root;
        TreeNode<T> *left = ancester(_root->leftChild, p, q);
        TreeNode<T> *right = ancester(_root->rightChild, p, q);
        if (left == NULL)
            return right;
        if (right == NULL)
            return left;
        return _root;
    }

} // namespace myDataStructure

#endif