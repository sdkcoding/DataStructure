#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define	MAX_SIZE	10000000
int list[MAX_SIZE];

// 오름차순으로 정렬된 배열 리스트의 순차탐색 
int sorted_seq_search(int key, int low, int high)
{
	int i;
	for (i = low; i <= high; i++) {
		if (list[i] > key) return -1;
		if (list[i] == key) return i;
	}
}

//재귀 호출을 이용한 이진 탐색
int search_binary(int key, int low, int high)
{
	int middle;
	if (low <= high) {
		middle = (low + high) / 2;
		if (key == list[middle])    // 탐색 성공
			return middle;
		else if (key < list[middle]) // 왼쪽 부분리스트 탐색 
			return search_binary(key, low, middle - 1);
		else                   // 오른쪽 부분리스트 탐색 
			return search_binary(key, middle + 1, high);
	}
	return -1;        // 탐색 실패
}

//반복을 이용한 이진 탐색
int search_binary2(int key, int low, int high)
{
	int middle;

	while (low <= high) {       // 아직 숫자들이 남아 있으면
		middle = (low + high) / 2;
		if (key == list[middle])
			return middle;
		else if (key > list[middle])
			low = middle + 1;
		else
			high = middle - 1;
	}
	return -1;   // 발견되지 않음 
}


int main()
{
	clock_t start;
	int resultIndex;
	int i;
	for (i = 0; i < MAX_SIZE; i++) {
		list[i] = i;
	}

	start = (int)clock();
	resultIndex = sorted_seq_search(34, 0 , MAX_SIZE-1);
	printf("%0.5f\n", (float)(clock() - start) / CLOCKS_PER_SEC);
	printf("%d\n", resultIndex);

	start = (int)clock();
	resultIndex = search_binary(34, 0, MAX_SIZE - 1);
	printf("%0.5f\n", (float)(clock() - start) / CLOCKS_PER_SEC);
	printf("%d\n", resultIndex);

	start = (int)clock();
	resultIndex = search_binary2(34, 0, MAX_SIZE - 1);
	printf("%0.5f\n", (float)(clock() - start) / CLOCKS_PER_SEC);
	printf("%d\n", resultIndex);

	return 0;
}

