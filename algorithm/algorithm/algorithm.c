#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define max(a,b)    (((a) > (b)) ? (a) : (b))
#define MAX 500

typedef struct AvlNode
{
	int data; // key ��
	struct AvlNode* left_child, * right_child;
}AvlNode;
AvlNode* root;



AvlNode* rotate_LL(AvlNode* parent);
AvlNode* rotate_RR(AvlNode* parent);
AvlNode* rotate_RL(AvlNode* parent);
AvlNode* rotate_LR(AvlNode* parent);
int get_height(AvlNode* node);
int get_balance(AvlNode* node);
AvlNode* balance_tree(AvlNode** node);
AvlNode* avl_add(AvlNode** root, int key);
AvlNode* avl_search(AvlNode* node, int key);
void findnum(root);

int main()
{
	int* key;
	int num[MAX] = { 0, };
	int i, j;
	srand((unsigned)time(NULL));//���� �ʱ�ȭ
	key = (int*)malloc((sizeof(int)) * MAX);

	for (i = 0; i < MAX; i++)
	{// i�� 0���� MAX������ �ݺ�
		num[i] = rand() % MAX ; //0 ~ MAX-1���� �� �̱�
		for (j = 0; j < i; j++) {         //j�� 0���� i�� ���� ���� ���� �ݺ�.
			if (num[i] == num[j])  //�ߺ���
			{
				i--;  // ����
				break;
			}
		}
	}
	for (i = 0; i < MAX; i++){
		if (key) {
			key[i] = num[i];
		}
	}
	for (i = 0; i < MAX; i++) {
		if (key) {
			avl_add(&root, key[i]);
		}
	}
	findnum(root);
	return 0;
}

AvlNode* rotate_LL(AvlNode* parent)
{
	AvlNode* child = parent->left_child;
	parent->left_child = child->right_child;
	child->right_child = parent;
	return child;
}

AvlNode* rotate_RR(AvlNode* parent)
{
	AvlNode* child = parent->right_child;
	parent->right_child = child->left_child;
	child->left_child = parent;
	return child;
}

AvlNode* rotate_RL(AvlNode* parent)
{
	AvlNode* child = parent->right_child;
	parent->right_child = rotate_LL(child);
	return rotate_RR(parent);
}

AvlNode* rotate_LR(AvlNode* parent)
{
	AvlNode* child = parent->left_child;
	parent->left_child = rotate_RR(child);
	return rotate_LL(parent);
}

// Ʈ���� ���� ���� �Լ�

int get_height(AvlNode* node)
{
	int height = 0;
	if (node != NULL)
		height = 1 + max(get_height(node->left_child), get_height(node->right_child));
	return height;
}

// ����� �����μ� ��ȯ �Լ�

int get_balance(AvlNode* node)
{
	if (node == NULL) return 0;
	return get_height(node->left_child) - get_height(node->right_child);
}

// ���� Ʈ���� ����� �Լ�
AvlNode* balance_tree(AvlNode** node)
{
	int height_diff = get_balance(*node);

	if (height_diff > 1) // ���� ����Ʈ���� ������ �����
	{
		if (get_balance((*node)->left_child) > 0)
			*node = rotate_LL(*node);
		else
			*node = rotate_LR(*node);
	}
	else if (height_diff < -1) // ������ ����Ʈ���� ������ �����
	{
		if (get_balance((*node)->right_child) < 0)
			*node = rotate_RR(*node);
		else
			*node = rotate_RL(*node);
	}
	return *node;
}

// AVL Ʈ���� ���� ����

AvlNode* avl_add(AvlNode** root, int key)
{
	if (*root == NULL)
	{
		*root = (AvlNode*)malloc(sizeof(AvlNode));
		if (*root == NULL)
		{
			printf("�޸� �Ҵ� ����\n");
			exit(-1);
		}

		(*root)->data = key;
		(*root)->left_child = (*root)->right_child = NULL;
	}
	else if (key < (*root)->data)
	{
		(*root)->left_child = avl_add(&((*root)->left_child), key);
		(*root) = balance_tree(root);
	}
	else if (key > (*root)->data)
	{
		(*root)->right_child = avl_add(&((*root)->right_child), key);
		(*root) = balance_tree(root);
	}
	else
	{
		printf("�ߺ� Ű�� ���� ���� ����\n");
		exit(-1);
	}
	return *root;
}
AvlNode* avl_search(AvlNode* node, int key)
{
	if (node == NULL) return NULL;


	if (key == node->data) {
		return node;
	}
	else if (key < node->data)
		avl_search(node->left_child, key);
	else
		avl_search(node->right_child, key);
}

void findnum(root)
{
	clock_t start[MAX] = { 0 }, finish[MAX] = { 0 };

	int num[MAX] = { 0 };
	int state = 0, i;
	double result[MAX] = { 0 };
	double sum = 0;
	double avg = 0;
	int treeheight = 0;
	const char bar = '='; // ���α׷����� ����  
	const char blank = ' '; // ����ִ� ���α׷����� ����  
	const int LEN = 20; // ���α׷����� ����  
	const int SPEED = 50; // ī��Ʈ ���� ���ð�  
	int count = 0; // ���� ����� �۾�  
	float tick = (float)100 / LEN; // �� %���� ���α׷����� �߰����� ��� 
	int bar_count; // ���α׷����� ���� ���� ����  
	float percent; // �ۼ�Ʈ ���� ���� 

	FILE* fp;
	fp = fopen("AVL.txt", "a+");
	if (fp == NULL) {
		printf("���� ���� ���� \n");
		return;
	}
	for (i = 0; i < MAX; i++)
		num[i] = i;
	while (count < MAX) {
		i = count;
		start[i] = clock();
		avl_search(root, num[i]);
		finish[i] = clock();
		result[i] = (double)(finish[i] - start[i]) / CLOCKS_PER_SEC;
		sum += result[i];
		printf("\r%d/%d [", count, MAX); // ���� ���� ���  
		percent = (float)count / MAX * 100; // �ۼ�Ʈ ���  
		bar_count = percent / tick; // ���α׷����� ���� ���  
		for (i = 0; i < LEN; i++) { // LEN������ ���α׷����� ���  
			if (bar_count > i) { // ���α׷����� ���̺��� i�� ������ 
				printf("%c", bar);
			}
			else { // i�� �� Ŀ����  
				printf("%c", blank);
			}
		}
		printf("] %0.2f%%", percent); // �ۼ�Ʈ ���  
		count++;
		Sleep(SPEED); // SPEEDms ���  
	}
	avg = (double) sum / MAX;
	printf("_______________________\n"); //ping
	treeheight = get_height(root);
	/*fprintf(fp, "This is AVL program.\n");
	fprintf(fp, "_______________________\n");
	fprintf(fp, "1~%d\n", MAX);
	fprintf(fp, "Searching Time of AVG: %lf\n", avg);
	fprintf(fp, "BST High of AVG: %lf\n", treeheight);*/

	printf("This is AVL program.\n");
	printf("_______________________\n");
	printf("1~%d\n", MAX);
	printf("Searching Time of AVG: %lf\n", avg);
	printf("AVL High of AVG: %d\n", treeheight);

	fclose(fp);
}
