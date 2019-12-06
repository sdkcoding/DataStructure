// ���� Ž�� Ʈ���� ����� ���� ����

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#define MAX_WORD_SIZE	 100
#define MAX_MEANING_SIZE 200

// ������ ����
typedef struct {
	char word[MAX_WORD_SIZE];		// Ű�ʵ�
	char meaning[MAX_MEANING_SIZE];
} element;
// ����� ����
typedef struct TreeNode {
	element key;
	struct TreeNode *left, *right;
} TreeNode;

// ���� e1 > e2 -> -1 ��ȯ
// ���� e1 == e2 -> 0  ��ȯ 
// ���� e1 < e2 -> 1 ��ȯ
int compare(element e1, element e2)
{
	return strcmp(e1.word, e2.word);
}
// ���� Ž�� Ʈ�� ��� �Լ�
void display(TreeNode *p)
{
	if( p != NULL ) {
		printf("(");
		display(p->left);
		printf("%s", p->key.word);
		display(p->right);
		printf(")");
	}
}
// ���� Ž�� Ʈ�� Ž�� �Լ�
TreeNode *search(TreeNode *root, element key) 
{    
	TreeNode *p=root;
	while(p != NULL){ 
		switch(compare(key, p->key)){
		case -1:
			p = p->left;
			break;
		case 0:
			return p;
		case 1:
	  		p = p->right;
			break;
		}
    } 
    return p; 	// Ž���� �������� ��� NULL ��ȯ
} 
// key�� ���� Ž�� Ʈ�� root�� �����Ѵ�. 
// key�� �̹� root�ȿ� ������ ���Ե��� �ʴ´�.
void insert_node(TreeNode **root, element key) 
{
    TreeNode *p, *t; // p�� �θ� ���, p�� �ڽ� ��� 
	TreeNode *n;	 // n�� ���ο� ���

	t = *root;
	p = NULL;
	// Ž���� ���� ���� 
	while (t != NULL){
	  if( compare(key, t->key)==0 ) return;
	  p = t;
      if( compare(key , t->key)<0 ) t = t->left;
	  else t = t->right;
    }
	// item�� Ʈ�� �ȿ� �����Ƿ� ���� ����
	n = (TreeNode *) malloc(sizeof(TreeNode));
	if( n == NULL ) return;
	// ������ ����
	n->key = key;
	n->left = n->right = NULL;
	// �θ� ���� ��ũ ����
	if( p != NULL ) 
		if( compare(key, p->key)<0 ) 
			p->left = n;
		else p->right = n;
	else *root = n;
}
// ���� �Լ�
void delete_node(TreeNode **root, element key)
{
TreeNode *p, *child, *succ, *succ_p, *t;

// key�� ���� ��� t�� Ž��, p�� t�� �θ���
p = NULL;
t = *root;
while( t != NULL && compare(t->key, key) != 0 ){
	p = t;
	t = ( compare(key, t->key)<0 ) ? t->left : t->right;
}
if( t == NULL ) { 	// Ž��Ʈ���� ���� Ű
	printf("key is not in the tree");
	return;
}
// �ܸ������ ���
if( (t->left==NULL) && (t->right==NULL) ){ 
	if( p != NULL ){
		if( p->left == t )	 
			p->left = NULL;
		else   p->right = NULL;
	}
	else					// �θ��尡 ������ ��Ʈ
		*root = NULL;
}
// �ϳ��� �ڽĸ� ������ ���
else if((t->left==NULL)||(t->right==NULL)){
	child = (t->left != NULL) ? t->left : t->right;
	if( p != NULL ){
		if( p->left == t )	// �θ��带 �ڽĳ��� ���� 
			p->left = child;
		else p->right = child;
	}
	else
		*root = child;
}
else{		// �ΰ��� �ڽ��� ������ ���
	// ������ ����Ʈ������ �ļ��ڸ� ã�´�.
	succ_p = t;
	succ = t->right;
	// �ļ��ڸ� ã�Ƽ� ��� �������� �̵��Ѵ�.
	while(succ->left != NULL){
		succ_p = succ;
		succ = succ->left;
	}
	// �ļ����� �θ�� �ڽ��� ���� 
	if( succ_p->left == succ )
		succ_p->left = succ->right;
	else 
		succ_p->right = succ->right;
	// �ļ��ڸ� ���� ���� �̵��Ѵ�.
	t->key = succ->key;
	t = succ;
}
free(t);
}
//
void help()
{
   printf("**************\n");
   printf("i: �Է�\n");
   printf("d: ����\n");
   printf("s: Ž��\n");
   printf("p: ���\n");
   printf("q: ����\n");
   printf("**************\n");
}
// ���� Ž�� Ʈ���� ����ϴ� ���� ���� ���α׷� 
void main()
{
    char command;
 	element e;
	TreeNode *root=NULL;
	TreeNode *tmp;

    do{
		help();
       	command = getchar();
        fflush(stdin);
		switch(command){
		case 'i':
			printf("�ܾ�:");
			gets(e.word);
			printf("�ǹ�:");
			gets(e.meaning);
			insert_node(&root, e);
			break;
		case 'd':
			printf("�ܾ�:");
			gets(e.word);
			delete_node(&root, e);
			break;
		case 'p':
			display(root);
			printf("\n");
			break;
		case 's':
			printf("�ܾ�:");
			gets(e.word);
			tmp=search(root, e);
			if( tmp != NULL )
				printf("�ǹ�:%s\n", e.meaning);
			break;
		}
		
    } while(command != 'q');
}
