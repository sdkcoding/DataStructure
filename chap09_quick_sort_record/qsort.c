#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )
#define MAX_WORD_SIZE 50
#define MAX_MEANING_SIZE 500
#define MAX_SIZE 1000

typedef struct {
	char word[MAX_WORD_SIZE];
	char meaning[MAX_MEANING_SIZE];
} element;
element list[MAX_SIZE];   	/* 구조체 배열 선언 */
int n;

// e1 > e2 -> 1
// e1 == e2 -> 0
// e2 < e2 -> -1
int compare(element e1, element e2)
{
	return strcmp(e1.word, e2.word);
}
//
int partition(element list[], int left, int right)
{
	element pivot, temp;
	int low, high;

	low = left;
	high = right + 1;
	pivot = list[left];
	do {
		do
			low++;
		while (compare(list[low], pivot) < 0);
		do
			high--;
		while (compare(list[high], pivot) > 0);
		if (low < high) SWAP(list[low], list[high], temp);
	} while (low < high);

	SWAP(list[left], list[high], temp);
	return high;
}
//
void quick_sort(element list[], int left, int right)
{
	if (left < right) {
		int q = partition(list, left, right);
		quick_sort(list, left, q - 1);
		quick_sort(list, q + 1, right);
	}
}
//
void help()
{
	printf("**************\n");
	printf("i: 입력\n");
	printf("s: 정렬\n");
	printf("p: 출력\n");
	printf("q: 종료\n");
	printf("**************\n");
}
//
void insert(element e)
{
	if (n < (MAX_SIZE - 1))
		list[n++] = e;
}
//
void print()
{
	int i;
	for (i = 0; i < n; i++) {
		printf("%s:%s\n", list[i].word, list[i].meaning);
	}
}

void ClearLineFromReadBuffer(void)
{
	while (getchar() != '\n');
}

void main()
{
	char command;
	element e;

	do {
		help();
		scanf_s("%c", &command, 1);
		ClearLineFromReadBuffer();
		switch (command) {
		case 'i':
			printf("단어:");
			fgets(e.word, sizeof(e.word), stdin);
			e.word[strlen(e.word) - 1] = '\0';
			printf("의미:");
			fgets(e.meaning, sizeof(e.meaning), stdin);
			e.meaning[strlen(e.meaning) - 1] = '\0';
			insert(e);
			break;
		case 's':
			quick_sort(list, 0, n - 1);
			break;
		case 'p':
			print();
			break;

		}

	} while (command != 'q');
}
