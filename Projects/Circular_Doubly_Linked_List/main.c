#include <stdio.h>
#include <stdlib.h>
#include "CDLL_Functions.h"

int main()
{
    Linked_List linked_list_object;
    initialization_list(&linked_list_object);

    menu();

    short choice;
    char decision, file_name[21];
    Node *current = NULL, *previous = NULL, *next = NULL;
    int data, how_many, end_num, target;

    while(1)
    {
        printf("Please input your choice (1 to show menu): ");
        scanf("%hd", &choice);

        switch(choice)
        {
            case 0:
                printf("\nThe program is terminated.\n\n");
                exit(0);

            case 1:
                menu();
                break;

            case 2:
                enter_msg();
                scanf("%d", &data);

                if(insert_at_head(&linked_list_object, data))
                    printf("\nData is inserted successfully at head.\n\n");
                else
                    error_data_msg();
                break;

            case 3:
                enter_msg();
                scanf("%d", &data);

                if(insert_at_tail(&linked_list_object, data))
                    printf("\nData is inserted successfully at tail.\n\n");
                else
                    error_data_msg();
                break;

            case 4:
                enter_msg();
                scanf("%d", &data);

                if(insert_in_ascending(&linked_list_object, data))
                    printf("\nData is inserted successfully in ascending way.\n\n");
                else
                    error_data_msg();
                break;

            case 5:
                enter_msg();
                scanf("%d", &data);

                if(insert_in_descending(&linked_list_object, data))
                    printf("\nData is inserted successfully in descending way.\n\n");
                else
                    error_data_msg();
                break;

            case 6:
                printf("Enter the file name with its file format (e.g. mix.txt): ");
                scanf(" %[^\n]", file_name);

                if(load_from_file(&linked_list_object, file_name))
                    printf("\nFile has been loaded successfully.\n\n");
                else
                    printf("\nThere was some error while loading and creating the list!\n\n");
                break;

            case 7:
                jump_case7:
                printf("There will be random generation between 0 and N. Specify N value: ");
                scanf("%d", &end_num);

                if(end_num <= 0)
                {
                    printf("N value can't be equal or less than 0!\n");
                    goto jump_case7;
                }

                printf("Enter how many random values that you want it to be generated: ");
                scanf("%d", &how_many);

                if(create_list_with_random(&linked_list_object, how_many, end_num))
                    printf("\nLinked list is created by generating random values.\n\n");
                else
                    error_data_msg();
                break;

            case 8:
                jump_case8:
                printf("Do you want to print the list in reverse? (Y/N): ");
                scanf(" %c", &decision);

                if(decision == 'y' || decision == 'Y' || decision == 'n' || decision == 'N')
                    print_linked_list_detail(&linked_list_object, decision);
                else
                {
                    enter_valid_char();
                    goto jump_case8;
                }
                break;

            case 9:
                jump_case9:

                printf("Do you want to print the list in reverse? (Y/N): ");
                scanf(" %c", &decision);

                if(decision == 'y' || decision == 'Y' || decision == 'n' || decision == 'N')
                    print_linked_list(&linked_list_object, decision);
                else
                {
                    enter_valid_char();
                    goto jump_case9;
                }
                break;

            case 10:
                printf("Enter target number to find: ");
                scanf("%d", &data);

                current = find_target(&linked_list_object, data, &next, &previous);

                if (current == NULL)
                    find_error_msg();
                else
                  printf("\nAddress of the target node: %p\n"
                        "previous node address: %p, and next node address: %p\n\n", current, previous, next);
                break;

            case 11:
                printf("Enter target number to add after: ");
                scanf("%d", &target);

                current = find_target(&linked_list_object, target, &next, &previous);

                if(current == NULL)
                    find_error_msg();
                else
                {
                    enter_msg();
                    scanf("%d", &data);

                    if(insert_after(&linked_list_object, current, data))
                        printf("\nData is inserted after the target node successfully.\n\n");
                    else
                        error_data_msg();
                }
                break;

            case 12:
                printf("Enter target number to add before: ");
                scanf("%d", &target);

                current = find_target(&linked_list_object, target, &next, &previous);

                if(current == NULL)
                    find_error_msg();
                else
                {
                    enter_msg();
                    scanf("%d", &data);

                    if(insert_before(&linked_list_object, current, data))
                        printf("\nData is inserted before the target node successfully.\n\n");
                    else
                        error_data_msg();
                }
                break;

            case 13:
                data = delete_first(&linked_list_object);

                if(data != -99899)
                    printf("\nDeleted first node data is: %d\n\n", data);
                else
                    print_empty_msg();
                break;

            case 14:
                data = delete_last(&linked_list_object);

                if(data != -99899)
                    printf("\nDeleted last node data is: %d\n\n", data);
                else
                    print_empty_msg();
                break;

            case 15:
                printf("Enter target integer to delete it: ");
                scanf("%d", &target);

                current = find_target(&linked_list_object, target, &next, &previous);

                if(current == NULL)
                    find_error_msg();
                else
                    printf("\nData of deleted target node is: %d.\n\n", delete_target(&linked_list_object, current));
                break;

            case 16:
                printf("Enter target integer to delete after: ");
                scanf("%d", &target);

                current = find_target(&linked_list_object, target, &next, &previous);

                if(current == NULL)
                    find_error_msg();
                else
                    printf("\nData of deleted target node is: %d.\n\n", delete_after_target(&linked_list_object, current));
                break;

            case 17:
                printf("Enter target integer to delete before: ");
                scanf("%d", &target);

                current = find_target(&linked_list_object, target, &next, &previous);

                if(current == NULL)
                    find_error_msg();
                else
                    printf("\nData of deleted target node is: %d.\n\n", delete_before_target(&linked_list_object, current));
                break;

            case 18:
                jump_case18:

                printf("\nThere are two options.\n1. Just reverse the linked list data.\n"
                       "2. Reverse addresses of the linked list.\nWhat's your choice: ");
                scanf(" %c", &decision);

                if(decision == '1')
                {
                    if(reverse_data(&linked_list_object))
                        print_linked_list_detail(&linked_list_object, 'n');
                    else
                        error_reverse_msg();
                }
                else if(decision == '2')
                {
                    if(reverse_address(&linked_list_object))
                        print_linked_list_detail(&linked_list_object, 'n');
                    else
                        error_reverse_msg();
                }
                else
                {
                    print_valid_msg();
                    goto jump_case18;
                }
                break;

            case 19:
                jump_case19:

                printf("\n1. Sort in ascending order.\n2. Sort in descending order.\nWhat's your choice: ");
                scanf(" %c", &decision);

                if(decision == '1' || decision == '2')
                {
                    if(sort(&linked_list_object, decision))
                        print_linked_list_detail(&linked_list_object, 'n');
                    else
                        printf("\nLinked list is empty or has one node!\n\n");
                }
                else
                {
                    print_valid_msg();
                    goto jump_case19;
                }
                break;

            default:
                print_valid_msg();
                break;
        }
    }
    return 0;
}
