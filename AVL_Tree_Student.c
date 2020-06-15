#include<stdio.h>
#include<stdlib.h>

typedef struct
{
	int id ;
	char name[50] , surname[50] , dept[20] ;
	float cgpa ;
} student ;

struct Node
{
	struct Node *left , *right ;
	int height ;
	student stu ;
} ;

int max( int a , int b)
{
	return (a>b)?a:b ;
}

int height(struct Node *N)
{
	if(N==NULL)
		return 0 ;
	return N->height ;
}

struct Node* newNode(student s)
{
	struct Node *node = (struct Node*)malloc(sizeof(struct Node)) ;
	node->left = NULL ;
	node->right = NULL ;
	node->height = 1 ;
	node->stu = s ;
	return node ;
}

struct Node *rightrotate(struct Node *y)
{
	struct Node *x = y->left ;
	struct Node *z = x->right ;
	
	x->right = y ;
	y->left = z ;
	
	x->height = max(height(x->right) , height(x->left)) + 1 ;
	y->height = max(height(y->right) , height(y->left)) + 1 ;
	
	return x ;
}

struct Node *leftrotate(struct Node *y)
{
	struct Node *x = y->right ;
	struct Node *z = x->left ;
	
	x->left = y ;
	y->right = z ;
	
	x->height = max(height(x->right) , height(x->left)) + 1 ;
	y->height = max(height(y->right) , height(y->left)) + 1 ;
	
	return x ;
}

int getBal(struct Node* N)
{
	if(N==NULL)
		return 0 ;
	return (height(N->left) - height(N->right)) ;
}

void inorder(struct Node *root)
{
	if(root!=NULL)
	{
		inorder(root->left) ;
		printf("%d\t%s\t%s\t%s\t%f\n" , root->stu.id , root->stu.name , root->stu.surname , root->stu.dept , root->stu.cgpa) ; 
		inorder(root->right) ;
	}
}

struct Node *insert(struct Node *node , student key)
{
	if(node==NULL)
		return(newNode(key)) ;
		
	if(key.id < node->stu.id)
		node->left = insert(node->left,key) ;
	else if(key.id > node->stu.id)
		node->right = insert(node->right,key) ;
	else return node ;
	
	node->height = 1 + max(height(node->left) , height(node->right)) ;
	
	int balance =  getBal(node) ;
	
	if(balance>1 && key.id < node->left->stu.id)
		return rightrotate(node) ;
	
	if(balance<-1 && key.id>node->right->stu.id)
		return leftrotate(node) ;
		
	if(balance>1 && key.id > node->left->stu.id)
	{
		node->left = leftrotate(node->left) ;
		return rightrotate(node) ;
	}
	
	if(balance<-1 && key.id<node->right->stu.id)
	{
		node->right = rightrotate(node->right) ;
		return leftrotate(node) ;
	}
	
	return node ;
}

void search(struct Node* root , int key)
{
	if(root!=NULL)
	{
		if(key < root->stu.id)
			search(root->left , key) ;
		else if(key > root->stu.id)
			search(root->right , key) ;
		else if( key == root->stu.id)
			printf("%d\t%s\t%s\t%s\t%f\n" , root->stu.id , root->stu.name , root->stu.surname , root->stu.dept , root->stu.cgpa) ;	
	}	
	else
		printf("Not found!\n") ;
}

int main()
{
	struct Node *root = NULL ; 
	student s1 ;
	int id , ch = 1;
	while(1)
	{
		printf("\n1. Enter data\n2. InOrder Traversal\n3. Search\n4. Exit\nEnter your choice : ") ;
		scanf("%d",&ch) ;
		switch(ch)
		{
			case 1 :
				printf("Enter data for student\n") ;
				printf("Enter ID : ") ;
				scanf("%d",&s1.id) ;
				printf("Enter name : ") ;
				scanf("%s",&s1.name) ;
				printf("Enter surname : ") ;
				scanf("%s",&s1.surname) ;
				printf("Enter department : ") ;
				scanf("%s",&s1.dept) ;
				printf("Enter CGPA : ") ;
				scanf("%f",&s1.cgpa) ;
				root = insert(root,s1) ;
				break ;
			case 2 :
				printf("Inorder traversal of AVL TREE : \n\n") ;
				inorder(root) ;
				break ;
			case 3 :
				printf("Enter ID : ") ;
				scanf("%d",&id) ;
				search(root , id) ;
				break ;
			case 4 :
				exit(1) ;
		}
	}
	return 0 ;
}
