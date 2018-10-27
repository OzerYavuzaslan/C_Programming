#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, m;

    printf("This is a program that finds transpose matrix of a matrix. Enter numbers for\nrow and column numbers between >= 3 and <= 10 to make a NxM matrix: ");
    scanf("%d %d", &n, &m);

    if(n < 3 || n > 10 || m < 3 || m > 10)
    {
        printf("\n\nYou must enter between 3 and 10! The program is terminated...");
        return 0;
    }
    else
    {
        int matrix[n][m], matrix_value;

        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                printf("Enter value of Matrix[%d][%d]: ", i, j);
                scanf("%d", &matrix_value);
                matrix[i][j] = matrix_value;
            }
        }

        printf("\n\nYour matrix values are:\n");

        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                printf("%4d", matrix[i][j]);
            }
            printf("\n");
        }

        printf("\n\nThis is the transpose matrix of your matrix:\n");

        for(int i = 0; i < m; i++)
        {
            for(int j = 0; j < n; j++)
            {
                printf("%4d", matrix[j][i]);
            }
            printf("\n");
        }
    }
    return 0;
}
