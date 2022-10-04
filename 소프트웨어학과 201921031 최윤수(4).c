#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int  N;
void merge(int A[], int left, int mid, int right) {
	int i = left;
	int j = mid + 1;
	int t = 0;
	int* temp = (int*)malloc(sizeof(int) * (right + 1));

	while (i <= mid && j <= right) { // 분할 정렬된 배열 병합
		if (A[i] <= A[j]) {
			temp[t++] = A[i++];
		}
		else
			temp[t++] = A[j++];
	}

	// 남아 있는 값들 복사
	while (i <= mid)
		temp[t++] = A[i++];
	while (j <= right)
		temp[t++] = A[j++];

	int idx = left;
	int idx2 = 0;
	// 배열 temp에 있는 값을 A로 재복사
	while (idx <= right)
		A[idx++] = temp[idx2++];

	printf("병합 정렬 >> ");
	for (int i = 0; i < N; i++) {
		if (i == left)
			printf("[%d ", A[i]);
		else if (i == right)
			printf(" %d]", A[i]);
		else
			printf("%d ", A[i]);
	}printf("\n");
}

void mergeSort(int A[], int left, int right) {
	int mid;

	if (left < right) {
		mid = (left + right) / 2;
		mergeSort(A, left, mid); // 앞쪽 부분 정렬
		mergeSort(A, mid + 1, right); // 뒤쪽 부분 정렬
		merge(A, left, mid, right); // 정렬된 2개의 부분 배열 병합
	}
}

void mergeSort2(int A[], int n)
{
	for (int size = 1; size <= n - 1; size = 2 * size){
		for (int left = 0; left < n - 1; left += 2 * size){  // 현재 크기의 서로 다른 하위 배열의 시작점 선택
			int mid = min(left + size - 1, n - 1);   // 왼쪽 하위 배열의 끝 위치
			int right = min(left + 2 * size - 1, n - 1);  // 오른쪽 끝 위치
			merge(A, left, mid, right);
		}
	}
}

void menu() {
	printf("\n0.종료\n");
	printf("1.병합정렬(재귀)\n");
	printf("2.병합정렬(반복)\n");
	printf("번호를 입력하세요 : ");
}

int main(void) {
	int n;

	while (1) {
		menu();
		scanf("%d", &n);

		switch (n) {
		case 0: {
			printf("프로그램을 종료합니다.\n");
			return 0;
		}
		case 1: {
			printf("배열의 크기 입력: ");
			scanf("%d", &N);

			int* A = (int*)malloc(sizeof(int) * N);
			printf("\n정렬할 원소 >> ");
			for (int i = 0; i < N; i++) {
				A[i] = rand() % 50 + 1;
				printf("%d ", A[i]);
			}printf("\n");

			printf("\n<<<<<<<<<<<<<<<<<<<<병합 정렬 수행>>>>>>>>>>>>>>>>>>>>\n\n");
			mergeSort(A, 0, N-1);
			break;
		}
		case 2: {
			printf("배열의 크기 입력: ");
			scanf("%d", &N);

			int* A = (int*)malloc(sizeof(int) * N);
			printf("\n정렬할 원소 >> ");
			for (int i = 0; i < N; i++) {
				A[i] = rand() % 50 + 1;
				printf("%d ", A[i]);
			}printf("\n");

			printf("\n<<<<<<<<<<<<<<<<<<<<병합 정렬 수행>>>>>>>>>>>>>>>>>>>>\n\n");
			mergeSort2(A, N);
			break;
		}
		}
	}
	return 0;
}