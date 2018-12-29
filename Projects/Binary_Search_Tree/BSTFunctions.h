#include <time.h>

typedef enum
{
	false, true
} Boolean;

typedef struct BinarySearchTree
{
    int data;
    struct BinarySearchTree *left;
    struct BinarySearchTree *right;
} Node;

int nodeCounter = 0;
int maxData, minData;

void print_menu();
Node *get_min(Node *);
Node *get_max(Node *);
void print_valid_msg();
Node *create_node(int);
Node *delete_tree(Node *);
Boolean check_tree(Node *);
Node *delete_minimum(Node *);
Node *delete_maximum(Node *);
void inoder_traverse(Node *);
void preoder_traverse(Node *);
void postoder_traverse(Node *);
Node *delete_node(Node *, int);
Boolean check_data(Node *, int);
void insert_node(Node *, Node *);
Node *find_target_node(Node *, int);
void not_found_target_data_msg(int);
void reverse_inoder_traverse(Node *);
Node *get_successor(Node *, Node *, int);
Node *get_predecessor(Node *, Node *, int);
Node *create_bst_randomly(Node *, int, int);

void print_menu()
{
    printf("\n0. Terminate the program."
           "\n1. Show menu."
           "\n2. Enter an integer by creating new node."
		   "\n3. Create a binary search tree by assinging random integers."
           "\n4. Traverse inorder."
           "\n5. Traverse inorder reversely."
           "\n6. Traverse preorder."
           "\n7. Traverse postorder."
		   "\n8. Get minimum integer."
		   "\n9. Get maximum integer."
		   "\n10. Find a target data."
           "\n11. Delete a node by finding target integer."
		   "\n12. Delete minimum integer."
		   "\n13. Delete maximum integer."
		   "\n14. Delete all nodes in the tree."
		   "\n15. Find predessor and successor of a target node."
		   "\n16. Show how many nodes in the tree.");
}

void print_valid_msg()
{
	printf("\nEnter a valid choice!\n\n");
}

void not_found_target_data_msg(int data)
{
	printf("%d is not in the tree.\n", data);
}

Boolean check_tree(Node *rootNodePtr)
{
	if(rootNodePtr == NULL)
	{
		printf("\nTree is empty!\n");
		return false;
	}
	
	return true;
}

Node *create_node(int newData)
{
    Node *newNodePtr = (Node *) malloc(sizeof(Node));
    newNodePtr->data = newData;
    newNodePtr->left = newNodePtr->right = NULL;
	nodeCounter++;
	
	if(minData >= newData)
		minData = newData;
	
	if(maxData <= newData)
		maxData = newData;
	
    return newNodePtr;
}

void insert_node(Node *rootNodePtr, Node *tempNodePtr)
{
    if(tempNodePtr->data < rootNodePtr->data)
    {		
        if(rootNodePtr->left != NULL)
            insert_node(rootNodePtr->left, tempNodePtr);
        else
            rootNodePtr->left = tempNodePtr;
    }
    else
    {
        if(rootNodePtr->right != NULL)
            insert_node(rootNodePtr->right, tempNodePtr);
        else
            rootNodePtr->right = tempNodePtr;
    }
}

Node *create_bst_randomly(Node *rootNodePtr, int howManyNode, int endNum)
{
	srand(time(NULL));

	for(register int i = 0; i < howManyNode; i++)
	{
		Node *tempNodePtr = create_node((rand() % endNum));
		
		if(rootNodePtr == NULL)
		{
			maxData = minData = tempNodePtr->data;
			rootNodePtr = tempNodePtr;
		}
		else
			insert_node(rootNodePtr, tempNodePtr);
	}
	
	return rootNodePtr;
}

void inoder_traverse(Node *rootNodePtr)
{
	if(rootNodePtr != NULL)
	{
		inoder_traverse(rootNodePtr->left);
		printf("%d --> ", rootNodePtr->data);
		inoder_traverse(rootNodePtr->right);
	}
}

void reverse_inoder_traverse(Node *rootNodePtr)
{
	if(rootNodePtr != NULL)
	{
		reverse_inoder_traverse(rootNodePtr->right);
		printf("%d --> ", rootNodePtr->data);
		reverse_inoder_traverse(rootNodePtr->left);
	}
}

void preoder_traverse(Node *rootNodePtr)
{
	if(rootNodePtr != NULL)
	{
		printf("%d --> ", rootNodePtr->data);
		preoder_traverse(rootNodePtr->left);
		preoder_traverse(rootNodePtr->right);
	}
}

void postoder_traverse(Node *rootNodePtr)
{
	if(rootNodePtr != NULL)
	{
		postoder_traverse(rootNodePtr->left);
		postoder_traverse(rootNodePtr->right);
		printf("%d --> ", rootNodePtr->data);
	}
}

Node *get_min(Node *rootNodePtr)
{
	if(rootNodePtr->left == NULL)
		return rootNodePtr;
	
	return get_min(rootNodePtr->left);
}

Node *get_max(Node *rootNodePtr)
{
	if(rootNodePtr->right == NULL)
		return rootNodePtr;
	
	return get_max(rootNodePtr->right);
}

