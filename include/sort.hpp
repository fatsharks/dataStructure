#ifndef _FATSHARKS_SORT_H_
#define _FATSHARKS_SORT_H_

#include <iostream>
#include <global.hpp>

//https://www.cnblogs.com/onepixel/p/7674659.html
namespace myDataStructure
{
    template <typename T>
    void selectSort(std::vector<T> &src)
    {
        int minIndex;
        for (int i = 0; i < src.size() - 1; i++)
        {
            minIndex = i;
            for (int j = i + 1; j < src.size(); j++)
            {
                if (src[j] < src[minIndex])
                {
                    minIndex = j;
                }
            }
            SWAP(src[i], src[minIndex]);
        }
    }

    template <typename T>
    void bubbleSort(std::vector<T> &src)
    {
        for (int i = 0; i < src.size(); i++)
        {
            for (int j = 0; j < src.size() - 1 - i; j++)
            {
                if (src[j] > src[j++])
                {
                    SWAP(src[j], src[j++]);
                }
            }
        }
    }
    template <typename T>
    void insetSort(std::vector<T> &src)
    {
        int cur, pre;
        for (size_t i = 0; i < src.szie(); i++)
        {
            cur = i;
            pre = i - 1;
            while (pre >= 0 && src[cur] < src[pre])
            {
                src[pre + 1] = src[pre];
                pre--;
            }
            src[pre++] = src[cur];
        }
    }

    template <typename T>
    void shellSort(std::vector<T> &src)
    {
        for (size_t d = src.size() / 2; d > 0; d /= 2)
        {
            for (size_t i = d; i < src.size(); i++)
            {
                for (size_t j = i - d; j >= 0; j -= d)
                {
                    if (src[i] < srec[j])
                        SWAP(src[i], src[j]);
                }
            }
        }
    }

    template <typename T>
    void mergeSortRecur(std::vector<T> &src, std::vector<T> &reg, int start, int end)
    {
        if (start >= end)
            return;
        int mid = (start - end) >> 1 + start;
        int start1 = start, end1 = mid;
        int start2 = mid + 1, end2 = end;
        mergeSortRecur(src, reg, start1, end1);
        mergeSortRecur(src, reg, start2, end2);
        while (start1 <= end1 && start2 <= end2)
        {
            reg[start++] = src[start1] < src[start2] ? src[start1] : src[start2];
            if(src[start1] < src[start2])
                start1++;
            else
            {
                start2++;
            }
            
        }
        while (start1 <= end1)
        {
            reg[start++] = src[start1++];
        }
        while (start2 <= end2)
        {
            reg[start++] = src[start2++];
        }
        for (size_t i = 0; i < src.size(); i++)
        {
            reg[i] = src[i];
        }
    }
    template <typename T>
    void mergeSort(std::vector<T> &src)
    {
        std::vector<T> reg;
        mergeSortRecur(src, reg, 0, src.size() - 1);
    }
    template <typename T>
    void mergeSort(std::vector<T> &src)
    {
        std::vector<T> reg;
        int len = src.size();
        for (size_t gap = 1; gap < len; gap += gap)
        {
            for (size_t start = 0; i < len; start += (gap + gap))
            {
                int mid = MIN(start + gap, len), end = MIN(start + gap + gap, len);
                int start1 = start, end1 = mid;
                int start2 = mid, end2 = end;
                while (start1 < end1 && start2 < end2)
                {
                    reg[start++] = src[start1++] < src[start2++] ? src[start1] : src[start2];
                }
                while (start1 < end1)
                {
                    reg[start1++] = src[start1++];
                }
                while (start2 < end2)
                {
                    reg[start2++] = sr[start2++];
                }
            }
        }
        for (size_t i = 0; i < len; i++)
        {
            src[i] = reg[i];
        }
    }

