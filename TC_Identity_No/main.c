#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "functions.h"

int main(int argc, char const *argv[])
{
    char *tc_num = (char *) malloc(11 * sizeof(char));

    jump1:
    printf("This is a program that checks a TC number, which is valid or not.\nEnter first 11 digits: ");
    scanf(" %[^\n]", tc_num);

    if(!check_first_digit(tc_num))
    {
        printf("\nFirst digit cannot be 0! Enter a correct number!\n\n");
        goto jump1;
    }
    else if(!check_length(tc_num))
    {
        printf("\nYou have to enter 11 digits! Enter a correct number!\n\n");
        goto jump1;
    }
    else if(!check_integer(tc_num))
    {
        printf("\nYou have to enter integer values! Enter a correct number!\n\n");
        goto jump1;
    }
    else if(!check_digit(tc_num))
    {
        printf("\n%s is not a valid TC number! Enter a valid TC number.\n\n", tc_num);
        goto jump1;
    }
    else
    {
        printf("\n%s is a valid TC number!\n", tc_num);
    }

    free(tc_num);

    printf("\nPress enter to exit.");
    getch();
    return 0;
}
