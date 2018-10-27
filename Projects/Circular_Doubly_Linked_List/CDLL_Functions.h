#include <time.h>

typedef enum
{
	FALSE, TRUE
} Boolean;

typedef struct Node
{
    int data;
    struct Node *next;
	struct Node *previous;
} Node;

typedef struct
{
    struct Node *head;
    struct Node *tail;
    int node_counter;
} Linked_List;

typedef struct
{
	int *stack_data_item;
	int top;
	int size;
} Stack;

typedef struct
{
	int *data_item;
	int front;
	int rear;
} Queue;
//------------------------Prototype Declarations-----------------------------------
void menu();
void enter_msg();
int dequeue(Queue *);
void error_data_msg();
void find_error_msg();
void print_empty_msg();
void print_valid_msg();
int pop_stack(Stack *);
void enter_valid_char();
void error_reverse_msg();
int delete_last(Linked_List *);
int delete_first(Linked_List *);
void enqueue(Queue *, int, int);
Boolean push_stack(Stack *, int);
Boolean sort(Linked_List *, char);
Boolean reverse_data(Linked_List *);
Boolean reverse_address(Linked_List *);
void initialization_list(Linked_List *);
void initialization_queue(Queue *, int);
void initialization_stack(Stack *, int );
int delete_target(Linked_List *, Node *);
Boolean insert_at_head(Linked_List *, int);
Boolean insert_at_tail(Linked_List *, int);
void print_linked_list(Linked_List *, char);
Boolean load_from_file(Linked_List *, char *);
Boolean insert_in_ascending(Linked_List *, int);
Boolean insert_in_descending(Linked_List *, int);
Boolean insert_after(Linked_List *, Node *, int);
Boolean insert_before(Linked_List *, Node *, int);
void print_linked_list_detail(Linked_List *, char);
Node *find_target(Linked_List *, int, Node **, Node **);
Boolean create_list_with_random(Linked_List *, int, int);
//---------------------------------------------------------------------------------
void menu()
{
    printf("*********************************************************\n");
    printf("*\t Doubly Circular Linked List Operations\t\t*\n"
    "*********************************************************\n"
    "*\t 0. Quit.\t\t\t\t\t*\n" // to terminate each node.
	"*\t 1. Show menu.\t\t\t\t\t*\n"
    "*\t 2. Insert at head.\t\t\t\t*\n" // inserting a new node as the first node.
    "*\t 3. Insert at tail.\t\t\t\t*\n" // inserting a new node as the last node.
    "*\t 4. Insert in ascending order.\t\t\t*\n"
    "*\t 5. Insert in descending order.\t\t\t*\n"
    "*\t 6. Load from file.\t\t\t\t*\n" // load integer data from file and will create the list by using insert_at_tail operation.
    "*\t 7. Create a List with random numbers.\t\t*\n"
    "*\t 8. Print List (detail).\t\t\t*\n" //printing the linked list in details including the data and pointer in each node.
    "*\t 9. Print List (data only).\t\t\t*\n"
    "*\t10. Find an integer.\t\t\t\t*\n" // finds if an integer exists in a node.
    "*\t11. Insert after a node.\t\t\t*\n"
    "*\t12. Insert before a node.\t\t\t*\n"
    "*\t13. Delete first node.\t\t\t\t*\n"
    "*\t14. Delete last node.\t\t\t\t*\n"
    "*\t15. Delete a target node.\t\t\t*\n"
    "*\t16. Delete after a target node.\t\t\t*\n"
    "*\t17. Delete before a target node.\t\t*\n"
	"*\t18. Reverse the List.\t\t\t\t*\n"
    "*\t19. Sort, unsorted data \t\t\t*\n");
    printf("*********************************************************\n\n");
}

void error_data_msg()
{
    printf("\nData could not be inserted!\n");
}

void find_error_msg()
{
    printf("\nTarget not found in the Linked List!\n\n");
}

void enter_msg()
{
    printf("Enter an integer: ");
}

void print_empty_msg()
{
	printf("\nThe linked list is empty!\n\n");
}

void print_valid_msg()
{
	printf("\nEnter valid choice!\n\n");
}

void error_reverse_msg()
{
	printf("\nLinked list could not be reversed!\n\n");
}

