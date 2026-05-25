#include <stdio.h>
#include <ctype.h>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        perror("not enough imput");
        return -1;
    }
    FILE* input = fopen(argv[1], "r");
    if (!input)
    {
        perror("cannot open the file");
        return -1;
    }
    int arr[26] = {0};
    char ch;
    while((ch = fgetc(input)) != EOF)
    {
        ch = tolower(ch);
        if (ch >= 'a' && ch <= 'z')
        {
            arr[ch - 'a']++;
        }
    }
    for (int i = 0; i < 26; i++)
    {
        if (arr[i] > 0)
        {
            printf("%c - %d\n", i + 'a', arr[i]);
        }
    }
    fclose(input);
}