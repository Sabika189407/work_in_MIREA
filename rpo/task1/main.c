#include <stdio.h>
#include <string.h>
#include <ctype.h>

void is_palindrome(char* str)
{
    int flag = 0;
    int left = -1;
    int right = strlen(str);
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (tolower(str[left++]) != tolower(str[right--]))
        {
            flag = 1;
        }
    }
    if (flag == 0)
    {
        printf("true\n");
    }
    else
    {
        printf("false\n");
    }
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        perror("not enough imput");
        return -1;
    }
    char str[strlen(argv[1])+1];
    int num = 0;
    for (int i = 0; argv[1][i] != '\0'; i++)
    {
        if (isalpha(argv[1][i]))
        {
            str[num] = argv[1][i];
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