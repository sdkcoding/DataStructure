/*
	day : 2016.01.20
	content : linked list�� ������ sparse matrix(��� ���)
*/
#include <stdio.h>
#include <stdlib.h>
#define STRUCT_DECLARATION_1	0	//struct declaration(����ü ����) ù��° ���
#define STRUCT_DECLARATION_2	1	//struct declaration(����ü ����) �ι�° ���
#define MAX_SIZE				5
/*
	��� ��� ��� ����ü ����
*/
typedef enum {head, entry} tagfield;
#if STRUCT_DECLARATION_1
typedef struct mNode* mPtr;
typedef struct {
	int row, col, val;
}entryNode;
typedef struct mNode{ //mNode �ݵ�� ����
	tagfield tag;
	union {
		mPtr next; entryNode term;
	}u;
	mPtr down, right;
}mNode, *mPtr;
#endif
#if STRUCT_DECLARATION_2
typedef struct mNode* mPtr;
typedef struct {
	int row, col, val;
}entryNode;
typedef struct mNode{ //mNode �ݵ�� ����
	tagfield tag;
	union {
		mPtr next; entryNode term;
	}u;
	mPtr down, right;
}mNode;
#endif 
mPtr H[MAX_SIZE];
int sparse_matrix[6][3] = { { 4,3,5 },{ 0,0,2 }, //4->�ִ� Row ��, 3->�ִ� Column ��, 5-> �ִ� �׸� 
							{ 1,0,4 },{ 1,2,3 },
							{ 3,0,8 },{ 3,1,6 } };
int count_i = 1;
mPtr newNode(void) {
	mPtr p = (mPtr)malloc(sizeof(mNode));
	return p;
}
void get_terms(int * row, int * col, int * val) {
	int i = 0;
	*row = sparse_matrix[count_i][i++];
	*col = sparse_matrix[count_i][i++];
	*val = sparse_matrix[count_i++][i++];
}
//��� ��� �Է�
mPtr mread(int Rows, int Cols, int Terms) {
	int row, col, val, cRow, Heads, i;
	mPtr m, tmp, last;
	Heads = (Rows > Cols) ? Rows : Cols;
	m = newNode();	m->tag = entry;
	m->u.term.row = Rows;	m->u.term.col = Cols;
	m->u.term.val = Terms;
	if (!Heads)	m->right = m;
	else {
		for (i = 0; i < Heads; i++) {
			tmp = newNode();	H[i] = tmp; 
			H[i]->tag = head;	H[i]->u.next = tmp;
			H[i]->down = H[i]->right = tmp;
		}
		cRow = 0; last = H[0];							//���� �� ������ ���
		for (i = 0; i < Terms; i++) {
			get_terms(&row, &col, &val);
			if (row > cRow) {							//���� �� ����
				last->right = H[cRow];	cRow = row;
				last = H[row];
			}
			tmp = newNode();		tmp->tag = entry;		
			tmp->u.term.val = val;	tmp->u.term.row = row;	
			tmp->u.term.col = col;
			last->right = H[col]->u.next->down = tmp;
			last = H[col]->u.next = tmp;
		}												//�� * �� ����Ʈ�� ����
		last->right = H[cRow];
		for (i = 0; i < Cols; i++)
			H[i]->u.next->down = H[i];
		for (i = 0; i < Heads - 1; i++)
			H[i]->u.next = H[i + 1];
		H[Heads - 1]->u.next = m;
		m->right = H[0];
	}
	return m;
}
//��� ��� ���
void mwrite(mPtr m) {
	int i;	mPtr tmp, H = m->right;
	printf("%d %d\n", m->u.term.row, m->u.term.col);
	for (i = 0; i < m->u.term.row; i++) {
		for (tmp = H->right; tmp != H; tmp = tmp->right) {
			printf("%d %d %d\n", tmp->u.term.row,
				tmp->u.term.col, tmp->u.term.val);
		}
		H = H->u.next;
	}
}
//��� ��� ����
void merase(mPtr * pm) {								//��� ����� ��� ptr
	int i; mPtr p, r, H = (*pm)->right;
	for (i = 0; i < (*pm)->u.term.row; i++) {
		p = H->right;
		while (p != H) { r = p; p = p->right; free(r); }
		H = H->u.next; free(p);							//���� ��
	}
	p = H;												//������ ��� ��ȯ
	while (p != *pm) { r = p; p = p->u.next; free(r); }
	free(*pm); *pm = NULL;
}

int main(void) {
	mPtr Matrix_List = mread(4, 3, 5);
	mwrite(Matrix_List);
	merase(&Matrix_List);
	return 0;
}