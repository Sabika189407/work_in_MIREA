#include <stdio.h>
#include <string.h>
#include <ctype.h>

void delete(char* str, char del)
{
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
        perror("not enough imput");
        return -1;
    }
    FILE* f = fopen("output.txt", "w");
    if (!f)
    {
        perror("cannot open this file");
        return -1;
    }
    char* str = argv[1];
    char del = argv[2][0];
    delete(str, del);   
    if (fprintf(f, "%s\n", str) == -1)
    {
        perror("cannot write in file");
        return -1;
    }
    fclose(f);
}