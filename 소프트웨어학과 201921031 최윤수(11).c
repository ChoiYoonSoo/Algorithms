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
	int n; // ������ ����
	int weight[MAX_VERTICES][MAX_VERTICES];
}GraphType;

typedef struct GraphNode {
	int vertex;
	struct GraphNode* link;
}GraphNode;

typedef struct GraphType2 {
	int n; // ������ ����
	GraphNode* adj_list[MAX_VERTICES];
}GraphType2;

typedef struct ListNode {
	int data;
	struct ListNode* link;
}ListNode;

ListNode* insert(ListNode* head, int value) {
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = head;
	head = p;
	return head;
}

void print_list(ListNode* head) {
	for (ListNode* p = head; p != NULL; p = p->link) {
		printf("%d-> ", p->data);
	}
}

void graph_init(GraphType2* g) { // �׷��� �ʱ�ȭ
	int v;
	g->n = 0;
	for (v = 0; v < MAX_VERTICES; v++)
		g->adj_list[v] = NULL;
}

void insert_vertex(GraphType2* g, int v) { // ���� ���� ����
	if ((g->n) + 1 > MAX_VERTICES) {
		fprintf(stderr, "�׷���: ������ ���� �ʰ�");
		return;
	}
	g->n++;
}

void insert_edge(GraphType2* g, int u, int v) { // ���� ���� ����, v�� u�� ��������Ʈ�� �����Ѵ�.
	GraphNode* node;
	if (u > g->n || v > g->n) {
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
		return;
	}
	node = (GraphNode*)malloc(sizeof(GraphNode));
	node->vertex = v;
	node->link = g->adj_list[u];
	g->adj_list[u] = node;
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

void print_adj_list2(GraphType2* g) {
	for (int i = 1; i <= g->n; i++) {
		GraphNode* p = g->adj_list[i];
		printf("%d�� ���� ����Ʈ ", i);
		while (p != NULL) {
			printf("-> %d ", p->vertex);
			p = p->link;
		}
		printf("\n");
	}
}

ListNode* head = NULL;
int visited[8];
void dfs_list(GraphType2* g, int v) {
	GraphNode* w;
	visited[v] = TRUE;

	for (w = g->adj_list[v]; w; w = w->link) {
		if (!visited[w->vertex]) {
			dfs_list(g, w->vertex);
		}
	}
	head = insert(head, v);
}

void reset_arr(int* visited, int size) {
	for (int i = 0; i <= size; i++) {
		visited[i] = 0;
	}
}

int distance[MAX_VERTICES]; // ���� �������κ����� �ִܰ�� �Ÿ�
int found[MAX_VERTICES]; // �湮�� ���� ǥ��
int prev[MAX_VERTICES]; // ���Ŀ� ���� ǥ��

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

void print_status(GraphType* g, int start) {
	printf("distance: ");

	for (int i = 0; i < g->n; i++) {
		if (distance[i] == INF) {
			printf("*    ");
		}
		else
			printf("%-5d", distance[i]);
	}
	printf("\n");
	printf("visited:  ");
	for (int i = 0; i < g->n; i++) {
		printf("%-5d", found[i]);
	}
	printf("\n");
	printf("prev:     ");
	for (int i = 0; i < g->n; i++) {
		if (i == start) printf("-    ");
		else printf("%-5d", prev[i]);
	}
	printf("\n\n");
}

void shortest_path(GraphType* g, int start) {
	int i, u, w;
	int idx = 0;
	for (i = 0; i < g->n; i++) {
		prev[i] = 0;
	}

	for (i = 0; i < g->n; i++) { // �ʱ�ȭ
		distance[i] = g->weight[start][i];
		found[i] = FALSE;
		if(g->weight[start][i] != INF)
			prev[i] = start;
	}
	found[start] = TRUE; // ���� ���� �湮 ǥ��
	distance[start] = 0;

	for (i = 0; i < g->n - 1; i++) {
		print_status(g,start);
		u = choose(distance, g->n, found);
		found[u] = TRUE;

		for (w = 0; w < g->n; w++) {
			if (!found[w]) {
				if (distance[u] + g->weight[u][w] < distance[w]) {
					distance[w] = distance[u] + g->weight[u][w];
					prev[w] = u;
				}
			}
		}
	}

	printf("\n");
	for (int i = 0; i < g->n; i++)
		if (distance[i] == INF) {
			printf("%d�� �ִܰ�� %2s\n", i, "INF");
		}
		else {
			printf("%d�� �ִܰ�� %2d\n", i, distance[i]);
		}
}

void all_shortest_path(GraphType* g, int start) {
	int i, u, w;
	for (i = 0; i < g->n; i++) { // �ʱ�ȭ
		distance[i] = g->weight[start][i];
		found[i] = FALSE;
	}
	found[start] = TRUE; // ���� ���� �湮 ǥ��
	distance[start] = 0;

	for (i = 0; i < g->n - 1; i++) {
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
			printf("%d�� �ִܰ�� %2s\n", i, "INF");
		}
		else {
			printf("%d�� �ִܰ�� %2d\n", i, distance[i]);
		}
}

void print_adj_mat(GraphType* g) { // ���� ��� ��� �Լ�
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

void menu() {
	printf("\n0.����\n");
	printf("1.��������\n");
	printf("2.Dijkstra\n");
	printf("��ȣ�� �Է��ϼ���: ");
}

int main(void) {
	int n;

	while (1) {
		menu();
		scanf("%d", &n);

		switch (n) {
		case 0: {
			printf("\n���α׷��� �����մϴ�.\n");
			return 0;
		}
		case 1: {
			int num;
			
			while (1) {
				printf("\n0.����\n");
				printf("1.��������(15) �׷���\n");
				printf("2.�ǽ����� �׷���\n");
				scanf("%d", &num);

				if (num == 0) {
					break;
				}

				else if (num == 1) {
					GraphType2* g2;
					g2 = (GraphType2*)malloc(sizeof(GraphType2));
					graph_init(g2);

					for (int i = 0; i <= 7; i++) {
						insert_vertex(g2, i);
					}

					// ���� 0�� ���� ����Ʈ
					insert_edge(g2, 0, 1);
					insert_edge(g2, 0, 3);

					// ���� 1�� ���� ����Ʈ
					insert_edge(g2, 1, 2);

					// ���� 2�� ���� ����Ʈ
					insert_edge(g2, 2, 5);
					insert_edge(g2, 2, 7);

					// ���� 3�� ���� ����Ʈ
					insert_edge(g2, 3, 4);
					insert_edge(g2, 3, 5);

					// ���� 4�� ���� ����Ʈ
					insert_edge(g2, 4, 5);
					insert_edge(g2, 4, 6);

					// ���� 5�� ���� ����Ʈ
					insert_edge(g2, 5, 6);
					insert_edge(g2, 5, 7);

					// ���� 6�� ���� ����Ʈ
					insert_edge(g2, 6, 7);

					printf("\n");
					print_adj_list(g2);

					int t;
					printf("\n���� �Է�: ");
					scanf("%d", &t);

					dfs_list(g2, t);
					printf("\n");

					for (int i = 0; i < g2->n; i++) {
						if (!visited[i]) {
							print_list(head);
							printf("\n\n");
							printf("\n\n�湮���� ���� ���� %d�� �ֽ��ϴ�.\n\n",i);
							dfs_list(g2, i);
						}
					}

					print_list(head);
					head = NULL;
					reset_arr(&visited, g2->n);
				}
				else if (num == 2) {
					GraphType2* g1;
					g1 = (GraphType2*)malloc(sizeof(GraphType2));
					graph_init(g1);

					for (int i = 0; i <= 7; i++) {
						insert_vertex(g1, i);
					}

					// ���� 1�� ���� ����Ʈ
					insert_edge(g1, 1, 2);

					// ���� 2�� ���� ����Ʈ
					insert_edge(g1, 2, 3);
					insert_edge(g1, 2, 5);
					insert_edge(g1, 2, 6);

					// ���� 3�� ���� ����Ʈ
					insert_edge(g1, 3, 8);

					// ���� 4�� ���� ����Ʈ
					insert_edge(g1, 4, 7);

					// ���� 5�� ���� ����Ʈ
					insert_edge(g1, 5, 6);
					insert_edge(g1, 5, 7);

					// ���� 6�� ���� ����Ʈ
					insert_edge(g1, 6, 8);

					// ���� 7�� ���� ����Ʈ
					insert_edge(g1, 7, 8);

					printf("\n");
					print_adj_list2(g1);

					int t;
					printf("\n���� �Է�: ");
					scanf("%d", &t);

					dfs_list(g1, t);
					printf("\n");

					for (int i = 1; i <= g1->n; i++) {
						if (!visited[i]) {
							print_list(head);
							printf("\n\n");
							printf("\n\n�湮���� ���� ���� %d�� �ֽ��ϴ�.\n\n",i);
							dfs_list(g1, i);
						}
					}

					print_list(head);
					printf("\n");
					head = NULL;
					reset_arr(&visited, g1->n);

				}

			}
			break;
		}
		case 2: {
			int a;
			while (1) {
				printf("\n0.����\n");
				printf("1.�������� 16�� �׷���\n");
				printf("2.���� 333�� �׷���\n");
				scanf("%d", &a);

				if (a == 0) {
					break;
				}
				else if (a == 1) {
					int num;
					GraphType g = { 8,
						{{0,10,7,4,INF,INF,INF,INF},
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

					printf("\n�������� �Է�: ");
					scanf("%d", &num);
					shortest_path(&g, num);

					int n;
					printf("\n��� ���� ������ ���� �ִܰ��\n");
					printf("0.No\n");
					printf("1.Yes");
					scanf("%d", &n);

					if (n == 1) {
						for (int i = 0; i <= 7; i++) {
							printf("\n�������� : %d\n", i);
							all_shortest_path(&g, i);
							for (int j = 0; j <= 8; j++) {
								distance[i] = 0;
								found[i] = 0;
								prev[i] = 0;
							}
						}
					}
				}
				else if (a == 2) {
					int num;
					GraphType g2 = { 8,
						{{0,8,9,11,INF,INF,INF,INF},
						{INF,0,INF,INF,10,INF,INF,INF},
						{INF,6,0,3,1,INF,INF,INF},
						{INF,INF,INF,0,INF,INF,8,8},
						{INF,INF,INF,INF,0,2,INF,INF},
						{INF,INF,INF,INF,INF,0,INF,4},
						{INF,INF,12,INF,INF,5,0,INF},
						{INF,INF,INF,INF,INF,INF,7,0}}
					};

					print_adj_mat(&g2);
					printf("\n\n");

					printf("\n�������� �Է�: ");
					scanf("%d", &num);
					shortest_path(&g2, num);

					int n;
					printf("\n��� ���� ������ ���� �ִܰ��\n");
					printf("0.No\n");
					printf("1.Yes");
					scanf("%d", &n);

					if (n == 1) {
						for (int i = 0; i <= 7; i++) {
							printf("\n�������� : %d\n", i);
							all_shortest_path(&g2, i);
							for (int j = 0; j <= 8; j++) {
								distance[i] = 0;
								found[i] = 0;
								prev[i] = 0;
							}
						}
					}
				}
			}


			break;
		}
		}
	}

	return 0;
}