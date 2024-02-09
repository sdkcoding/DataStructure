#include <stdio.h>
#include <stdlib.h>
#include <windows.h> //windows.h ��� �߰�
#pragma comment(lib, "Winmm.lib") //winmm.lib �߰�

#define	MAX_SIZE	100000000
int list[MAX_SIZE];

//������������ ���ĵ� �迭 ����Ʈ�� ����Ž�� 
int sorted_seq_search(int key, int low, int high)
{
	int i;
	for (i = low; i <= high; i++) {
		if (list[i] > key) return -1;
		if (list[i] == key) return i;
	}
}

//������������ ���ĵ� �迭 ����Ʈ�� ��� ȣ���� �̿��� ���� Ž��
int search_binary1(int key, int low, int high)
{
	int middle;
	if (low <= high) {
		middle = (low + high) / 2;
		if (key == list[middle])    // Ž�� ����
			return middle;
		else if (key < list[middle]) // ���� �κи���Ʈ Ž�� 
			return search_binary1(key, low, middle - 1);
		else                   // ������ �κи���Ʈ Ž�� 
			return search_binary1(key, middle + 1, high);
	}
	return -1;        // Ž�� ����
}

//������������ ���ĵ� �迭 ����Ʈ�� �ݺ��� �̿��� ���� Ž��
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
	unsigned __int64 start;
	unsigned __int64 end;
	int resultIndex;
	int i;
	for (i = 0; i < MAX_SIZE; i++) {
		list[i] = i;
	}

	start = GetTickCount64();
	resultIndex = sorted_seq_search(90000000, 0 , MAX_SIZE-1);
	end = GetTickCount64();
	printf("%lld\n", end - start);
	printf("%d\n", resultIndex);

	start = GetTickCount64();
	resultIndex = search_binary1(90000000, 0, MAX_SIZE - 1);
	end = GetTickCount64();
	printf("%lld\n", end - start);
	printf("%d\n", resultIndex);

	start = GetTickCount64();
	resultIndex = search_binary2(90000000, 0, MAX_SIZE - 1);
	end = GetTickCount64();
	printf("%lld\n", end - start);
	printf("%d\n", resultIndex);

	return 0;
}

