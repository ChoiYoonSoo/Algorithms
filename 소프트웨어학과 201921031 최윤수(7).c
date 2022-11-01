#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int key;
	struct TreeNode* left;
	struct TreeNode* right;
}TreeNode;

TreeNode* search(TreeNode* node, int key) { // Ž�� �Լ�
	if (node == NULL) return NULL;

	if (node->key == key) return node;
	else if (node->key > key)
		return search(node->left, key);
	else
		return search(node->right, key);
}

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
	else
		node->right = insert_node(node->right, key);

	return node; // ����� ��Ʈ �����͸� ��ȯ
}

void inorder(TreeNode* node) { // ������ȸ ���
	if (node != NULL) {
		inorder(node->left);
		printf("[%d] ", node->key);
		inorder(node->right);
	}
}

TreeNode* min_value_node(TreeNode* node) {              // ������ ����Ʈ������ �ּҰ��� ã�� �Լ�
	TreeNode* current = node;
	while (current->left != NULL) {                     // �� ���� �ܸ� ��带 ã���� ������
		current = current->left;
	}
	return current;
}

TreeNode* delete_node(TreeNode* node, int key) { // ���� Ž�� Ʈ���� Ű�� �־����� Ű�� ����� ��带 �����ϰ� ���ο� ��Ʈ ��带 ��ȯ
	if (node == NULL) return node;
	if (node->key > key) // ���� Ű�� ��Ʈ���� ������ ���� ���� Ʈ���� �ִ� ����
		node->left = delete_node(node->left, key);
	else if (node->key < key) // ���� Ű�� ��Ʈ���� ũ�� ������ ���� Ʈ���� �ִ� ����
		node->right = delete_node(node->right, key);
	else { // Ű�� ��Ʈ�� ������ �� ��带 �����ϸ� ��
		if (node->left == NULL) { // ù ��°�� �� ��° ���
			TreeNode* temp = node->right;
			free(node);
			return temp;
		}
		else if (node->right == NULL) {
			TreeNode* temp = node->left;
			free(node);
			return temp;
		}
		TreeNode* temp = min_value_node(node->right); // �����Ϸ��� ��尡 �ΰ��� ����Ʈ���� ���°��
		node->key = temp->key; // ���� ��ȸ�� �İ� ��带 �����Ѵ�.
		node->right = delete_node(node->right, temp->key); // ���� ��ȸ�� �İ� ��带 �����Ѵ�.
	}
	return node;
}

int IPL(TreeNode* node, int count) { // ���ΰ�α��� ���
	int sum = 0;

	if (node == NULL) return 0;
	sum = count + IPL(node->left, count+1) + IPL(node->right, count+1);
	return sum;
}

int get_node_count(TreeNode* node) { // ����� ���� ���ϴ� �Լ�
	int count = 0;

	if (node != NULL) {
		count = 1 + get_node_count(node->left) + get_node_count(node->right);
	}

	return count;
}

int idx = 0;
void BST_inorder(TreeNode* node, int arr[]) {
	if (node != NULL) {
		BST_inorder(node->left, arr);
		arr[idx++] = node->key;
		printf("[%d] ", node->key);
		BST_inorder(node->right, arr);
	}
}

int BST_check(TreeNode* root, int cnt) {
	int* arr = (int*)malloc(sizeof(int) * cnt);
	BST_inorder(root, arr);

	for (int i = 0; i < cnt - 1; i++) {
		if (arr[i] > arr[i + 1]) {
			return 0;
		}
	}
	return 1;
}

int hasPathSum(TreeNode* root, int sum) {
	if (root == NULL) return 0;
	if (root->left == NULL && root->right == NULL) {
		if (sum - root->key == 0) { // ������忡 ���������� 0�� ������ ���̽��� ������
			return 1;
		}
		else
			return 0;
	}
	else {
		return hasPathSum(root->left, sum - root->key) || hasPathSum(root->right, sum - root->key);
	}
}

TreeNode* addNewNode(int data, TreeNode* leftNode, TreeNode* rightNode) {
	TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
	root->key = data;
	root->left = leftNode;
	root->right = rightNode;
	return root;
}

