#if !defined(STACK_H)
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#define INIT_CAPACITY 16

typedef struct stack_t
{
    void *stack;
    size_t elem_size;
    size_t capacity;
    size_t top;
} stack_t;

stack_t create_stack(size_t elem_size);

int is_empty(stack_t *stack);

void push(stack_t *stack, void *value);

void *pop(stack_t *stack);

void print_stack(stack_t *stack, void (*print_func)(void *));

#endif // STACK_H
