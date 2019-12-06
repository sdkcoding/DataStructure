#include <stdio.h>
#include <stdlib.h>
#define	MAX_SIZE	100
#define	MAX_STRING	20
#define MAX_STUDENT	3

typedef struct {
	int student_no;
	char name[MAX_STRING];
}element;

typedef struct {
	element stack[MAX_SIZE];
	int top;
}StackType;

void init(StackType * s) {
	s->top = -1;
}

int is_empty(StackType * s) {
	return (s->top == -1);
}

int is_full(StackType * s) {
	return (s->top == (MAX_SIZE - 1));
}

void push(StackType * s, element item) {
	if (is_full(s)) exit(1);
	else s->stack[++(s->top)] = item;
}

element pop(StackType * s) {
	if (is_empty(s)) exit(1);
	else return s->stack[(s->top)--];
}

int main(void)
{
	StackType StudentStack;
	element item;
	init(&StudentStack);
	for (int i = 0; i < MAX_STUDENT; i++) {
		fputs("�л� �й��� �Է� : ", stdout); scanf("%d", &(item.student_no)); getchar();
		fputs("�л� �̸��� �Է� : ", stdout); fgets(item.name, sizeof(item.name), stdin);
		push(&StudentStack, item);
	}
	for (int i = 0; i < MAX_STUDENT; i++) {
		item = pop(&StudentStack);
		printf("�л� �й� : %d\n", item.student_no);
		printf("�л� �̸� : %s\n", item.name);
	}
	return 0;
}