#include <stdio.h>

#define MAX_SIZE 100
int n = 9;
int list[MAX_SIZE] = { 9, 8, 7, 6, 5, 4, 3, 2, 1 };
#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )
//
print(int list[], int n)
{
	int i;
	for (i = 0; i < n; i++)
		printf("%d ", list[i]);
	printf("\n");
}
//
int partition(int list[], int left, int right)
{
	int pivot, temp;
	int low, high;

	low = left;
	high = right + 1;
	pivot = list[left]; 	/* �ǹ� ���� */
	do {
		do
			low++;
		/* ���� ����Ʈ���� �ǹ����� ū ���ڵ� ���� */
		while (low <= right && list[low] < pivot);
		do
			high--;
		/* ������ ����Ʈ���� �ǹ����� ���� ���ڵ� ���� */
		while (high >= left && list[high] > pivot);
		if (low < high) SWAP(list[low], list[high], temp); /* ���õ� �� ���ڵ� ��ȯ */
	} while (low < high);	  /* �ε��� i,j�� �������� �ʴ� �� �ݺ� */

	SWAP(list[left], list[high], temp); /* ���ؽ� j�� ����Ű�� ���ڵ�� �ǹ� ��ȯ */
	return high;
}

//
void quick_sort(int list[], int left, int right)
{
	if (left < right) {     /* ����Ʈ�� 2�� �̻��� ���ڵ尡 ���� ��� */
		int q = partition(list, left, right);
		print(list, 9);
		quick_sort(list, left, q - 1);         /* ���� �κи���Ʈ�� ������ */
		quick_sort(list, q + 1, right);       /* ������ �κи���Ʈ�� ������ */
	}
}
//
int main()
{
	quick_sort(list, 0, 8);
}
