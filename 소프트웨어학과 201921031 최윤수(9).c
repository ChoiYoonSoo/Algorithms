#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 11 // 해싱 테이블의 크기

typedef struct {
	int key;
}element;

element hash_table[TABLE_SIZE];

typedef struct list {
	element item;
	struct list* link;
}list;
struct list* hash_table2[TABLE_SIZE];

typedef struct GraphType {
	int n; // 정점의 개수
	int** adj_mat;
}GraphType;

typedef struct GraphNode {
	int vertex;
	struct GraphNode* link;
}GraphNode;

typedef struct GraphType2 {
	int n;
	GraphNode* adj_list[10];
}GraphType2;

void init_table(element ht[]) { // 테이블 초기화
	for (int i = 0; i < TABLE_SIZE; i++) {
		ht[i].key = 0;
	}
}

int hash_function(int key) { // 제산 함수 이용 해싱 함수
	return key % TABLE_SIZE;
}

void hash_lp_add(element item, element ht[]) { // 선형 조사법을 이용하여 테이블에 키 삽입
	int i, hash_value;
	hash_value = i = hash_function(item.key);

	while (ht[i].key != 0) {
		if (item.key == ht[i].key) {
			printf("탐색키 중복\n");
			return;
		}
		i = (i + 1) % TABLE_SIZE;
		if (i == hash_value) {
			printf("테이블이 가득참\n");
			return;
		}
	}
	ht[i] = item;
}

void hash_lp_print(element ht[]) { // 해싱 테이블 내용 출력
	printf("\n============================\n");
	for (int i = 0; i < TABLE_SIZE; i++) {
		printf("[%d] %d\n", i, ht[i].key);
	}
	printf("\n============================\n\n");
}

void hash_qp_add(element item, element ht[]) { // 이차조사법
	int i, hash_value, inc = 0;
	hash_value = i = hash_function(item.key);

	while (ht[i].key != 0) {
		if (item.key == ht[i].key) {
			printf("탐색키 중복\n");
			return;
		}
		i = (hash_value + inc * inc) % TABLE_SIZE;
		inc = inc + 1;
	}
	ht[i] = item;
}

void hash_dh_add(element item, element ht[]) { // 더블해싱 방법
	int i, hash_value, inc;
	hash_value = i = hash_function(item.key);
	inc = 7 - (item.key % 7);

	while (ht[i].key != 0) {
		if (item.key == ht[i].key) {
			printf("탐색키 중복\n");
			return;
		}
		i = (i + inc) % TABLE_SIZE;
		if (i == hash_value) {
			printf("테이블이 가득참\n");
			return;
		}
	}
	ht[i] = item;
}

void hash_chain_add(element item, struct list* ht[]) {
	int hash_value = hash_function(item.key);
	struct list* ptr;
	struct list* node_before = NULL, *node = ht[hash_value];
	for (; node; node_before = node, node = node->link) {
		if (node->item.key == item.key) {
			fprintf(stderr, "이미 탐색키가 저장되어 있음\n");
			return;
		}
	}
	ptr = (struct list*)malloc(sizeof(struct list));
	ptr->item = item;
	ptr->link = NULL;

	if (node_before) {
		node_before->link = ptr;
	}
	else {
		ht[hash_value] = ptr;
	}
}

void hash_chain_print(struct list* ht[]) {
	struct list* node;
	printf("\n=====================================\n");
	for (int i = 0; i < TABLE_SIZE; i++) {
		printf("[%d]->", i);
		for (node = ht[i]; node; node = node->link) {
			printf("%d->", node->item.key);
		}
		printf("\n");
	}
	printf("=====================================\n");
}

void init(GraphType* g, int a, int b) { // 그래프 초기화
	g->n = 0;
	g->adj_mat = (int**)malloc(sizeof(int*) * a);
	for (int i = 0; i < a; i++) {
		g->adj_mat[i] = (int*)malloc(sizeof(int) * b);
	}

	for (int r = 0; r < a; r++) {
		for (int c = 0; c < b; c++) {
			g->adj_mat[r][c] = 0;
		}
	}
}

