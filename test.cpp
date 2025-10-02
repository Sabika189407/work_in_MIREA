#include <iostream>



int sum_of_num(int a) 
{
	int sum = 0;
	while (a > 0)
	{
		sum += a%10;
		a = a/10;
	}
	return sum;
}

int task_test()
{
	for (int x = 0; x < 5; x++)
	{
		if ((x < 3) && ((x < 2) | (x > 2)))
		{
			std::cout<<x<<std::endl;
		}
	}
	return 0;
}

int main()
{
	int a = 125;
/*	int a = 0;
	scanf("%d", &a);
	int answer = sum_of_num(a);
	printf("%s\t%d\n", "Your sum of numbers is:", answer); */
	//task_test();
	sum_of_num(a);
	return 0;
}
