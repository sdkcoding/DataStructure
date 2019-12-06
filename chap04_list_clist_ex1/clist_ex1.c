#include <stdio.h>

typedef struct node { 
	char data[4]; 		
	struct node *link;   	
} node_str; 

// 첫번째 원형 연결리스트 정의
node_str an3={"a3",NULL};
node_str an2={"a2",&an3};
node_str an1={"a1",&an2};

// 첫번째 원형 연결리스트 헤드포인터
node_str *aptr=&an1; 

// 두번째 원형 연결리스트 정의
node_str bn3={"b3",NULL};
node_str bn2={"b2",&bn3};
node_str bn1={"b1",&bn2};

// 첫번째 원형 연결리스트 헤드포인터
node_str *bptr=&bn1; 

// 단순 연결리스트를 원형 연결리스트로 바꾼다.
init_lists()
{
	an3.link = &an1;
	bn3.link = &bn1;
}

//
// 원형 연결리스트의 내용을 출력한다,
//
void display_list(node_str *p)
{
	node_str *startp;
	startp = p;
	if( p == NULL ) return;
	printf(" 헤드포인터 ");
	do{
		printf(" ----> %s ", p->data);
		p = p->link;
	} while (p != startp);
	printf(" ----> 처음으로\n");
}

// 원형 리스트 2개를 합병한다.
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