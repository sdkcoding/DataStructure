#include <stdio.h>¡¡ 
#include <malloc.h>
#include <time.h>

typedef int element;
typedef struct StackNode {
	element item;
	struct StackNode * link;
}StackNode;

typedef struct {
	StackNode *top;
}LinkedStack;

void init(LinkedStack *s) {
	s->top = NULL;
}

int is_empty(LinkedStack * s) {
	return (s->top == NULL);
}

int is_full(LinkedStack * s) {
	return 0;
}

void push(LinkedStack * s, element item) {
	StackNode * t =
		(StackNode *)malloc(sizeof(StackNode));
	if (t == NULL) exit(1);
	t->item = item;	t->link = s->top; s->top = t;
}

element pop(LinkedStack * s) {
	if (is_empty(s)) exit(1);
	StackNode * t = s->top; element item = t->item;
	s->top = s->top->link; free(t);
	return item;
}

int main(void)
{
	clock_t Start = clock();
	LinkedStack StackList;
	init(&StackList);
	for (int i = 10; i < 40; i += 10) {
		push(&StackList, i);
	}
	for (int i = 0; i < 3; i++) {
		printf("%d\n", pop(&StackList));
	}
	clock_t finish = clock();
	double end = (double)(finish - Start) / CLOCKS_PER_SEC;
	printf("Time Delay : %f second\n", end);
	return 0;
}