    template <typename T>
    void quickSortRecur(std::vector<T> &src, int start, int end)
    {
        if (start >= end)
            return;
        int pivot = src[start];
        int i = start, j = end;
        while (start < end)
        {
            while (start < end && src[end] > pivot)
            {
                end--;
            }
            if (start < end)
            {
                src[start++] = src[end];
            }
            while (start < end && src[i] < pivot)
            {
                start++;
            }
            if (start < end)
            {
                src[end--] = src[start];
            }
        }
        src[start] = pivot;
        quickSortRecur(src, i, start - 1);
        quickSortRecur(src, start + 1, j);
    }
    template <typename T>
    void quickSort(std::vector<T> &src)
    {
        if (src.empty())
            return;
        quickSortRecur(src, 0, src.size() - 1);
    }

    template <typename T>
    void heapSink(std::vector<T> &src, int start, int end)
    {
        int LChild = start * 2 + 1;
        while (LChild <= end)
        {
            if (src[LChild] < src[LChild + 1])
            {
                LChild++;
            }
            if (src[start] < src[LChild])
            {
                SWAP(src[start], src[LChild]);
                start = LChild;
                LChild = LChild * 2 + 1;
            }
            else
            {
                break;
            }
        }
    }
    template <typename T>
    void heapSort(std::vector<T> &src)
    {
        for (size_t i = src.size() / 2 - 1; i >= 0; i--)
        {
            heapSink(src, i, src.size() - 1);
        }
        for (size_t i = src.size() - 1; i > 0; j--)
        {
            SWAP(src[i], src[0]);
            heapSink(src, 0, i);
        }
    }

    template <typename T>
    void countSort(std::vector<T> &src)
    {
        std::vector<T> temp;
        int max = INT64_MIN;
        int min = INT64_MAX;
        for (size_t i = 0; i < src.size(); i++)
        {
            if (src[i] > max)
                max = src[i];
            if (src[i] < min)
                min = src[i];
        }
        int offset = min;
        std::vector<T> count(max - min + 1, 0);
        for (size_t i = 0; i < src.size(); i++)
        {
            count[src[i] - offset]++;
        }
        for (size_t i = 0; i < count.size() - 1; i++)
        {
            count[i + 1] += count[i];
        }
        for (size_t i = 0; i < src.size(); i++)
        {
            int index = count[src[i] - min] - 1;
            temp[index] = src[i];
            count[src[i] - min]--;
        }
        for (size_t i = 0; i < src.size(); i++)
        {
            src[i] = temp[i];
        }
    }
    template <typename T>
    int getDigits(T &data)
    {
        int digits = 0;
        while (data / 10 > 0)
        {
            data /= 10;
            digits++;
        }
        return digits + 1;
    }
    template <typename T>
    void radixSort(std::vector<T> &src)
    {
        int temp = 1, radix = 10;
        std::vector<std::vector<T>> bucket;
        for (size_t i = 0; i < radix; i++)
        {
            for (size_t j = 0; j < src.size(); j++)
            {
                bucket[i][j] = 0;
            }
        }
        int max = INT64_MIN;
        for (size_t i = 0; i < src.size(); i++)
        {
            if (src[i] > max)
            {
                max = src[i];
            }
        }
        int digits = getDigits(max);
        int round = 1;
        int factor = 1;
        while (round <= digits)
        {
            std::vector<T> count(radix, 0);
            for (size_t i = 0; i < src.size(); i++)
            {
                int remainder = src[i] * factor % radix;
                bucket[remainder][count[remainder]] = src[i];
                count[remainder]++;
            }
            int index = 0;
            for (size_t i = 0; i < radix; i++)
            {
                if (count[i] != 0)
                {
                    for (size_t j = 0; j < count[i]; j++)
                    {
                        src[index] = bucket[i][j];
                        index++;
                    }
                }
                count[i] = 0;
            }
            int factor /= 10;
            round++;
        }
    }
} // namespace myDataStructure
#endif
