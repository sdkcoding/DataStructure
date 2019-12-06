/*
	day : 2016.01.20
	content : linked list로 구현한 sparse matrix(희소 행렬)
*/
#include <stdio.h>
#include <stdlib.h>
#define STRUCT_DECLARATION_1	0	//struct declaration(구조체 선언) 첫번째 방법
#define STRUCT_DECLARATION_2	1	//struct declaration(구조체 선언) 두번째 방법
#define MAX_SIZE				5
/*
	희소 행렬 노드 구조체 정의
*/
typedef enum {head, entry} tagfield;
#if STRUCT_DECLARATION_1
typedef struct mNode* mPtr;
typedef struct {
	int row, col, val;
}entryNode;
typedef struct mNode{ //mNode 반드시 포함
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
typedef struct mNode{ //mNode 반드시 포함
	tagfield tag;
	union {
		mPtr next; entryNode term;
	}u;
	mPtr down, right;
}mNode;
#endif 
mPtr H[MAX_SIZE];
int sparse_matrix[6][3] = { { 4,3,5 },{ 0,0,2 }, //4->최대 Row 수, 3->최대 Column 수, 5-> 최대 항목 
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
//희소 행렬 입력
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
		cRow = 0; last = H[0];							//현재 행 마지막 노드
		for (i = 0; i < Terms; i++) {
			get_terms(&row, &col, &val);
			if (row > cRow) {							//현재 행 종료
				last->right = H[cRow];	cRow = row;
				last = H[row];
			}
			tmp = newNode();		tmp->tag = entry;		
			tmp->u.term.val = val;	tmp->u.term.row = row;	
			tmp->u.term.col = col;
			last->right = H[col]->u.next->down = tmp;
			last = H[col]->u.next = tmp;
		}												//행 * 열 리스트에 연결
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
//희소 행렬 출력
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
//희소 행렬 삭제
void merase(mPtr * pm) {								//헤더 노드의 헤더 ptr
	int i; mPtr p, r, H = (*pm)->right;
	for (i = 0; i < (*pm)->u.term.row; i++) {
		p = H->right;
		while (p != H) { r = p; p = p->right; free(r); }
		H = H->u.next; free(p);							//다음 행
	}
	p = H;												//나머지 헤더 반환
	while (p != *pm) { r = p; p = p->u.next; free(r); }
	free(*pm); *pm = NULL;
}

int main(void) {
	mPtr Matrix_List = mread(4, 3, 5);
	mwrite(Matrix_List);
	merase(&Matrix_List);
	return 0;
}