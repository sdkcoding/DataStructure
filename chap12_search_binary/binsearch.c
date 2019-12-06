#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define	MAX_SIZE	10000000
int list[MAX_SIZE];

// ������������ ���ĵ� �迭 ����Ʈ�� ����Ž�� 
int sorted_seq_search(int key, int low, int high)
{
	int i;
	for (i = low; i <= high; i++) {
		if (list[i] > key) return -1;
		if (list[i] == key) return i;
	}
}

//��� ȣ���� �̿��� ���� Ž��
int search_binary(int key, int low, int high)
{
	int middle;
	if (low <= high) {
		middle = (low + high) / 2;
		if (key == list[middle])    // Ž�� ����
			return middle;
		else if (key < list[middle]) // ���� �κи���Ʈ Ž�� 
			return search_binary(key, low, middle - 1);
		else                   // ������ �κи���Ʈ Ž�� 
			return search_binary(key, middle + 1, high);
	}
	return -1;        // Ž�� ����
}

//�ݺ��� �̿��� ���� Ž��
int search_binary2(int key, int low, int high)
{
	int middle;

	while (low <= high) {       // ���� ���ڵ��� ���� ������
		middle = (low + high) / 2;
		if (key == list[middle])
			return middle;
		else if (key > list[middle])
			low = middle + 1;
		else
			high = middle - 1;
	}
	return -1;   // �߰ߵ��� ���� 
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

