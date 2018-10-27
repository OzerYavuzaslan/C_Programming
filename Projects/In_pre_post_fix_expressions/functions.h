#include <string.h>
#include <math.h>

//Creating Boolean Struct
typedef enum
{
	FALSE, TRUE
}Boolean;

//--------------------------Prototype declarations and their structs-------------------------
short assign_expression(char *, char *);

//-------------------------------------------------------------------------------------------
typedef struct
{
	char *parenthesis_item;
	int parenthesis_top;
	int parenthesis_size;
} Stack_Parenthesis;

short check_expression(char *, int);
Boolean check_parenthesis(char, char);
char parenthesis_pop(Stack_Parenthesis *);
short check_underflow(Stack_Parenthesis *);
char top_parenthesis_stack(Stack_Parenthesis *);
void parenthesis_push(Stack_Parenthesis *, char);
void parenthesis_initialization(Stack_Parenthesis *, int);

//-------------------------------------------------------------------------------------------
typedef struct
{
	char *char_item;
	int char_top;
	int char_size;
}Operator_Stack;

int num_of_parenthesis(char *);
Boolean precedence(char, char);
char operator_pop(Operator_Stack *);
Boolean prefix_precedence(char, char);
void operator_push(Operator_Stack *, char);
void char_initialization(Operator_Stack *, int);
void convert_infix_to_prefix(char *, char *, int);
void convert_infix_to_postfix(char *, char *, int);

//-------------------------------------------------------------------------------------------
typedef struct
{
	double *double_item;
	int double_top;
	int double_size;
}Operand_Stack;

double pop_operand(Operand_Stack *);
double evaluate_prefix(char *, int);
double operate(double, double, char);
double evaluate_postfix(char *, int);
double root_of_value(double, double);
void push_operand(Operand_Stack *, double);
void double_initialization(Operand_Stack *, int);

//-------------------------------------------------------------------------------------------

// Separate operands and operators with comma
short assign_expression(char *temp_expression, char *infix)
{
	short error = 1;

    for(register int i = 0, j = 0; temp_expression[i] != '\0'; i++, j++)
    {
		if((temp_expression[0] >= '0' && temp_expression[0] <= '9') || temp_expression[0] == '(')
		{
			if(j == 0 && temp_expression[0] != '(')
			{
				infix[j] = ',';
				i = -1;
			}

			else if(temp_expression[i] >= '0' && temp_expression[i] <= '9')
			{
				infix[j] = temp_expression[i];

				if(temp_expression[i + 1] == '+' || temp_expression[i + 1] == '-' || temp_expression[i + 1] == '*' || temp_expression[i + 1] == '/'
				|| temp_expression[i + 1] == '$' || temp_expression[i + 1] == '(' || temp_expression[i + 1] == ')')
					infix[++j] = ',';
			}

			else if(temp_expression[i] == '+' || temp_expression[i] == '-' || temp_expression[i] == '/' || temp_expression[i] == '*' ||
				   temp_expression[i] == '$' || temp_expression[i] == '(' || temp_expression[i] == ')')
			{
				infix[j] = temp_expression[i];

				if(temp_expression[i + 1] >= '0' && temp_expression[i + 1] <= '9')
					infix[++j] = ',';
			}

			if(temp_expression[i + 1] == '\0')
			{
				if(temp_expression[i] >= '0' && temp_expression[i] <= '9')
				{
					infix[j + 1] = ',';
					infix[j + 2] = '\0';
				}
				else
					infix[j + 1] = '\0';
			}
		}
		else
		{
			printf("\n\nYou can't start your expression with %c\n\n", temp_expression[0]);
			error = 0;
			break;
		}
	}
	return error;
}

