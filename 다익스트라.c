#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 9999

typedef struct GraphType {
	int n; // 정점의 개수
	int weight[MAX_VERTICES][MAX_VERTICES];
}GraphType;

int distance[MAX_VERTICES]; // 시작 정점으로부터의 최단경로 거리
int found[MAX_VERTICES]; // 방문한 정점 표시

int choose(int distance[], int n, int found[]) {
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for (i = 0; i < n; i++) {
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	}
	return minpos;
}

void print_status(GraphType* g) {
	static int step = 1;
	printf("%d단계 : ", step++);
	printf("distance: ");

	for (int i = 0; i < g->n; i++) {
		if (distance[i] == INF) {
			printf(" * ");
		}
		else
			printf("%3d", distance[i]);
	}
	printf("\n");
	printf(" found: ");
	for (int i = 0; i < g->n; i++) {
		printf("%3d", found[i]);
	}
	printf("\n\n");
}

void shortest_path(GraphType* g, int start) {
	int i, u, w;
	for (i = 0; i < g->n; i++) { // 초기화
		distance[i] = g->weight[start][i];
		found[i] = FALSE;
	}
	found[start] = TRUE; // 시작 정점 방문 표시
	distance[start] = 0;

	for (i = 0; i < g->n-1; i++) {
		print_status(g);
		u = choose(distance, g->n, found);
		found[u] = TRUE;

		for (w = 0; w < g->n; w++) {
			if (!found[w]) {
				if (distance[u] + g->weight[u][w] < distance[w])
					distance[w] = distance[u] + g->weight[u][w];
			}
		}
	}

	printf("\n");
	for (int i = 0; i < g->n; i++)
		if (distance[i] == INF) {
			printf("%d의 최단경로 %2s\n", i, "INF");
		}
		else {
			printf("%d의 최단경로 %2d\n", i, distance[i]);
		}
}

void print_adj_mat(GraphType* g) { // 인접 행렬 출력 함수
	char* str = "INF";
	for (int i = 0; i < g->n; i++) {
		for (int j = 0; j < g->n; j++) {
			if (g->weight[i][j] == INF) {
				printf("%5s ", str);
			}
			else
				printf("%5d ", g->weight[i][j]);
		}
		printf("\n");
	}
}

int main(void) {
	int num;
	GraphType g = { 8,
		{{0,4,7,10,INF,INF,INF,INF},
		{INF,0,INF,INF,8,INF,INF,INF},
		{INF,2,0,2,8,INF,INF,INF},
		{INF,INF,INF,0,INF,INF,8,20},
		{INF,INF,INF,INF,0,12,INF,INF},
		{INF,INF,INF,INF,INF,0,INF,4},
		{INF,INF,12,INF,INF,7,0,INF},
		{INF,INF,INF,INF,INF,INF,3,0}}
		
	};

	print_adj_mat(&g);
	printf("\n\n");

	printf("\n시작정점 입력: ");
	scanf("%d", &num);
	shortest_path(&g, num);

	return 0;
}