#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_SIZE 10

void swap(int* a, int* b) { // 값 바꿈
	int temp = *a;
	*a = *b;
	*b = temp;
}

typedef struct Queue { // 큐 생성
	int heap[MAX_SIZE];
	int count;
}Queue;

void print_Queue(Queue* root) { // 큐 출력
	printf("\n------------------------------------------\n");
	for (int i = 0; i < root->count; i++) {
		printf("%d ", root->heap[i]);
	}
	printf("\n------------------------------------------\n");
}

void push(Queue* root, int data) { // 큐 원소 삽입
	if (root->count >= MAX_SIZE) return; // 노드의 갯수가 사이즈보다 크면 중지

	root->heap[root->count] = data;

	int idx = root->count; // data 위치
	int parent = (root->count - 1); // data의 부모위치

	while (idx > 0 && root->heap[idx] > root->heap[parent]) { // 상향식으로 최상단까지 data값 힙 구성 부모노드의 data값보다 현재 값이 더 크면 실행
		swap(&root->heap[idx], &root->heap[parent]); // 부모값과 현재값 스왑
		idx = parent; // 상향식으로 부모노드와 비교를 위해 부모값은 현재
		parent = (parent - 1); // 부모값의 위치도 다음 검사할 부모값 위치로 저장
	}
	root->count++;
}

int pop(Queue* root) {
	if (root->count <= 0) { // 삭제할 값이 없을경우
		printf("\n삭제할 원소가 없습니다.\n");
		return -1;
	}

	int res = root->heap[0]; // 반환할 최상단 루트값
	root->count--;

	root->heap[0] = root->heap[root->count]; // 최상단 루트에 마지막값을 넣어 하향식으로 최대힙 구성

	int idx = 0, left = 1, right = 2; 
	int target = idx;

	while (left < root->count) {
		if (root->heap[target] < root->heap[left]) { // 현재 부모값 보다 왼쪽 자식값이 더 크면 자식값 참조
			target = left;
		}
		if (root->heap[target] < root->heap[right] && right < root->count) { // 현재 부모값 보다 오른쪽 자식값이 더 크고 오른쪽 자식 값보다 현재 값이 더 클때
			target = right;
		}

		if (target == idx) break; // 더 이상 내려가지 않아도 될 때 종료
		else {
			swap(&root->heap[idx], &root->heap[target]); // 현재값과 자식값의 자리 바꿔줌
			idx = target; // 다음 검사대상을 idx에 저장 후 하향식으로 내려가면서 검사 반복
			left = idx * 2 + 1;
			right = idx * 2 + 2;
		}
	}
	return res;
}

void heapify(int arr[], int k, int n) {
	int left = k * 2; // 왼쪽 자식 인덱스
	int right = k * 2 + 1; // 오른쪽 자식 인덱스
	int big = 0;

	if (right <= n) { // 오른쪽 자식 인덱스가 배열의 크기보다 작을시 자식이 있다는 뜻
		if (arr[left] < arr[right]) { // max heap을 하기 위해 큰값 대입
			big = right;
		}
		else
			big = left;
	}
	else if (left <= n) {
		big = left;
	}
	else return; // 자식이 없을경우 리턴

	int temp = 0;
	if (arr[big] > arr[k]) { // 부모 인덱스보다 자식인덱스가 크면 원소 교환
		printf("\n원소 교환 [%d] <-> [%d]\n\n", arr[big], arr[k]);

		temp = arr[k];
		arr[k] = arr[big];
		arr[big] = temp;

		printf("\n----------초기힙 상태----------\n");
		for (int i = 1; i <= n; i++) {
			printf("%d ", arr[i]);
		}printf("\n");

		heapify(arr, big, n);
	}
}

void buildHeap(int arr[], int n) {

	for (int i = n / 2; i >= 1; i--) {
		heapify(arr, i, n);
	}
}

