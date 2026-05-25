#include <stdio.h>
#include <stdlib.h>

char* is_lucky(char* num)
{
    if (!num)
    {
        perror("the pointer is NULL");
        exit(-1);
    }
    if ((num[0] + num[1] + num[2]) - 90 == (num[3] + num[4] + num[5]) - 90)
    {
        return "true";
    }
    return "false";
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

    char* num;
    while (fscanf(input, "%s", num) != EOF)
    {
        fprintf(output, "%s %s\n", num, is_lucky(num));
    }
    fclose(input);
    fclose(output);
}