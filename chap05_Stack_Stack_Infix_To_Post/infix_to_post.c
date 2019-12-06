#include <stdio.h>
#include <string.h>

//	arraystack3.c

#include <stdio.h>

#define MAX_STACK_SIZE 100
typedef int element;
typedef struct {
	element stack[MAX_STACK_SIZE];
	int top;
} StackType;

// 스택 초기화 함수
void init(StackType *s)
{
	s->top = -1;
}
// 공백 상태 검출 함수
int is_empty(StackType *s)
{
	return (s->top == -1);
}
// 포화 상태 검출 함수
int is_full(StackType *s)
{
	return (s->top == (MAX_STACK_SIZE-1));
}
// 삽입함수
void push(StackType *s, element item)
{ 
  	  if( is_full(s) ) { 
		fprintf(stderr,"스택 포화 에러\n");
		return; 		 
	  } 
	  else s->stack[++(s->top)] = item; 
}
// 삭제함수
element pop(StackType *s) 
{ 
   	if( is_empty(s) ) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1); 		
	}
	else return s->stack[(s->top)--]; 
} 
// 피크함수
element peek(StackType *s) 
{ 
   	if( is_empty(s) ) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1); 		
	}
	else return s->stack[s->top]; 
}
// 연산자의 우선순위를 반환한다.
int prec(char op)
{
	switch(op){
		case '(': case ')': return 0;
		case '+': case '-': return 1;
		case '*': case '/': return 2;
	}
	return -1;
}
#if 0
// 중위 표기 수식 -> 후위 표기 수식
void infix_to_postfix(char exp[])
{   
  int i=0;
  char ch, top_op;		
  int len=strlen(exp);
  StackType s;

  init(&s);					// 스택 초기화 
  for(i=0; i<len; i++){
	ch = exp[i];
	// 연산자이면
    if( ch == '+' || ch == '-' || ch == '*' || ch == '/' ){	  // 스택에 있는 연산자의 우선순위가 더 크거나 같으면 출력
      while(!is_empty(&s) && (prec(ch) <= prec(peek(&s))))
	    printf("%c", pop(&s));
	  push(&s, ch);
	}
	else if ( ch == '(' )	// 왼쪽 괄호
	  push(&s, ch);
	else if ( ch == ')' ){	// 오른쪽 괄호
	  top_op = pop(&s);
	  // 왼쪽 괄호를 만날때까지 출력
	  while( top_op != '(' ){ 
	    printf("%c", top_op);
	    top_op = pop(&s);
	  }
	}
	else					// 피연산자
	  printf("%c", ch);
  }
  while( !is_empty(&s) )	// 스택에 저장된 연산자들 출력
	printf("%c", pop(&s));
}
#endif
// 중위 표기 수식 -> 후위 표기 수식
void infix_to_postfix(char exp[])
{   
  int i=0;
  char ch, top_op;		
  int len=strlen(exp);
  StackType s;

  init(&s);					// 스택 초기화 
  for(i=0; i<len; i++){
	ch = exp[i];
	// 연산자이면
    switch(ch){
	case '+': case '-': case '*': case '/': // 연산자
	  // 스택에 있는 연산자의 우선순위가 더 크거나 같으면 출력
      while(!is_empty(&s) && (prec(ch) <= prec(peek(&s))))
	    printf("%c", pop(&s));
	  push(&s, ch);
	  break;
	case '(':	// 왼쪽 괄호
	  push(&s, ch);
	  break;
	case ')':	// 오른쪽 괄호
	  top_op = pop(&s);
	  // 왼쪽 괄호를 만날때까지 출력
	  while( top_op != '(' ){ 
	    printf("%c", top_op);
	    top_op = pop(&s);
	  }
	  break;
	default:		// 피연산자
	  printf("%c", ch);
	  break;
	}
  }
  while( !is_empty(&s) )	// 스택에 저장된 연산자들 출력
	printf("%c", pop(&s));
}
// 
main()
{
  infix_to_postfix("(2+3)*4+9");
}