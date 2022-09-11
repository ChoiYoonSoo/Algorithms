/* 1���� �ǽ�
* 1. ���� ������ �迭�� ����� �� ���� ������ �߿��� �ִ밪�� �ּҰ��� ã�� ���α׷��� �ϳ��� �ݺ��������� �ۼ��Ͻÿ�.
* 2. Ű����� �Էµ� ���ڿ��� ���̸� ���ϴ� ���α׷��� (1) �ݺ��������� (2) ��ȯȣ��� �ۼ��Ͻÿ�. ��, strlen() ��� ����
* 3. ������ n�� b������ ��ȯ�ϴ� ���α׷��� �ݺ� �������� �ۼ��Ͻÿ�
* 4. �����˻�Ʈ���� ������ ���� 10���� �����ϰ�, (1) �ϼ��� Ʈ���� ���̸� ���ϰ� (2) Ʈ���� ������ȸ�� ������ ���Ͻÿ�
*/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct TreeNode { // ����� ����
	int key;
	struct TreeNode* left;
	struct TreeNode* right;
}TreeNode;

TreeNode* new_node(int item) { // ���ο� ��� ���� �Լ�
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->key = item;
	temp->left = temp->right = NULL;
	return temp;
}

TreeNode* insert_node(TreeNode* node, int key) { // ���� �Լ�
	if (node == NULL) return new_node(key); // Ʈ���� �����̸� ���ο� ��带 ��ȯ�Ѵ�.
	if (node->key > key) // �׷��� ������ ��ȯ������ Ʈ���� ��������.
		node->left = insert_node(node->left, key);
	else if (node->key == key) // �ߺ��� Ű���� ������� �������� ����
		return node;
	else
		node->right = insert_node(node->right, key);

	return node; // ����� ��Ʈ �����͸� ��ȯ
}

void inorder(TreeNode* node) { // ������ȸ
	if (node != NULL) {
		inorder(node->left);
		printf("[%d] ", node->key);
		inorder(node->right);
	}
}

void remove_all(TreeNode* node) { // ��� free
	if (node != NULL) {
		remove_all(node->left);
		remove_all(node->right);
		free(node);
	}
}

int get_heigth(TreeNode* node) { // Ʈ���� ���̸� ����ϴ� �Լ�
	int height = 0;

	if (node != NULL) {
		height = 1 + max(get_heigth(node->left), get_heigth(node->right));
	}

	return height;
}

int MAX(int* arr) { // �ִ밪 ã�� �Լ�
	int max = arr[0];

	for (int i = 1; i < 10; i++) {
		if (max < arr[i]) {
			max = arr[i];
		}
	}
	return max;
}

int MIN(int* arr) { // �ּҰ� ã�� �Լ�
	int min = arr[0];

	for (int i = 1; i < 10; i++) {
		if (min > arr[i]) {
			min = arr[i];
		}
	}
	return min;
}

int length(char* str) { // ��ȯȣ���� �̿��� ���ڿ����� ��� �Լ�
	if (*str == '\0') {
		return 0;
	}
	else {
		return 1 + length(str + 1);
	}
}

int length2(char* str) { // �ݺ����� �̿��� ���ڿ����� ��� �Լ�
	int len = 0;
	while (*str++ != '\0') {
		len++;
	}
	return len;
}

char arr2[100];
int change(int n, int b) { // ���� ��ȯ �Լ�
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
	printf("\n=====��ȣ ����=====\n");
	printf("1.�ִ밪, �ּҰ�\n");
	printf("2.���ڿ� ���� ���\n");
	printf("3.���� ��ȯ\n");
	printf("4.Ʈ�� ����, ������ȸ\n");
	printf("5.����\n");
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
			printf("\n�ݺ����� �̿��� �ִ밪 : %d\n", MAX(&arr));
			printf("�ݺ����� �̿��� �ּҰ� : %d\n", MIN(&arr));
			break;
		}
		case 2: {
			char str[100];
			printf("���ڿ� �Է�: ");
			scanf("%s", str);
			printf("��ȯȣ�� �̿��� ���ڿ��� ����: %d\n", length(str));
			printf("�ݺ����� �̿��� ���ڿ��� ����: %d\n", length2(str));
			break;
		}
		case 3: {
			int n, b;
			printf("10���� �Է�: ");
			scanf("%d", &n);
			printf("��ȯ�� ���� �Է�: ");
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
				printf("%d��° ��尪 : %d\n", i, number[i]);
				root = insert_node(root, number[i]);
			}
			printf("�ϼ��� Ʈ���� ���� : %d\n", get_heigth(root));
			printf("Ʈ���� ������ȸ�� ���� : ");
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