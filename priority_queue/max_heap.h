#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef MAX_HEAP_H
#define MAX_HEAP_H

#define MAX_HEAP_CAPACITY 32
#define MAX_HEAP_BUFLEN 128 // max size of each string in the heap

typedef struct
{
    char data[MAX_HEAP_BUFLEN];
    size_t priority;
} heap_data; // a node

typedef struct
{
    heap_data data[MAX_HEAP_CAPACITY];
    size_t size;
} max_heap;

max_heap *max_heap_create()
{
    max_heap *heap = (max_heap *)malloc(sizeof(max_heap));
    if (heap == NULL)
    {
        return NULL;
    }
    heap->size = 0;
    return heap;
}

void max_heap_destroy(max_heap *heap)
{
    if (heap != NULL)
    {
        free(heap);
    }
}

size_t max_heap_size(max_heap *heap)
{
    // if the heap is NULL, return 0
    if (heap == NULL)
    {
        return 0;
    }
    return heap->size;
}

int max_heap_insert(max_heap *heap, char *data, size_t priority)
{
    // if the heap is NULL, return -1
    if (heap == NULL)
    {
        return -1;
    }
    // if the heap is full, return -2
    if (heap->size == MAX_HEAP_CAPACITY)
    {
        return -2;
    }
    // if the data is NULL or the priority is 0, return -3
    if (data == NULL || priority == 0)
    {
        return -3;
    }
    
    // this is where you want to "bubble up" the new node as much as you need to
    heap->data[heap->size].priority = priority;
    strncpy(heap->data[heap->size].data, data, MAX_HEAP_BUFLEN);    
    
    size_t current_index = heap->size;
    while (1)
    {
        size_t parent_index = (current_index - 1) / 2;
        size_t current_priority = heap->data[current_index].priority;
        size_t parent_priority = heap->data[parent_index].priority;
        if (current_priority > parent_priority)
        {
            // swap
            heap_data temp = heap->data[current_index];
            heap->data[current_index] = heap->data[parent_index];
            heap->data[parent_index] = temp;

            // move up tree
            current_index = parent_index;
        }
        else if (current_priority < parent_priority)
        {
            break;
        }
    }
    heap->size++;

    return 0;
}

int max_heap_remove(max_heap *heap, char *outData, size_t *outPriority)
{
    // if the heap is NULL, return -1
    if (heap == NULL)
    {
        return -1;
    }
    // if the heap is empty, return -2
    if (heap->size == 0)
    {
        return -2;
    }
    // if the outData or outPriority is NULL, return -3
    if (outData == NULL || outPriority == NULL)
    {
        return -3;
    }
    // copy the data and priority of the root node to outData and outPriority
    strncpy(outData, heap->data[0].data, MAX_HEAP_BUFLEN);
    *outPriority = heap->data[0].priority;

    // move the last element to the root 
    heap->data[0] = heap->data[heap->size - 1];
    // this is where you want to "boogie" the new root node as much as you need to
    size_t current_index = 0;
    while(1)
    {
        size_t left_child_index = (current_index * 2) + 1;
        size_t right_child_index = (current_index + 1) * 2;
        size_t max_index = current_index;
        size_t left_child_priority = heap->data[left_child_index].priority;
        size_t right_child_priority = heap->data[right_child_index].priority;
        
        if (left_child_index < heap->size && left_child_priority > heap->data[max_index].priority)
        {
            max_index = left_child_index;
        }
        if (right_child_index < heap->size && right_child_priority > heap->data[max_index].priority)
        {
            max_index = right_child_index;
        }

        if (max_index != current_index)
        {
            heap_data temp = heap->data[current_index];
            heap->data[current_index] = heap->data[max_index];
            heap->data[max_index] = temp;
            current_index = max_index;
        }
        else
        {
            break;
        }
    }

    heap->size--;

    return 0;
}

int max_heap_peek(max_heap *heap, char *outData, size_t *outPriority)
{
    // if the heap is NULL, return -1
    if (heap == NULL)
    {
        return -1;
    }
    // if the heap is empty, return -2
    if (heap->size == 0)
    {
        return -2;
    }
    // if the outData or outPriority is NULL, return -3
    if (outData == NULL || outPriority == NULL)
    {
        return -3;
    }
    // copy the data and priority of the root node to outData and outPriority
    strncpy(outData, heap->data[0].data, MAX_HEAP_BUFLEN);
    *outPriority = heap->data[0].priority;
    return 0;
}

#endif // MAX_HEAP_H
