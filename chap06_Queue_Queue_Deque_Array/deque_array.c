/*
*	덱은 double-ended queue의 줄임말으로, 큐의 앞, 뒤 모두에서 삽입 및 삭제가 가능한 큐를 의미한다.
*	큐나 스택보다는 유연하고, 링크드리스트보다는 조금 덜 유연한 자료구조라고 생각하면 될 듯 하다.
*	(링크드리스트는 중간에서 삽입, 삭제가 가능하다)
*	덱은 원형 큐 (Cicle Queue)를 조금 확장하면 손쉽게 구현할 수 있다.
*	원형 큐에서 플러스로 전단(front)에서의 삽입과 후단(rear)에서의 삭제만 추가되면 덱(Deque)를 구현할 수 있기
*	때문에 먼저 원형큐가 어떤 식으로 구현이 되어 있는지를 알면 더 이해가 쉬울 것이다.
*	먼저 코드의 가독성 및 나중에 수정의 용이함을 위해 선언한 매크로 및 타입 재정의를 보자.
*/
#include <stdio.h>
#include <stdlib.h>
/*
*	boolean은 참(TRUE)과 거짓(FALSE)를 return하는 함수 및 변수들을 위해 정의하였고,
*	이를 가독성이 좋게 하기 위해, 추가적으로 TRUE와 FALSE를 정의하였다.
*	내가 원하지 않는 방향으로 코드가 흘러갔을때를 체크하기 위해, 원하지 않는 곳에서 함수가 종료될 시
*	return 값을 통일하기 위해 ERROR(-1)을 정의했고, 나중에 int 타입만이 아닌 다른 데이터 타입에
*	이 코드를 사용하고 싶을 때, 수정하기 쉽게 element로 타입을 정의 해놓았다.
*/
#define	TRUE	1
#define	FALSE	0
#define	ERROR	-1
#define MAX_DEQUE_SIZE	5

typedef	int	boolean;
typedef	int	element;

