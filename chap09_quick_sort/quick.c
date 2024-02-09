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
#endif
#if ex02
int n = 10;
int arr[1000001] = { 15, 25, 22, 357, 16, 23, -53, 12, 46, 3 };

void quick_sort(int st, int en) { // arr[st to en-1]�� ������ ����
	if (en <= st + 1) return; // ������ ���̰� 1 �����̸� �Լ� ����.(base condition)
	int pivot = arr[st]; // ���� ���� ���� pivot���� ��´�. ������ ���� ��� arr[st]�� swap�ص� �������.
	int l = st + 1; // ������ l
	int r = en - 1; // ������ r
	int temp = 0;
	while (1) {
		while (l <= r && arr[l] <= pivot) l++;
		while (l <= r && arr[r] >= pivot) r--;
		if (l > r) break; // l�� r�� �����Ǵ� �� ��� Ż��
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
