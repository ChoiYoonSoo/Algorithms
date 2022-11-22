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

typedef struct { // ť Ÿ��
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

void queue_init(QueueType* q) { // ���� ���� ���� �Լ�
	q->front = q->rear = 0;
}

int is_empty(QueueType* q) { // ���� ���� ���� �Լ�
	return (q->front == q->rear);
}

int is_full(QueueType* q) { // ��ȭ ���� ���� �Լ�
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void enqueue(QueueType* q, int item) { // ���� �Լ�
	if (is_full(q))
		error("ť�� ��ȭ�����Դϴ�");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
}

int dequeue(QueueType* q) {
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
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

void insert_vertex(GraphType1* g, int v, int size) { // ���� ���� ����
	if ((g->n) + 1 > size) {
		fprintf(stderr, "�׷���: ������ ���� �ʰ�");
		return;
	}
	g->n++;
}

void insert_vertex2(GraphType2* g, int v) { // ���� ���� ����
	if ((g->n) + 1 > 10) {
		fprintf(stderr, "�׷���: ������ ���� �ʰ�");
		return;
	}
	g->n++;
}

int s = 1;
void insert_edge(GraphType1* g, int start, int end) { // ���� ���� ����
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
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
		printf("���� ��ȣ ����");
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

	queue_init(&q); // ť �ʱ�ȭ
	visited1[v] = TRUE; // ���� v �湮 ǥ��
	enqueue(&q, v); // ���� ������ ť�� ����

	while (!is_empty(&q)) {
		v = dequeue(&q); // ť�� ���� ����
		printf("\n=============���� %d================\n",v);
		for (w = 0; w < g->n; w++) { // ���� ���� Ž��
			if (g->adj_mat[v][w]) {
				printf("\n���� %d ->  ���� ���� %d", v, w);
			}
			if (g->adj_mat[v][w] && !visited1[w]) {
				visited1[w] = TRUE; // �湮 ǥ��
				printf("\n���� %d ť ����\n", w);
				enqueue(&q, w); // �湮�� ������ ť�� ����
			}
		}
	}
}

void bfs_list(GraphType2* g, int v) {
	GraphNode* w;
	QueueType q;

	queue_init(&q); // ť �ʱ�ȭ
	visited2[v] = TRUE; // ���� v �湮 ǥ��
	printf("���� %d -> ", v);
	enqueue(&q, v); // ���������� ť�� ����
	while (!is_empty(&q)) {
		v = dequeue(&q); // ť�� ����� ���� ����

		for (w = g->adj_list[v]; w; w = w->link) { // ���� ���� Ž��
			if (!visited2[w->vertex]) { // �̹湮 ���� Ž��
				visited2[w->vertex] = TRUE; // �湮 ǥ��
				printf("%d �湮 -> ", w->vertex);
				enqueue(&q, w->vertex); // ������ ť�� ����
			}
		}
	}
}

void print_adj_mat(GraphType1* g) { // ���� ��� ��� �Լ�
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
		printf("%d�� ���� ����Ʈ ", i);
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

int get_min_vertex(int n) { // �ּ� dist[v] ���� ���� ������ ��ȯ
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
		u = get_min_vertex(g->n); // ���� ���� distance ���� ������ ����
		selected[u] = TRUE;
		if (distance[u] == INF)
			return;
		printf("%d��° �ּ� ��� ���� : %d\n", i + 1, u);
		printf("����ġ: %d\n\n", distance[u]);
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

void bfs_list2(GraphType2* g, int v) { // ���� �˻� �Լ�
	GraphNode* w;
	QueueType q;

	queue_init(&q); // ť �ʱ�ȭ
	visited2[v] = TRUE; // ���� v �湮 ǥ��
	enqueue(&q, v); // ���������� ť�� ����
	while (!is_empty(&q)) {
		v = dequeue(&q); // ť�� ����� ���� ����

		for (w = g->adj_list[v]; w; w = w->link) { // ���� ���� Ž��
			if (!visited2[w->vertex]) { // �̹湮 ���� Ž��
				visited2[w->vertex] = TRUE; // �湮 ǥ��
				enqueue(&q, w->vertex); // ������ ť�� ����
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

void print_adj_mat2(GraphType1* g) { // ���� ���
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
	printf("\n0.����\n");
	printf("1.�ʺ�켱Ž��\n");
	printf("2.�ּ� ��� ���� Ʈ��(Prim)\n");
	printf("��ȣ�� �Է��ϼ���: ");
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
			printf("\n���α׷��� �����մϴ�.\n");
			return 0;
		}
		case 1: {
			int k;

			while (1) {
				printf("\n0.����\n");
				printf("1.�׷��� ����\n");
				printf("2.���\n");
				printf("3.�ʺ�켱Ž��\n");
				printf("��ȣ�� �Է��ϼ���: ");
				scanf("%d", &k);

				if (k == 0) {
					break;
				}
				else if (k == 1) {

					while (1) {
						printf("\n������ ���� �Է� : ");
						scanf("%d", &a);
						printf("������ ���� �Է� : ");
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
								printf("\n����Ǿ� ���� �ʽ��ϴ�.\n");
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
						printf("\n0.����\n");
						printf("1.G1 �׷���(�������) �ʺ�켱Ž��\n");
						printf("2.G2 �׷���(��������Ʈ) �ʺ�켱Ž��\n");
						printf("��ȣ�� �Է��ϼ���: ");
						scanf("%d", &x);

						if (x == 0) {
							break;
						}
						else if (x == 1) {
							int t;
							printf("\n���� �Է� : ");
							scanf("%d", &t);

							bfs_mat(g1, t);
							printf("\n");
							for (int i = 1; i < g1->n; i++) {
								if (!visited1[i]) {
									printf("\n\n����Ǿ����� �ʽ��ϴ�.\n");
									bfs_mat(g1, i);
								}
							}
							reset_arr(&visited1, g1->n);

						}
						else if (x == 2) {
							int t;
							printf("\n���� �Է�: ");
							scanf("%d", &t);

							bfs_list(g2, t);
							printf("\n");
							for (int i = 1; i < g2->n; i++) {
								if (!visited2[i]) {
									printf("\n\n����Ǿ����� �ʽ��ϴ�.\n");
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
				printf("\n���� �Է�: (-1 �Է½� ����)");
				scanf("%d", &t);
				if (t == -1) {
					break;
				}
				print_adj_mat2(g3);
				prim(g3, t);
				printf("����ġ�� ��: %d\n", min);

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