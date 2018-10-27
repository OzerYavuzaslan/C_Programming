#include <sys/time.h>

/*
  function prototypes
*/
void menu();
void error_msg();
void array_empty_msg();
short sort_order_func();
void print_data(int *, int);
void heapify(int *, int, short);
void heap_sort(int *, int, short);
void ozer_sort(int *, int, short);
void input_from_console(int *, int);
void create_random_data(int *, int);
void bubble_sort(int *, int, short);
short check_sorted(int *, int, short);
int partition(int *, int, int, short);
void selection_sort(int *, int, short);
void insertion_sort(int *, int, short);
void quick_sort(int *, int, int, short);
void shell_sort_default(int *, int, short);
void adjust(int *, register int, int, short);
void merge(int *, int, int, int, int, short);
void merge_sort(int *, int, int, int, short);
void shell_sort_sedgewick(int *, int, short);
float timediff(struct timeval, struct timeval);


//--------------------------Functions----------------------------
void error_msg()
{
	printf("\nEnter valid choice!\n");
}

//---------------------------------------------------------------
void menu()
{
	printf("\n 1. Create an array with random numbers.\n"
	" 2. Create an array by entering from console.\n"
	" 3. Print the array.\n"
	" 4. Bubble Sort.\n"
	" 5. Selection Sort.\n"
	" 6. Insertion Sort.\n"
	" 7. Shell Sort.\n"
	" 8. Quick Sort.\n"
	" 9. Merge Sort.\n"
	"10. Heap Sort.\n"
	"11. Ozer Sort.\n"
	"12. Check array is sorted or not.\n"
	"13. Terminate the program.\n\n");
}

//---------------------------------------------------------------
void array_empty_msg()
{
	printf("\nYou haven't input any numbers into the array! Fill the array first.\n");
		
}

//---------------------------------------------------------------
void input_from_console(int array[], int n)
{
    printf("\nPlease input integer numbers.\n");
    printf("You will need to input %d integers in total.\n\n", n);

    // iterate n times from 0 to n-1, each time ask for input and
    // take the input using scanf into the ith element of the array
    for(register int i = 0; i < n; i++)
	{
        printf("array[%d]: ", i);
        scanf("%d", &array[i]);
    }
}

//---------------------------------------------------------------
void print_data(int array[], int n)
{
    printf("\n  Content of the array\n");
    printf("------------------------\n");

    for(register int i = 0; i < n; i++)
	{
        printf("%6d", array[i]);

        // give a line break after every 10 numbers
        if ((i + 1) % 10 == 0)
            printf("\n");
    }
}

//---------------------------------------------------------------
void create_random_data(int array[], int n)
{
    // randomize the seed using current system time, this is required to generate
    // different series of random numbers on every call. Otherwise, rand() function
    // will generate the same set of random numbers.
    srand(time(NULL));

    // Now fill the array
    for(register int i = 0; i < n; i++)
        array[i] = rand() % 10000;  // fill the array with numbers from 0 - 9999

    printf("\nArray is created by random numbers.\n");
}

//---------------------------------------------------------------
float timediff(struct timeval start, struct timeval end)
{
    return (end.tv_sec - start.tv_sec) * 1000.0f + (end.tv_usec - start.tv_usec) / 1000.0f;
}

//---------------------------------------------------------------
short sort_order_func()
{
	short sort_order;
	
	printf("\n0. Ascending order.\n"
	"1. Descending order.\n"
	"Enter your choice: ");
	scanf("%hd", &sort_order);

	if(sort_order != 0 && sort_order != 1)
	{
		error_msg();
		sort_order_func();
	}
		
	return sort_order;
}

//---------------------------------------------------------------
void bubble_sort(int array[], int n, short sort_order)
{
	short sorted = 0;

	for(register int i = 0, temp; i < n - 1 && !sorted; i++)
	{
		sorted = 1;

		for(register int j = 0; j < n - 1 - i; j++)
		{
			if(sort_order == 0)
			{
				if (array[j] > array[j + 1])
				{
					temp = array[j];
					array[j] = array[j + 1];
					array[j + 1] = temp;
					sorted = 0;
				}
			}
			else
			{
				if (array[j] < array[j + 1])
				{
					temp = array[j];
					array[j] = array[j + 1];
					array[j + 1] = temp;
					sorted = 0;
				}
			}
		}
	}
}

