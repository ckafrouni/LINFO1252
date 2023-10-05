#include "utils.h"

void sort(void *base, size_t nel, size_t width, int (*compar)(const void *, const void *))
{
    char *arr = (char *)base;
    for (size_t i = 0; i < nel-1; i++)
    {
        // print_{str|int}_array(base, nel);
        int swapped = 0;
        for (size_t j = 0; j < nel - i - 1; j++)
        {
            if (compar(arr + width * j, arr + width * (j+1)) > 0) {
                swap(arr + width * j, arr + width * (j+1), width);
                swapped = 1;
            }
            
        }
        if (!swapped) break;
    }
}

// int main(int argc, char **argv)
// {
//     char *str_base[9] = {"abc", "bak", "k", "abc", "aA", "m", "L", "a", "j"};
//     size_t nel1 = 9;
//     size_t str_width = sizeof(char *);

//     print_str_array(str_base, nel1);
//     printf("\n");
//     sort(str_base, nel1, str_width, compare_str);
//     printf("\n");
//     print_str_array(str_base, nel1);

//     int int_base[9] = {1, 4, 5, 1, 2, 6, 3, 4, 9};
//     size_t nel2 = 9;
//     size_t int_width = sizeof(int);

//     print_int_array(int_base, nel2);
//     printf("\n");
//     sort(int_base, nel2, int_width, compare_int);
//     printf("\n");
//     print_int_array(int_base, nel2);

//     return EXIT_SUCCESS;
// }
