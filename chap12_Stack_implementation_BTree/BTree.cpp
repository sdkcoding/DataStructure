#include <cstdio>
#include <stdlib.h>
#include <stack>
#include <stdio.h>
using namespace std;
#define M         3 //차수
#define MAX_STACK   1000
#define MAX_numKey     1000
#define MAX_child  1000
class Node
{
public:
	int n;
	int numKey[M - 1];
	class Node* child[M];
};
class Parent//분할 하는 경우를 대비
{
public:
	int n;
	int numKey[M];
	class Node* child[M + 1];
};
class Split//재분배 하는 경우를 대비
{
public:
	int n;
	int numKey[2 * (M - 1)];
	class Node* child[2 * (M - 1) + 1];
};
class Btree//B-Tree
{
public:
	int n;
	class Node* p;
};
Node* root = NULL;//루트 null로 초기화
void inorder(Node* root)
{
	int i, j;
	if (root != NULL)
	{
		for (i = 0; i < root->n; i++)
		{
			inorder(root->child[i]);
			printf("%d ", root->numKey[i]);
		}
		inorder(root->child[i]);
	}
}
void print_inorder()
{
	inorder(root);
	printf("\n");
}
void insertBT(int data)
{
	int i, j, N, mid;
	bool is_found = false;//삽입할 공간을 찾았는지 확인하는 변수
	bool is_finished = false;//삽입 했는지 확인하는 변수
	Node* currentNode, * p, * newnode;//노드 분할 시 사용될 변수들
	Btree node;
	Parent tempNode;//오버플로우 해결 하기 위한 변수
	stack<Btree> s;
	if (root == NULL)//첫 삽입인 경우 적절하게 초기화
	{
		root = (Node*)malloc(sizeof(Node));
		root->n = 1;
		root->numKey[0] = data;
		for (i = 0; i <= 1; i++)  root->child[i] = NULL;
		return;
	}
	//스택에 넣기 전이므로 루트 노드를 현재노드에 복사한다.
	currentNode = root;
	is_found = false;//다시 초기화
	do
	{
		p = NULL;
		N = currentNode->n;
		for (i = 0; i < N; i++)
		{
			//삽입할 키 값이 이미 있는경우
			if (currentNode->numKey[i] == data)
			{
				is_found = 1;
				break;
			}
			else if (currentNode->numKey[i] > data)//자식 노드 찾음
			{
				p = currentNode->child[i];
				break;
			}
		}
		if (currentNode->numKey[i - 1] < data && p == NULL) p = currentNode->child[i]; //마지막 자식 노드 인 경우
		if (p != NULL)//들어갈 곳을 찾은 경우
		{
			node.p = currentNode;
			s.push(node);//스택에 삽입해준다.
			currentNode = p;
		}
	} while (is_found == 0 && p != NULL);//삽입할 위치를 찾을때까지 반복문 수행
	if (is_found == 1) return;
	p = NULL;//p 다시 초기화
	is_finished = 0;//변수 다시 초기화
	//삽입할 노드가 오버플로우 발생하는지 안발생하는지에 따라서 경우가 나뉨.
	do
	{
		if (currentNode->n < M - 1)//오버플로우 x
		{
			for (i = 0; i < currentNode->n; i++)
			{
				if (currentNode->numKey[i] > data)  break;
			}
			for (j = currentNode->n; j > i; j--)
			{
				currentNode->numKey[j] = currentNode->numKey[j - 1];
				currentNode->child[j + 1] = currentNode->child[j];
			}
			//삽입
			currentNode->numKey[i] = data;
			currentNode->child[i + 1] = p;
			(currentNode->n)++;
			return;  //삽입이 끝났으므로 함수 종료
		}
		else//오버플로우 o
		{
			tempNode.n = currentNode->n + 1;
			tempNode.child[0] = currentNode->child[0];//오버플로우 발생 노드 복사
			for (i = 0; i < currentNode->n; i++)//노드의 키의 수 만큼 수행
			{
				if (currentNode->numKey[i] > data)
				{
					tempNode.numKey[i] = data;
					tempNode.child[i + 1] = p;//오른쪽
					break;
				}
				else
				{
					tempNode.numKey[i] = currentNode->numKey[i];
					tempNode.child[i + 1] = currentNode->child[i + 1];//오른쪽
				}
			}
			if (i < M - 1)
			{
				for (j = currentNode->n; j > i; j--)
				{
					tempNode.numKey[j] = currentNode->numKey[j - 1];
					tempNode.child[j + 1] = currentNode->child[j];
				}
			}
			else//나머지 공간에 키값을 삽입한다.
			{
				tempNode.numKey[i] = data;
				tempNode.child[i + 1] = p;
			}
			//노드 복사 끝났음 -> 분할 시작
			mid = tempNode.n / 2;
			data = tempNode.numKey[mid];
			currentNode->n = mid;
			currentNode->child[i] = tempNode.child[0];
			for (i = 0; i < mid; i++)
			{
				currentNode->numKey[i] = tempNode.numKey[i];
				currentNode->child[i + 1] = tempNode.child[i + 1];
			}
			newnode = (Node*)malloc(sizeof(Node));
			newnode->n = M - 1 - mid;
			newnode->child[0] = tempNode.child[mid + 1];
			j = 0;
			//오른쪽 분할 노드의 값들은 newnode로 보낸다.
			for (i = mid + 1; i < tempNode.n; i++)
			{
				newnode->numKey[j] = tempNode.numKey[i];
				newnode->child[++j] = tempNode.child[i + 1];
			}
			p = newnode;
			if (!s.empty())
			{
				node = s.top();
				s.pop();
				currentNode = node.p;
			}
			else//stack empty() -> 트리의 레벨이 한단계 증가
			{
				//newnode의 왼쪽에 root 오른쪽에 p를 연결
				newnode = (Node*)malloc(sizeof(Node));
				newnode->n = 1;
				newnode->child[0] = root;
				newnode->numKey[0] = data;
				newnode->child[1] = p;
				root = newnode;
				return;
			}
		}
	} while (1);
}
void deleteBT(int data)
{
	int i, j, k, N, mid;
	bool is_found = false; //삭제할 키값을 찾았는지 확인 하는 변수
	bool is_finished = false;//삭제했는지 확인하는 변수
	Node* currentNode, * p, * temp;//키 재분배 및 노드 합병 시 사용될 변수
	Btree node;
	Split splitNode;//재분배에 사용된다
	stack<Btree> s;
	if (root == NULL)//비어있는 트리인 경우 삭제 불가
	{
		printf("더 이상 삭제 할 수 없습니다...\n");
		return;
	}
	currentNode = root;  //현재 노드를 루트 노드로 초기화한다.
	is_found = false;
	//삭제할 노드를 찾는 반복문
	do
	{
		p = NULL;
		N = currentNode->n; //현재 노드의 키 개수
		for (i = 0; i < N; i++)
		{
			if (currentNode->numKey[i] == data)//삭제할 키 값 발견
			{
				k = i;//키의 위치 값 저장
				is_found = 1;
				break;
			}
			else if (currentNode->numKey[i] > data)//p에 자식노드 저장
			{
				p = currentNode->child[i];
				k = i;//위치 값 저장
				break;
			}
		}
		if (i - 1 >= 0 && is_found == 0)//아직 위치 못찾았을 때
		{
			if (currentNode->numKey[i - 1] < data)
			{
				p = currentNode->child[i];//가장 오른쪽 자식노드 저장
				k = i - 1;
			}
		}
		//부모 노드 currentNode
		//자식 p
		if (p != NULL)//자식노드를 저장한 경우
		{
			node.p = currentNode;
			node.n = k;
			s.push(node);
			currentNode = p;
		}
	} while (is_found == 0 && p != NULL);
	if (is_found == 0)  return;  //삭제에 성공했으므로 함수 종료
	if (currentNode->child[k + 1] != NULL)//삭제할 노드의 오른쪽에 자식노드가 있을 때
	{
		temp = currentNode;//노드 복사
		node.p = currentNode;
		node.n = k;
		s.push(node);//스택에 삽입한다.
		currentNode = currentNode->child[k + 1];
		//삭제할 키의 후행키를 찾는다.
		while (currentNode->child[0] != NULL)
		{
			node.p = currentNode;
			node.n = 0;
			s.push(node);
			currentNode = currentNode->child[0];
		}
		temp->numKey[k] = currentNode->numKey[0];
		data = currentNode->numKey[0];
	}
	is_finished = false;
	//삭제할 키 값을 가진 노드에서 키를 삭제하는 반복문
	do
	{
		//정렬
		j = 0;
		for (i = 0; i < currentNode->n; i++)
		{
			if (currentNode->numKey[i] != data)
			{
				currentNode->numKey[j] = currentNode->numKey[i];
				currentNode->child[j + 1] = currentNode->child[i + 1];
				j++;
			}
		}
		(currentNode->n)--;//키 개수 감소
		if (currentNode->n > 0)  return;
		else if (s.empty())//level이 감소한 경우
		{
			temp = root;
			root = root->child[0];
			if (temp) free(temp);
			return;
		}
		else if (s.top().p->child[s.top().n]->n > 1 || s.top().p->child[s.top().n + 1]->n > 1)//언더플로우 발생 -> 재분배
		{
			if (s.top().p->child[s.top().n]->n > 1)
			{
				temp = s.top().p->child[s.top().n];//왼쪽 형제 노드 저장
				j = 0;
				//노드 복사
				for (i = 0; i < temp->n; i++)
				{
					splitNode.child[j] = temp->child[i];
					splitNode.numKey[j] = temp->numKey[i];
					j++;
				}
				//마지막 자식도 복사
				splitNode.child[j] = temp->child[i];
				splitNode.numKey[j] = s.top().p->numKey[s.top().n];
				j++;
				//부모의 오른쪽 노드에 남은 키 있는경우 복사해준다.
				for (i = 0; i < currentNode->n; i++)
				{
					splitNode.child[j] = currentNode->child[i];
					splitNode.numKey[j] = currentNode->numKey[i];
				}
				splitNode.child[j] = currentNode->child[i];
				splitNode.n = j;
				mid = j / 2;
				for (i = 0; i < mid; i++)
				{
					temp->child[i] = splitNode.child[i];
					temp->numKey[i] = splitNode.numKey[i];
				}
				temp->child[i] = splitNode.child[i];
				temp->n = mid;//왼쪽 자식의 키 개수 변경
				s.top().p->numKey[s.top().n] = splitNode.numKey[mid];
				//중간값을 기준으로 오른쪽 키 값은 currentNode로 보낸다
				for (i = mid + 1; i < splitNode.n; i++)
				{
					currentNode->child[i - mid - 1] = splitNode.child[i];
					currentNode->numKey[i - mid - 1] = splitNode.numKey[i];
				}
				currentNode->child[mid] = splitNode.child[i];
				currentNode->n = splitNode.n - mid - 1;
			}
			else//오른쪽 형제의 키 개수가 1개 이상이면
			{
				temp = s.top().p->child[s.top().n + 1];//오른쪽 형제 노드 복사
				j = 0;
				//자식노드 복사
				for (i = 0; i < currentNode->n; i++)
				{
					splitNode.child[j] = currentNode->child[i];
					splitNode.numKey[j] = currentNode->numKey[i];
					j++;
				}
				//마지막 자식노드 복사
				splitNode.child[j] = currentNode->child[i];
				splitNode.numKey[j] = s.top().p->numKey[s.top().n];
				j++;
				//부모의 왼쪽 노드에 남은 키가 있다면 복사
				for (i = 0; i < temp->n; i++) {
					splitNode.child[j] = temp->child[i];
					splitNode.numKey[j] = temp->numKey[i];
					j++;
				}
				splitNode.child[j] = temp->child[i];
				splitNode.n = j;
				mid = j / 2;
				//중간값 기준 왼쪽은 currentNode로 보낸다.
				for (i = 0; i < mid; i++)
				{
					currentNode->child[i] = splitNode.child[i];
					currentNode->numKey[i] = splitNode.numKey[i];
				}
				currentNode->child[i] = splitNode.child[i];
				currentNode->n = mid;
				s.top().p->numKey[s.top().n] = splitNode.numKey[mid]; //부모 노드에 중간값 올림
				//중간값 기준 왼쪽은 temp노드로 보낸다
				for (i = mid + 1; i < splitNode.n; i++) {
					temp->child[i - mid - 1] = splitNode.child[i];
					temp->numKey[i - mid - 1] = splitNode.numKey[i];
				}
				temp->child[i - mid - 1] = splitNode.child[i];
				temp->n = splitNode.n - mid - 1;
			}
			return;
		}
		else//노드 합병하는 경우
		{
			if (s.top().p->child[s.top().n]->n > 0)//부모의 왼쪽 자식이 0이상
			{
				temp = s.top().p->child[s.top().n];//temp에 왼쪽 자식 저장
				temp->numKey[temp->n] = s.top().p->numKey[s.top().n];
				(temp->n)++;
				j = temp->n;
				//오른쪽 자식에 키의 개수가 0이상이면 왼쪽 자식에 옮긴다.
				for (i = 0; i < currentNode->n; i++)
				{
					temp->child[j + i] = currentNode->child[i];
					temp->numKey[j + i] = currentNode->numKey[i];
				}
				//오른쪽 자식의 가장 오른쪽 자식도 부모의 왼쪽으로 옮긴다.
				temp->child[j + i] = currentNode->child[i];
				temp->n = temp->n + currentNode->n;//키의 개수 합친다.
				if (currentNode) free(currentNode);//노드 삭제
				data = s.top().p->numKey[s.top().n];
				node = s.top();
				s.pop();
				currentNode = node.p;//부모노드
			}
			else
			{
				temp = s.top().p->child[s.top().n + 1];//temp에 부모 오른쪽 자식 저장
				currentNode->numKey[currentNode->n] = s.top().p->numKey[s.top().n];
				(currentNode->n)++;
				j = currentNode->n;
				for (i = 0; i < temp->n; i++)
				{
					currentNode->child[j + i] = temp->child[i];
					currentNode->numKey[j + i] = temp->numKey[i];
				}
				currentNode->child[j + i] = temp->child[i];
				currentNode->n = currentNode->n + temp->n;
				if (temp)  free(temp);
				data = s.top().p->numKey[s.top().n];
				node = s.top();
				s.pop();
				currentNode = node.p;
			}
		}
	} while (1);
}
int main()
{
	printf("m 이 %d 일 때,\n", M);
	printf("삽입\n");
	int insert_arr[4][10] = { {30,20,62,110,140,15,65,136,150,120},
	  {40,132,19,128,138,100,16,145,70,42},
	  {69,43,26,60,130,50,18,7,36,58},
	  {22,41,59,57,54,33,75,124,122,123} };
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			insertBT(insert_arr[i][j]);
			print_inorder();
		}
	}
	printf("\n삭제\n");
	int delete_arr[4][10] = { {40,132,19,128,138,100,16,145,70,42},
	 {22,41,62,110,140,15,65,124,122,123},
	 {30,20,59,57,54,33,75,136,150,120},
	 {69,43,26,60,130,50,18,7,36,58} };
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			deleteBT(delete_arr[i][j]);
			print_inorder();
		}
	}
	return 0;
}