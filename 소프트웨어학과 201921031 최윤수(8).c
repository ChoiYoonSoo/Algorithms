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

void preorder(TreeNode* node) { // 전위순회 출력
	if (node != NULL) {
		printf("[%d] ", node->key);
		preorder(node->left);
		preorder(node->right);
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
	sum = count + IPL(node->left, count + 1) + IPL(node->right, count + 1);
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

int get_heigth(TreeNode* ptr) { // 이진트리의 높이를 계산하는 함수
	int height = 0;

	if (ptr != NULL) {
		height = 1 + max(get_heigth(ptr->left), get_heigth(ptr->right));
	}

	return height;
}

TreeNode* rotate_right(TreeNode* parent) { // 오른쪽으로 회전시키는 함수
	TreeNode* child = parent->left;
	parent->left = child->right;
	child->right = parent;

	return child; // 새로운 루트 반환
}

TreeNode* rotate_left(TreeNode* parent) { // 왼쪽으로 회전시키는 함수
	TreeNode* child = parent->right;
	parent->right = child->left;
	child->left = parent;

	return child; // 새로운 루트 반환
}

int get_balance(TreeNode* node) { // 노드의 균형인수를 반환
	if (node == NULL) return 0;

	return get_heigth(node->left) - get_heigth(node->right);
}

TreeNode* insert(TreeNode* node, int key) { // 삽입 함수
	if (node == NULL) return new_node(key); // 트리가 공백이면 새로운 노드를 반환한다.

	if (node->key > key) // 그렇지 않으면 순환적으로 트리를 내려간다.
		node->left = insert(node->left, key);
	else if (node->key < key)
		node->right = insert(node->right, key);
	else
		return node; // 변경된 루트 포인터를 반환

	int balance = get_balance(node); // 노드들의 균형인수 재계산

	if (balance > 1 && key < node->left->key) { // 새로운 노드가 왼쪽 자식의 왼쪽에 추가되었으면 LL타입 처리
		printf("\n----------균형깨짐----------\n\n");
		printf("---------- LL회전 ----------\n");
		return rotate_right(node);
	}

	if (balance < -1 && key > node->right->key) { // 새로운 노드가 오른쪽 자식의 오른쪽에 추가되었으면 RR타입 처리
		printf("\n----------균형깨짐----------\n\n");
		printf("---------- RR회전 ----------\n");
		return rotate_left(node);
	}

	if (balance > 1 && key > node->left->key) // 새로운 노드가 왼쪽 자식의 오른쪽에 추가되었으면 LR타입 처리
	{
		printf("\n----------균형깨짐----------\n\n");
		printf("---------- LR회전 ----------\n\n");
		node->left = rotate_left(node->left);
		return rotate_right(node);
	}

	if (balance < -1 && key < node->right->key) // 새로운 노드가 오른쪽 자식의 왼쪽에 추가되었으면 RL타입 처리
	{
		printf("\n----------균형깨짐----------\n\n");
		printf("---------- RL회전 ----------\n\n");
		node->right = rotate_right(node->right);
		return rotate_left(node);
	}
	return node;
}

TreeNode* delete(TreeNode* root, int key) {

	if (root == NULL) return root;

	if (key < root->key) { // 삭제할 키가 더 작은 경우 왼쪽 서브트리
		root->left = delete(root->left, key);
	}
	else if (key > root->key) { // 삭제할 키가 더 큰 경우 오른쪽 서브트리
		root->right = delete(root->right, key);
	}

	else { // 키가 루트의 키와 같을경우 삭제할 노드
		if ((root->left == NULL) || (root->right == NULL)) { // 자식이 하나인 노드
			TreeNode* temp = NULL;

			if (temp == root->left) {
				temp = root->right;
			}
			else {
				temp = root->left;
			}

			if (temp == NULL) { // 자식이 없을 경우
				temp = root;
				root = NULL;
			}
			else {
				root = temp;
			}
		}
		else { // 자식이 두개인 노드일 경우
			TreeNode* temp = min_value_node(root->right); // 후계노드를 복사
			root->key = temp->key;
			root->right = delete(root->right, temp->key); // 후계자 삭제
		}
	}

	if (root == NULL) return root; // 노드가 하나뿐인 경우 루트 반환

	int balance = get_balance(root); // 노드의 균형계수
	
	if (balance > 1 && get_balance(root->left) >= 0) { // LL타입 처리
		printf("\n----------균형깨짐----------\n\n");
		printf("---------- LL회전 ----------\n");
		return rotate_right(root);
	}

	if (balance < -1 && get_balance(root->right) <= 0) { // RR타입 처리
		printf("\n----------균형깨짐----------\n\n");
		printf("---------- RR회전 ----------\n");
		return rotate_left(root);
	}

	if (balance > 1 && get_balance(root->left) < 0) // LR타입 처리
	{
		printf("\n----------균형깨짐----------\n\n");
		printf("---------- LR회전 ----------\n\n");
		root->left = rotate_left(root->left);
		return rotate_right(root);
	}

	if (balance < -1 && get_balance(root->right) > 0) // RL타입 처리
	{
		printf("\n----------균형깨짐----------\n\n");
		printf("---------- RL회전 ----------\n\n");
		root->right = rotate_right(root->right);
		return rotate_left(root);
	}
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
	printf("8.AVL트리 삽입\n");
	printf("9.AVL트리 삭제\n");
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

	TreeNode* T3 = NULL;
	TreeNode* T4 = NULL;

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
			printf("\nAVL 트리 IPL : %d", IPL(T4, 1));
			printf("\n");
			printf("\n이진검색트리 IPL : %d", IPL(T3, 1));
			printf("\n");
			break;
		}
		case 5: {
			int ipl = IPL(T4, 1);
			int cnt = get_node_count(T4);
			double avg = (double)ipl / cnt;

			printf("\nAVL트리의 평균 검색 성능 : %.2f", avg);
			printf("\n");

			int ipl2 = IPL(T3, 1);
			int cnt2 = get_node_count(T3);
			double avg2 = (double)ipl2 / cnt2;

			printf("\n이진검색트리의 평균 검색 성능 : %.2f", avg2);
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
		case 8: {
			int n = 1, key;
			while (1) {
				printf("\n---------------------------------%d번째 Key  --------------------------------------\n", n);
				scanf("%d", &key);
				if (key == 0) {
					break;
				}
				T4 = insert(T4, key);
				T3 = insert_node(T3, key);

				printf("\nAVL트리 %d 단계 >>>> ", n);
				preorder(T4);
				printf("\n");
				printf("\n현재 AVL 트리의 높이 : %d", get_heigth(T4));
				printf("\n");

				printf("\n이진검색트리 %d 단계 >>>> ", n);
				preorder(T3);
				printf("\n");
				printf("\n현재 이진검색트리의 높이 : %d", get_heigth(T3));
				printf("\n");
				n++;
			}
			printf("\nAVL트리 중위 순회 결과 \n\n");
			inorder(T4);
			printf("\n\n이진검색트리 중위 순회 결과 \n\n");
			inorder(T3);
			printf("\n");
			break;
		}
		case 9: {
			int n = 1, key;
			while (1) {
				printf("\n---------------------------------%d번째 삭제할 Key  --------------------------------------\n", n);
				scanf("%d", &key);
				if (key == 0) {
					break;
				}
				T4 = delete(T4, key);
				T3 = delete_node(T3, key);

				printf("\nAVL트리 %d 단계 >>>> ", n);
				preorder(T4);
				printf("\n");
				printf("\n현재 AVL 트리의 높이 : %d", get_heigth(T4));
				printf("\n");

				printf("\n이진검색트리 %d 단계 >>>> ", n);
				preorder(T3);
				printf("\n");
				printf("\n현재 이진검색트리의 높이 : %d", get_heigth(T3));
				printf("\n");
				n++;
			}
			printf("\nAVL트리 중위 순회 결과 \n\n");
			inorder(T4);
			printf("\n\n이진검색트리 중위 순회 결과 \n\n");
			inorder(T3);
			printf("\n");
			break;
		}
		}
	}
	return 0;
}