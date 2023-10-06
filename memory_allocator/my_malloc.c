#include <stddef.h>
#include <stdint.h>

#include "my_malloc.h"

// Define the block header structure here if you're using one
// Or define macros/constants for bit manipulation

// The heap size
#define HEAP_SIZE 64000
#define WORD_SIZE sizeof(size_t)

// The heap itself
static uint8_t MY_HEAP[HEAP_SIZE];

// Initialize the memory allocator
void init()
{
    // We cast to (size_t *) in order to select WORD_SIZE bytes
    *((size_t *)MY_HEAP) = HEAP_SIZE;         // (bloc size & allocated flag) - 64000 & FREE
    *((size_t *)MY_HEAP + WORD_SIZE) = 0;     // (prev pointer) - NULL
    *((size_t *)MY_HEAP + 2 * WORD_SIZE) = 0; // (next pointer) - NULL
}

// Allocate a block of memory of the given size
void *my_malloc(size_t size)
{
    // TODO - work in progress, I feel I didn't really make use of next, and prev pointer yet.

    // Align to next word & add 2 more for header and footer
    size = (size + WORD_SIZE - 1) & ~(WORD_SIZE - 1);
    size += 2 * WORD_SIZE;

    size_t *current = (size_t *)MY_HEAP;
    while (current < MY_HEAP + HEAP_SIZE)
    {
        size_t current_size = *current & ~1;
        int allocated_flag = *current & 1;

        if (!allocated_flag && current_size >= size) 
        {
            // We found a seemingly suitable spot.
            // We just need to split if a free block can fit (needs 4 words)
            if (current_size >= 4 * WORD_SIZE)
            {
                // TODO
            }

            *current = *current | 1;
            return current + WORD_SIZE;
        }

        current = current + (current_size / WORD_SIZE);
    }
    

    return NULL;
}

// Free a previously allocated block of memory
void my_free(void *ptr)
{
    // Freeing code here
    // For example, insert the block back into the free list and
    // coalesce adjacent free blocks
}
