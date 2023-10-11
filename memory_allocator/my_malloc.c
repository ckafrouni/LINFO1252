#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "my_malloc.h"

/**
 * This heap is build as a doubly linked, explicit list.
 *
 * Explicit list, meaning each free block points towards the next free block.
 * Unlike implicit list, where every block points to the next, wether it is free, or not.
 *
 * Doubly linked, meaning each block starts and ends with a metadata word. Allowing traversing both ways.
 * Free block contain on top of that, two extra words, one containing a offset to the next free block, and
 * another containing a offset towards the previous free block.
 * --
 * Our heap size is 64 [kb], and we chose 2 [byte] length words.
 * --
 * The heap starts with a word that points towards the first free block.
 */

uint8_t MY_HEAP[64000];

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

void my_init()
{
    const uint16_t METADATA_SIZE = 2;
    const uint16_t HEAP_SIZE = 64000;

    // Initialize start block to point to 1st free block
    uint16_t *start = (uint16_t *)MY_HEAP;
    uint16_t *block = (uint16_t *)(MY_HEAP + 1 * METADATA_SIZE);

    *start = METADATA_SIZE; // offset to first free block

    uint16_t block_size = HEAP_SIZE - 1 * METADATA_SIZE;
    *(block + 0) = block_size;                    // block size (in bytes)
    *(block + 1) = 0;                             // offset to next free block (0)
    *(block + 2) = 0;                             // offset to prev free block (0)
    *(block + (block_size / 2) - 1) = block_size; // last: = 1st
}

void *my_malloc(size_t size)
{
    const uint16_t METADATA_SIZE = 2;
    const uint16_t MIN_BLOCK_SIZE = 4 * METADATA_SIZE;

    size += 2 * METADATA_SIZE; // Additional words for metadata
    size = size < MIN_BLOCK_SIZE ? MIN_BLOCK_SIZE : size;
    size = (size + 1) & ~1; // rounding to nearest even size

    uint16_t *start = (uint16_t *)MY_HEAP;
    uint16_t *current = (uint16_t *)(MY_HEAP + *start);

    while (current != NULL)
    {
        uint16_t block_size = *(current + 0);
        if (block_size >= size)
        {
            uint16_t remaining_size = block_size - size;
            uint16_t *new_block;

            if (remaining_size >= MIN_BLOCK_SIZE)
            {
                // Split block
                new_block = current + (size / 2);
                *(new_block + 0) = remaining_size;
                *(new_block + 1) = *(current + 1); // offset to next free block
                *(new_block + 2) = *(current + 2); // offset to prev free block
                *(new_block + (remaining_size / 2) - 1) = remaining_size;

                if (*(new_block + 2) == 0)
                {
                    *start = (uint8_t *)new_block - MY_HEAP; // offset from MY_HEAP
                }
            }
            else
            {
                // Create unusable block, to be reclaimed by free later
                uint16_t *block = current + (size / 2);
                *(block + 0) = remaining_size;
                if (remaining_size != 2)
                {
                    *(block + (remaining_size / 2) - 1) = remaining_size;
                }
            }

            // Update current block
            *(current + 0) = size | 1;
            *(current + (size / 2) - 1) = size | 1;

            // Update previous block's next offset
            uint16_t *prev = *(current + 2) == 0 ? NULL : current - *(current + 2);
            if (prev)
            {
                *(prev + 1) = new_block ? (uint8_t *)new_block - (uint8_t *)(prev + 1) : *(current + 1);
            }

            // Update next block's previous offset
            uint16_t *next = *(current + 1) == 0 ? NULL : current + *(current + 1);
            if (next)
            {
                *(next + 2) = new_block ? (uint8_t *)(next + 2) - (uint8_t *)new_block : *(current + 2);
            }

            return (void *)(current + 1);
        }

        current = *(current + 1) == 0 ? NULL : current + *(current + 1);
    }

    return NULL;
}

void my_free(void *pointer)
{
    // Find the first previous free space
    //      if previous is adjacent => merge
    //          Change size of previous: previous += current
    //          Wait to point to next with the 'next pointer' of the previous => current becomes previous
    //      else
    //          Point to the head of previous
    //          Change 'next pointer' of previous to current

    // Find the next free space
    //      if next is adjacent => merge
    //          Change size of current: current += next
    //          Change 'next pointer' of current with the value form 'next pointer' of next
    //      else
    //          Point the 'next pointer' to the head of next
    //          Change 'previous pointer' of next to the head of current/previous of current
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