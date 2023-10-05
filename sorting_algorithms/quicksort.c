#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

void partition(void *base, int lo, int hi, size_t width, int (*compar)(const void *, const void *))
{
    char *arr = (char *)base;
    if (lo < hi)
    {
        char *pivot = arr + hi * width;
        int i = lo;

        for (int j = lo; j < hi; j++)
        {
            if (compar(arr + j * width, pivot) < 0)
            {
                swap(arr + i * width, arr + j * width, width);
                i++;
            }
        }

        swap(arr + i * width, pivot, width);

        partition(base, lo, i - 1, width, compar);
        partition(base, i + 1, hi, width, compar);
    }
}

void sort(void *base, size_t nel, size_t width, int (*compar)(const void *, const void *))
{
    partition(base, 0, nel - 1, width, compar);
}