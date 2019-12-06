#include <stdio.h>

typedef struct node { 
	char data[4]; 		
	struct node *link;   	
} node_str; 

// ù��° ���� ���Ḯ��Ʈ ����
node_str an3={"a3",NULL};
node_str an2={"a2",&an3};
node_str an1={"a1",&an2};

// ù��° ���� ���Ḯ��Ʈ ���������
node_str *aptr=&an1; 

// �ι�° ���� ���Ḯ��Ʈ ����
node_str bn3={"b3",NULL};
node_str bn2={"b2",&bn3};
node_str bn1={"b1",&bn2};

// ù��° ���� ���Ḯ��Ʈ ���������
node_str *bptr=&bn1; 

// �ܼ� ���Ḯ��Ʈ�� ���� ���Ḯ��Ʈ�� �ٲ۴�.
init_lists()
{
	an3.link = &an1;
	bn3.link = &bn1;
}

//
// ���� ���Ḯ��Ʈ�� ������ ����Ѵ�,
//
void display_list(node_str *p)
{
	node_str *startp;
	startp = p;
	if( p == NULL ) return;
	printf(" ��������� ");
	do{
		printf(" ----> %s ", p->data);
		p = p->link;
	} while (p != startp);
	printf(" ----> ó������\n");
}

// ���� ����Ʈ 2���� �պ��Ѵ�.
node_str *merge_clist(node_str *pa, node_str *pb)
{
	node_str *temp;
	temp = pa->link;
	pa->link = pb->link;
	pb->link = temp;
}

main()
{
	init_lists();
	display_list(aptr);
	merge_clist(aptr,bptr);
	display_list(aptr);
}