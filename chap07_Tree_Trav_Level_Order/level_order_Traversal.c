#include <stdio.h>
#include <malloc.h>

typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
} TreeNode;

typedef TreeNode* element;

typedef struct QueueNode {	// ť�� ����� Ÿ�� 
	element item;
	struct QueueNode* link;
} QueueNode;

typedef struct {		// ť ADT ����
	QueueNode* front, * rear;
} QueueType;

// ���� �Լ�
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
// �ʱ�ȭ �Լ�
void init(QueueType* q)
{
	q->front = q->rear = 0;
}
// ���� ���� ���� �Լ�
int is_empty(QueueType* q)
{
	return (q->front == NULL);
}
// ��ȭ ���� ���� �Լ�
int is_full(QueueType* q)
{
	return 0;
}
// ���� �Լ�
void enqueue(QueueType* q, element item)
{
	QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
	if (temp == NULL)
		error("�޸𸮸� �Ҵ��� �� �����ϴ�");
	else {
		temp->item = item; 		// ������ ����
		temp->link = NULL; 		// ��ũ �ʵ带 NULL
		if (is_empty(q)) { 		// ť�� �����̸�
			q->front = temp;
			q->rear = temp;
		}
		else { 		// ť�� ������ �ƴϸ�
			q->rear->link = temp;  // ������ �߿�
			q->rear = temp;
		}
	}
}
// ���� �Լ�
element dequeue(QueueType* q)
{
	QueueNode* temp = q->front;
	element item;
	if (is_empty(q))			// �������
		error("ť�� ��� �����ϴ�");
	else {
		item = temp->item; 		// �����͸� ������.
		q->front = q->front->link; // front�� ������带 ����Ű���� �Ѵ�.
		if (q->front == NULL) 	// ���� ����
			q->rear = NULL;
		free(temp); 			// �����޸� ����
		return item; 			// ������ ��ȯ
	}
}
// peek �Լ�
element peek(QueueType* q)
{
	element item;
	if (is_empty(q))
		error("ť�� ��� �����ϴ�");
	else {
		item = q->front->item;	// �����͸� ������.
		return item; 			// ������ ��ȯ
	}
}
// ���� ��ȸ 
void level_order(TreeNode* ptr)
{
	QueueType q;

	init(&q);
	if (!ptr) return;
	enqueue(&q, ptr);
	while (is_empty(&q)) {
		ptr = dequeue(&q);
		printf(" %d ", ptr->data);
		if (ptr->left)
			enqueue(&q, ptr->left);
		if (ptr->right)
			enqueue(&q, ptr->right);
	}
}
TreeNode n1 = { 1,  NULL, NULL };
TreeNode n2 = { 4,  NULL,  NULL };
TreeNode n3 = { '*',  &n1,  &n2 };
TreeNode n4 = { 16, NULL, NULL };
TreeNode n5 = { 25, NULL, NULL };
TreeNode n6 = { '+', &n4,  &n5 };
TreeNode n7 = { '+', &n3,  &n6 };
TreeNode* exp = &n7;

int main(void)
{
	level_order(exp);
}