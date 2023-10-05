#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
void print_str_array(char **array, size_t size)
{
    printf("{");
    for (size_t i = 0; i < size; i++)
    {
        printf("%s, ", array[i]);
    }
    printf("}\n");
}

void qsort_recursion(char **base, int lo, int hi, int (*compar)(const void *, const void *))
{
    if (lo < hi)
    {
        char *pivot = base[hi];

        int i = lo;

        for (int j = lo; j < hi; j++)
        {
            printf("pivot: %s\tbase[%d]: %s\n", pivot, j, base[j]);
            if (compar(base[j], pivot) < 0)
            {
                // swap arr[i] & arr[j]
                char *tmp = base[i];
                base[i] = base[j];
                base[j] = tmp;
                i++;
            }
        }

        // swap pivot (base[hi]) & base[i]
        char *tmp = base[i];
        base[i] = base[hi];
        base[hi] = tmp;
        print_str_array(base, 9);
        printf("End it\n");

        qsort_recursion(base, lo, i - 1, compar);
        qsort_recursion(base, i + 1, hi, compar);
    }
}

void sort(void *base, size_t nel, size_t width, int (*compar)(const void *, const void *))
{
    // void *base ou char *base ou char **base ... ??
    qsort_recursion(base, 0, nel - 1, compar);
}

int compareStr(const void *s1, const void *s2)
{
    char *str1 = (char *)s1;
    char *str2 = (char *)s2;
    int i = 0;

    while (str1[i] && (tolower(str1[i]) == tolower(str2[i])))
    {
        i++;
    }

    return tolower(str1[i]) - tolower(str2[i]);
}

int compareInt(const void *i1, const void *i2) {
    return i1 < i2;
}

int main(int argc, char **argv)
{
    //char *base[9] = {"abc", "bak", "k", "abc", "aA", "m", "l", "a", "j"};
    int *base[9] = {1, 4, 5, 1, 2, 6, 3, 4, 9};
    size_t nel = 9;
    size_t width = sizeof(char *);

    //print_str_array(base, nel);

    sort(base, nel, width, compareInt);

    printf("%d\n", compareInt(&base[2], &base[2]));

    //print_str_array(base, nel);
    return EXIT_SUCCESS;
}
