#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "BSTFunctions.h"

int main()
{
    Node *rootNode = NULL, *tempNode;
    short choice;

    print_menu();
    printf("\n");

    while(1)
    {
        printf("\nPlease input your choice (1 to show menu): ");
        scanf("%hd", &choice);

        int data, howManyNode, endNum;

        switch(choice)
        {
            case 0:
                printf("\nThe program is terminated.\n\n");
                exit(0);

            case 1:
                print_menu();
                break;

            case 2:
                printf("Enter an integer: ");
                scanf("%d", &data);

                tempNode = create_node(data);

                if(rootNode == NULL)
                {
                    maxData = minData = data;
                    rootNode = tempNode;
                }
                else
                    insert_node(rootNode, tempNode);
                break;

            case 3:
                jump_case2a1:
                printf("\nThere will be random generation between 0 and N. Specify N value: ");
                scanf("%d", &endNum);

                if(endNum <= 0)
                {
                    printf("\nN value can't be equal or less than 0!");
                    goto jump_case2a1;
                }

                jump_case2a2:
                printf("Enter how many nodes do you want to create: ");
                scanf("%d", &howManyNode);

                if(howManyNode <= 0)
                {
                    printf("\nNumber of node can't be equal or less than 0!");
                    goto jump_case2a2;
                }

                rootNode = create_bst_randomly(rootNode, howManyNode, endNum);
                break;

            case 4:
                if(!check_tree(rootNode))
                    break;

                printf("\nInorder traversal:\n");
                inoder_traverse(rootNode);
                printf("\nMin data = %d, Max data = %d in the tree.\n", minData, maxData);
                break;

            case 5:
                if(!check_tree(rootNode))
                    break;

                printf("\nReverse inorder traversal:\n");
                reverse_inoder_traverse(rootNode);
                printf("\nMin data = %d, Max data = %d in the tree.\n", minData, maxData);
                break;

            case 6:
                if(!check_tree(rootNode))
                    break;

                printf("\nPreorder traversal:\n");
                preoder_traverse(rootNode);
                printf("\nMin data = %d, Max data = %d in the tree.\n", minData, maxData);
                break;

            case 7:
                if(!check_tree(rootNode))
                    break;

                printf("\nPostorder traversal:\n");
                postoder_traverse(rootNode);
                printf("\nMin data = %d, Max data = %d in the tree.\n", minData, maxData);
                break;

            case 8:
                if(!check_tree(rootNode))
                    break;

                tempNode = get_min(rootNode);
                printf("\nMinimum integer in the tree is: %d\n", tempNode->data);
                break;

            case 9:
                if(!check_tree(rootNode))
                    break;

                tempNode = get_max(rootNode);
                printf("\nMaximum integer in the tree is: %d\n", tempNode->data);
                break;

            case 10:
                if(!check_tree(rootNode))
                    break;
                else
                {
                    printf("\nEnter a data to find: ");
                    scanf("%d", &data);

                    if(check_data(rootNode, data))
                        printf("%d is in the tree.\n", data);
                    else
                        not_found_target_data_msg(data);
                }
                break;

            case 11:
                if(!check_tree(rootNode))
                    break;
                else
                {
                    printf("\nEnter a data to delete: ");
                    scanf("%d", &data);

                   rootNode = delete_node(rootNode, data);
                }
                break;

            case 12:
                if(!check_tree(rootNode))
                    break;
                else
                    rootNode = delete_minimum(rootNode);
                break;

            case 13:
                if(!check_tree(rootNode))
                    break;
                else
                    rootNode = delete_maximum(rootNode);
                break;

            case 14:
                if(!check_tree(rootNode))
                    break;
                else
                {
                    rootNode = delete_tree(rootNode);

                    if(rootNode == NULL)
                        printf("\nAll nodes are deleted.\n");
                }
                break;

            case 15:
                if(!check_tree(rootNode))
                    break;
                else
                {
                    printf("Enter a data to find its predecessor and successor: ");
                    scanf("%d", &data);

                    tempNode = rootNode;

                    if((tempNode = find_target_node(tempNode, data)) == NULL)
                        not_found_target_data_msg(data);
                    else
                    {
                        if(nodeCounter == 1)
                            printf("\nThere is no predecessor and successor, because there is one node in the tree.\n");
                        else if(data == minData)
                            printf("\nThere is no predecessor.\nBecause %d is the minimum integer in the tree.\nSuccessor = %d of target data %d.\n",
                                   data, get_successor(tempNode, rootNode, data)->data, data);
                        else if(data == maxData)
                            printf("\nThere is no successor.\nBecause %d is the maximum integer in the tree.\nPredecessor = %d of target data %d.\n",
                                   data, get_predecessor(tempNode, rootNode, data)->data, data);
                        else
                            printf("\nPredecessor = %d, and Successor = %d of target data %d.\n",
                                get_predecessor(tempNode, rootNode, data)->data, get_successor(tempNode, rootNode, data)->data, data);
                    }
                }
                break;

            case 16:
                if(!check_tree(rootNode))
                    break;

                printf("\nThere is/are %d node(s) in the tree.\n", nodeCounter);
                break;

            default:
                print_valid_msg();
                break;
        }
    }

    getch();
    return 0;
}
