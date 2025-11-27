#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "calc.h"
#include "check.h"

void calc(int* size, char** ar)
{
	int iterator = atoi(ar[*size-1]);
	int count = 0;
	for (int i = 2; i < (*size)-2; i += 3)
	{
		count++;
	}
	
	
	char* answer = (char*) calloc(count + 1, sizeof(char));	
	for (int i = 0; i < count; i++)
	{
		int letter = 0;
		if (*ar[2 + i*3] == '+')
		{
			letter = ((atoi(ar[2 + i*3 -1]) + atoi(ar[2 + i*3 + 1])) - iterator);
		}
		else if (*ar[2 + i*3] == '-')
		{
			letter = ((atoi(ar[2 + i*3 -1]) - atoi(ar[2 + i*3 + 1])) - iterator);
		}
		else if (strcmp(ar[2 + i*3], "\"*\"") == 0)
		{
			letter = ((atoi(ar[2 + i*3 -1]) * atoi(ar[2 + i*3 + 1])) - iterator);
		}
		else if (*ar[2 + i*3] == '%')
		{
			letter = ((atoi(ar[2 + i*3 -1]) % atoi(ar[2 + i*3 + 1])) - iterator);
		}

			printf("Ответ №%d: %d\n", i+1,letter+iterator);
			answer[i] = (char)letter;
	}
	answer[count] = '\0';
	printf("Результирующая строка: %s\n", answer);
	free(answer);
}
