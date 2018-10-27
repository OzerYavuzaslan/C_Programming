#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main(int argc, char const *argv[])
{
    printf("This is a program that converts mathematical expressions from\n"
               "infix expressions to polish, and reverse polish notations.\n");

//-------------------------------------------------------------------------------------------------------------------
    for(short termination = 0 ;;)
    {
        if(termination)
        {
            char terminate;

            printf("\n\nIf you wish to terminate the program, enter e or E to terminate the program.\nOtherwise enter something else: ");
            scanf(" %c", &terminate);

            if(terminate == 'e' || terminate == 'E')
            {
                printf("\nThe program is terminated.\n");
                break;
            }
        }

//----------------------------------------Finding the exact SIZE that we need!------------------------------------
        char *temp_expression, *temp_expression2;
        temp_expression = (char *) malloc(60 * sizeof(char));
        temp_expression2 = (char *) malloc(120 * sizeof(char));

        printf("\n\nHint: root of a value expressed by using $ symbol.\n"
            "For example: square root of 3 must be shown as 3$2\n"
            "\nInput expression string: ");
        scanf(" %s", temp_expression);

        if(!assign_expression(temp_expression, temp_expression2))
            continue;

        free(temp_expression);

        int SIZE = 0;

        for(register int i = 0; temp_expression2[i] != '\0'; i++)
        {
            SIZE++;

            if(temp_expression2[i + 1] == '\0')
                SIZE += 1; //+1 for NULL
        }

        char *infix;
        infix = (char *) malloc(SIZE * sizeof(char));

        for(register int i = 0; temp_expression2[i] != '\0'; i++)
        {
            infix[i] = temp_expression2[i];

            if(temp_expression2[i + 1] == '\0')
                infix[i + 1] = '\0';
        }
        free(temp_expression2);

//-------------------------------------------------------------------------------------------------------------------
        char *postfix, *prefix;
        postfix = (char *) malloc(SIZE * sizeof(char));
        prefix = (char *) malloc(SIZE * sizeof(char));

        if(!check_expression(infix, SIZE))
        {
            convert_infix_to_postfix(infix, postfix, SIZE);
            convert_infix_to_prefix(infix, prefix, SIZE);
            double postfix_result = evaluate_postfix(postfix, SIZE);
            double prefix_result = evaluate_prefix(prefix, SIZE);

            printf("\n\n\nThe equivalent postfix is: ");
            for(register int i = 0; postfix[i] != '\0'; i++)
                if(postfix[i] != ',')
                    printf("%c", postfix[i]);

            printf("\nThe equivalent prefix is: ");
            for(register int i = 0; prefix[i] != '\0'; i++)
                if(prefix[i] != ',')
                    printf("%c", prefix[i]);

            printf("\nResult of the expression in postfix order is: %0.3lf\n", postfix_result);
            printf("Result of the expression in prefix order is: %0.3lf\n\n", prefix_result);
        }
        else
            printf("\n\nEnter valid parenthesis! You can use only ( and ) parenthesis.\n"
                       "The order is also important. You can't input ) before (\n\n");

        termination = 1;
    }
    printf("\n");
	return 0;
}
