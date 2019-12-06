#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable:4996) // This function or variable may be unsafe.

#define RIGHT_LEFTMOST	0
#define LEFT_RIGHTMOST	1
#define REMOVE_TYPE		RIGHT_LEFTMOST

typedef struct Node
{
	int data;
	struct Node* left;
	struct Node* right;
} Node;

Node* CreateNode(int data)
{
	// TODO:
	Node* newNode = (Node*)malloc(sizeof(Node));

	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}
Node* SearchNode(Node* tree, int data)
{
	// TODO:
	if (tree == NULL)
		return NULL;

	if (tree->data > data)
		return SearchNode(tree->left, data);
	else if (tree->data < data)
		return SearchNode(tree->right, data);
	else
		return tree;
}
void InsertNode(Node* tree, Node* newNode)
{
	// TODO:
	if (tree == NULL)
		return;

	if (tree->data > newNode->data)
	{
		if (tree->left == NULL)
			tree->left = newNode;
		else
			InsertNode(tree->left, newNode);
	}
	else if (tree->data < newNode->data)
	{
		if (tree->right == NULL)
			tree->right = newNode;
		else
			InsertNode(tree->right, newNode);
	}
}
Node* FindMaxNode(Node* tree)
{
	// TODO:
	if (tree == NULL)
		return NULL;

	if (tree->right == NULL)
		return tree;
	else
		return FindMaxNode(tree->right);
}
Node* FindMinNode(Node* tree)
{
	// TODO:
	if (tree == NULL)
		return NULL;

	if (tree->left == NULL)
		return tree;
	else
		return FindMinNode(tree->left);
}
Node* avl_remove(Node* tree, int data)
{
	// TODO:
	Node* tempNode;

	if (tree == NULL)
		return NULL;

	if (tree->data > data)
		tree->left = avl_remove(tree->left, data);
	else if (tree->data < data)
		tree->right = avl_remove(tree->right, data);
	else
	{
		if (tree->left != NULL && tree->right != NULL)
		{
#if (REMOVE_TYPE==RIGHT_LEFTMOST)
			tempNode = FindMinNode(tree->right);
			tree->data = tempNode->data;
			tree->right = avl_remove(tree->right, tempNode->data);
#else
			tempNode = FindMinNode(tree->left);
			tree->data = tempNode->data;
			tree->left = RemoveNode(tree->left, tempNode->data);
#endif
		}
		else
		{
			tempNode = tree;
			if (tree->left == NULL && tree->right != NULL)
				tree = tree->right;
			else if (tree->left != NULL && tree->right == NULL)
				tree = tree->left;
			else
				tree = NULL;
			free(tempNode);
		}
	}

	return tree;
}
int PrintTree(Node* tree)
{
	// TODO:
	if (tree == NULL)
		return 1;

	PrintTree(tree->left);
	printf("%d ", tree->data);
	PrintTree(tree->right);

	return 0;
}
void main(void)
{
	Node* tree = CreateNode(10);
	Node* findNode;
	int input;

	InsertNode(tree, CreateNode(5));
	InsertNode(tree, CreateNode(1));
	InsertNode(tree, CreateNode(6));
	InsertNode(tree, CreateNode(17));
	InsertNode(tree, CreateNode(14));
	InsertNode(tree, CreateNode(21));

	while (1)
	{
		printf("현재 트리 출력: ");
		if (PrintTree(tree))
		{
			printf("출력할 노드가 없습니다.\n");
			break;
		}
		printf("\n\n");
		printf(">> 삭제할 노드 : ");
		scanf("%d", &input);
		fflush(stdin);
		findNode = SearchNode(tree, input);
		if (findNode != NULL)
		{
			printf("해당 노드를 찾았습니다. 노드를 제거합니다. 노드의 위치는 %x 입니다.\n", findNode);
			tree = avl_remove(tree, input);
		}
		else
			printf("노드를 찾을 수 없습니다.\n");
	}
	system("PAUSE");
}