Boolean check_data(Node *rootNodePtr, int targetData)
{
	if(targetData == rootNodePtr->data)
		return true;
	else if(targetData < rootNodePtr->data && rootNodePtr->left != NULL)
		return check_data(rootNodePtr->left, targetData);
	else if(targetData > rootNodePtr->data && rootNodePtr->right != NULL)
		return check_data(rootNodePtr->right, targetData);
	
	return false;
}

Node *delete_node(Node *rootNodePtr, int targetData)
{
	if(rootNodePtr == NULL)
	{
		not_found_target_data_msg(targetData);
		return rootNodePtr;
	}
	
	if(targetData < rootNodePtr->data)
		rootNodePtr->left = delete_node(rootNodePtr->left, targetData);
	else if(targetData > rootNodePtr->data)
		rootNodePtr->right = delete_node(rootNodePtr->right, targetData);
	else
	{ //we have found the target node that we want to remove
		if(rootNodePtr->left == NULL && rootNodePtr->right == NULL)
		{
			printf("A leaf node is deleted.\n");
			free(rootNodePtr);
			nodeCounter--;
			return NULL;
		}
		else if(rootNodePtr->left == NULL || rootNodePtr->right == NULL) //Target node has 1 child case
		{
			Node *tempNodePtr;
			
			if(rootNodePtr->left == NULL)
				tempNodePtr = rootNodePtr->right;
			else
				tempNodePtr = rootNodePtr->left;
			
			printf("A parent node is deleted, which has 1 child.\n");
			free(rootNodePtr);
			nodeCounter--;
			return tempNodePtr;
		}
		else //This is the target with two children case
		{
			printf("A parent node is deleted, which has 2 children.\n");
				
			if((rand() % 2) == 0)
			{
				Node *tempNodePtr = get_max(rootNodePtr->left);
				rootNodePtr->data = tempNodePtr->data;
				rootNodePtr->left = delete_node(rootNodePtr->left, tempNodePtr->data);
			}
			else
			{
				Node *tempNodePtr = get_min(rootNodePtr->right);
				rootNodePtr->data = tempNodePtr->data;
				rootNodePtr->right = delete_node(rootNodePtr->right, tempNodePtr->data);
			}
		}
	}
	return rootNodePtr;
}

Node *delete_minimum(Node *rootNodePtr)
{
	if(rootNodePtr->left != NULL)
		rootNodePtr->left = delete_minimum(rootNodePtr->left);
	else
	{
		if(rootNodePtr->left == NULL && rootNodePtr->right == NULL)
		{
			printf("Minimum integer is deleted.\n");
			free(rootNodePtr);
			nodeCounter--;
			return NULL;
		}
		else
		{
			Node *tempNodePtr = rootNodePtr->right;
			printf("Minimum integer is deleted, which has 1 child.\n");
			free(rootNodePtr);
			nodeCounter--;
			return tempNodePtr;
		}
	}
	
	return rootNodePtr;
}

Node *delete_maximum(Node *rootNodePtr)
{
	if(rootNodePtr->right != NULL)
		rootNodePtr->right = delete_minimum(rootNodePtr->right);
	else
	{
		if(rootNodePtr->left == NULL && rootNodePtr->right == NULL)
		{
			printf("Maximum integer is deleted.\n");
			free(rootNodePtr);
			nodeCounter--;
			return NULL;
		}
		else
		{
			Node *tempNodePtr = rootNodePtr->left;
			printf("Maximum integer is deleted, which has 1 child.\n");
			free(rootNodePtr);
			nodeCounter--;
			return tempNodePtr;
		}
	}
	
	return rootNodePtr;
}

Node *delete_tree(Node *rootNodePtr)
{
	while(nodeCounter != 0)
		rootNodePtr = delete_minimum(rootNodePtr);
	
	return rootNodePtr;
}

Node *find_target_node(Node *rootNodePtr, int targetData)
{
	if(targetData == rootNodePtr->data)
		return rootNodePtr;
	else if(targetData < rootNodePtr->data && rootNodePtr->left != NULL)
		return find_target_node(rootNodePtr->left, targetData);
	else if(targetData > rootNodePtr->data && rootNodePtr->right != NULL)
		return find_target_node(rootNodePtr->right, targetData);
	
	return NULL;
}

Node *get_successor(Node *successorPtr, Node *rootNodePtr, int targetData)
{
	if(successorPtr->right != NULL)
		return get_min(successorPtr->right);
	
	while(rootNodePtr != NULL)
	{
		if(targetData < rootNodePtr->data)
		{
			successorPtr = rootNodePtr;
			rootNodePtr = rootNodePtr->left;
		}
		else if(targetData > rootNodePtr->data)
			rootNodePtr = rootNodePtr->right;
		else
			break;
	}
	
	return successorPtr;
}

Node *get_predecessor(Node *predecessorPtr, Node *rootNodePtr, int targetData)
{
	if(predecessorPtr->left != NULL)
		return get_max(predecessorPtr->left);
	
	while(rootNodePtr != NULL)
	{
		if(targetData > rootNodePtr->data)
		{
			predecessorPtr = rootNodePtr;
			rootNodePtr = rootNodePtr->right;
		}
		else if(targetData < rootNodePtr->data)
			rootNodePtr = rootNodePtr->left;
		else
			break;
	}
	
	return predecessorPtr;
}