#include <stdio.h>

char* is_lucky(char* a)
{
    if ((a[0] + a[1] + a[2])-90 == (a[5] + a[4] + a[3]) - 90)
    {
        return "true";
    }
    else
    {
        return "false";
    }
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        perror("not enough imput");
        return -1;
    }
    FILE* input = fopen(argv[1], "r");
    FILE* output = fopen("output.txt", "a");
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
}