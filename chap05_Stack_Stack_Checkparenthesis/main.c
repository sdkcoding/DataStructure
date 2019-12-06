#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define MAX_STACK_SIZE 100
typedef char element;
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
//
int check_matching(char *in) 
{ 
	StackType s;
	char ch, open_ch; 
	int i, n = strlen(in);  
	init(&s);
   
	for (i = 0; i < n; i++) { 
		  ch = in[i];
		  switch(ch){
			case '(':   case '[':    case '{':
			  push(&s, ch);
			  break;
			case ')':   case ']':    case '}':
			  if(is_empty(&s))  return FALSE;
			  else {
				open_ch = pop(&s);
				if ((open_ch == '(' && ch != ')') ||
					(open_ch == '[' && ch != ']') ||
					(open_ch == '{' && ch != '}')) {
					 return FALSE;
				}
				break;
			 }
		  }
	}
	if(!is_empty(&s)) return FALSE; 
	return TRUE;
}

int main()
{
	if( check_matching("{ A[(i+1)]=0; }") == TRUE )
		printf("��ȣ�˻缺��\n");
	else
		printf("��ȣ�˻����\n");
}
