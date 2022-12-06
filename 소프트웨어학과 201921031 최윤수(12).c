#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define max(a,b)  (((a) > (b)) ? (a) : (b))

//1. ������ ����� ä���� 5*5 ����� �����ϰ�, ��� ��ι����� �������α׷������� �ϼ��Ͻÿ�.
int arr[][6] = {
	{0, 0, 0, 0, 0, 0},
	{0, 6, 7, 12, 5, 1},
	{0, 5, 3, 11, 18, 9},
	{0, 7, 17, 3, 3, 11},
	{0, 8, 10, 14, 9, 19},
	{0, 14, 22, 2, 7, 5}
};
int c[6][6];

int max_path(int a, int b) {
	if (a > b)
		return a;
	else
		return b;
}

int dp(int n) {

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			c[i][j] = max(c[i - 1][j]+arr[i][j], c[i][j-1]+arr[i][j]);
		}
	}
	return c[n][n];
	
}

//2. �� ���� 1�� ���ȣ��� �����ؼ� ���� Ȯ���ϰ�, ȣ���� ��� �� �� �߻��ߴ����� Ȯ���Ͻÿ�.
int loop(int* cnt, int i, int j) {
	(*cnt)++;
	if (i == 0 || j == 0) {
		return 0;
	}
	else {
		return (arr[i][j] + max(loop(cnt,i - 1, j), loop(cnt,i, j - 1)));
	}
}

//3. ���� 290�� �������� 06�� �������α׷��� ������� �ϼ��Ͻÿ�.
int max_Path(int a, int b, int c) {
	if (a > b) {
		if (a > c)
			return a;
		else
			return c;
	}
	else {
		if (b > c)
			return b;
		else
			return c;
	}
}

void init_table(int a[][6]) { // ���̺� �ʱ�ȭ �Լ�
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 6; j++)
			a[i][j] = 0;
}

void print_table(int a[][6]) { // ��� ��� �Լ�
	printf("\n���: \n");
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++)
			printf("%3d ", a[i][j]);
		printf("\n");
	}
}

int matrix_Path(int n) {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			c[i][j] = max_Path(c[i - 1][j] + arr[i][j],c[i-1][j-1] + arr[i][j], c[i][j - 1] + arr[i][j]);
		}
	}
	return c[n][n];
}

//4. 3*n ���̺��� ������ ������ ������ ������ ä���, �� ���� ������ ���� ���α׷������� �ϼ��Ͻÿ�.
void pebbleDP(int** arr, int** peb, int n) {
	for (int i = 0; i < 4; i++) {
		peb[i][0] = arr[i][0];
	}

	for (int i = 1; i < n; i++) {
		for (int p = 0; p < 4; p++) {
			if (p == 0) peb[p][i] = arr[p][i] + max(peb[1][i - 1], peb[2][i - 1]);
			else if (p == 1) peb[p][i] = arr[p][i] + max_Path(peb[0][i - 1], peb[2][i - 1], peb[3][i - 1]);
			else if (p == 2) peb[p][i] = arr[p][i] + max(peb[0][i - 1], peb[1][i - 1]);
			else peb[p][i] = arr[0][i] + arr[2][i] + peb[1][i-1];
		}
	}

	printf("\n---------���̺�----------\n");
	for (int i = 0; i < 4; i++) {
		printf("\n");
		for (int j = 0; j < n; j++) {
			printf("%-4d ", peb[i][j]);
		}
	}printf("\n");
}

//5. ���� 294�� �������� 17���� �������α׷��� ������� �ϼ��Ͻÿ�.
int domino(int n) {
	int* d = (int*)malloc(sizeof(int) * n);
	d[0] = 1;
	d[1] = 1;

	for (int i = 2; i <= n; i++) {
		d[i] = d[i - 1] + d[i - 2];
	}
	return d[n];
}

/*
6. N�� ����� �ö󰡷��� �Ѵ�. �Ź� ����� 1ĭ �Ǵ� 2ĭ�� �ö� �� �ִ�.

�� ������ �ö� �� �ִ� ����� ���� �� ������ ���ϴ� ���α׷��� ���� ���α׷��� ������� �ϼ��Ͻÿ�.
*/
int upstair(int n) {
	int* stairs = (int*)malloc(sizeof(int) * n);
	stairs[0] = 0;
	stairs[1] = 1;
	stairs[2] = 1;
	stairs[3] = 2;

	for (int i = 4; i <= n; i++) {
		stairs[i] = stairs[i - 1] + stairs[i - 3];
	}
	return stairs[n];
}

/*
7. ��� ��ü������ 80��¥��, 50��¥��, 10��¥�� ��ǥ�� �ִ�.

(1) Ư�� �ݾ��� �������� ���� ����ϴ� �ּ� ������ ��ǥ ������ �������α׷������� ���Ͻÿ�. (10, 20, 30, 40, 50 �� 300���� ����� �ּ� ��ǥ ������ ���ϴ� ǥ�� �ϼ��Ͻÿ�).

���û�������, ������ �ذ� �� ��ǥ�� �� �徿 ����ϴ����� ����Ͻÿ�.

(2) ����, ��ü�� ������ �׸��� �˰����� �����Ѵٸ� � �������� ��ǥ���� �ް� �Ǵ���

����ϴ� ���α׷��� �ۼ��ϰ�, �� ����� ������ ������� (1)�� ���Ͻÿ�.
*/
int post[5][31];
int greedy[5][31];

