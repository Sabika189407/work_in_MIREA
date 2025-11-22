#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "check.h"
int check_imput(int* size, char** ar)
{
	if (size == NULL || ar == NULL)
	{
		printf("pointers are NULL\n");
		return 1;
	}
    if (*size <= 2 || (*size-1) % 3 != 0)
    {
        printf("not enough data for run programm. Pls write more imput\n");
        return 1;
    }
    else
    {
	    if (*size >= 2 || (*size-1) % 3 == 0)
	    {
		    for (int i = 1; i < *size; i++)
		    {
			    if (i % 3 == 1 || i % 3 == 0)
			    {
				    if (isdigit(ar[i]) == 0)
				    {
					    printf("not digit in imput");
					    return 1;
			    	}
			    }
		    }
		    for (int i = 2; i < *size; i += 3)
            {
                if (strcmp(ar[i], "+") != 0 || strcmp(ar[i], "-") != 0 || strcmp(ar[i], "\"*\"") != 0 || strcmp(ar[i], "/") || strcmp(ar[i], "\%") != 0)
                {
                    printf("not a operand in imput\n");
                    return 1;
                }
            }
        }
    }
    return 0;
}