void enter_valid_char()
{
	printf("Enter valid character (Y/N)!\n");
}



void initialization_list(Linked_List *linked_list_ptr)
{
    linked_list_ptr->head = NULL;
    linked_list_ptr->tail = NULL;
    linked_list_ptr->node_counter = 0;
}


Boolean insert_at_head(Linked_List *linked_list_ptr, int new_data)
{
	Node *new_node_ptr = (Node *) malloc(sizeof(Node));

	if(new_node_ptr == NULL)
		return FALSE;

	new_node_ptr->data = new_data;

	if(linked_list_ptr->node_counter == 0)
	{
		new_node_ptr->next = new_node_ptr->previous = new_node_ptr;
		linked_list_ptr->head = linked_list_ptr->tail = new_node_ptr;
	}
	else
	{
		new_node_ptr->next = linked_list_ptr->head;
		new_node_ptr->previous = linked_list_ptr->tail;

		linked_list_ptr->head->previous = new_node_ptr;
		linked_list_ptr->head = new_node_ptr;

		linked_list_ptr->tail->next = new_node_ptr;
		linked_list_ptr->tail = new_node_ptr->previous;
	}

	linked_list_ptr->node_counter++;
	return TRUE;
}


Boolean insert_at_tail(Linked_List *linked_list_ptr, int new_data)
{
	Node *new_node_ptr = (Node *) malloc(sizeof(Node));

	if(new_node_ptr == NULL)
		return FALSE;

	new_node_ptr->data = new_data;

	if(linked_list_ptr->node_counter == 0)
	{
		new_node_ptr->next = new_node_ptr->previous = new_node_ptr;
		linked_list_ptr->head = linked_list_ptr->tail = new_node_ptr;
	}
	else
	{
		new_node_ptr->next = linked_list_ptr->head;
		new_node_ptr->previous = linked_list_ptr->tail;

		linked_list_ptr->head->previous = new_node_ptr;
		linked_list_ptr->head = new_node_ptr->next;

		linked_list_ptr->tail->next = new_node_ptr;
		linked_list_ptr->tail = new_node_ptr;
	}

	linked_list_ptr->node_counter++;
	return TRUE;
}


Boolean insert_in_ascending(Linked_List *linked_list_ptr, int new_data)
{
	if(linked_list_ptr->node_counter == 0)
	{
		if(!insert_at_head(linked_list_ptr, new_data))
			return FALSE;
	}
	else
	{
		Node *iterator = linked_list_ptr->head;

		if(new_data > iterator->data && linked_list_ptr->node_counter == 1)
		{
			if(!insert_at_tail(linked_list_ptr, new_data))
				return FALSE;
			else
				return TRUE;
		}

		for(register int i = 0; i < linked_list_ptr->node_counter; i++, iterator = iterator->next)
		{
			if(new_data <= iterator->data && iterator == linked_list_ptr->head)
			{
				if(!insert_at_head(linked_list_ptr, new_data))
					return FALSE;

				break;
			}
			else if(new_data <= iterator->next->data && iterator->next != linked_list_ptr->head)
			{
				Node *new_node_ptr = (Node *) malloc(sizeof(Node));

				if(new_node_ptr == NULL)
					return FALSE;

				new_node_ptr->data = new_data;

				new_node_ptr->next = iterator->next;
				new_node_ptr->previous = iterator;

				iterator->next->previous = new_node_ptr;
				iterator->next = new_node_ptr;

				linked_list_ptr->node_counter++;
				break;
			}
			else if(new_data > iterator->data && iterator->next == linked_list_ptr->tail)
			{
				if(!insert_at_tail(linked_list_ptr, new_data))
					return FALSE;

				break;
			}
		}
	}
	return TRUE;
}


