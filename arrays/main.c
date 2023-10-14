#include <stdio.h>

#include "Stack.h"

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
    stack_t *stack = create_stack(sizeof(int));

    int *v1 = (int *)malloc(sizeof(int));
    int *v2 = (int *)malloc(sizeof(int));
    int *v3 = (int *)malloc(sizeof(int));

    *v1 = 1;
    *v2 = 2;
    *v3 = 3;

    push(stack, v1);
    print(stack);

    push(stack, v2);
    print(stack);

    push(stack, v3);

    print(stack);

    int *vx = pop(stack);
    printf("Popped: %d\n", *vx);
    print(stack);

    // pop(stack);
    // print(stack);

    // pop(stack);
    // print(stack);

    // Don't forget to free the stack memory
    free(vx);
    free_stack(stack);
    return 0;
}
