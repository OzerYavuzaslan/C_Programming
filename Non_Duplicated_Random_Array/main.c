#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void main()
{
    int n;
    srand(time(NULL));

    printf("Enter size of the array: ");
    scanf("%d", &n);

    int x[n];

    for(int i = 0; i < n; i++)
    {
        if(i == 0)
        {
            x[i] = rand() % n;
        }
        else
        {
            int temp_random = rand() % n;

            for(int j = 0; j < i; j++)
            {
                if(temp_random ==  x[j] || temp_random == x[0])
                {
                    temp_random = rand() % n;
                    j = 0;
                }
            }
            x[i] = temp_random;
        }
    }

    printf("\n\n\nNon-Duplicated array elements: \n");
    long sum = 0;

    for(int i = 0; i < n; i++)
    {
        if(i % 15 == 0)
        {
            printf("\n%5d", x[i]);
        }
        else
        {
            printf("%5d", x[i]);
        }
        sum += x[i];
    }
    printf("\n\nSum of the array elements is %ld\nAverage of the array elements is %0.3lf\n\n\n", sum, (double) sum / n);
}
