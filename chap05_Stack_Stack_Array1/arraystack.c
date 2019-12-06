/*
 *	arraystack.c
 */
#include <stdio.h>

#define MAX_STACK_SIZE 100
typedef int StackObject;
int  stack[MAX_STACK_SIZE]; 
int  top = -1; 

void initialize()
{
	top = -1;
}

int isEmpty()
{
	return (top == -1);
}

int isFull()
{
	return (top == (MAX_STACK_SIZE-1));
}

void push(StackObject item)
{ 
  	  if( isFull() ) { 
		  printf("stack is full\n");
	  } 
	  else stack[++top] = item; 
}

StackObject pop() 
{ 
   	if( isEmpty() ) {
		printf("stack is empty\n");
	}
	else return stack[top--]; 
} 

void main()
{
	push(1);
	push(2);
	push(3);
	printf("%d\n", pop());
	printf("%d\n", pop());
	printf("%d\n", pop());
	printf("%d\n", isEmpty());
}


