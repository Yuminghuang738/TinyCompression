#include "decode.h"

#include <stdint.h>
#include <stdio.h>

#include "encode.h"
#include "bit_io.h"

void huffman_decode(struct HuffmanTree *root, struct BitRead *bitread, FILE *write_fp,
                    uint64_t total_counts)
{
    struct HuffmanTree *current = root;
    uint64_t decode_count = 0;

    while (decode_count < total_counts)
    {
        uint8_t bit = bit_read(bitread);

        if (bit == 0)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }

        if (current->left == NULL)
        {
            fputc(current->byte_value, write_fp);
            
            decode_count++;
            current = root;
        }
    }
}