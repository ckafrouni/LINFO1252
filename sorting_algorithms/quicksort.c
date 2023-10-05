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

int main(int argc, char **argv)
{
    char *str_base[9] = {"abc", "bak", "k", "abc", "aA", "m", "L", "a", "j"};
    size_t nel = 9;
    size_t str_width = sizeof(char *);

    print_str_array(str_base, nel);
    sort(str_base, nel, str_width, compare_str);
    print_str_array(str_base, nel);

    int int_base[9] = {1, 4, 5, 1, 2, 6, 3, 4, 9};
    size_t int_width = sizeof(int);

    print_int_array(int_base, nel);
    sort(int_base, nel, int_width, compare_int);
    print_int_array(int_base, nel);

    return EXIT_SUCCESS;
}
