#include <stdio.h>
#include <stdlib.h>

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

struct list_node
{
    int data;
    struct list_node *next;
};

struct linked_list
{
    size_t length;
    struct list_node *head;
    struct list_node *tail;
};

struct linked_list create_new_linked_list()
{
    struct linked_list output;
    output.length = 0;
    output.head = NULL;
    output.tail = NULL;
    return output;
}

size_t linked_list_length(struct linked_list *lst)
{
    if (lst == NULL)
    {
        return 0;
    }

    return lst->length;
}

int linked_list_append(struct linked_list *lst, int new_val)
{
    // if lst is NULL return -1
    // if you fail to allocate heap memory return -2
    // otherwise return 0

    if (lst == NULL)
    {
        return -1;
    }

    struct list_node *new_node = malloc(sizeof(struct list_node));

    if (new_node == NULL)
    {
        return -2;
    }

    new_node->data = new_val;
    new_node->next = NULL;

    if (lst->length == 0)
    {
        lst->head = new_node;
        lst->tail = new_node;
    }
    else
    {
        lst->tail->next = new_node;
        lst->tail = new_node;
    }

    lst->length += 1;
    return 0;
}

int linked_list_prepend(struct linked_list *lst, int new_val)
{
    // if lst is NULL return -1
    // if you fail to allocate heap memory return -2
    // otherwise return 0
    if (lst == NULL)
    {
        return -1;
    }

    if (lst->length == 0)
    {
        struct list_node *new_node = malloc(sizeof(struct list_node));
        if (new_node == NULL)
        {
            return -2;
        }
        new_node->data = new_val;
        new_node->next == NULL;
        lst->head = new_node;
        lst->tail = new_node;
        lst->length += 1;
        return 0;
    }

    struct list_node *new_node = malloc(sizeof(struct list_node));
    if (new_node == NULL)
    {
        return -2;
    }

    new_node->data = new_val;
    new_node->next = lst->head;
    lst->head = new_node;
    lst->length += 1;
    return 0;
}

int linked_list_insert_at_index(
    struct linked_list *lst,
    int new_val,
    size_t index)
{
    // if lst is NULL return -1
    // if index is out of bounds return -3
    // if you fail to allocate heap memory return -2
    // otherwise return 0
    if (lst == NULL)
    {
        return -1;
    }

    if (index >= lst->length)
    {
        return -3;
    }

    if (index == 0)
    {
        return linked_list_prepend(lst, new_val);
    }

    struct list_node *new_node = malloc(sizeof(struct list_node));
    if (new_node == NULL)
    {
        return -2;
    }

    new_node->data = new_val;
    struct list_node *current = lst->head;
    for (size_t i = 0; i < index - 1; i++)
    {
        current = current->next;
    }
    new_node->next = current->next;
    current->next = new_node;
    lst->length += 1;
    return 0;
}

int linked_list_fetch_at_index(
    struct linked_list *lst,
    size_t index,
    int *target)
{
    if (lst == NULL)
    {
        return -1;
    }
    if (index >= lst->length)
    {
        return -2;
    }
    struct list_node *current = lst->head;
    for (size_t i = 0; i < index; i++)
    {
        current = current->next;
    }
    *target = current->data;
    return 0;
}

int linked_list_remove_at_index(struct linked_list *lst, size_t index)
{
    // if lst is NULL return -1
    if (lst == NULL)
    {
        return -1;
    }
    // if index is out of bounds return -2
    if (index >= lst->length)
    {
        return -2;
    }
    if (lst->length == 1)
    {
        free(lst->head);
        lst->head = NULL;
        lst->tail = NULL;
        lst->length = 0;
    }
    if (index == 0)
    {
        struct list_node *temp = lst->head;
        lst->head = lst->head->next;
        free(temp);
        lst->length--;
        return 0;
    }
    // otherwise return 0
    struct list_node *previous_node;
    struct list_node *cursor = lst->head;
    for (int i = 0; i < index; i++)
    {
        previous_node = cursor;
        cursor = cursor->next;
    }

    previous_node->next = cursor->next;
    free(cursor);    
    lst->length--;
    
    return 0;
}

int linked_list_pop_front(struct linked_list * lst)
{
    if (lst == NULL)
    {
        return -1;
    }
    if (lst->length == 0)
    {
        return -2;
    }

    if (lst->length == 1)
    {
        free(lst->head);
        lst->head = NULL;
        lst->tail = NULL;
        lst->length = 0;
    }

    struct list_node * after_head = lst->head->next;
    free(lst->head);
    lst->head = after_head;

    return 0;
}

struct list_node *merge(struct list_node *left, struct list_node *right)
{
    struct list_node *result;

    if (left == NULL)
    {
        return right;
    }

    if (right == NULL)
    {
        return left;
    }

    if (left->data <= right->data)
    {
        result = left;
        result->next = merge(left->next, right);
    }
    else
    {
        result = right;
        result->next = merge(left, right->next);
    }

    return result;
}

struct list_node *mergeSort(struct list_node *head)
{
    if (head == NULL || head->next == NULL)
    {
        return head;
    }

    struct list_node *current = head;
    struct list_node *cursor = head->next;

    while (cursor != NULL && cursor->next != NULL)
    {
        current = current->next;
        cursor = cursor->next->next;
    }

    struct list_node *mid = current->next;
    current->next = NULL;

    struct list_node *left = mergeSort(head);
    struct list_node *right = mergeSort(mid);

    return merge(left, right);
}

void linked_list_sort(struct linked_list *lst)
{
    // if lst is NULL return
    if (lst == NULL)
    {
        return;
    }
    // if the list is empty return
    if (lst->length == 0)
    {
        return;
    }    
    // base case
    if (lst->length == 1)
    {        
        return;
    }

    if (lst->head == NULL || lst->head->next == NULL)
    {
        return;
    }

    struct list_node *current = lst->head;
    struct list_node *cursor = lst->head->next;

    while (cursor != NULL && cursor->next != NULL)
    {
        current = current->next;
        cursor = cursor->next->next;
    }

    struct list_node *mid = current->next;
    current->next = NULL;

    struct list_node *left = mergeSort(lst->head);
    struct list_node *right = mergeSort(mid);

    lst->head = merge(left, right);
}

void linked_list_print_all_elements(struct linked_list *lst)
{
    if (lst == NULL)
    {
        return;
    }
    struct list_node *current = lst->head;
    while (current != NULL)
    {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void destroy_linked_list(struct linked_list *lst)
{
    if (lst == NULL)
        return;

    struct list_node *current = lst->head;
    struct list_node *next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    lst->head = NULL;
    lst->tail = NULL;
    lst->length = 0;
}

void reverseLinkedList(struct linked_list * list) {
    struct list_node* cursor = list->head;
    struct linked_list temp = create_new_linked_list(); 

    while (cursor != NULL) 
    {
        linked_list_prepend(&temp, cursor->data);
        cursor = cursor->next;
    }

    list->tail = temp.tail;
    list->head = temp.head;
}

#endif // LINKED_LIST_H