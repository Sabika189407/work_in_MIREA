#include <stdio.h>
#include <math.h>


int is_tr(float a, float b, float c) {
	if (a + b > c && a + c > b && b + c > a) {
		return 1;
	}
	else {
		return 0;
	}
}
int sum_of_number(int a)
{
	int sum = 0;
	while (a > 0)
	{
		sum += a % 10;
		a = a/10;
	}
	return sum;
}

int prod_of_number(int a)
{
	int pr = 1;
	while (a > 0)
	{
		pr *= a % 10;
		a = a/10;
	}
	return pr;
}

int main() {
	const double g_pi = 3.14159;
	//task_1
	float x1;
	float x2;
	float y1;
	float y2;
	
	printf("%s", "enter cordinates of two points - (<x y> <x y>):");
	scanf("%f %f", &x1, &y1);
	scanf("%f %f", &x2, &y2);
	
	float k = (y1 - y2) / (x1 - x2);
	float b = y2 - k*x2;

	printf("%s\n", "task_1");
	printf("%s\t%s\t%+.2f\t%s\t%+.2f\n", "Your answer is:", "b=", b, "k=", k);
	
	//task_2
	float side_tr_1, side_tr_2, side_tr_3;
	float height_rec, width_rec;
	float rad;
	
	printf("%s\n%s", "task_2", "enter three sides of a triangle (<side1> <side2> <side3>):");

	scanf("%f %f %f", &side_tr_1, &side_tr_2, &side_tr_3);

	if (is_tr(side_tr_1, side_tr_2, side_tr_3) == 1) {
		float per = side_tr_1 + side_tr_2 + side_tr_3;
		float area = sqrt(per/2*(per/2 - side_tr_1)*(per/2 - side_tr_2)*(per/2-side_tr_3));
		printf("%s\t%.4f\t%s\t%.4f\n", "Your perimeter of triangle=", per, "Your area of triangle = ", area);
	}
	else {
		printf("%s\n", "Your triangle does not exist");
	}
	printf("%s", "enter a height and width of a rectangle (<height> <width>):");
	scanf("%f %f", &height_rec, &width_rec);
	float per = 2 * (height_rec + width_rec);
	float area  = height_rec * width_rec;
	printf("%s\t%.4f\t%s\t%.4f\n", "Your perimeter of rectangle", per, "Your area of rectangle = ", area);
	
	printf("%s", "enter a radius of a circle (<radius>):");
	scanf("%f", &rad);
	per = 2 * g_pi * rad;
	area = g_pi * pow(rad, 2);
	printf("%s\t%.4f\t%s\t%.4f\n", "Your perimeter of circle=", per, "Your area of circle = ", area);
	
	//task_3
	int num;
	int wide;
	printf("%s\n%s\n", "task_3", "enter a three-digit number and a wide of the next answer:");
	scanf("%d %d", &num, &wide);
	printf("%s\t%o\t%s\t%o\n%s\t%X\t%s\t%x\n", "This is ur number in OCT:", num, "and ur number in oct:", num, "This is ur number in HEX:", num, "and ur number in hex:", num);
	int sum = sum_of_number(num);
	int pr = prod_of_number(num);
	printf("%s\t%*d\t%s\t%*d\n", "This is a sum of numbers:",wide, sum, "and this is a product of numbers:", wide, pr);
	return 0;
}
