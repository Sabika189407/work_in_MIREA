#include <stdio.h>
#include <stdlib.h>

int max(const int* arr, const size_t size)
{
    int max = arr[0];
    for (int i = 0; i < size; i++)
    {
        if(max < arr[i])
        {
            max = arr[i];
        }

    }
    return max;
}

int count(const int* arr, const size_t size)
{
    int q = 0;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] % 2 == 0)
        {
            q++;
        }
    }
    return q;
}

int is_growing(const int* arr, const size_t size)
{
    for (int i = 0; i < size-1; i++)
    {
        if (arr[i] > arr[i+1])
        {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        perror("not enough imput");
        return -1;
    }
    FILE* input = fopen(argv[1], "r");
    if (!input)
    {
        perror("cannot read the file");
        return -1;
    }
    int capacity = 100;
    int* arr = (int*)malloc(capacity * sizeof(int));
    int num = 0;
    size_t size = 0;
    while(fscanf(input, "%d", &num) != EOF)
    {
        if (size+1 > capacity)
        {
            int* temp = (int*)realloc(arr, capacity * 2 * sizeof(int));
            capacity*=2;
            if (!temp)
            {
                perror("cannot realloc");
                return -1;
            }
            arr = temp;
        }
        arr[size] = num;
        size++;
    }
    printf("max - %d\n", max(arr, size));
    printf("count - %d\n", count(arr, size));
    printf("%d\n", is_growing(arr, size));
    free(arr);
    fclose(input);
}