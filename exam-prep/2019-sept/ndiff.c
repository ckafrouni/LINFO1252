#include <stdio.h>
#include <stdlib.h>

int str_equals(size_t size, char *expected, char *actual)
{
    for (size_t i = 0; i < size; i++)
    {
        if (expected[i] != actual[i])
        {
            printf("expected[%ld] = '%c'\nactual[%ld] = '%c'\n", i, expected[i], i, actual[i]);
            return 0;
        }
    }
    return 1;
}

int contains(char *str, size_t size, char c)
{
    for (size_t i = 0; i < size; i++)
    {
        if (str[i] == c)
            return 1;
    }

    return 0;
}

char *append_char(char *str, size_t size, char c)
{
    str = (char *)realloc(str, size + 1);
    if (str == NULL)
        return NULL;
    str[size - 1] = c;
    str[size] = '\0';

    return str;
}

char *ndiff(char *string)
{
    char *res = (char *)malloc(1);
    res[0] = '\0';
    size_t res_size = 1;

    int i = 0;
    while (string[i] != '\0')
    {
        if (!contains(res, res_size, string[i]))
        {
            res = append_char(res, res_size, string[i]);
            if (res == NULL)
                return NULL;
            res_size++;
        }
        i++;
    }
    printf("res = '%s'\n", res);
    return res;
}

int main()
{
    char *ndiff1 = ndiff("AABABBC");
    char *expected1 = "ABC";
    if (!str_equals(4, expected1, ndiff1))
    {
        printf("1 fu.\n");
    }
    free(ndiff1);

    char *ndiff2 = ndiff("ZZZZ12AAZZ21");
    char *expected2 = "Z12A";
    if (!str_equals(5, expected2, ndiff2))
    {
        printf("2 fu.\n");
    }
    free(ndiff2);
}
