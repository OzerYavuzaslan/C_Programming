#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int dice1, dice2, user_guess, sum = 0, user_score = 0;
    srand(time(NULL));

    printf("This is a dice game. Two dices will be rolled and you are going to guess the\nsummation of these dices. Good Luck & Have Fun!...\n\n");

    while(1)
    {
        dice1 = (rand() % 6) + 1;
        dice2 = (rand() % 6) + 1;
        sum = dice1 + dice2;

        printf("Enter a guess (Enter 0 to terminate the program): ");
        scanf("%d", &user_guess);
        printf("\n");

        if(user_guess < 0 || user_guess > 12)
        {
            printf("Enter valid number between 0 and 12!\n\n");
            continue;
        }
        else if(user_guess == 0)
        {
            printf("\n\nThe program is terminated.\nYour total score is %d\n", user_score);
            break;
        }
        else if(user_guess != sum)
        {
            user_score -= 5;
            printf("Your guess is incorrect!\nYour score is %d.\nThe sum was %d\n\n", user_score, sum);
            continue;
        }
        else
        {
            user_score += 25;
            printf("Well done, you've guessed the sum!\nYour score is %d.\nThe sum is %d\n\n", user_score, sum);
        }
    }
    printf("Thank you for playing...\n\n");
    return 0;
}
