#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "check.h"
#include "calc.h"

int check_imput(int* size, char** ar)
{
	if (size == NULL || ar == NULL)
	{
		printf("pointers are NULL!\n");
		return 1;
	}
	if (*size <= 2  || (*size-1) % 3 != 0)
	{
		printf("incorret imput\n");
		for (int i = 1; i < size; i++)
		{
			if (isdigit(ar[i]))
		return 1;
	}
	return 0;
}

int main(int argc, char** argv)
{
	printf("%d", argc);
	check_imput(&argc, argv);
	return 0;
}