Boolean insert_in_descending(Linked_List *linked_list_ptr, int new_data)
{
	if(linked_list_ptr->node_counter == 0)
	{
		if(!insert_at_head(linked_list_ptr, new_data))
			return FALSE;
	}
	else
	{
		Node *iterator = linked_list_ptr->head;

		if(new_data < iterator->data && linked_list_ptr->node_counter == 1)
		{
			if(!insert_at_tail(linked_list_ptr, new_data))
				return FALSE;
			else
				return TRUE;
		}

		for(register int i = 0; i < linked_list_ptr->node_counter; i++, iterator = iterator->next)
		{
			if(new_data >= iterator->data && iterator == linked_list_ptr->head)
			{
				if(!insert_at_head(linked_list_ptr, new_data))
					return FALSE;

				break;
			}
			else if(new_data >= iterator->next->data && iterator->next != linked_list_ptr->head)
			{
				Node *new_node_ptr = (Node *) malloc(sizeof(Node));

				if(new_node_ptr == NULL)
					return FALSE;

				new_node_ptr->data = new_data;

				new_node_ptr->next = iterator->next;
				new_node_ptr->previous = iterator;

				iterator->next->previous = new_node_ptr;
				iterator->next = new_node_ptr;

				linked_list_ptr->node_counter++;
				break;
			}
			else if(new_data < iterator->data && iterator->next == linked_list_ptr->tail)
			{
				if(!insert_at_tail(linked_list_ptr, new_data))
					return FALSE;

				break;
			}
		}
	}
	return TRUE;
}


Boolean load_from_file(Linked_List *linked_list_ptr, char *file_name)
{
	FILE *input_file = fopen(file_name, "r");

	if(input_file == NULL)
		return FALSE;
	else
	{
		int data;
		fscanf(input_file, "%d", &data);

		while(!feof(input_file))
		{
			insert_at_head(linked_list_ptr, data);
			fscanf(input_file, "%d", &data);
		}
	}
	fclose(input_file);
	return TRUE;
}


Boolean create_list_with_random(Linked_List *linked_list_ptr, int how_many, int end_num)
{
	srand(time(NULL));
	Boolean check_success;

	for(register int i = 0; i < how_many; i++)
		check_success = insert_at_tail(linked_list_ptr, (rand() % end_num));

	return check_success;
}


void print_linked_list(Linked_List *linked_list_ptr, char decision)
{
    if(linked_list_ptr->node_counter == 0)
    {
        print_empty_msg();
        return;
    }

	if(decision == 'N' || decision == 'n')
	{
		Node *iterator = linked_list_ptr->head;

		for(register int i = 0; i < linked_list_ptr->node_counter; i++, iterator = iterator->next)
			printf("%d\n", iterator->data);
	}
	else
	{
		Node *iterator = linked_list_ptr->tail;
		printf("\nThe Linked List Datas in Reverse:\n");

		for(register int i = 0; i < linked_list_ptr->node_counter; i++, iterator = iterator->previous)
			printf("%d\n", iterator->data);
	}
}


void print_linked_list_detail(Linked_List *linked_list_ptr, char decision)
{
    if(linked_list_ptr->node_counter == 0)
    {
        print_empty_msg();
        return;
    }

    printf("\nPrinting the linked list in details...\n");
	printf("\n Data Address\tPrevious Node Address\tData\t\tNext Node Address\n");

	if(decision == 'N' || decision == 'n')
	{
		Node *iterator = linked_list_ptr->head;

		for(register int i = 0; i < linked_list_ptr->node_counter; i++, iterator = iterator->next)
			printf("%d. (%p)\t[%p\t\t| %d |\t\t%p]\n", i + 1, iterator, iterator->previous, iterator->data,  iterator->next);
	}
	else
	{
		Node *iterator = linked_list_ptr->tail;

		for(register int i = 0; i < linked_list_ptr->node_counter; i++, iterator = iterator->previous)
			printf("%d. (%p)\t[%p\t\t| %d |\t\t%p]\n", i + 1, iterator, iterator->previous, iterator->data,  iterator->next);
	}

    printf("\nAddress of the Head Node: %p\n", linked_list_ptr->head);
    printf("Address of the Tail Node: %p\n\n", linked_list_ptr->tail);
}


Node *find_target(Linked_List *linked_list_ptr, int target, Node **next_ptr, Node **previous_ptr)
{
	if(linked_list_ptr->node_counter == 0)
		return NULL;

	Node *current = linked_list_ptr->head;
	*previous_ptr = *next_ptr = NULL;

	for(register int i = 0; i < linked_list_ptr->node_counter; i++, current = current->next)
	{
		*previous_ptr = current->previous;
		*next_ptr = current->next;

		if(current->data == target)
		  return current;

		if(current->data != target && current->next == linked_list_ptr->head)
		  return NULL;
	}
	return current;
}


