#include "utils.h"

size_t find_smallest(void *base, size_t width, size_t lo, size_t hi, int (*compar)(const void *, const void *))
{
    char *arr = (char *)base;
    size_t smallest_addr = lo;
    for (size_t i = lo + 1; i < hi; i++)
    {
        if (compar(arr + i * width, arr + smallest_addr * width) < 0)
        {
            smallest_addr = i;
        }
    }
    return smallest_addr;
}

void sort(void *base, size_t nel, size_t width, int (*compar)(const void *, const void *))
{
    char *arr = (char *)base;

    for (size_t i = 0; i < nel - 1; i++)
    {
        size_t smallest_addr = find_smallest(base, width, i, nel, compar);
        swap(arr + i * width, arr + smallest_addr * width, width);
    }
}