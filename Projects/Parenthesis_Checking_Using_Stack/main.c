#include <stdio.h>
#include <stdlib.h>
#include "paranthesis_functions.h"

char top_stack(Stack *);
char pop_stack(Stack *);

void deallocate_stack(Stack *);
void push_stack(Stack *, char);
void char_initializiation(Stack *);

short check_overflow(Stack *);
short check_underflow(Stack *);
short check_parenthesis(char, char);
short check_expression(char *, int);


int main()
{
    int SIZE;

    printf("Enter size of the array: ");
    scanf("%d", &SIZE);

	char expression[SIZE + 1]; //1 for NULL
	printf("\nInput expression: ");
	scanf(" %s", expression); //scanf(" %[\n]", expression);

	if (check_expression(expression, (SIZE + 1)))
		printf("\n\nDoes not contain well formed brackets.\n\n");
	else
		printf("\n\nContains well formed brackets.\n\n");

	return 0;
}
