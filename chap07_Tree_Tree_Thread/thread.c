#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct TreeNode {
	int data;
	struct TreeNode *left, *right;
	int is_thread;	
} TreeNode;
//		     G
//	     C		  F
//    A	   B   D     E
/*오른쪽 자식을 넣어야 할 경우*/
void thread_insert_right(TreeNode * p, int data)
{
	TreeNode *q = (TreeNode*)malloc(sizeof(TreeNode));
	q->data = data;
	q->right = p->right;	q->is_thread = p->is_thread;
	q->left = NULL;		p->right = q;	p->is_thread = FALSE;
}
void thread_insert_left(TreeNode * p, int data)
{
	TreeNode *q = (TreeNode*)malloc(sizeof(TreeNode));
	q->data = data;
	q->left = p->left; q->right = p; p->left = q; q->is_thread = TRUE;
	if (q->left != NULL) {
		TreeNode * s = q->left;
		while (s->right != p) s = s->right;
		s->right = q;
	}
}
//
TreeNode *find_thread_successor(TreeNode *p)
{
	TreeNode *q = p->right;
	if (q == NULL || p->is_thread == TRUE)
		return q;
	while( q->left != NULL ) q = q->left;
	return q;
}
void thread_inorder(TreeNode *t)
{
	TreeNode *q;
	q=t;
	while (q->left) q = q->left;
	do
	{
		printf("%c ", q->data);
		q = find_thread_successor(q);
	} while(q);
}
int main(void)
{
	TreeNode *q = (TreeNode *)malloc(sizeof(TreeNode));
	q->data = 'G'; q->left = q->right = NULL; q->is_thread = FALSE;
	thread_insert_right(q, 'F');
	thread_insert_left(q, 'C');
	thread_insert_right(q->right, 'E');
	thread_insert_left(q->right, 'D');
	thread_insert_right(q->left, 'B');
	thread_insert_left(q->left, 'A');
	thread_inorder(q);
	return 0;
}

