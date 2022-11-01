#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int key;
	struct TreeNode* left;
	struct TreeNode* right;
}TreeNode;

TreeNode* search(TreeNode* node, int key) { // 탐색 함수
	if (node == NULL) return NULL;

	if (node->key == key) return node;
	else if (node->key > key)
		return search(node->left, key);
	else
		return search(node->right, key);
}

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
	else
		node->right = insert_node(node->right, key);

	return node; // 변경된 루트 포인터를 반환
}

void inorder(TreeNode* node) { // 중위순회 출력
	if (node != NULL) {
		inorder(node->left);
		printf("[%d] ", node->key);
		inorder(node->right);
	}
}

TreeNode* min_value_node(TreeNode* node) {              // 오른쪽 서브트리에서 최소값을 찾는 함수
	TreeNode* current = node;
	while (current->left != NULL) {                     // 맨 왼쪽 단말 노드를 찾으러 내려감
		current = current->left;
	}
	return current;
}

TreeNode* delete_node(TreeNode* node, int key) { // 이진 탐색 트리와 키가 주어지면 키가 저장된 노드를 삭제하고 새로운 루트 노드를 반환
	if (node == NULL) return node;
	if (node->key > key) // 만약 키가 루트보다 작으면 왼쪽 서브 트리에 있는 것임
		node->left = delete_node(node->left, key);
	else if (node->key < key) // 만약 키가 루트보다 크면 오른쪽 서브 트리에 있는 것임
		node->right = delete_node(node->right, key);
	else { // 키가 루트와 같으면 이 노드를 삭제하면 됨
		if (node->left == NULL) { // 첫 번째나 두 번째 경우
			TreeNode* temp = node->right;
			free(node);
			return temp;
		}
		else if (node->right == NULL) {
			TreeNode* temp = node->left;
			free(node);
			return temp;
		}
		TreeNode* temp = min_value_node(node->right); // 삭제하려는 노드가 두개의 서브트리를 갖는경우
		node->key = temp->key; // 중위 순회시 후계 노드를 복사한다.
		node->right = delete_node(node->right, temp->key); // 중위 순회시 후계 노드를 삭제한다.
	}
	return node;
}

int IPL(TreeNode* node, int count) { // 내부경로길이 계산
	int sum = 0;

	if (node == NULL) return 0;
	sum = count + IPL(node->left, count+1) + IPL(node->right, count+1);
	return sum;
}

int get_node_count(TreeNode* node) { // 노드의 개수 구하는 함수
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
		if (sum - root->key == 0) { // 리프노드에 도달했을때 0이 나오는 케이스가 있으면
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
	printf("\n0.종료\n");
	printf("1.검색\n");
	printf("2.삽입\n");
	printf("3.삭제\n");
	printf("4.IPL 계산\n");
	printf("5.평균 검색 성능 계산\n");
	printf("6.이진검색트리 판별\n");
	printf("7.경로의 값과 주어진 합의 경로가 있는지 판단\n");
	printf("번호를 입력하세요 : ");
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
			printf("\n프로그램을 종료합니다.\n");
			return 0;
		}
		case 1: {
			TreeNode* tree = NULL;
			int key;
			printf("\n검색할 키 입력: ");
			scanf("%d", &key);
			tree = search(T1, key);

			if (tree != NULL) {
				printf("찾은 키 값 : %d", tree->key);
				printf("\n");
			}
			else
				printf("\n찾은 키 값이 존재하지 않습니다.\n");
			break;
		}
		case 2: {
			int key;
			printf("\n삽입할 키 입력 : ");
			scanf("%d", &key);
			T1 = insert_node(T1, key);
			inorder(T1);
			printf("\n");
			break;
		}
		case 3: {
			int key;
			TreeNode* tree = NULL;
			printf("\n삭제할 키 입력 : ");
			scanf("%d", &key);

			tree = search(T1, key);
			if (tree != NULL) {
				T1 = delete_node(T1, key);
				printf("\n키 값 삭제 후 트리 출력\n");
				inorder(T1);
				printf("\n");
			}
			else
				printf("\n삭제할 키 값이 존재하지 않습니다.\n");
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

			printf("\n이진검색트리의 평균 검색 성능 : %.2f",avg);
			printf("\n");
			break;
		}
		case 6: {
			idx = 0;
			int num;
			printf("\n두 트리중 판별할 트리 선택\n");
			printf("1.T1\n");
			printf("2.T2\n");
			scanf("%d", &num);

			if (num == 1) {
				if (BST_check(T1, get_node_count(T1)) == 0) {
					printf("\n이진검색트리가 아닙니다.\n");
				}
				else
					printf("\n이진검색트리 입니다.\n");

			}
			else {
				if (BST_check(T2, get_node_count(T2)) == 0) {
					printf("\n이진검색트리가 아닙니다.\n");
				}
				else
					printf("\n이진검색트리 입니다.\n");
			}
			break;
		}
		case 7: {
			int sum;
			printf("\n합 입력: ");
			scanf("%d", &sum);
			if (hasPathSum(T2, sum) == 0) {
				printf("\n경로가 없습니다.\n");
			}
			else
				printf("\n경로가 있습니다.\n");
			break;
		}
		}
	}
	return 0;
}