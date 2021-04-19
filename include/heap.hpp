#include <iostream>
#include <global.hpp>

//https://www.cnblogs.com/skywang12345/p/3610382.html
//https://zhuanlan.zhihu.com/p/75894663

namespace myDataStructure
{
    template <typename T>
    class heap
    {
    private:
        T *heapData;
        size_t capacity_;
        size_t size_;

        void sink(size_t index);
        void floating(size_t index);

    public:
        heap();
        ~heap();

        bool insert(T &_data);
        bool remove(T &_data);
        bool full();
        bool empty();
    };

    template <typename T>
    heap<T>::heap() : heapData(NULL), capacity_(0), size_(0)
    {
    }

    template <typename T>
    heap<T>::~heap()
    {
    }
    template <typename T>
    bool heap<T>::insert(T &_data)
    {
        if (full())
        {
            return false;
        }
        else
        {
            heapData[size_] = _data;
            size_++;
            floating(size_);
            return true;
        }
    }
    template <typename T>
    bool heap<T>::remove(T &_data)
    {
        if (empty())
        {
            return false;
        }
        else
        {
            int index = -1;
            for (size_t i = 0; i < count; i++)
            {
                if (heapData[i] == _data)
                {
                    index = i;
                }
            }
            if (index == -1)
            {
                return false;
            }
            heapData[index] == heapData[--size_];
            sink(index);
            return true;
        }
    }
    template <typename T>
    void heap<T>::sink(size_t index)
    {
        int parent = index;
        int LChild = 2 * index + 1;
        while (LChild <= size_)
        {
            if (LChild < size_ && heapData[LChild] < heapData[LChild++])
            {
                LChild++;
            }
            if (heapData[parent] > heapData[LChild])
            {
                break;
            }
            SWAP(heapData[parent], heapData[LChild]);
            parent = LChild;
            LChild = 2 * parent + 1;
        }
    }

    template <typename T>
    void heap<T>::floating(size_t index)
    {
        int child = index;
        int parent = (child - 1) / 2;
        while (parent >= 0)
        {
            if (heapData[parent] > heapData[child])
            {
                break;
            }
            else
            {
                SWAP(heapData[parent], heapData[child]);
                child = parent;
                parent = (child - 1) / 2;
            }
        }
    }
    template <typename T>
    bool heap<T>::full()
    {
        return size_ >= capacity_ ? true : false;
    }
    template <typename T>
    bool heap<T>::empty()
    {
        return size_ == 0 ? true : false;
    }

} // namespace myDataStructure
