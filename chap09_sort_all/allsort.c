#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 11
#define NAME_SIZE 32

#if 0
typedef struct {
	int key;
	char name[NAME_SIZE];
} record;
record list[MAX_SIZE];
int n;

//
insertion_sort_record(record list[], int n)
{
	int i, j;
	record current_record;
	for(i=1; i<n; i++){
		current_record = list[i];
		for(j=i-1; j>=0 && list[j].key>current_record.key;j--)
			list[j+1]=list[j];
		list[j+1]=current_record;
	}
}
#else
int list[MAX_SIZE];
int n;
#endif

//
insertion_sort(int list[], int n, int (*f)())
{
	int i, j;
	int key;
	for(i=1; i<n; i++){
#if 0
		int k;
		// ���ĵ� ����Ʈ ���
		printf("(");
		for(k=0;k<i;k++)
			printf("%d ", list[k]);
		printf(")	");

		// �����ؾ��� ����Ʈ ���
		printf("(");
		for(k=i;k<n;k++)
			printf("%d ", list[k]);
		printf(")\n");
#endif
		key = list[i];
		for(j=i-1; j>=0 && f(list[j],key);j--)
			list[j+1]=list[j];
		list[j+1]=key;
	}
}

int ascend(int x, int y)
{
	if( x<y ) return 1;
	else return 0;
}
int descend(int x, int y)
{
	if( x>y ) return 1;
	else return 0;
}


#if 0
#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )
//
void selection_sort(int list[], int n)
{  
	int i, j, least, temp;
	for(i=0; i<n-1; i++) { 
	   least = i;
       for(j=i+1; j<n; j++) 	// �ּҰ� Ž��
		  if(list[j]<list[least]) least = j;
       SWAP(list[i], list[least], temp); 
	}
}

//
void bubble_sort(int list[], int n)
{  
   int i, j, temp;
   for(i=n-1; i>0; i--){
	for(j=0; j<i; j++)
		/* �յ��� ���ڵ带 ���� �� ��ü */
	      if(list[j]>list[j+1])   
     		    SWAP(list[j], list[j+1], temp);
   }
}

//
inc_insertion_sort(int list[], int first, int last, int gap)
{
	int i, j, key;
	for(i=first+gap; i<=last; i=i+gap){
		key = list[i];
		for(j=i-gap; j>=first && key<list[j];j=j-gap)
			list[j+gap]=list[j];
		list[j+gap]=key;
	}
}
//
void shell_sort( int list[], int n )   // n = size
{
	int i, gap;
	for( gap=n/2; gap>0; gap = gap/2 ) {
		if( (gap%2) == 0 ) gap++;
		for(i=0;i<gap;i++)		// �κ� ����Ʈ�� ������ gap
			inc_insertion_sort(list, i, n-1, gap);
	}
}

int sorted[MAX_SIZE];

/* i�� ���ĵ� ���ʸ���Ʈ�� ���� �ε���
   j�� ���ĵ� �����ʸ���Ʈ�� ���� �ε���
   k�� ���ĵ� ����Ʈ�� ���� �ε��� */
void merge(int list[], int left, int mid, int right)
{  
   int i, j, k, l;
   i=left;  j=mid+1;  k=left;

   /* ���� ���ĵ� list�� �պ� */
   while(i<=mid && j<=right){
     if(list[i]<=list[j])
	    sorted[k++] = list[i++];
	 else
	    sorted[k++] = list[j++];
   }
   if(i>mid)	/* ���� �ִ� ���ڵ��� �ϰ� ���� */
	  for(l=j; l<=right; l++)
  	     sorted[k++] = list[l];
   else	/* ���� �ִ� ���ڵ��� �ϰ� ���� */
	  for(l=i; l<=mid; l++)
 	     sorted[k++] = list[l];
   /* �迭 sorted[]�� ����Ʈ�� �迭 list[]�� �纹�� */
   for(l=left; l<=right; l++)
      list[l] = sorted[l];
}
//
void merge_sort(int list[], int left, int right)
{  
   int mid;
   if(left<right){
      mid = (left+right)/2;     /* ����Ʈ�� �յ� ���� */
      merge_sort(list, left, mid);    /* �κ� ����Ʈ ���� */
      merge_sort(list, mid+1, right); /* �κ� ����Ʈ ���� */
	  merge(list, left, mid, right);    /* �պ� */
   }
}

