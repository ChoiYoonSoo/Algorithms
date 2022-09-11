/* 1주차 실습
* 1. 임의 순서로 배열에 저장된 열 개의 정수값 중에서 최대값과 최소값을 찾는 프로그램을 하나의 반복문장으로 작성하시오.
* 2. 키보드로 입력된 문자열의 길이를 구하는 프로그램을 (1) 반복문장으로 (2) 순환호출로 작성하시오. 단, strlen() 사용 금지
* 3. 십진수 n을 b진수로 변환하는 프로그램을 반복 문장으로 작성하시오
* 4. 이진검색트리에 임의의 정수 10개를 삽입하고, (1) 완성된 트리의 높이를 구하고 (2) 트리를 중위순회한 순서를 말하시오
*/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct TreeNode { // 노드의 구조
	int key;
	struct TreeNode* left;
	struct TreeNode* right;
}TreeNode;

TreeNode* new_node(int item) { // 새로운 노드 생성 함수
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->key = item;
	temp->left = temp->right = NULL;
	return temp;
}

TreeNode* insert_node(TreeNode* node, int key) { // 삽입 함수
	if (node == NULL) return new_node(key); // 트리가 공백이면 새로운 노드를 반환한다.
	if (node->key > key) // 그렇지 않으면 순환적으로 트리를 내려간다.
		node->left = insert_node(node->left, key);
	else if (node->key == key) // 중복된 키값이 있을경우 저장하지 않음
		return node;
	else
		node->right = insert_node(node->right, key);

	return node; // 변경된 루트 포인터를 반환
}

void inorder(TreeNode* node) { // 중위순회
	if (node != NULL) {
		inorder(node->left);
		printf("[%d] ", node->key);
		inorder(node->right);
	}
}

void remove_all(TreeNode* node) { // 노드 free
	if (node != NULL) {
		remove_all(node->left);
		remove_all(node->right);
		free(node);
	}
}

int get_heigth(TreeNode* node) { // 트리의 높이를 계산하는 함수
	int height = 0;

	if (node != NULL) {
		height = 1 + max(get_heigth(node->left), get_heigth(node->right));
	}

	return height;
}

int MAX(int* arr) { // 최대값 찾는 함수
	int max = arr[0];

	for (int i = 1; i < 10; i++) {
		if (max < arr[i]) {
			max = arr[i];
		}
	}
	return max;
}

int MIN(int* arr) { // 최소값 찾는 함수
	int min = arr[0];

	for (int i = 1; i < 10; i++) {
		if (min > arr[i]) {
			min = arr[i];
		}
	}
	return min;
}

int length(char* str) { // 순환호출을 이용한 문자열길이 계산 함수
	if (*str == '\0') {
		return 0;
	}
	else {
		return 1 + length(str + 1);
	}
}

int length2(char* str) { // 반복문을 이용한 문자열길이 계산 함수
	int len = 0;
	while (*str++ != '\0') {
		len++;
	}
	return len;
}

char arr2[100];
int change(int n, int b) { // 진법 변환 함수
	int i = 0;

	while (n >= b) {
		if (n % b > 10) {
			arr2[i] = (n % b) + 55;
		}
		else {
			arr2[i] = (n % b) + 48;
		}
		n = n / b;
		i++;
	}
	if (n > 10) {
		arr2[i] = n + 55;
	}
	else {
		arr2[i] = n + 48;
	}
	return i;
}

void menu() {
	printf("\n=====번호 선택=====\n");
	printf("1.최대값, 최소값\n");
	printf("2.문자열 길이 계산\n");
	printf("3.진법 변환\n");
	printf("4.트리 높이, 중위순회\n");
	printf("5.종료\n");
}

int main(void) {
	int num;
	int arr[10];

	while (1) {
		menu();
		scanf("%d", &num);

		switch (num) {
		case 1: {
			for (int i = 0; i < 10; i++) {
				arr[i] = rand() % 30 + 1;
				printf("%d ", arr[i]);
			}
			printf("\n반복문을 이용한 최대값 : %d\n", MAX(&arr));
			printf("반복문을 이용한 최소값 : %d\n", MIN(&arr));
			break;
		}
		case 2: {
			char str[100];
			printf("문자열 입력: ");
			scanf("%s", str);
			printf("순환호출 이용한 문자열의 길이: %d\n", length(str));
			printf("반복문을 이용한 문자열의 길이: %d\n", length2(str));
			break;
		}
		case 3: {
			int n, b;
			printf("10진수 입력: ");
			scanf("%d", &n);
			printf("변환할 진수 입력: ");
			scanf("%d", &b);
			int j = change(n, b);
			for (int i = j; i >= 0; i--) {
				printf("%c", arr2[i]);
			}
			printf("(%d)", b);
			break;
		}
		case 4: {
			TreeNode* root = NULL;
			int number[10];

			for (int i = 0; i < 10; i++) {
				number[i] = rand() % 50 + 1;
				printf("%d번째 노드값 : %d\n", i, number[i]);
				root = insert_node(root, number[i]);
			}
			printf("완성된 트리의 높이 : %d\n", get_heigth(root));
			printf("트리를 중위순회한 순서 : ");
			inorder(root);
			remove_all(root);
			break;
		}
		case 5: {
			return 0;
		}
		}
	}
	return 0;
}