Boolean insert_after(Linked_List *linked_list_ptr, Node *target_node, int new_data)
{
	if(target_node == linked_list_ptr->tail)
		return insert_at_tail(linked_list_ptr, new_data);
	else
	{
		Node *new_node_ptr = (Node *) malloc(sizeof(Node));

		if(new_node_ptr == NULL)
			return FALSE;

		new_node_ptr->data = new_data;

		new_node_ptr->previous = target_node;
		new_node_ptr->next = target_node->next;

		target_node->next->previous = new_node_ptr;
		target_node->next = new_node_ptr;
	}
	linked_list_ptr->node_counter++;
	return TRUE;
}


Boolean insert_before(Linked_List *linked_list_ptr, Node *target_node, int new_data)
{
	if(target_node == linked_list_ptr->head)
		return insert_at_head(linked_list_ptr, new_data);
	else
	{
		target_node = target_node->previous;

		if(!insert_after(linked_list_ptr, target_node, new_data))
			return FALSE;
	}
	return TRUE;
}


int delete_first(Linked_List *linked_list_ptr)
{
	Node *iterator = linked_list_ptr->head;
	int deleted_node_data = iterator->data;

	if(linked_list_ptr->node_counter == 0)
		return -99899;

	else if(linked_list_ptr->node_counter == 1)
		linked_list_ptr->head = linked_list_ptr->tail = NULL;

	else
	{
		linked_list_ptr->head = linked_list_ptr->tail->next = iterator->next;
		linked_list_ptr->head->previous = linked_list_ptr->tail;
	}

	free(iterator);
	linked_list_ptr->node_counter--;
	return deleted_node_data;
}


int delete_last(Linked_List *linked_list_ptr)
{
	Node *iterator = linked_list_ptr->tail;
	int deleted_node_data = iterator->data;

	if(linked_list_ptr->node_counter == 0)
		return -99899;

	else if(linked_list_ptr->node_counter == 1)
		linked_list_ptr->head = linked_list_ptr->tail = NULL;

	else
	{
		linked_list_ptr->tail = linked_list_ptr->head->previous = iterator->previous;
		linked_list_ptr->tail->next = linked_list_ptr->head;
		free(iterator);
	}

	linked_list_ptr->node_counter--;
	return deleted_node_data;
}


int delete_target(Linked_List *linked_list_ptr, Node *target_node)
{
	int deleted_node_data = target_node->data;

	if(linked_list_ptr->node_counter == 1)
		linked_list_ptr->head = linked_list_ptr->tail = NULL;

	else if(target_node == linked_list_ptr->head)
		return delete_first(linked_list_ptr);

	else if(target_node == linked_list_ptr->tail)
		return delete_last(linked_list_ptr);

	else
	{
		target_node->next->previous = target_node->previous;
		target_node->previous->next = target_node->next;
		free(target_node);
	}

	linked_list_ptr->node_counter--;
	return deleted_node_data;
}


int delete_after_target(Linked_List *linked_list_ptr, Node *target_node)
{
	int deleted_node_data = target_node->next->data;

	if(linked_list_ptr->node_counter == 1)
		linked_list_ptr->head = linked_list_ptr->tail = NULL;

	else if(target_node->next == linked_list_ptr->head)
		return delete_first(linked_list_ptr);

	else if(target_node->next == linked_list_ptr->tail)
		return delete_last(linked_list_ptr);

	else
	{
		target_node = target_node->next;
		target_node->previous->next = target_node->next;
		target_node->next->previous = target_node->previous;
		free(target_node);
	}

	linked_list_ptr->node_counter--;
	return deleted_node_data;
}


int delete_before_target(Linked_List *linked_list_ptr, Node *target_node)
{
	target_node = target_node->previous;
	int deleted_node_data;

	if(linked_list_ptr->node_counter == 1)
		linked_list_ptr->head = linked_list_ptr->tail = NULL;

	else if(target_node == linked_list_ptr->head)
		return delete_first(linked_list_ptr);

	else if(target_node == linked_list_ptr->tail)
		return delete_last(linked_list_ptr);

	else
	{
		target_node = target_node->previous;
		deleted_node_data = delete_after_target(linked_list_ptr, target_node);
	}

	return deleted_node_data;
}