//---------------------------------------------------------------
void selection_sort(int array[], int n, short sort_order)
{	
	for(register int i = 0, temp, index_of_min; i < n - 1; i++)
	{
		index_of_min = i;

		for(register int j = i + 1; j < n; j++)
		{
			if(sort_order == 0)
			{
				if (array[j] < array[index_of_min])
					index_of_min = j;
			}
			else
			{
				if (array[j] > array[index_of_min])
					index_of_min = j;
			}
		}
		if (index_of_min != i)
		{
			temp = array[index_of_min];
			array[index_of_min] = array[i];
			array[i] = temp;
		}
	}
}

//---------------------------------------------------------------
void insertion_sort(int array[], int n, short sort_order)
{	
	for(register int i = 1, j, current; i < n; i++)
	{
		current = array[i];

		if(sort_order == 0)
		{
			for(j = i - 1; j >= 0 && current < array[j]; j--)
				array[j + 1] = array[j];
			
			array[j + 1] = current;
		}
		else
		{
			for(j = i - 1; j >= 0 && current > array[j]; j--)
				array[j + 1] = array[j];
			
			array[j + 1] = current;
		}
	}
}

//---------------------------------------------------------------
/*
  Implementation of Shell Sort, uses gap sequence of Shell
*/
void shell_sort_default(int array[], int n, short sort_order)
{	
	for(register int gap = n / 2; gap >= 1; gap /= 2)
	{
        for(register int i = gap, j, current; i < n; i++)
		{
            current = array[i];
			
			if(sort_order == 0)
			{
				for(j = i; j >= gap && current < array[j - gap]; j -= gap)
					array[j] = array[j - gap];
			}
			else
			{
				for(j = i; j >= gap && current > array[j - gap]; j -= gap)
					array[j] = array[j - gap];
			}
            array[j] = current;
        }
	}
}

/*
    Implementation of Shell sort using gap sequence of Sedgewick
*/
void shell_sort_sedgewick(int array[], int n, short sort_order)
{
    int gap, gaps[] = {16577, 4193, 1073, 281, 77, 23, 8, 1};
	
    for(register int i = 0; i < 8; i++)
	{
        int gap = gaps[i];
		
        for(register int j = gap, k, current; j < n; j++)
		{
            current = array[j];
			
			if(sort_order == 0)
			{
				for(k = j; k >= gap && current < array[k - gap]; k -= gap)
					array[k] = array[k - gap];
			}
			else
			{
				for(k = j; k >= gap && current > array[k - gap]; k -= gap)
					array[k] = array[k - gap];
			}
            array[k] = current;
        }
    }
}

//---------------------------------------------------------------
/*
	A Divide and Conquer based sort algorithm
*/
void quick_sort(int array[], int lb, int ub, short sort_order) //lb = lower bound, ub = upper bound
{
    // check the base condition of recurtion, if there is only one element 
    // or no element terminate the recursion.
    if (lb >= ub)
        return;
	
    // If not reached the base, do the partition. Get the index j where the 
    // partition function placed the pivot.
    int j = partition(array, lb, ub, sort_order);
	
    // There are 2 unsorted sections, lb to j-1 and j+1 to ub.
    // Sorting lb to j-1 using quick sort
    quick_sort(array, lb, j - 1, sort_order);

    // sorting j+1 to ub using quick sort.
    quick_sort(array, j + 1, ub, sort_order);
}

/*
    Implementation of Partition Function.
*/
int partition(int array[], int lb, int ub, short sort_order)
{
    int down, up, pivot, temp;
	
    down = lb;
    up = ub;
    
	//pivot = array[lb];
	pivot = array[rand() % (up - lb) + lb]; //Pick a pivot randomly in between up and lb
	
    while(down < up)
	{
		if(sort_order == 0)
		{
			while(array[down] <= pivot && down < ub)
				down++;

			while(array[up] > pivot)
				up--;
		}
		else
		{
			while(array[down] >= pivot && down < ub)
				down++;

			while(array[up] < pivot)
				up--;
		}
		
        if (down < up)
		{
            temp = array[down];
            array[down] = array[up];
            array[up] = temp;
        }
    }
	
    // Now place the pivot at index up, so exchange the pivot index(lb) with the up
    array[lb] = array[up];
    array[up] = pivot;
    return up;
}

