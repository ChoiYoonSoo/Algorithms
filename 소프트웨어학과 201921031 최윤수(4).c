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

	while (i <= mid && j <= right) { // ���� ���ĵ� �迭 ����
		if (A[i] <= A[j]) {
			temp[t++] = A[i++];
		}
		else
			temp[t++] = A[j++];
	}

	// ���� �ִ� ���� ����
	while (i <= mid)
		temp[t++] = A[i++];
	while (j <= right)
		temp[t++] = A[j++];

	int idx = left;
	int idx2 = 0;
	// �迭 temp�� �ִ� ���� A�� �纹��
	while (idx <= right)
		A[idx++] = temp[idx2++];

	printf("���� ���� >> ");
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
		mergeSort(A, left, mid); // ���� �κ� ����
		mergeSort(A, mid + 1, right); // ���� �κ� ����
		merge(A, left, mid, right); // ���ĵ� 2���� �κ� �迭 ����
	}
}

void mergeSort2(int A[], int n)
{
	for (int size = 1; size <= n - 1; size = 2 * size){
		for (int left = 0; left < n - 1; left += 2 * size){  // ���� ũ���� ���� �ٸ� ���� �迭�� ������ ����
			int mid = min(left + size - 1, n - 1);   // ���� ���� �迭�� �� ��ġ
			int right = min(left + 2 * size - 1, n - 1);  // ������ �� ��ġ
			merge(A, left, mid, right);
		}
	}
}

void menu() {
	printf("\n0.����\n");
	printf("1.��������(���)\n");
	printf("2.��������(�ݺ�)\n");
	printf("��ȣ�� �Է��ϼ��� : ");
}

int main(void) {
	int n;

	while (1) {
		menu();
		scanf("%d", &n);

		switch (n) {
		case 0: {
			printf("���α׷��� �����մϴ�.\n");
			return 0;
		}
		case 1: {
			printf("�迭�� ũ�� �Է�: ");
			scanf("%d", &N);

			int* A = (int*)malloc(sizeof(int) * N);
			printf("\n������ ���� >> ");
			for (int i = 0; i < N; i++) {
				A[i] = rand() % 50 + 1;
				printf("%d ", A[i]);
			}printf("\n");

			printf("\n<<<<<<<<<<<<<<<<<<<<���� ���� ����>>>>>>>>>>>>>>>>>>>>\n\n");
			mergeSort(A, 0, N-1);
			break;
		}
		case 2: {
			printf("�迭�� ũ�� �Է�: ");
			scanf("%d", &N);

			int* A = (int*)malloc(sizeof(int) * N);
			printf("\n������ ���� >> ");
			for (int i = 0; i < N; i++) {
				A[i] = rand() % 50 + 1;
				printf("%d ", A[i]);
			}printf("\n");

			printf("\n<<<<<<<<<<<<<<<<<<<<���� ���� ����>>>>>>>>>>>>>>>>>>>>\n\n");
			mergeSort2(A, N);
			break;
		}
		}
	}
	return 0;
}