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
	c[0][0] = arr[0][0]; // 행렬의 첫 번째 테이블에 첫 번째 값을 담는다
	(*cnt1)++;

	for (int i = 1; i < n; i++) {
		c[0][i] = arr[0][i] + c[0][i - 1]; // 1열일 때 행들의 누적 값들을 각 테이블에 담는다

		(*cnt1)++;
	}

	for (int i = 1; i < n; i++) {
		c[i][0] = arr[i][0] + c[i - 1][0]; // 1행일 때 열들의 누적 값들을 각 테이블에 담는다
		(*cnt1)++;
	}

	for (int i = 1; i < n; i++) {
		for (int j = 1; j < n; j++) {
			c[i][j] = max_path(arr[i][j] + c[i - 1][j], arr[i][j] + c[i][j - 1]);
			// 기억 되어있는 누적값들을 이용하여 현재 값과 더한 -1열이나 -1행 중에서 더 큰값을 현재테이블에 담는다
			(*cnt1)++;
		}
	}

	return c[n - 1][n - 1]; // 최고점반환
}

int loop(int** arr, int** c, int* cnt, int i, int j) { // memoization 기법
	// 달라진 것은 반환 값을 테이블 배열에 담는다는 것이다.
	int a, b;
	if (c[i][j] != -1) { // 테이블 배열에 값이 담겨있다면
		return c[i][j]; // 바로 그 즉시 반환 카운트 x
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
	scanf("%d", &n); // 행렬의 크기 n*n

	int** arr = (int**)malloc(sizeof(int*) * n); // 행렬을 크기만큼 선언

	for (int i = 0; i < n; i++) {
		arr[i] = (int*)malloc(sizeof(int) * n);
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &arr[i][j]); // 행렬에 값을 입력
		}
	}

	int** c = (int**)malloc(sizeof(int*) * n); // 행렬의 테이블이 되어줄 행렬을 선언

	for (int i = 0; i < n; i++) {
		c[i] = (int*)malloc(sizeof(int) * n);
	}

	printf("최고점: %d\n\n", dp(arr, c, n, &cnt1));
	printf("수행횟수: %d\n", cnt1);
	return 0;
}