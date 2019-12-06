#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct node { 
	char data[4]; 		
	struct node *link;   	
} node_str; 

node_str *ptr=NULL; 		

//
// ���� ����Ʈ�� ������ ����Ѵ�,
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

	// ù��° ��� ����, ����
	p1 = (node_str *)malloc(sizeof(node_str)); 

	strcpy(p1->data, "bat"); 
	p1->link = NULL; 
	ptr = p1;

	// �ι�° ��� ����, ù���� ����� �ڿ� ����
	p2 = (node_str *)malloc(sizeof(node_str)); 

	strcpy(p2->data, "sat"); 
	p2->link = NULL;  // �� ��° ����� ��ũ�� NULL
	p1->link = p2;       // ù ��° ����� ��ũ�� �� ��°�� ����Ų��.

	list_rev();

	display_list();
}
