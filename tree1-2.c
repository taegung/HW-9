/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	do {printf("\n");
        printf("[2019038059                    윤태경]\n");
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);//command 입력

		switch (command) {
		case 'z': case 'Z'://z또는 z를 입력한경우
			initializeBST(&head);
			break;
		case 'q': case 'Q'://q또는 Q를 입력한경우
			freeBST(head);
			break;
		case 'n': case 'N'://n또는N을 입력한경우
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D'://d또는 D를 입력한경우
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F'://f또는 F를 입력한경우
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S'://s또는 S를 입력한경우
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I'://i또는 I를 입력한경우
			inorderTraversal(head->left);
			break;
		case 'p': case 'P'://p또는 P를 입력한경우
			preorderTraversal(head->left);
			break;
		case 't': case 'T'://t또는 T를 입력한경우
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if (*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));//포인터변수h에 구조체 node만큼 메모리할당
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)
{
	if (ptr) {
		inorderTraversal(ptr->left);//재귀함수를 통하여 ptr이 왼쪽자식을 가르킴
		printf(" [%d] ", ptr->key);//ptr의 key값 출력
		inorderTraversal(ptr->right);//재귀함수를 통하여 ptr이 오른쪽을 가르킴
	}
  
}

void preorderTraversal(Node* ptr)
{
	if (ptr) {
		printf(" [%d] ", ptr->key);//ptr의 key값 출력
		preorderTraversal(ptr->left);//재귀함수를 통하여 ptr이 왼쪽자식을 가르킴
		preorderTraversal(ptr->right);//재귀함수를 통하여 ptr이 오른쪽을 가르킴
	}
     
}


void postorderTraversal(Node* ptr)
{
	if (ptr) {
		postorderTraversal(ptr->left);//재귀함수를 통하여 ptr이 왼쪽자식을 가르킴
		postorderTraversal(ptr->right);//재귀함수를 통하여 ptr이 오른쪽을 가르킴
		printf(" [%d] ", ptr->key);//ptr의 key값 출력
	}
    
}



int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));//입력받은 key값을 넣을 새로운 노드 생성
	newNode->key = key;//Newnode->key에 입력받은 key값 대입
	newNode->left = NULL;//newNode->left은 NULL
	newNode->right = NULL;//newNode->right은 NULL

	if (head->left == NULL) {//입력받은 노드가없다면 즉 처음 노드를 입력하면
		head->left = newNode;//head->left에 newnode연결
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;//ptr은 head->left가 가르키는 노드

	Node* parentNode = NULL;//parentNode를 NULL로설정
	while (ptr != NULL) {//ptr이 NULL이 아닐때 까지 반복

		/* if there is a node for the key, then just return */
		if (ptr->key == key) return 1;//ptr의key값이랑 입력받은 key값이 같은경우 함수 종료

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;//parentNode가 ptr노드랑 같게해줌

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if (ptr->key < key)//ptr의 key값이 입력받은 key값보다 작은경우
			ptr = ptr->right;//ptr을 ptr->right로 바꿔줌 만약 ptr->right가 NULL이라면 while문 탈출
		else//ptr의 key값이 입력받은 key값보다 큰경우
			ptr = ptr->left;//ptr을 ptr->left로 바꿔줌 만약 ptr->left가 NULL이라면 while문 탈출
	}

	/* linking the new node to the parent */
	if (parentNode->key > key)//parentNode의 key값이 입력받은 key값보다 작은경우
		parentNode->left = newNode;//parentNode의 왼쪽자식을 새로만든 노드로 만듬
	else
		parentNode->right = newNode;//parentNode의 오르쪽자식을 새로만든 노드로 만듬
	return 1;
}

int deleteLeafNode(Node* head, int key)
{
	if (head == NULL) {//head를 생성하지 않을경우 오류메세지 출력
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) {//입력받은 노드가 없을경우 오류 메세지 출력
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	/* head->left is the root */
	Node* ptr = head->left;//ptr을 head->left를 가르키게함


	/* we have to move onto children nodes,
	 * keep tracking the parent using parentNode */
	Node* parentNode = head;//parentNode를 head노드로 설정

	while (ptr != NULL) {//ptr이 NULL이 될떄 까지 반복

		if (ptr->key == key) {//ptr의key값이 입력받은 key값이랑 같은경우
			if (ptr->left == NULL && ptr->right == NULL) {//ptr->left랑 ptr->right가 NULL일떄 실행 즉 ptr의 자식노드가 없을때실행

				/* root node case */
				if (parentNode == head)//입력받은 노드가 하나일때 그노드를 삭제할려할때
					head->left = NULL;//head->left를 NULL해줌 

				/* left node case or right case*/
				if (parentNode->left == ptr)//parentNode->left가ptr일때
					parentNode->left = NULL;//parentNode->left을 NULL해줌
				else//parentNode->right가ptr일때
					parentNode->right = NULL;//parentNode->right을 NULL해줌

				free(ptr);
			}
			else {
				printf("the node [%d] is not a leaf \n", ptr->key);//입력받은 key값이 없다
			}
			return 1;
		}

		/* keep the parent node */
		parentNode = ptr;//parentNode가 ptr노드랑 같게해줌

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if (ptr->key < key)//ptr->key값이 입력받은 key값보다 작은경우
			ptr = ptr->right;//ptr을 ptr->right로 바꿔줌
		else//ptr->key값이 입력받은 key값보다 큰경우
			ptr = ptr->left;//ptr을 ptr->left로 바꿔줌


	}

	printf("Cannot find the node for key [%d]\n ", key);//입력받은 key값이 없다는 메세지 출력
	return 1;
}
Node* searchRecursive(Node* ptr, int key)//재귀함수를 사용해서 key값 찾기
{
	if (ptr == NULL)
		return NULL;

	if (ptr->key < key)//ptr의key값이 key값보다 작은경우
		ptr = searchRecursive(ptr->right, key);//재귀함수를 통해서 ptr값을 ptr->right로 바꿔줌
	else if (ptr->key > key)//ptr의key값이 key값보다 큰경우
		ptr = searchRecursive(ptr->left, key);//재귀함수를 통해서 ptr값을 ptr->left로 바꿔줌

	/* if ptr->key == key */
	return ptr;//ptr리턴

}
Node* searchIterative(Node* head, int key)
{
	/* root node */
	Node* ptr = head->left;//ptr=head->left로 설정

	while (ptr != NULL)//ptr이 NULL이 아닐때 까지반복
	{
		if (ptr->key == key)//ptr의key값이 입력받은 key값이랑 같으면
			return ptr;//ptr리턴

		if (ptr->key < key) ptr = ptr->right;//ptr의key값이 key값보다 작은경우 ptr을 ptr->right로 바까줌
		else//ptr의key값이 key값보다 큰경우
			ptr = ptr->left;//ptr을 ptr->left로 바까줌
	}

	return NULL;
}




