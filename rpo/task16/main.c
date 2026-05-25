#include <stdio.h>
#include <stdlib.h>

char* divide(int first, int second, size_t sequenceLength)
{
    if (second == 0)
    {
        char* error = (char*)malloc(20 * sizeof(char));
        if (!error)
        {
            perror("cannot malloc");
            exit(-1);
        }
        snprintf(error, 6, "error");
        return error;
    }
    double num = (double)first/second;
    char* result = (char*)malloc(sizeof(char) * sequenceLength);
    if (!result)
    {
        perror("cannot malloc");
        exit(-1);
    }
    snprintf(result, sequenceLength+1, "%.*f", (int)sequenceLength-2, num);
    return result;
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
        perror("cannot read files");
        return -1;
    }
    int first, second, sequenceLength;
    fscanf(input, "%d %d %d", &first, &second, &sequenceLength);
    char* result = divide(first, second, sequenceLength);
    fprintf(output, "%s\n", result);
    free(result);
    fclose(input);
    fclose(output);
}