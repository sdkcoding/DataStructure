#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>

#pragma warning(disable:4996) // This function or variable may be unsafe.

#define RIGHT_LEFTMOST	0
#define LEFT_RIGHTMOST	1
#define REMOVE_TYPE		RIGHT_LEFTMOST

typedef struct avl_node {
	int data;
	int diff;
	struct avl_node* left_child;
	struct avl_node* right_child;  /* Subtrees. */                   /* Pointer to data. */
}AVL_NODE;
 
// 오른쪽 회전 함수(아래로부터 Left-Left로 불균형) 
AVL_NODE* rotate_right(AVL_NODE* parent)
{
	AVL_NODE* child = parent->left_child;
	parent->left_child = child->right_child;
	child->right_child = parent;
	return child;
}
// 왼쪽 회전 함수(아래로부터 Right-Right로 불균형)
AVL_NODE* rotate_left(AVL_NODE* parent)
{
	AVL_NODE* child = parent->right_child;
	parent->right_child = child->left_child;
	child->left_child = parent;
	return child;
}
// 오른쪽-왼쪽 회전 함수(아래로부터 Left-Right로 불균형)
AVL_NODE* rotate_right_left(AVL_NODE* parent)
{
	AVL_NODE* child = parent->right_child;
	parent->right_child = rotate_right(child);
	return rotate_left(parent);
}
// 왼쪽-오른쪽 회전 함수(아래로부터 Right-Left로 불균형)
AVL_NODE* rotate_left_right(AVL_NODE* parent)
{
	AVL_NODE* child = parent->left_child;
	parent->left_child = rotate_left(child);
	return rotate_right(parent);
}
// 트리의 높이를 반환
int get_height(AVL_NODE* node)
{
	int height = 0;
	if (node != NULL)
		height = 1 + max(get_height(node->left_child),
			get_height(node->right_child));
	return height;
}

// 노드의 균형인수를 반환
int get_height_diff(AVL_NODE* node)
{
	if (node == NULL) return 0;
	return get_height(node->left_child) - get_height(node->right_child);
}

// 트리를 균형트리로 만든다
AVL_NODE* rebalance(AVL_NODE** node)
{
	int height_diff = get_height_diff(*node);
	if (height_diff > 1) {
		if (get_height_diff((*node)->left_child) > 0)
			*node = rotate_right(*node);
		else
			*node = rotate_left_right(*node);
	}
	else if (height_diff < -1) {
		if (get_height_diff((*node)->right_child) < 0)
			*node = rotate_left(*node);
		else
			*node = rotate_right_left(*node);
	}
	return *node;
}

// AVL 트리의 삽입 연산
AVL_NODE* avl_add(AVL_NODE** root, int new_key)
{
	if (*root == NULL) {
		*root = (AVL_NODE*) malloc(sizeof(AVL_NODE));
		if (*root == NULL) {
			fprintf(stderr, "메모리 할당 에러\n");
			exit(1);
		}
		(*root)->data = new_key;
		(*root)->diff = 0;
		(*root)->left_child = (*root)->right_child = NULL;
	}
	else if (new_key < (*root)->data) {
		(*root)->left_child = avl_add(&((*root)->left_child), new_key);
		*root = rebalance(root);
	}
	else if (new_key > (*root)->data) {
		(*root)->right_child = avl_add(&((*root)->right_child), new_key);
		*root = rebalance(root);
	}
	else {
		fprintf(stderr, "중복된 키 에러\n");
		exit(1);
	}
	return *root;
}

// AVL 트리의 탐색함수
AVL_NODE* avl_search(AVL_NODE* node, int key)
{
	if (node == NULL) return NULL;
	printf("%d ", node->data);
	if (key == node->data) return node;
	else if (key < node->data)
		return avl_search(node->left_child, key);
	else
		return avl_search(node->right_child, key);
}

AVL_NODE* avl_findMaxNode(AVL_NODE* tree)
{
	// TODO:
	if (tree == NULL)
		return NULL;

	if (tree->right_child == NULL)
		return tree;
	else
		return avl_findMaxNode(tree->right_child);
}

AVL_NODE* avl_findMinNode(AVL_NODE* tree)
{
	// TODO:
	if (tree == NULL)
		return NULL;

	if (tree->left_child == NULL)
		return tree;
	else
		return avl_findMinNode(tree->left_child);
}

AVL_NODE* avl_remove(AVL_NODE* tree, int data)
{
	// TODO:
	AVL_NODE* tempNode;

	if (tree == NULL)
		return NULL;

	if (tree->data > data)
		tree->left_child = avl_remove(tree->left_child, data);
	else if (tree->data < data)
		tree->right_child = avl_remove(tree->right_child, data);
	else
	{
		if (tree->left_child != NULL && tree->right_child != NULL)
		{
#if (REMOVE_TYPE==RIGHT_LEFTMOST)
			tempNode = avl_findMinNode(tree->right_child);
			tree->data = tempNode->data;
			tree->right_child = avl_remove(tree->right_child, tempNode->data);
#else
			tempNode = avl_findMaxNode(tree->left_child);
			tree->data = tempNode->data;
			tree->left_child = avl_remove(tree->left_child, tempNode->data);
#endif
		}
		else
		{
			tempNode = tree;
			if (tree->left_child == NULL && tree->right_child != NULL)
				tree = tree->right_child;
			else if (tree->left_child != NULL && tree->right_child == NULL)
				tree = tree->left_child;
			else
				tree = NULL;
			free(tempNode);
		}
	}

	return tree;
}

void diff_tree(AVL_NODE* tree) {
	if (tree != NULL) {
		diff_tree(tree->left_child);
		tree->diff = get_height_diff(tree);
		diff_tree(tree->right_child);
	}
}

#define space 5

void draw_tree_hor2(AVL_NODE* tree, int depth, char* path, int right)
{
	// stopping condition
	if (tree == NULL)
		return;

	// increase spacing
	depth++;

	// start with right node
	draw_tree_hor2(tree->right_child, depth, path, 1);

	if (depth > 1)
	{
		// set | draw map
		path[depth - 2] = 0;

		if (right)
			path[depth - 2] = 1;
	}

	if (tree->left_child)
		path[depth - 1] = 1;

	// print root after spacing
	printf("\n");

	for (int i = 0; i < depth - 1; i++)
	{
		if (i == depth - 2)
			printf("+");
		else if (path[i])
			printf("|");
		else
			printf(" ");

		for (int j = 1; j < space; j++)
			if (i < depth - 2)
				printf(" ");
			else
				printf("-");
	}

	printf("%d(%d)\n", tree->data, tree->diff);

	// vertical spacers below
	for (int i = 0; i < depth; i++)
	{
		if (path[i])
			printf("|");
		else
			printf(" ");

		for (int j = 1; j < space; j++)
			printf(" ");
	}

	// go to left node
	draw_tree_hor2(tree->left_child, depth, path, 0);
}

//primary fuction
void draw_tree_hor(AVL_NODE* tree)
{
	// should check if we don't exceed this somehow..
	char path[1000] = { 0 };

	//initial depth is 0
	draw_tree_hor2(tree, 0, path, 0);
	printf("\n");
}

AVL_NODE* root;

void main()
{
	srand((int)time(NULL));
	int data[100] = { 0 };
	int random;
	for (int i = 0; i < 100; ) {
		random = rand() % 100;	// 0 ~ 99
		if (!data[random]) {
			avl_add(&root, random + 1);
			data[random] = 1;
			i++;
		}
	}
	diff_tree(root);
	draw_tree_hor(root);
	system("pause");
}