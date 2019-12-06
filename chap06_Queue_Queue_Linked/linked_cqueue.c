/*
 *	LinkedQueue.c
 */
#include <stdio.h>
#include <malloc.h>�� 

typedef int QueueObject;
typedef struct QueueRec { 
	QueueObject item; 
	struct QueueRec *link; 
} QueueNode;
QueueNode *front, *rear;

void initialize()
{
	front = rear = 0;
}

int isEmpty()
{
	return (front==NULL);
}

int isFull()
{
 	QueueNode *temp = (QueueNode *)malloc(sizeof(QueueNode)); 
	if(temp == NULL ){
		free(temp);
		return 1;
	}
	else return 0;
}

void addq(QueueObject item)
{ 
 	QueueNode *temp = (QueueNode *)malloc(sizeof(QueueNode)); 
	if(temp == NULL ){
		printf("�޸𸮸� �Ҵ��� �� �����ϴ�.\n");
	}
	else {
		temp->item = item; 
		temp->link = NULL; 
		if( front ) rear->link = temp;	// ť�� ������ 
		else front = temp;		// ť�� �����϶� 
		rear = temp; 
	}
}

QueueObject deleteq() 
{ 
 	QueueNode *temp = front;
 	QueueObject item; 
	if( isEmpty() ){
		printf("ť�� ��� �����ϴ�.\n");
	}
	else {
		item = temp->item; 
		front = front->link; 
		free(temp); 
		return item; 
	}
} 

void main()
{
	addq(1);
	addq(2);
	addq(3);
	printf("deleteq()=%d\n",deleteq());
	printf("deleteq()=%d\n",deleteq());
	printf("deleteq()=%d\n",deleteq());
}