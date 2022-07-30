#include <stdio.h>

int result;

int add(int a, int b)
{
	return a+b;
}

int main()
{
	result = add(1,2);
	printf("%d\n", result);
}