void insert_vertex(GraphType* g, int v,int size) { // 정점 삽입 연산
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

void insert_edge(GraphType* g, int start, int end) { // 간선 삽입 연산
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}

void print_adj_mat(GraphType* g) { // 인접 행렬 출력 함수
	for (int i = 0; i < g->n; i++) {
		for (int j = 0; j < g->n; j++) {
			printf("%2d ", g->adj_mat[i][j]);
		}
		printf("\n");
	}
}

void init2(GraphType2* g) {

	g->n = 0;
	for (int v = 0; v < 10; v++) {
		g->adj_list[v] = NULL;
	}
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

void print_adj_list2(GraphType2* g) {
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

#define TRUE 1
#define FALSE 0
int visited1[11];
int visited2[7];
int visited3[6];
void dfs_mat(GraphType* g, int v) { // 인접 행렬로 표현된 그래프에 대한 깊이 우선 탐색
	int w;
	visited1[v] = TRUE; // 정점 v의 방문 표시
	printf("정점 %d -> ", v); // 방문한 정점 출력
	for (w = 0; w < g->n; w++) { // 인접 정점 탐색
		if (g->adj_mat[v][w] && !visited1[w]) {
			dfs_mat(g, w); // 정점 w에서 DFS 새로 시작
		}
	}
}

void dfs_list(GraphType2* g, int v, int x) {
	GraphNode* w;
	if (x == 2) {
		visited2[v] = TRUE;
		printf("정점 %d -> ", v);
		for (w = g->adj_list[v]; w; w = w->link) {
			if (!visited2[w->vertex]) {
				dfs_list(g, w->vertex,x);
			}
		}
	}
	else if (x == 3) {
		visited3[v] = TRUE;
		printf("정점 %d -> ", v);
		for (w = g->adj_list[v]; w; w = w->link) {
			if (!visited3[w->vertex]) {
				dfs_list(g, w->vertex,x);
			}
		}
	}
}

void reset_arr(int* visited, int size) {
	for (int i = 0; i < size; i++) {
		visited[i] = 0;
	}
}

void menu() {
	printf("\n0.종료\n");
	printf("1.해시테이블\n");
	printf("2.그래프\n");
	printf("번호를 입력하세요 : ");
}
int main(void) {
	int n;
	
	while (1) {
		menu();
		scanf("%d", &n);

		switch (n) {
		case 0: {
			printf("\n프로그램을 종료합니다.\n");
			return 0;
		}
		case 1: {
			int k, j;
			element e;
			while (1) {
				printf("\n0.종료\n");
				printf("1.충돌 선형조사법 처리\n");
				printf("2.충돌 이차조사법 처리\n");
				printf("3.충돌 더블해싱법(f(x) = 7-(x mod 7)) 처리\n");
				printf("4.충돌 체이닝 방법 처리\n");
				printf("번호를 입력하세요 : ");
				scanf("%d", &k);
				printf("\n");

				if (k == 0) {
					break;
				}
				else if (k == 1) {
					init_table(hash_table);
					for (int i = 0; i < TABLE_SIZE; i++) {
						printf("%d번째 키 값 입력: ", i + 1);
						scanf("%d", &e.key);
						hash_lp_add(e, hash_table);
						hash_lp_print(hash_table);
					}
				}
				else if (k == 2) {
					init_table(hash_table);
					for (int i = 0; i < TABLE_SIZE; i++) {
						printf("%d번째 키 값 입력: ", i + 1);
						scanf("%d", &e.key);
						hash_qp_add(e, hash_table);
						hash_lp_print(hash_table);
					}
				}
				else if (k == 3) {
					init_table(hash_table);
					for (int i = 0; i < TABLE_SIZE; i++) {
						printf("%d번째 키 값 입력: ", i + 1);
						scanf("%d", &e.key);
						hash_dh_add(e, hash_table);
						hash_lp_print(hash_table);
					}
				}
				else if(k == 4) {
					init_table(hash_table2);
					for (int i = 0; i < TABLE_SIZE; i++) {
						printf("%d번째 키 값 입력: ", i + 1);
						scanf("%d", &e.key);
						hash_chain_add(e, hash_table2);
						hash_chain_print(hash_table2);
					}
				}
			}
			break;
			
		}
		case 2: {
			int k;
			GraphType* g1;
			GraphType2* g2;
			GraphType2* g3;
			g1 = (GraphType*)malloc(sizeof(GraphType));
			g2 = (GraphType2*)malloc(sizeof(GraphType2));
			g3 = (GraphType2*)malloc(sizeof(GraphType2));

			init(g1, 10, 10);
			init2(g2);
			init2(g3);
			for (int i = 0; i < 10; i++) {
				insert_vertex(g1, i, 10);
			}

			insert_edge(g1, 0, 8);
			insert_edge(g1, 0, 7);
			insert_edge(g1, 0, 3);
			insert_edge(g1, 8, 0);
			insert_edge(g1, 3, 0);
			insert_edge(g1, 3, 1);
			insert_edge(g1, 3, 2);
			insert_edge(g1, 7, 0);
			insert_edge(g1, 7, 2);
			insert_edge(g1, 7, 4);
			insert_edge(g1, 1, 3);
			insert_edge(g1, 1, 5);
			insert_edge(g1, 2, 3);
			insert_edge(g1, 2, 7);
			insert_edge(g1, 2, 5);
			insert_edge(g1, 2, 9);
			insert_edge(g1, 4, 7);
			insert_edge(g1, 4, 9);
			insert_edge(g1, 9, 4);
			insert_edge(g1, 9, 2);
			insert_edge(g1, 9, 6);
			insert_edge(g1, 6, 5);
			insert_edge(g1, 6, 9);
			insert_edge(g1, 5, 1);
			insert_edge(g1, 5, 2);
			insert_edge(g1, 5, 6);

			for (int i = 0; i < 6; i++) {
				insert_vertex2(g2, i);
			}

			insert_edge2(g2, 0, 1);
			insert_edge2(g2, 0, 3);
			insert_edge2(g2, 1, 0);
			insert_edge2(g2, 1, 3);
			insert_edge2(g2, 3, 1);
			insert_edge2(g2, 3, 0);
			insert_edge2(g2, 5, 4);
			insert_edge2(g2, 4, 5);
			insert_edge2(g2, 4, 2);
			insert_edge2(g2, 2, 4);

			for (int i = 0; i < 5; i++) {
				insert_vertex2(g3, i);
			}

			insert_edge2(g3, 0, 1);
			insert_edge2(g3, 0, 3);
			insert_edge2(g3, 1, 0);
			insert_edge2(g3, 1, 4);
			insert_edge2(g3, 2, 0);
			insert_edge2(g3, 2, 3);
			insert_edge2(g3, 3, 2);
			insert_edge2(g3, 4, 2);

			while (1) {
				printf("\n0.종료\n");
				printf("1.G1 인접행렬 출력\n");
				printf("2.G2 인접리스트 출력\n");
				printf("3.G3 인접리스트 출력\n");
				printf("4.깊이우선탐색\n");
				printf("번호를 입력하세요 :");
				scanf("%d", &k);

				if (k == 0) {
					break;
				}
				else if (k == 1) {
					print_adj_mat(g1);
					printf("\n");
				}
				else if (k == 2) {
					print_adj_list2(g2);
					printf("\n");
				}
				else if (k == 3) {
					print_adj_list2(g3);
					printf("\n");
				}
				else if (k == 4) {
					int x;

					while (1) {
						printf("\n0.종료\n");
						printf("1.G1 그래프 깊이우선탐색\n");
						printf("2.G2 그래프 깊이우선탐색\n");
						printf("3.G3 그래프 깊이우선탐색\n");
						printf("번호를 입력하세요: ");
						scanf("%d", &x);

						if (x == 0) {
							break;
						}
						else if (x == 1) {
							int t;
							printf("\n정점 입력 : ");
							scanf("%d", &t);

							dfs_mat(g1, t);
							printf("\n");
							reset_arr(&visited1, g1->n);
						}
						else if (x == 2) {
							int t;
							printf("\n정점 입력: ");
							scanf("%d", &t);

							dfs_list(g2, t,2);
							printf("\n");
							for (int i = 1; i < g2->n; i++) {
								if (!visited2[i]) {
									printf("\n연결되어있지 않습니다.\n\n");
									dfs_list(g2, i, 2);
								}
							}
							reset_arr(&visited2, g2->n);
						}
						else if (x == 3) {
							int t;
							printf("\n정점 입력: ");
							scanf("%d", &t);

							dfs_list(g3, t,3);
							printf("\n");
							reset_arr(&visited3, g3->n);
						}

					}
				}
			}

		}
		}
	}
	return 0;
}