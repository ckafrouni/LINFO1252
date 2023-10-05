#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_str_array(char **array, size_t nel)
{
    printf("\033[1;36m[\033[0m"); // Cyan for opening bracket
    for (size_t i = 0; i < nel; ++i)
    {
        printf("\033[1;35m\"%s\"\033[0m", array[i]); // Purple for strings
        if (i < nel - 1)
        {
            printf("\033[1;36m, \033[0m"); // Cyan for comma
        }
    }
    printf("\033[1;36m]\033[0m\n"); // Cyan for closing bracket
}

void print_int_array(int *array, size_t nel)
{
    printf("\033[1;36m[\033[0m"); // Cyan for opening bracket
    for (size_t i = 0; i < nel; ++i)
    {
        printf("\033[1;31m%d\033[0m", array[i]); // Red for integers
        if (i < nel - 1)
        {
            printf("\033[1;36m, \033[0m"); // Cyan for comma
        }
    }
    printf("\033[1;36m]\033[0m\n"); // Cyan for closing bracket
}

int compare_int(const void *x, const void *y)
{
    int a = *(int *)x;
    int b = *(int *)y;
    return a - b;
}

int compare_str(const void *x, const void *y)
{
    char *a = *(char **)x;
    char *b = *(char **)y;

    int i = 0;
    while (a[i] && b[i])
    {
        // a[i] is the current character in a, same for b[i]
        char a_lower = (a[i] >= 'A' && a[i] <= 'Z') ? a[i] + 32 : a[i];
        char b_lower = (b[i] >= 'A' && b[i] <= 'Z') ? b[i] + 32 : b[i];

        if (a_lower != b_lower)
        {
            return a_lower - b_lower;
        }

        i++;
    }

    return a[i] - b[i];
}

void swap(void *a, void *b, size_t width)
{
    char tmp[width];
    memcpy(tmp, a, width);
    memcpy(a, b, width);
    memcpy(b, tmp, width);
}
