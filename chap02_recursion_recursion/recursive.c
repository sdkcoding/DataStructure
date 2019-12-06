#include <stdio.h>

int factorial(int n)
{
	printf("factorial(%d)\n", n);
	if( n == 1 ) return(1);
	else
	return (n * factorial(n - 1));
}
int main()
{
	int value;
	value = factorial(8);
	printf("°è»ê°ª=%d\n", value);
}
