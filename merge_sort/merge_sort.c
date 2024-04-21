#include <stdio.h>
#include <stdlib.h>

void merge(int* arr, int* left_array, int* right_array, int size_left_array, int size_right_array)
{
    int i = 0;
    int j = 0;
    int k = 0;

    while (i < size_left_array && j < size_right_array)
    {
        if (left_array[i] < right_array[j])
        {
            arr[k] = left_array[i];
            i++;
        }
        else
        {
            arr[k] = right_array[j];
            j++;
        }
        k++;
    }

    while (i < size_left_array)
    {
        arr[k] = left_array[i];
        i++;
        k++;
    }

    while (j < size_right_array)
    {
        arr[k] = right_array[j];
        j++;
        k++;
    }
}

int mergeSort(int* arr, size_t arrSize)
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

    int* left_array = malloc(sizeof(int) * size_left_array);
    if (left_array == NULL)
    {
        free(left_array);
        return -2;
    }

    for (int i = 0; i < size_left_array; i++)
    {
        left_array[i] = arr[i];
    }
    int result = mergeSort(left_array, size_left_array);
    if (result != 0)
    {
        free(left_array);
        return -3;
    }

    int* right_array = malloc(sizeof(int) * size_right_array);
    if (right_array == NULL)
    {
        free(left_array);
        return -2;
    }

    for (int i = 0; i < size_right_array; i++)
    {
        right_array[i] = arr[i + size_left_array];
    }
    result = mergeSort(right_array, size_right_array);
    if (result != 0)
    {
        free(right_array);
        free(left_array);
        return -3;
    }

    merge(arr, left_array, right_array, size_left_array, size_right_array);
    free(left_array);
    free(right_array);
}


int main()
{
    int arr[] = {8, 2, 5, 3, 4, 7, 6, 1};
    size_t arrSize = sizeof(arr) / sizeof(arr[0]);
    printf("Before sort\n");
    for (int i = 0; i < arrSize; i++)
    {
        printf("%d\n", arr[i]);
    }

    mergeSort(arr, arrSize);

    printf("After sort\n");
    for (int i = 0; i < arrSize; i++)
    {
        printf("%d\n", arr[i]);
    }

    return 0;
}