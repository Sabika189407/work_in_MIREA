#include <stdio.h>

typedef enum {
    DD_MM_YY = 1,
    DD_MM_YYYY,
    YYYY_MM_DD
}DateFormat;

void print_date(FILE* output, int day, int month, int year, DateFormat mode)
{
    switch (mode)
    {
    case DD_MM_YY:
        fprintf(output, "%02d.%02d.%02d\n", day, month, year);
        break;
    case DD_MM_YYYY:
        fprintf(output, "%02d.%02d.%04d\n", day, month, year);
        break;
    case YYYY_MM_DD:
        fprintf(output, "%04d/%02d/%02d\n", year, month, day);
        break;
    default:
        fprintf(output, "incorrect format\n");
        break;
    }
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        perror("not enough imput");
        return -1;
    }
    FILE* input  = fopen(argv[1], "r");
    FILE* output = fopen("out.txt", "a");
    if (!input || !output)
    {
        perror("cannot open files");
        return -1;
    }
    int d, m, y, k;
    while(fscanf(input, "%d %d %d %d", &d, &m, &y, &k) != EOF)
    {
        print_date(output, d, m, y, k);
    }
    fclose(input);
    fclose(output);
}