#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int cnt = 1;
int Partition1(int arr[], int left, int right) {
	int p = right; // �ǹ��� ��ġ�� ���������� ����
	int l = left;
	int r = right;
	int temp = 0;

	printf("%d�ܰ� pivot -> %d\n", cnt++, arr[p]);
	while (l < r) { // �����Ǳ� ������ �ݺ�
		while (l < r && arr[l] < arr[p]) { // �ǹ����� �������� ã��
			l++; // ���������� �̵�
		}
		while (l < r && arr[r] >= arr[p]) { // �ǹ����� ū ���� ã��
			r--; // �������� �̵�
		}

		if (l < r) { // �������� ���� ���¸� ����
			temp = arr[l];
			arr[l] = arr[r];
			arr[r] = temp;
		}
	}
	temp = arr[p]; // r�� ���ҿ� �ǹ� ���� ��ȯ
	arr[p] = arr[r];
	arr[r] = temp;
	for (int i = 0; i < right+1; i++) {
		if (i == left)
			printf("[ %d ", arr[i]);
		else if (i == right)
			printf(" %d ] ", arr[i]);
		else
			printf("%d ", arr[i]);
	}printf("\n\n");

	return r; // ��ȯ�� r�� �ڸ��� ��ȯ
}

int Partition2(int arr[], int left, int right) {
	int p = left; // �ǹ��� ��ġ�� ó������ ����
	int l = p + 1;
	int r = right;
	int temp = 0;

	printf("%d�ܰ� pivot -> %d\n", cnt++, arr[p]);
	while (l <= r) {
		while (l <= right && arr[l] < arr[p]) {
			l++;
		}
		while (r > left && arr[r] >= arr[p]) {
			r--;
		}

		if (l < r) {
			temp = arr[l];
			arr[l] = arr[r];
			arr[r] = temp;
		}
	}
	temp = arr[p];
	arr[p] = arr[r];
	arr[r] = temp;

	for (int i = 0; i < right + 1; i++) {
		if (i == left)
			printf("[ %d ", arr[i]);
		else if (i == right)
			printf(" %d ] ", arr[i]);
		else
			printf("%d ", arr[i]);
	}printf("\n\n");
	return r;
}

int Partition3(int arr[], int left, int right) {
	int Pivot = arr[left];
	int Left_Mark = left + 1;
	int Right_Mark = right;
	int temp = 0;

	printf("%d�ܰ� pivot -> %d\n", cnt++, Pivot);
	while (Left_Mark <= Right_Mark) {
		while (arr[Left_Mark] <= Pivot) {
			Left_Mark++;
		}
		while (arr[Right_Mark] > Pivot) {
			Right_Mark--;
		}

		if (Left_Mark < Right_Mark) {
			temp = arr[Left_Mark];
			arr[Left_Mark] = arr[Right_Mark];
			arr[Right_Mark] = temp;
		}
	}
	temp = arr[left];
	arr[left] = arr[Right_Mark];
	arr[Right_Mark] = temp;

	for (int i = 0; i < right + 1; i++) {
		if (i == left)
			printf("[ %d ", arr[i]);
		else if (i == right)
			printf(" %d ] ", arr[i]);
		else
			printf("%d ", arr[i]);
	}printf("\n\n");

	return Right_Mark;
}

void QuickSort(int arr[], int left, int right, int n) {
	if (n == 1) {
		if (left <= right) {
			int pivot = Partition1(arr, left, right);
			QuickSort(arr, left, pivot - 1, 1);
			QuickSort(arr, pivot + 1, right, 1);
		}
	}
	if (n == 2) {
		if (left <= right) {
			int pivot = Partition2(arr, left, right);
			QuickSort(arr, left, pivot - 1, 2);
			QuickSort(arr, pivot + 1, right, 2);
		}
	}
	if (n == 3) {
		if (left <= right) {
			int pivot = Partition3(arr, left, right);
			QuickSort(arr, left, pivot - 1, 3);
			QuickSort(arr, pivot + 1, right, 3);
		}
	}
	
}

void menu() {
	printf("\n0.����\n");
	printf("1.partition1\n");
	printf("2.partition2\n");
	printf("3.partition3\n");
	printf("��ȣ�� �Է��ϼ���: ");
}

int main(void) {
	int n;

	while (1) {
		menu();
		scanf("%d", &n);

		switch (n) {
		case 1: {
			int num;
			printf("�迭�� ũ�� �Է�: ");
			scanf("%d", &num);

			int* arr = (int*)malloc(sizeof(int) * num);

			printf("\n====================�迭 ���====================\n");
			for (int i = 0; i < num; i++) {
				arr[i] = rand() % 50 + 1;
				printf("%d ", arr[i]);
			}printf("\n\n");

			QuickSort(arr, 0, num - 1, 1);

			printf("\n====================���ĵ� �迭 ���====================\n");
			for (int i = 0; i < num; i++) {
				printf("%d ", arr[i]);
			}printf("\n");
			cnt = 1;
			break;
		}
		case 2: {
			int num;
			printf("�迭�� ũ�� �Է�: ");
			scanf("%d", &num);

			int* arr = (int*)malloc(sizeof(int) * num);

			printf("\n====================�迭 ���====================\n");
			for (int i = 0; i < num; i++) {
				arr[i] = rand() % 50 + 1;
				printf("%d ", arr[i]);
			}printf("\n\n");

			QuickSort(arr, 0, num - 1, 2);

			printf("\n====================���ĵ� �迭 ���====================\n");
			for (int i = 0; i < num; i++) {
				printf("%d ", arr[i]);
			}printf("\n");
			cnt = 1;
			break;
		}
		case 3: {
			int num;
			printf("�迭�� ũ�� �Է�: ");
			scanf("%d", &num);

			int* arr = (int*)malloc(sizeof(int) * num);

			printf("\n====================�迭 ���====================\n");
			for (int i = 0; i < num; i++) {
				arr[i] = rand() % 50 + 1;
				printf("%d ", arr[i]);
			}printf("\n\n");

			QuickSort(arr, 0, num - 1, 3);

			printf("\n====================���ĵ� �迭 ���====================\n");
			for (int i = 0; i < num; i++) {
				printf("%d ", arr[i]);
			}printf("\n");
			cnt = 1;
			break;
		}
		}
	}
}