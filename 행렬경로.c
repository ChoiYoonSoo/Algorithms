#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


int g_Path[4][4] = {
	{6,7,12,5},
	{5,3,11,18},
	{7,17,3,3},
	{8,10,14,9} };

int g_DT[4][4];

int max_path(int a, int b) {
	return a > b ? a : b;
}

int dp(int** arr, int** c, int n, int* cnt1) {
	c[0][0] = arr[0][0]; // ����� ù ��° ���̺� ù ��° ���� ��´�
	(*cnt1)++;

	for (int i = 1; i < n; i++) {
		c[0][i] = arr[0][i] + c[0][i - 1]; // 1���� �� ����� ���� ������ �� ���̺� ��´�

		(*cnt1)++;
	}

	for (int i = 1; i < n; i++) {
		c[i][0] = arr[i][0] + c[i - 1][0]; // 1���� �� ������ ���� ������ �� ���̺� ��´�
		(*cnt1)++;
	}

	for (int i = 1; i < n; i++) {
		for (int j = 1; j < n; j++) {
			c[i][j] = max_path(arr[i][j] + c[i - 1][j], arr[i][j] + c[i][j - 1]);
			// ��� �Ǿ��ִ� ���������� �̿��Ͽ� ���� ���� ���� -1���̳� -1�� �߿��� �� ū���� �������̺� ��´�
			(*cnt1)++;
		}
	}

	return c[n - 1][n - 1]; // �ְ�����ȯ
}

int loop(int** arr, int** c, int* cnt, int i, int j) { // memoization ���
	// �޶��� ���� ��ȯ ���� ���̺� �迭�� ��´ٴ� ���̴�.
	int a, b;
	if (c[i][j] != -1) { // ���̺� �迭�� ���� ����ִٸ�
		return c[i][j]; // �ٷ� �� ��� ��ȯ ī��Ʈ x
	}

	(*cnt)++;
	if (i == 0 && j == 0) {
		return c[i][j] = arr[i][j];
	}
	else if (i == 0) {
		return c[i][j] = loop(arr, c, cnt, i, j - 1) + arr[i][j];
	}
	else if (j == 0) {
		return c[i][j] = loop(arr, c, cnt, i-1, j) + arr[i][j];
	}
	else {
		return c[i][j] = max_path(loop(arr, c, cnt, i, j - 1) + arr[i][j], loop(arr, c, cnt, i - 1, j) + arr[i][j]);
	}
}

int main(void){
	int n, cnt1 = 0;
	scanf("%d", &n); // ����� ũ�� n*n

	int** arr = (int**)malloc(sizeof(int*) * n); // ����� ũ�⸸ŭ ����

	for (int i = 0; i < n; i++) {
		arr[i] = (int*)malloc(sizeof(int) * n);
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &arr[i][j]); // ��Ŀ� ���� �Է�
		}
	}

	int** c = (int**)malloc(sizeof(int*) * n); // ����� ���̺��� �Ǿ��� ����� ����

	for (int i = 0; i < n; i++) {
		c[i] = (int*)malloc(sizeof(int) * n);
	}

	printf("�ְ���: %d\n\n", dp(arr, c, n, &cnt1));
	printf("����Ƚ��: %d\n", cnt1);
	return 0;
}