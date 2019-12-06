// ���� Ž�� Ʈ���� ����� ���� ����

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

// ����� ����
typedef struct TreeNode {
	int key;
	struct TreeNode *left, *right;
} TreeNode;

// ���� Ž�� Ʈ�� ��� �Լ�
void display(TreeNode *p)
{
	if( p != NULL ) {
		printf("(");
		display(p->left);
		printf("%d", p->key);
		display(p->right);
		printf(")");
	}
}
// �ݺ����� Ž�� �Լ�
TreeNode *isearch(TreeNode *node, int key) 
{    
	while(node != NULL){ 
		if( key == node->key ) return node; 
		else if( key < node->key ) 
			node = node->left; 
		else 
			node = node->right; 
	} 
	return NULL; 	// Ž���� �������� ��� NULL ��ȯ
}
// ��ȯ���� Ž�� �Լ�
TreeNode *rsearch(TreeNode * t, int key)
{  
	if (t == NULL) return NULL;
	if (key == t->key)	return t;
	else if (key < t->key)	return rsearch(t->left, key);
	else return rsearch(t->right, key);
}
// key�� ���� Ž�� Ʈ�� root�� �����Ѵ�. 
// key�� �̹� root�ȿ� ������ ���Ե��� �ʴ´�.
void insert_node(TreeNode **root, int key) 
{
	TreeNode *p, *q; // p�� ���� ���, q�� �θ� ��� 
	TreeNode *n;	 // n�� ���ο� ���

	p = *root;
	q = NULL;
	// Ž���� ���� ���� 
	while (p != NULL){
		if( key == p->key) return;
		q = p;
		if( key < p->key ) p = p->left;
		else p = p->right;
	}
	// item�� Ʈ�� �ȿ� �����Ƿ� ���� ����
	n = (TreeNode *) malloc(sizeof(TreeNode));
	if( n == NULL ) return;
	// ������ ����
	n->key = key;
	n->left = n->right = NULL;
	// �θ� ���� ��ũ ����
	if( q != NULL ) 
		if( key < q->key ) 
			q->left = n;
		else q->right = n;
	else *root = n;
}
void delete_node(TreeNode *node, int key)
{
	TreeNode *p, *child, *succ, *succ_p, *t;

	// key�� ���� ��� t�� Ž��, p�� t�� �θ���
	p = NULL;
	t = node;
	while( t != NULL && t->key != key ){
		p = t;
		t = ( key < t->key ) ? t->left : t->right;
	}
	if( t == NULL ) { 	// Ž��Ʈ���� ���� Ű
		printf("key is not in the tree");
		return;
	}
	// �ܸ������ ���
	if( (t->left==NULL) && (t->right==NULL) ){ 
		if( p->left == t )  
			p->left = NULL;
		else   p->right = NULL;
	}
	// �ϳ��� �ڽĸ� ������ ���
	else if((t->left==NULL)||(t->right==NULL)){
		child = (t->left != NULL) ? t->left : t->right;
		if( p->left == t ) 
			p->left = child;
		else p->right = child;
	}
	else{		// �ΰ��� �ڽ��� ������ ���
		succ = t->right;
		while(succ->left != NULL){
			succ_p = succ;
			succ = succ->left;
		}
		if( succ_p->left == succ )
			succ_p->left = succ->right;
		else 
			succ_p->right = succ->right;
		t->key = succ->key;
		t = succ;
	}
	free(t);
}
//
int get_maximum(TreeNode *root)
{
	while(root->right != NULL) root=root->right;
	return root->key;
}
//
int get_minimum(TreeNode *root)
{
	while(root->left != NULL) root=root->left;
	return root->key;
}
//�ܸ� ��� �� ���ϱ�
int get_leaf_count(TreeNode *node)
{
	int count=0;
	if( node != NULL ){
		if( node->left==NULL && node->right==NULL ) return 1;
		else count = get_leaf_count(node->left)+ 
			get_leaf_count(node->right);
	}
	return count;
}
//��� �� ���ϱ�
int get_node_count(TreeNode *node)
{
	int count=0;
	if( node != NULL )
		count = 1 + get_node_count(node->left)+ 
			get_node_count(node->right);
	return count;
}
//
void delete_all(TreeNode *root)
{
	if( root!= NULL ){
		delete_all(root->left);
		delete_all(root->right);
		free(root);
	}
}
//���� ���ϱ�
int get_height(TreeNode *node)
{
	int height=0;
	if( node != NULL )
		height = 1 + max(get_height(node->left), 
			get_height(node->right));
	return height;
}
//
void help()
{
	printf("**************\n");
	printf("i: �Է�\n");
	printf("d: ����\n");
	printf("s: Ž��\n");
/*   printf("x: ��ü ��� ����\n");
	printf("h: ����\n");
	printf("c: ����� ����\n");
	printf("m: �ִ밪\n");
	printf("n: �ּҰ�\n");
	printf("t: �ܸ������ ����\n"); */
	printf("p: ���\n");
	printf("q: ����\n");
	printf("**************\n");
}

// ���� Ž�� Ʈ�� �׽�Ʈ ���α׷� 
void main()
{
	char command;
	int key;
	TreeNode *root=NULL;
	TreeNode *tmp;
	int count;

	do{
		help();
		command = getchar();
   
		switch(command){
		case 'i':
			printf("����:");
			scanf("%d", &key);
			insert_node(&root, key);
			break;
		case 'd':
			printf("����:");
			scanf("%d", &key);
			delete_node(root, key);
			break;
		case 'm':
			printf("%d\n",get_maximum(root));
			break;
		case 'n':
			printf("%d\n",get_minimum(root));
			break;
		case 't':
			count=0;
			count = get_leaf_count(root);
			printf("%d\n",count);
			break;
		case 'c':
			count=0;
			count = get_node_count(root);
			printf("%d\n",count);
			break;
		case 'x':
			delete_all(root);
			root=NULL;
			break;
		case 'h':
			printf("%d\n",get_height(root));
			break;
		case 'p':
			display(root);
			printf("\n");
			break;
		case 's':
			printf("����:");
			scanf("%d", &key);
			tmp=isearch(root, key);
			if( tmp != NULL )
				printf("Ž������:%d\n", tmp->key);
			break;
		}
		fflush(stdin);
		
	} while(command != 'q');
}
