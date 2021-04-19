#include <iostream>
#include "global.hpp"

namespace myDataStructure
{
    template <typename T>
    struct segNode
    {
        int left_;
        int right_;
        int value_;
        int cover_;
        struct segNode<T> *leftChild;
        struct segNode<T> *rightChild;
    };

    template <typename T>
    class segmentTree
    {
    private:
        segNode<T> *root_;

        segNode<T> *build(int start, int end, int cover);

    public:
        segmentTree(int start, int end, int cover = 0);
        ~segmentTree();
    };

    template <typename T>
    segmentTree<T>::segmentTree(int start, int end, int cover = 0)
    {
        root_ = new segNode<T>;
        root_->left_ = start;
        root_->right_ = end;
        root_->leftChild = NULL;
        root_->rightChild = nullptr;
        // root_->cover_++;
        if (start < end)
        {
            int mid = (start + end) >> 1;
            root_->leftChild = build(start, mid, root_->cover_);
            root_->rightChild = build(mid, emd, root_->cover_);
            root_->value_ = MIN(root_->leftChild->value_, root_->rightChild->value_);
        }
        else
        {
            root_->value_ = start;
        }
    }

    template <typename T>
    segNode<T> *segmentTree<T>::build(int start, int end, int cover)
    {
        if (start < end)
        {
            segNode<T> *root = new segNode<T>;
            root->left_ = start;
            root->right_ = end;
            root->cover_ = cover;
            int mid = (start + end) >> 1;
            root->leftChild = build(start, mid, root->cover_);
            root->rightChild = build(mid, end, root->cover_);
        }
        else if (start == end)
        {
            segNode<T> *root = new segNode<T>;
            root->leftChild = nullptr;
            root->rightChild = nullptr;
            root->value_ = start;
        }
        root->value_ = MIN(root->leftChild->value_, root->rightChild->value_);
        return root;
    }

    template <typename T>
    segmentTree<T>::~segmentTree()
    {
    }

} // namespace myDataStructure
