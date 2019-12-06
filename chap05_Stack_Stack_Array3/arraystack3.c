/*
 *	arraystack3.c
 */
#include <stdio.h>

#define MAX_STACK_SIZE 100

typedef int StackObject;

struct StackRec {
	StackObject stack[MAX_STACK_SIZE];
	int top;
};
typedef struct StackRec StackType;

void initialize(StackType *s)
{
	(*s).top = -1;
}

int isEmpty(StackType *s)
{
	return ((*s).top == -1);
}

int isFull(StackType *s)
{
	return ((*s).top == (MAX_STACK_SIZE-1));
}

void push(StackType *s, StackObject item)
{ 
  	  if( isFull(s) ) { 
		  printf("stack is full\n");
	  } 
	  else (*s).stack[++(*s).top] = item; 
}

StackObject pop(StackType *s) 
{ 
   	if( isEmpty(s) ) {
		printf("stack is empty\n");
	}
	else return (*s).stack[(*s).top--]; 
} 

void main()
{
	StackType s;

	initialize(&s);
	push(&s, 1);
	push(&s, 2);
	push(&s, 3);
	printf("%d\n", pop(&s));
	printf("%d\n", pop(&s));
	printf("%d\n", pop(&s));
	printf("%d\n", isEmpty(&s));
}
