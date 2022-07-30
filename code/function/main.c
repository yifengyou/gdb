#include <stdio.h>

int global = 1;

int func(void)
{
	return (++global);
} 

int main(void)
{
	int a = 0;
	a = func();
	printf("%d\n", a);
	return 0;
}
