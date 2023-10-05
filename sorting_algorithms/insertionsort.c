#include "utils.h"

// PSEUDO

// for i from 1 to n-1
//     j = i
//     while j > 0 and array[j-1] > array[j]
//         swap array[j] and array[j-1]
//         j = j - 1

void sort(void *base, size_t nel, size_t width, int (*compar)(const void *, const void *))
{
    char *arr = (char *)base;

    for (size_t i = 0; i < nel - 1 ; i++)
    {
        size_t j = i;
        while (j > 0 && compar(arr + (j-1) * width, arr + j*width) > 0)
        {
            swap(arr + width * j, arr + width * (j-1), width);
            j--;
        }
    }
}