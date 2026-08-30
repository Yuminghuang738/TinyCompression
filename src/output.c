#include "output.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "statistics.h"
#include "bit_io.h"

static void serialize_tree(struct HuffmanTree *node, struct BitWrite *bitwrite)
{
    //leaf node: node->left == NULL and node->right == NULL
    if (node->left == NULL)
    {
        bit_write(bitwrite, LEAF_NODE);
        for (size_t bit_pos = 0; bit_pos < BYTE_LENGTH; bit_pos++)
        {
            bit_write(bitwrite, (node->byte_value >> (BYTE_LENGTH - 1 - bit_pos)) & 1U);
        }
    }
    else
    {
        bit_write(bitwrite, MERGE_NODE);
        serialize_tree(node->left, bitwrite);
        serialize_tree(node->right, bitwrite);
    }
}

void head_output(struct HuffmanTree *root, struct BitWrite *bitwrite, uint64_t total_counts)
{
    fwrite(&total_counts, sizeof(total_counts), WRITE_NUM, bitwrite->write_fp);
    
    bitwrite->bit_used = 0;
    bitwrite->write_buffer = 0;
    
    //node->left: merge_node, write 0, node->right: leaf_node, write 1 and byte_value, root node write nothing
    serialize_tree(root, bitwrite);

    bit_flush(bitwrite);
}

void code_output(struct HuffmanCode *huffmancode, struct BitWrite *bitwrite, FILE *read_fp)
{
    bitwrite->bit_used = 0;
    bitwrite->write_buffer = 0;
    
    struct Buffer *buffer = malloc(sizeof(struct Buffer));
    if (buffer == NULL)
    {
        perror("Error while allowcating buffer struct!\n");
        return;
    }

    buffer->size = sizeof(*(buffer->buffer_ptr)) * READ_COUNT;
    buffer->buffer_ptr = malloc(buffer->size);
    if (buffer->buffer_ptr == NULL)
    {
        perror("Error while allowcating buffer memory!\n");
        free(buffer);
        return;
    }

    size_t count = 0;
    while ((count = fread(buffer->buffer_ptr, READ_SIZE, READ_COUNT, read_fp)) > 0)
    {
        for (size_t cur_byte = 0; cur_byte < count; cur_byte++)
        {   
            uint8_t byte = buffer->buffer_ptr[cur_byte];
            uint32_t code_val = huffmancode[byte].code_val;
            uint8_t code_len = huffmancode[byte].code_len;

            for (size_t bit_pos = 0; bit_pos < code_len; bit_pos++)
            {
                bit_write(bitwrite, (code_val >> (code_len - 1 - bit_pos)) & 1U);
            }
        }
    }
    bit_flush(bitwrite);

    free(buffer->buffer_ptr);
    free(buffer);
}