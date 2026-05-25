#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int count_str(char* str, char* sub_str)
{
    if (!str || !sub_str)
    {
        return -1;
    }
    int q = strlen(sub_str);
    if (q == 0)
    {
        return -1;
    }
    int count = 0;
    size_t len = strlen(sub_str);
    char* temp = strstr(str, sub_str);
    while (temp != NULL)
    {
        count++;
        temp = strstr(temp + len, sub_str);
    }
    return count;
}

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
    char* str = NULL;
    char* sub_str = NULL;
    size_t size = 0;
    size_t buffer_str = 0;
    size_t buffer_sub = 0;
    
    size = getline(&str, &buffer_str, input);
    size = getline(&sub_str, &buffer_sub, input);
    if (str[strlen(str)-1] == '\n')
    {
        str[strlen(str)-1] = '\0';
    }
    if (sub_str[strlen(sub_str)-1] == '\n')
    {
        sub_str[strlen(sub_str)-1] = '\0';
    }
    printf("%d\n", count_str(str, sub_str));
    free(str);
    free(sub_str);
    fclose(input);
}