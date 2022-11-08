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

void preorder(TreeNode* node) { // ������ȸ ���
	if (node != NULL) {
		printf("[%d] ", node->key);
		preorder(node->left);
		preorder(node->right);
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
	sum = count + IPL(node->left, count + 1) + IPL(node->right, count + 1);
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

int get_heigth(TreeNode* ptr) { // ����Ʈ���� ���̸� ����ϴ� �Լ�
	int height = 0;

	if (ptr != NULL) {
		height = 1 + max(get_heigth(ptr->left), get_heigth(ptr->right));
	}

	return height;
}

TreeNode* rotate_right(TreeNode* parent) { // ���������� ȸ����Ű�� �Լ�
	TreeNode* child = parent->left;
	parent->left = child->right;
	child->right = parent;

	return child; // ���ο� ��Ʈ ��ȯ
}

TreeNode* rotate_left(TreeNode* parent) { // �������� ȸ����Ű�� �Լ�
	TreeNode* child = parent->right;
	parent->right = child->left;
	child->left = parent;

	return child; // ���ο� ��Ʈ ��ȯ
}

int get_balance(TreeNode* node) { // ����� �����μ��� ��ȯ
	if (node == NULL) return 0;

	return get_heigth(node->left) - get_heigth(node->right);
}

TreeNode* insert(TreeNode* node, int key) { // ���� �Լ�
	if (node == NULL) return new_node(key); // Ʈ���� �����̸� ���ο� ��带 ��ȯ�Ѵ�.

	if (node->key > key) // �׷��� ������ ��ȯ������ Ʈ���� ��������.
		node->left = insert(node->left, key);
	else if (node->key < key)
		node->right = insert(node->right, key);
	else
		return node; // ����� ��Ʈ �����͸� ��ȯ

	int balance = get_balance(node); // ������ �����μ� ����

	if (balance > 1 && key < node->left->key) { // ���ο� ��尡 ���� �ڽ��� ���ʿ� �߰��Ǿ����� LLŸ�� ó��
		printf("\n----------��������----------\n\n");
		printf("---------- LLȸ�� ----------\n");
		return rotate_right(node);
	}

	if (balance < -1 && key > node->right->key) { // ���ο� ��尡 ������ �ڽ��� �����ʿ� �߰��Ǿ����� RRŸ�� ó��
		printf("\n----------��������----------\n\n");
		printf("---------- RRȸ�� ----------\n");
		return rotate_left(node);
	}

	if (balance > 1 && key > node->left->key) // ���ο� ��尡 ���� �ڽ��� �����ʿ� �߰��Ǿ����� LRŸ�� ó��
	{
		printf("\n----------��������----------\n\n");
		printf("---------- LRȸ�� ----------\n\n");
		node->left = rotate_left(node->left);
		return rotate_right(node);
	}

	if (balance < -1 && key < node->right->key) // ���ο� ��尡 ������ �ڽ��� ���ʿ� �߰��Ǿ����� RLŸ�� ó��
	{
		printf("\n----------��������----------\n\n");
		printf("---------- RLȸ�� ----------\n\n");
		node->right = rotate_right(node->right);
		return rotate_left(node);
	}
	return node;
}

TreeNode* delete(TreeNode* root, int key) {

	if (root == NULL) return root;

	if (key < root->key) { // ������ Ű�� �� ���� ��� ���� ����Ʈ��
		root->left = delete(root->left, key);
	}
	else if (key > root->key) { // ������ Ű�� �� ū ��� ������ ����Ʈ��
		root->right = delete(root->right, key);
	}

	else { // Ű�� ��Ʈ�� Ű�� ������� ������ ���
		if ((root->left == NULL) || (root->right == NULL)) { // �ڽ��� �ϳ��� ���
			TreeNode* temp = NULL;

			if (temp == root->left) {
				temp = root->right;
			}
			else {
				temp = root->left;
			}

			if (temp == NULL) { // �ڽ��� ���� ���
				temp = root;
				root = NULL;
			}
			else {
				root = temp;
			}
		}
		else { // �ڽ��� �ΰ��� ����� ���
			TreeNode* temp = min_value_node(root->right); // �İ��带 ����
			root->key = temp->key;
			root->right = delete(root->right, temp->key); // �İ��� ����
		}
	}

	if (root == NULL) return root; // ��尡 �ϳ����� ��� ��Ʈ ��ȯ

	int balance = get_balance(root); // ����� �������
	
	if (balance > 1 && get_balance(root->left) >= 0) { // LLŸ�� ó��
		printf("\n----------��������----------\n\n");
		printf("---------- LLȸ�� ----------\n");
		return rotate_right(root);
	}

	if (balance < -1 && get_balance(root->right) <= 0) { // RRŸ�� ó��
		printf("\n----------��������----------\n\n");
		printf("---------- RRȸ�� ----------\n");
		return rotate_left(root);
	}

	if (balance > 1 && get_balance(root->left) < 0) // LRŸ�� ó��
	{
		printf("\n----------��������----------\n\n");
		printf("---------- LRȸ�� ----------\n\n");
		root->left = rotate_left(root->left);
		return rotate_right(root);
	}

	if (balance < -1 && get_balance(root->right) > 0) // RLŸ�� ó��
	{
		printf("\n----------��������----------\n\n");
		printf("---------- RLȸ�� ----------\n\n");
		root->right = rotate_right(root->right);
		return rotate_left(root);
	}
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
	printf("8.AVLƮ�� ����\n");
	printf("9.AVLƮ�� ����\n");
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

	TreeNode* T3 = NULL;
	TreeNode* T4 = NULL;

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
			printf("\nAVL Ʈ�� IPL : %d", IPL(T4, 1));
			printf("\n");
			printf("\n�����˻�Ʈ�� IPL : %d", IPL(T3, 1));
			printf("\n");
			break;
		}
		case 5: {
			int ipl = IPL(T4, 1);
			int cnt = get_node_count(T4);
			double avg = (double)ipl / cnt;

			printf("\nAVLƮ���� ��� �˻� ���� : %.2f", avg);
			printf("\n");

			int ipl2 = IPL(T3, 1);
			int cnt2 = get_node_count(T3);
			double avg2 = (double)ipl2 / cnt2;

			printf("\n�����˻�Ʈ���� ��� �˻� ���� : %.2f", avg2);
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
		case 8: {
			int n = 1, key;
			while (1) {
				printf("\n---------------------------------%d��° Key  --------------------------------------\n", n);
				scanf("%d", &key);
				if (key == 0) {
					break;
				}
				T4 = insert(T4, key);
				T3 = insert_node(T3, key);

				printf("\nAVLƮ�� %d �ܰ� >>>> ", n);
				preorder(T4);
				printf("\n");
				printf("\n���� AVL Ʈ���� ���� : %d", get_heigth(T4));
				printf("\n");

				printf("\n�����˻�Ʈ�� %d �ܰ� >>>> ", n);
				preorder(T3);
				printf("\n");
				printf("\n���� �����˻�Ʈ���� ���� : %d", get_heigth(T3));
				printf("\n");
				n++;
			}
			printf("\nAVLƮ�� ���� ��ȸ ��� \n\n");
			inorder(T4);
			printf("\n\n�����˻�Ʈ�� ���� ��ȸ ��� \n\n");
			inorder(T3);
			printf("\n");
			break;
		}
		case 9: {
			int n = 1, key;
			while (1) {
				printf("\n---------------------------------%d��° ������ Key  --------------------------------------\n", n);
				scanf("%d", &key);
				if (key == 0) {
					break;
				}
				T4 = delete(T4, key);
				T3 = delete_node(T3, key);

				printf("\nAVLƮ�� %d �ܰ� >>>> ", n);
				preorder(T4);
				printf("\n");
				printf("\n���� AVL Ʈ���� ���� : %d", get_heigth(T4));
				printf("\n");

				printf("\n�����˻�Ʈ�� %d �ܰ� >>>> ", n);
				preorder(T3);
				printf("\n");
				printf("\n���� �����˻�Ʈ���� ���� : %d", get_heigth(T3));
				printf("\n");
				n++;
			}
			printf("\nAVLƮ�� ���� ��ȸ ��� \n\n");
			inorder(T4);
			printf("\n\n�����˻�Ʈ�� ���� ��ȸ ��� \n\n");
			inorder(T3);
			printf("\n");
			break;
		}
		}
	}
	return 0;
}