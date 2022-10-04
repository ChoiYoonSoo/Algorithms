#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void selection_sort(int arr[], int num) {  // 선택정렬 함수
	int temp = 0;
	int cnt = 0;
	int cnt2 = 0;

	for (int i = 0; i < num - 1; i++) {
		printf("\n===============================%d단계==================================\n\n", i + 1);

		for (int j = i + 1; j < num; j++) {
			cnt++;
			if (arr[i] > arr[j]) {                               // 최소값 앞으로 이동
				printf("[%d] -> [%d] 변경  ------------>  ", arr[i], arr[j]);
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;

				for (int i = 0; i < num; i++) {
					printf("%d ", arr[i]);
				}printf("\n");
			}
		}
		cnt2 += cnt;
		printf("\n%d단계 %d번 비교\n\n", i + 1, cnt);
		cnt = 0;
		printf("변경된 배열출력\n");
		for (int i = 0; i < num; i++) {
			printf("%d ", arr[i]);
		}printf("\n");
	}
	printf("\n\n총 %d번 변경\n", cnt2);

	printf("\n\n==========정렬된 배열 출력==========\n");
	for (int i = 0; i < num; i++) {
		printf("%d ", arr[i]);
	}
}

void insertion_sort(int arr[], int num) { // 삽입정렬
	int temp = 0;
	int i, j, cnt = 0, cnt2 = 1;

	for (i = 1; i < num; i++) {
		temp = arr[i]; // 현재 삽입될 숫자인 i번째 정수를 temp 변수로 복사

		for (j = i - 1; j >= 0 && arr[j] > temp; j--) { // temp가 더 큰 값일 때까지 
			arr[j + 1] = arr[j]; // 한 칸 뒤로 이동 
			cnt2++;
		}
		cnt += cnt2;
		arr[j + 1] = temp; // 알맞은 위치에 temp 삽입 
		printf("\n%d단계: ", i);

		for (int i = 0; i < num; i++) {
			printf("%d ", arr[i]);
		}printf("     비교횟수: %d\n",cnt2);
		cnt2 = 1;
	}
	printf("\n전체 비교 횟수: %d", cnt);
	printf("\n\n==========정렬된 배열 출력==========\n");
	for (int i = 0; i < num; i++) {
		printf("%d ", arr[i]);
	}printf("\n");
}

void bubble_sort(int arr[], int num) {
	int temp, n;
	int cnt = 0, cnt2 = 0;

	for (int i = 0; i < num; i++) {
		printf("\n===============================%d번단계==================================\n\n", i + 1);
		for (int j = 0; j < num - i - 1; j++) {
			cnt++;
			if (arr[j] > arr[j + 1]) {
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				cnt2++;
			}
			for (int i = 0; i < num; i++) {
				printf("%d ", arr[i]);
			}printf("\n");
		}

		if (cnt2 == 0) {
			printf("\n변경된 값이 없습니다 정렬이 완료된 배열입니다.\n");
			printf("0.비교 진행\n");
			printf("1.비교 종료\n");
			scanf("%d", &n);

			if (n == 1) {
				break;
			}
		}
		cnt2 = 0;

		printf("\n총 %d번 비교\n", cnt);
		cnt = 0;
		printf("\n-----변경된 배열 출력-----\n");

		for (int i = 0; i < num; i++) {
			printf("%d ", arr[i]);
		}printf("\n");
	}
	printf("\n\n==========정렬된 배열 출력==========\n");
	for (int i = 0; i < num; i++) {
		printf("%d ", arr[i]);
	}printf("\n");
}

void menu() {
	printf("\n========================번호입력=======================\n");
	printf("1.선택정렬\n");
	printf("2.삽입정렬\n");
	printf("3.버블정렬\n");
	printf("4.프로그램 종료\n");
}

int main(void) {
	int n;

	while (1) {
		menu();
		scanf("%d", &n);

		switch (n) {
		case 1: {
			int num;
			printf("N: ");
			scanf("%d", &num);
			int* arr = (int*)malloc(sizeof(int) * num);

			printf("배열 출력\n");
			for (int i = 0; i < num; i++) {
				arr[i] = rand() % 50 + 1;
				printf("%d ", arr[i]);
			}printf("\n");

			selection_sort(arr, num);
			break;
		}
		case 2: {
			int num;
			printf("N: ");
			scanf("%d", &num);
			int* arr = (int*)malloc(sizeof(int) * num);

			printf("정렬할 원소: ");
			for (int i = 0; i < num; i++) {
				arr[i] = rand() % 50 + 1;
				printf("%d ", arr[i]);
			}printf("\n");

			printf("\n<<<<<<<<<<<<<<<<<<<<< 삽입 정렬 수행 >>>>>>>>>>>>>>>>>>>>>>>>\n\n");
			insertion_sort(arr, num);
			break;
		}
		case 3: {
			int num;
			printf("N: ");
			scanf("%d", &num);
			int* arr = (int*)malloc(sizeof(int) * num);

			printf("정렬할 원소: ");
			for (int i = 0; i < num; i++) {
				arr[i] = rand() % 50 + 1;
				printf("%d ", arr[i]);
			}printf("\n");

			printf("<<<<<<<<<<<<<<<<<<<<< 버블 정렬 수행 >>>>>>>>>>>>>>>>>>>>>>>>\n");
			bubble_sort(arr, num);
			break;
		}
		case 4: {
			printf("프로그램을 종료합니다.\n");
			return 0;
		}
		}
	}
	return 0;
}