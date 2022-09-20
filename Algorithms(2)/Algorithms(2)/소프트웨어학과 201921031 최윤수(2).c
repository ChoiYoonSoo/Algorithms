#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
	int data;
	struct ListNode* link;
}ListNode;

ListNode* insert(ListNode* head, int value) {
	ListNode* p = malloc(sizeof(ListNode));
	if (head == NULL) {
		p->data = value;
		p->link = head;
		head = p;
		return head;
	}
}

void print_list(ListNode* head) {
	for (ListNode* p = head; p != NULL; p = p->link)
		printf("%d ", p->data);
	printf("\n");
}

ListNode* add_list(ListNode* head1, ListNode* head2) {
	ListNode* tmp = NULL;
	ListNode* head;

	if (head1->data < head2->data) {
		tmp = head1;
		head1 = head1->link;
		head = tmp;
	}
	else {
		tmp = head2;
		head2 = head2->link;
		head = tmp;
	}

	while (head1->link != NULL && head2->link != NULL) {
		if (head1->data < head2->data) {
			tmp->link = head1;
			tmp = tmp->link;
			head1 = head1->link;
		}
		else {
			tmp->link = head2;
			tmp = tmp->link;
			head2 = head2->link;
		}
	}
	if (head1->link == NULL)
		tmp->link = head2;

	if(head2->link == NULL)
		tmp->link = head1;

	return head;
}

double w_aver = 0.0;
double b_aver = 0.0;
int w = 0, b = 0;
void binary_search(int arr[],int len, int key) {
	int first, last;
	int mid;
	first = 0;
	last = len - 1;

	int cnt = 0;
	int x = 0;

	while (first <= last) {
		mid = (first + last) / 2;
		if (key == arr[mid]) {
			cnt++; x++;
			printf("성공! 키값 %d을(를) 찾았습니다! \n",key);
			printf("총 비교 횟수 : %d\n\n", cnt);
			if (b < cnt) {
				b = cnt;
			}
			b_aver += cnt;
			break;
		}
		else if (key < arr[mid]) {
			printf("현재 검색 인덱스: %d\n",mid);
			printf("비교 값 : %d <-> %d\n", key, arr[mid]);
			printf("%d가 %d보다 작음\n왼쪽으로 이동\n\n", key, arr[mid]);
			cnt++;
			last = mid - 1;
		}
		else if (key > arr[mid]) {
			printf("현재 검색 인덱스 : %d\n",mid);
			printf("비교 값 : %d <-> %d\n", key, arr[mid]);
			printf("%d가 %d보다 큼\n오른쪽으로 이동\n\n", key, arr[mid]);
			cnt++;
			first = mid + 1;
		}
	}
	if (x == 0) {
		printf("실패! 키값 %d을(를) 찾지 못했습니다.\n", key);
		printf("총 비교 횟수 : %d\n\n", cnt);
		if (w < cnt) {
			w = cnt;
		}
		w_aver += cnt;
	}
}

void add_arr(int* arr1, int* arr2) {
	int arrlen1 = 3;
	int arrlen2 = 5;
	int arr[10] = { 0, };
	int i, j, k;
	i = j = k = 0;

	while (i < arrlen1 && j < arrlen2) {
		if (arr1[i] < arr2[j]) {
			arr[k] = arr1[i];
			i++; k++;
		}
		else if (arr1[i] > arr2[j]) {
			arr[k] = arr2[j];
			j++; k++;
		}
	}

	while (i < arrlen1) {
		arr[k] = arr1[i];
		i++; k++;
	}

	while (j < arrlen2) {
		arr[k] = arr2[j];
		k++; j++;
	}

	printf("\n병합된 정렬 출력\n");
	for (int i = 0; i < 8; i++) {
		printf("%d ", arr[i]);
	}printf("\n");
}

int cnt = 1;
void hanoi(int N, char A, char B, char C) {
	if (N == 1) {
		printf("<1> 원판을 <%c>에서 <%c>으로 옮긴다.\n", A, C); cnt++;
	}
	else {
		hanoi(N - 1, A, C, B);
		printf("<%d> 원판을 <%c>에서 <%c>으로 옮긴다.\n", N, A, C); cnt++;
		hanoi(N - 1, B, A, C);
	}
}

void menu() {
	printf("\n=====번호입력=====\n");
	printf("1.이진검색\n");
	printf("2.배열/연결리스트 정렬\n");
	printf("3.하노이탑\n");
}

int main(void) {
	int n;

	while (1) {
		menu();
		scanf("%d", &n);

		switch (n) {
		case 1: {
			int a, key;
			int n = 0;
			int arr1[10] = { 1,4,6,9,11,13,16,20,25,30 };
			int arr2[20] = { 1,6,9,11,13,17,19,21,24,28,30,33,35,38,40,60,63,67,70,80 };
			int arr3[30] = { 1,6,9,11,13,17,19,21,24,28,30,33,35,38,40,60,63,67,70,80,91,94,96,101,105,109,111,115,120,130 };
			printf("1~3개 배열중 선택: ");
			scanf("%d", &a);

			if (a == 1) n = 10;
			else if (a == 2) n = 20;
			else n = 30;

			for (int i = 0; i < n; i++) {
				printf("찾을 키 값: ");
				scanf("%d", &key);
				binary_search(&arr1, n, key);
			}
			printf("성공 평균 비교 횟수: %f\n", b_aver / n);
			printf("최악의 경우 : %d\n", b);
			b_aver = 0.0;
			b = 0;
			printf("실패 평균 비교 횟수: %f\n", w_aver / n);
			printf("최악의 경우 : %d\n", w);
			w_aver = 0.0;
			w = 0;

			break;
		}
		case 2: {
			int a;
			printf("1.배열\n");
			printf("2.연결리스트\n");
			scanf("%d", &a);
			if (a == 1) {
				int arr1[3] = { 5,7,24 };
				int arr2[5] = { 19,45,61,79,92 };

				printf("1번째 배열 출력\n");
				for (int i = 0; i < 3; i++) {
					printf("%d ", arr1[i]);
				}

				printf("\n2번째 배열 출력\n");
				for (int i = 0; i < 3; i++) {
					printf("%d ", arr2[i]);
				}
				add_arr(&arr1, &arr2);
			}
			else if (a == 2) {
				ListNode h1 = { 12, NULL };
				ListNode h2 = { 9, &h1 };
				ListNode h3 = { 5, &h2 };
				ListNode* head1 = &h3;

				ListNode h4 = { 20,NULL };
				ListNode h5 = { 17,&h4 };
				ListNode h6 = { 7,&h5 };
				ListNode h7 = { 6, &h6 };
				ListNode h8 = { 1, &h7 };
				ListNode *head2 = &h7;

				int n;

				printf("정렬된 첫 번째 리스트 출력\n");
				print_list(head1);
				printf("정렬된 두 번째 리스트 출력\n");
				print_list(head2);

				printf("병합된 리스트 출력\n");
				ListNode* head3 = add_list(head1, head2);
				print_list(head3);
				
			}
			break;
		}
		case 3: {
			int n;
			printf("원판 갯수 입력 :");
			scanf("%d", &n);
			hanoi(n, 'A', 'B', 'C');
			printf("총 %d번 이동\n", cnt - 1);
			cnt = 1;
		}
		}
	}

	
}