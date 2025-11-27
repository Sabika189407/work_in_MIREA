#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "check.h"

int is_number(char* ar)
{
	if (ar == NULL || ar[0] == '\0')
	{
		printf("pointer is NULL!\n");
		return -1;
	}

	if (ar[0] == '-')
	{
		for (int i = 1; ar[i] != '\0'; i++)
		{
			if (isdigit(ar[i]) == 0)
			{
				return 1;
			}
		}
	}
	else
	{
		for (int i = 0; ar[i] != '\0'; i++)
		{
			if (isdigit(ar[i]) == 0)
			{
				return 1;
			}
		}
	}
	return 0;
}

int is_operand(char* ar)
{
	if (ar == NULL)
	{
		printf("pointer is NULL!\n");
		return -1;
	}
	if (ar[0] != '+' &&
		ar[0] != '-' &&
		ar[0] != '*' &&
		ar[0] != '%')
	{
		return 1;
	}
	
	return 0;
}

int check_imput(int* size, char** ar)
{
	if (size == NULL || ar == NULL)
	{
		printf("pointers are NULL\n");
		return -1;
	}
	
	if (*size <= 2)
        {
                printf("imput is empty\n");
                return 1;
        }
	int flag = 0;

	for (int i = 0; i < *size; i++)
	{
		if (strcmp(ar[i], "-k") == 0)
		{
			flag = 1;
		}
	}

	if (flag == 0 || is_number(ar[(*size)-1]) != 0)
	{
		printf("flag \"-k\" not included or it was written incorrectly\n");
		return 1;
	}
	
	if (*size % 3 != 0)
	{
		printf("not enough operands\n");
		return 1;
	}
	
	int count = 0;
	for (int i = 2; i < (*size)-2; i += 3)
	{
		count++;
	}

	for (int i = 0; i < count; i++)
	{
		if (is_operand(ar[2 + i*3]) != 0)
		{
			printf("%s %c\n", "incorrect operand in input:", *ar[2 + i*3]);

			return 1;
		}
		if (is_number(ar[2 + i*3 - 1]) != 0)
		{
			 printf("%s %c\n", "incorrect number in input:", *ar[2 + i*3 - 1]);
			 return 1;
		}
		if (is_number(ar[2 + i*3 + 1]) != 0)
		{
			printf("%s %c\n", "incorrect number in input:", *ar[2 + i*3 + 1]);
			return 1;
		}
	}
    	return 0;
}
