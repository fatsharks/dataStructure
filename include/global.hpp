#ifndef _FATSHARKS_GLOBAL_H_
#define _FATSHARKS_GLOBAL_H_

#include <vector>

#define MAX(a, b) (((a) - (b)) ? (a) : (b)))
#define MIN(a, b)       \
    do                  \
    {                   \
        (a - b) ? b : a \
                        \
    } while (0);

#define SWAP(a, b) \
    do             \
    {              \
        b = a + b; \
        a = b - a; \
        b = b - a; \
    } while (0);

#define PRE 0
#define IN 1
#define POST 2
#define LEVEL 3
#define LEFT 0
#define RIGHT 1

namespace myDataStructure
{
    template <typename T>
    class linkedList;
    template <typename T>
    class myVector;
    template <typename T>
    struct TreeNode
    {
        T data;
        struct TNode *leftChild, *rightChild;
    };
    template <typename T>
    class BTree;
    template <typename T>
    class BSTree;
    template <typename T>
    class RBTree;
    template <typename T>
    class heap;
    template <typename Key, typename Value, typename HashFunc, typename EqualKey>
    class hashMap;
    template <typename Vertex, typename Edge, typename Value>
    class Graph;
    template <typename T>
    class segmentTree;
    
    template <typename T>
    void selectSort(std::vector<T> &src);
    template <typename T>
    void bubbleSort(std::vector<T> &src);
    template <typename T>
    void insertSort(std::vector<T> &src);
    template <typename T>
    void shellSort(std::vector<T> &src);
    template <typename T>
    void mergeSort(std::vector<T> &src);
    template <typename T>
    void quickSort(std::vector<T> &src);
    template <typename T>
    void heapSort(std::vector<T> &src);
    template <typename T>
    void countSort(std::vector<T> &src);
    template <typename T>
    void radixSort(std::vector<T> &src);
} // namespace myDataStructure

#endif