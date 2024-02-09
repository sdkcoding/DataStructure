#include <stdio.h>
#define	ex01	0
#define	ex02	1
#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )

#if ex01
#define MAX_SIZE 100
int n = 9;
int list[MAX_SIZE] = { 9, 8, 7, 6, 5, 4, 3, 2, 1 };

void print(int list[], int n)
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
#endif
#if ex02
int n = 10;
int arr[1000001] = { 15, 25, 22, 357, 16, 23, -53, 12, 46, 3 };

void quick_sort(int st, int en) { // arr[st to en-1]을 정렬할 예정
	if (en <= st + 1) return; // 수열의 길이가 1 이하이면 함수 종료.(base condition)
	int pivot = arr[st]; // 제일 앞의 것을 pivot으로 잡는다. 임의의 값을 잡고 arr[st]와 swap해도 상관없음.
	int l = st + 1; // 포인터 l
	int r = en - 1; // 포인터 r
	int temp = 0;
	while (1) {
		while (l <= r && arr[l] <= pivot) l++;
		while (l <= r && arr[r] >= pivot) r--;
		if (l > r) break; // l과 r이 역전되는 그 즉시 탈출
		SWAP(arr[l], arr[r], temp);
	}
	SWAP(arr[st], arr[r], temp);
	quick_sort(st, r);
	quick_sort(r + 1, en);
}

int main() {
	quick_sort(0, n);
	for (int i = 0; i < n; i++) 
		printf("%d ", arr[i]);
}
#endif // ex02
