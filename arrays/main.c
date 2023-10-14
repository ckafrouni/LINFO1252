#include <stdio.h>

#include "stack.h"

void print_int(void *data)
{
    printf("%d", *(int *)data);
}

void print(stack_t *stack)
{
    print_stack(stack, print_int);
}

int main()
{
    stack_t stack = create_stack(sizeof(int));

    int val1 = 1, val2 = 2, val3 = 3;
    push(&stack, &val1);
    print(&stack);

    push(&stack, &val2);
    print(&stack);

    push(&stack, &val3);

    print(&stack);

    // Don't forget to free the stack memory
    free(stack.stack);
    return 0;
}
