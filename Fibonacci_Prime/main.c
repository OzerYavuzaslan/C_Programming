#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

/*
    This program looks for a subtraction that is between the greatest value below the limit and the smallest value above the limit of prime Fibonacci values.
*/

void main()
{
    int flag, cnt = 0;
    long long int first_num = 1, second_num = 1, third_num = 0, *fib, limit, j = 0;
    fib = (long long int*) malloc(275 * sizeof(long long int));

    printf("Enter the limit that you are looking for a subtraction that is between the\ngreatest value below the limit and the smallest value above the limit of prime\nFibonacci series (Do not Enter Bigger than 2971215072): ");
    scanf("%llu",&limit);
    printf("\n\nThe limit: %llu\n\n", limit);

    for (;;)
    {
        flag = 0;
        third_num = first_num + second_num;
        first_num = second_num;
        second_num = third_num;
        for (long long int i = 2; i < third_num/2; i++)
        {
            if (third_num % i == 0)
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0 && third_num<=limit)
        {
            *(fib + cnt) = third_num;
            printf("%d. Prime number of Fibonacci series: %llu\n", cnt+1,  *(fib + cnt));
            cnt++;
        }
        else if (flag == 0 && third_num>limit)
        {
            *(fib + cnt) = third_num;
            printf("%d. Prime number of Fibonacci series: %llu\n", cnt+1,  *(fib + cnt));
            break;
        }
    }
    long long int sub = *(fib + cnt) - *(fib + cnt - 1);
    printf("\nThe result (%llu - %llu) = %llu\n\n",*(fib + cnt), *(fib + cnt - 1), sub);
    free(fib);
    getch();
}
