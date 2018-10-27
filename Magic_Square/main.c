#include <stdio.h>
#include <stdlib.h>

int main()
{
    int dimension;
    printf("This is a magic square matrix program. Enter odd integers between 1 and 15\n(inclusive): ");
    scanf("%d", &dimension);

    if(dimension % 2 == 0 || dimension < 1 || dimension > 15)
    {
        printf("\n\nYou can't enter %d! Enter valid odd number between 1 and 15!\nThe program is terminated...\n\n", dimension);
        return 0;
    }
    else
    {
		//Magic Square implementation algorithm
        int magic_square_matrix[dimension][dimension];

        for(int i = 0; i < dimension; i++)
        {
            for(int j = 0; j < dimension; j++)
            {
                magic_square_matrix[i][j] = 0;
            }
        }
		
        for(int row = dimension - 1, column = dimension / 2, k = 1; k <= dimension * dimension; k++)
        {
            magic_square_matrix[row][column] = k;

            int old_row = row;
            int old_column = column;

            row = (row + 1) % dimension;
            column = (column + 1) % dimension;

            if(magic_square_matrix[row][column] != 0)
            {
                row = old_row;
                column = old_column;
                row -= 1;
            }
        }
		//End of magic square algorithm implementation

        printf("\n\nThe magic square: \n\n");

        for(int i = 0; i < dimension; i++)
        {
            for(int j = 0; j < dimension; j++)
            {
                printf("%4d", magic_square_matrix[i][j]);
            }
            printf("\n");
        }

        int magic_constant = ((dimension * dimension * dimension) + dimension) / 2;
        printf("\nThe magic constant of your matrix is %d\n\n\n", magic_constant);

        int array_sum[(dimension * 2) + 2];

        for(int i = 0; i < (dimension * 2) + 2; i++)
        {
            array_sum[i] = 0;
        }

        for(int i = 0; i < dimension; i++)
        {
            for(int j = 0; j < dimension; j++)
            {
                array_sum[i] += magic_square_matrix[i][j];
            }
        }

        for(int j = 0; j < dimension; j++)
        {
            for(int i = 0; i < dimension; i++)
            {
                array_sum[dimension + j] += magic_square_matrix[i][j];
            }
        }

        for(int row = 0, column = 0, i = 0; i < dimension; i++, row++, column++)
        {
            array_sum[dimension * 2] += magic_square_matrix[row][column];
        }

        for(int row = 0, column = dimension - 1, i = 0; i < dimension; i++, row++, column--)
        {
            array_sum[(dimension * 2) + 1] += magic_square_matrix[row][column];
        }

        int correct = 1;

        for(int i = 0; i < (dimension * 2) + 2; i++)
        {
            if(array_sum[i] =! magic_constant)
                correct = 0;
        }

        if(correct)
            printf("Your algorithm calculates correctly for magic square matrix!\nSum of each row, column, and both two diagonals are equal to each other.\n\n\n");
        else
            printf("Your algorithm DOESN'T calculate correctly for magic square matrix!\nSum of each row, column, and both two diagonals are equal to each other.\n\n\n");
    }
    return 0;
}
