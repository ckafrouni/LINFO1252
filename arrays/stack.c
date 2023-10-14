#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "stack.h"

stack_t create_stack(size_t elem_size)
{
    stack_t stack = {
        .stack = malloc(elem_size * INIT_CAPACITY),
        .elem_size = elem_size,
        .capacity = INIT_CAPACITY,
        .top = 0};

    if (stack.stack == NULL)
    {
        exit(EXIT_FAILURE);
    }

    return stack;
}

int is_empty(stack_t *stack)
{
    return stack->top == 0;
}

void push(stack_t *stack, void *value)
{
    if (stack->capacity == stack->top)
    {
        stack->capacity *= 2;
        stack->stack = realloc(stack->stack, stack->capacity * stack->elem_size);

        if (stack->stack == NULL)
        {
            exit(EXIT_FAILURE);
        }
    }

    memcpy((char *)stack->stack + stack->elem_size * stack->top, value, stack->elem_size);
    stack->top++;
}

void *pop(stack_t *stack)
{
    if (is_empty(stack))
    {
        return NULL;
    }

    stack->top--;

    void *ret_val = malloc(stack->elem_size);
    if (ret_val == NULL)
    {
        exit(EXIT_FAILURE);
    }

    memcpy(ret_val, (char *)stack->stack + stack->top * stack->elem_size, stack->elem_size);
    return ret_val;
}

// Implement a generic display function
void print_stack(stack_t *stack, void (*print_func)(void *))
{
    printf("\033[1m");

    for (size_t i = 0; i < stack->top; ++i)
    {
        void *elem = (char *)stack->stack + i * stack->elem_size;
        printf("| ");
        print_func(elem); // Call the print function
        printf(" ");
    }

    printf("\033[31m<TOP\n");
    printf("\033[0m");
}