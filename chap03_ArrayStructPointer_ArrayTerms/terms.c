#include <stdio.h>
#define MAX_T	101
typedef struct {
	float c; int e;
}term;
term terms[MAX_T] = { {2,3},{4,1},{5,0},{1,3},{2,2},{3,1} };
int avail = 6;

char comp(int a, int b) {
	if (a > b)	return	'>';
	else if (a < b)	return	'<';
	else return '=';
}
void att(float coef, int expo) {
	if (avail >= MAX_T) exit(1);
	terms[avail].c = coef; terms[avail++].e = expo;
}

void poly_add2(int sA, int eA, int sB, int eB, int *sC, int *eC) {
	float tc; *sC = avail;
	while (sA <= eA && sB <= eB) {
		switch (comp(terms[sA].e, terms[sB].e)) {
		case '>': att(terms[sA].c, terms[sA].e); sA++; break;
		case '<': att(terms[sB].c, terms[sB].e); sB++; break;
		case '=': tc = terms[sA].c + terms[sB].c;
			if (tc) att(tc, terms[sA].e); sA++; sB++; break;
		}
	}
	for (;sA <= eA; sA++) att(terms[sA].c, terms[sA].e);
	for (;sB <= eB; sB++) att(terms[sB].c, terms[sB].e);
	*eC = avail - 1;
}

void main() {
	int sC, eC; poly_add2(0, 2, 3, 5, &sC, &eC);
	int i = 0;
	for (;i<MAX_T;i++) {
		printf("(%.1f, %d)\n", terms[i].c, terms[i].e);
	}
}