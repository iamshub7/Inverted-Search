#include "main.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Status read_and_validate_arguments(char* argv[], int argc, Slist** head)
{
    int flag = 0;
    for (int i = 1; i < argc; i++)
    {
        if (strstr(argv[i], ".txt") == NULL)
        {
            printf("%s is not an valid argument\n", argv[i]);
            flag++;
            continue;
        }
        FILE* fptr = fopen(argv[i], "r");
        if (fptr == NULL)
        {
            printf("ERROR: No file name %s\n", argv[i]);
            flag++;
            continue;
        }
        fseek(fptr, 0, SEEK_END);
        unsigned long int set = ftell(fptr);
        if (set == 0)
        {
            printf("File opened but there is no data in %s\n", argv[i]);
            flag++;
            fclose(fptr);
            continue;
        }
        fclose(fptr);
        printf("FILE NAME %s is a valid FILE\n", argv[i]);
        if (*head == NULL)
        {
            Slist* new = (Slist*)malloc(sizeof(Slist));
            new->link = NULL;
            strncpy(new->file_name, argv[i], max_len-1);
            new->file_name[max_len-1] = '\0';
            *head = new;
        }
        else
        {
            Slist* temp = *head;
            Slist* prev = NULL;
            int flag1 = 0;
            while (temp != NULL)
            {
                if (strcmp(temp->file_name, argv[i]) == 0)
                {
                    printf("the file %s is a duplicate file\n", argv[i]);
                    flag1 = 1;
                    break;
                }
                prev = temp;
                temp = temp->link;
            }
            if (flag1 == 1)
            {
                flag++;
                continue;
            }
            Slist* new = (Slist*)malloc(sizeof(Slist));
            new->link = NULL;
            strncpy(new->file_name, argv[i], max_len-1);
            new->file_name[max_len-1] = '\0';
            prev->link = new;
        }

    }
    if (flag == argc - 1)
    {
        printf("ERROR: No files are valid files\n");
        return FAILURE;
    }
    return SUCCESS;
}
