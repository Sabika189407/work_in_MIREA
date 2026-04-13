#include "binary_find.h"

void quick_sort(int* ar, int size)
{
    if (ar == nullptr)
    {
        throw "the pointer is null, stopped sorting\n";
    }
    if (size == 0)
    {
        throw "size is 0, stopped sorting\n";
    }

    int left = 0;
    int right = size-1;
    int pivot = ar[size/2];

    while(left <= right)
    {
        while(ar[left] < pivot)
        {
            left++;
        }
        while(ar[right] > pivot)
        {
            right--;
        }
        if (left <= right)
        {
            std::swap(ar[left], ar[right]);
            left++;
            right--;
        }
    }
    if (right > 0)
    {
        quick_sort(&ar[0], left);
        quick_sort(&ar[left], size - left);
    }
    return;
}

int binary_find(int* ar, int size, int num)
{
    if (ar == nullptr)
    {
        throw std::invalid_argument("the pointer is null!\n");
    }

    if (size == 0)
    {
        throw std::invalid_argument("size of the array = 0!\n");
    }
    int pivot = size/2;
    if (size % 2 != 0) pivot++;
    if (ar[pivot] == num)
    {
        return pivot;
    }
    if (ar[pivot] < num)
    {
        return (pivot + binary_find(ar + size/2, size/2, num));
    }
    else if (ar[pivot] > num)
    {
        return (pivot + binary_find(ar, size/2, num));
    }
    else
    {
        throw "can't find element\n";
        return -1;
    }
}