/*
*	다음은 Deque의 구조체이다.
*	Deque의 크기는 동적으로 할당하기 위해 구조체에 포인터 타입의 변수(배열의 주소값이 될)와
*	Duque의 전단(front), 후단(rear)을 구조체의 멤버로 선언했다.
*/
typedef struct __dequeueType
{
	element* data;
	int rear, front;
}Deque;
/*
*	덱을 처음 생성하는 함수이다.
*	덱을 처음 생성하므로, front == rear인 상태를 만들어주고, a=미리 정의해놓은 MAX_DEQUE_SIZE만큼의
*	크기를 동적할당해준다.   크기를 다르게 하고 싶다면 매크로로 선언해놓은 MAX_DEQUE_SIZE를 수정하거나
*	유저에게 변수를 입력받아서 변수로 동적할당을 해주면 될 것이다.
*/
void init_deque(Deque* q)
{
	q->data = (element*)malloc(sizeof(element) * MAX_DEQUE_SIZE);
	q->front = q->rear = 0;
}
/*
*	다음은 덱이 위의 그림처럼 공백상태인지를 검사해서 TRUE or FALSE를 리턴하는 함수이다.
*	위의 코드를 아래와 같이 한 줄로 줄일 수도 있겠지만, 코드의 가독성을 위해 위와 같이 구현했다.
*	boolean is_empty(Deque *q) {
*		return (q->front == q->rear);
*	}
*/
boolean is_empty(Deque* q)
{
	if (q->front == q->rear) return TRUE;
	else	return FALSE;
}
//	덱의 rear를 반환        
element get_rear(Deque* q) {
	if (is_empty(q)) {
		printf("공백큐\n");
		return ERROR;
	}
	return q->data[q->rear];
}
/*	
*	덱의 앞의 요소를 반환        
*	front에 +1을 하고 return하는 이유는 front는 항상 공백을 가르키고 있기 때문에, 실제 첫 요소는
*	front+1의 index에 위치하고 있기 때문이다.
*/
element get_front(Deque* q) {
	if (is_empty(q)) {
		printf("공백큐\n");
		return ERROR;
	}
	return q->data[(q->front + 1) % MAX_DEQUE_SIZE];
}
/*	
*	덱의 뒤에 요소를 추가        
*	front는 가만히 있고, rear가 움직이면서 데이터를 삽입한다.
*	지금의 삽입 과정은 원형큐에서의 데이터 삽입과 똑같다. 
*	여기서 주목해야 할 점이 있다.
*	실제 배열에서의 데이터 삽입의 진행방향이다.  
*	지금 rear 변수가 움직이는 방향이 -> 임을 기억해 둬야 한다.
*	0 -> 1 -> 2 .... DEQUE_MAX_SIZE-1까지 순차적으로 진행을 하다가 
*	index 초과시 0으로 돌아가게 해야 한다.
*	가장 간단한 방법으로는 다음과 같은 방법이 있다.
*	if(q->rear==DEQUE_MAX_SIZE-1){
*		 q->rear=0
*	}
*	하지만 매번 rear나 front 변수가 -> 방향으로 움직일 때마다 if문을 검사하기 보다는,
*	% 연산자 (나머지 연산자)를 사용하는 더 나은 방법이 있다.
*	(q->rear + 1) % (MAX_SIZE) 와 같이 q->rear 변수에 +1을 해준 뒤에 
*	MAX_SIZE로 나눠서 나머지를 확인한다면
*	q->rear + 1 < MAX_SIZE 라면 q->rear +1 그대로 유지가 될 것이고, 
*	q->rear +1 == MAX_SIZE 라면 MAX_SIZE % MAX_SIZE 이므로 0이 나오게 된다.
*	원형 큐에서는 이러한 알고리즘으로 rear 변수와 front 변수를 업데이트하는데, 덱에서도 이를 
*	똑같이 따와서 구현한다. 아래는 위의 아이디어를 구현한 코드이다.	
*/
void add_rear(Deque* q, element data) {
	if (is_full(q)) {
		printf("포화큐\n");
		return;
	}
	q->rear = (q->rear + 1) % MAX_DEQUE_SIZE;
	q->data[q->rear] = data;
}
/*
*	덱의 앞의 요소를 반환후 삭제        
*	이번에는 front가 움직이면서 데이터를 삭제했다.
*	여기서 front 변수의 움직임을 방향을 살펴보자.
*	방금 전의 add_rear와 진행방향이 동일함을 알 수 있다.
*	그러므로 add_rear에서의 rear 변수의 업데이트 방식과 동일한 알고리즘을 사용한다.​
*/
element delete_front(Deque* q) {
	if (is_empty(q)) {
		printf("공백큐\n");
		return ERROR;
	}
	element tmp = get_front(q);
	q->front = (q->front + 1) % MAX_DEQUE_SIZE;
	return tmp;
}
/*
*	덱의 뒤에 요소를 반환후 삭제
*	이는 원형큐(Circle Queue)에는 없는 동작이다. 
*	앞서 살펴봤던 동작과는 반대 방향으로 진행되는 것을 확인할 수 있다.
*	그러므로 rear 변수의 업데이트 방향이 반대로 되어야 할 것이다.
*	앞에서 q->rear = (q->rear + 1) % MAX_DEQUE_SIZE 와 같이 업데이트를 했으니 
*	단순하게 생각하면 q->rear = (q->rear - 1) % MAX_DEQUE_SIZE로 업데이트를 하면 되겠지? 
*	라고 생각을 할 것이다. 하지만, rear 변수가 0일 때, 위의 수식을 계산하면 -1이 나오게 되어, 
*	배열의 index 범위를 벗어나 버린다. (존재x) 이렇게, 계산시 마이너스가 되는 것을 
*	방지하기 위하여 rear 변수 업데이트 식을 다음과 같이 수정한다.
*	q->rear = (q->rear - 1 + MAX_DEQUE_SIZE) % MAX_DEQUE_SIZE
*	MAX_DEQUE_SIZE를 더해준 뒤에 MAX_DEQUE_SIZE로 나누어 나머지를 구함으로써 
*	배열 index가 마이너스가 되는 것을 방지하면서, 원하는 동작이 이루어지도록 구현하였다.  
*	덱에서는 양쪽 방향으로 삽입 및 삭제가 이루어지기 때문에, 구현할 시에 front, rear가 
*	어느 방향으로 업데이트 되는지를 잘 생각을 해주어야 한다. 
*	아래는 위의 아이디어를 바탕으로 구현한 코드이다.
*/
element delete_rear(Deque* q) {
	if (is_empty(q)) {
		printf("공백큐\n");
		return ERROR;
	}
	element tmp = get_rear(q);
	q->rear = (q->rear - 1 + MAX_DEQUE_SIZE) % MAX_DEQUE_SIZE;
	return tmp;
}
/*
*	덱의 앞에 요소를 추가 
*	front 변수는 역시 공백을 가르키기 때문에 한칸 씩 차이를 두고 데이터를 삽입하였다.
*	이번에도 실제 배열에서 데이터가 삽입되는 방향을 살펴보자.
*	방금 전의 후단에서의 데이터 삭제 방향과 똑같은 방향이므로, 
*	q->front = (q->front - 1 + MAX_DEQUE_SIZE) % MAX_DEQUE_SIZE
*	로 업데이트를 해주면 될 것이다.
*/
void add_front(Deque* q, element data) {
	if (is_full(q)) {
		printf("포화큐\n");
		return;
	}
	q->data[q->front] = data;
	q->front = (q->front - 1 + MAX_DEQUE_SIZE) % MAX_DEQUE_SIZE;
	return;
}
/*
*	덱이 포화인지 검사
*	앞에서 front == rear 일 때를 우리는 공백 상태로 보기로 했었다. 
*	한 칸을 비우지 않은 상태로 덱을 꽉 채운다면 rear == front인 상태가 되고
*	우리는 큐가 공백 상태인지, 포화 상태인지를 구별할 수 없을 것이다. 
*	물론 현재 큐에 저장된 요소의 개수를 나타내는 변수를 추가한다면 구별할 수 있겠지만, 
*	(이건 또 다른 방법) 여기서는 그러기보다 배열에서 한 칸을 비움으로써, 
*	공백 상태와 포화 상태를 구분하기로 한다.
*/
boolean is_full(Deque* q) {
	if (((q->rear + 1) % MAX_DEQUE_SIZE) == q->front) return TRUE;
	else return FALSE;
}
/*        
*	덱의 모든 요소 print
*	처음 i를 front+1 변수로 초기화해주고 (front는 비어있으므로..) 
*	rear를 만날 때 까지 while을 반복한다.
*/
void deque_print(Deque* q) {
	int i = (q->front + 1) % MAX_DEQUE_SIZE;
	printf("DEQUE(front=%d rear=%d) = ", q->front, q->rear);
	if (is_empty(q)) {
		printf("공백큐\n");
		return;
	}
	while (i != q->rear) {
		printf("%d | ", q->data[i]);
		i = (i + 1) % MAX_DEQUE_SIZE;
	}
	printf("%d\n", q->data[i]);
}

int main() {

	Deque q;

	init_deque(&q);
	printf("# ADD FRONT\n\n");
	for (int i = 0; i < 3; i++) {
		add_front(&q, i);
		deque_print(&q);
	}
	printf("\n# DELETE REAR\n\n");
	for (int i = 0; i < 3; i++) {
		delete_rear(&q);
		deque_print(&q);
	}
	printf("\n# ADD REAR\n\n");
	for (int i = 0; i < 3; i++) {
		add_rear(&q, i);
		deque_print(&q);
	}
	printf("\n# DELETE FRONT\n\n");
	for (int i = 0; i < 3; i++) {
		delete_front(&q);
		deque_print(&q);
	}
	free(q.data);
	return 0;
}

