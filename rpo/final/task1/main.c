#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

void is_palindrome(char* str)
{
    if (!str)
    {
        exit(-1);
    }
    int left = 0;
    int right = strlen(str) - 1;
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[left] != str[right])
        {
            printf("false\n");
            return;
        }
        left++;
        right--;
    }
    printf("true\n");
    return;
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        perror("not enough imput");
        return -1;
    }
    int num = 0;
    char* str = (char*)malloc(strlen(argv[1]) * sizeof(char));
    for (int i = 0; i < argv[1][i] != '\0'; i++)
    {
        if (isalpha(argv[1][i]))
        {
            str[num] = tolower(argv[1][i]);
            num++;
        }
        else
        {
            continue;
        }
    }
    str[num] = '\0';
    printf("%s\n", str);
    is_palindrome(str);
    return 0;
}