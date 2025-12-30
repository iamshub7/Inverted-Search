#include "main.h"
#include <stdio.h>
#include <string.h>

void save_database(Table* table)
{
    int cont = 1;
    char file[256];
    while (cont)
    {
        printf("Enter the file that you want to save: ");
        getchar();
        scanf("%255s", file);
        if (strstr(file, ".txt") != NULL)
        {
            cont = 0;
        }
        else
        {
            printf("Enter valid file name\n");
        }
    }
    FILE* fptr = fopen(file, "w");
    if (!fptr)
    {
        printf("ERROR: Could not open %s for writing\n", file);
        return;
    }
    for (int i = 0; i < 27; i++)
    {
        if (table[i].main_link == NULL)
        {
            continue;
        }
        Main* main = table[i].main_link;
        while (main != NULL)
        {
            fprintf(fptr, "#%d;%s;%d", i, main->word, main->file_count);
            int count = main->file_count;
            Sub* sub = main->sub_link;
            while (sub != NULL)
            {
                fprintf(fptr, ";%s;%d", sub->file_name, sub->word_count);
                sub = sub->sub_link;
            }
            fprintf(fptr, ";#\n");
            main = main->main_link;
        }
    }
    fclose(fptr);
    printf("SUCCESS: Database saved successfully to %s\n", file);
}