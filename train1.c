#include <stdio.h>
#include <math.h>
int temperature()
{
	float temp_c = 0.0;
	scanf("%f", &temp_c);
	float temp_f = 1.8*temp_c + 32;
	return temp_f;
}

int vel()
{
	int vel_km = 0;
	scanf("%d", &vel_km);
	float vel_m = vel_km / 3.6;
	return vel_m;
}
int time_moments()
{
	int hour1 = 0;
	int min1 = 0;
	int sec1 = 0;
	int hour2 = 0;
	int min2 = 0;
	int sec2 = 0;
	scanf("%d %d %d %d %d %d", &hour1, &min1, &sec1, &hour2, &min2, &sec2);
	return (360*hour2+60*min2+sec2 - 360*hour1+60*min1+sec1);
}
int len(int a)
{
	int count = 1;
	while (a / 10 != 0)
	{
		count  = count + 1;
		a = a/10;
	}
	return count;
}
int math_swap(int a, int b)
{
	scanf("%d %d", &a, &b);
	b = b * (1/10 * len(b));
	a = a + b;
	b = (b - a) * (-1);
	a = a - b;
	if (a < 0.1)
	{
		a = a * 10;
	}
	do
	{
		a = a * 10;
	}while(a * 10 < 1);
	return a;

}

int base_2() 
{
	int base = 0;
	scanf("%d", &base);
	return 1<<base;
}

void get_dublicates(int* ar, int size)
{
	int temp[size];
	for (int i = 0, i < size, i++)
	{
		int flag = 0;
		for (int q = 0, q < size, q++)
		{
			if ar[i] == temp[q]
			{
				flag = 1;
			}
		}
		if flag == 1
		{
			continue;
		}
		else 
		{
			for (int q = 0; q < size, q++)
			{
				if ar[i] == ar[q] {
					temp[i] = ar[i];
					printf("%d", ar[i]);
				}
			}
		}
	}
}













int main()
{
	/*
	//1-st lesson, task_1
	printf("%s\n%s\n%s\n", "the first lesson, task_1", "Hello, world!", "________________________");
	
	//task_2
	int first_num = 0.0;
	int second_num = 0.0;
	printf("%s", "task_2. Enter two numbers(<float1> <float2>):");
	scanf("%d %d", &first_num, &second_num);
	float answer1 = first_num/second_num;
	float answer2 = first_num%second_num;
	printf("%s\t%f\t%s\t%f\n%s\n","division of ur two numbers without remainder", answer1, "ur remainer", answer2, "________________________");
	//task_3
	printf("%s", "task_3. Enter three caracters(<int> <double> <char>):");
	int num = 0;
	float double_num = 0.0;
	char char_num;
	scanf("%d %f %c", &num, &double_num, &char_num);
	printf("%s\t%d\t%f\t%c\n%s\t%lu\t%lu\t%lu\n%s\n", "Here are ur caracters:", num, double_num, char_num, "here are sizes or ur catacters", sizeof(num), sizeof(double_num), sizeof(char_num), "________________________");
	
	//2-nd lesson, task_2
	printf("%s", "lesson_2, task_2. Enter ur temperature C (<float>):");
	float answer = temperature();
	printf("%s\t%f\n%s\n", "this is ur temperature in Farengate:", answer, "________________________");
	
	//task_3
	printf("%s", "task_3. Enter ur velocity (<int>):");
	float answer = vel();
	printf("%s\t%f\n%s\n", "this is ur velocity in mph:", answer, "________________________");
	return 0;
	
	//task_4
	printf("task_4. Enter two moment of time(<hour_int1> <minute_int2> <second_int1> <hour_int2> <minute_int2> <seconds_int2>):");
	int answer = time_moments();
	printf("%s\t%d\n%s\n","amount seconds between ur moments:", answer, "_______________________");
	





	int a = 0;
	int b = 0;
	scanf("%d %d", &a, &b);
	int answer = math_swap(a, b);
	printf("%d", answer);

	//task_6
	printf("%s", "task_6. enter a base (<int>):");
	int answer = base_2();
	printf("%s\t%d\n%s\n", "here ur 2 ** base:", answer, "________________________");
	




	//lesson_4 task_1
	printf("%s", "lesson_4 task_1. Enter 6 coordinates or two vectors (<intx1> <inty1> <intz1> <intx2> <inty2> <intz2>):");
	int vector_1[3];
	int vector_2[3];

	for (int i = 0; i < 3; i++)
	{
		scanf("%d", &vector_1[i]);
	}
	for (int i = 0; i < 3; i++)
	{
		scanf("%d", &vector_2[i]);
	}

	int vector_sum[3];
	for (int i = 0; i < 3; i++)
	{
		vector_sum[i] = vector_1[i] + vector_2[i];
	}

	printf("%s\t%d\t%d\t%d\n%s\t%ld\n%s", "here ur summed vector of two last (x y z):", vector_sum[0], vector_sum[1], vector_sum[2], "this is a size of ur vector:", sizeof(vector_sum), "________________________");
	
	
	//task_2
	printf("task_2. enter ur float and a size (<float> <int>):");
	double x = 0.0;
	int n = 0;
	scanf("%lf%d", &x, &n);
	int array[n];
	printf("%s","enter coefficients(<int> <int>...<int>):");
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &array[i]);
	}
	int answer = 0;
	for (int i = n; i != 0; i--)
	{
		answer += array[i-1] * pow(x,i);
	}
	printf("%s\t%d\n%s\n", "here is ur sub", answer, "________________________");	
	*/
	
	return 0;
}
