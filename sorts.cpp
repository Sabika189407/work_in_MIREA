#include "sorts.h"
#include "tools.h"

using std::string;

void bubbleSort_stupid(int* ar, int size)
{
    if (ar == nullptr)
    {
        std::cerr << "the pointer is null, stopped sorting";
        return;
    }
    if (size == 0)
    {
        std::cerr << "size is 0, stopped sorting";
        return;
    }

    for (int i = 0; i < size-1; i++)
    {
        for (int j = 0; j < size- i - 1; j++)
        {
            if (ar[j] > ar[j+1])
            {
                std::swap(ar[j], ar[j+1]);
            }
        }
    }
    return;
}

void insertion_sort(int* ar, int size)
{
    if (ar == nullptr)
    {
        std::cerr << "the pointer is null, stopped sorting";
        return;
    }
    if (size == 0)
    {
        std::cerr << "size is 0, stopped sorting";
        return;
    }
    
    for (int i = 1; i < size; i++)
    {
        for (int j = i; j > 0 && ar[j-1] > ar[j]; j--)
        {
            std::swap(ar[j], ar[j-1]);            
        }
    }
    return;
}

void selectionSort(int* ar, int size) 
{
    if (ar == nullptr)
    {
        std::cerr << "the pointer is null, stopped sorting";
        return;
    }
    if (size == 0)
    {
        std::cerr << "size is 0, stopped sorting";
        return;
    }

    for (int i = 0; i < size - 1; i++) {
        int min = i;
        for (int j = i + 1; j < size; j++) {
            if (ar[j] < ar[min]) {
                min = j;
            }
        }
        std::swap(ar[min], ar[i]);
    }
    return;
}

/*void merge_sort(int* ar, int size)
{
    if (ar == nullptr)
    {
        std::cerr << "the pointer is null, stopped sorting" << std::endl;
        return;
    }
    int* result = new int[size];
    int pivot = size/2;
    int h = 1;
    int step;
    while(h < size) 
    {
        step = h;
        int left = 0;
        int right = pivot;
        int j_result = 0;
        while(step <= pivot)
        {
            while((left < step) && (right < size) && (right < (pivot + step)))
            {
                if (ar[left] < ar[right])
                {
                    result[j_result] = ar[left];
                    left++;
                    j_result++;
                }
                else
                {
                    result[j_result] = ar[right];
                    right++;
                    j_result++;
                }
            }
            while(left < step)
            {
                result[j_result] = ar[left];
                left++;
                j_result++;
            }
            while((right < (pivot + step)) && (right < size))
            {
                result[j_result] = ar[right];
                right++;
                j_result++;
            }
            step = step + h;    
    }
    h = h * 2;
    memcpy(ar, result, sizeof(int) * size);
    }
        delete[] result;
}*/

/*void merge_sort(int* ar, int size)
{
    int pivot = size/2;
    int left = 0;
    int right = pivot;
    int* res = new int[size];
    int i = 0;
    while(i < size)
    {
        if(ar[left] >= ar[right])
        {
            res[i] = ar[right];
            right++;
            i++;
        }
        if (right >= size)
        {
            while (i < size)
            {
                res[i++] = ar[left++];
            }
            break;
        }
        
        if (ar[left] < ar[right])
        {
            res[i] = ar[left];
            left++;
            i++;
            if (left >= pivot)
            {
                while(i < pivot)
                {
                    res[i++] = ar[right++];
                }
                break;
            }
        }
    }
    memcpy(ar, res, size * sizeof(int));
    delete[] res;
}*/

void merge_sort(int* ar, int left, int right)
{
    if (ar == nullptr)
    {
        std::cerr << "the pointer is null, stopped sorting";
        return;
    }

    if (left >= right)
    {
        return;
    }

    int pivot = (left + right)/2;
    merge_sort(ar, left, pivot);
    merge_sort(ar, pivot+1, right);
    int i = left;
    int j = pivot + 1;
    int* res = new int[right - left + 1];

    for (int step = 0; step < right - left + 1; step++)
    {
        if (i <= pivot && (j > right || ar[i] <= ar[j]))
        {
            res[step] = ar[i];
            i++;
        }
        else
        {
            res[step] = ar[j];
            j++;
        }
    }
    for (int step = 0; step < right - left + 1; step++)
    {
        ar[left + step] = res[step];
    }
    delete[] res;
    return;
}

