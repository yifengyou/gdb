#include<stdio.h>

void a(void)
{
	printf("Tail call frame\n");
} 

void b(void)
{
	a();
}

void c(void)
{
	b();
}

int main(void)
{
	c();
	return 0;
}
