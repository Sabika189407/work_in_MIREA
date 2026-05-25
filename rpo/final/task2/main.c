#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void delete(char* str, char del)
{
    if (!str)
    {
        exit(-1);
    }
    int index = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (tolower(str[i]) != tolower(del))
        {
            str[index] = str[i];
            index++;
        }   
    }
    str[index] = '\0';
    return;
}

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        return -1;
    }
    char* str = argv[1];
    char del = argv[2][0];
    delete(str, del);
    printf("%s\n", str);
    return 0;
}