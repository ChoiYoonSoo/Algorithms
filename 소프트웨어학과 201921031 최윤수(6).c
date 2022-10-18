#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_SIZE 10

void swap(int* a, int* b) { // �� �ٲ�
	int temp = *a;
	*a = *b;
	*b = temp;
}

typedef struct Queue { // ť ����
	int heap[MAX_SIZE];
	int count;
}Queue;

void print_Queue(Queue* root) { // ť ���
	printf("\n------------------------------------------\n");
	for (int i = 0; i < root->count; i++) {
		printf("%d ", root->heap[i]);
	}
	printf("\n------------------------------------------\n");
}

void push(Queue* root, int data) { // ť ���� ����
	if (root->count >= MAX_SIZE) return; // ����� ������ ������� ũ�� ����

	root->heap[root->count] = data;

	int idx = root->count; // data ��ġ
	int parent = (root->count - 1); // data�� �θ���ġ

	while (idx > 0 && root->heap[idx] > root->heap[parent]) { // ��������� �ֻ�ܱ��� data�� �� ���� �θ����� data������ ���� ���� �� ũ�� ����
		swap(&root->heap[idx], &root->heap[parent]); // �θ𰪰� ���簪 ����
		idx = parent; // ��������� �θ���� �񱳸� ���� �θ��� ����
		parent = (parent - 1); // �θ��� ��ġ�� ���� �˻��� �θ� ��ġ�� ����
	}
	root->count++;
}

int pop(Queue* root) {
	if (root->count <= 0) { // ������ ���� �������
		printf("\n������ ���Ұ� �����ϴ�.\n");
		return -1;
	}

	int res = root->heap[0]; // ��ȯ�� �ֻ�� ��Ʈ��
	root->count--;

	root->heap[0] = root->heap[root->count]; // �ֻ�� ��Ʈ�� ���������� �־� ��������� �ִ��� ����

	int idx = 0, left = 1, right = 2; 
	int target = idx;

	while (left < root->count) {
		if (root->heap[target] < root->heap[left]) { // ���� �θ� ���� ���� �ڽİ��� �� ũ�� �ڽİ� ����
			target = left;
		}
		if (root->heap[target] < root->heap[right] && right < root->count) { // ���� �θ� ���� ������ �ڽİ��� �� ũ�� ������ �ڽ� ������ ���� ���� �� Ŭ��
			target = right;
		}

		if (target == idx) break; // �� �̻� �������� �ʾƵ� �� �� ����
		else {
			swap(&root->heap[idx], &root->heap[target]); // ���簪�� �ڽİ��� �ڸ� �ٲ���
			idx = target; // ���� �˻����� idx�� ���� �� ��������� �������鼭 �˻� �ݺ�
			left = idx * 2 + 1;
			right = idx * 2 + 2;
		}
	}
	return res;
}

void heapify(int arr[], int k, int n) {
	int left = k * 2; // ���� �ڽ� �ε���
	int right = k * 2 + 1; // ������ �ڽ� �ε���
	int big = 0;

	if (right <= n) { // ������ �ڽ� �ε����� �迭�� ũ�⺸�� ������ �ڽ��� �ִٴ� ��
		if (arr[left] < arr[right]) { // max heap�� �ϱ� ���� ū�� ����
			big = right;
		}
		else
			big = left;
	}
	else if (left <= n) {
		big = left;
	}
	else return; // �ڽ��� ������� ����

	int temp = 0;
	if (arr[big] > arr[k]) { // �θ� �ε������� �ڽ��ε����� ũ�� ���� ��ȯ
		printf("\n���� ��ȯ [%d] <-> [%d]\n\n", arr[big], arr[k]);

		temp = arr[k];
		arr[k] = arr[big];
		arr[big] = temp;

		printf("\n----------�ʱ��� ����----------\n");
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

		printf("\n----------�� ũ�� �پ�� �迭 ���----------\n");
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

		printf("\n%d�� �ڸ� >>>>>> \n",cnt);
		for (int i = 0; i < n; i++) {
			printf("%d ", arr[i]);
		}printf("\n");
		cnt *= 10;
	}
}

void menu() {
	printf("\n0.����\n");
	printf("1.�� ����\n");
	printf("2.�켱���� ť\n");
	printf("3.��� ����\n");
	printf("��ȣ�� �Է��ϼ��� :");
}

int main(void) {
	int num;

	while (1) {
		menu();
		scanf("%d", &num);

		switch (num) {
		case 0: {
			printf("\n���α׷��� �����մϴ�.\n");
			return 0;
		}
		case 1: {
			int n;
			printf("N: ");
			scanf("%d", &n);
			n += 1;
			int* arr = (int*)malloc(sizeof(int) * n);
			printf("\n------------------�迭 ���--------------------\n");
			for (int i = 1; i < n; i++) {
				arr[i] = rand() % 50 + 1;
				printf("%d ", arr[i]);
			}printf("\n");

			arr = heapSort(arr, n - 1);
			printf("\n------------------����� �迭 ���--------------------\n");
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
				printf("\n1.����\n");
				printf("2.����\n");
				scanf("%d", &menu);

				if (menu == 1) {
					printf("\n������ ���� : ");
					scanf("%d", &num);
					push(&root, num);
					print_Queue(&root);
				}
				else if (menu == 2) {
					int data = pop(&root);
					if(data >=0)
						printf("�ִ밪: %d\n", data);
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
			printf("\n----------------�迭 ���---------------------\n");
			for (int i = 0; i < n; i++) {
				printf("%d ", arr[i]);
			}printf("\n");
			
			radix_Sort(arr, n);

			printf("\n------------------����� �迭 ���--------------------\n");
			for (int i = 0; i < n; i++) {
				printf("%d ", arr[i]);
			}printf("\n");

			break;
		}
		}
	}
	return 0;
}