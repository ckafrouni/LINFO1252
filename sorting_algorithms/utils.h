#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_str_array(char **array, size_t nel);

void print_int_array(int *array, size_t nel);

int compare_int(const void *x, const void *y);

int compare_str(const void *x, const void *y);

void swap(void *a, void *b, size_t width);

#endif // UTILS_H