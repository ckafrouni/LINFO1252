#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

#include "my_malloc.h"

/**
 * This heap is build as a doubly linked, explicit list.
 *
 * Explicit list, meaning each free block points towards the next free block.
 * Unlike implicit list, where every block points to the next, wether it is free, or not.
 *
 * Doubly linked, meaning each block starts and ends with a metadata word. Allowing traversing both ways.
 * Free block contain on top of that, two extra words, one containing a pointer to the next free block, and
 * another containing a pointer towards the previous free block.
 * --
 * Our heap size is 64 [kb], and we chose 2 [byte] length words.
 * --
 * The heap starts with a word that points towards the first free block.
 */

#define HEAP_SIZE 64000 // Amount of bytes
#define WORD 2          // Words are 2 bytes long
#define MIN_BLOCK_SIZE 4 * WORD

uint8_t MY_HEAP[64000];

void my_init()
{
    // Initialize start block to point to 1st free block
    uint16_t *start = (uint16_t *)MY_HEAP;
    *start = WORD;

    uint16_t *block = (uint16_t *)(MY_HEAP + 1 * WORD);
    uint16_t block_size = HEAP_SIZE - 1 * WORD;
    *block = block_size;               // 1st: block size (in bytes)
    *(block + 1 * WORD) = 0;           // 2nd: ptr to next free block (here: null)
    *(block + 2 * WORD) = 0;           // 3rd: ptr to previous free block
    *(block + *block - WORD) = *block; // last: = 1st
}

void *my_malloc(size_t size)
{
    size +=  2 * WORD; // Additional words for metadata

    uint16_t *start = (uint16_t *)MY_HEAP;
    uint16_t *current = (uint16_t *)(MY_HEAP + *start);

    while (current != NULL)
    {
        uint16_t block_size = *current;
        if (block_size >= size)
        {
            uint16_t remaining_size = block_size - size;
            uint16_t *new_block;

            if (remaining_size >= MIN_BLOCK_SIZE)
            {
                // Split block
                new_block = current + size;
                *new_block = remaining_size;
                *(new_block + 1 * WORD) = *(current + 1 * WORD);
                *(new_block + 2 * WORD) = *(current + 2 * WORD);
                *(new_block + *new_block - WORD) = *new_block;
            }

            // Update current block
            *current = size;
            *(current + size - WORD) = size;

            // CETTE PARTIE VIENT DE CHATGPT
            // Update previous block's next pointer
            // uint16_t previous_offset = *(current + 2 * WORD);
            // if (previous_offset)
            // {
            //     uint16_t *previous = (uint16_t *)(MY_HEAP + previous_offset);
            //     *(previous + 1 * WORD) = (uint8_t *)new_block ? (uint8_t *)new_block - MY_HEAP : 0;
            // }
            // Update next block's previous pointer
            // uint16_t next_offset = *(current + 1 * WORD);
            // if (next_offset)
            // {
            //     uint16_t *next = (uint16_t *)(MY_HEAP + next_offset);
            //     *(next + 2 * WORD) = (uint8_t *)new_block ? (uint8_t *)new_block - MY_HEAP : 0;
            // }

            return (void *)(current + 1 * WORD);
        }

        current = *(current + 1 * WORD);
    }

    return NULL;
}