int heap[MAX_SIZE+1];
//
void adjust(int heap[], int root, int n)
{  
   int child, temp;
   temp = heap[root];				// ��Ʈ �� ����
   child = 2*root;         		// ���� �ڽ� ��� 
   while(child <= n){				// ������ ������ �ݺ�
      if(child<n && heap[child]<heap[child+1])//�� ���� �ڽĳ��
         child++;
      if(temp>heap[child])    // �θ� ���� �ڽ� ��� �� 
	      break;
      else						// �ڽ� ��� ���� �θ� ���� ���� 
	      heap[child/2] = heap[child]; 
      child = child*2;		   // �� ���� �Ʒ��� �̵� 
   }
   heap[child/2] = temp;      // temp�� child���� ���� ��ġ 
}
//
void heap_sort(int list[], int n)
{  
   int i, temp;
   
   for(i=0;i<n; i++)
	   heap[i+1]=list[i];

   for(i=n/2; i>0; i--)		// �־��� ����Ʈ�� �ִ� ������ ��ȯ
      adjust(heap, i, n);
   for(i=n-1; i>0; i--){	// ��Ʈ ���� ������ ��� ��ȯ 
   		SWAP(heap[1], heap[i+1], temp);
		adjust(heap, 1, i);  // ��ҵ� ����Ʈ�� ��Ʈ ������ ������ 
	}

     for(i=0;i<n; i++)
	   list[i]=heap[i+1];
}
#endif

#define MAX_QUEUE_SIZE 100
typedef int element;
typedef struct {
	element  queue[MAX_QUEUE_SIZE]; 
	int  front, rear;
} QueueType; 
//
void error(char *message)
{
	fprintf(stderr,"%s\n",message);
	exit(1);
}
// �ʱ�ȭ �Լ�
void init(QueueType *q)
{
	q->front = q->rear = 0;
}
// ���� ���� ���� �Լ�
int is_empty(QueueType *q)
{
	return (q->front == q->rear);
}
// ��ȭ ���� ���� �Լ�
int is_full(QueueType *q)
{
	return ((q->rear+1)%MAX_QUEUE_SIZE == q->front);
}
// ���� �Լ�
void enqueue(QueueType *q, element item)
{ 
  	if( is_full(q) ) 
		error("ť�� ��ȭ�����Դϴ�");
	q->rear = (q->rear+1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
}
// ���� �Լ�
element dequeue(QueueType *q) 
{ 
   	if( is_empty(q) )
		error("ť�� ��������Դϴ�");
	q->front = (q->front+1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];
} 
// ���� �Լ�
element peek(QueueType *q) 
{ 
   	if( is_empty(q) )
		error("ť�� ��������Դϴ�");
	return q->queue[(q->front+1) % MAX_QUEUE_SIZE];
} 
#if 0
#define BUCKETS 10
#define DIGITS  4
void radix_sort(int list[], int n)
{
	int i, b, d, factor=1;
	QueueType queues[BUCKETS];

	for(b=0;b<BUCKETS;b++) init(&queues[b]);  // ť���� �ʱ�ȭ

	for(d=0; d<DIGITS; d++){
		for(i=0;i<n;i++)			// �����͵��� �ڸ����� ���� ť�� ����
			enqueue( &queues[(list[i]/factor)%10], list[i]);

		for(b=i=0;b<BUCKETS;b++)  // ��Ŷ���� ������ list�� ��ģ��.
			while( !is_empty(&queues[b]) )
				list[i++] = dequeue(&queues[b]);
		factor *= 10;					// �� ���� �ڸ����� ����.
	}
}
#endif
//
void main()
{  
   int i;
   n = MAX_SIZE;
   for(i=0; i<n; i++)      	/* ���� ���� �� ��� */
   	  list[i] = rand()%n;/*���� �߻� ���� 0~MAX_SIZE*/
   
   insertion_sort(list, n, ascend); /* �������� ȣ�� */
   for(i=0; i<n; i++)
       printf("%d\n", list[i]);
   insertion_sort(list, n, descend); /* �������� ȣ�� */
   for(i=0; i<n; i++)
       printf("%d\n", list[i]);
}