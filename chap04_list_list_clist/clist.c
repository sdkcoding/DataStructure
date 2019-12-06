#include <stdio.h>
#include <stdio.h>


typedef int element;
typedef struct ListNode { 
	element data;
	struct ListNode *link;   	
} ListNode; 

// ��带 �������� �����ϴ� ���α׷�
ListNode *create_node(element data, ListNode *link)
{
	ListNode *new_node;
	new_node = (ListNode *)malloc(sizeof(ListNode)); 
	if( new_node == NULL ) {
		fprintf(stderr, "�޸� �Ҵ� ����\n");
		exit(1);
	}
	new_node->data = data;
	new_node->link = link;
	return(new_node);
}

// phead: ����Ʈ�� ��� �������� ������
// p : ���� ���
// node : ���Ե� ��� 
void insert_first(ListNode **phead,	ListNode *node) 
{
	if( *phead == NULL ){
		*phead = node;
		node->link = node;
	}
	else {
		node->link = (*phead)->link;
		(*phead)->link = node;
	}
}
// phead: ����Ʈ�� ��� �������� ������
// p : ���� ���
// node : ���Ե� ��� 
void insert_last(ListNode **phead, ListNode *node) 
{
	if( *phead == NULL ){
		*phead = node;
		node->link = node;
	}
	else {
		node->link = (*phead)->link;
		(*phead)->link = node;
		*phead = node;
	}
}
void display(ListNode *head)
{
	ListNode *p;
	if( head == NULL ) return;

	p = head;
	do {
		printf("%d->", p->data);
		p = p->link;
    } while(p != head);
}
// ���� ���� ����Ʈ �׽�Ʈ ���α׷�
main()
{
	ListNode *list1=NULL;

	// list1 = 20->10->30
	insert_first(&list1, create_node(10, NULL));
	insert_first(&list1, create_node(20, NULL));
	insert_last(&list1,  create_node(30, NULL));
	display(list1);
}
