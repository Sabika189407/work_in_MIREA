#include <stdio.h>
#include <ctype.h>
#include <string.h>
int main(int argc, char** argv)
{
    if (argc < 2)
    {
        perror("not enough imput");
        return 1;
    }
    int size = strlen(argv[1]);
    char ar[size+1];
    int j = 0;
    for (int i = 0; i < size; i++)
    {
        if (isdigit(argv[1][i]) || ispunct(argv[1][i]) || isspace(argv[1][i]))
        {
            continue;
        }
        else
        {
            ar[j++] = tolower(argv[1][i]);
        }
    }
    ar[j] = '\0';
    printf("%s\n", ar);
    size = j;
    for (int i = 0; i < size/2; i++)
    {
        if(ar[i] != ar[size-i-1])
        {
            printf("false\n");
            return 0;
        }
    }
    printf("true\n");
    return 0;
}