#include "sorts.h"
#include "tools.h"

void randInt(int* ar, int count, int from, int to)
{
    if (ar == nullptr)
    {
        std::cout << "the pointer is null, stopped randoming" << std::endl;
        return;
    }
    std::srand(std::time({}));
    for (int i = 0; i < count; i++)
    {
        ar[i] = (rand() % (to - from)) + from;
    }
    return;
}

void print(int* ar, int size)
{
    if (ar == nullptr)
    {
        std::cout << "the pointer is null, stopped printing" << std::endl;
        return;
    }
    
    std::cout << "array:\t";
    for (int i = 0; i < size; i++)
    {
        std::cout << ar[i] << "\t";
    }
    std::cout << std::endl;
    return;
}

int find_radix(int a)
{
    int count = 0;
    if (a == 0) count = 1;
    else {
        int temp = std::abs(a);
        while (temp > 0) {
            temp /= 10;
            count++;
        }
    }
    return count;
}