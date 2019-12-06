#include <cstdio>
#include <stdlib.h>
#include <stack>
#include <stdio.h>
using namespace std;
#define M         3 //����
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
class Parent//���� �ϴ� ��츦 ���
{
public:
	int n;
	int numKey[M];
	class Node* child[M + 1];
};
class Split//��й� �ϴ� ��츦 ���
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
Node* root = NULL;//��Ʈ null�� �ʱ�ȭ
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
	bool is_found = false;//������ ������ ã�Ҵ��� Ȯ���ϴ� ����
	bool is_finished = false;//���� �ߴ��� Ȯ���ϴ� ����
	Node* currentNode, * p, * newnode;//��� ���� �� ���� ������
	Btree node;
	Parent tempNode;//�����÷ο� �ذ� �ϱ� ���� ����
	stack<Btree> s;
	if (root == NULL)//ù ������ ��� �����ϰ� �ʱ�ȭ
	{
		root = (Node*)malloc(sizeof(Node));
		root->n = 1;
		root->numKey[0] = data;
		for (i = 0; i <= 1; i++)  root->child[i] = NULL;
		return;
	}
	//���ÿ� �ֱ� ���̹Ƿ� ��Ʈ ��带 �����忡 �����Ѵ�.
	currentNode = root;
	is_found = false;//�ٽ� �ʱ�ȭ
	do
	{
		p = NULL;
		N = currentNode->n;
		for (i = 0; i < N; i++)
		{
			//������ Ű ���� �̹� �ִ°��
			if (currentNode->numKey[i] == data)
			{
				is_found = 1;
				break;
			}
			else if (currentNode->numKey[i] > data)//�ڽ� ��� ã��
			{
				p = currentNode->child[i];
				break;
			}
		}
		if (currentNode->numKey[i - 1] < data && p == NULL) p = currentNode->child[i]; //������ �ڽ� ��� �� ���
		if (p != NULL)//�� ���� ã�� ���
		{
			node.p = currentNode;
			s.push(node);//���ÿ� �������ش�.
			currentNode = p;
		}
	} while (is_found == 0 && p != NULL);//������ ��ġ�� ã�������� �ݺ��� ����
	if (is_found == 1) return;
	p = NULL;//p �ٽ� �ʱ�ȭ
	is_finished = 0;//���� �ٽ� �ʱ�ȭ
	//������ ��尡 �����÷ο� �߻��ϴ��� �ȹ߻��ϴ����� ���� ��찡 ����.
	do
	{
		if (currentNode->n < M - 1)//�����÷ο� x
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
			//����
			currentNode->numKey[i] = data;
			currentNode->child[i + 1] = p;
			(currentNode->n)++;
			return;  //������ �������Ƿ� �Լ� ����
		}
		else//�����÷ο� o
		{
			tempNode.n = currentNode->n + 1;
			tempNode.child[0] = currentNode->child[0];//�����÷ο� �߻� ��� ����
			for (i = 0; i < currentNode->n; i++)//����� Ű�� �� ��ŭ ����
			{
				if (currentNode->numKey[i] > data)
				{
					tempNode.numKey[i] = data;
					tempNode.child[i + 1] = p;//������
					break;
				}
				else
				{
					tempNode.numKey[i] = currentNode->numKey[i];
					tempNode.child[i + 1] = currentNode->child[i + 1];//������
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
			else//������ ������ Ű���� �����Ѵ�.
			{
				tempNode.numKey[i] = data;
				tempNode.child[i + 1] = p;
			}
			//��� ���� ������ -> ���� ����
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
			//������ ���� ����� ������ newnode�� ������.
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
			else//stack empty() -> Ʈ���� ������ �Ѵܰ� ����
			{
				//newnode�� ���ʿ� root �����ʿ� p�� ����
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
	bool is_found = false; //������ Ű���� ã�Ҵ��� Ȯ�� �ϴ� ����
	bool is_finished = false;//�����ߴ��� Ȯ���ϴ� ����
	Node* currentNode, * p, * temp;//Ű ��й� �� ��� �պ� �� ���� ����
	Btree node;
	Split splitNode;//��й迡 ���ȴ�
	stack<Btree> s;
	if (root == NULL)//����ִ� Ʈ���� ��� ���� �Ұ�
	{
		printf("�� �̻� ���� �� �� �����ϴ�...\n");
		return;
	}
	currentNode = root;  //���� ��带 ��Ʈ ���� �ʱ�ȭ�Ѵ�.
	is_found = false;
	//������ ��带 ã�� �ݺ���
	do
	{
		p = NULL;
		N = currentNode->n; //���� ����� Ű ����
		for (i = 0; i < N; i++)
		{
			if (currentNode->numKey[i] == data)//������ Ű �� �߰�
			{
				k = i;//Ű�� ��ġ �� ����
				is_found = 1;
				break;
			}
			else if (currentNode->numKey[i] > data)//p�� �ڽĳ�� ����
			{
				p = currentNode->child[i];
				k = i;//��ġ �� ����
				break;
			}
		}
		if (i - 1 >= 0 && is_found == 0)//���� ��ġ ��ã���� ��
		{
			if (currentNode->numKey[i - 1] < data)
			{
				p = currentNode->child[i];//���� ������ �ڽĳ�� ����
				k = i - 1;
			}
		}
		//�θ� ��� currentNode
		//�ڽ� p
		if (p != NULL)//�ڽĳ�带 ������ ���
		{
			node.p = currentNode;
			node.n = k;
			s.push(node);
			currentNode = p;
		}
	} while (is_found == 0 && p != NULL);
	if (is_found == 0)  return;  //������ ���������Ƿ� �Լ� ����
	if (currentNode->child[k + 1] != NULL)//������ ����� �����ʿ� �ڽĳ�尡 ���� ��
	{
		temp = currentNode;//��� ����
		node.p = currentNode;
		node.n = k;
		s.push(node);//���ÿ� �����Ѵ�.
		currentNode = currentNode->child[k + 1];
		//������ Ű�� ����Ű�� ã�´�.
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
	//������ Ű ���� ���� ��忡�� Ű�� �����ϴ� �ݺ���
	do
	{
		//����
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
		(currentNode->n)--;//Ű ���� ����
		if (currentNode->n > 0)  return;
		else if (s.empty())//level�� ������ ���
		{
			temp = root;
			root = root->child[0];
			if (temp) free(temp);
			return;
		}
		else if (s.top().p->child[s.top().n]->n > 1 || s.top().p->child[s.top().n + 1]->n > 1)//����÷ο� �߻� -> ��й�
		{
			if (s.top().p->child[s.top().n]->n > 1)
			{
				temp = s.top().p->child[s.top().n];//���� ���� ��� ����
				j = 0;
				//��� ����
				for (i = 0; i < temp->n; i++)
				{
					splitNode.child[j] = temp->child[i];
					splitNode.numKey[j] = temp->numKey[i];
					j++;
				}
				//������ �ڽĵ� ����
				splitNode.child[j] = temp->child[i];
				splitNode.numKey[j] = s.top().p->numKey[s.top().n];
				j++;
				//�θ��� ������ ��忡 ���� Ű �ִ°�� �������ش�.
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
				temp->n = mid;//���� �ڽ��� Ű ���� ����
				s.top().p->numKey[s.top().n] = splitNode.numKey[mid];
				//�߰����� �������� ������ Ű ���� currentNode�� ������
				for (i = mid + 1; i < splitNode.n; i++)
				{
					currentNode->child[i - mid - 1] = splitNode.child[i];
					currentNode->numKey[i - mid - 1] = splitNode.numKey[i];
				}
				currentNode->child[mid] = splitNode.child[i];
				currentNode->n = splitNode.n - mid - 1;
			}
			else//������ ������ Ű ������ 1�� �̻��̸�
			{
				temp = s.top().p->child[s.top().n + 1];//������ ���� ��� ����
				j = 0;
				//�ڽĳ�� ����
				for (i = 0; i < currentNode->n; i++)
				{
					splitNode.child[j] = currentNode->child[i];
					splitNode.numKey[j] = currentNode->numKey[i];
					j++;
				}
				//������ �ڽĳ�� ����
				splitNode.child[j] = currentNode->child[i];
				splitNode.numKey[j] = s.top().p->numKey[s.top().n];
				j++;
				//�θ��� ���� ��忡 ���� Ű�� �ִٸ� ����
				for (i = 0; i < temp->n; i++) {
					splitNode.child[j] = temp->child[i];
					splitNode.numKey[j] = temp->numKey[i];
					j++;
				}
				splitNode.child[j] = temp->child[i];
				splitNode.n = j;
				mid = j / 2;
				//�߰��� ���� ������ currentNode�� ������.
				for (i = 0; i < mid; i++)
				{
					currentNode->child[i] = splitNode.child[i];
					currentNode->numKey[i] = splitNode.numKey[i];
				}
				currentNode->child[i] = splitNode.child[i];
				currentNode->n = mid;
				s.top().p->numKey[s.top().n] = splitNode.numKey[mid]; //�θ� ��忡 �߰��� �ø�
				//�߰��� ���� ������ temp���� ������
				for (i = mid + 1; i < splitNode.n; i++) {
					temp->child[i - mid - 1] = splitNode.child[i];
					temp->numKey[i - mid - 1] = splitNode.numKey[i];
				}
				temp->child[i - mid - 1] = splitNode.child[i];
				temp->n = splitNode.n - mid - 1;
			}
			return;
		}
		else//��� �պ��ϴ� ���
		{
			if (s.top().p->child[s.top().n]->n > 0)//�θ��� ���� �ڽ��� 0�̻�
			{
				temp = s.top().p->child[s.top().n];//temp�� ���� �ڽ� ����
				temp->numKey[temp->n] = s.top().p->numKey[s.top().n];
				(temp->n)++;
				j = temp->n;
				//������ �ڽĿ� Ű�� ������ 0�̻��̸� ���� �ڽĿ� �ű��.
				for (i = 0; i < currentNode->n; i++)
				{
					temp->child[j + i] = currentNode->child[i];
					temp->numKey[j + i] = currentNode->numKey[i];
				}
				//������ �ڽ��� ���� ������ �ڽĵ� �θ��� �������� �ű��.
				temp->child[j + i] = currentNode->child[i];
				temp->n = temp->n + currentNode->n;//Ű�� ���� ��ģ��.
				if (currentNode) free(currentNode);//��� ����
				data = s.top().p->numKey[s.top().n];
				node = s.top();
				s.pop();
				currentNode = node.p;//�θ���
			}
			else
			{
				temp = s.top().p->child[s.top().n + 1];//temp�� �θ� ������ �ڽ� ����
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
	printf("m �� %d �� ��,\n", M);
	printf("����\n");
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
	printf("\n����\n");
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