void menu() {
	printf("\n0.����\n");
	printf("1.�˻�\n");
	printf("2.����\n");
	printf("3.����\n");
	printf("4.IPL ���\n");
	printf("5.��� �˻� ���� ���\n");
	printf("6.�����˻�Ʈ�� �Ǻ�\n");
	printf("7.����� ���� �־��� ���� ��ΰ� �ִ��� �Ǵ�\n");
	printf("��ȣ�� �Է��ϼ��� : ");
}

int main(void) {
	int n;
	TreeNode* T1 = NULL;

	TreeNode* n8 = addNewNode(42, NULL, NULL);
	TreeNode* n7 = addNewNode(30, NULL, NULL);
	TreeNode* n6 = addNewNode(55, n8, NULL);
	TreeNode* n5 = addNewNode(15, n7, NULL);
	TreeNode* n4 = addNewNode(2, NULL, NULL);
	TreeNode* n3 = addNewNode(10, NULL, n6);
	TreeNode* n2 = addNewNode(16, n4, n5);
	TreeNode* n1 = addNewNode(22, n2, n3);
	TreeNode* T2 = n1;

	while (1) {
		menu();
		scanf("%d", &n);

		switch (n) {

		case 0: {
			printf("\n���α׷��� �����մϴ�.\n");
			return 0;
		}
		case 1: {
			TreeNode* tree = NULL;
			int key;
			printf("\n�˻��� Ű �Է�: ");
			scanf("%d", &key);
			tree = search(T1, key);

			if (tree != NULL) {
				printf("ã�� Ű �� : %d", tree->key);
				printf("\n");
			}
			else
				printf("\nã�� Ű ���� �������� �ʽ��ϴ�.\n");
			break;
		}
		case 2: {
			int key;
			printf("\n������ Ű �Է� : ");
			scanf("%d", &key);
			T1 = insert_node(T1, key);
			inorder(T1);
			printf("\n");
			break;
		}
		case 3: {
			int key;
			TreeNode* tree = NULL;
			printf("\n������ Ű �Է� : ");
			scanf("%d", &key);

			tree = search(T1, key);
			if (tree != NULL) {
				T1 = delete_node(T1, key);
				printf("\nŰ �� ���� �� Ʈ�� ���\n");
				inorder(T1);
				printf("\n");
			}
			else
				printf("\n������ Ű ���� �������� �ʽ��ϴ�.\n");
			break;
		}
		case 4: {
			printf("\nIPL : %d", IPL(T1, 1));
			printf("\n");
			break;
		}
		case 5: {
			int ipl = IPL(T1, 1);
			int cnt = get_node_count(T1);
			double avg = (double)ipl / cnt;

			printf("\n�����˻�Ʈ���� ��� �˻� ���� : %.2f",avg);
			printf("\n");
			break;
		}
		case 6: {
			idx = 0;
			int num;
			printf("\n�� Ʈ���� �Ǻ��� Ʈ�� ����\n");
			printf("1.T1\n");
			printf("2.T2\n");
			scanf("%d", &num);

			if (num == 1) {
				if (BST_check(T1, get_node_count(T1)) == 0) {
					printf("\n�����˻�Ʈ���� �ƴմϴ�.\n");
				}
				else
					printf("\n�����˻�Ʈ�� �Դϴ�.\n");

			}
			else {
				if (BST_check(T2, get_node_count(T2)) == 0) {
					printf("\n�����˻�Ʈ���� �ƴմϴ�.\n");
				}
				else
					printf("\n�����˻�Ʈ�� �Դϴ�.\n");
			}
			break;
		}
		case 7: {
			int sum;
			printf("\n�� �Է�: ");
			scanf("%d", &sum);
			if (hasPathSum(T2, sum) == 0) {
				printf("\n��ΰ� �����ϴ�.\n");
			}
			else
				printf("\n��ΰ� �ֽ��ϴ�.\n");
			break;
		}
		}
	}
	return 0;
}