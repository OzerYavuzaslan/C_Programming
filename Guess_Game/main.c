#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int user_guess, random_num, chance_cnt = 1, match = 0;
    const int max_chances = 7;

    srand(time(NULL));
    random_num = rand() % 100;

    printf("***********************************************************\n");
    printf("**----------------Welcome to Guessing Game---------------**\n");
    printf("**---------You can guess if you understand the MATH------**\n");
    printf("**---------------------------------------------------------\n");
    printf("\n\n");

    printf("Program has guessed a number between 0 and 100 (100 is not included),\nwhat you need to do is match it.\n");
    printf("Remember, you have only 7 chances.\n");
    printf("Best wishes...\n\n");

    while(chance_cnt <= max_chances)
    {
        printf("Enter your guess: ");
        scanf("%d", &user_guess);
        printf("\n");

        if(user_guess > random_num)
        {
            printf("Your guess is high!\n");
            printf("You have %d chances left\n", max_chances - chance_cnt);
        }
        else if(user_guess < random_num)
        {
            printf("Your guess is low!\n");
            printf("You have %d chances left\n", max_chances - chance_cnt);
        }
        else
        {
            match = 1;
            printf("Well done, you've guessed the number!\n");
            break;
        }
        printf("\n\n");
        chance_cnt++;
    }

    if(match == 0)
    {
        printf("Game is over...\n");
    }
    else
    {
        if(chance_cnt <= 3)
        {
            printf("You're Super Duper NINJA\n");
        }
        else if(chance_cnt > 3 && chance_cnt <= 5)
        {
            printf("You're Crazy NINJA\n");
        }
        else
        {
            printf("You have potential to be a NINJA!\n");
        }
    }
    return 0;
}