//----------------------------------Checking parenthesis is valid--------------------------------------
void parenthesis_initialization(Stack_Parenthesis *stack_pointer, int SIZE)
{
    stack_pointer->parenthesis_top = -1;
    stack_pointer->parenthesis_item = (char *) malloc(SIZE * sizeof(char));

    if(stack_pointer->parenthesis_item == NULL)
    {
        printf("\nUnable to allocate memory!\n");
        exit(1);
    }

    stack_pointer->parenthesis_size = SIZE;
}

short check_underflow(Stack_Parenthesis *stack_pointer)
{
    return stack_pointer->parenthesis_top == -1;
}

void push_stack(Stack_Parenthesis *stack_pointer, char ch_value)
{
	if (stack_pointer->parenthesis_top == stack_pointer->parenthesis_size - 1)
    {
        char *temp = (char *) malloc((stack_pointer->parenthesis_size + 1) * sizeof(char));

        if(temp == NULL)
        {
            printf("\nUnable to allocate memory!\n");
            exit(1);
        }

        for(register int i = 0; i <= stack_pointer->parenthesis_top; i++)
        {
            *(temp + i) = *(stack_pointer->parenthesis_item + i);
        }
        free(stack_pointer->parenthesis_item);

        stack_pointer->parenthesis_item = temp;
        stack_pointer->parenthesis_size++;
        stack_pointer->parenthesis_item[++stack_pointer->parenthesis_top] = ch_value;
    }
    else
        stack_pointer->parenthesis_item[++stack_pointer->parenthesis_top] = ch_value;
}

char pop_stack(Stack_Parenthesis *stack_pointer)
{
    if(check_underflow(stack_pointer))
    {
		printf("\nStack underflow, terminating program...\n");
		exit(1);
    }
    else
    {
        char popped_value = stack_pointer->parenthesis_item[--stack_pointer->parenthesis_top];

        char *temp = (char *) malloc((stack_pointer->parenthesis_top + 1) * sizeof(char));

        if(temp == NULL)
        {
            printf("\nUnable to allocate memory!\n");
            exit(1);
        }

        for(register int i = 0; i <= stack_pointer->parenthesis_top; i++)
        {
            *(temp + i) = *(stack_pointer->parenthesis_item + i);
        }

        free(stack_pointer->parenthesis_item);
        stack_pointer->parenthesis_item = temp;
        stack_pointer->parenthesis_size = stack_pointer->parenthesis_top + 1;

        return popped_value;
    }
}

char top_stack(Stack_Parenthesis *stack_pointer)
{
	if (check_underflow(stack_pointer))
	{
		printf("\nStack underflow, terminating program...\n");
		exit(1);
	}
	return stack_pointer->parenthesis_item[stack_pointer->parenthesis_top];
}

Boolean check_parenthesis(char left_parenthesis, char right_parenthesis)
{
	if(left_parenthesis == '(' && right_parenthesis == ')')
		return TRUE;

	else if(left_parenthesis == '(' && right_parenthesis == '(')
		return TRUE;

	else
		return FALSE;
}

short check_expression(char *expression, int SIZE)
{
	Stack_Parenthesis parenthesis_stack_object;
	parenthesis_initialization(&parenthesis_stack_object, SIZE);

	short error = 0;

	for(register int i = 0; expression[i] != '\0'; i++)
	{
		if(expression[i] == '{' || expression[i] == '}' || expression[i] == '[' || expression[i] == ']')
		{
			error = 1;
			break;
		}

		else if(expression[i] == '(')
			push_stack(&parenthesis_stack_object, expression[i]);

		else if(expression[i] == ')')
		{
			if(check_underflow(&parenthesis_stack_object))
			{
				error = 1;
				break;
			}
			else if(check_parenthesis(top_stack(&parenthesis_stack_object), expression[i]))
				pop_stack(&parenthesis_stack_object);

			else
			{
				error = 1;
				break;
			}
		}
	}

	if(!error && !check_underflow(&parenthesis_stack_object))
		error = 1;

	deallocate_stack(&parenthesis_stack_object);
	return error;
}

