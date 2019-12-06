
#include <stdio.h>
#include <limits.h>

#define TRUE	1
#define FALSE	0
#define VERTICES	7		/* 정점의 수 */
#define INF	10000	/* 무한대 (연결이 없는 경우) */

/* 네트워크의 인접행렬 */
int weight[VERTICES][VERTICES]={
	{   0,  7,  INF, INF,   3,  10, INF },
	{   7,  0,    4,  10,   2,   6, INF },
	{ INF,  4,    0,   2, INF, INF, INF },
	{ INF, 10,    2,   0,  11,   9,   4 },
	{   3,  2,  INF,  11,   0, INF,   5 },
	{  10,  6,  INF,   9, INF,   0, INF },
	{ INF, INF, INF,   4,   5, INF,   0 }};

int A[VERTICES][VERTICES];

printA(int n)
{
	int i, j, k;
	printf("===============================\n");
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			if( A[i][j] == INF )
				printf("INF ");
				else printf("%3d ", A[i][j]);
		}
		printf("\n");
	}
	printf("===============================\n");
}
void floyd(int n)  
{ 

	int i, j, k;
	for(i=0; i<n; i++)
		for(j=0; j<n; j++)
			A[i][j]=weight[i][j];

		for(k=0; k<n; k++){
		for(i=0; i<n; i++)
	   		for(j=0; j<n; j++)
	      		if (A[i][k]+A[k][j] < A[i][j])
	         		A[i][j] = A[i][k]+A[k][j];
				printA(n);
		}
}

main()
{
	floyd(VERTICES);
}
