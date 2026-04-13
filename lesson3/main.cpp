#include "binary_find.h"

int main()
{
    int* ar = new int[8] {4, 13, 19, 35, 41, 47, 58, 77};
    quick_sort(ar, 8);
    std::cout << binary_find(ar, 8, 58) << std::endl;
}