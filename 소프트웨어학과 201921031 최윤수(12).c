#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define max(a,b)  (((a) > (b)) ? (a) : (b))

//1. 임의의 양수로 채워진 5*5 행렬을 생성하고, 행렬 경로문제를 동적프로그래밍으로 완성하시오.
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

//2. 위 문제 1을 재귀호출로 구현해서 답을 확인하고, 호출이 모두 몇 번 발생했는지도 확인하시오.
int loop(int* cnt, int i, int j) {
	(*cnt)++;
	if (i == 0 || j == 0) {
		return 0;
	}
	else {
		return (arr[i][j] + max(loop(cnt,i - 1, j), loop(cnt,i, j - 1)));
	}
}

//3. 교재 290쪽 연습문제 06을 동적프로그래밍 방법으로 완성하시오.
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

void init_table(int a[][6]) { // 테이블 초기화 함수
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 6; j++)
			a[i][j] = 0;
}

void print_table(int a[][6]) { // 행렬 출력 함수
	printf("\n행렬: \n");
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

//4. 3*n 테이블을 음수를 포함한 임의의 정수로 채우고, 돌 놓기 문제를 동적 프로그래밍으로 완성하시오.
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

	printf("\n---------테이블----------\n");
	for (int i = 0; i < 4; i++) {
		printf("\n");
		for (int j = 0; j < n; j++) {
			printf("%-4d ", peb[i][j]);
		}
	}printf("\n");
}

//5. 교재 294쪽 연습문제 17번을 동적프로그래밍 방법으로 완성하시오.
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
6. N개 계단을 올라가려고 한다. 매번 계단을 1칸 또는 2칸을 올라갈 수 있다.

맨 위까지 올라갈 수 있는 방법의 수는 몇 개인지 구하는 프로그램을 동적 프로그래밍 방법으로 완성하시오.
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
7. 어느 우체국에는 80원짜리, 50원짜리, 10원짜리 우표가 있다.

(1) 특정 금액의 우편요금을 위해 사용하는 최소 개수의 우표 개수를 동적프로그래밍으로 구하시오. (10, 20, 30, 40, 50 … 300원을 만드는 최소 우표 개수를 구하는 표를 완성하시오).

선택사항으로, 최적의 해가 각 우표를 몇 장씩 사용하는지도 출력하시오.

(2) 만약, 우체국 직원이 그리디 알고리즘을 적용한다면 어떤 조합으로 우표들을 받게 되는지

계산하는 프로그램을 작성하고, 그 결과가 최적의 결과인지 (1)과 비교하시오.
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

	int index = n / 10; //금액의 인덱스

	for (int i = 1; i <= index; i++) {
		for (int j = 1; j <= 3; j++) {
			if (p[j] <= post[0][i] && post[4][i - (p[j] / 10)] + 1 < post[4][i]) {

				post[4][i] = post[4][i - (p[j] / 10)] + 1; //최적해

				post[3][i] = post[3][i - (p[j] / 10)]; //10원짜리
				post[2][i] = post[2][i - (p[j] / 10)]; //50원짜리
				post[1][i] = post[1][i - (p[j] / 10)]; //80원짜리
				post[j][i]++; //j번째 우표 액면가 증가

				printf("-------------------------\n");
				printf("%d원의 최적해 : %d장\n80원 : %d개\n50원 : %d개\n10원 : %d개\n", post[0][i], post[4][i], post[1][i], post[2][i], post[3][i]);

			}

		}

	}
	return post[4][index];
}

int greedypost(int n) {

	int index = n / 10, value; //금액의 인덱스

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
	printf("%d원의 Greedy : %d장\n80원 : %d개\n50원 : %d개\n10원 : %d개\n", greedy[0][index], greedy[4][index], greedy[1][index], greedy[2][index], greedy[3][index]);
	return greedy[4][index];
}

void menu() {
	printf("\n0.종료\n");
	printf("1.행렬 경로문제 동적&재귀\n");
	printf("2.290쪽 6번 행렬 경로 연습문제\n");
	printf("3.돌 놓기 문제\n");
	printf("4.도미노 문제\n");
	printf("5.계단 올라가기 문제\n");
	printf("6.우표 문제\n");
	printf("번호를 입력하세요: ");
}

int main(void) {
	int n;

	while (1) {
		menu();
		scanf("%d", &n);

		switch (n) {

		case 0: {
			printf("\n\n프로그램을 종료합니다.\n");
			return 0;
		}
		case 1: {
			int cnt1 = 0;
			init_table(c);
			print_table(arr);
			printf("\n");
			printf("재귀함수 최고점: %d\n동적프로그래밍 최고점: %d\n\n",loop(&cnt1,5,5),dp(5));
			printf("재귀함수 수행횟수: %d\n", cnt1);
			break;
		}
		case 2: {
			init_table(c);
			int num = matrix_Path(5);
			print_table(arr);
			print_table(c);
			printf("\n최적해는 %d 입니다.\n", num);
			break;
		}
		case 3: {
			int num;
			printf("\nN: ");
			scanf("%d", &num);

			int** arr2 = (int**)malloc(sizeof(int*) * 4); // 돌 배열 할당

			for (int i = 0; i < 4; i++) {
				arr2[i] = (int*)malloc(sizeof(int) * num);
			}

			int** peb = (int**)malloc(sizeof(int*) * 4); // 테이블 할당

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

			printf("\n---------테이블----------\n");
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

			printf("\n방법의 수: %d\n", domino(num));
			break;
		}
		case 5: {
			int num;
			printf("몇 개의 계단을 올라갈까요?\n");
			scanf("%d", &num);

			printf("\n%d개의 계단을 올라갈 때 경우의 수는 %d개 입니다.\n", num, upstair(num));
			break;
		}
		case 6: {
			int num;
			int a = 0;
			init_post(post);
			init_post(greedy);

			printf("\n금액 입력: ");
			scanf("%d", &num);

			a = minpost(num);
			a = greedypost(num);
			break;
		}
		}
	}

	return 0;
}