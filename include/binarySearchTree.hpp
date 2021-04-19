#include <iostream>
#include <algorithm>
#include <stack>
#include <queue>
#include <global.hpp>

#define MAX     256
#define MIN     0

//https://www.cnblogs.com/gaochundong/p/binary_search_tree.html 二叉搜索树删除节点

namespace myDataStructure
{
    template <typename T>
    class BSTree
    {
    private:
        TreeNode<T> *root_;
        int height_;
        int size_;

        void destory(TreeNode<T> *_root);
        TreeNode<T> *createRecur(TreeNode<T> *_root);
        TreeNode<T> *create(TreeNode<T> *_root);
        TreeNode<T> *searchNode(TreeNode<T> *_root, T &key_);
        T &extremum(TreeNode<T> *_root, uint8_t direction);

        void preOrderRecur(TreeNode<T> *_root);
        void preOrderStack(TreeNode<T> *_root);
        void inOrderRecur(TreeNode<T> *_root);
        void inOrderStack(TreeNode<T> *_root);
        void postOrderRecur(TreeNode<T> *_root);
        void postOrderStack(TreeNode<T> *_root);
        void levelTravel(TreeNode<T> *_root);

    public:
        BSTree();
        BSTree(BSTree &_src);
        ~BSTree();
        TreeNode<T> *searchRecur(T &key_);
        TreeNode<T> *search(T &key_);
        BSTree &operator=(const BSTree &_src);
        void travel(TreeNode<T> *_root, int index);
        T &maximum();
        T &minimum();
        void insert(T &key_);
        void remove(T &key_);
    };

    template <typename T>
    BSTree<T>::BSTree() : root_(NULL), height_(0), size_(0)
    {
    }
    template <typename T>
    BSTree<T>::BSTree(BSTree &_src) : height_(_src.height_), size_(_src.size_)
    {
        this->root_ = create(_src.root_);
    }
    template <typename T>
    BSTree<T> &BSTree<T>::operator=(const BSTree<T> &_src)
    {
        if (_src.root_)
            return NULL;
        else
        {
            std::stack<TreeNode<T> *> TStackSrc, TStackNew;
            TStackSrc.push(_root);
            TStackNew.push(this->root_);
            while (!TStackSrc.empty())
            {
                TreeNode<T> *srcNode = TStackSrc.top();
                TreeNode<T> *newNode = TStackNew.top();
                newNode->data = srcNode->data;
                TStackSrc.pop();
                TStackNew.pop();
                if (srcNode->rightChild)
                {
                    TStackSrc.push(srcNode->rightChild);
                    if (!newNode->rightChild)
                        newNode->rightChild = new TreeNode<T>;
                    TStackNew.push(newNode->rightChild);
                }
                else if (!srcNode->rightChild && newNode->rightChild)
                {
                    destory(newNode->rightChild);
                }

                if (srcNode->leftChild)
                {
                    TStackSrc.push(srcNode->leftChild);
                    if (newNode->leftChild)
                        newNode->leftChild = new TreeNode<T>;
                    TStackNew.push(newNode->leftChild);
                }
                else if (!srcNode->leftChild && newNode->leftChild)
                {
                    destory(newNode);
                }
            }
            // destory(root_);
            // root_ = create(_src.root_);
        }
        size_ = _src.size_;
        height_ = _src.height_;
        return *this;
    }

    template <typename T>
    BSTree<T>::~BSTree()
    {
        destory(root_);
    }
    template <typename T>
    void BSTree<T>::destory(TreeNode<T> *_root)
    {
        if (_root)
        {
            destory(_root->leftChild);
            destory(_root->rightChild);
            delete _root;
            _root = NULL;
        }
    }

