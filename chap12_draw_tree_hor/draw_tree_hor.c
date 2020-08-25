#include <stdio.h>

#define space 5

typedef struct node {
	int value;          // value of the node
	struct node* left;  // left node
	struct node* right; // right node
}node;

//secondary function
void draw_tree_hor2(node* tree, int depth, char* path, int right)
{
	// stopping condition
	if (tree == NULL)
		return;

	// increase spacing
	depth++;

	// start with right node
	draw_tree_hor2(tree->right, depth, path, 1);

	if (depth > 1)
	{
		// set | draw map
		path[depth - 2] = 0;

		if (right)
			path[depth - 2] = 1;
	}

	if (tree->left)
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

	printf("%d\n", tree->value);

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
	draw_tree_hor2(tree->left, depth, path, 0);
}

//primary fuction
void draw_tree_hor(node* tree)
{
	// should check if we don't exceed this somehow..
	char path[1000] = { 0 };

	//initial depth is 0
	draw_tree_hor2(tree, 0, path, 0);
	printf("\n");
}

node n1, n2, n3, n4, n5, n6, n7;

int main()
{
	n1.value = 1;
	n2.value = 2;
	n3.value = 3;
	n4.value = 4;
	n5.value = 5;
	n6.value = 6;
	n7.value = 7;

	n1.right = &n2;
	n1.left = &n3;
	//n2.right = &n4;
	//n2.left = &n5;
	n3.right = &n6;
	n3.left = &n7;

	n2.right = &n3;
	n2.left = &n3;

	draw_tree_hor(&n1);

	return 0;
}