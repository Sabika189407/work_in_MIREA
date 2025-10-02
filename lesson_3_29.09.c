#include <stdio.h>



int main() 
{
	//task_2
	int size = 0;
	printf("%s\n%s\n", "task_2", "enter a size of algebra function and ur number(<size> <number>):");
	double num = 0.0;
	scanf("%d %d", &size, &num);
	double answer = 0;
	for (int i = 1; i++; i < size)
	{
		answer+= size*num**(size-1);
	}
	printf(
	return 0;
}
