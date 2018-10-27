typedef struct
{
	char *char_item;
	int top;
	int size;
} Stack;


void char_initialization(Stack *stack_pointer, int SIZE)
{
    stack_pointer->top = -1;
    stack_pointer->char_item = (char *) malloc(SIZE * sizeof(char));

    if(stack_pointer->char_item == NULL)
    {
        printf("Unable to allocate memory!\n");
        exit(1);
    }

    stack_pointer->size = SIZE;
}

short check_underflow(Stack *stack_pointer)
{
    return stack_pointer->top == -1;
}

short check_overflow(Stack *stack_pointer)
{
    return stack_pointer->top == stack_pointer->size -1;
}

void push_stack(Stack *stack_pointer, char ch_value)
{
	if (check_overflow(stack_pointer))
    {
        char *temp = (char *) malloc((stack_pointer->size + 1) * sizeof(char));

        if(temp == NULL)
        {
            printf("Unable to allocate memory!\n");
            exit(1);
        }

        for(register int i = 0; i <= stack_pointer->top; i++)
        {
            *(temp + i) = *(stack_pointer->char_item + i);
        }
        free(stack_pointer->char_item);

        stack_pointer->char_item = temp;
        stack_pointer->size++;
        stack_pointer->char_item[++stack_pointer->top] = ch_value;
    }
    else
        stack_pointer->char_item[++stack_pointer->top] = ch_value;
}

char pop_stack(Stack *stack_pointer)
{
    if(check_underflow(stack_pointer))
    {
		printf("\nStack underflow, terminating program...\n");
		exit(1);
    }
    else
    {
        char popped_value = stack_pointer->char_item[--stack_pointer->top];

        char *temp = (char *) malloc((stack_pointer->top + 1) * sizeof(char));

        if(temp == NULL)
        {
            printf("Unable to allocate memory!\n");
            exit(1);
        }

        for(register int i = 0; i <= stack_pointer->top; i++)
        {
            *(temp + i) = *(stack_pointer->char_item + i);
        }

        free(stack_pointer->char_item);
        stack_pointer->char_item = temp;
        stack_pointer->size = stack_pointer->top + 1;

        return popped_value;
    }
}

char top_stack(Stack *stack_pointer)
{
	if (check_underflow(stack_pointer))
	{
		printf("Stack underflow, terminating program\n");
		exit(1);
	}
	return stack_pointer->char_item[stack_pointer->top];
}

short check_parenthesis(char left, char right)
{
	short match = 0;
	switch(left)
	{
		case '(': if (right == ')')
					match = 1;
				  break;

		case '{': if (right == '}')
					match = 1;
				  break;

		case '[': if (right == ']')
					match = 1;
				  break;

		default: printf("\nInvalid symbol encountered, terminating program...\n");
				 exit(1);
	}
	return match;
}

short check_expression(char *expression, int SIZE)
{
	Stack stack_object;
	char_initialization(&stack_object, SIZE);

	short error = 0;

	for(register int i = 0; expression[i] != '\0'; i++)
	{
		if(expression[i] == '(' || expression[i] == '{' || expression[i] == '[')
			push_stack(&stack_object, expression[i]);

		else if(expression[i] == ')' || expression[i] == '}' || expression[i] == ']')
		{
			if(check_underflow(&stack_object))
			{
				error = 1;
				break;
			}
			else if(check_parenthesis(top_stack(&stack_object), expression[i]))
				pop_stack(&stack_object);

			else
			{
				error = 1;
				break;
			}
		}
	}

	if(!error && !check_underflow(&stack_object))
		error = 1;

	deallocate_stack(&stack_object);
	return error;
}

void deallocate_stack(Stack *stack_pointer)
{
    if(stack_pointer->char_item != NULL)
        free(stack_pointer->char_item);

    stack_pointer->top = -1;
    stack_pointer->size = 0;
}