    template <typename T>
    TreeNode<T> *BSTree<T>::create(TreeNode<T> *_root)
    {
        std::stack<TreeNode<T> *> TStackSrc, TStackNew;
        TreeNode<T> *head = new TreeNode<T>;
        TStackSrc.push(_root);
        TStackNew.push(head);
        while (!TStackSrc.empty())
        {
            TreeNode<T> *srcNode = TStackSrc.top();
            TreeNode<T> *newNode = TStackNew.top();
            newNode->data = srcNode->data;
            TStackSrc.pop();
            TStackNew.pop();
            if (srcNode->rightChild)
            {
                TStackSrc.push(srcNode->rightChild);
                newNode->rightChild = new TreeNode<T>;
                TStackNew.push(newNode->rightChild);
            }
            if (srcNode->rightChild)
            {
                TStackSrc.push(srcNode->leftChild);
                newNode->leftChild = new TreeNode<T>;
                TStackNew.push(newNode->leftChild);
            }
        }
        return head;
    }
    template <typename T>
    TreeNode<T> *BSTree<T>::createRecur(TreeNode<T> *_root)
    {
        TreeNode<T> *head = NULL;
        if (!_root)
            return NULL;
        else
        {
            TreeNode<T> *head = new TreeNode<T>;
            head->data = _root->data;
            head->leftChild = createRecur(_root->leftChild);
            head->rightChild = createRecur(_root->rightChild);
        }
        return head;
    }

