#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "Stack.h"

typedef struct node_t
{
    void *value;
    struct node_t *next;
} node_t;

struct stack_t {
    node_t *node;
    size_t elem_size;
    size_t top;
};

stack_t *create_stack(size_t elem_size)
{
    stack_t *stack = (stack_t *)malloc(sizeof(stack_t));
    if (stack == NULL)
    {
        exit(EXIT_FAILURE);
    }

    node_t *node = malloc(sizeof(node_t));
    if (node == NULL)
    {
        exit(EXIT_FAILURE);
    }
    node->next = NULL;
    node->value = NULL;

    stack->node = node;    
    stack->elem_size = elem_size;
    stack->top = 0;

    return stack;
}

void free_stack(stack_t *stack)
{
    free_node(stack->node);
    free(stack);
}

void free_node(node_t *node)
{
    if (node == NULL) return;
    if (node->value != NULL)
    {
        free(node->value);
    }
    free_node(node->next);
    free(node);
}

int is_empty(stack_t *stack)
{
    return stack->top == 0;
}

void push(stack_t *stack, void *value)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));
    node->next = stack->node;
    stack->node = node;

    node->value = value;
    stack->top++;
}

void *pop(stack_t *stack)
{
    if (is_empty(stack))
    {
        return NULL;
    }

    stack->top--;

    node_t *node = (node_t *)stack->node;
    void *ret_val = node->value;
    stack->node = node->next;

    free(node);

    return ret_val;
}

// Implement a generic display function
void print_stack(stack_t *stack, void (*print_func)(void *))
{
    printf("\033[1m");

    node_t *cursor = (node_t *)stack->node;
    for (size_t i = 0; i < stack->top; ++i)
    {
        void *elem = cursor->value;
        printf("| ");
        print_func(elem); // Call the print function
        printf(" ");
        cursor = cursor->next;
    }

    printf("\033[31m<TOP\n");
    printf("\033[0m");
}