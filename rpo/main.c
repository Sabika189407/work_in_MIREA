#include <stdio.h>
#include <time.h>
#include <stdlib.h>


int main(int argc, char** argv)
{
    srand(time(NULL));
    if (argc < 2)
    {
        perror("not enough imput");
        return -1;
    }

    FILE* f = fopen(argv[1], "r");
    FILE* output = fopen("output.txt", "a");
    if (!f || !output)
    {
        perror("cannot read file");
    }

    int size, min, max;
    fscanf(f, "%d %d %d", &size, &min, &max);
    int* arr = (int*)malloc(size * sizeof(int));
    if (!arr)
    {
        perror("cannot allocate memory for array");
        return -1;
    }
    for (int i = 0; i < size; i++)
    {
        arr[i] = min + rand() % (max - min + 1);
    }
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (arr[i] > arr[j])
            {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    int max_int = 0;
    for (int i = 0; i < size; i++)
    {
        if (max_int < arr[i])
        {
            max_int = arr[i];
        }
    }
    int min_int = 0;
    for (int i = 0; i < size; i++)
    {
        if (min_int > arr[i])
        {
            min_int = arr[i];
        }
    }
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum+=arr[i];
    }
    float average = sum/size;

    fprintf(output, "sorted array:\n");
    for (int i = 0; i < size; i++)
    {
        fprintf(output, "%d\t", arr[i]);
    }
    fprintf(output, "\n");
    fprintf(output, "max of array - %d\n", max_int);
    fprintf(output, "min of array - %d\n", min_int);
    fprintf(output, "average of array - %f\n", average);

    free(arr);
    fclose(f);
    fclose(output);
    return 0;
}