void initialization_stack(Stack *stack_ptr, int stack_size)
{
	stack_ptr->stack_data_item = (int *) malloc(stack_size * sizeof(int));

	if(stack_ptr->stack_data_item == NULL)
	{
		printf("Unable to allocate memory now!\n");
		exit(1);
	}

	stack_ptr->top = -1;
	stack_ptr->size = stack_size;
}

Boolean push_stack(Stack *stack_ptr, int new_data)
{
	if(stack_ptr->top == stack_ptr->size - 1)
		return FALSE;

	stack_ptr->stack_data_item[++stack_ptr->top] = new_data;
	return TRUE;
}


int pop_stack(Stack *stack_ptr)
{
	if(stack_ptr->top == -1)
		return -989898;

	return stack_ptr->stack_data_item[stack_ptr->top--];
}


Boolean reverse_data(Linked_List *linked_list_ptr)
{
	Stack stack_object;
	initialization_stack(&stack_object, linked_list_ptr->node_counter);

	Node *iterator = linked_list_ptr->head;

	for(register int i = 0; i < linked_list_ptr->node_counter; i++, iterator = iterator->next)
	{
		if(!push_stack(&stack_object, iterator->data))
			return FALSE;
	}

	iterator = linked_list_ptr->head;

	for(register int i = 0; i < linked_list_ptr->node_counter; i++, iterator = iterator->next)
	{
		int temp = pop_stack(&stack_object);

		if(temp != -989898)
			iterator->data = temp;
		else
			return FALSE;
	}
	return TRUE;
}


Boolean reverse_address(Linked_List *linked_list_ptr)
{
	if (linked_list_ptr->node_counter <= 1)
		return FALSE;

	// declaring 3 Node pointers for doing the reversal
	Node *current, *previous_of_current, *next_of_current;

	previous_of_current = linked_list_ptr->tail;
	current = linked_list_ptr->head;
	next_of_current = current->next;

	while(1)
	{
		// reverse the link
		current->next = previous_of_current;

		if (current == linked_list_ptr->tail)
			break;

		// shift the pointers towards right
		previous_of_current = current;
		current = next_of_current;
		next_of_current = next_of_current->next;
	}
	Node *temp_tail = linked_list_ptr->tail;
	linked_list_ptr->tail = linked_list_ptr->head;
	linked_list_ptr->head = temp_tail;

	return TRUE;
}



void initialization_queue(Queue *queue_ptr, int queue_size)
{
	queue_ptr->data_item = (int *) malloc(queue_size * sizeof(int));

	if(queue_ptr->data_item == NULL)
	{
		printf("Unable to allocate memory now!\n");
		exit(1);
	}

	queue_ptr->front = 0;
	queue_ptr->rear = 0;
}


void enqueue(Queue *queue_ptr, int queue_size, int data)
{
	if(queue_ptr->rear == queue_size)
	{
		printf("Queue overflow!\n");
		exit(1);
	}

	queue_ptr->data_item[queue_ptr->rear++] = data;
}


int dequeue(Queue *queue_ptr)
{
	if(queue_ptr->rear == queue_ptr->front)
	{
		printf("Queue underflow!\n");
		exit(1);
	}

	return queue_ptr->data_item[queue_ptr->front++];
}


Boolean sort(Linked_List *linked_list_ptr, char choice)
{
	if(linked_list_ptr->node_counter == 0 || linked_list_ptr->node_counter == 1)
		return FALSE;

	Queue queue_object;
	int queue_size = linked_list_ptr->node_counter;
	initialization_queue(&queue_object, queue_size);
	
	for(Node *iterator = linked_list_ptr->head; linked_list_ptr->node_counter != 0; iterator = iterator->next)
		enqueue(&queue_object, queue_size, delete_first(linked_list_ptr));
	
	for(register int i = 0; i < queue_size; i++)
	{
		if(choice == '1')
			insert_in_ascending(linked_list_ptr, dequeue(&queue_object));
		else
			insert_in_descending(linked_list_ptr, dequeue(&queue_object));
	}
	
	return TRUE;
}