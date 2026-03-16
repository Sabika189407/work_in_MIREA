#include "tools.h"
#include "sorts.h"

int main(int argc, char** argv)
{
    if (argc <= 3)
    {
        std::cout << "not enough imput" << std::endl;
        return 1;
    }

    int count = atoi(argv[1]);
    int from = atoi(argv[2]);
    int to = atoi(argv[3]);

    int* arr1 = new int[count];
    randInt(arr1, count, from, to);
    int* arr2 = new int[count];
    memcpy(arr2, arr1, sizeof(int) * count);
    int* arr3 = new int[count];
    memcpy(arr3, arr1, sizeof(int) * count);
    int* arr4 = new int[count];
    memcpy(arr4, arr1, sizeof(int) * count);
    int* arr5 = new int[count];
    memcpy(arr5, arr1, sizeof(int) * count);
    int* arr6 = new int[count];
    memcpy(arr6, arr1, sizeof(int) * count);
    int* arr7 = new int[count];
    memcpy(arr7, arr1, sizeof(int) * count);
    int* arr8 = new int[count];
    memcpy(arr8, arr1, sizeof(int) * count);
    int* arr9 = new int[count];
    memcpy(arr9, arr1, sizeof(int) * count);

    std::cout << "____________bubble sort____________" << std::endl;
    auto start1 = std::chrono::high_resolution_clock::now();
    bubbleSort_stupid(arr1, count);
    auto end1 = std::chrono::high_resolution_clock::now();
    print(arr1, count);
    std::chrono::duration<double, std::milli> duration1 = end1 - start1;
    std::cout << "Func duration:\t" << duration1.count() << " ms" << std::endl;

    std::cout << "__________insertion_sort___________" << std::endl;
    auto start2 = std::chrono::high_resolution_clock::now();
    insertion_sort(arr2, count);
    auto end2 = std::chrono::high_resolution_clock::now();
    print(arr2, count);
    std::chrono::duration<double, std::milli> duration2 = end2 - start2;
    std::cout << "Func duration:\t" << duration2.count() << " ms" << std::endl;

    std::cout << "__________selection_sort____________" << std::endl;
    auto start3 = std::chrono::high_resolution_clock::now();
    insertion_sort(arr3, count);
    auto end3 = std::chrono::high_resolution_clock::now();
    print(arr3, count);
    std::chrono::duration<double, std::milli> duration3 = end3 - start3;
    std::cout << "Func duration:\t" << duration3.count() << " ms" << std::endl;

    std::cout << "____________merge_sort_____________" << std::endl;
    auto start4 = std::chrono::high_resolution_clock::now();
    merge_sort(arr4, 0, count-1);
    auto end4 = std::chrono::high_resolution_clock::now();
    print(arr4, count);
    std::chrono::duration<double, std::milli> duration4 = end4 - start4;
    std::cout << "Func duration:\t" << duration4.count() << " ms" << std::endl;

    std::cout << "____________quick_sort_____________" << std::endl;
    auto start5 = std::chrono::high_resolution_clock::now();
    quick_sort(arr5, count);
    auto end5 = std::chrono::high_resolution_clock::now();
    print(arr5, count);
    std::chrono::duration<double, std::milli> duration5 = end5 - start5;
    std::cout << "Func duration:\t" << duration5.count() << " ms" << std::endl;

    std::cout << "_____________radix_sort_____________" << std::endl;
    auto start6 = std::chrono::high_resolution_clock::now();
    quick_sort(arr6, count);
    auto end6 = std::chrono::high_resolution_clock::now();
    print(arr6, count);
    std::chrono::duration<double, std::milli> duration6 = end6 - start6;
    std::cout << "Func duration:\t" << duration6.count() << " ms" << std::endl;

    std::cout << "_____________Stalin_sort____________" << std::endl;
    auto start7 = std::chrono::high_resolution_clock::now();
    std::cout << "rasstrelyat x" << Stalin_sort(arr7, count) << "!" << std::endl;
    auto end7 = std::chrono::high_resolution_clock::now();
    print(arr7, count);
    std::chrono::duration<double, std::milli> duration7 = end7 - start7;
    std::cout << "Func duration:\t" << duration7.count() << " ms" << std::endl;

    std::cout << "___________cocktail_sort____________" << std::endl;
    auto start8 = std::chrono::high_resolution_clock::now();
    cocktail_sort(arr8, count);
    auto end8 = std::chrono::high_resolution_clock::now();
    print(arr8, count);
    std::chrono::duration<double, std::milli> duration8 = end8 - start8;
    std::cout << "Func duration:\t" << duration8.count() << " ms" << std::endl;

    std::cout << "_____________heap_sort______________" << std::endl;
    auto start9 = std::chrono::high_resolution_clock::now();
    heap_sort(arr9, count);
    auto end9 = std::chrono::high_resolution_clock::now();
    print(arr9, count);
    std::chrono::duration<double, std::milli> duration9 = end9 - start9;
    std::cout << "Func duration:\t" << duration9.count() << " ms" << std::endl;

    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    delete[] arr4;
    delete[] arr5;
    delete[] arr6;
    delete[] arr7;
    delete[] arr8;
    delete[] arr9;

    return 0;
}