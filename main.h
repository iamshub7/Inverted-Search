#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_table 27
#define max_len 20

typedef enum
{
    FAILURE,
    SUCCESS
} Status;

typedef struct sub_node
{
    char file_name[max_len];
    int word_count;
    struct sub_node* sub_link;
} Sub;

typedef struct main_node
{
    char word[max_len];
    int file_count;
    struct main_node* main_link;
    struct sub_node* sub_link;
} Main;

typedef struct hash_table
{
    int key;
    struct main_node* main_link;
} Table;

typedef struct node
{
    char file_name[max_len];
    struct node* link;
} Slist;

/* Function prototypes */
Status read_and_validate_arguments(char* argv[], int argc, Slist** head);
void create_database(Slist* head, Table* table);
void display_database(Table* table);
void save_database(Table* table);
void search_database(Table* table);
Status update_database(Table* table, Slist** head, int* real);
int delete_node(Slist** head, char* file_name);

#endif
