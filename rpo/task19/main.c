#include <stdio.h>

int* getData(const FILE* fname, size_t* size)
{
    int _size = *size;
    int* arr = (int*)malloc(_size * sizeof(int));
    if (!arr)
    {
        perror("cannot malloc");
        return NULL;
    }
    for (int i = 0; i < _size; i++)
    {
        fscanf(fname, "%d", &arr[i]);
    }
    return arr;
}

void print(const int* data, size_t size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", data[i]);
    }
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
    FILE* positive = fopen("positive.txt", "a");
    FILE* negative = fopen("negative.txt", "a");
    if (!input || !positive || !negative)
    {
        perror("cannot open files");
        return -1;
    }
    int nefig = 0;
    size_t size = 0;
    while (fscanf(input, "%d", &nefig) != EOF)
    {
        size++;
    }
    rewind(input);
    int* arr = getData(input, &size);
    for (int i = 0; i < size; i++)
    {
        if (arr[i] > 0)
        {
            fprintf(positive, "%d ", arr[i]);
        }
        if (arr[i] < 0)
        {
            fprintf(negative, "%d ", arr[i]);
        }
    }
    free(arr);
    fclose(input);
    fclose(positive);
    fclose(negative);
}