//---------------------------------------------------------------
/*
	A Divide and Conquer based sort algorithm
*/
void merge_sort(int array[], int lb, int ub, int n, short sort_order)
{
    if (lb >= ub)
        return;
	
    int mid = (lb + ub) / 2;

    // sort the left half using merge sort
    merge_sort(array, lb, mid, n, sort_order);
	
    // sort the right half using merge sort
    merge_sort(array, mid + 1, ub, n, sort_order);
	
    // finally merge the 2 sorted portion.
    merge(array, lb, mid, ub, n, sort_order);
}

/*
    Implementation of merge function for merge sort.
*/
void merge(int array[], int lb, int mid, int ub, int n, short sort_order)
{
	int *temp = (int *) malloc(n * sizeof(int));
	
    if (temp == NULL)
	{
        printf("\nUnable to allocate dynamic memory for merge sort!\n");
        exit(1);
    }
	
    register int i, j, k;
	
    for(i = lb, j = mid + 1, k = lb; i <= mid && j <= ub; k++)
	{
		if(sort_order == 0)
		{
			if (array[i] <= array[j])
				temp[k] = array[i++];
			else
				temp[k] = array[j++];
		}
		else
		{
			if (array[i] >= array[j])
				temp[k] = array[i++];
			else
				temp[k] = array[j++];
		}
    }
	
    // copy the additional elements, if any there in the sorted sections
    while(i <= mid)
        temp[k++] = array[i++];

    while(j <= ub)
        temp[k++] = array[j++];

    // finally copy back the merged sorted numbers from temp to array
    for(i = lb; i <= ub; i++)
        array[i] = temp[i];
	
	free(temp);
}

//---------------------------------------------------------------
void heap_sort(int array[], int n, short sort_order)
{
    // calling heapify for building the heap in place
    heapify(array, n, sort_order);
	
    // doing the heap sort.
    for(register int i = n, temp; i >= 2; i--)
	{
        // getting the largest element from the root
        temp = array[1];
		
        // copying the last element from the heap into the root.
        array[1] = array[i];
		
        // adjust the root
        adjust(array, 1, i - 1, sort_order);
		
        //place the largest element that we just deleted into the index i
        array[i] = temp;
    }
}

void heapify(int array[], int n, short sort_order)
{
    for(register int i = n / 2; i >= 1; i--)
        adjust(array, i, n, sort_order);
}

void adjust(int heap_array[], register int i, int n, short sort_order)
{
    register int j = 2 * i; // left child of i
    int item = heap_array[i];  // getting the content of the index i in variable temp
    
    // iterate as long as j is valid, that means there is an element at j
    while(j <= n)
	{
		if(sort_order == 0)
		{
			// compare between j and its sibling if sibling exists
			if(j < n && heap_array[j] < heap_array[j + 1])
				j++;
			
			if (item >= heap_array[j])
				break;
		}
		else
		{
			// compare between j and its sibling if sibling exists
			if(j < n && heap_array[j] > heap_array[j + 1])
				j++;
			
			if (item <= heap_array[j])
				break;
		}
		
        heap_array[j / 2] = heap_array[j];
        j *= 2;
    }
    heap_array[j / 2] = item;
}

//---------------------------------------------------------------
void ozer_sort(int array[], int n, short sort_order)
{
    for(register int flag = 0, i = 0; i < n && !flag; i++)
    {
        flag = 1;

        for(register int j = i + 1; j < n; j++)
        {
			if(sort_order == 0)
			{
				if(array[i] > array[j])
				{
					int temp = array[i];
					array[i] = array[j];
					array[j] = temp;
					flag = 0;
				}
			}
			else
			{
				if(array[j] > array[i])
				{
					int temp = array[i];
					array[i] = array[j];
					array[j] = temp;
					flag = 0;
				}
			}
        }
    }
}

//---------------------------------------------------------------
short check_sorted(int array[], int n, short sort_order)
{
    short sorted = 1;

    for(register int i = 0; i < n - 1 && sorted; i++)
	{
        if (sort_order == 0 && array[i] > array[i+1])
            sorted = 0;

        else if (sort_order == 1 && array[i] < array[i+1])
            sorted = 0;
    }
    return sorted;
}