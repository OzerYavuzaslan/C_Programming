#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n; //Line Numbers
    int i, j; // i = row numbers, j = column numbers in the line
    int check_shape;

    while(1)
    {
        printf("\nShape of stars:\n1. Right Triangle\n2. Reverse Right Triangle\n"
               "3. Right Triangle and Reverse Triangle\n4. Right Triangle with number series in columns\n"
               "5. Right Triangle with 0 and 1\n");

        printf("\nENTER THE SHAPE NUMBER (0 to terminate the program): ");
        scanf("%d", &check_shape);

        if(check_shape == 0)
        {
            printf("\nThe program is terminated...\n");
            break;
        }
        else if(check_shape < 0 || check_shape > 5)
        {
            printf("\n\nEnter valid number!\n\n");
            continue;
        }
        else
        {
            printf("\n\nEnter how many lines that you want to print star (*): ");
            scanf("%d", &n);
            printf("\n");

            if(check_shape == 1)
            {
                for(i = 1; i <= n; ++i)
                {
                    for(j = 1; j <= i; ++j)
                    {
                        printf("* ");
                    }
                    printf("\n");
                }

                for(i = 1; i <= n; ++i)
                {
                    for(j = 1; j <= i; ++j)
                    {
                        printf("%d ", j);
                    }
                    printf("\n");
                }
            }

            else if(check_shape == 2)
            {
                for(i = 1; i <= n; ++i)
                {
                    for(j = 10; i <= j; --j)
                    {
                        printf("* ");
                    }
                    printf("\n");
                }

                for(i = 1; i <= n; ++i)
                {
                    for(j = 10; i <= j; --j)
                    {
                        printf("%d ", j);
                    }
                    printf("\n");
                }
            }

            else if(check_shape == 3)
            {
                for(i = 1; i <= n; ++i)
                {
                    for(j = 1; j <= i; ++j)
                    {
                        printf("*");
                    }
                    printf("\n");
                }

                for(i = 1; i <= n; ++i)
                {
                    for(j = 10; i <= j; --j)
                    {
                        printf("*");
                    }
                    printf("\n");
                }

                for(i = 1; i <= n; ++i)
                {
                    for(j = 1; j <= i; ++j)
                    {
                        printf("%d", j);
                    }
                    printf("\n");
                }

                for(i = 1; i <= n; ++i)
                {
                    for(j = 10; i <= j; --j)
                    {
                        printf("%d", j);
                    }
                    printf("\n");
                }
            }

            else if(check_shape == 4)
            {
                for(i = 1; i <= n; ++i)
                {
                    for(j = 1; j <= i; ++j)
                    {
                        if(i % 10 != 0)
                        {
                            printf("%d   ", i);
                        }
                        else
                        {
                            printf("%d  ", i);
                        }
                    }
                    printf("\n");
                }
            }

            else if(check_shape == 5)
            {
                for(i = 1; i <= n; ++i)
                {
                    for(j = 1; j <= i; ++j)
                    {
                        printf("%d  ", (i + j) % 2);
                    }
                    printf("\n");
                }
            }
        }
    }
    return 0;
}
