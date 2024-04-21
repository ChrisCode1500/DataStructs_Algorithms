#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <math.h>
#include <float.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

#define BUFFLEN 100

// ARRAYLIST IMPLEMENTATION

struct ArrayList
{
    size_t length;   // current number of actual elements
    size_t capacity; // total available allocated space
    int *data;       // pointer to beginning of the data array
};

struct ArrayList createArrayList()
{
    return (struct ArrayList){0, 0, NULL};
}

void destroyArrayList(struct ArrayList *list)
{
    if (list == NULL)
    {
        return; // if it's null, we don't need to free anything. Just return
    }
    if (list->data != NULL)
    {
        free(list->data);
    }
    list->length = 0;
    list->capacity = 0;
}

bool isEmpty(struct ArrayList *list)
{
    if (list == NULL)
    {
        return false;
    }
    if (list->length == 0)
    {
        return true;
    }
    return false;
}

size_t getLength(struct ArrayList *list)
{
    return list->length;
}

size_t getCapacity(struct ArrayList *list)
{
    return list->capacity;
}

int getItemAtIndex(struct ArrayList *list, size_t index, int *targetValue)
{
    if (list == NULL)
    {
        return -1;
    }
    if (index >= list->length)
    {
        return -2;
    }
    *targetValue = list->data[index];
    return 0;
}

int getIndexOf(struct ArrayList *list, int value, size_t *targetIndex)
{
    if (list == NULL)
    {
        return -1;
    }

    for (int i = 0; i < list->length; i++)
    {
        if (list->data[i] == value)
        {
            *targetIndex = i;
            break;
        }
        if (i == list->length - 1 && list->data[i] != value)
        {
            return -2;
        }
    }

    return 0;
}

int updateValueAtIndex(struct ArrayList *list, int value, size_t index)
{
    if (list == NULL)
    {
        return -1;
    }
    if (index >= list->length)
    {
        return -2;
    }

    list->data[index] = value;

    return 0;
}

int appendItem(struct ArrayList *list, int value)
{
    if (list == NULL)
    {
        return -1;
    }

    if (list->data == NULL)
    {
        list->data = malloc(sizeof(int) * 2);
        if (list->data == NULL)
        { // this is saying if malloc failed
            return -2;
        }
        list->capacity = 2;
        list->data[0] = value;
        list->length = 1;
        return 0;
    }

    if (list->length == list->capacity)
    {
        int *newData = malloc(sizeof(int) * list->capacity * 2);
        if (newData == NULL)
        { // this is saying if malloc failed
            return -2;
        }
        for (int i = 0; i < list->length; i++)
        {
            newData[i] = list->data[i];
        }
        free(list->data);
        list->data = newData;
        list->capacity *= 2;
    }

    list->data[list->length] = value;
    list->length++;
    return 0;
}

int insertItemAtIndex(struct ArrayList *list, int value, size_t index)
{
    // insert the given value at the given index
    if (list == NULL)
    {
        return -1;
    }
    if (list->length == list->capacity)
    {
        return -2;
    }
    if (index >= list->length)
    {
        return -3;
    }

    for (int i = list->length - 1; i >= index; i--)
    {
        list->data[i + 1] = list->data[i];
    }

    list->data[index] = value;
    list->length++;

    // if the list is full, double the capacity and copy any data as necessary
    if (list->length < list->capacity / 4)
    {
        int *newData = malloc(sizeof(int) * list->capacity / 2);
        if (newData == NULL)
        { // this is saying if malloc failed
            return -2;
        }
        for (int i = 0; i < list->length; i++)
        {
            newData[i] = list->data[i];
        }
        free(list->data);
        list->data = newData;
        list->capacity /= 2;
    }
    return 0;
}

int removeItemAtIndex(struct ArrayList *list, size_t index)
{
    // remove the item at the given index
    if (list == NULL)
    {
        return -1;
    }
    if (index >= list->length)
    {
        return -2;
    }

    for (int i = index; i < list->length - 1; i++)
    {
        list->data[i] = list->data[i + 1];
    }
    list->length -= 1;
    // if the list is less than 1/4 full, halve the capacity and copy any data as necessary
    if (list->length < list->capacity / 4)
    {
        int *newData = malloc(sizeof(int) * list->capacity / 2);
        if (newData == NULL)
        { // this is saying if malloc failed
            return -2;
        }
        for (int i = 0; i < list->length; i++)
        {
            newData[i] = list->data[i];
        }
        free(list->data);
        list->data = newData;
        list->capacity /= 2;
    }

    return 0;
}

void merge(struct ArrayList* arr, struct ArrayList* left_array, struct ArrayList* right_array, int size_left_array, int size_right_array)
{
    int i = 0;
    int j = 0;
    int k = 0;

    while (i < size_left_array && j < size_right_array)
    {
        if (left_array->data[i] < right_array->data[j])
        {
            arr->data[k] = left_array->data[i];
            i++;
        }
        else
        {
            arr->data[k] = right_array->data[j];
            j++;
        }
        k++;
    }

    while (i < size_left_array)
    {
        arr->data[k] = left_array->data[i];
        i++;
        k++;
    }

    while (j < size_right_array)
    {
        arr->data[k] = right_array->data[j];
        j++;
        k++;
    }
}

int mergeSort(struct ArrayList* arr, size_t arrSize)
{
    // base case
    if (arrSize == 1)
    {
        // array is sorted
        return 0;
    }

    int middle = (arrSize - 1) / 2;
    int size_left_array = middle + 1;
    int size_right_array = arrSize - 1 - middle;

    // struct ArrayList* left_array = malloc(sizeof(int) * size_left_array);
    struct ArrayList left_array = createArrayList();
    
    if (!isEmpty(&left_array))
    {
        destroyArrayList(&left_array);
        return -2;
    }

    for (int i = 0; i < size_left_array; i++)
    {
        appendItem(&left_array, arr->data[i]);
    }
    int result = mergeSort(&left_array, size_left_array);
    if (result != 0)
    {
        destroyArrayList(&left_array);
        return -3;
    }

    struct ArrayList right_array = createArrayList();
    if (!isEmpty(&right_array))
    {
        destroyArrayList(&left_array);
        return -2;
    }

    for (int i = 0; i < size_right_array; i++)
    {        
        appendItem(&right_array, arr->data[i + size_left_array]);
    }
    result = mergeSort(&right_array, size_right_array);
    if (result != 0)
    {
        destroyArrayList(&right_array);
        destroyArrayList(&left_array);
        return -3;
    }

    merge(arr, &left_array, &right_array, size_left_array, size_right_array);
    destroyArrayList(&left_array);
    destroyArrayList(&right_array);

    return 0;
}