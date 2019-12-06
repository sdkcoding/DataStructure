#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#define MAX_SIZE	101

typedef struct tree_node {
	int data;
	struct tree_node *left_child, *right_child;
} tnode_str;

typedef tnode_str element;

typedef struct {
	element queue[MAX_SIZE];
	int front, rear;
}QueueType;

typedef struct {
	element stack[MAX_SIZE];
	int top;
}StackType;

element * root;

void init(QueueType * q)
{
	q->front = q->rear = 0;
}

int is_empty(QueueType * q)
{
	return (q->front == q->rear);
}

int is_full(QueueType * q)
{
	return ((q->rear + 1) % MAX_SIZE == q->front);
}

void enqueue(QueueType * q, element * item)
{
	if (is_full(q)) {
		printf("Error1!!");  exit(1);
	}
	q->rear = (q->rear + 1) % MAX_SIZE;
	q->queue[q->rear] = *item;
}

element* dequeue(QueueType * q)
{
	if (is_empty(q)) {
		printf("Error2!!"); exit(1);
	}
	q->front = (q->front + 1) % MAX_SIZE;
	return &(q->queue[q->front]);
}
void push(element * node, StackType * stack) {
	if (stack->top == MAX_SIZE - 1) return;
	else stack->stack[++(stack->top)] = *node;
}
element* pop(StackType * stack) {
	if (stack->top == -1) return 0;
	else {
		return &(stack->stack[(stack->top)--]);
	}
}
/*트리 중위 순회 재귀 구현*/
void inorder( element *ptr ){
    if ( ptr ){
	 inorder( ptr->left_child );       // 좌측 서브 트리 검사
	 printf("%d ", ptr->data );    	// 노드 방문
	 inorder( ptr->right_child );      // 우측 서브 트리 검사
    }
}
/*트리 전위 순회 재귀 구현(dfs)*/
void preorder( element *ptr ){
    if ( ptr ){
        printf("%d ", ptr->data );        // 노드 방문
	  preorder( ptr->left_child );      // 좌측 서브 트리 검사
	  preorder( ptr->right_child );     // 우측 서브 트리 검사
    }
}
/*트리 후위 순회 재귀 구현*/
void postorder( element *ptr ){
    if ( ptr ){
	 postorder( ptr->left_child );       // 좌측 서브 트리 검사
	 postorder( ptr->right_child );     // 우측 서브 트리 검사
	 printf("%d ", ptr->data );     	   // 노드 방문
    }
}

/*트리 레벨 순회 구현(bfs)*/
void level_order( element * ptr) {
	QueueType q;
	init(&q);
	if (!ptr) return;
	enqueue(&q, ptr);
	while (!is_empty(&q)) {
		ptr = dequeue(&q);
		printf("%d ", ptr->data);
		if (ptr->left_child)	enqueue(&q, ptr->left_child);
		if (ptr->right_child)	enqueue(&q, ptr->right_child);
	}
}

/*트리 중위 순회 반복적 구현*/
void iterInorder(element *node)
{
	StackType stack;
	stack.top = -1;
	for (;;) {
		for (; node ; node = node->left_child)
			push(node, &stack);
		node = pop(&stack);
		if (!node)	break;
		printf("%d ", node->data);
		node = node->right_child;
	}
}
/*트리 전위 순회 반복적 구현 중*/
void iterPreorder(element * node)
{
	StackType stack;
	stack.top = -1;
	while (1) {
		while(node){
			push(node, &stack);
			printf("%d ", node->data);
			if (!node->left_child) node = node->left_child;
			else node = node->right_child;
		}
		node = pop(&stack);
		if (!node) break;
	}
}
//
//   		  n1
//		     /  ＼
//		   n2    n3
//		  / ＼  /  ＼
//       n4 n5 n6  n7
int main(void)
{
	element *n1, *n2, *n3, *n4, *n5, *n6, *n7;

	n1 = (element *)malloc(sizeof(element));
	n2 = (element *)malloc(sizeof(element));
	n3 = (element *)malloc(sizeof(element));
	n4 = (element *)malloc(sizeof(element));
	n5 = (element *)malloc(sizeof(element));
	n6 = (element *)malloc(sizeof(element));
	n7 = (element *)malloc(sizeof(element));

	// 첫 번째 노드를 설정한다.
	n1->data = 10;
	n1->left_child = n2;
	n1->right_child = n3;
	
	// 두 번째 노드를 설정한다.
	n2->data = 20;
	n2->left_child = n4;
	n2->right_child = n5;

	// 세 번째 노드를 설정한다.
	n3->data = 30;
	n3->left_child = n6;
	n3->right_child = n7;

	// 네 번째 노드를 설정한다.
	n4->data = 40;
	n4->left_child = NULL;
	n4->right_child = NULL;

	//다섯 번째 노드를 설정한다.
	n5->data = 50;
	n5->left_child = NULL;
	n5->right_child = NULL;

	//여섯 번째 노드를 설정한다.
	n6->data = 60;
	n6->left_child = NULL;
	n6->right_child = NULL;

	//일곱 번째 노드를 설정한다.
	n7->data = 70;
	n7->left_child = NULL;
	n7->right_child = NULL;

	// 루트 노드를 n1으로 한다.
	root = n1;
	printf("\nLevelTraversal\n");
	level_order(root);
	printf("\niterinorder\n");
	iterInorder(root);
	printf("\ninorder\n");
	inorder(root);
	printf("\npreorder\n");
	preorder(root);
	printf("\npostorder\n");
	postorder(root);
	
	fputs("\n", stdout);
	return 0;
}