int* heapSort(int arr[], int n) {
	int* a = (int*)malloc(sizeof(int) * (n + 1));
	int idx = 1;
	int temp = 0;

	buildHeap(arr, n);
	for (int i = n; i >= 2; i--) {
		temp = arr[1];
		a[idx++] = temp;
		arr[1] = arr[i];
		arr[i] = temp;

		printf("\n----------힙 크기 줄어든 배열 출력----------\n");
		for (int j = 1; j <= i - 1; j++) {
			printf("%d ", arr[j]);
		}printf("\n");

		heapify(arr, 1, i - 1);
	}
	a[idx] = arr[1];
	return a;
}

void radix_Sort(int arr[], int n) {
	int* arr2 = (int*)malloc(sizeof(int) * n);
	int value = 0;
	int cnt = 1;
	int result = 0;

	for (int i = 0; i < n; i++) {
		if (arr[i] > value)
			value = arr[i];
	}

	while ((value / cnt) > 0) {
		int bucket[8] = { 0 };

		for (int i = 0; i < n; i++) {
			result = (arr[i] / cnt) % 10;
			bucket[result]++;
		}
		
		for (int i = 1; i < 8; i++) {
			bucket[i] += bucket[i - 1];
		}
		  
		for (int i = n - 1; i >= 0; i--) {
			result = arr[i] / cnt % 10;
			arr2[--bucket[result]] = arr[i];
		}

		for (int i = 0; i < n; i++) 
			arr[i] = arr2[i];

		printf("\n%d의 자리 >>>>>> \n",cnt);
		for (int i = 0; i < n; i++) {
			printf("%d ", arr[i]);
		}printf("\n");
		cnt *= 10;
	}
}

void menu() {
	printf("\n0.종료\n");
	printf("1.힙 정렬\n");
	printf("2.우선순위 큐\n");
	printf("3.기수 정렬\n");
	printf("번호를 입력하세요 :");
}

int main(void) {
	int num;

	while (1) {
		menu();
		scanf("%d", &num);

		switch (num) {
		case 0: {
			printf("\n프로그램을 종료합니다.\n");
			return 0;
		}
		case 1: {
			int n;
			printf("N: ");
			scanf("%d", &n);
			n += 1;
			int* arr = (int*)malloc(sizeof(int) * n);
			printf("\n------------------배열 출력--------------------\n");
			for (int i = 1; i < n; i++) {
				arr[i] = rand() % 50 + 1;
				printf("%d ", arr[i]);
			}printf("\n");

			arr = heapSort(arr, n - 1);
			printf("\n------------------변경된 배열 출력--------------------\n");
			for (int i = n-1; i >= 1; i--) {
				printf("%d ", arr[i]);
			}printf("\n");

			break;
		}
		case 2: {
			int menu, n, num;
			Queue root;
			root.count = 0;

			while (1) {
				printf("\n1.삽입\n");
				printf("2.삭제\n");
				scanf("%d", &menu);

				if (menu == 1) {
					printf("\n삽입할 정수 : ");
					scanf("%d", &num);
					push(&root, num);
					print_Queue(&root);
				}
				else if (menu == 2) {
					int data = pop(&root);
					if(data >=0)
						printf("최대값: %d\n", data);
					print_Queue(&root);
				}
				else break;
			}
			break;
		}
		case 3: {
			int n, cnt=1, a=0, number=0;
			printf("N: ");
			scanf("%d", &n);

			int* arr = (int*)malloc(sizeof(int) * n);

			for (int i = 0; i < n; i++) {
				number = rand() % (99998 - 10000 + 1) + 10000;
				while(a < 5) {
					if ((number / cnt) % 10 < 8) {
						cnt *= 10;
						a++;
					}
					else
						break;
				}
				
				if (a == 5) {
					arr[i] = number;
				}
				else {
					i = i - 1;
				}
				cnt = 1;
				a = 0;
			}
			printf("\n----------------배열 출력---------------------\n");
			for (int i = 0; i < n; i++) {
				printf("%d ", arr[i]);
			}printf("\n");
			
			radix_Sort(arr, n);

			printf("\n------------------변경된 배열 출력--------------------\n");
			for (int i = 0; i < n; i++) {
				printf("%d ", arr[i]);
			}printf("\n");

			break;
		}
		}
	}
	return 0;
}