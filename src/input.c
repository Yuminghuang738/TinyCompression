#include "input.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "bit_io.h"
#include "output.h"
#include "encode.h"

static struct HuffmanTree *deserialize_tree(struct BitRead *bitread)
{
    uint8_t flag = bit_read(bitread);

    if (flag == LEAF_NODE)
    {
        struct HuffmanTree *leaf_node = malloc(sizeof(struct HuffmanTree));
        
        leaf_node->byte_value = 0;
        leaf_node->freq = 0;
        leaf_node->left = NULL;
        leaf_node->right = NULL;
        leaf_node->next = NULL;

        for (size_t count = 0; count < BYTE_LENGTH; count++)
        {
            uint8_t bit = bit_read(bitread);
            leaf_node->byte_value |= (bit << (BYTE_LENGTH - count - 1));
        }

        return leaf_node;
    }
    else
    {
        struct HuffmanTree *merge_node = malloc(sizeof(struct HuffmanTree));

        merge_node->byte_value = 0;
        merge_node->freq = 0;
        merge_node->next = NULL;

        merge_node->left = deserialize_tree(bitread);
        merge_node->right = deserialize_tree(bitread);

        return merge_node;
    }
}

struct HuffmanTree *head_input(struct BitRead *bitread, uint64_t *total_counts)
{
    fread(total_counts, sizeof(*total_counts), WRITE_NUM, bitread->read_fp);

    struct HuffmanTree *root = deserialize_tree(bitread);

    return root;
}