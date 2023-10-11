#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "my_malloc.h"

uint8_t MY_HEAP[64000];

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
    *(block + (block_size / 2) - 1) = block_size; // last: = 1st
}

void *my_malloc(size_t size)
{
    const uint16_t METADATA_SIZE = 2;
    const uint16_t MIN_BLOCK_SIZE = 3 * METADATA_SIZE;

    size += 2 * METADATA_SIZE; // Additional words for metadata
    size = size < MIN_BLOCK_SIZE ? MIN_BLOCK_SIZE : size;
    size = (size + 1) & ~1; // rounding to nearest even size

    uint16_t *start = (uint16_t *)MY_HEAP;
    uint16_t *current = (uint16_t *)(MY_HEAP + *start);
    uint16_t *prev = NULL;

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
                *(new_block + (remaining_size / 2) - 1) = remaining_size;
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

            if (prev == NULL)
            {
                *start = new_block == NULL ? *(current + 1) : (uint8_t *)new_block - MY_HEAP; // offset from MY_HEAP
            }
            else
            {
                *(prev + 1) = new_block == NULL ? *(current + 1) : (uint8_t *)new_block - (uint8_t *)prev;
            }

            // Update current block
            *(current + 0) = size | 1;
            *(current + (size / 2) - 1) = size | 1;

            return (void *)(current + 1);
        }

        prev = current;
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

    const uint16_t HEAP_SIZE = 64000;

    uint16_t *ptr = ((uint16_t *)pointer) - 1; // ptr to header

    uint16_t size = *(ptr) & ~1;
    *ptr = size;
    *(ptr + (*ptr / 2) - 1) = size;

    uint16_t *start = (uint16_t *)MY_HEAP;
    uint16_t offset_from_start = (uint8_t *)ptr - (uint8_t *)start;

    // combine with block on the left if free
    // 0b10101000
    // if (offset_from_start != 2 && !(*(ptr - 1) & 1))
    // {
    //     // combine
    //     // adjust offset_from_start
    //     uint16_t *prev = ptr - (*(ptr - 1) / 2);
    //     printf("prev: %p\n", prev);
    // }

    // combine with block on the right if free
    if (offset_from_start + size != HEAP_SIZE)
    {
        // combine
        // boucle
    }

    if (offset_from_start < *start)
    {
        *start = offset_from_start;
    }
}