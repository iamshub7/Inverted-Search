#include "main.h"
#include <stdio.h>
#include <stdlib.h>

void create_HT(Table *HT)
{
    for (int i = 0; i < 27; i++)
    {
        HT[i].key = i;
        HT[i].main_link = NULL;
    }
}
int main(int argc, char *argv[])
{
    Slist *head = NULL;
    Table table[27];
    create_HT(table);
    printf("\n==============================================\n");
    printf("          WELCOME TO INVERTED SEARCH\n");
    printf("==============================================\n");

    if (argc != 1)
    {
        if (read_and_validate_arguments(argv, argc, &head) == FAILURE)
        {
            return 0;
        }
        int cont = 1;
        int created = 0;
        int updated = 0;

    // infinite menu loop
    while (1)
    {
        printf("\n==============================================\n");
        printf("                 MAIN MENU\n");
        printf("==============================================\n");
        printf("1. Create Database\n");
        printf("2. Search Word\n");
        printf("3. Display Database\n");
        printf("4. Update Database\n");
        printf("5. Save Database\n");
        printf("6. Exit\n");
        printf("----------------------------------------------\n");
        printf("Enter your choice : ");
        int opt;
            if (scanf("%d", &opt) != 1) { printf("Invalid input\n"); break; }
            switch (opt)
            {
                case 1:
                    if (created == 0)
                    {
                        create_database(head, table);
                        created = 1;
                    }
                    else
                    {
                        printf("ERROR: you cant create a data base again\n");
                    }
                    break;
                case 2:
                    search_database(table);
                    break;
                case 3:
                    display_database(table);
                    break;
                case 4:
                    if (created == 0 && updated == 0)
                    {
                        int real = 0;
                        if (update_database(table, &head, &real) == SUCCESS)
                        {
                            updated = 1;
                        }
                    }
                    else
                    {
                        printf("ERROR: You have already Updated. You cant Re-Update DataBase\n");
                    }
                    break;
                case 5:
                    save_database(table);
                    break;
                case 6:
                    printf("\nExiting... Thank you for using Inverted Search!\n");
                    return 0;
                default:
                    printf("INVALID!, Enter valid option\n");
            }
        }
    }
    else
    {
        printf("ERROR: Enter valid number of arguments\n");
    }
    return 0;
}
