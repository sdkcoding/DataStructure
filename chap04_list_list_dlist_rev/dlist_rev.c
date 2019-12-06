#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct node { 
	char data[4]; 		
	struct node *link;   	
} node_str; 

node_str *ptr=NULL; 		

//
// 연결 리스트의 내용을 출력한다,
//
void display_list()
{
	node_str *p;

	p = ptr;
	printf(" ptr ", p->data);
	while(p != NULL){
		printf(" ----> %s ", p->data);
		p = p->link;
	}
	printf(" ----> NULL ");
}

void list_rev()
{
	node_str *p;
	node_str *curr;
	node_str *next;

	p = ptr;
	curr = NULL;
	while(p != NULL){
		next = p->link;
		p->link = curr;
		curr = p;
		p = next;
	}
	ptr = curr;
}

//
//
//
main()
{
	node_str *p1, *p2;

	// 첫번째 노드 생성, 연결
	p1 = (node_str *)malloc(sizeof(node_str)); 

	strcpy(p1->data, "bat"); 
	p1->link = NULL; 
	ptr = p1;

	// 두번째 노드 생성, 첫번쨰 노드의 뒤에 연결
	p2 = (node_str *)malloc(sizeof(node_str)); 

	strcpy(p2->data, "sat"); 
	p2->link = NULL;  // 두 번째 노드의 링크는 NULL
	p1->link = p2;       // 첫 번째 노드의 링크가 두 번째를 가리킨다.

	list_rev();

	display_list();
}
