#include <string.h>
#include <stdint.h>
#include <stdio.h>

#include "my_malloc.h"

void print_all_blocks()
{
    const uint16_t METADATA_SIZE = 2;
    uint16_t *start = (uint16_t *)MY_HEAP;
    uint16_t *current = (uint16_t *)(MY_HEAP + METADATA_SIZE); // Skip the initial "start" pointer

    printf("\033[34;1m=== HEAP STATE ===\n\033[0;1m");
    printf("heap address = %p\n", MY_HEAP);
    printf("1st free block's offset = %u\n", *start);
    printf("\033[34m------------------\n");

    int num_block = 0;
    while ((uint8_t *)current < MY_HEAP + sizeof(MY_HEAP))
    {
        uint16_t metadata = *current;
        uint16_t size = metadata & ~1;   // Mask out the lowest bit to get the size
        int is_allocated = metadata & 1; // Check the lowest bit to see if it's allocated
        uint16_t offset = (uint8_t *)current - (uint8_t *)MY_HEAP;

        printf("\033[31m#%d\033[0;1m\t", num_block);
        if (is_allocated)
        {
            printf("\033[33mallocated\toffset = %u\t%%p = %p\tsize = %u\tpayload size = %u\tcontent: \"%s\"\n\033[0;1m", offset, current, size, size - 2 * METADATA_SIZE, (char *)(current + 1));
        }
        else
        {
            uint16_t next_offset = *(current + 1);
            uint16_t prev_offset = *(current + 2);
            printf("\033[32mfree\t\toffset = %u\t%%p = %p\tsize = %u\tnext offset = %u\tprev offset = %u\n\033[0;1m", offset, current, size, next_offset, prev_offset);
        }

        num_block++;
        current += size / METADATA_SIZE; // Move to the next block based on the size
    }

    printf("\033[34m==================\n\033[0m");
}

int main()
{
    my_init();
    print_all_blocks();

    char *p = (char *)my_malloc(5);
    print_all_blocks();
    strcpy(p, "Hello");
    print_all_blocks();

    char *q = (char *)my_malloc(6);
    strcpy(q, "world!");
    print_all_blocks();

    char *pq = (char *)my_malloc(11);
    sprintf(pq, "%s %s", p, q);
    print_all_blocks();

    my_init();
    print_all_blocks();

    return 0;
}