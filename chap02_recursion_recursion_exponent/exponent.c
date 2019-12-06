#include <stdio.h>
#include <time.h>

//
double fast_expon(double x, int n)
{
	if( n==0 ) return 1;
	else if ( (n%2)==0 ) {
		return fast_expon(x*x, n/2);
	}
	else return x*fast_expon(x*x, (n-1)/2);
}
//
double expon(double x, int n)
{
	int i;
	double r=1;
	for(i=0;i<n;i++)
		r = r * x;
	return r;
}
//
void main()
{
	int i;
	double r;
	clock_t start, end;
	start = clock();
	for(i=0;i<1000000;i++)
		r = expon(2,500);
	end =clock();
	printf("%f\n", (double)(end - start) / CLOCKS_PER_SEC);
}
