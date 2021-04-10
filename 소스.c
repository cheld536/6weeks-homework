/*
 * singly linked list
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

 /* �ʿ��� ������� �߰� */

typedef struct Node {
	int key; 								//����� ������ �ʵ�
	struct Node* link;						//���� ��带 ����Ű�� ��ũ
} listNode;

typedef struct Head {
	struct Node* first;						// ��� ���
}headNode;


/* �Լ� ����Ʈ */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode = NULL;

	do {
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if (h != NULL)
		freeList(h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h) {
	/* h�� ����� listNode �޸� ����
	 * headNode�� �����Ǿ�� ��.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while (p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}



/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;
	h->first = node;

	return 0;
}


/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {

	listNode* prenode = (listNode*)malloc(sizeof(listNode));

	listNode* newnode;
	newnode = (listNode*)malloc(sizeof(listNode));       		// ����ڷκ��� �Է¹��� ���� �ӽ÷� ������ ���

	listNode* findnode;
	findnode = (listNode*)malloc(sizeof(listNode)); 				// ���� ��ġ�� �����ϴ� ������ ���

	newnode->key = key;											// ����ڷκ��� �Է¹��� ���� ��忡 �ӽ÷� ����
	prenode->link = NULL;

	if (h->first == NULL) // frist�� NULL�϶� first �� ���ο� ��带 ����Ű�� �Ѵ�.
	{
		insertFirst(h, key);
	}
	else if (h->first != NULL)   // first�� NULL�� �ƴҶ�
	{
		findnode->link = h->first;                        // findnode�� �ּҰ��� frist�� ����Ų��.
		prenode = h->first;

		while (findnode != NULL) {                      // findnode�� ���Ḯ��Ʈ�� Ž�� ���� �� NULL ���ö� ���� �ݺ�
			prenode = findnode;
			if (findnode->link == NULL) {            // findnode�� link�� null ���� Ž��
				
				if (newnode->key < findnode->key)
				{
					newnode->link = findnode->link;                     // newnode�� findnode�� link ���� ����Ų��.
					prenode->link = newnode;                        // findnode�� ��ũ�� newnode�� ����Ų��.
				}
				
				else {
					newnode->link = NULL;                           // newnode�� link�� NULL������ �ʱ�ȭ �ϰ�
					findnode->link = newnode;                        // �տ� �ִ� ����� link�� newnode�� ����Ű���Ѵ�.
				}
				break;
			}
			else
			{
				prenode = findnode->link;
				findnode = findnode->link;
			}

		}


	}


		return 0;
	}



/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {

	return 0;
}


/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {
	listNode* removenode = (listNode*)malloc(sizeof(listNode));
	removenode = h->first;
	h->first = removenode->link;
	free(removenode);
	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {
	
	return 0;

}

/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {
	listNode* removenode = (listNode*)malloc(sizeof(listNode));
	
	if (h->first == NULL)
		return;						// ���� ����Ʈ�� ���, ���� �ߴ�
	


	return 0;
}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {

	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while (p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}