void deallocate_stack(Stack_Parenthesis *stack_pointer)
{
    if(stack_pointer->parenthesis_item != NULL)
        free(stack_pointer->parenthesis_item);

    stack_pointer->parenthesis_top = -1;
    stack_pointer->parenthesis_size = 0;
}


//--------------------------------Collecting operands and operators as string-----------------------------------
void char_initialization(Operator_Stack *stack_pointer, int SIZE)
{
    stack_pointer->char_top = -1;
    stack_pointer->char_item = (char *) malloc(SIZE * sizeof(char));

    if(stack_pointer->char_item == NULL)
    {
        printf("\nUnable to allocate memory!\n");
        exit(1);
    }

    stack_pointer->char_size = SIZE;
}


void operator_push(Operator_Stack *stack_pointer, char ch_value)
{
	if (stack_pointer->char_top == stack_pointer->char_size - 1)
    {
        char *temp = (char *) malloc((stack_pointer->char_size + 1) * sizeof(char));

        if(temp == NULL)
        {
            printf("\nUnable to allocate memory!\n");
            exit(1);
        }

        for(register int i = 0; i <= stack_pointer->char_top; i++)
        {
            *(temp + i) = *(stack_pointer->char_item + i);
        }
        free(stack_pointer->char_item);

        stack_pointer->char_item = temp;
        stack_pointer->char_size++;
        stack_pointer->char_item[++stack_pointer->char_top] = ch_value;
    }
    else
        stack_pointer->char_item[++stack_pointer->char_top] = ch_value;
}


char operator_pop(Operator_Stack *stack_pointer)
{
	if(stack_pointer->char_top == - 1)
    {
		printf("\nStack underflow, terminating program...\n");
		exit(1);
    }
    else
    {
        char popped_value = stack_pointer->char_item[stack_pointer->char_top--];

        char *temp = (char *) malloc((stack_pointer->char_top + 1) * sizeof(char));

        if(temp == NULL)
        {
            printf("\nUnable to allocate memory!\n");
            exit(1);
        }

        for(register int i = 0; i <= stack_pointer->char_top; i++)
        {
            *(temp + i) = *(stack_pointer->char_item + i);
        }

        free(stack_pointer->char_item);
        stack_pointer->char_item = temp;
        stack_pointer->char_size = stack_pointer->char_top + 1;

        return popped_value;
    }
}


/**
	precedence (op, '(' ) = FALSE
	precedence ('(', op ) = FALSE,
	precedence(op, ')') = TRUE,  except op = '('
	precedence('(', ')') = FALSE, instead of PUSH we will pop_operand
*/
Boolean precedence(char left, char right)
{
	if (left == '(' || right == '(')
		return FALSE;

	if (right == ')')
		return TRUE;

	if (left == '*' || left == '/')
	{
		if (right == '*' ||  right == '/' || right == '+' || right == '-')
			return TRUE;
		else
			return FALSE;
	}

	if (left == '+' || left == '-')
	{
		if (right == '+' || right == '-')
			return TRUE;
		else
			return FALSE;
	}

	if (left == '$')
	{
		return TRUE;
	}
	else
		return FALSE;
}


/*
   conversion: converts the supplied infix string to postfix string and assigns that
   postfix string to the postfix array supplied as parameter
*/

