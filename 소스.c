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

typedef struct Head {						// ��� ���
	struct Node* first;						
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
		printf("----------- [ �� �� �� ] ------------ [ 2018038014 ] -----------\n");
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

	listNode* newnode;
	newnode = (listNode*)malloc(sizeof(listNode));       		// ����ڷκ��� �Է¹��� ���� �ӽ÷� ������ ���

	listNode* findnode;
	findnode = (listNode*)malloc(sizeof(listNode)); 				// ���� ��ġ�� �����ϴ� ������ ���

	newnode->key = key;											// ����ڷκ��� �Է¹��� ���� ��忡 �ӽ÷� ����


	if (h->first == NULL) // frist�� NULL�϶� first �� ���ο� ��带 ����Ű�� �Ѵ�.
	{
		insertFirst(h, key);
	}
	else if (h->first != NULL)   // first�� NULL�� �ƴҶ�
	{
		findnode = h->first;								  // findnode�� �ּҰ��� frist�� ����Ų��.
		while (findnode->link != NULL && findnode->link->key < key)	// ����ڷκ��� �Է� ���� ������ �۰ų� �� ���� ������ ������
		{
			findnode = findnode->link;						// ���� ����Ʈ�� �Ѿ��.
		}

		newnode->link = findnode->link;						// newnode.link�� findnode.link�� ����Ų��
		findnode->link = newnode;							// findnode.link�� ����Ű�� �ּҸ� newnode����Ʈ�� �����Ѵ�.
	}

	return 0;
}



/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {
	listNode* newNode = (listNode*)malloc(sizeof(listNode));		//������ ��带 �����Ҵ��Ѵ�.
	listNode* lastNode;												//����Ʈ�� ��尡 �����ϴ� ��� ��������� ������ ��´�.
	newNode->key = key;

	if (h->first == NULL)		// ���� ����Ʈ�� �����϶�
	{
		h->first = newNode;		// first�� newNode�� ����
		newNode->link = NULL;	// newNode.link�� NULL������ �ʱ�ȭ
		return 0;
	}
	lastNode = h->first;				//��� ����
	while (lastNode->link != NULL)		// lastNode�� �� ���� ���������� �̵�
		lastNode = lastNode->link;
	lastNode->link = newNode;			// �ΰ��� ã������ link�� newNode�� ����Ų��.
	newNode->link = NULL;				// newNode.link ���� NULL �ʱ�ȭ

	return 0;
}


/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {
	listNode* removenode = (listNode*)malloc(sizeof(listNode)); // ù ��° ��带 ���� ������ ��带 �����Ҵ� �޴´�.
	removenode = h->first;										// removernode�� h.first�� �ּҰ��� ���´�.
	h->first = removenode->link;								// h.first�� removernode.link�� �ű��.
	free(removenode);											// �޸� ����
	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {

	listNode* prenode;
	listNode* remove;

	if (h->first == NULL)
	{
		return 0;
	}
	else if (h->first->key == key) // key���� ù ��� �� ���
	{
		listNode* removenode1 = (listNode*)malloc(sizeof(listNode));				// �����Ҵ� 
		removenode1 = h->first;														// ��尡 ��带 ����Ų��.
		h->first = removenode1->link;												// ��尡 removenode1.link�� ����Ű�� ����Ʈ�� ����Ų��.
		free(removenode1);															// �޸� �Ҵ� ����
		return 0;
	}
	else {
		prenode = h->first;
		remove = h->first->link;
		while (remove->link != NULL && remove->link->key == key)						// remove ->link �� ���� �ƴҶ�����, ����ڰ� ã�� �� ���� Ž��
		{
			prenode = remove;														// removenode�� �ּҸ� prenode�� ����
			remove = remove->link;													// ���� ����Ʈ�� ã�´�.
		}

		prenode->link = remove->link;												// �����ϰ� �߰� ���� �����ϰ�  ��带 �̾��ش�.
	}

	return 0;

}

/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {
	listNode* removenode;			// ������ ��带 ���� ������
	listNode* prenode;				// �����ϱ��� ����� ������ �����ϴ� ������

	if (h->first == NULL)
		return 0;						// ���� ����Ʈ�� ���, ���� �ߴ�
	if (h->first->link == NULL)		// ����Ʈ�� ��尡 �Ѱ��� ���
	{
		free(h->first);				// ù��° ��� �޸� ����
		h->first = NULL;			// ����Ʈ ���� �����͸� null�� �����Ѵ�.
		return 0;
	}
	else                           // ����Ʈ�� ��尡 ������ �ִ� ���
	{
		prenode = h->first;					//���� ��尡 first�� ����Ų��.
		removenode = h->first->link;		//���� ��尡 first�� link�� ����Ų��.
		while (removenode->link != NULL)		// ����Ű�� ��ũ�� NULL���̸�
		{
			prenode = removenode;				// removenode�� �ּҸ� prenode�� ����
			removenode = removenode->link;		// ���� ����Ʈ�� ã�´�.
		}
		prenode->link = NULL;				//pre�� ����Ű�� �ִ� ��ũ�� NULL�θ����.


	}


	return 0;
}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {
	listNode* p;
	listNode* q;
	listNode* r;
	p = h->first;			// ������ p�� ù ��° ��忡 ����
	q = NULL;				// �ʱ�ȭ

	while (p != NULL) {		// ����Ʈ��ù ��° ������ ��ũ�� ���� ���� ���� �̵��ϸ鼭 ��尣 ������ �ٲ۴�.
		r = q;				// �ʱ�ȭ
		q = p;				// q�� p����� ������ ����
		p = p->link;		// ���� ��带 ã�´�.
		q->link = r;		// r�� ���� ���� �����Ѵ�.
	}
	h->first = q;
	return 0;
}

/*����Ʈ�� ���*/
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

