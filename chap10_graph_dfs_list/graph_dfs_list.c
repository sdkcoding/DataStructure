#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 50

typedef struct GraphNode
{
	int vertex;
	struct GraphNode* link;
} GraphNode;

typedef struct GraphType {
	int n;	// 정점의 개수
	GraphNode* adj_list[MAX_VERTICES];
} GraphType;

// 그래프 초기화 
void graph_init(GraphType* g)
{
	int v;
	g->n = 0;
	for (v = 0; v < MAX_VERTICES; v++)
		g->adj_list[v] = NULL;
}
// 정점 삽입 연산
void insert_vertex(GraphType* g, int v)
{
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	g->n++;
}
// 간선 삽입 연산, v를 u의 인접 리스트에 삽입한다.
void insert_edge(GraphType* g, int u, int v)
{
	GraphNode* node;
	if (u >= g->n || v >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	node = (GraphNode*)malloc(sizeof(GraphNode));
	node->vertex = v;
	node->link = g->adj_list[u];
	g->adj_list[u] = node;
}
int visited[MAX_VERTICES];

// 인접 리스트로 표현된 그래프에 대한 깊이 우선 탐색
void dfs_list(GraphType* g, int v)
{
	GraphNode* w;
	visited[v] = TRUE;   		// 정점 v의 방문 표시 
	printf("%d ", v);   		// 방문한 정점 출력 
	for (w = g->adj_list[v]; w; w = w->link)// 인접 정점 탐색 
		if (!visited[w->vertex])
			dfs_list(g, w->vertex); //정점 w에서 DFS 새로시작
}

void main()
{
	int i;
	GraphType g;

	graph_init(&g);
	// 인접 리스트 생성 
	for (i = 0; i < 4; i++)
		insert_vertex(&g, i);
	insert_edge(&g, 0, 1);
	insert_edge(&g, 1, 0);
	insert_edge(&g, 0, 3);
	insert_edge(&g, 3, 0);
	insert_edge(&g, 1, 2);
	insert_edge(&g, 2, 1);
	insert_edge(&g, 1, 3);
	insert_edge(&g, 3, 1);
	insert_edge(&g, 2, 3);
	insert_edge(&g, 3, 2);
	dfs_list(&g, 0);
}