void convert_infix_to_postfix(char *infix, char *postfix, int SIZE)
{
	Operator_Stack operator_stack_object;
	char_initialization(&operator_stack_object, SIZE);

	int j = 0;

	char *temp_postfix;
	temp_postfix = (char *) malloc(SIZE * sizeof(char));

    if(temp_postfix == NULL)
    {
        printf("\nUnable to allocate memory!\n");
        exit(1);
    }

	for(register int i = 0; infix[i] != '\0'; i++)
	{
		// if the infix[i] is an operand or a comma
		if ((infix[i] >= '0' && infix[i] <= '9') || infix[i] == ',')
			temp_postfix[j++] = infix[i];

		// if the infix[i] is an operator
		else if(infix[i] == '+' || infix[i] == '-' || infix[i] =='/' || infix[i] == '*' || infix[i] == '$' || infix[i] == '(' || infix[i] ==')')
		{
				while(operator_stack_object.char_top != -1)
				{
					if(precedence(operator_stack_object.char_item[operator_stack_object.char_top], infix[i]))
						temp_postfix[j++] = operator_pop(&operator_stack_object);
					else
						break;
				}

				if (infix[i] == ')')
					operator_pop(&operator_stack_object);
				else
					operator_push(&operator_stack_object, infix[i]);
		}
		else
		{
			printf("\nInvalid symbol %c encountered!\n", infix[i]);
			break;
		}
	}

	while(operator_stack_object.char_top != -1)
		temp_postfix[j++] = operator_pop(&operator_stack_object);

	temp_postfix[j] = '\0';

	for(register int i = 0, j = 0; temp_postfix[i] != '\0'; i++, j++)
	{
		postfix[j] = temp_postfix[i];

		if(temp_postfix[i] == ',' && temp_postfix[i + 1] == ',')
			i++;

		if(temp_postfix[i + 1] == '\0')
			postfix[j + 1] = '\0';
	}
	free(temp_postfix);
}

//--------------------------------------------Calculation part---------------------------------------
void double_initialization(Operand_Stack *stack_pointer, int SIZE)
{
    stack_pointer->double_top = -1;
    stack_pointer->double_item = (double *) malloc(SIZE * sizeof(double));

    if(stack_pointer->double_item == NULL)
    {
        printf("\nUnable to allocate memory!\n");
        exit(1);
    }

    stack_pointer->double_size = SIZE;
}


void push_operand(Operand_Stack *stack_pointer, double value)
{
	if (stack_pointer->double_top == stack_pointer->double_size - 1)
    {
        double *temp = (double *) malloc((stack_pointer->double_size + 1) * sizeof(double));

        if(temp == NULL)
        {
            printf("\nUnable to allocate memory!\n");
            exit(1);
        }

        for(register int i = 0; i <= stack_pointer->double_top; i++)
        {
            *(temp + i) = *(stack_pointer->double_item + i);
        }
        free(stack_pointer->double_item);

        stack_pointer->double_item = temp;
        stack_pointer->double_size++;
        stack_pointer->double_item[++stack_pointer->double_top] = value;
    }
    else
        stack_pointer->double_item[++stack_pointer->double_top] = value;
}

double pop_operand(Operand_Stack *stack_pointer)
{
	if(stack_pointer->double_top == - 1)
    {
		printf("\nStack underflow, terminating program...\n");
		exit(1);
    }
    else
    {
        double popped_value = stack_pointer->double_item[stack_pointer->double_top--];

        double *temp = (double *) malloc((stack_pointer->double_top + 1) * sizeof(double));

        if(temp == NULL)
        {
            printf("\nUnable to allocate memory!\n");
            exit(1);
        }

        for(register int i = 0; i <= stack_pointer->double_top; i++)
        {
            *(temp + i) = *(stack_pointer->double_item + i);
        }

        free(stack_pointer->double_item);
        stack_pointer->double_item = temp;
        stack_pointer->double_size = stack_pointer->double_top + 1;

        return popped_value;
    }
}


double root_of_value(double left_operand, double right_operand)
{
	double result = 1;

	if(right_operand != 0)
		for(register int i = 0; i < right_operand; i++)
			result *= left_operand;

	return result;
}


double operate(double left_operand, double right_operand, char oprtr)
{
	double result = 0.0;

	switch(oprtr)
	{
		case '+':
			result = left_operand + right_operand;
			break;

		case '-':
			result = left_operand - right_operand;
			break;

		case '*':
			result = left_operand * right_operand;
			break;

		case '/':
			result = left_operand / right_operand;
			break;

		case '$':
			result = pow(left_operand, right_operand);
			//result = root_of_value(left_operand, right_operand); This is my root function, it doesn't consider - values.
			//Use this function to find how many digits between 2 commas.
			break;

		default:
			printf("\n%c is not a valid operator!\n", oprtr);
			break;
	}
	return result;
}


