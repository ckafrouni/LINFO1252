#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "Stack.h"

#define INIT_CAPACITY 16

struct stack_t {
    void *stack;
    size_t elem_size;
    size_t capacity;
    size_t top;
};


stack_t *create_stack(size_t elem_size)
{

    stack_t *stack = (stack_t *)malloc(sizeof(stack_t));
    if (stack == NULL)
    {
        exit(EXIT_FAILURE);
    }
    stack->capacity = INIT_CAPACITY;
    stack->elem_size = elem_size;
    stack->top = 0;

    stack->stack = malloc(sizeof(char *) * INIT_CAPACITY);
    if (stack->stack == NULL)
    {
        exit(EXIT_FAILURE);
    }

    return stack;
}

void free_stack(stack_t *stack)
{
    free(stack->stack);
    free(stack);
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
        stack->stack = realloc(stack->stack, stack->capacity * sizeof(char *));

        if (stack->stack == NULL)
        {
            exit(EXIT_FAILURE);
        }
    }

    ((char *)stack->stack)[stack->top * sizeof(char *)] = (char *)value;
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

    return ret_val;
}

// Implement a generic display function
void print_stack(stack_t *stack, void (*print_func)(void *))
{
    printf("\033[1m");

    for (size_t i = 0; i < stack->top; ++i)
    {
        void *elem = (char *)stack->stack + i * sizeof(char *);
        printf("| ");
        print_func(elem); // Call the print function
        printf(" ");
    }

    printf("\033[31m<TOP\n");
    printf("\033[0m");
}