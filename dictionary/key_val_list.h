#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef KEY_VAL_LIST_H
#define KEY_VAL_LIST_H

#define MAX_KEY_LEN 100

typedef struct
{
    char key[MAX_KEY_LEN];
    int value;
} key_val;

// Forward declare the key_val_list_node type
typedef struct key_val_list_node key_val_list_node;

// Define the key_val_list_node struct
struct key_val_list_node
{
    key_val data;
    key_val_list_node *next;
};

typedef struct
{
    key_val_list_node *head;
    key_val_list_node *tail;
    size_t size;
} key_val_list;

key_val_list key_val_list_create()
{
    key_val_list list;
    list.head = NULL;
    list.tail = NULL;
    list.size = 0;
    return list;
}

size_t key_val_list_size(key_val_list *list)
{
    if (list == NULL)
        return 0;
    return list->size;
}

int key_val_list_add(key_val_list *list, char *key, int value)
{
    if (list == NULL)
    {
        return -1;
    }

    // ensure the key does not already exist:
    key_val_list_node *current = list->head;
    while (current != NULL)
    {
        // the strcmp function returns 0 if the strings are equal
        if (strcmp(current->data.key, key) == 0)
        {
            return -2;
        }
        current = current->next;
    }

    key_val_list_node *new_node = malloc(sizeof(key_val_list_node));
    if (new_node == NULL)
    {
        return -3;
    }
    
    strncpy(new_node->data.key, key, MAX_KEY_LEN - 1);
    new_node->data.key[MAX_KEY_LEN - 1] = '\0';

    new_node->data.value = value;
    new_node->next = NULL;

    if (list->size == 0)
    {
        // special case for the first node to be added
        list->head = new_node;
        list->tail = new_node;
    }
    else
    {
        list->tail->next = new_node;
        list->tail = new_node;
    }
    list->size++;
    return 0;
}

int key_val_list_remove(key_val_list *list, char *key)
{
    if (list == NULL)
    {
        return -1;
    }
    key_val_list_node *current = list->head;
    key_val_list_node *previous = NULL;
    while (current != NULL)
    {
        if (strcmp(current->data.key, key) == 0)
        {
            // found it!
            if (previous == NULL)
            {
                // we are removing the head
                list->head = current->next;
            }
            else
            {
                previous->next = current->next;
            }
            if (current == list->tail)
            {
                // we are removing the tail
                list->tail = previous;
            }
            free(current);
            list->size--;
            return 0;
        }
        previous = current;
        current = current->next;
    }
    return -2;
}

// function to free all the memory used by the list
void key_val_list_destroy(key_val_list *list)
{
    if (list == NULL)
    {
        return;
    }
    key_val_list_node *current = list->head;
    key_val_list_node *next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

// function to update the value of a key in the list
int key_val_list_update(key_val_list *list, char *key, int newValue)
{
    // if the list is NULL, return -1
    if (list == NULL)
    {
        return -1;
    }
    key_val_list_node *current = list->head;    
    
    while (current != NULL)
    {
        if (strcmp(current->data.key, key) == 0)
        {                   
            current->data.value = newValue;
            return 0;
        }
        current = current->next;
    }

    // key not found
    return -2;
}

// function to find a key in the list and return its value
int key_val_list_fetch(key_val_list *list, const char *key, int *target)
{
    // if the list is NULL, return -1
    if (list == NULL)
    {
        return -1;
    }
    key_val_list_node *current = list->head;

    while(current != NULL)
    {
        if (strcmp(current->data.key, key) == 0)
        {
            *target = current->data.value;
            // otherwise return 0
            return 0;
        }
        current = current->next;
    }
    // if the key is not found, return -2
    return -2;
}

// used for debugging:
void key_val_list_print_all(key_val_list *list)
{
    // if the list is NULL, return
    if (list == NULL)
    {
        return;
    }
    key_val_list_node *current = list->head;
    // prints the elements of the list one on each line
    while (current != NULL)
    {
        printf("%s: %d\n", current->data.key, current->data.value);
        current = current->next;
    }
}

#endif // KEY_VAL_LIST_H
