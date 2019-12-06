#include <stdio.h>
#include <stdlib.h>
struct node {
	int				data;
	struct node *	left_link;
	struct node *	right_link;
};
typedef struct node Tree;

Tree* get_node()
{
	Tree *tmp;
	tmp = (Tree*)malloc(sizeof(Tree));
	tmp->left_link = NULL;
	tmp->right_link = NULL;
	return tmp;
}
void Tree_ins(Tree** root, int data)
{
	if (*root == NULL)
	{
		*root = get_node();
		(*root)->data = data;
		return;
	}
	if ((*root)->data> data)
		Tree_ins(&(*root)->left_link, data);
	else
		Tree_ins(&(*root)->right_link, data);
}
int Tree_search(Tree *root, int data)
{
	if (root == NULL)
	{
		printf("데이터가 존재하지 않습니다.");
		return 0;
	}
	if ((root)->data> data)
		Tree_search((root)->left_link, data);
	else if ((root)->data == data)
		return data;
	else
		Tree_search((root)->right_link, data);
}
void preorder(Tree *root)
{
	if (root)
	{
		printf("%d  ", root->data);
		preorder(root->left_link);
		preorder(root->right_link);
	}
}
void inorder(Tree *root)
{
	if (root)
	{
		inorder(root->left_link);
		printf("%d  ", root->data);
		inorder(root->right_link);
	}
}
void postorder(Tree *root)
{
	if (root)
	{
		postorder(root->left_link);
		postorder(root->right_link);
		printf("%d  ", root->data);
	}
}
Tree *find_min(Tree* root)
{
	if (root == NULL)  return  NULL;
	if (root->left_link == NULL)  return root;
	else	return (find_min(root->left_link));
}
Tree* delete_Tree(Tree *root, int x)
{
	Tree *temp, *child;
	if (root == NULL)  printf("Not Found");
	else  if (x < root->data)
		root->left_link = delete_Tree(root->left_link, x);
	else  if (x > root->data)
		root->right_link = delete_Tree(root->right_link, x);
	else  if (root->left_link && root->right_link) {
		temp = find_min(root->right_link);
		root->data = temp->data;
		root->right_link = delete_Tree(root->right_link, root->data);
	}
	else {
		temp = root;
		if (root->left_link == NULL)    child = root->right_link;
		if (root->right_link == NULL)  child = root->left_link;
		free(temp);
		return child;
	}
	return root;
}
int main(void)
{
	int test[20] = { 45,27,17,62,57,52,73,65,63,64,69,71,76 };
	Tree *root = NULL; Tree *delete_node = NULL;  int i;
	for (i = 0; test[i]>0; i++)
		Tree_ins(&root, test[i]);

	printf("기본 데이터 : ");
	for (i = 0; test[i]; i++)
		printf("%d  ", test[i]);
	printf("\npreorder 데이터 : ");
	preorder(root);
	printf("\ninorder 데이터 : ");
	inorder(root);
	printf("\npostorder 데이터 : ");
	postorder(root);
	printf("\n");
	fputs("찾을 데이터는 65입니다.\n", stdout);
	printf("찾은 데이터 : %d\n", Tree_search(root, 65));
	fputs("삭제할 데이터는 62입니다.\n", stdout);
	delete_Tree(root, 62);
	printf("\ninorder 데이터 : ");
	inorder(root);
	return 0;
}
