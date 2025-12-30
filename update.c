#include "main.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int delete_node(Slist** head, char* file_name)
{
    Slist* temp = *head;
    Slist* prev = NULL;
    while (temp != NULL)
    {
        if (strcmp(temp->file_name, file_name) == 0)
        {
            if (prev == NULL)
            {
                *head = temp->link;
                free(temp);
                return 0;
            }
            prev->link = temp->link;
            free(temp);
            return 0;
        }
        prev = temp;
        temp = temp->link;
    }
    return 1;
}

Status update_database(Table* table, Slist** head, int* real)
{
    printf("Enter the file you want to upload: ");
    char file[256];
    getchar();
    scanf("%255s", file);
    if (strstr(file, ".txt") == NULL)
    {
        printf("%s is not an valid argument\n", file);
        *real = 1;
        return FAILURE;
    }
    FILE* fptr = fopen(file, "r");
    if (fptr == NULL)
    {
        printf("ERROR: No file name %s\n", file);
        *real = 1;
        return FAILURE;
    }
    // Check header format expected (#index;word;filecount;...;#)
    char ch1;
    ch1 = fgetc(fptr);
    fseek(fptr, -1, SEEK_END);
    char ch2 = fgetc(fptr);
    rewind(fptr);
    if (ch1 == '#' && ch2 == '#')
    {
        while (fscanf(fptr, "%c", &ch1) != EOF)
        {
            char ind[4] = "\0\0\0\0";
            fscanf(fptr, "%[^;];", ind);
            int i = 0;
            int index = 0;
            while (ind[i])
            {
                index = index * 10 + (ind[i] - 48);
                i++;
            }
            char word[20];
            fscanf(fptr, "%[^;];", word);
            char file_cnt[4] = "\0\0\0\0";
            fscanf(fptr, "%[^;];", file_cnt);
            i = 0;
            int file_count = 0;
            while (file_cnt[i])
            {
                file_count = file_count * 10 + (file_cnt[i] - 48);
                i++;
            }
            for (int k = 0; k < file_count; k++)
            {
                char file_name[20];
                fscanf(fptr, "%[^;];", file_name);
                char word_cnt[4] = "\0\0\0\0";
                fscanf(fptr, "%[^;];", word_cnt);
                int j = 0;
                int word_count = 0;
                while (word_cnt[j])
                {
                    word_count = word_count * 10 + (word_cnt[j] - 48);
                    j++;
                }
                if (table[index].main_link == NULL)
                {
                    Main* new = (Main*)malloc(sizeof(Main));
                    Sub* sub_new = (Sub*)malloc(sizeof(Sub));
                    table[index].main_link = new;
                    new->file_count = file_count;
                    new->main_link = NULL;
                    new->sub_link = sub_new;
                    strncpy(new->word, word, max_len-1);
                    new->word[max_len-1] = '\0';
                    sub_new->word_count = word_count;
                    sub_new->sub_link = NULL;
                    strncpy(sub_new->file_name, file_name, max_len-1);
                    sub_new->file_name[max_len-1] = '\0';
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
                            Sub* sub_node_link = (Sub*)malloc(sizeof(Sub));
                            sub_node_link->word_count = word_count;
                            strncpy(sub_node_link->file_name, file_name, max_len-1);
                            sub_node_link->file_name[max_len-1] = '\0';
                            sub_node_link->sub_link = NULL;
                            Sub* sub_nlink = main->sub_link;
                            Sub* prev_sub = NULL;
                            while (sub_nlink != NULL)
                            {
                                prev_sub = sub_nlink;
                                sub_nlink = sub_nlink->sub_link;
                            }
                            if (prev_sub == NULL)
                            {
                                main->sub_link = sub_node_link;
                            }
                            else
                            {
                                prev_sub->sub_link = sub_node_link;
                            }
                            flag = 1;
                            break;

                        }
                        prev = main;
                        main = main->main_link;
                    }
                    if (flag == 0)
                    {
                        Main* new = (Main*)malloc(sizeof(Main));
                        new->main_link = NULL;
                        new->sub_link = NULL;
                        new->file_count = file_count;
                        strncpy(new->word, word, max_len-1);
                        new->word[max_len-1] = '\0';
                        Sub* sub_new = (Sub*)malloc(sizeof(Sub));
                        sub_new->word_count = word_count;
                        sub_new->sub_link = NULL;
                        strncpy(sub_new->file_name, file_name, max_len-1);
                        sub_new->file_name[max_len-1] = '\0';
                        if (prev)
                            prev->main_link = new;
                    }

                }
            }
            fseek(fptr, 2, SEEK_CUR); // move past ;#\n
        }
    }
    else
    {
        printf("ERROR: thats not a valid file\n");
        *real = 1;
        fclose(fptr);
        return FAILURE;
    }
    fclose(fptr);

    // Remove uploaded files from the Slist head if already present in DB
    Slist* temp = *head;
    while (temp != NULL)
    {
        for (int i = 0; i < 27; i++)
        {
            if (table[i].main_link == NULL)
            {
                continue;
            }
            Main* main = table[i].main_link;
            while (main != NULL)
            {
                Sub* sub = main->sub_link;
                while (sub != NULL)
                {
                    if (strcmp(sub->file_name, temp->file_name) == 0)
                    {
                        delete_node(head, temp->file_name);
                        temp = *head; // restart scanning after deletion
                        break;
                    }
                    sub = sub->sub_link;
                }
                main = main->main_link;
            }
        }
        if (temp)
            temp = temp->link;
    }
    printf("SUCCESS: Update Successfully done\n");
    return SUCCESS;
}