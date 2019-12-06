#include <stdio.h>
#include <stdlib.h>

#define ROWS 3
#define COLS 3

#define MAX_TERMS 10 
typedef struct { 
    int row; 
    int col; 
    int value; 
} element; 

typedef struct SparseMatrix {
	element data[MAX_TERMS];
	int rows;	// ���� ����
	int cols;	// ���� ����
	int terms; 	// 0�� �ƴ� ���� ����
} SparseMatrix;

// ��� ��� ���� �Լ�
void sparse_matrix_add(int A[ROWS][COLS], 
		int B[ROWS][COLS], int C[ROWS][COLS])  // C=A+B
{	
	int r,c;
	for(r=0;r<ROWS;r++)
		for(c=0;c<COLS;c++)
			C[r][c] = A[r][c] + B[r][c];
}

// ��� ��� ���� �Լ�
SparseMatrix sparse_matrix_add2(SparseMatrix a, SparseMatrix b)  // C=A+B
{	
	SparseMatrix c;
	int ca=0, cb=0, cc=0;
	// ũ�Ⱑ �������� Ȯ��
	if( a.rows != b.rows || a.cols != b.cols ){
		fprintf(stderr,"������ ũ�⿡��\n");
		exit(1);
	}
	c.rows = a.rows;
	c.cols = a.cols;
	c.terms = 0;

	while( ca < a.terms && cb < b.terms ){
		int inda = a.data[ca].row * a.cols + a.data[ca].col;
		int indb = b.data[cb].row * b.cols + b.data[cb].col;
		if( inda < indb) {
			// b �׸��� �� ���߿� �;� ��
			c.data[cc++] = a.data[ca++];
		}
		else if( inda == indb ){
			// a�� b�� ���� ��ġ
			c.data[cc].row = a.data[ca].row;
			c.data[cc].col = a.data[ca].col;
			c.data[cc++].value = a.data[ca++].value +
					      b.data[cb++].value;
		}
		else 
			c.data[cc++] = b.data[cb++];
		
	}
	// �������׵��� �ű��.
	for(; ca < a.terms; ca++)
		c.data[cc++] = a.data[ca++];
	for(; cb < b.terms; cb++)
		c.data[cc++] = b.data[cb++];
	c.terms = cc;
	return c;
}
// ���Լ�
#if 1
main()
{
	SparseMatrix m1 = {	{{ 1,1,5 },{ 2,2,9 }}, 3,3,2 };
	SparseMatrix m2 = {	{{ 0,0,5 },{ 2,2,9 }}, 3,3,2 };
	SparseMatrix m3;

	m3 = sparse_matrix_add2(m1, m2);
}
#endif
#if 0
// ���Լ�
main()
{
	int array1[ROWS][COLS] = {	{ 2,3,0 },
					{ 8,9,1 },
					{ 7,0,5 } };
	int array2[ROWS][COLS] = {	{ 1,0,0 },
					{ 1,0,0 },
					{ 1,0,0 } };
	int array3[ROWS][COLS];
	sparse_matrix_add(array1,array2,array3);
}
#endif