    template <typename T>
    void BSTree<T>::travel(TreeNode<T> *_root, int index)
    {
        switch (index)
        {
        case PRE:
            preOrderStack(_root);
            break;
        case IN:
            inOrderStack(_root);
        case POST:
            postOrderStack(_root);
        case LEVEL:
            levelTravel(_root);
        default:
            break;
        }
    }
    template <typename T>
    void BSTree<T>::preOrderRecur(TreeNode<T> *_root)
    {
        if (_root)
        {
            std::cout << _root->data << " ";
            preOrderRecur(_root->leftChild);
            preOrderRecur(_root->rightChild);
        }
    }
    template <typename T>
    void BSTree<T>::preOrderStack(TreeNode<T> *_root)
    {
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
    void BSTree<T>::inOrderRecur(TreeNode<T> *_root)
    {
        if (_root)
        {
            inOrderRecur(_root->leftChild);
            std::cout << _root->data << " ";
            inOrderRecur(_root->rightChild);
        }
    }
    template <typename T>
    void BSTree<T>::inOrderStack(TreeNode<T> *_root)
    {
        std::stack<TreeNode<T> *> TStack;
        TStack.push(_root);
        while (!TStack.empty())
        {
            TreeNode<T> *temp = TStack.top();
            if (temp->leftChild)
            {
                temp = temp->leftChild;
                TStack.push(temp);
            }
            else
            {
                std::cout << temp->data << " ";
                TStack.pop();
                if (temp->rightChild)
                {
                    temp = temp->rightChild;
                    TStack.push(temp);
                }
            }
        }
        std::cout << std::endl;
    }
    template <typename T>
    void BSTree<T>::postOrderRecur(TreeNode<T> *_root)
    {
        if (_root)
        {
            postOrderRecur(_root->leftChild);
            postOrderRecur(_root->rightChild);
            std::cout << _root->data << " ";
        }
    }
    template <typename T>
    void BSTree<T>::postOrderStack(TreeNode<T> *_root)
    {
        if (_root)
            return;
        std::stack<TreeNode<T> *> TStack;
        TreeNode<T> *temp = _root;
        TreeNode<T> *lastvisit = _root;
        while (temp || !TStack.empty())
        {
            while (temp)
            {
                TStack.push(temp);
                temp = temp->leftChild;
            }
            temp = TStack.top();
            if (temp->rightChild == NULL || lastvisit == temp->rightChild)
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
    void BSTree<T>::levelTravel(TreeNode<T> *_root)
    {
        std::queue<TreeNode<T> *> que;
        que.push(_root);
        TreeNode<T> *temp;
        while (que.empty())
        {
            temp = que.front();
            std::cout << temp->data << " ";
            que.pop();
            if (temp->leftChild)
            {
                que.push(temp->leftChild);
            }
            if (temp->rightChild)
            {
                que.push(temp->rightChild);
            }
        }
        std::cout << std::endl;
    }

    template <typename T>
    TreeNode<T> *BSTree<T>::searchRecur(T &key_)
    {
        return searchNode(root_);
    }
    template <typename T>
    TreeNode<T> *BSTree<T>::searchNode(TreeNode<T> *_root, T &key_)
    {
        if (_root == NULL || _root->data == key_)
        {
            return _root;
        }
        else if (key_ < _root->data)
        {
            searchNode(_root->leftChild);
        }
        else if (key_ > _root->data)
        {
            searchNode(_root->rightChild);
        }
        return _root;
    }
    template <typename T>
    TreeNode<T> *BSTree<T>::search(T &key_)
    {
        TreeNode<T> *temp = root_;
        while (temp == NULL || temp->data == key_)
        {
            if (key_ < temp->data)
            {
                temp = temp->leftChild
            }
            else
            {
                temp = temp->rightChild
            }
        }
        return temp;
    }
    template <typename T>
    T &BSTree<T>::extremum(TreeNode<T> *_root, uint8_t direction)
    {
        if (_root == NULL)
            return (T)NULL;
        switch (direction)
        {
        case MAX:
            while (_root)
                _root = _root->rightChild;
            break;
        case MIN:
            while (_root)
                _root = _root->leftChild;
            break;
        default:
            break;
        }
        return _root->data;
    }
    template <typename T>
    T &BSTree<T>::maximum()
    {
        return extremum(root_, MAX);
    }
    template <typename T>
    T &BSTree<T>::minimum()
    {
        return extremum(root_, MIN);
    }

    template <typename T>
    void BSTree<T>::insert(T &key_)
    {
        if (root_ == NULL)
        {
            root_->data = key_;
            root_->leftChild = root_->rightChild = NULL;
            return ;
        }
        int direction = 0;
        TreeNode<T> *parent = NULL;
        TreeNode<T> *temp = root_;
        while (temp)
        {
            parent = temp;
            if (key_ < temp->data)
            {
                temp = temp->leftChild;
                direction = 0;
            }
            else if (key_ > temp->data)
            {
                temp = temp->rightChild;
                direction = 1;
            }
            else
                return;
        }
        if (direction)
        {
            parent->rightChild = new TreeNode<T>(key_);
        }
        else
        {
            parent->leftChild = new TreeNode<T>(key_);
        }
    }
    template <typename T>
    void BSTree<T>::remove(T &key_)
    {
        TreeNode<T> *temp = root_;
        TreeNode<T> *parent = NULL;
        int direction = 0;
        while (temp || temp->data == key_)
        {
            parent = temp;
            if (key_ < temp->data)
            {
                temp = temp->leftChild;
                direction = 0;
            }
            else if (key_ > temp->data)
            {
                temp = temp->rightChild;
                direction = 1;
            }
        }
        if (temp)
        {
            if (!temp->leftChild && !temp->rightChild)
            {
                if (direction)
                {
                    parent->rightChild = NULL;
                    delete temp;
                }
                else
                {
                    parent->leftChild = NULL;
                    delete temp;
                }
            }
            else if (temp->leftChild && !temp->rightChild)
            {
                if (direction)
                {
                    parent->rightChild = temp->leftChild;
                    delete temp;
                }
                else
                {
                    parent->leftChild = temp->leftChild;
                    delete temp;
                }
            }
            else if (temp->rightChild && !temp->leftChild)
            {
                if (direction)
                {
                    parent->rightChild = temp->rightChild;
                    delete temp;
                }
                else
                {
                    parent->leftChild = temp->rightChild;
                    delete temp;
                }
            }
            else
            {
                TreeNode<T>* ptemp = temp;
                TreeNode<T>* papa = NULL;
                while (ptemp->leftChild)
                {
                    papa = ptemp;
                    ptemp = ptemp->leftChild;
                }
                temp->data = ptemp->data;
                papa->leftChild = ptemp->rightChild;
                delete ptemp;    
            }
        }
        else
        {
            return;
        }
    }
} // namespace myDataStructure
