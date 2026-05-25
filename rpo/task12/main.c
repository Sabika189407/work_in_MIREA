#include <stdio.h>
#include <stdlib.h>

void cyclic_shift(int* arr, int size, int shift)
{
    shift = shift % size;
    if (shift < 0)
    {
        shift += size;
    }
    int* temp = (int*)malloc(size * sizeof(int));
    if (!temp)
    {
        perror("cannot malloc");
        return;
    }
    for (int i = 0; i < size; i++)
    {
        temp[(i + shift) % size] = arr[i];
    }
    for (int i = 0; i < size; i++)
    {
        arr[i] = temp[i];
    }
    free(temp);
    return;
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        perror("not enough imput");
        return -1;
    }
    FILE* input = fopen(argv[1], "r");
    FILE* output = fopen("out.txt", "a");
    if (!input || !output)
    {
        perror("cannot open files");
        return -1;
    }
    int shift = 0;
    int num = 0;
    size_t size = 0;
    int capacity = 100;
    int* arr = (int*) malloc(capacity * sizeof(int));
    fscanf(input, "%d", &shift);
    while(fscanf(input, "%d", &num) != EOF)
    {
        if (size+1 > capacity)
        {
            int* temp = (int*)realloc(arr, capacity * 2 * sizeof(int));
            capacity*=2;
        }
        arr[size] = num;
        size++;
    }
    cyclic_shift(arr, size, shift);
    for(int i = 0; i < size; i++)
    {
        fprintf(output, "%d\t", arr[i]);
    }
    fprintf(output, "\n");
    free(arr);
    fclose(input);
    fclose(output);
}