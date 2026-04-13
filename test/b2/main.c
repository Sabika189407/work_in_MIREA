#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        perror("not enough imput");
    }
    char erase = *argv[2];
    int size = strlen(argv[1]);
    for (int i = 0; i < size-1; i++)
    {
        if (argv[1][i] == erase)
        {
            argv[1][i] = argv[1][i+1];
            size--;
        }
    }
    printf("%*s\n", size, argv[1]);
}