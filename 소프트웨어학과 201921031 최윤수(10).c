#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
#define MAX_QUEUE_SIZE 10
#define MAX_VERTICES 100
#define INF 999

int visited1[10];
int visited2[6];
int selected[MAX_VERTICES];
int distance[MAX_VERTICES];

typedef struct { // 큐 타입
	int queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;

typedef struct {
	int n;
	int **adj_mat;
}GraphType1;

typedef struct GraphNode {
	int vertex;
	struct GraphNode* link;
}GraphNode;

typedef struct GraphType2 {
	int n;
	GraphNode* adj_list[20];
}GraphType2;

void error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void queue_init(QueueType* q) { // 공백 상태 검출 함수
	q->front = q->rear = 0;
}

int is_empty(QueueType* q) { // 공백 상태 검출 함수
	return (q->front == q->rear);
}

int is_full(QueueType* q) { // 포화 상태 검출 함수
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void enqueue(QueueType* q, int item) { // 삽입 함수
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
}

int dequeue(QueueType* q) {
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];
}

void graph_init(GraphType1* g,int a,int b) {
	int r, c;
	g->n = 0;
	g->adj_mat = (int**)malloc(sizeof(int*) * a);
	for (int i = 0; i < a; i++) {
		g->adj_mat[i] = (int*)malloc(sizeof(int) * b);
	}

	for (r = 0; r < a; r++) {
		for (c = 0; c < b; c++) {
			g->adj_mat[r][c] = 0;
		}
	}
}

void graph_init2(GraphType2* g) {

	g->n = 0;
	for (int v = 0; v < 20; v++) {
		g->adj_list[v] = NULL;
	}
}

void insert_vertex(GraphType1* g, int v, int size) { // 정점 삽입 연산
	if ((g->n) + 1 > size) {
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	g->n++;
}

void insert_vertex2(GraphType2* g, int v) { // 정점 삽입 연산
	if ((g->n) + 1 > 10) {
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	g->n++;
}

int s = 1;
void insert_edge(GraphType1* g, int start, int end) { // 간선 삽입 연산
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	if (s == g->adj_mat[start][end]) {
		s++;
	}
	g->adj_mat[start][end] = 1;
}

void insert_edge2(GraphType2* g, int u, int v) {
	GraphNode* node;
	if (u >= g->n || v >= g->n) {
		printf("정점 번호 오류");
		return;
	}
	node = (GraphNode*)malloc(sizeof(GraphNode));
	node->vertex = v;
	node->link = g->adj_list[u];
	g->adj_list[u] = node;
}

void bfs_mat(GraphType1* g, int v) {
	int w;
	QueueType q;

	queue_init(&q); // 큐 초기화
	visited1[v] = TRUE; // 정점 v 방문 표시
	enqueue(&q, v); // 시작 정점을 큐에 저장

	while (!is_empty(&q)) {
		v = dequeue(&q); // 큐에 정점 추출
		printf("\n=============정점 %d================\n",v);
		for (w = 0; w < g->n; w++) { // 인접 정점 탐색
			if (g->adj_mat[v][w]) {
				printf("\n정점 %d ->  인접 정점 %d", v, w);
			}
			if (g->adj_mat[v][w] && !visited1[w]) {
				visited1[w] = TRUE; // 방문 표시
				printf("\n정점 %d 큐 삽입\n", w);
				enqueue(&q, w); // 방문한 정점을 큐에 저장
			}
		}
	}
}

void bfs_list(GraphType2* g, int v) {
	GraphNode* w;
	QueueType q;

	queue_init(&q); // 큐 초기화
	visited2[v] = TRUE; // 정점 v 방문 표시
	printf("정점 %d -> ", v);
	enqueue(&q, v); // 시작정점을 큐에 저장
	while (!is_empty(&q)) {
		v = dequeue(&q); // 큐에 저장된 정점 선택

		for (w = g->adj_list[v]; w; w = w->link) { // 인접 정점 탐색
			if (!visited2[w->vertex]) { // 미방문 정점 탐색
				visited2[w->vertex] = TRUE; // 방문 표시
				printf("%d 방문 -> ", w->vertex);
				enqueue(&q, w->vertex); // 정점을 큐에 삽입
			}
		}
	}
}

void print_adj_mat(GraphType1* g) { // 인접 행렬 출력 함수
	for (int i = 0; i < g->n; i++) {
		for (int j = 0; j < g->n; j++) {
			printf("%2d ", g->adj_mat[i][j]);
		}
		printf("\n");
	}
}

void print_adj_list(GraphType2* g) {
	for (int i = 0; i < g->n; i++) {
		GraphNode* p = g->adj_list[i];
		printf("%d의 인접 리스트 ", i);
		while (p != NULL) {
			printf("-> %d ", p->vertex);
			p = p->link;
		}
		printf("\n");
	}
}

void reset_arr(int* visited, int size) {
	for (int i = 0; i < size; i++) {
		visited[i] = 0;
	}
}

int get_min_vertex(int n) { // 최소 dist[v] 값을 갖는 정점을 반환
	int v, i;
	for (i = 0; i < n; i++) {
		if (!selected[i]) {
			v = i;
			break;
		}
	}
	for (i = 0; i < n; i++) {
		if (!selected[i] && (distance[i] < distance[v]))
			v = i;
	}
	return (v);
}

int min = 0;
void prim(GraphType1* g, int s) {
	int i, u, v;

	for (u = 0; u < g->n; u++) {
		distance[u] = INF;
	}
	distance[s] = 0;

	for (i = 0; i < g->n; i++) {
		u = get_min_vertex(g->n); // 가장 작은 distance 값을 가지는 정점
		selected[u] = TRUE;
		if (distance[u] == INF)
			return;
		printf("%d번째 최소 비용 정점 : %d\n", i + 1, u);
		printf("가중치: %d\n\n", distance[u]);
		min += distance[u];

		for (v = 0; v < g->n; v++) {
			if (g->adj_mat[u][v] != INF) {
				if (!selected[v] && g->adj_mat[u][v] < distance[v]) {
					distance[v] = g->adj_mat[u][v];
				}
			}
		}
	}
}

void bfs_list2(GraphType2* g, int v) { // 연결 검사 함수
	GraphNode* w;
	QueueType q;

	queue_init(&q); // 큐 초기화
	visited2[v] = TRUE; // 정점 v 방문 표시
	enqueue(&q, v); // 시작정점을 큐에 저장
	while (!is_empty(&q)) {
		v = dequeue(&q); // 큐에 저장된 정점 선택

		for (w = g->adj_list[v]; w; w = w->link) { // 인접 정점 탐색
			if (!visited2[w->vertex]) { // 미방문 정점 탐색
				visited2[w->vertex] = TRUE; // 방문 표시
				enqueue(&q, w->vertex); // 정점을 큐에 삽입
			}
		}
	}
}

void create_prim(GraphType1* g1, GraphType1* g3) {
	g3->n = g1->n;
	int rn = 0;
	for (int i = 0; i < g3->n; i++) {
		for (int j = 0; j < g3->n; j++) {
			if (g1->adj_mat[i][j] != 0) {
				rn = rand() % 50 + 1;
				g3->adj_mat[i][j] = rn;
				g3->adj_mat[j][i] = rn;
			}
			else if (g1->adj_mat[i][j] == 0) {
				g3->adj_mat[i][j] = INF;
			}
		}
	}
}

void print_adj_mat2(GraphType1* g) { // 프림 출력
	char* str = "INF";
	for (int i = 0; i < g->n; i++) {
		for (int j = 0; j < g->n; j++) {
			if (g->adj_mat[i][j] == INF) {
				printf("%5s ", str);
			}
			else
				printf("%5d ", g->adj_mat[i][j]);
		}
		printf("\n");
	}
}

void menu() {
	printf("\n0.종료\n");
	printf("1.너비우선탐색\n");
	printf("2.최소 비용 신장 트리(Prim)\n");
	printf("번호를 입력하세요: ");
}

int main(void) {
	int n;
	int a, b;
	GraphType1* g1;
	GraphType2* g2;
	g1 = (GraphType1*)malloc(sizeof(GraphType1));
	g2 = (GraphType2*)malloc(sizeof(GraphType2));

	while (1) {
		menu();
		scanf("%d", &n);

		switch (n) {
		case 0: {
			printf("\n프로그램을 종료합니다.\n");
			return 0;
		}
		case 1: {
			int k;

			while (1) {
				printf("\n0.종료\n");
				printf("1.그래프 생성\n");
				printf("2.출력\n");
				printf("3.너비우선탐색\n");
				printf("번호를 입력하세요: ");
				scanf("%d", &k);

				if (k == 0) {
					break;
				}
				else if (k == 1) {

					while (1) {
						printf("\n정점의 개수 입력 : ");
						scanf("%d", &a);
						printf("간선의 개수 입력 : ");
						scanf("%d", &b);

						graph_init(g1, a, a);
						graph_init2(g2);

						for (int i = 0; i < a; i++) {
							insert_vertex(g1, i, a);
							insert_vertex2(g2, i);
						}

						for (int i = 0; i < b; i++) {
							int a1 = rand() % a;
							int a2 = rand() % a;
							if (a1 == a2) continue;
							insert_edge(g1, a1, a2);
							insert_edge(g1, a2, a1);
							if (s > 1) {
								s--;
								continue;
							}

							insert_edge2(g2, a1, a2);
							insert_edge2(g2, a2, a1);
						}

						print_adj_list(g2);
						printf("\n");
						bfs_list2(g2,0);

						int i;
						for (i = 0; i < g2->n; i++) {
							if (visited2[i] == FALSE) {
								printf("\n연결되어 있지 않습니다.\n");
								reset_arr(visited2, g2->n);
								break;
							}
						}

						if (i == g2->n) {
							print_adj_mat(g1);
							printf("\n");
							print_adj_list(g2);
							break;
						}

					}
					reset_arr(visited2, g2->n);

				}
				else if (k == 2) {
					printf("\n");
					print_adj_mat(g1);
					printf("\n");
					print_adj_list(g2);
				}
				else if (k == 3) {
					int x;

					while (1) {
						printf("\n0.종료\n");
						printf("1.G1 그래프(인접행렬) 너비우선탐색\n");
						printf("2.G2 그래프(인접리스트) 너비우선탐색\n");
						printf("번호를 입력하세요: ");
						scanf("%d", &x);

						if (x == 0) {
							break;
						}
						else if (x == 1) {
							int t;
							printf("\n정점 입력 : ");
							scanf("%d", &t);

							bfs_mat(g1, t);
							printf("\n");
							for (int i = 1; i < g1->n; i++) {
								if (!visited1[i]) {
									printf("\n\n연결되어있지 않습니다.\n");
									bfs_mat(g1, i);
								}
							}
							reset_arr(&visited1, g1->n);

						}
						else if (x == 2) {
							int t;
							printf("\n정점 입력: ");
							scanf("%d", &t);

							bfs_list(g2, t);
							printf("\n");
							for (int i = 1; i < g2->n; i++) {
								if (!visited2[i]) {
									printf("\n\n연결되어있지 않습니다.\n");
									bfs_list(g2, i);
								}
							}
							reset_arr(&visited2, g2->n);
						}
					}
				}
			}

			break;
		}
		case 2: {
			GraphType1* g3;
			g3 = (GraphType1*)malloc(sizeof(GraphType1));
			int t;

			graph_init(g3, a, a);
			create_prim(g1, g3);


			while (1) {
				printf("\n정점 입력: (-1 입력시 종료)");
				scanf("%d", &t);
				if (t == -1) {
					break;
				}
				print_adj_mat2(g3);
				prim(g3, t);
				printf("가중치의 합: %d\n", min);

				for (int i = 0; i < MAX_VERTICES; i++) {
					distance[i] = INF;
					selected[i] = 0;
				}
				min = 0;
			}

			break;
		}
		}

	}
	return 0;
}