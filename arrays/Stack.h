#if !defined(STACK_H)
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

typedef struct stack_t stack_t;

stack_t *create_stack(size_t elem_size);

void free_stack(stack_t *stack);

int is_empty(stack_t *stack);

void push(stack_t *stack, void *value);

void *pop(stack_t *stack);

void print_stack(stack_t *stack, void (*print_func)(void *));

#endif // STACK_H
