#include <stdio.h>

#define MAX_ELEMENT 200
typedef struct {
	int key;
} element;
typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
} HeapType;

// �ʱ�ȭ �Լ�
init(HeapType *h)
{
	h->heap_size =0;
}
// ���� ���� ��� �Լ�
print_heap(HeapType *h)
{
	int i;
	int level=1;
	printf("\n===================");
	for(i=1;i<=h->heap_size;i++){
		if( i == level ) {
			printf("\n");
			level *= 2;
		}
		printf("\t%d", h->heap[i].key);
	}
	printf("\n===================");
}
// ���� �Լ�
void insert_max_heap(HeapType *h, element item) 
{ 
    int i; 
    i = ++(h->heap_size); 

    //  Ʈ���� �Ž��� �ö󰡸鼭 �θ� ���� ���ϴ� ����
    while((i != 1) && (item.key > h->heap[i/2].key)){ 
	   h->heap[i] = h->heap[i/2]; 
       i /= 2; 
    } 
    h->heap[i] = item;     // ���ο� ��带 ����
} 
// ���� �Լ�
element delete_max_heap(HeapType *h) 
{ 
    int parent, child; 
    element item, temp;

    item = h->heap[1];
    temp = h->heap[(h->heap_size)--];
    parent = 1;	
    child = 2;
    while( child <= h->heap_size ){
	  // ���� ����� �ڽĳ���� �� ���� �ڽĳ�带 ã�´�.
	  if( ( child < h->heap_size ) && 
	      (h->heap[child].key) < h->heap[child+1].key)
	      child++;
	  if( temp.key >= h->heap[child].key ) break;
	  // �Ѵܰ� �Ʒ��� �̵�
	  h->heap[parent] = h->heap[child];
	  parent = child;
	  child *= 2;
    }
    h->heap[parent] = temp;
    return item;
} 
// �켱 ���� ť�� ������ �̿��� ����
void heap_sort(element a[], int n)
{
	int i;
	HeapType h;

	init(&h);
	for(i=0;i<n;i++){
		insert_max_heap(&h, a[i]);
	}
	for(i=(n-1);i>=0;i--){
		a[i] = delete_max_heap(&h);
	}
}

element test[] = { {10},{9},{8},{2},{3} };

// ���Լ� 
void main()
{
	element e1={10}, e2={5}, e3={30};
	element e4, e5, e6;
	HeapType heap;	// ���� ����
	init(&heap);		// �ʱ�ȭ
	// ����
	insert_max_heap(&heap, e1);
	insert_max_heap(&heap, e2);
	insert_max_heap(&heap, e3);
//	print_heap(&heap);
	// ����
	e4 = delete_max_heap(&heap);
	printf("< %d > ", e4.key);
	e5 = delete_max_heap(&heap);
	printf("< %d > ", e5.key);
	e6 = delete_max_heap(&heap);
	printf("< %d > \n", e6.key);
	heap_sort(test,5);
}
