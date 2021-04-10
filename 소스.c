/*
 * singly linked list
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

 /* 필요한 헤더파일 추가 */

typedef struct Node {
	int key; 								//노드의 데이터 필드
	struct Node* link;						//다음 노드를 가르키는 링크
} listNode;

typedef struct Head {
	struct Node* first;						// 헤더 노드
}headNode;


/* 함수 리스트 */
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

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if (h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h) {
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
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
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;
	h->first = node;

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* prenode = (listNode*)malloc(sizeof(listNode));

	listNode* newnode;
	newnode = (listNode*)malloc(sizeof(listNode));       		// 사용자로부터 입력받은 값을 임시로 저장할 노드

	listNode* findnode;
	findnode = (listNode*)malloc(sizeof(listNode)); 				// 삽입 위치를 지정하는 포인터 노드

	newnode->key = key;											// 사용자로부터 입력받은 값을 노드에 임시로 저장
	prenode->link = NULL;

	if (h->first == NULL) // frist가 NULL일때 first 가 새로운 노드를 가르키게 한다.
	{
		insertFirst(h, key);
	}
	else if (h->first != NULL)   // first가 NULL이 아닐때
	{
		findnode->link = h->first;                        // findnode의 주소값을 frist로 가르킨다.
		prenode = h->first;

		while (findnode != NULL) {                      // findnode가 연결리스트를 탐색 했을 때 NULL 나올때 까지 반복
			prenode = findnode;
			if (findnode->link == NULL) {            // findnode의 link가 null 까지 탐색
				
				if (newnode->key < findnode->key)
				{
					newnode->link = findnode->link;                     // newnode가 findnode의 link 값을 가르킨다.
					prenode->link = newnode;                        // findnode의 링크가 newnode를 가르킨다.
				}
				
				else {
					newnode->link = NULL;                           // newnode의 link를 NULL값으로 초기화 하고
					findnode->link = newnode;                        // 앞에 있는 노드의 link가 newnode를 가르키게한다.
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
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	listNode* removenode = (listNode*)malloc(sizeof(listNode));
	removenode = h->first;
	h->first = removenode->link;
	free(removenode);
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	
	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	listNode* removenode = (listNode*)malloc(sizeof(listNode));
	
	if (h->first == NULL)
		return;						// 공백 리스트인 경우, 삭제 중단
	


	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
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

