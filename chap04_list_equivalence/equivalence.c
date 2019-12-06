/*
	day : 2016.01.20
	<content>
	음이 아닌 10미만 정수에 대해 %3이 같은 수
	equivalence relation(동치 관계) : 0≡9, 4≡1, 8≡5, 6≡3, 1≡7, 5≡2, 9≡6
	equivalence class(동치 부류) : {0,3,6,9},{1,4,7},{2,5,8}
*/
#include <stdio.h>
#include <stdlib.h>
#define	MAX_SIZE	10
#define TRUE		1
#define	FALSE		0

typedef int element;
typedef struct ListNode * NodePtr;
typedef struct ListNode {
	element data;
	NodePtr link;
}ListNode;

/*
	typedef struct ListNode{
		element data;
		struct ListNode * link;
	}ListNode;
*/

NodePtr	seq[MAX_SIZE];
int out[MAX_SIZE];

void equ_pairs(int i, int j) {
	NodePtr	p;					//ListNode * p;
	p = (ListNode*)malloc(sizeof(ListNode));
	p->data = j; p->link = seq[i]; seq[i] = p;
	p = (ListNode*)malloc(sizeof(ListNode));
	p->data = i; p->link = seq[j]; seq[j] = p;
}

void equ_class(void) {
	NodePtr p, tmp, top;
	int i, j;
	for (i = 0; i < MAX_SIZE; i++) {
		out[i] = TRUE; seq[i] = 0;
	}
	equ_pairs(0, 9);	equ_pairs(4, 1);
	equ_pairs(8, 5);	equ_pairs(6, 3);
	equ_pairs(1, 7);	equ_pairs(5, 2);
	equ_pairs(9, 6);
	for (i = 0; i < MAX_SIZE; i++) {
		if (out[i]) {
			printf("[%d] : %d", i, i);
			out[i] = FALSE; p = seq[i];
			top = 0;			//스택 초기화
			for (;;) {
				while (p) {
					j = p->data;
					if (out[j]) {
						printf(", %d", j);
						out[j] = FALSE; tmp = p->link;
						p->link = top; top = p; p = tmp;
					}
					else
						p = p->link;
				}
				if (!top) break;
				p = seq[top->data]; top = top->link;
			}
			printf("\n");
		}
	}
}

int main(void) {
	equ_class();
	return 0;
}