double evaluate_postfix(char *postfix, int SIZE)
{
	Operand_Stack operand_stack_object;
	double_initialization(&operand_stack_object, SIZE);

	for(register int i = 0; postfix[i] != '\0'; i++)
	{
		if(postfix[i] == ',')
		{
			i++;

			if (postfix[i] >= '0' && postfix[i] <= '9')
			{
				register int cnt = 0;

				//Finding how many digits are there between 2 commas
				for(register int j = i; ; j++, cnt++)
					if(postfix[j] == ',')
						break;

				double value = 0.0;

				//Finding the equivalent double value of character numbers between 2 commas.
				for(register int root = cnt - 1, j = i; i < (cnt + j); root--, i++)
					value += (double) (root_of_value(10, root) * (postfix[i] - '0'));

				push_operand(&operand_stack_object, value);
			}
			i--;
		}
		else if (postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/' || postfix[i] == '$')
		{
			double operand1 = pop_operand(&operand_stack_object);
			double operand2 = pop_operand(&operand_stack_object);
			double result = operate(operand2, operand1, postfix[i]);
			push_operand(&operand_stack_object, result);
		}
		else
		{
			printf("\nInvalid symbol %c encountered\n", postfix[i]);
			break;
		}
	}
	return pop_operand(&operand_stack_object);
}


//--------------------------------Collecting operands and operators as string for prefix-----------------------------------
//TRUE means PUSH, FALSE means POP
Boolean prefix_precedence(char stack_top, char right)
{
	if(stack_top == ')' || right == ')')
		return TRUE;

	if(stack_top == '$')
	{
		if(right == '$')
			return TRUE;
		else
			return FALSE;
	}

	if(stack_top == '*' || stack_top == '/')
	{
		if(right == '*' || right == '/' || right == '$')
			return TRUE;
		else
			return FALSE;
	}

	if(stack_top == '+' || stack_top == '-')
	{
		if(right == '+' || right == '-' || right == '*' || right == '/' || right == '$')
			return TRUE;
		else
			return FALSE;
	}
}

int how_many_parenthesis(char *infix)
{
	int cnt = 0;

	for(register int i = 0; infix[i] != '\0'; i++)
		if(infix[i] == ')' || infix[i] == '(')
			cnt++;

	return cnt;
}


/*
Comma is needed to separate numbers between them so we can find number of the digits between 2 commas.
*/

void convert_infix_to_prefix(char *infix, char *prefix, int SIZE)
{
	Operator_Stack operator_stack_object;
	char_initialization(&operator_stack_object, SIZE);

	char *temp_prefix;
	temp_prefix = (char *) malloc(SIZE * sizeof(char));

    if(temp_prefix == NULL)
    {
        printf("\nUnable to allocate memory!\n");
        exit(1);
    }
	
	infix = strrev(infix); //Reverse the infix to implement prefix order.

	//Find how many parenthesis to subtract from infix length to place array members into temp_prefix correctly.
	int num_of_parenthesis = how_many_parenthesis(infix);
	temp_prefix[strlen(infix) - num_of_parenthesis] = '\0';

	for(register int i = 0, j = strlen(infix) - num_of_parenthesis - 1; infix[i] != '\0'; i++)
	{
		// if the infix[i] is an operand or a comma
		if ((infix[i] >= '0' && infix[i] <= '9') || infix[i] == ',')
			temp_prefix[j--] = infix[i];

		// if the infix[i] is an operator
		else if(infix[i] == '$' || infix[i] == '*' || infix[i] == '/' || infix[i] == '+' || infix[i] == '-')
		{
			//if stack is empty then push, and go back to begining of the loop. Because stack has just one element now.
			//Otherwise it is gonna comparison same operator twice, and its decision will be wrong.
			if(operator_stack_object.char_top == -1)
			{
				operator_push(&operator_stack_object, infix[i]);
				continue;
			}

			//Compare infix[i] and top of the stack element. If true then push.
			if(prefix_precedence(operator_stack_object.char_item[operator_stack_object.char_top], infix[i]))
				operator_push(&operator_stack_object, infix[i]);

			//If false then pop, and decrement i. Because stack may not be empty after pop operation.
			//So we can compare infix[i] again with the stack top element.
			else
			{
				temp_prefix[j--] = operator_pop(&operator_stack_object);
				i--;
			}
		}

		//if the infix[i] is a parenthesis
		else if(infix[i] == ')' || infix[i] == '(')
		{
			//if the infix[i] is a closing parenthesis (in our case it behaves as an opening parenthesis because of the reverse order.)
			if(infix[i] == ')')
				operator_push(&operator_stack_object, infix[i]);

			//if the infix[i] is an opening parenthesis (in our case it behaves as an closing parenthesis because of the reverse order.)
			else
			{
				//Pop operators from stack into temp_prefix then just pop the parenthesis.
				while(1)
				{
					if(operator_stack_object.char_item[operator_stack_object.char_top] == ')')
					{
						operator_pop(&operator_stack_object);
						break;
					}
					else
						temp_prefix[j--] = operator_pop(&operator_stack_object);
				}
			}
		}

		else
		{
			printf("\nInvalid symbol %c encountered!\n", infix[i]);
			break;
		}

		if(infix[i + 1] == '\0')
			while(operator_stack_object.char_top != -1)
				temp_prefix[j--] = operator_pop(&operator_stack_object);
	}
	
	//Placing temp_prefix into the prefix by rejecting extra commas that we don't need.
	for(register int i = 0, j = 0; temp_prefix[i] != '\0'; i++, j++)
	{
		prefix[j] = temp_prefix[i];

		if(temp_prefix[i] == ',' && temp_prefix[i + 1] == ',')
			i++;

		if(temp_prefix[i + 1] == '\0')
			prefix[j + 1] = '\0';
	}
	free(temp_prefix);
}


double evaluate_prefix(char *prefix, int SIZE)
{
	Operand_Stack operand_stack_object;
	double_initialization(&operand_stack_object, SIZE);

	//We're starting to place from last element to 0th because of the prefix order (reverse order).
	for(register int i = strlen(prefix) - 1; i >= 0; i--)
	{
		//if prefix[i] is comma, decrement the i to get character numbers.
		if(prefix[i] == ',')
		{
			i--;

			if (prefix[i] >= '0' && prefix[i] <= '9')
			{
				register int cnt = 0;

				//Finding how many digits are there between 2 commas
				for(register int j = i; ; j--, cnt++)
					if(prefix[j] == ',')
						break;

				double value = 0.0;

				//Finding the equivalent double value of character numbers between 2 commas.
				for(register int root = 0, j = i; i > (j - cnt); root++, i--)
					value += (double) (root_of_value(10, root) * (prefix[i] - '0'));
				
				push_operand(&operand_stack_object, value);
			}
			i++;
		}
		else if (prefix[i] == '+' || prefix[i] == '-' || prefix[i] == '*' || prefix[i] == '/' || prefix[i] == '$')
		{
			//First pop left, second pop right value. For example 2+3 (infix expression), +23 (prefix expression).
			//in this case stack_top element will be 2, and 3 is the bottom element of the stack.
			double operand2 = pop_operand(&operand_stack_object);
			double operand1 = pop_operand(&operand_stack_object);
			double result = operate(operand2, operand1, prefix[i]);
			push_operand(&operand_stack_object, result);
		}
		else
		{
			printf("\nInvalid symbol %c encountered\n", prefix[i]);
			break;
		}
	}
	return pop_operand(&operand_stack_object);
}
