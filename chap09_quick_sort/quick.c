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
	pivot = list[left]; 	/* 피벗 설정 */
	do {
		do
			low++;
		/* 왼쪽 리스트에서 피벗보다 큰 레코드 선택 */
		while (low <= right && list[low] < pivot);
		do
			high--;
		/* 오른쪽 리스트에서 피벗보다 작은 레코드 선택 */
		while (high >= left && list[high] > pivot);
		if (low < high) SWAP(list[low], list[high], temp); /* 선택된 두 레코드 교환 */
	} while (low < high);	  /* 인덱스 i,j가 엇갈리지 않는 한 반복 */

	SWAP(list[left], list[high], temp); /* 인텍스 j가 가리키는 레코드와 피벗 교환 */
	return high;
}

//
void quick_sort(int list[], int left, int right)
{
	if (left < right) {     /* 리스트에 2개 이상의 레코드가 있을 경우 */
		int q = partition(list, left, right);
		print(list, 9);
		quick_sort(list, left, q - 1);         /* 왼쪽 부분리스트를 퀵정렬 */
		quick_sort(list, q + 1, right);       /* 오른쪽 부분리스트를 퀵정렬 */
	}
}
//
int main()
{
	quick_sort(list, 0, 8);
}
