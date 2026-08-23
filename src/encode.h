#ifndef ENCODE_H
#define ENCODE_H

#include <stdint.h>
#include <stddef.h>

#include "statistics.h"

struct HuffmanTree
{
    uint8_t byte_value;
    size_t freq;
    struct HuffmanTree *left;
    struct HuffmanTree *right;
    struct HuffmanTree *next;
};

struct HuffmanCode
{
    uint32_t code_val;
    uint8_t code_len;
};

void huffman_encode(struct Statistics *statistics, struct HuffmanCode *huffmancode);

void traversal_tree(struct HuffmanTree *node, uint32_t current_code_val, uint8_t current_depth, 
                    struct HuffmanCode *huffmancode);

#endif