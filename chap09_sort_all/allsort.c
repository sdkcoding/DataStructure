#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100
#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )
#define	INSERT_SORT	1
int list[MAX_SIZE];
int n;

#if INSERT_SORT
int ascend(int x, int y)
{
	if (x < y) return 1;
	else return 0;
}
int descend(int x, int y)
{
	if (x > y) return 1;
	else return 0;
}
void insertion_sort(int list[], int n, int (*f)())
{
	int i, j;
	int key;
	for(i=1; i<n; i++){
		int k;
		// 정렬된 리스트 출력
		printf("(");
		for(k=0;k<i;k++)
			printf("%d ", list[k]);
		printf(")	");

		// 정렬해야할 리스트 출력
		printf("(");
		for(k=i;k<n;k++)
			printf("%d ", list[k]);
		printf(")\n");
		key = list[i];
		for(j=i-1; j>=0 && f(list[j],key);j--)
			list[j+1]=list[j];
		list[j+1]=key;
	}
}
void main()
{
	int i;
	n = MAX_SIZE;
	for (i = 0; i < n; i++)      	/* 난수 생성 및 출력 */
		list[i] = rand() % n;/*난수 발생 범위 0~MAX_SIZE*/

	insertion_sort(list, n, ascend); /* 삽입정렬 호출 */
	for (i = 0; i < n; i++)
		printf("%d ", list[i]);
	printf("\n");
	insertion_sort(list, n, descend); /* 삽입정렬 호출 */
	for (i = 0; i < n; i++)
		printf("%d ", list[i]);
}
#endif
#if 0
void selection_sort(int list[], int n)
{  
	int i, j, least, temp;
	for(i=0; i<n-1; i++) { 
	   least = i;
       for(j=i+1; j<n; j++) 	// 최소값 탐색
		  if(list[j]<list[least]) least = j;
       SWAP(list[i], list[least], temp); 
	}
}
#endif
#if 0
void bubble_sort(int list[], int n)
{  
   int i, j, temp;
   for(i=n-1; i>0; i--){
	for(j=0; j<i; j++)
		/* 앞뒤의 레코드를 비교한 후 교체 */
	      if(list[j]>list[j+1])   
     		    SWAP(list[j], list[j+1], temp);
   }
}
#endif
#if 0
void inc_insertion_sort(int list[], int first, int last, int gap)
{
	int i, j, key;
	for(i=first+gap; i<=last; i=i+gap){
		key = list[i];
		for(j=i-gap; j>=first && key<list[j];j=j-gap)
			list[j+gap]=list[j];
		list[j+gap]=key;
	}
}

void shell_sort( int list[], int n )   // n = size
{
	int i, gap;
	for( gap=n/2; gap>0; gap = gap/2 ) {
		if( (gap%2) == 0 ) gap++;
		for(i=0;i<gap;i++)		// 부분 리스트의 개수는 gap
			inc_insertion_sort(list, i, n-1, gap);
	}
}
#endif
#if 0

int heap[MAX_SIZE+1];
//
void adjust(int heap[], int root, int n)
{  
   int child, temp;
   temp = heap[root];				// 루트 값 저장
   child = 2*root;         		// 왼쪽 자식 노드 
   while(child <= n){				// 마지막 노드까지 반복
      if(child<n && heap[child]<heap[child+1])//더 작은 자식노드
         child++;
      if(temp>heap[child])    // 부모 노드와 자식 노드 비교 
	      break;
      else						// 자식 노드 값을 부모 노드로 복사 
	      heap[child/2] = heap[child]; 
      child = child*2;		   // 한 레벨 아래로 이동 
   }
   heap[child/2] = temp;      // temp가 child보다 작은 위치 
}
//
void heap_sort(int list[], int n)
{  
   int i, temp;
   
   for(i=0;i<n; i++)
	   heap[i+1]=list[i];

   for(i=n/2; i>0; i--)		// 주어진 리스트를 최대 히프로 변환
      adjust(heap, i, n);
   for(i=n-1; i>0; i--){	// 루트 노드와 마지막 노드 교환 
   		SWAP(heap[1], heap[i+1], temp);
		adjust(heap, 1, i);  // 축소된 리스트를 루트 노드부터 재조정 
	}

     for(i=0;i<n; i++)
	   list[i]=heap[i+1];
}
#endif
#if 0
#define MAX_QUEUE_SIZE 100
typedef int element;
typedef struct {
	element  queue[MAX_QUEUE_SIZE]; 
	int  front, rear;
} QueueType; 

void error(char *message)
{
	fprintf(stderr,"%s\n",message);
	exit(1);
}
// 초기화 함수
void init(QueueType *q)
{
	q->front = q->rear = 0;
}
// 공백 상태 검출 함수
int is_empty(QueueType *q)
{
	return (q->front == q->rear);
}
// 포화 상태 검출 함수
int is_full(QueueType *q)
{
	return ((q->rear+1)%MAX_QUEUE_SIZE == q->front);
}
// 삽입 함수
void enqueue(QueueType *q, element item)
{ 
  	if( is_full(q) ) 
		error("큐가 포화상태입니다");
	q->rear = (q->rear+1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
}
// 삭제 함수
element dequeue(QueueType *q) 
{ 
   	if( is_empty(q) )
		error("큐가 공백상태입니다");
	q->front = (q->front+1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];
} 
// 삭제 함수
element peek(QueueType *q) 
{ 
   	if( is_empty(q) )
		error("큐가 공백상태입니다");
	return q->queue[(q->front+1) % MAX_QUEUE_SIZE];
} 

#define BUCKETS 10
#define DIGITS  4
void radix_sort(int list[], int n)
{
	int i, b, d, factor=1;
	QueueType queues[BUCKETS];

	for(b=0;b<BUCKETS;b++) init(&queues[b]);  // 큐들의 초기화

	for(d=0; d<DIGITS; d++){
		for(i=0;i<n;i++)			// 데이터들을 자리수에 따라 큐에 삽입
			enqueue( &queues[(list[i]/factor)%10], list[i]);

		for(b=i=0;b<BUCKETS;b++)  // 버킷에서 꺼내어 list로 합친다.
			while( !is_empty(&queues[b]) )
				list[i++] = dequeue(&queues[b]);
		factor *= 10;					// 그 다음 자리수로 간다.
	}
}
#endif

