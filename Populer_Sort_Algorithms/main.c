#include <stdio.h>
#include <stdlib.h>
#include "Sort_Algorithms.h"

int main()
{
    int n;
    float elapsed;
	short array_cnt = 0;
    struct timeval end;
    struct timeval start;

	printf("This is a program that consists of popular sort algorithms to sort integers.\n"
	"Enter number of the integers will be inserted: ");
	scanf("%d", &n);

    int *array = (int *) malloc(sizeof(int) * n);

    if (array == NULL)
	{
        printf("\nUnable to allocate dynamic memory!\n");
        exit(0);
    }

	menu();

	while(1)
	{
		short choice, sort_process = 0;

		printf("\nWhat do you want to do?\n"
        "Enter your choice (0 to show menu): ");
		scanf("%hd", &choice);

		switch(choice)
		{
			case 0:
				menu();
				break;

			case 1:
				create_random_data(array, n);
				array_cnt = 1;
				break;

			case 2:
				input_from_console(array, n);
				array_cnt = 1;
				break;

			case 3:
				if(array_cnt == 0)
				{
					array_empty_msg();
					continue;
				}

				print_data(array, n);
				break;

			case 4:
				if(array_cnt == 0)
				{
					array_empty_msg();
					continue;
				}

                gettimeofday(&start, 0);  // getting the system time just before calling bubble sort.
                bubble_sort(array, n, sort_order_func());  // calling the bubble sort.
                gettimeofday(&end, 0);    // getting the system time just after calling bubble sort.
                sort_process = 1; // Calculating the time to take to sort.
                break;

			case 5:
				if(array_cnt == 0)
				{
					array_empty_msg();
					continue;
				}

                gettimeofday(&start, 0);
                selection_sort(array, n, sort_order_func());
                gettimeofday(&end, 0);
                sort_process = 1;
                break;

			case 6:
				if(array_cnt == 0)
				{
					array_empty_msg();
					continue;
				}

                gettimeofday(&start, 0);
                insertion_sort(array, n, sort_order_func());
                gettimeofday(&end, 0);
                sort_process = 1;
                break;

			case 7:
				jump_case7:

				if(array_cnt == 0)
				{
					array_empty_msg();
					continue;
				}

				printf("\nWhat do you want to do?\n"
				"1. Sort by using Shell's Gap Sequence.\n"
				"2. Sort by using Sedgewick's Gap Sequence.\n"
				"Enter your choice: ");
				scanf("%hd", &choice);

				if(choice == 1 || choice == 2)
				{
					gettimeofday(&start, 0);

					if(choice == 1)
						shell_sort_default(array, n, sort_order_func());
					else
						shell_sort_sedgewick(array, n, sort_order_func());

					gettimeofday(&end, 0);
					sort_process = 1;
				}
				else
				{
					error_msg();
					goto jump_case7;
				}
                break;

			case 8:
				if(array_cnt == 0)
				{
					array_empty_msg();
					continue;
				}

                gettimeofday(&start, 0);
                quick_sort(array, 0, n - 1, sort_order_func());
                gettimeofday(&end, 0);
                sort_process = 1;
                break;

			case 9:
				if(array_cnt == 0)
				{
					array_empty_msg();
					continue;
				}

                gettimeofday(&start, 0);
                merge_sort(array, 0, n - 1, n, sort_order_func());
                gettimeofday(&end, 0);
                sort_process = 1;
                break;

			case 10:
				if(array_cnt == 0)
				{
					array_empty_msg();
					continue;
				}

                gettimeofday(&start, 0);
                heap_sort(array, n, sort_order_func());
                gettimeofday(&end, 0);
                sort_process = 1;
                break;

			case 11:
				if(array_cnt == 0)
				{
					array_empty_msg();
					continue;
				}

                gettimeofday(&start, 0);
                ozer_sort(array, n, sort_order_func());
                gettimeofday(&end, 0);
                sort_process = 1;
                break;

			case 12:
				if(array_cnt == 0)
				{
					array_empty_msg();
					continue;
				}

                if (check_sorted(array, n, sort_order_func()))
                    printf("\nArray is sorted.\n");
                else
                    printf("\nArray is not sorted.\n");
				break;

			case 13:
				printf("\nThe program is terminated...\n");
				exit(1);

			default:
				error_msg();
				break;
		}

		if(sort_process)
		{
			// displaying the execution time.
			elapsed = timediff(start, end);
			printf("\nTime taken to sort %d numbers using bubble sort is: %f msec\n", n, elapsed);
		}
	}
    return 0;
}
