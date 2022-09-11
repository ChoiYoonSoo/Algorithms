#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct TreeNode {
	int key;
	struct TreeNode* left;
	struct TreeNode* right;
}TreeNode;

int MAX1(int* arr, int max) {

	for (int i = 0; i < 10; i++) {
		if (max < arr[i]) {
			max = arr[i];
		}
	}
	return max;
}

int MAX2(int* arr, int max, int count) {
	if (count == 0) {
		return max;
	}
	else {
		if (max < *arr) {
			max = *arr;
		}
		MAX2(arr + 1, max, count - 1);
	}
}

void change(int a, int b) {
	int arr[100];
	int i = 0;

	while (a >= b) {
		arr[i] = a % b;
		a = a / b;
		i++;
	}
	arr[i] = a;

	for (; i >= 0; i--) {
		printf("%d", arr[i]);
	}
}

void change2(int a, int b) {
	if (a < b) {
		printf("%d", a);
	}
	else {
		change2(a / b, b);
		printf("%d", a % b);
	}
}

int change3(int bin) {
	int dec = 0;
	int add = 1;

	while (bin > 0) {
		if (bin % 10 != 0) {
			dec += (bin % 10) * add;
		}
		bin = bin / 10;
		add = add * 2;
	}
	return dec;
}

int length(char* str) {
	if (*str == '\0') {
		return 0;
	}
	else {
		return 1 + length(str + 1);
	}
}

typedef struct Point {
	int xpos;
	int ypos;
}Point;

typedef struct ListNode {
	int x;
	int y;
	struct ListNode* link;
}ListNode;

ListNode* insert(ListNode* head, int xpos, int ypos) {
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->x = xpos;
	p->y = ypos;
	p->link = head;
	head = p;
	return head;
}

ListNode* delete(ListNode* head) {
	ListNode* removed;
	if (head == NULL) return NULL;
	removed = head;
	head = removed->link;
	free(removed);
	return head;
}

double dis(ListNode* head, Point* pos) {
	double result = 0.0;

	for (ListNode* p = head; p != NULL; p = p->link) {
		result += sqrt(pow(p->x, 2) + pow(p->y, 2));
	}
	return result;
}

void menu() {
	printf("\n=====번호 선택=====\n");
	printf("1.최댓값\n");
	printf("2.진수변환\n");
	printf("3.2진수 10진수로 변환\n");
	printf("4.문자열 길이 계산\n");
	printf("5.원점에서부터 평균거리 계산\n");
	printf("6.종료\n");
}

int main(void) {
	int n;
	int arr[10];

	while (1) {
		menu();
		scanf("%d", &n);

		switch (n) {
		case 1: {
			printf("10개의 정수 입력: ");
			for (int i = 0; i < 10; i++) {
				scanf("%d", &arr[i]);
			}
			int max = arr[0];

			printf("반복문을 이용한 최댓값 : %d\n", MAX1(&arr, max));
			printf("순환호출을 이용한 최댓값 : %d\n", MAX2(&arr, max, 10));
			break;
		}
		case 2: {
			int a, b;
			printf("10진수 입력: ");
			scanf("%d", &a);
			printf("변환할 진수 입력: ");
			scanf("%d", &b);
			change(a, b);
			printf("\n");
			change2(a, b);
			break;
		}
		case 3: {
			int bin;
			printf("2진수 입력: ");
			scanf("%d", &bin);
			printf("변환된 10진수 : %d\n", change3(bin));
			break;
		}
		case 4: {
			char str[100];
			printf("문자열 입력: ");
			scanf("%s", str);
			printf("문자열의 길이: %d\n", length(str));
			break;
		}
		case 5: {
			ListNode* head = NULL;
			Point pos[5];

			printf("5개의 좌표 입력: ");
			for (int i = 0; i < 5; i++) {
				scanf("%d %d", &pos[i].xpos, &pos[i].ypos);
				head = insert(head, pos[i].xpos, pos[i].ypos);
			}

			double result = dis(head, pos);
			printf("원점으로부터 평균 거리: %f\n", result / 5);
			break;

		}
		case 6: {
			return 0;
		}
		}

	}
	return 0;
}