void quick_sort(int* ar, int size)
{
    if (ar == nullptr)
    {
        std::cerr << "the pointer is null, stopped sorting";
        return;
    }
    if (size == 0)
    {
        std::cerr << "size is 0, stopped sorting";
        return;
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


void radix_sort(int* ar, int size)
{
    if (ar == nullptr)
    {
        std::cerr << "the pointer is null, stopped sorting";
        return;
    }
    if (size == 0)
    {
        std::cerr << "size is 0, stopped sorting";
        return;
    }

    int max_r = 0;

    for (int i = 0; i < size; i++)
    {
        if (max_r < find_radix(ar[i]))
        {
            max_r = find_radix(ar[i]);
        }
    }
    for (int digit = 1; max_r/digit > 0; digit*=10)
    {
        digit_sort(ar, digit, size);
    }
    return;
}

void digit_sort(int* ar, int digit, int size)
{
    if (ar == nullptr)
    {
        std::cerr << "the pointer is null, stopped sorting";
        return;
    }
    if (size == 0)
    {
        std::cerr << "size is 0, stopped sorting";
        return;
    }

    int* res = new int[size];
    int positions[10] = {0};
    
    for (int i = 0; i < size; i++)
    {
        int number = (ar[i] / digit) % 10;
        positions[number]++;
    }
    for (int i = 1; i < 10; i++)
    {
        positions[i] += positions[i-1];
    }
    for (int i = size-1; i >= 0; i--)
    {
        int number = (ar[i] / digit) % 10;
        res[positions[number]-1] = ar[i];
        positions[number]--;
    }
    for (int i = 0; i < size; i++)
    {
        ar[i] = res[i];
    }
    delete[] res;
    return;
}

int Stalin_sort(int* ar, int size) 
{
    if (ar == nullptr)
    {
        std::cerr << "the pointer is null, stopped sorting";
        return 0;
    }
    if (size == 0)
    {
        std::cerr << "size is 0, stopped sorting";
        return 0;
    }
    int rasstrelyat = 1;

    for (int i = 1; i < size; ++i) {
        if (ar[i] >= ar[rasstrelyat - 1]) {
            ar[rasstrelyat] = ar[i];
            rasstrelyat++;
        }
    }
    return rasstrelyat; 
}

void cocktail_sort(int* ar, int size)
{
    if (ar == nullptr)
    {
        std::cerr << "the pointer is null, stopped sorting";
        return;
    }
    if (size == 0)
    {
        std::cerr << "size is 0, stopped sorting";
        return;
    } 

    bool swapped = 1;
    int left = 0;
    int right = size - 1;

    while(swapped)
    {
        swapped = 0;

        for (int i = left; i < size; i++)
        {
            if (ar[i] > ar[i+1])
            {
                std::swap(ar[i], ar[i+1]);
                swapped = 1;
            }
        }

        if (swapped == 0)
        {
            break;
        }

        swapped = 0;
        right--;

        for (int i = right - 1; i >= left; i--)
        {
            if (ar[i] > ar[i+1])
            {
                std::swap(ar[i], ar[i+1]);
                swapped = 1;
            }
        }
        left++;
    }
}

void heapify(int* ar, int n, int i) {
    if (ar == nullptr)
    {
        std::cerr << "the pointer is null, stopped sorting";
        return;
    }

    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && ar[l] > ar[largest])
        largest = l;

    if (r < n && ar[r] > ar[largest])
        largest = r;

    if (largest != i) {
        std::swap(ar[i], ar[largest]);
        heapify(ar, n, largest);
    }
}

void heap_sort(int* ar, int size) {
    if (ar == nullptr)
    {
        std::cerr << "the pointer is null, stopped sorting";
        return;
    }

    for (int i = size / 2 - 1; i >= 0; i--) {
        heapify(ar, size, i);
    }

    for (int i = size - 1; i > 0; i--) {
        std::swap(ar[0], ar[i]);
        heapify(ar, i, 0);
    }
}