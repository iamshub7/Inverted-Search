#include "main.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int check_word(char* file_name, Sub* temp1, Sub** prev)
{
    while (temp1 != NULL)
    {
        if (strcmp(file_name, temp1->file_name) == 0)
        {
            *prev = temp1; // set prev to the matched node
            return 0;
        }
        *prev = temp1;
        temp1 = temp1->sub_link;
    }
    return 1;
}

void insert_into_hash_table(Table* table, int index, char* word, char* file_name)
{
    Main* new = (Main*)malloc(sizeof(Main));
    Sub* sub_new = (Sub*)malloc(sizeof(Sub));
    table[index].main_link = new;
    new->file_count = 1;
    new->main_link = NULL;
    new->sub_link = sub_new;
    strncpy(new->word, word, max_len - 1);
    new->word[max_len-1] = '\0';
    sub_new->word_count = 1;
    sub_new->sub_link = NULL;
    strncpy(sub_new->file_name, file_name, max_len - 1);
    sub_new->file_name[max_len-1] = '\0';
}

void create_database(Slist* head, Table* table)
{
    Slist* temp = head;
    while (temp != NULL)
    {
        char word[ max_len ];
        FILE* fptr = fopen(temp->file_name, "r");
        if (!fptr)
        {
            printf("WARNING: Could not open %s - skipping\n", temp->file_name);
            temp = temp->link;
            continue;
        }
        while (fscanf(fptr, "%19s", word) != EOF)
        {
            int number = 0;
            if (word[0] >= 'A' && word[0] <= 'Z')
            {
                word[0] = word[0] + 32; // to lower
            }
            else if (word[0] >= '0' && word[0] <= '9')
            {
                number = 1;
            }
            else if (word[0] >= 'a' && word[0] <= 'z')
            {
                number = 0;
            }
            else
            {
                number = 1;
            }
            int index;
            if (number == 0)
            {
                index = word[0] % 97; // 'a' -> 0
            }
            else
            {
                index = 26;
            }
            if (table[index].main_link == NULL)
            {
                insert_into_hash_table(table, index, word, temp->file_name);
            }
            else
            {
                Main* main = table[index].main_link;
                Main* prev = NULL;
                int flag = 0;
                while (main != NULL)
                {
                    if (strcmp(main->word, word) == 0)
                    {
                        Sub* sub = main->sub_link;
                        Sub* sub_prev = NULL;
                        int res = check_word(temp->file_name, sub, &sub_prev);
                        if (res == 0)
                        {
                            // found existing file -> increase word count in that subnode
                            // sub_prev points to matched node
                            sub_prev->word_count++;
                            flag = 1;
                            break;
                        }
                        else
                        {
                            // add new subnode at end
                            Sub* new_sub = (Sub*)malloc(sizeof(Sub));
                            new_sub->sub_link = NULL;
                            strncpy(new_sub->file_name, temp->file_name, max_len-1);
                            new_sub->file_name[max_len-1] = '\0';
                            new_sub->word_count = 1;
                            // attach
                            Sub* it = main->sub_link;
                            if (it == NULL)
                            {
                                main->sub_link = new_sub;
                            }
                            else
                            {
                                while (it->sub_link != NULL) it = it->sub_link;
                                it->sub_link = new_sub;
                            }
                            main->file_count++;
                            flag = 1;
                            break;
                        }
                    }
                    prev = main;
                    main = main->main_link;
                }
                if (flag == 0)
                {
                    // create new main node and attach at end
                    Main* main_node = (Main*)malloc(sizeof(Main));
                    main_node->main_link = NULL;
                    main_node->sub_link = NULL;
                    main_node->file_count = 1;
                    strncpy(main_node->word, word, max_len-1);
                    main_node->word[max_len-1] = '\0';
                    // new subnode
                    Sub* sub_new = (Sub*)malloc(sizeof(Sub));
                    sub_new->sub_link = NULL;
                    sub_new->word_count = 1;
                    strncpy(sub_new->file_name, temp->file_name, max_len-1);
                    sub_new->file_name[max_len-1] = '\0';
                    main_node->sub_link = sub_new;
                    if (prev)
                        prev->main_link = main_node;
                }
            }
        }
        printf("Successfully created database for %s\n", temp->file_name);
        fclose(fptr);
        temp = temp->link;

    }
    printf("SUCCESS: DataBase Created Successfully\n");
}