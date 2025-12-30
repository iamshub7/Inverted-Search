#include "main.h"
#include <stdio.h>

void display_database(Table* table)
{
    printf("\nDatabase details:\n");
    for (int i = 0; i < 27; i++)
    {
        if (table[i].main_link == NULL)
        {
            continue;
        }
        Main* main = table[i].main_link;
        while (main != NULL)
        {
            printf("%2d    %-10s    %d    ", i, main->word, main->file_count);
            int count = main->file_count;
            Sub* sub = main->sub_link;
            while (sub != NULL)
            {
                printf("%-10s --> %d    ", sub->file_name, sub->word_count);
                sub = sub->sub_link;
            }
            main = main->main_link;
            printf("\n");
        }
    }
}
