#include <stdio.h>

double calculate_series(int n)
{
	if( n==1 ) return 1;
	else return ( calculate_series(n-1) + 1/n );
}

main()
{
	printf("%f", calculate_series(10));
}

