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
        printf("[2019038059                    ���°�]\n");
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
		scanf(" %c", &command);//command �Է�

		switch (command) {
		case 'z': case 'Z'://z�Ǵ� z�� �Է��Ѱ��
			initializeBST(&head);
			break;
		case 'q': case 'Q'://q�Ǵ� Q�� �Է��Ѱ��
			freeBST(head);
			break;
		case 'n': case 'N'://n�Ǵ�N�� �Է��Ѱ��
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D'://d�Ǵ� D�� �Է��Ѱ��
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F'://f�Ǵ� F�� �Է��Ѱ��
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S'://s�Ǵ� S�� �Է��Ѱ��
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I'://i�Ǵ� I�� �Է��Ѱ��
			inorderTraversal(head->left);
			break;
		case 'p': case 'P'://p�Ǵ� P�� �Է��Ѱ��
			preorderTraversal(head->left);
			break;
		case 't': case 'T'://t�Ǵ� T�� �Է��Ѱ��
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
	*h = (Node*)malloc(sizeof(Node));//�����ͺ���h�� ����ü node��ŭ �޸��Ҵ�
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)
{
	if (ptr) {
		inorderTraversal(ptr->left);//����Լ��� ���Ͽ� ptr�� �����ڽ��� ����Ŵ
		printf(" [%d] ", ptr->key);//ptr�� key�� ���
		inorderTraversal(ptr->right);//����Լ��� ���Ͽ� ptr�� �������� ����Ŵ
	}
  
}

void preorderTraversal(Node* ptr)
{
	if (ptr) {
		printf(" [%d] ", ptr->key);//ptr�� key�� ���
		preorderTraversal(ptr->left);//����Լ��� ���Ͽ� ptr�� �����ڽ��� ����Ŵ
		preorderTraversal(ptr->right);//����Լ��� ���Ͽ� ptr�� �������� ����Ŵ
	}
     
}


void postorderTraversal(Node* ptr)
{
	if (ptr) {
		postorderTraversal(ptr->left);//����Լ��� ���Ͽ� ptr�� �����ڽ��� ����Ŵ
		postorderTraversal(ptr->right);//����Լ��� ���Ͽ� ptr�� �������� ����Ŵ
		printf(" [%d] ", ptr->key);//ptr�� key�� ���
	}
    
}



int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));//�Է¹��� key���� ���� ���ο� ��� ����
	newNode->key = key;//Newnode->key�� �Է¹��� key�� ����
	newNode->left = NULL;//newNode->left�� NULL
	newNode->right = NULL;//newNode->right�� NULL

	if (head->left == NULL) {//�Է¹��� ��尡���ٸ� �� ó�� ��带 �Է��ϸ�
		head->left = newNode;//head->left�� newnode����
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;//ptr�� head->left�� ����Ű�� ���

	Node* parentNode = NULL;//parentNode�� NULL�μ���
	while (ptr != NULL) {//ptr�� NULL�� �ƴҶ� ���� �ݺ�

		/* if there is a node for the key, then just return */
		if (ptr->key == key) return 1;//ptr��key���̶� �Է¹��� key���� ������� �Լ� ����

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;//parentNode�� ptr���� ��������

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if (ptr->key < key)//ptr�� key���� �Է¹��� key������ �������
			ptr = ptr->right;//ptr�� ptr->right�� �ٲ��� ���� ptr->right�� NULL�̶�� while�� Ż��
		else//ptr�� key���� �Է¹��� key������ ū���
			ptr = ptr->left;//ptr�� ptr->left�� �ٲ��� ���� ptr->left�� NULL�̶�� while�� Ż��
	}

	/* linking the new node to the parent */
	if (parentNode->key > key)//parentNode�� key���� �Է¹��� key������ �������
		parentNode->left = newNode;//parentNode�� �����ڽ��� ���θ��� ���� ����
	else
		parentNode->right = newNode;//parentNode�� �������ڽ��� ���θ��� ���� ����
	return 1;
}

int deleteLeafNode(Node* head, int key)
{
	if (head == NULL) {//head�� �������� ������� �����޼��� ���
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) {//�Է¹��� ��尡 ������� ���� �޼��� ���
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	/* head->left is the root */
	Node* ptr = head->left;//ptr�� head->left�� ����Ű����


	/* we have to move onto children nodes,
	 * keep tracking the parent using parentNode */
	Node* parentNode = head;//parentNode�� head���� ����

	while (ptr != NULL) {//ptr�� NULL�� �ɋ� ���� �ݺ�

		if (ptr->key == key) {//ptr��key���� �Է¹��� key���̶� �������
			if (ptr->left == NULL && ptr->right == NULL) {//ptr->left�� ptr->right�� NULL�ϋ� ���� �� ptr�� �ڽĳ�尡 ����������

				/* root node case */
				if (parentNode == head)//�Է¹��� ��尡 �ϳ��϶� �׳�带 �����ҷ��Ҷ�
					head->left = NULL;//head->left�� NULL���� 

				/* left node case or right case*/
				if (parentNode->left == ptr)//parentNode->left��ptr�϶�
					parentNode->left = NULL;//parentNode->left�� NULL����
				else//parentNode->right��ptr�϶�
					parentNode->right = NULL;//parentNode->right�� NULL����

				free(ptr);
			}
			else {
				printf("the node [%d] is not a leaf \n", ptr->key);//�Է¹��� key���� ����
			}
			return 1;
		}

		/* keep the parent node */
		parentNode = ptr;//parentNode�� ptr���� ��������

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if (ptr->key < key)//ptr->key���� �Է¹��� key������ �������
			ptr = ptr->right;//ptr�� ptr->right�� �ٲ���
		else//ptr->key���� �Է¹��� key������ ū���
			ptr = ptr->left;//ptr�� ptr->left�� �ٲ���


	}

	printf("Cannot find the node for key [%d]\n ", key);//�Է¹��� key���� ���ٴ� �޼��� ���
	return 1;
}
Node* searchRecursive(Node* ptr, int key)//����Լ��� ����ؼ� key�� ã��
{
	if (ptr == NULL)
		return NULL;

	if (ptr->key < key)//ptr��key���� key������ �������
		ptr = searchRecursive(ptr->right, key);//����Լ��� ���ؼ� ptr���� ptr->right�� �ٲ���
	else if (ptr->key > key)//ptr��key���� key������ ū���
		ptr = searchRecursive(ptr->left, key);//����Լ��� ���ؼ� ptr���� ptr->left�� �ٲ���

	/* if ptr->key == key */
	return ptr;//ptr����

}
Node* searchIterative(Node* head, int key)
{
	/* root node */
	Node* ptr = head->left;//ptr=head->left�� ����

	while (ptr != NULL)//ptr�� NULL�� �ƴҶ� �����ݺ�
	{
		if (ptr->key == key)//ptr��key���� �Է¹��� key���̶� ������
			return ptr;//ptr����

		if (ptr->key < key) ptr = ptr->right;//ptr��key���� key������ ������� ptr�� ptr->right�� �ٱ���
		else//ptr��key���� key������ ū���
			ptr = ptr->left;//ptr�� ptr->left�� �ٱ���
	}

	return NULL;
}




