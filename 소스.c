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

typedef struct Head {						// 헤더 노드
	struct Node* first;						
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
		printf("----------- [ 김 윤 희 ] ------------ [ 2018038014 ] -----------\n");
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

	listNode* newnode;
	newnode = (listNode*)malloc(sizeof(listNode));       		// 사용자로부터 입력받은 값을 임시로 저장할 노드

	listNode* findnode;
	findnode = (listNode*)malloc(sizeof(listNode)); 				// 삽입 위치를 지정하는 포인터 노드

	newnode->key = key;											// 사용자로부터 입력받은 값을 노드에 임시로 저장


	if (h->first == NULL) // frist가 NULL일때 first 가 새로운 노드를 가르키게 한다.
	{
		insertFirst(h, key);
	}
	else if (h->first != NULL)   // first가 NULL이 아닐때
	{
		findnode = h->first;								  // findnode의 주소값을 frist로 가르킨다.
		while (findnode->link != NULL && findnode->link->key < key)	// 사용자로부터 입력 받은 값보다 작거나 널 값을 가지기 전까지
		{
			findnode = findnode->link;						// 다음 리스트로 넘어간다.
		}

		newnode->link = findnode->link;						// newnode.link가 findnode.link를 가르킨다
		findnode->link = newnode;							// findnode.link가 가르키는 주소를 newnode리스트로 변경한다.
	}

	return 0;
}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	listNode* newNode = (listNode*)malloc(sizeof(listNode));		//삽입할 노드를 동적할당한다.
	listNode* lastNode;												//리스트에 노드가 존재하는 경우 마지막노드 정보를 담는다.
	newNode->key = key;

	if (h->first == NULL)		// 현재 리스트가 공백일때
	{
		h->first = newNode;		// first를 newNode로 저장
		newNode->link = NULL;	// newNode.link를 NULL값으로 초기화
		return 0;
	}
	lastNode = h->first;				//헤드 부터
	while (lastNode->link != NULL)		// lastNode가 널 값을 만날때까지 이동
		lastNode = lastNode->link;
	lastNode->link = newNode;			// 널값을 찾았으면 link로 newNode를 가르킨다.
	newNode->link = NULL;				// newNode.link 값을 NULL 초기화

	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	listNode* removenode = (listNode*)malloc(sizeof(listNode)); // 첫 번째 노드를 지울 포인터 노드를 동적할당 받는다.
	removenode = h->first;										// removernode는 h.first의 주소값을 같는다.
	h->first = removenode->link;								// h.first를 removernode.link로 옮긴다.
	free(removenode);											// 메모리 해제
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	listNode* prenode;
	listNode* remove;

	if (h->first == NULL)
	{
		return 0;
	}
	else if (h->first->key == key) // key값이 첫 노드 일 경우
	{
		listNode* removenode1 = (listNode*)malloc(sizeof(listNode));				// 동적할당 
		removenode1 = h->first;														// 노드가 헤드를 가르킨다.
		h->first = removenode1->link;												// 헤드가 removenode1.link가 가르키는 리스트를 가르킨다.
		free(removenode1);															// 메모리 할당 해제
		return 0;
	}
	else {
		prenode = h->first;
		remove = h->first->link;
		while (remove->link != NULL && remove->link->key == key)						// remove ->link 가 널이 아닐때까지, 사용자가 찾는 값 까지 탐색
		{
			prenode = remove;														// removenode의 주소를 prenode에 저장
			remove = remove->link;													// 다음 리스트를 찾는다.
		}

		prenode->link = remove->link;												// 삭제하고 중간 값을 삭제하고  노드를 이어준다.
	}

	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	listNode* removenode;			// 삭제할 노드를 담을 포인터
	listNode* prenode;				// 삭제하기전 노드의 정보를 저장하는 포인터

	if (h->first == NULL)
		return 0;						// 공백 리스트인 경우, 삭제 중단
	if (h->first->link == NULL)		// 리스트에 노드가 한개인 경우
	{
		free(h->first);				// 첫번째 노드 메모리 해제
		h->first = NULL;			// 리스트 시작 포인터를 null로 설정한다.
		return 0;
	}
	else                           // 리스트에 노드가 여려개 있는 경우
	{
		prenode = h->first;					//이전 노드가 first를 가르킨다.
		removenode = h->first->link;		//제거 노드가 first의 link를 가르킨다.
		while (removenode->link != NULL)		// 가르키는 링크가 NULL값이면
		{
			prenode = removenode;				// removenode의 주소를 prenode에 저장
			removenode = removenode->link;		// 다음 리스트를 찾는다.
		}
		prenode->link = NULL;				//pre가 가르키고 있는 링크를 NULL로만든다.


	}


	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	listNode* p;
	listNode* q;
	listNode* r;
	p = h->first;			// 포인터 p를 첫 번째 노드에 설정
	q = NULL;				// 초기화

	while (p != NULL) {		// 리스트의첫 번째 노드부터 링크를 따라 다음 노드로 이동하면서 노드간 연결을 바꾼다.
		r = q;				// 초기화
		q = p;				// q에 p노드의 정보를 저장
		p = p->link;		// 다음 노드를 찾는다.
		q->link = r;		// r을 다음 노드로 지정한다.
	}
	h->first = q;
	return 0;
}

/*리스트를 출력*/
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

