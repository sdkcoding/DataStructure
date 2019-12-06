#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100
typedef int element;
typedef struct {
	element stack[MAX_STACK_SIZE];
	int top;
} StackType;

// ���� �ʱ�ȭ �Լ�
void init(StackType *s)
{
	s->top = -1;
}
// ���� ���� ���� �Լ�
int is_empty(StackType *s)
{
	return (s->top == -1);
}
// ��ȭ ���� ���� �Լ�
int is_full(StackType *s)
{
	return (s->top == (MAX_STACK_SIZE-1));
}
// �����Լ�
void push(StackType *s, element item)
{ 
  	  if( is_full(s) ) { 
		fprintf(stderr,"���� ��ȭ ����\n");
		return; 		 
	  } 
	  else s->stack[++(s->top)] = item; 
}
// �����Լ�
element pop(StackType *s) 
{ 
   	if( is_empty(s) ) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1); 		
	}
	else return s->stack[(s->top)--]; 
} 
// ��ũ�Լ�
element peek(StackType *s) 
{ 
   	if( is_empty(s) ) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1); 		
	}
	else return s->stack[s->top]; 
}

// ���� ǥ�� ���� ��� �Լ�
eval(char exp[])
{   
int op1, op2, value, i=0;
int len = strlen(exp);
char ch;
StackType s;

init(&s);
for( i=0; i<len; i++){
	ch = exp[i];
    if( ch != '+' && ch != '-' && ch != '*' && ch != '/' ){ 
	    value = ch - '0';	// �Է��� �ǿ������̸�
	    push(&s, value);
	}
	else{	//�������̸� �ǿ����ڸ� ���ÿ��� ����
	    op2 = pop(&s);
	    op1 = pop(&s);
	    switch(ch){ //������ �����ϰ� ���ÿ� ���� 
		case '+': push(&s,op1+op2); break;
		case '-': push(&s,op1-op2); break;
		case '*': push(&s,op1*op2); break;
		case '/': push(&s,op1/op2); break;
	    }
	}
}
return pop(&s);
}
// 
void main()
{	
	int result;
	printf("����ǥ����� 82/3-32*+\n");
	result = eval("82/3-32*+");
	printf("������� %d\n", result);
}