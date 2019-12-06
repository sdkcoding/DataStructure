/*
 *	arraystack2.c
 */
#include <stdio.h>
#include <string.h>

#define MAX_STACK_SIZE 100
#define MAX_STRING 100

typedef struct  { 
	int student_no;
	char name[MAX_STRING];
	char address[MAX_STRING];
} StackObject;

StackObject  stack[MAX_STACK_SIZE]; 
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
	StackObject ie;
	StackObject oe;

	strcpy(ie.name, "HongGilDong");
	strcpy(ie.address, "Seoul");
	ie.student_no = 20053001;
	push(ie);
	oe = pop();
	printf("name: %s\n", oe.name);
	printf("address: %s\n", oe.address);
	printf("student number: %d\n", oe.student_no);
}