void init_post(int a[][31]) {

	for (int i = 0; i < 31; i++)
		a[0][i] = 10 * i;

	for (int i = 0; i < 5; i++)
		a[i][0] = 0;

	for (int i = 1; i < 31; i++)
		a[4][i] = 9999;
}

int p[4] = { 0, 80, 50, 10 };
int minpost(int n) {

	int index = n / 10; //�ݾ��� �ε���

	for (int i = 1; i <= index; i++) {
		for (int j = 1; j <= 3; j++) {
			if (p[j] <= post[0][i] && post[4][i - (p[j] / 10)] + 1 < post[4][i]) {

				post[4][i] = post[4][i - (p[j] / 10)] + 1; //������

				post[3][i] = post[3][i - (p[j] / 10)]; //10��¥��
				post[2][i] = post[2][i - (p[j] / 10)]; //50��¥��
				post[1][i] = post[1][i - (p[j] / 10)]; //80��¥��
				post[j][i]++; //j��° ��ǥ �׸鰡 ����

				printf("-------------------------\n");
				printf("%d���� ������ : %d��\n80�� : %d��\n50�� : %d��\n10�� : %d��\n", post[0][i], post[4][i], post[1][i], post[2][i], post[3][i]);

			}

		}

	}
	return post[4][index];
}

int greedypost(int n) {

	int index = n / 10, value; //�ݾ��� �ε���

	for (int i = 1; i <= index; i++) {
		value = greedy[0][i];
		for (int j = 1; j <= 3; j++) {

			if (value / p[j] > 0) {

				greedy[j][i] = value / p[j];
				value = value % p[j];
			}

		}
		greedy[4][i] = greedy[1][i] + greedy[2][i] + greedy[3][i];

	}

	printf("\n-------------Greedy------------\n\n");
	printf("%d���� Greedy : %d��\n80�� : %d��\n50�� : %d��\n10�� : %d��\n", greedy[0][index], greedy[4][index], greedy[1][index], greedy[2][index], greedy[3][index]);
	return greedy[4][index];
}

void menu() {
	printf("\n0.����\n");
	printf("1.��� ��ι��� ����&���\n");
	printf("2.290�� 6�� ��� ��� ��������\n");
	printf("3.�� ���� ����\n");
	printf("4.���̳� ����\n");
	printf("5.��� �ö󰡱� ����\n");
	printf("6.��ǥ ����\n");
	printf("��ȣ�� �Է��ϼ���: ");
}

int main(void) {
	int n;

	while (1) {
		menu();
		scanf("%d", &n);

		switch (n) {

		case 0: {
			printf("\n\n���α׷��� �����մϴ�.\n");
			return 0;
		}
		case 1: {
			int cnt1 = 0;
			init_table(c);
			print_table(arr);
			printf("\n");
			printf("����Լ� �ְ���: %d\n�������α׷��� �ְ���: %d\n\n",loop(&cnt1,5,5),dp(5));
			printf("����Լ� ����Ƚ��: %d\n", cnt1);
			break;
		}
		case 2: {
			init_table(c);
			int num = matrix_Path(5);
			print_table(arr);
			print_table(c);
			printf("\n�����ش� %d �Դϴ�.\n", num);
			break;
		}
		case 3: {
			int num;
			printf("\nN: ");
			scanf("%d", &num);

			int** arr2 = (int**)malloc(sizeof(int*) * 4); // �� �迭 �Ҵ�

			for (int i = 0; i < 4; i++) {
				arr2[i] = (int*)malloc(sizeof(int) * num);
			}

			int** peb = (int**)malloc(sizeof(int*) * 4); // ���̺� �Ҵ�

			for (int i = 0; i < 4; i++) {
				peb[i] = (int*)malloc(sizeof(int) * num);
			}
		
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < num; j++) {
					int x = rand() % 20 - 5;
					arr2[i][j] = x;
				}
			}

			for (int i = 0; i < num; i++) {
				arr2[3][i] = arr2[0][i] + arr2[2][i];
			}

			printf("\n---------���̺�----------\n");
			for (int i = 0; i < 4; i++) {
				printf("\n");
				for (int j = 0; j < num; j++) {
					printf("%-4d ", arr2[i][j]);
				}
			}

			pebbleDP(arr2, peb, num);
			break;
		}
		case 4: {
			int num;
			printf("\nN: ");
			scanf("%d", &num);

			int** arr2 = (int**)malloc(sizeof(int*) * 2);

			for (int i = 0; i < 2; i++) {
				arr2[i] = (int*)malloc(sizeof(int) * num);
			}

			printf("\n����� ��: %d\n", domino(num));
			break;
		}
		case 5: {
			int num;
			printf("�� ���� ����� �ö󰥱��?\n");
			scanf("%d", &num);

			printf("\n%d���� ����� �ö� �� ����� ���� %d�� �Դϴ�.\n", num, upstair(num));
			break;
		}
		case 6: {
			int num;
			int a = 0;
			init_post(post);
			init_post(greedy);

			printf("\n�ݾ� �Է�: ");
			scanf("%d", &num);

			a = minpost(num);
			a = greedypost(num);
			break;
		}
		}
	}

	return 0;
}